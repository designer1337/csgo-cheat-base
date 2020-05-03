#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include <string>

namespace menu_framework {
	void group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label);
	void tab(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string, std::int32_t& tab, std::int32_t count, bool outline);
	void check_box(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, bool& var);
	void slider(std::int32_t x, std::int32_t y, std::int32_t position, float min, float max, unsigned long font, const std::string string, float& value);
	void menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h);

	inline bool should_drag = false;
	inline bool should_move = false; 
};