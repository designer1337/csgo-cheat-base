#include "fgui_menu.hpp"

void gui::initialize() {
	fgui::element_font title_font = { "Tahoma", 11, fgui::external::font_flags::SHADOW , false };
	REGISTER_NOTIFICATIONS(title_font);
	ADD_WINDOW(vars::container["#window"], 50, 50, "csgo-cheat", 560, 450, fgui::external::key_code::KEY_INSERT, title_font);
	REGISTER_CURSOR(fgui::cursor_type::ARROW, fgui::input_state::UNLOCKED);

	REGISTER_TAB(vars::tabs["#tab_panel"], 7, 1, title_font, vars::container["#window"], -1);

	ADD_TAB(vars::tabs["#tab_panel"], "aimbot"); {
		ADD_GROUPBOX(vars::container["#groupbox"], 15, 40, "group box 1", 260, 370, title_font, vars::container["#window"], 0, false, false, false);
		ADD_CONTROLLER(vars::container["#groupbox"], vars::tabs["#tab_panel"]);
		ADD_CHECKBOX(vars::checkbox["#checkbox"], 15, 15, "test checkbox", "vars.checkbox", title_font, vars::container["#groupbox"], 0);

		ADD_GROUPBOX(vars::container["#groupbox1"], 285, 40, "group box 2", 260, 370, title_font, vars::container["#window"], 0, false, false, false);
		ADD_CONTROLLER(vars::container["#groupbox1"], vars::tabs["#tab_panel"]);
	}

	ADD_TAB(vars::tabs["#tab_panel"], "visuals"); {
	}

	ADD_TAB(vars::tabs["#tab_panel"], "misc"); {
	}
}