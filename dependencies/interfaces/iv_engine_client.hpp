#pragma once
#include <cstdint>
#include "../../source-sdk/math/vector3d.hpp"
#include "../../source-sdk/math/vector2d.hpp"
#include "../../source-sdk/math/view_matrix.hpp"
#include "../../source-sdk/classes/net_channel.hpp"
#include "../../dependencies/utilities/utilities.hpp"

struct player_info_t {
	int64_t __pad0;
	union {
		int64_t xuid;
		struct {
			int xuidlow;
			int xuidhigh;
		};
	};
	char name[128];
	int userid;
	char guid[33];
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
};

class iv_engine_client {
public:
	i_net_channel* get_net_channel_info() {
		using original_fn = i_net_channel * (__thiscall*)(iv_engine_client*);
		return (*(original_fn * *)this)[78](this);
	}
	int get_local_player() {
		using original_fn = int(__thiscall*)(iv_engine_client*);
		return (*(original_fn * *)this)[12](this);
	}
	int get_player_for_user_id(int user_id) {
		using original_fn = int(__thiscall*)(iv_engine_client*, int);
		return (*(original_fn * *)this)[9](this, user_id);
	}
	void get_player_info(int index, player_info_t* info) {
		using original_fn = void(__thiscall*)(iv_engine_client*, int, player_info_t*);
		return (*(original_fn * *)this)[8](this, index, info);
	}
	void get_screen_size(int& width, int& height) {
		using original_fn = void(__thiscall*)(iv_engine_client*, int&, int&);
		return (*(original_fn * *)this)[5](this, width, height);
	}
	bool is_in_game() {
		using original_fn = bool(__thiscall*)(iv_engine_client*);
		return (*(original_fn * *)this)[26](this);
	}
	bool is_connected() {
		using original_fn = bool(__thiscall*)(iv_engine_client*);
		return (*(original_fn * *)this)[27](this);
	}
	void execute_cmd(const char* cmd) {
		using original_fn = void(__thiscall*)(iv_engine_client*, const char*);
		return (*(original_fn * *)this)[108](this, cmd); // this always seems to crash whilst debugging, just feel free to continue.
	}
	void set_view_angles(vec3_t& angles) {
		using original_fn = void(__thiscall*)(iv_engine_client*, vec3_t&);
		return (*(original_fn * *)this)[19](this, angles);
	}

	void get_view_angles(vec3_t& angles) {
		return utilities::call_virtual<void(__thiscall*)(void*, vec3_t&)>(this, 18)(this, angles);
	}

	view_matrix_t& world_to_screen_matrix() {
		using original_fn = view_matrix_t & (__thiscall*)(iv_engine_client*);
		return (*(original_fn * *)this)[37](this);
	}

	bool is_taking_screenshot() {
		using original_fn = bool(__thiscall*)(iv_engine_client*);
		return (*(original_fn * *)this)[92](this);
	}

	const char* get_level_name() {
		using original_fn = const char* (__thiscall*)(iv_engine_client*);
		return (*(original_fn * *)this)[53](this);
	}
};
