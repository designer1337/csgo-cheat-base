#pragma once

#pragma pack(push, 1)

class i_net_channel_info {
public:

	enum {
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};

	virtual const char* get_name(void) const = 0;	// get channel name
	virtual const char* get_address(void) const = 0; // get channel IP address as string
	virtual float		get_time(void) const = 0;	// current net time
	virtual float		get_time_connected(void) const = 0;	// get connection time in seconds
	virtual int			get_buffer_size(void) const = 0;	// netchannel packet history size
	virtual int			get_data_rate(void) const = 0; // send data rate in byte/sec

	virtual bool		is_loop_back(void) const = 0;	// true if loopback channel
	virtual bool		is_timing_out(void) const = 0;	// true if timing out
	virtual bool		is_play_back(void) const = 0;	// true if demo playback

	virtual float		get_latency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		get_average_latency(int flow) const = 0; // average packet latency in seconds
	virtual float		get_average_loss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		get_average_choke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		get_average_data(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		get_average_packets(int flow) const = 0; // avg packets/sec
	virtual int			get_total_data(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			get_sequence_number(int flow) const = 0;	// last send seq number
	virtual bool		is_valid_packet(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		get_packet_time(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			get_packet_bytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		get_stream_progress(int flow, int* received, int* total) const = 0;  // TCP progress if transmitting
	virtual float		get_since_last_time_recieved(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		get_command_interpolation_ammount(int flow, int frame_number) const = 0;
	virtual void		get_packet_response_latency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke) const = 0;
	virtual void		get_remote_framerate(float* pflFrameTime, float* pflFrameTimeStdDeviation) const = 0;

	virtual float		get_timeout_seconds() const = 0;
};


class i_client_state {
public:
	char pad_0000[156];
	i_net_channel_info* net_channel;
	uint32_t challenge_count;
	double reconnect_time;
	int32_t retry_count;
	char pad_00A8[88];
	int32_t signon_state_count;
	char pad_0104[8];
	float next_cmd_time;
	int32_t server_count;
	uint32_t current_sequence;
	char pad_0118[8];
	char pad_0120[0x4C];
	int32_t delta_tick;
	bool is_paused;
	char pad_0171[3];
	int32_t view_entity;
	int32_t player_slot;
	char pad_017C[4];
	char level_name[260];
	char level_name_short[40];
	char pad_02AC[92];
	int32_t max_clients;
	char pad_030C[4083];
	uint32_t string_table_container;
	char pad_1303[14737];
	float last_server_tick_time;
	bool is_in_simulation;
	char pad_4C99[3];
	uint32_t old_tick_count;
	float tick_remainder;
	float frame_time;
	int32_t last_outgoing_command;
	int32_t choked_commands;
	int32_t last_command_ack;
	int32_t command_ack;
	int32_t sound_sequence;
	char pad_4CBC[80];
	vec3_t view_angles;

	void full_update() {
		delta_tick = -1;
	}
};

#pragma pack(pop)