#include "fgui_input.hpp"

void fgui_input::initialize() {
	fgui::input.get_key_state = fgui_input::get_key_state;
	fgui::input.get_scroll_delta = fgui_input::get_scroll_delta;
	fgui::input.get_mouse_position = fgui_input::get_mouse_position;
}

fgui::state fgui_input::get_key_state(const fgui::key& key) {

	return interfaces::inputsystem->is_button_down(key);
}

fgui::delta fgui_input::get_scroll_delta() {

	return interfaces::inputsystem->get_analog_delta(analog_code_t::MOUSE_WHEEL);
}

fgui::point fgui_input::get_mouse_position() {

	static fgui::point temporary_point = { 0, 0 };
	interfaces::surface->surface_get_cursor_pos(temporary_point.x, temporary_point.y);

	return temporary_point;
}