#define MAX_SEQ 1

typedef enum {
	frame_arrival, cksum_err, timeout
} event_type;

#include "protocol.h"

void sender3(void) {
	seq_nr next_frame_to_send; // Sequential number of next outgoign frame
	frame s; 
	packet buffer; // Outgoing packet buffer
	event_type event; 

	next_frame_to_send = 0;      // Initializing outgoing serial packets
	from_network_layer(&buffer); // Get first packet from network layer
	while (true) {
		s.info = buffer;            // Form a frame to transmit
		s.seq = next_frame_to_send; // Insert sequence number in frame
		to_physical_layer(&s);      // Send frame over channel
		start_timer(s.seq);         // Start a waiting timer for confirmation
		wait_for_event(&event);     // Wait for frame_arrival, cksim_err or timeout event
		if (event == frame_arrival) {
			from_physical_layer(&s); // Get acknowledgement
			if (s.ack == next_frame_to_send) {
				stop_timer(s.ack);
				from_network_layer(&buffer); // Get next outgoing packet
				inc(next_frame_to_send); // Invert next_frame_to_send value
			}
		}

	}
}

void receiver3(void) {
	seq_nr frame_expected;
	frame r, s;
	event_type event;

	frame_expected = 0;
	while (true) {
		wait_for_event(&event);         // Wait for possible events: frame_arrival or cksum_err
		if (event == frame_arrival) {   // Arrived uncorrupted frame
			from_physical_layer(&r);     // Get incoming frame
			if (r.seq == frame_expected) { // This frame was expected
				to_network_layer(&r.info); // Transfer data to network layer
				inc(frame_expected);      // Wait for frame with incremented number 
			};
			s.ack = 1 - frame_expected; // Number of frame for acknowledgement waiting
			to_physical_layer(&s);      // Send acknowldgement
		}
	}
}