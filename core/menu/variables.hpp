#pragma once

namespace variables {
	inline bool test_bool = false;
	inline float test_float = 0.f;
	inline float test_float_2 = 0.f;

	namespace color_picker_1 {
		inline color clr = color(255, 255, 255);
		inline bool opened;
	}

	namespace color_picker_2 {
		inline color clr = color(255, 255, 255);
		inline bool opened;
	}


	namespace menu {
		inline bool opened = true;
		inline int x = 140, y = 140;
		inline int w = 400, h = 300;
	}
}
