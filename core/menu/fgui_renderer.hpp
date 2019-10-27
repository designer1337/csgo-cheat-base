#pragma once
#include "..//..//dependencies/common_includes.hpp"
#include "FGUI/dependencies/aliases.hh"
#include "FGUI/dependencies/definitions.hh"

enum : fgui::font { FONT_TAHOMA, FONT_VERDANA, FONT_ARIAL, FONT_MAX };
inline std::vector<fgui::font> fonts;

namespace fgui_renderer {

	void initialize();

	void create_font(fgui::font& font, const std::string_view family, int size,
		int flags, bool bold);
	fgui::dimension get_text_size(const fgui::font& font,
		const std::string_view text);
	void get_screen_size(int& width, int& height);
	void clip_rect(int x, int y, int width, int height);
	bool world_to_screen(vec3_t& origin, vec3_t& screen);

	void rect(int x, int y, int w, int h, fgui::color color);
	void gradient(int x, int y, int w, int h, int alpha1, int alpha2,
		fgui::color color, bool is_horizontal);
	void colored_gradient(int x, int y, int w, int h, fgui::color color1,
		fgui::color color2, bool is_horizontal);
	void outline(int x, int y, int w, int h, fgui::color color);
	void line(int x, int y, int x2, int y2, fgui::color color);
	void text(int x, int y, fgui::color color, unsigned long font,
		std::string_view text);
	void polygon(int count, fgui::vertex* vertex, fgui::color color);
	void circle(int x, int y, int radius, int segments, fgui::color color);
	void rounded_rect(int x, int y, int w, int h, int radius, fgui::color color);
	void texture(const std::string_view texture_name, int x, int y, int w, int h);
	void alpha(int x, int y, int w, int h);
	void outlets(int x, int y, int w, int h);
} // namespace draw