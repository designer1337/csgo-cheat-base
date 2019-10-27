#include "..//..//dependencies/common_includes.hpp"
#include "FGUI/dependencies/aliases.hh"
#include "FGUI/dependencies/definitions.hh"

namespace fgui_input {

	void initialize();

	fgui::state get_key_state(const fgui::key& key);
	fgui::point get_mouse_position();
	fgui::delta get_scroll_delta();
}