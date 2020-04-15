#pragma once

namespace hooks {
	bool initialize();
	void release();

	namespace create_move {
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __fastcall hook(void* ecx, void* edx, int input_sample_frametime, c_usercmd* cmd);
	};

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

}