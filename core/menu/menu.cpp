#include "menu.hpp"

//todo auto elements positioning

auto do_frame = [&](std::int32_t x,
		   		    std::int32_t y,
		  		    std::int32_t w,
				    std::int32_t h,
				    color bg,
				    color header_text,
				    color header_line,
					const std::string& name) {

	render::draw_filled_rect(x, y, w, h, bg);
	render::draw_filled_rect(x, y, w, 30, header_text);
	render::draw_filled_rect(x, y + 30, w, 2, header_line);
	render::draw_text_string(x + 10, y + 8, render::fonts::watermark_font, name, false, color::white());
};

void menu::render() {
	if (!variables::menu::opened)
		return;

	do_frame(
		// x
		variables::menu::x,
		// y
		variables::menu::y,
		// w
		variables::menu::w,
		// h
		variables::menu::h,
		// background
		color(36, 36, 36, 255),
		// header for text
		color(25, 25, 25, 255),
		// header line
		color(36, 36, 36, 255),
		// frame name
		"csgo-cheat"
	);

	menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 35, 100, 260, render::fonts::watermark_font, "tabs", false); {
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2) - 35, 100, 30, render::fonts::watermark_font, "aimbot", menu::current_tab, 0, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2), 100, 30, render::fonts::watermark_font, "visuals", menu::current_tab, 1, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2) + 35, 100, 30, render::fonts::watermark_font, "misc", menu::current_tab, 2, false);
	}

	switch (current_tab) {
		case 0:
		{
			menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "aimbot", false); {
				menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 45, variables::menu::x + 375, render::fonts::watermark_font, "test checkbox", variables::test_bool);
				menu_framework::slider(variables::menu::x + 120, variables::menu::y + 60, 125, 0.f, 101.f, render::fonts::watermark_font, "test slider", variables::test_float);
			}
			break;
		}
		case 1:
		{
			menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "visuals", false); {

			}
			break;
		}
		case 2:
		{
			menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "misc", false); {

			}
			break;
		}
	}

	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30, 0);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}