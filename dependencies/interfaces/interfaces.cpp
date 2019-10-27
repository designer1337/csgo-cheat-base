#include "interfaces.hpp"
#include "../common_includes.hpp"

i_base_client_dll* interfaces::client = nullptr;
i_input* interfaces::input = nullptr;
i_client_entity_list* interfaces::entity_list = nullptr;
iv_engine_client* interfaces::engine = nullptr;
i_client_mode* interfaces::clientmode = nullptr;
i_client_state* interfaces::clientstate = nullptr;
i_panel* interfaces::panel = nullptr;
i_surface* interfaces::surface = nullptr;
c_global_vars_base* interfaces::globals = nullptr;
i_material_system* interfaces::material_system = nullptr;
iv_model_info* interfaces::model_info = nullptr;
iv_model_render* interfaces::model_render = nullptr;
i_render_view* interfaces::render_view = nullptr;
i_console* interfaces::console = nullptr;
i_localize* interfaces::localize = nullptr;
i_game_event_manager2* interfaces::event_manager = nullptr;
i_inputsytem* interfaces::inputsystem = nullptr;
iv_debug_overlay* interfaces::debug_overlay = nullptr;
IDirect3DDevice9* interfaces::directx = nullptr;
trace* interfaces::trace_ray = nullptr;
glow_manager_t* interfaces::glow_manager = nullptr;
player_game_movement* interfaces::game_movement = nullptr;
player_prediction* interfaces::prediction = nullptr;
player_move_helper* interfaces::move_helper = nullptr;
i_weapon_system* interfaces::weapon_system = nullptr;

bool interfaces::initialize() {
	client = get_interface<i_base_client_dll, interface_type::index>("client_panorama.dll", "VClient018");
	if (!client)
		throw std::runtime_error("failed to initialize client interface.");

	entity_list = get_interface<i_client_entity_list, interface_type::index>("client_panorama.dll", "VClientEntityList003");
	if (!entity_list)
		throw std::runtime_error("failed to initialize entity_list interface.");

	engine = get_interface<iv_engine_client, interface_type::index>("engine.dll", "VEngineClient014");
	if (!engine)
		throw std::runtime_error("failed to initialize engine interface.");

	panel = get_interface<i_panel, interface_type::index>("vgui2.dll", "VGUI_Panel009");
	if (!panel)
		throw std::runtime_error("failed to initialize panel interface.");

	surface = get_interface<i_surface, interface_type::index>("vguimatsurface.dll", "VGUI_Surface031");
	if (!surface)
		throw std::runtime_error("failed to initialize surface interface.");

	material_system = get_interface<i_material_system, interface_type::index>("materialsystem.dll", "VMaterialSystem080");
	if (!material_system)
		throw std::runtime_error("failed to initialize material_system interface.");

	model_info = get_interface<iv_model_info, interface_type::index>("engine.dll", "VModelInfoClient004");
	if (!model_info)
		throw std::runtime_error("failed to initialize model_info interface.");

	model_render = get_interface<iv_model_render, interface_type::index>("engine.dll", "VEngineModel016");
	if (!model_render)
		throw std::runtime_error("failed to initialize model_render interface.");

	render_view = get_interface<i_render_view, interface_type::index>("engine.dll", "VEngineRenderView014");
	if (!render_view)
		throw std::runtime_error("failed to initialize render_view interface.");

	console = get_interface<i_console, interface_type::index>("vstdlib.dll", "VEngineCvar007");
	if (!console)
		throw std::runtime_error("failed to initialize console interface.");

	localize = get_interface<i_localize, interface_type::index>("localize.dll", "Localize_001");
	if (!localize)
		throw std::runtime_error("failed to initialize localize interface.");

	event_manager = get_interface<i_game_event_manager2, interface_type::index>("engine.dll", "GAMEEVENTSMANAGER002");
	if (!event_manager)
		throw std::runtime_error("failed to initialize event_manager interface.");

	debug_overlay = get_interface<iv_debug_overlay, interface_type::index>("engine.dll", "VDebugOverlay004");
	if (!debug_overlay)
		throw std::runtime_error("failed to initialize debug_overlay interface.");

	inputsystem = get_interface<i_inputsytem, interface_type::index>("inputsystem.dll", "InputSystemVersion001");
	if (!inputsystem)
		throw std::runtime_error("failed to initialize inputsystem interface.");

	trace_ray = get_interface<trace, interface_type::index>("engine.dll", "EngineTraceClient004");
	if (!trace_ray)
		throw std::runtime_error("failed to initialize trace_ray interface.");

	game_movement = get_interface<player_game_movement, interface_type::index>("client_panorama.dll", "GameMovement001");
	if (!game_movement)
		throw std::runtime_error("failed to initialize game_movement interface.");

	prediction = get_interface<player_prediction, interface_type::index>("client_panorama.dll", "VClientPrediction001");
	if (!prediction)
		throw std::runtime_error("failed to initialize prediction interface.");

	/*custom interfaces*/
	clientmode = **reinterpret_cast<i_client_mode * **>((*reinterpret_cast<uintptr_t * *>(client))[10] + 5);
	globals = **reinterpret_cast<c_global_vars_base * **>((*reinterpret_cast<uintptr_t * *>(client)[0] + 27));

	clientstate = **(i_client_state ***)(utilities::pattern_scan(GetModuleHandleA("engine.dll"), sig_client_state) + 1);
	directx = **(IDirect3DDevice9***)(utilities::pattern_scan(GetModuleHandleA("shaderapidx9.dll"), sig_directx) + 1);
	input = *(i_input**)(utilities::pattern_scan(GetModuleHandleA("client_panorama.dll"), sig_input) + 1);
	glow_manager = (glow_manager_t*)(*(uintptr_t*)(utilities::pattern_scan(GetModuleHandleA("client_panorama.dll"), sig_glow_manager) + 3));
	move_helper = **(player_move_helper***)(utilities::pattern_scan(GetModuleHandleA("client_panorama.dll"), sig_player_move_helper) + 2);
	weapon_system = *(i_weapon_system**)(utilities::pattern_scan(GetModuleHandleA("client_panorama.dll"), sig_weapon_data) + 2);

	console::log("[setup] interfaces initialized!\n");
	return true;
}