#pragma once
#include "../../source-sdk/math/vector3d.hpp"

class glow_object_definition_t {
public:
	void set(float r, float g, float b, float a) {
		color = vec3_t(r, g, b);
		alpha = a;
		render_when_occluded = true;
		render_when_unoccluded = false;
		bloom_amount = 1.0f;
	}
	bool unused() {
		return next_free_slot != -2;
	}

	void* entity;
	vec3_t color;
	float alpha;
	char unknown0[8];
	float bloom_amount;
	char unknown1[4];
	bool render_when_occluded;
	bool render_when_unoccluded;
	bool full_bloom_render;
	char unknown2[13];
	int next_free_slot;
};

class glow_manager_t {
public:
	glow_object_definition_t* objects;
	char pad[8];
	int size;
};