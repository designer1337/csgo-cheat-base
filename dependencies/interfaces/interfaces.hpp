#pragma once
#include <windows.h>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "i_base_client_dll.hpp"
#include "i_client_entity_list.hpp"
#include "iv_engine_client.hpp"
#include "i_client_state.hpp"
#include "i_panel.hpp"
#include "i_surface.hpp"
#include "c_global_vars_base.hpp"
#include "i_material_system.hpp"
#include "iv_model_info.hpp"
#include "iv_model_render.hpp"
#include "iv_debug_overlay.hpp"
#include "i_console.hpp"
#include "i_localize.hpp"
#include "i_game_event_manager.hpp"
#include "i_input.hpp"
#include "i_input_system.hpp"
#include "i_trace.hpp"
#include "i_render_view.hpp"
#include "glow_manager.hpp"
#include "i_player_movement.hpp"
#include "i_weapon_system.hpp"

namespace interfaces {
	enum class interface_type { index, bruteforce };

	template <typename ret, interface_type type>
	ret* get_interface(std::string module_name, std::string interface_name) {
		using create_interface_fn = void* (*)(const char*, int*);
		create_interface_fn fn = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandle(module_name.c_str()), "CreateInterface"));

		if (fn) {
			void* result = nullptr;

			switch (type) {
			case interface_type::index:
				result = fn(interface_name.c_str(), nullptr);

				break;
			case interface_type::bruteforce:
				char buf[128];

				for (uint32_t i = 0; i <= 100; i++) {
					memset((void*)buf, 0, sizeof buf);

					result = fn(interface_name.c_str(), nullptr);

					if (result)
						break;
				}

				break;
			}
		
			if (!result)
				throw std::runtime_error(interface_name.c_str());

			return reinterpret_cast<ret*>(result);
		}

		return reinterpret_cast<ret*>(nullptr);
	}

	extern i_base_client_dll* client;
	extern i_input* input;
	extern i_client_entity_list* entity_list;
	extern iv_engine_client* engine;
	extern i_client_mode* clientmode;
	extern i_client_state* clientstate;
	extern i_panel* panel;
	extern i_surface* surface;
	extern c_global_vars_base* globals;
	extern i_material_system* material_system;
	extern iv_model_info* model_info;
	extern iv_model_render* model_render;
	extern i_render_view* render_view;
	extern iv_debug_overlay* debug_overlay;
	extern i_console* console;
	extern i_localize* localize;
	extern i_game_event_manager2* event_manager;
	extern i_inputsytem* inputsystem;
	extern IDirect3DDevice9* directx;
	extern trace* trace_ray;
	extern glow_manager_t* glow_manager;
	extern player_game_movement* game_movement;
	extern player_prediction* prediction;
	extern player_move_helper* move_helper;
	extern i_weapon_system* weapon_system;

	bool initialize();
}