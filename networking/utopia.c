#include "protocol.h"
typedef enum {
	frame_arrival
} event_type;

void sender1(void) {
	frame s; // buffer for outgoing frame
	packet buffer; // buffer for outgoing packet

	while (true) {
		from_network_layer(&buffer); // Get from network layer packet to transfer
		s.info = buffer; // Copy it to s frame for transmission
		to_physical_layer(&s); // Send frame by channel
	};
};

void receiver1(void) {
	frame r;
	event_type event;

	while (true) {
		wait_for_event(&event); // The only option is frame delivery (frame_arrival event)
		from_physical_layer(&r); // Get arrived frame
		to_network_layer(&r.info); // Send data to network layer
	};
};