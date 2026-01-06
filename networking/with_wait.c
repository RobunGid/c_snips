#include "protocol.h"

typedef enum {
	frame_arrival
} event_type;

void sender2(void) {
	frame s; // buffer for outgoing frame
	packet buffer; // buffer for outgoing packet
	event_type event;
	while (true) {
		from_network_layer(&buffer); // Get packet from network layer
		s.info = buffer; // Copy it to frame s for transmitting
		to_physical_layer(&s); // Sending frame
		wait_for_event(&event); // Dont continue untill allow
	}
}

void receiver2(void) {
	frame r, s; // Buffers for frames
	event_type event; 
	while (true) {
		wait_for_event(&event); // The only option is frame delivery (frame_arrival event)
		from_physical_layer(&r); // Get incoming frame
		to_network_layer(&r.info); // Transmit data to network layer
		to_physical_layer(&s); // Transmit empty frame to wake sender
	}
}