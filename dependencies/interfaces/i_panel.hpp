#pragma once

class i_panel {
public:
	const char* get_panel_name(unsigned int panel_id) {
		using original_fn = const char* (__thiscall*)(i_panel*, unsigned int);
		return (*(original_fn * *)this)[36](this, panel_id);
	}
};