#include "menu.hpp"

int current_tab = 0;
void menu::render() {
	if (!variables::menu::opened)
		return;

	render::draw_filled_rect(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(36, 36, 36, 255));
	render::draw_filled_rect(variables::menu::x, variables::menu::y, variables::menu::w, 30, color(25, 25, 25, 255));
	render::draw_filled_rect(variables::menu::x, variables::menu::y + 30, variables::menu::w, 2, color(36, 36, 36, 255));
	render::draw_text_string(variables::menu::x + 10, variables::menu::y + 8, render::fonts::watermark_font, "csgo-cheat", false, color(255, 255, 255, 255));

	menu_framework::tab(variables::menu::x, variables::menu::y + 32, 100, 30, render::fonts::watermark_font, "tab", current_tab, 0);
	menu_framework::tab(variables::menu::x, variables::menu::y + 32, 100, 30, render::fonts::watermark_font, "tab1", current_tab, 1);
	menu_framework::tab(variables::menu::x, variables::menu::y + 32, 100, 30, render::fonts::watermark_font, "tab2", current_tab, 2);

	switch (current_tab) {
	case 0:
		menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 75, 290, 220, render::fonts::watermark_font, "test group"); {
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 82, variables::menu::x + 280, render::fonts::watermark_font, "test checkbox", 0, variables::test_bool);
			menu_framework::slider(variables::menu::x + 10, variables::menu::y + 20, 138, 0.f, 101.f, variables::test_float, render::fonts::watermark_font, "test slider", 5);
		}
		break;
	case 1:
		break;
	case 2:
		break;
	}

	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30, 0);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}