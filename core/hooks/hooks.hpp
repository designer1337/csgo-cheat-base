#pragma once

namespace hooks {
	bool initialize();
	void release();

	namespace create_move {
		static const int index = 24;
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __fastcall hook(void* ecx, void* edx, int input_sample_frametime, c_usercmd* cmd);
	};

	namespace paint_traverse {
		static const int index = 41;
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace lock_cursor {
		static const int index = 67;
		using fn = void(__thiscall*)(void*);
		void __stdcall hook();
	}

	namespace in_key_event {
		static const int index = 21;
		using fn = int(__stdcall*)(int, int, const char*);
		int __fastcall hook(void* ecx, int edx, int event_code, int key_num, const char* current_binding);
	}

}