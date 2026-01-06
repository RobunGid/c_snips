#define MAX_PKT 1024 // Packet size in bytes
#define inc(k) if (k < MAX_SEQ) k = k+1; else k = 0
typedef enum {false, true} boolean; 
typedef unsigned int seq_nr; // Frame or ack ordinal numbers

typedef struct {
	unsigned char data[MAX_PKT];
} packet;

typedef enum {
	data, ack, nak
} frame_kind;

typedef struct {
	frame_kind kind;
	seq_nr seq;
	seq_nr ack;
	packet info;
} frame;

// Wait for an event and return the event type in the event variable
void wait_for_event(event_type *event);

// Get packet from network layer by channel
void from_network_layer(packet *p);

// Pass information from the received packet to the network layer
void to_network_layer(packet *p);

// Get the incoming packet from the physical layer and copy it to r
void from_physical_layer(frame *r);

// Pass frame to physical layer for sending
void to_physical_layer(frame *r);

// Start timer and allow timeout event
void start_timer (seq_nr k);

// Stop timer and disable timeout event
void stop_timer(seq_nr k);

// Start auxillary timer and allow ack_timeout event
void start_ack_timer(void);

// Stop auxillary timer and disable ack_timeout event
void stop_ack_timer(void);

// Allow network layer to initialize network_layer_ready event
void enable_network_layer(void);

// Disallow network layer to initialize network_layer_ready event
void disable_network_layer(void);

