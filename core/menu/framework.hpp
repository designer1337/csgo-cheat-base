#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "variables.hpp"
namespace menu_framework {
	void group_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string string, bool show_label);
	void tab(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, unsigned long font, const std::string, std::int32_t& tab, std::int32_t count, bool show_outline);
	void check_box(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, bool& value);
	void slider(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, float& value, float min_value, float max_value);
	void menu_movement(std::int32_t& x, std::int32_t& y, std::int32_t w, std::int32_t h);
	void combo_box(std::int32_t x, std::int32_t y, std::int32_t position, unsigned long font, const std::string string, std::vector<std::string> elements, int* values);
	void color_picker(std::int32_t x, std::int32_t y, std::int32_t position, std::string name, color& output_value, bool& is_opened);
	inline bool should_drag = false;
	inline bool should_move = false;
};