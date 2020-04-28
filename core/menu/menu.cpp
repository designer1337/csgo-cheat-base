#include "menu.hpp"

//todo auto elements positioning

static int current_tab = 0;
void menu::render() {
	if (!variables::menu::opened)
		return;

	render::draw_filled_rect(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(36, 36, 36, 255));
	render::draw_filled_rect(variables::menu::x, variables::menu::y, variables::menu::w, 30, color(25, 25, 25, 255));
	render::draw_filled_rect(variables::menu::x, variables::menu::y + 30, variables::menu::w, 2, color(36, 36, 36, 255));
	render::draw_text_string(variables::menu::x + 10, variables::menu::y + 8, render::fonts::watermark_font, "csgo-cheat", false, color::white());

	menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 35, 100, 260, render::fonts::watermark_font, "tabs", false); {
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2) - 35, 100, 30, render::fonts::watermark_font, "aimbot", current_tab, 0, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2), 100, 30, render::fonts::watermark_font, "visuals", current_tab, 1, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2) + 35, 100, 30, render::fonts::watermark_font, "misc", current_tab, 2, false);
	}

	switch (current_tab) {
	case 0:
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "aimbot", false); {
			menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 45, variables::menu::x + 375, render::fonts::watermark_font, "test checkbox", variables::test_bool);
			menu_framework::slider(variables::menu::x + 120, variables::menu::y + 60, 125, 0.f, 101.f, render::fonts::watermark_font, "test slider", variables::test_float);
		}
		break;
	case 1:
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "visuals", false); {

		}
		break;
	case 2:
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "misc", false); {

		}
		break;
	}

	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30, 0);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}