#include "renderer.hpp"
#pragma once

unsigned long render::fonts::watermark_font;

void render::setup() {
	render::fonts::watermark_font = interfaces::surface->font_create();

	interfaces::surface->set_font_glyph(render::fonts::watermark_font, "Tahoma", 12, 500, 0, 0, font_flags::fontflag_dropshadow);

#ifdef debug_build
	console::log("[setup] render initialized!\n");
#endif
}

/*gladiator cheatz*/
void render::draw_3d_cube(float scalar, vec3_t angles, vec3_t middle_origin, color outline) {
	vec3_t forward, right, up;
	math::angle_vectors(angles, &forward, &right, &up);

	vec3_t points[8];
	points[0] = middle_origin - (right * scalar) + (up * scalar) - (forward * scalar);
	points[1] = middle_origin + (right * scalar) + (up * scalar) - (forward * scalar); 
	points[2] = middle_origin - (right * scalar) - (up * scalar) - (forward * scalar); 
	points[3] = middle_origin + (right * scalar) - (up * scalar) - (forward * scalar); 

	points[4] = middle_origin - (right * scalar) + (up * scalar) + (forward * scalar);
	points[5] = middle_origin + (right * scalar) + (up * scalar) + (forward * scalar);
	points[6] = middle_origin - (right * scalar) - (up * scalar) + (forward * scalar); 
	points[7] = middle_origin + (right * scalar) - (up * scalar) + (forward * scalar); 

	vec3_t points_screen[8];
	for (int i = 0; i < 8; i++)
		if (!math::world_to_screen(points[i], points_screen[i]))
			return;

	interfaces::surface->set_drawing_color(outline.r, outline.g, outline.b, outline.a);

	interfaces::surface->draw_line(points_screen[0].x, points_screen[0].y, points_screen[1].x, points_screen[1].y);
	interfaces::surface->draw_line(points_screen[0].x, points_screen[0].y, points_screen[2].x, points_screen[2].y);
	interfaces::surface->draw_line(points_screen[3].x, points_screen[3].y, points_screen[1].x, points_screen[1].y);
	interfaces::surface->draw_line(points_screen[3].x, points_screen[3].y, points_screen[2].x, points_screen[2].y);

	interfaces::surface->draw_line(points_screen[0].x, points_screen[0].y, points_screen[4].x, points_screen[4].y);
	interfaces::surface->draw_line(points_screen[1].x, points_screen[1].y, points_screen[5].x, points_screen[5].y);
	interfaces::surface->draw_line(points_screen[2].x, points_screen[2].y, points_screen[6].x, points_screen[6].y);
	interfaces::surface->draw_line(points_screen[3].x, points_screen[3].y, points_screen[7].x, points_screen[7].y);

	interfaces::surface->draw_line(points_screen[4].x, points_screen[4].y, points_screen[5].x, points_screen[5].y);
	interfaces::surface->draw_line(points_screen[4].x, points_screen[4].y, points_screen[6].x, points_screen[6].y);
	interfaces::surface->draw_line(points_screen[7].x, points_screen[7].y, points_screen[5].x, points_screen[5].y);
	interfaces::surface->draw_line(points_screen[7].x, points_screen[7].y, points_screen[6].x, points_screen[6].y);
}

void render::draw_line(int x1, int y1, int x2, int y2, color colour) {
	interfaces::surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
	interfaces::surface->draw_line(x1, y1, x2, y2);
}

void render::draw_text_wchar(int x, int y, unsigned long font, const wchar_t* string, color colour) {
	interfaces::surface->set_text_color(colour.r, colour.g, colour.b, colour.a);
	interfaces::surface->draw_text_font(font);
	interfaces::surface->draw_text_pos(x, y);
	interfaces::surface->draw_render_text(string, wcslen(string));
}

void render::draw_text_string(int x, int y, unsigned long font, std::string string, bool text_centered, color colour) {
	const auto converted_text = std::wstring(string.begin(), string.end());

	int width, height;
	interfaces::surface->get_text_size(font, converted_text.c_str(), width, height);

	interfaces::surface->set_text_color(colour.r, colour.g, colour.b, colour.a);
	interfaces::surface->draw_text_font(font);
	if (text_centered)
		interfaces::surface->draw_text_pos(x - (width / 2), y);
	else
		interfaces::surface->draw_text_pos(x, y);
	interfaces::surface->draw_render_text(converted_text.c_str(), wcslen(converted_text.c_str()));
}

void render::draw_rect(int x, int y, int w, int h, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outlined_rect(x, y, w, h);
}

void render::draw_filled_rect(int x, int y, int w, int h, color colour) {
	interfaces::surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
	interfaces::surface->draw_filled_rectangle(x, y, w, h);
}

void render::draw_outline(int x, int y, int w, int h, color colour) {
	interfaces::surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
	interfaces::surface->draw_outlined_rect(x, y, w, h);
}

void render::draw_textured_polygon(int n, fgui::vertex* vertice, color col) {
	static int texture_id = interfaces::surface->create_new_texture_id(true);
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	interfaces::surface->set_texture_rgba(texture_id, buf, 1, 1);
	interfaces::surface->set_drawing_color(col.r, col.g, col.b, col.a);
	interfaces::surface->set_texture(texture_id);
	interfaces::surface->draw_polygon(n, vertice);
}

void render::draw_circle(int x, int y, int r, int s, color col) {
	float Step = M_PI * 2.0 / s;
	for (float a = 0; a < (M_PI * 2.0); a += Step) {
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;
		interfaces::surface->set_drawing_color(col.r, col.g, col.b, col.a);
		interfaces::surface->draw_line(x1, y1, x2, y2);
	}
}

void render::get_text_size(unsigned long font, std::string string, int w, int h) {
	std::wstring text = std::wstring(string.begin(), string.end());
	const wchar_t* out = text.c_str();

	interfaces::surface->get_text_size(font, out, w, h);
}