#pragma once
#include "../../dependencies/common_includes.hpp"
#include "framework.hpp"
#include "variables.hpp"

namespace menu {
	inline static int current_tab = 0;

	void render();
	void toggle();
};
