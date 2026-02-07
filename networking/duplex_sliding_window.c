#define MAX_SEQ 1 // In the protocol it must be equal to 1

typedef enum {
	frame_arrival, 
	cksum_err, 
	timeout
} event_type;

#include "protocol.h"

void protocol4(void)
{
    seq_nr next_frame_to_send; // Only 0 and 1
    seq_nr frame_expected;     // Only 0 and 1
    frame r, s;                // Temporary variables
    packet buffer;             // Current packet from network layer
    event_type event;

    next_frame_to_send = 0;    // Number of next frame in outgoing stream
    frame_expected = 0;        // Number of frame expected

    from_network_layer(&buffer); // Get first packet from network layer
    s.info = buffer;             // Prepare first frame for transmission
    s.seq = next_frame_to_send;  // Insert sequence number into frame
    s.ack = 1 - frame_expected;  // Acknowledgment embedded in data frame
    to_physical_layer(&s);       // Send frame
    start_timer(s.seq);           // Start timer for waiting acknowledgment

    while (true) {                // Wait for events: frame_arrival, cksum_err, timeout
        wait_for_event(&event);
        if (event == frame_arrival) { 
            from_physical_layer(&r);  // Receive the arrived frame
            if (r.seq == frame_expected) {
                to_network_layer(&r.info); // Deliver packet to network layer
                inc(frame_expected);       // Invert sequence number of next expected frame
            }
            if (r.ack == next_frame_to_send) {
                stop_timer(r.ack);        // Stop timer
                from_network_layer(&buffer); // Get next packet from network layer
                inc(next_frame_to_send);     // Invert sequence number of outgoing frame
            }
        }
    }

    s.info = buffer;             // Prepare frame for transmission
    s.seq = next_frame_to_send;  // Insert sequence number into frame
    s.ack = 1 - frame_expected;  // Sequence number of last received frame
    to_physical_layer(&s);       // Send frame
    start_timer(s.seq);           // Start timer for waiting acknowledgment
}
