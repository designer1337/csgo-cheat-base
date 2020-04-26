#pragma once
#include "../../dependencies/common_includes.hpp"

namespace menu_framework {
	void group_box(int x, int y, int w, int h, unsigned long font, const char* string, bool show_label);
	void tab(int x, int y, int w, int h, unsigned long font, const char* string, int& tab, int count);
	void check_box(int x, int y, int position, unsigned long font, const char* string, int count, bool& var);
	void slider(int x, int y, int w, float min, float max, unsigned long font, const char* string, int count, float& value);
	bool menu_movement(int& x, int& y, int w, int h, int index);
};
