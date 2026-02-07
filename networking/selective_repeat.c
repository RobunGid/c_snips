#define MAX_SEQ 7      // Must be 2^L - 1
#define NR_BUFS ((MAX_SEQ + 1)/2)

typedef enum {
	frame_arrival, 
	cksum_err, 
	timeout, 
	network_layer_ready, 
	ack_timeout
} event_type;

#include "protocol.h"

boolean no_nak = true;         // Negative acknowledgment (NAK) has not been sent yet
seq_nr oldest_frame = MAX_SEQ + 1; // Initial value for simulator

static boolean between(seq_nr a, seq_nr b, seq_nr c)
{
    /* Same as in protocol 5, but shorter and trickier */
    return ((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a));
}

static void send_frame(frame_kind fk, seq_nr frame_nr, seq_nr frame_expected, packet buffer[])
{
    /* Construct and send a data frame, as well as positive or negative acknowledgment */
    frame s;                   // Temporary variable
    s.kind = fk;               // kind == data, ack or nak
    if (fk == data) s.info = buffer[frame_nr % NR_BUFS]; // Insert data into frame
    s.seq = frame_nr;          // Sequence number for data frames
    s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1); // Embedded acknowledgment
    if (fk == nak) no_nak = false; // Only one NAK per frame, please
    to_physical_layer(&s);     // Send frame
    if (fk == data) start_timer(frame_nr % NR_BUFS); // Start timer for data frame
    stop_ack_timer();           // Separate ACK frame not needed
}

void protocol6(void)
{
    seq_nr ack_expected;        // Lower edge of sender window
    seq_nr next_frame_to_send;  // Upper edge of sender window + 1
    seq_nr frame_expected;      // Lower edge of receiver window
    seq_nr too_far;             // Upper edge of receiver window + 1
    int i;                      // Buffer array index
    frame r;                    // Temporary variable
    packet out_buf[NR_BUFS];    // Outgoing buffers
    packet in_buf[NR_BUFS];     // Incoming buffers
    boolean arrived[NR_BUFS];   // Incoming bitmap
    seq_nr nbuffered;           // Number of outstanding frames
    event_type event;

    enable_network_layer();     // Initialization
    ack_expected = 0;           // Next expected incoming acknowledgment
    next_frame_to_send = 0;     // Next frame to send
    frame_expected = 0;         // Next expected incoming frame
    too_far = NR_BUFS;          // Upper edge of receiver window
    nbuffered = 0;              // Initially buffer is empty
    for (i = 0; i < NR_BUFS; i++) arrived[i] = false;

    while (true) {
        wait_for_event(&event); // Five possible events: see event_type above

        switch(event) {
            case network_layer_ready:
                /* Get, save and send new frame */
                nbuffered = nbuffered + 1; // Increase sender window
                from_network_layer(&out_buf[next_frame_to_send % NR_BUFS]); // Get new packet from network layer
                send_frame(data, next_frame_to_send, frame_expected, out_buf); // Send frame
                inc(next_frame_to_send); // Increase upper edge of sender window
                break;

            case frame_arrival:
                /* Data or acknowledgment frame has arrived */
                from_physical_layer(&r); // Receive frame from physical layer
                if (r.kind == data) {
                    /* Frame arrived intact */
                    if ((r.seq != frame_expected) && no_nak)
                        send_frame(nak, 0, frame_expected, out_buf); // Send NAK if out of order
                    else
                        start_ack_timer(); // Start timer for delayed ACK

                    if (between(frame_expected, r.seq, too_far) && (arrived[r.seq % NR_BUFS] == false)) {
                        /* Frames may arrive in any order */
                        arrived[r.seq % NR_BUFS] = true;         // Mark buffer as occupied
                        in_buf[r.seq % NR_BUFS] = r.info;        // Store data in buffer

                        while (arrived[frame_expected % NR_BUFS]) {
                            /* Deliver packet to network layer and slide window */
                            to_network_layer(&in_buf[frame_expected % NR_BUFS]);
                            no_nak = true;
                            arrived[frame_expected % NR_BUFS] = false;
                            inc(frame_expected);                 // Slide lower edge of receiver window
                            inc(too_far);                         // Slide upper edge of receiver window
                            start_ack_timer();                     // Start helper timer in case separate ACK is needed
                        }
                    }
                }

                if ((r.kind == nak) && between(ack_expected, (r.ack + 1) % (MAX_SEQ + 1), next_frame_to_send))
                    send_frame(data, (r.ack + 1) % (MAX_SEQ + 1), frame_expected, out_buf); // Resend requested frame

                while (between(ack_expected, r.ack, next_frame_to_send)) {
                    nbuffered = nbuffered - 1;                 // Acknowledged frames
                    stop_timer(ack_expected % NR_BUFS);        // Frame arrived intact
                    inc(ack_expected);                          // Slide lower edge of sender window
                }
                break;

            case cksum_err:
                if (no_nak) send_frame(nak, 0, frame_expected, out_buf); // Damaged frame
                break;

            case timeout:
                send_frame(data, oldest_frame, frame_expected, out_buf); // Timer expired, resend frame
                break;

            case ack_timeout:
                send_frame(ack, 0, frame_expected, out_buf); // ACK timeout, send acknowledgment
                break;
        }

        if (nbuffered < NR_BUFS) enable_network_layer();
        else disable_network_layer();
    }
}
