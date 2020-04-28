#pragma once
#include "../../dependencies/common_includes.hpp"
#include <string>

namespace menu_framework {
	void group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label);
	void tab(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string, std::int32_t& tab, std::int32_t count, bool outline);
	void check_box(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, bool& var);
	void slider(std::int32_t x, std::int32_t y, std::int32_t position, float min, float max, unsigned long font, const std::string string, float& value);
	bool menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h, std::int32_t index);
};