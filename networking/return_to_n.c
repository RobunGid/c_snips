#define MAX_SEQ 7

typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready} event_type;

#include "protocol.h"

static boolean between(seq_nr a, seq_nr b, seq_nr c)
{
    /* Returns true if a <= b < c cyclically; otherwise false */
    if (((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)))
        return(true);
    else
        return(false);
}

static void send_data(seq_nr frame_nr, seq_nr frame_expected, packet buffer[])
{
    /* Prepare and send an information frame */
    frame s;                  // Temporary variable
    s.info = buffer[frame_nr]; // Insert packet into frame
    s.seq = frame_nr;          // Insert sequence number into frame
    s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1); // Acknowledgment embedded in data frame
    to_physical_layer(&s);     // Send frame
    start_timer(frame_nr);     // Start timer for waiting acknowledgment
}

void protocol5(void)
{
    seq_nr next_frame_to_send; // Next frame to send
    seq_nr ack_expected;        // Oldest unacknowledged frame
    seq_nr frame_expected;      // Next frame expected in incoming stream
    frame r;                    // Temporary variable
    packet buffer[MAX_SEQ + 1]; // Buffers for outgoing frames
    seq_nr nbuffered;           // Number of outstanding frames in use
    seq_nr i;                   // Buffer array index
    event_type event;           // Allow network_layer_ready events

    enable_network_layer();     // Enable network layer
    ack_expected = 0;           // Next expected incoming acknowledgment
    next_frame_to_send = 0;     // Next frame to send
    frame_expected = 0;         // Next expected incoming frame
    nbuffered = 0;              // Initially buffer is empty

    while (true) {              // Four possible events: see event_type above
        wait_for_event(&event);

        switch(event) {
            case network_layer_ready:
                /* Network layer has a packet ready to send */
                from_network_layer(&buffer[next_frame_to_send]); // Get new packet from network layer
                nbuffered = nbuffered + 1;                      // Increase sender window
                send_data(next_frame_to_send, frame_expected, buffer); // Send frame
                inc(next_frame_to_send);                         // Increment upper edge of sender window
                break;

            case frame_arrival:
                /* Frame with data or acknowledgment has arrived */
                from_physical_layer(&r);                        // Receive arrived frame from physical layer
                if (r.seq == frame_expected) {
                    /* Frames are accepted only in order */
                    to_network_layer(&r.info);                  // Deliver packet to network layer
                    inc(frame_expected);                        // Move lower edge of receiver window
                }
                /* Acknowledgment for frame n implies frames n-1, n-2, etc. */
                while (between(ack_expected, r.ack, next_frame_to_send)) {
                    /* Send acknowledgment together with information frame */
                    nbuffered = nbuffered - 1;                // One frame less in buffer
                    stop_timer(ack_expected);                 // Frame arrived intact; stop timer
                    inc(ack_expected);                         // Reduce sender window
                }
                break;

            case cksum_err: break;   // Bad frames are simply ignored

            case timeout:
                /* Time expired; resend all unacknowledged frames */
                next_frame_to_send = ack_expected;           // Sequence number of first frame to resend
                for (i = 1; i <= nbuffered; i++) {
                    send_data(next_frame_to_send, frame_expected, buffer); // Resend one frame
                    inc(next_frame_to_send);                                  // Prepare to send next frame
                }
        }

        if (nbuffered < MAX_SEQ)
            enable_network_layer();
        else
            disable_network_layer();
    }
}
