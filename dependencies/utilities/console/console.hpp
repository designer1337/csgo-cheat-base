#pragma once
#include "../../utilities/csgo.hpp"

namespace console {
	void initialize(const char* title);
	void release();

	template <typename ... Args>
	void log(char const* const format, Args const& ... args) {
#ifdef _DEBUG
		time_t t;
		t = time(NULL);
		struct tm tm = *localtime(&t);
		printf("[%d:%d:%d] [debug] --> ", tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf(format, args ...);
		printf("\n");
#endif
	}

}