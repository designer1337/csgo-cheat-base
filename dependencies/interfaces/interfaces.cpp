#include "interfaces.hpp"
#include "../utilities/csgo.hpp"

bool interfaces::initialize() {
	client = get_interface<i_base_client_dll, interface_type::index>("client.dll", "VClient018");
	if (client)
		console::log("interfaces client found at %p", client);

	entity_list = get_interface<i_client_entity_list, interface_type::index>("client.dll", "VClientEntityList003");
	if (entity_list)
		console::log("interfaces entity_list found at %p", entity_list);

	engine = get_interface<iv_engine_client, interface_type::index>("engine.dll", "VEngineClient014");
	if (entity_list)
		console::log("interfaces engine found at %p", engine);

	panel = get_interface<i_panel, interface_type::index>("vgui2.dll", "VGUI_Panel009");
	if (entity_list)
		console::log("interfaces panel found at %p", panel);

	surface = get_interface<i_surface, interface_type::index>("vguimatsurface.dll", "VGUI_Surface031");
	if (entity_list)
		console::log("interfaces surface found at %p", surface);

	material_system = get_interface<i_material_system, interface_type::index>("materialsystem.dll", "VMaterialSystem080");
	if (entity_list)
		console::log("interfaces material_system found at %p", material_system);

	model_info = get_interface<iv_model_info, interface_type::index>("engine.dll", "VModelInfoClient004");
	if (entity_list)
		console::log("interfaces model_info found at %p", model_info);

	model_render = get_interface<iv_model_render, interface_type::index>("engine.dll", "VEngineModel016");
	if (entity_list)
		console::log("interfaces model_render found at %p", model_render);

	render_view = get_interface<i_render_view, interface_type::index>("engine.dll", "VEngineRenderView014");
	if (entity_list)
		console::log("interfaces render_view found at %p", render_view);

	console = get_interface<i_console, interface_type::index>("vstdlib.dll", "VEngineCvar007");
	if (entity_list)
		console::log("interfaces console found at %p", console);

	localize = get_interface<i_localize, interface_type::index>("localize.dll", "Localize_001");
	if (entity_list)
		console::log("interfaces localize found at %p", localize);

	event_manager = get_interface<i_game_event_manager2, interface_type::index>("engine.dll", "GAMEEVENTSMANAGER002");
	if (entity_list)
		console::log("interfaces event_manager found at %p", event_manager);

	debug_overlay = get_interface<iv_debug_overlay, interface_type::index>("engine.dll", "VDebugOverlay004");
	if (entity_list)
		console::log("interfaces debug_overlay found at %p", debug_overlay);

	inputsystem = get_interface<i_inputsytem, interface_type::index>("inputsystem.dll", "InputSystemVersion001");
	if (entity_list)
		console::log("interfaces inputsystem found at %p", inputsystem);

	trace_ray = get_interface<trace, interface_type::index>("engine.dll", "EngineTraceClient004");
	if (entity_list)
		console::log("interfaces trace_ray found at %p", trace_ray);

	game_movement = get_interface<player_game_movement, interface_type::index>("client.dll", "GameMovement001");
	if (entity_list)
		console::log("interfaces game_movement found at %p", game_movement);

	prediction = get_interface<player_prediction, interface_type::index>("client.dll", "VClientPrediction001");
	if (entity_list)
		console::log("interfaces prediction found at %p", prediction);

	file_system = **reinterpret_cast<void***>(utilities::pattern_scan("engine.dll", sig_file_system) + 2);
	if (file_system)
		console::log("interfaces entity_list found at %p", file_system);

	// get the exported KeyValuesSystem function
	if (const HINSTANCE handle = GetModuleHandle("vstdlib.dll"))
	{		// set our pointer by calling the function
		key_values_system = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();
		if (key_values_system)
			console::log("interfaces key_values_system found at %p", key_values_system);
	}
	/*custom interfaces*/
	client_mode = **reinterpret_cast<i_client_mode * **>((*reinterpret_cast<uintptr_t * *>(client))[10] + 5);
	if (client_mode)
		console::log("interfaces client_mode found at %p", client_mode);

	globals = **reinterpret_cast<c_global_vars_base***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	if (globals)
		console::log("interfaces globals found at %p", globals);

	client_state = **reinterpret_cast<i_client_state***>(utilities::pattern_scan("engine.dll", sig_client_state) + 1);
	if (entity_list)
		console::log("interfaces client_state found at %p", client_state);

	directx = **reinterpret_cast<IDirect3DDevice9***>(utilities::pattern_scan("shaderapidx9.dll", sig_directx) + 1);
	if (entity_list)
		console::log("interfaces directx found at %p", directx);

	input = *reinterpret_cast<i_input**>(utilities::pattern_scan("client.dll", sig_input) + 1);
	if (entity_list)
		console::log("interfaces input found at %p", input);

	glow_manager = reinterpret_cast<glow_manager_t*>(*reinterpret_cast<uintptr_t*>(utilities::pattern_scan("client.dll", sig_glow_manager) + 3));
	if (entity_list)
		console::log("interfaces glow_manager found at %p", glow_manager);

	move_helper = **reinterpret_cast<player_move_helper***>(utilities::pattern_scan("client.dll", sig_player_move_helper) + 2);
	if (entity_list)
		console::log("interfaces move_helper found at %p", move_helper);

	weapon_system = *reinterpret_cast<i_weapon_system**>(utilities::pattern_scan("client.dll", sig_weapon_data) + 2);
	if (entity_list)
		console::log("interfaces weapon_system found at %p", weapon_system);


	//memory stuffs
	alloc_key_values_client = utilities::pattern_scan("client.dll", sig_alloc_key_value) + 3;
	alloc_key_values_engine = utilities::pattern_scan("engine.dll", sig_alloc_key_value) + 3;

	console::log("interfaces initialized!");

	return true;
}
