#pragma once

namespace hooks {
	bool initialize();
	void release();

	inline unsigned int get_virtual(void* _class, unsigned int index) { 
		return static_cast<unsigned int>((*static_cast<int**>(_class))[index]);
	}

	namespace create_move {
		using fn = bool(__thiscall*)(i_client_mode* ,float, c_usercmd*);
		inline fn original = nullptr;
		bool __stdcall hook(float input_sample_frametime, c_usercmd* cmd) noexcept;
	};

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		inline fn original = nullptr;
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force) noexcept;
	}

	namespace alloc_key_value_memory {
		using fn = void*(__thiscall*)(void*, const std::int32_t);
		inline fn original;
		void* __stdcall hook(const std::int32_t size) noexcept;
	}
	//sv_pure bypass hook
	namespace sv_pure_loose_files {
		bool __fastcall hook(void* ecx, void* edx);
	}

	namespace check_file_CRCs_with_server {
		void __fastcall hook(void*, void*);
	}

	namespace on_screen_size_changed {
		using fn = void(__thiscall*)(int, int);
		inline fn original;
		void __stdcall hook(int oldWidth, int oldHeight);
	}
}
