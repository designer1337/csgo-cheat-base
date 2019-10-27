#pragma once
#include "../../common_includes.hpp"

namespace console {
	void attach(const char* title);
	void release();
	void log_angles(vec3_t angles);
	void log(const char* format, ...);
}