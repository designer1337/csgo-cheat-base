#pragma once
#include "../../common_includes.hpp"

namespace console {
	void initialize(const char* title);
	void release();

	template <typename ... Args>
	void log(char const* const format, Args const& ... args) {
#ifdef debug_build
		printf(format, args ...);
#endif
	}

}