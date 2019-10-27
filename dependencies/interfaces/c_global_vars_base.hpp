#pragma once

class c_global_vars_base {
public:
	float realtime;
	int frame_count;
	float absolute_frametime;
	float absolute_frame_start_time;
	float cur_time;
	float frame_time;
	int max_clients;
	int tick_count;
	float interval_per_tick;
	float interpolation_amount;
	int sim_ticks_this_frame;
	int network_protocol;
	void* p_save_data;
	bool is_client;
	bool is_remote_client;
	int timestamp_networking_base;
	int timestamp_randomize_window;
};