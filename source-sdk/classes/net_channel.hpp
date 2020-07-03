#pragma once

class i_net_channel {
private:
	uint8_t u0[0x17];
public:
	bool should_delete;
	int out_sequence_nr;
	int in_sequence_nr;
	int out_sequence_nr_ack;
	int out_reliable_state;
	int in_reliable_state;
	int choked_packets;
};
