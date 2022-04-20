#include "../../dependencies/utilities/csgo.hpp"
#include "../features/features.hpp"
#include "../features/misc/engine_prediction.hpp"
#include "../menu/menu.hpp"


bool hooks::initialize() {
	const auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::client_mode, 24));
	const auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));
	const auto on_screen_size_changed_target = reinterpret_cast<void*>(get_virtual(interfaces::surface, 116));
	//sv_pure by pass
	const auto sv_pure_loose_files_target = reinterpret_cast<void*>(get_virtual(interfaces::file_system, 128));
	const auto check_file_CRCs_with_server = reinterpret_cast<void*>(utilities::pattern_scan("engine.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80"));
	//bypass key_value to choose team etc when join a match
	const auto key_value_system_target = reinterpret_cast<void*>(get_virtual(interfaces::key_values_system, 1));

	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("failed to initialize MH_Initialize.");

	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move::original)) != MH_OK)
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse::original)) != MH_OK)
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");

	if (MH_CreateHook(on_screen_size_changed_target, &on_screen_size_changed::hook, reinterpret_cast<void**>(&on_screen_size_changed::original)) != MH_OK)
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");

	if (MH_CreateHook(key_value_system_target ,&alloc_key_value_memory::hook ,reinterpret_cast<void**>(&alloc_key_value_memory::original)) != MH_OK)
		throw std::runtime_error("failed to initialize alloc_key_value_memory. (outdated index?)");

	if (MH_CreateHook(sv_pure_loose_files_target, &sv_pure_loose_files::hook, nullptr) != MH_OK)
		throw std::runtime_error("failed to initialize sv_pure_loose_files. (outdated index?)");

	if (MH_CreateHook(check_file_CRCs_with_server, &check_file_CRCs_with_server::hook, nullptr) != MH_OK)
		throw std::runtime_error("failed to initialize sv_pure_loose_files. ");

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("failed to enable hooks.");
		
	console::log("hooks initialized!");
	return true;
}

void hooks::release() {
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}

bool __stdcall hooks::create_move::hook(float input_sample_frametime, c_usercmd* cmd) noexcept {
	if (!cmd || !cmd->command_number)
		return create_move::original(interfaces::client_mode, input_sample_frametime, cmd);

	if (create_move::original(interfaces::client_mode, input_sample_frametime, cmd))
		interfaces::engine->set_view_angles(cmd->viewangles);

	csgo::local_player = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);

	misc::movement::bunny_hop(cmd);

	prediction::start(cmd); {

	} prediction::end();

	return false;
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) noexcept {
	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));

	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):
		
		render::text(10, 10, render::fonts::menu_font, "csgo-cheat", false, color::white(255));

		menu::toggle();
		menu::render();

		break;

	case fnv::hash("FocusOverlayPanel"):
		interfaces::panel->set_keyboard_input_enabled(panel, variables::menu::opened);
		interfaces::panel->set_mouse_input_enabled(panel, variables::menu::opened);
		break;
	}

	paint_traverse::original(interfaces::panel, panel, force_repaint, allow_force);
}

void _stdcall hooks::on_screen_size_changed::hook(int oldWidth, int oldHeightt) {
	render::fonts::menu_font = interfaces::surface->font_create();
	interfaces::surface->set_font_glyph(render::fonts::menu_font, "Tahoma", 12, 500, 0, 0, font_flags::fontflag_antialias | font_flags::fontflag_outline);

	console::log("font has been re-initialized! due to screen size changed");
	variables::menu::x = 140; variables::menu::y = 140; variables::menu::w = 400; variables::menu::h = 300;

	on_screen_size_changed::original(oldHeightt, oldWidth);
}

void* __stdcall hooks::alloc_key_value_memory::hook(const std::int32_t size) noexcept {
	// if function is returning to speficied addresses, return nullptr to "bypass"
	if (const std::uint32_t address = reinterpret_cast<std::uint32_t>(_ReturnAddress());
		address == reinterpret_cast<std::uint32_t>(interfaces::alloc_key_values_engine) ||
		address == reinterpret_cast<std::uint32_t>(interfaces::alloc_key_values_client))
		return nullptr;

	// return original
	return alloc_key_value_memory::original(interfaces::key_values_system, size);
}

bool __fastcall hooks::sv_pure_loose_files::hook(void* ecx, void* edx) {
	return true;
}

void __fastcall hooks::check_file_CRCs_with_server::hook(void* ecx, void* edx) {
	return;
}