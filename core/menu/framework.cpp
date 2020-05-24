#include "framework.hpp"

//credits to harcuz for menu framework (https://www.unknowncheats.me/forum/members/2669363.html),
POINT cursor;
POINT cursor_corrected;

vec2_t GetMousePosition()
{
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	ScreenToClient(FindWindow(0, "Counter-Strike: Global Offensive"), &mousePosition);
	return { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };
}

bool MouseInRegion(int x, int y, int x2, int y2) {
	if (GetMousePosition().x > x&& GetMousePosition().y > y&& GetMousePosition().x < x2 + x && GetMousePosition().y < y2 + y)
		return true;
	return false;
}

void menu_framework::group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label) {
	//groupbox background
	render::draw_filled_rect(x, y, w, h, color(25, 25, 25, 255));

	//groupbox outline
	render::draw_rect(x, y, w, h, color(45, 45, 45, 255));

	//groupbox label
	if (show_label)
		render::draw_text_string(x + 2, y - 12, font, string, false, color::white());
}

void menu_framework::tab(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, std::int32_t& tab, std::int32_t count, bool show_outline) {
	GetCursorPos(&cursor);

	if ((cursor.x > x) && (cursor.x < x + w) && (cursor.y > y) && (cursor.y < y + h) && (GetAsyncKeyState(VK_LBUTTON) & 1))
		tab = count;
	
	//tab background
	if (show_outline)
		render::draw_rect(x, y, w, h, tab == count ? color(52, 134, 235, 255) : color(25, 25, 25, 255));

	//tab label
	render::draw_text_string(x - render::get_text_size(font, string).x / 2 + 50, y + h / 2 - 8, font, string, false, show_outline ? color::white() : tab == count ? color(52, 134, 235, 255) : color::white());
}

void menu_framework::check_box(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, bool& value) {
	GetCursorPos(&cursor);

	int w = 10, h = 10;

	if ((cursor.x > position) && (cursor.x < position + w) && (cursor.y > y) && (cursor.y < y + h) && GetAsyncKeyState(VK_LBUTTON) & 1)
		value = !value;

	//checkbox background
	render::draw_filled_rect(position, y, w, h, value ? color(52, 134, 235, 255) : color(36, 36, 36, 255));

	//checkbox label
	render::draw_text_string(x + 2, y - 1, font, string, false, color::white());
}

void menu_framework::slider(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, float& value, float min_value, float max_value) {
	GetCursorPos(&cursor);
	
	int ix = x + 140;
	int yi = y + 4;
	
	if ((cursor.x > ix) && (cursor.x < ix + position) && (cursor.y > yi) && (cursor.y < yi + 6) && (GetAsyncKeyState(VK_LBUTTON)))
		value = (cursor.x - ix) / (float(position) / float(max_value));

	//slider background
	render::draw_filled_rect(ix, yi, position, 6, color(36, 36, 36, 255));
	render::draw_filled_rect(ix, yi, value * (float(position) / float(max_value)), 6, color(52, 134, 235, 255));

	//slider label
	render::draw_text_string(x + 2, y - 1, font, (std::stringstream{ } << string << ": " <<  std::setprecision(3) << value).str(), false, color::white());
}

const char* KeyStringsStick[254] = {
	"INVLD", "M1", "M2", "BRK", "M3", "M4", "M5",
	"INVLD", "BSPC", "TAB", "INVLD", "INVLD", "INVLD", "ENTER", "INVLD", "INVLD", "SHIFT",
	"CTRL", "ALT", "PAU", "CAPS", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"ESC", "INVLD", "INVLD", "INVLD", "INVLD", "SPACE", "PGUP", "PGDOWN", "END", "HOME", "LEFT",
	"UP", "RIGHT", "DOWN", "INVLD", "PRNT", "INVLD", "PRTSCR", "INS", "DEL", "INVLD", "0", "1",
	"2", "3", "4", "5", "6", "7", "8", "9", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
	"V", "W", "X", "Y", "Z", "LFTWIN", "RGHTWIN", "INVLD", "INVLD", "INVLD", "NUM0", "NUM1",
	"NUM2", "NUM3", "NUM4", "NUM5", "NUM6", "NUM7", "NUM8", "NUM9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3",
	"F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20",
	"F21",
	"F22", "F23", "F24", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"NUM LOCK", "SCROLL LOCK", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "LSHFT", "RSHFT", "LCTRL",
	"RCTRL", "LMENU", "RMENU", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "NTRK", "PTRK", "STOP", "PLAY", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", ";", "+", ",", "-", ".", "/?", "~", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "{", "\\|", "}", "'\"", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD", "INVLD",
	"INVLD", "INVLD"
};

bool keys[256];
bool oldKeys[256];

bool GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;

	return false;
}

void menu_framework::keybind(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, std::string string, int* item) {

	int w = 20, h = 20;
	static bool gettingkey = false;
	static int key = 0;
	static bool goodname = false;

	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++) keys[x] = (GetAsyncKeyState(x));

	char buf[128];
	const char* lastname = _("[   ]");

	if (GetAsyncKeyState(VK_LBUTTON) && MouseInRegion(x - 20, y - 20, 50, 40))
		if (!gettingkey) gettingkey = true;

	if (gettingkey)
	{
		lastname = _("[ - ]");
		for (int i = 0; i < 255; ++i)
		{
			if (GetKeyPress(i))
			{
				if (i == VK_ESCAPE)
				{
					key = -1;
					*item = key;
					gettingkey = false;
					return;
				}

				else
				{
					key = i;
					*item = key;
					gettingkey = false;
					return;
				}
			}
		}
	}
	else
	{
		if (*item >= 0)
		{
			lastname = KeyStringsStick[*item];
			if (lastname) goodname = true;
			
			else
			{
				if (GetKeyNameText(*item << 16, buf, 127))
				{
					lastname = buf;
					goodname = true;
				}
			}
		}

		if (!goodname)
			lastname = _("[   ]");
	}

	render::draw_text_string(x, y, font, lastname, false, color(233, 233, 233, 255) );
}

void menu_framework::menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h) {
	GetCursorPos(&cursor);
	
	if (GetAsyncKeyState(VK_LBUTTON) < 0 && (cursor.x > x && cursor.x < x + w && cursor.y > y && cursor.y < y + h)) {
		should_drag = true;

		if (!should_move) {
			cursor_corrected.x = cursor.x - x;
			cursor_corrected.y = cursor.y - y;
			should_move = true;
		}
	}
	
	if (should_drag) {
		x = cursor.x - cursor_corrected.x;
		y = cursor.y - cursor_corrected.y;
	}
	
	if (GetAsyncKeyState(VK_LBUTTON) == 0) {
		should_drag = false;
		should_move = false;
	}
}

