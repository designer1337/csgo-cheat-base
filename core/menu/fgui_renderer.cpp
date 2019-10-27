#include "fgui_renderer.hpp"

void fgui_renderer::initialize() {
	fgui::render.create_font = fgui_renderer::create_font;
	fgui::render.get_screen_size = fgui_renderer::get_screen_size;
	fgui::render.get_text_size = fgui_renderer::get_text_size;
	fgui::render.clip_rect = fgui_renderer::clip_rect;
	fgui::render.rect = fgui_renderer::rect;
	fgui::render.gradient = fgui_renderer::gradient;
	fgui::render.colored_gradient = fgui_renderer::colored_gradient;
	fgui::render.outline = fgui_renderer::outline;
	fgui::render.line = fgui_renderer::line;
	fgui::render.polygon = fgui_renderer::polygon;
	fgui::render.circle = fgui_renderer::circle;
	fgui::render.rounded_rect = fgui_renderer::rounded_rect;
	fgui::render.text = fgui_renderer::text;
	fgui::render.alpha = fgui_renderer::alpha;

	fonts.emplace_back(FONT_VERDANA);
	fonts.emplace_back(FONT_ARIAL);
	fonts.emplace_back(FONT_TAHOMA);

	fgui::render.create_font(fonts[FONT_VERDANA], "Verdana", 11,
		fgui::external::font_flags::SHADOW, false);
	fgui::render.create_font(fonts[FONT_ARIAL], "Arial", 11,
		fgui::external::font_flags::SHADOW, false);
	fgui::render.create_font(fonts[FONT_TAHOMA], "Tahoma", 11,
		fgui::external::font_flags::SHADOW, false);
}

void fgui_renderer::create_font(fgui::font& font, const std::string_view family,
	int size, int flags, bool bold) {

	font = interfaces::surface->font_create();
	interfaces::surface->set_font_glyph(font, family.data(), size,
		bold ? 800 : 0, 0, 0, flags);
}

fgui::dimension fgui_renderer::get_text_size(const fgui::font& font,
	const std::string_view text) {

	fgui::dimension temp = { 0, 0 };

	interfaces::surface->get_text_size(
		font, std::wstring(text.begin(), text.end()).data(), temp.width,
		temp.height);

	return temp;
}

void fgui_renderer::clip_rect(int x, int y, int width, int height) {

	fgui::rect viewport = { x, y, (x + width), (y + height) };

	interfaces::surface->set_clip_rect(viewport.left, viewport.top, viewport.right,
		viewport.bottom);
}

bool fgui_renderer::world_to_screen(vec3_t& origin, vec3_t& screen) {
	return (interfaces::debug_overlay->screen_position(origin, screen) != 1);
}


void fgui_renderer::rect(int x, int y, int w, int h, fgui::color color) {

	interfaces::surface->set_drawing_color(color.m_red, color.m_green, color.m_blue,
		color.m_alpha);
	interfaces::surface->draw_filled_rectangle(x, y, w, h);
	//	interfaces::surface->draw_filled_rectangle(x, y, x + w, y + h);
}

void fgui_renderer::gradient(int x, int y, int w, int h, int alpha1, int alpha2,
	fgui::color color, bool horizontal) {

	interfaces::surface->set_drawing_color(color.m_red, color.m_green, color.m_blue,
		color.m_alpha);
	interfaces::surface->draw_filled_rect_fade(x, y, x + w, y + h, alpha1, alpha2,
		horizontal);
}

void fgui_renderer::colored_gradient(int x, int y, int w, int h, fgui::color color1,
	fgui::color color2, bool is_horizontal) {

	if (is_horizontal) { // horizontal

		fgui_renderer::rect(x, y, w, h, color1);

		unsigned char first = color2.m_red;
		unsigned char second = color2.m_green;
		unsigned char third = color2.m_blue;

		for (int i = 0; i < w; i++) {
			float fi = i, fw = w;
			float a = fi / fw;
			unsigned int ia = a * 255;
			fgui_renderer::rect(x + i, y, 1, h, fgui::color(first, second, third, ia));
		}
	}

	else { // vertical

		fgui_renderer::rect(x, y, w, h, color1);

		unsigned char first = color2.m_red;
		unsigned char second = color2.m_green;
		unsigned char third = color2.m_blue;

		for (int i = 0; i < h; i++) {

			float fi = i, fh = h;
			float a = fi / fh;
			unsigned int ia = a * 255;
			fgui_renderer::rect(x, y + i, w, 1, fgui::color(first, second, third, ia));
		}
	}
}

void fgui_renderer::outline(int x, int y, int w, int h, fgui::color color) {

	interfaces::surface->set_drawing_color(color.m_red, color.m_green, color.m_blue,
		color.m_alpha);
	interfaces::surface->draw_outlined_rect(x, y, w, h);
	//	interfaces::surface->draw_outlined_rect(x, y, x + w, y + h);
}

void fgui_renderer::line(int x, int y, int x2, int y2, fgui::color color) {

	interfaces::surface->set_drawing_color(color.m_red, color.m_green, color.m_blue,
		color.m_alpha);
	interfaces::surface->draw_line(x, y, x2, y2);
}

void fgui_renderer::text(int x, int y, fgui::color color, unsigned long font, std::string_view text) { //works
	const auto converted_text = std::wstring(text.begin(), text.end());

	interfaces::surface->set_text_color(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->draw_text_font(font);
	interfaces::surface->draw_text_pos(x, y);
	interfaces::surface->draw_render_text(converted_text.c_str(), wcslen(converted_text.c_str()));
}

void fgui_renderer::get_screen_size(int& width, int& height) { //works

	interfaces::surface->get_screen_size(width, height);
}

void fgui_renderer::polygon(int count, fgui::vertex* vertex, fgui::color color) {

	static int texture = interfaces::surface->create_new_texture_id(true);
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	interfaces::surface->set_texture_rgba(texture, buffer, 1, 1);
	interfaces::surface->set_drawing_color(color.m_red, color.m_green, color.m_blue,
		color.m_alpha);
	interfaces::surface->set_texture(texture);

	interfaces::surface->draw_textured_polygon(count, vertex);
}

void fgui_renderer::circle(int x, int y, int radius, int segments, fgui::color color) {

	interfaces::surface->set_drawing_color(color.m_red, color.m_green, color.m_blue,
		color.m_alpha);
	interfaces::surface->draw_outlined_circle(x, y, radius, segments);
}

void fgui_renderer::rounded_rect(int x, int y, int w, int h, int radius,
	fgui::color color) {

	fgui::vertex round[64];

	for (std::size_t i = 0; i < 4; i++) {

		int new_x = x + ((i < 2) ? (w - radius) : radius);
		int new_y = y + ((i % 3) ? (h - radius) : radius);

		float a = 90.f * i;

		for (std::size_t j = 0; j < 16; j++) {

			float alpha = DEG2RAD(a + j * 6.f);

			round[(i * 16) + j] = fgui::vertex(fgui::precision_point(
				new_x + radius * sin(alpha), new_y - radius * cos(alpha)));
		}
	}

	fgui_renderer::polygon(64, round, color);
}

void fgui_renderer::texture(const std::string_view texture_name, int x, int y, int w,
	int h) {

	static unsigned int texture_id = 0;

	bool initialized = [&]() {
		texture_id = interfaces::surface->create_new_texture_id(true);

		// if somehow the texture id is invalid
		if (!texture_id)
			return false;

		interfaces::surface->draw_set_texture_file(texture_id, texture_name.data(),
			1, false);

		return true;
	}();

	if (initialized) {

		static bool draw_once = [&]() {
			if (!interfaces::surface->is_texture_id_valid(texture_id))
				return false;

			interfaces::surface->set_drawing_color(255, 255, 255, 255);
			interfaces::surface->set_texture(texture_id);

			return true;
		}();

		interfaces::surface->draw_textured_rect(x, y, x + w, y + h);
	};
}

void fgui_renderer::alpha(int x, int y, int w, int h) {

	for (std::size_t i = 0; i < h / 5; i++) {

		for (std::size_t t = 0; t < w / 5; t++) {

			int pixel_nr = roundf(t);
			int line_nr = roundf(i);
			bool start_with_light = line_nr % 2;
			bool is_brick_light = start_with_light ? pixel_nr % 2 : pixel_nr % 2 == 0;

			fgui::color new_color =
				is_brick_light ? fgui::color(60, 60, 60) : fgui::color(40, 40, 40);

			fgui_renderer::rect(x + t * 5, y + i * 5, 5, 5, new_color);
		}
	}
};

void fgui_renderer::outlets(int x, int y, int w, int h) { // laggy as fuck

	for (std::size_t i = 1; i < w; i++) {

		if (i % 4 == 0) {

			for (std::size_t t = 1; t < h; t++) {

				if (t % 4 == 0)
					fgui_renderer::rect(x + i - 2, y + t - 5, 1, 3, fgui::color(15, 15, 15));
			}
		}

		if (i % 4 == 2) {

			for (std::size_t t = 1; t < h; t++) {

				if (t % 4 == 0)
					fgui_renderer::rect(x + i - 2, y + t - 3, 1, 3, fgui::color(15, 15, 15));
			}
		}
	}
}