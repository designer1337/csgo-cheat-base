#pragma once

enum dlight_flags {
	dlight_no_world_illumination = 0x1,
	dlight_no_model_illumination = 0x2,
	dlight_add_displacement_alpha = 0x4,
	dlight_subtract_displacement_alpha = 0x8,
	dlight_displacement_mask = (dlight_add_displacement_alpha | dlight_subtract_displacement_alpha),
};

struct dlight_t {
	int flags;
	vec3_t origin;
	float radius;
	color color;
	float die_time;
	float decay;
	float min_light;
	int	key;
	int	style;
	vec3_t direction;
	float inner_angle;
	float outer_angle;
};