#include "framework.hpp"

//credits to harcuz for menu framework (https://www.unknowncheats.me/forum/members/2669363.html),
POINT cur;

void menu_framework::group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label) {
	//groupbox background
	render::draw_filled_rect(x, y, w, h, color(25, 25, 25, 255));

	//groupbox outline
	render::draw_rect(x, y, w, h, color(45, 45, 45, 255));

	//groupbox label
	if (show_label)
		render::draw_text_string(x + 2, y - 12, font, string, false, color::white());
}

void menu_framework::tab(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, std::int32_t& tab, std::int32_t count, bool outline) {
	GetCursorPos(&cur);

	if ((cur.x > x) && (cur.x < x + w) && (cur.y > y) && (cur.y < y + h) && (GetAsyncKeyState(VK_LBUTTON) & 1))
		tab = count;

	bool active = false;
	if (tab == count) active = true; else active = false;

	//tab background
	if (outline)
		render::draw_rect(x, y, w, h, active ? color(52, 134, 235, 255) : color(25, 25, 25, 255));

	//tab label
	render::draw_text_string(x - render::get_text_size(font, string).x / 2 + 50, y + h / 2 - 8, font, string, false, outline ? color::white() : active ? color(52, 134, 235, 255) : color::white());
}

void menu_framework::check_box(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, bool& var) {
	GetCursorPos(&cur);

	int w = 10, h = 10;

	if ((cur.x > position) && (cur.x < position + w) && (cur.y > y) && (cur.y < y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
		var = !var;

	//checkbox background
	render::draw_filled_rect(position, y, w, h, var ? color(52, 134, 235, 255) : color(36, 36, 36, 255));

	//checkbox label
	render::draw_text_string(x + 2, y - 1, font, string, false, color::white());
}

void menu_framework::slider(std::int32_t x, std::int32_t y, std::int32_t position, float min, float max, unsigned long font, const std::string string, float& value) {
	int ix = x + 140;
	GetCursorPos(&cur);
	int yi = y + 4;

	auto mouse_calculations = [](int start, int end, int _start, int _end) {
		int value = ((1920 / 2) - (1920 / 2)) + start; return cur.x - value; 
	};

	if ((cur.x > ix) && (cur.x < ix + position) && (cur.y > yi) && (cur.y < yi + 6) && (GetAsyncKeyState(VK_LBUTTON)))
		value = mouse_calculations(ix, y, position, 20) / (float(position) / float(max));

	//slider background
	render::draw_filled_rect(ix, yi, position, 6, color(36, 36, 36, 255));
	render::draw_filled_rect(ix, yi, value * (float(position) / float(max)), 6, color(52, 134, 235, 255));

	//slider label
	render::draw_text_string(x + 2, y - 1, font, (std::stringstream{ } << string << ": " <<  std::setprecision(3) << value).str(), false, color::white());
}

bool enabled[8][2];
POINT two;
bool menu_framework::menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h, std::int32_t index) {
	for (int i = 0; i < 8; i++)
		if (enabled[i][0] && i != index)
			return false;

	POINT one;
	GetCursorPos(&one);

	if (GetAsyncKeyState(VK_LBUTTON) < 0) {
		if (one.x > (x) && one.x < (x)+w && one.y >(y) && one.y < (y)+h || enabled[index][0]) {
			enabled[index][0] = true;

			if (!enabled[index][1]) {
				two.x = one.x - x;
				two.y = one.y - y;
				enabled[index][1] = true;
			}
		}
		else {
			enabled[index][0] = false;
			enabled[index][1] = false;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) == 0 && enabled[index][0]) { enabled[index][0] = false; enabled[index][1] = false; }
	if (enabled[index][0]) { x = one.x - two.x; y = one.y - two.y; }

	return true;
}