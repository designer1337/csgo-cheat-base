enum analog_code_t {
	ANALOG_CODE_INVALID = -1,
	MOUSE_X = 0,
	MOUSE_Y,
	MOUSE_XY, // invoked when either x or y changes
	MOUSE_WHEEL,
	ANALOG_CODE_LAST = 10,
};


class i_inputsytem {
public:
	void enable_input(bool bEnable) {
		using original_fn = void(__thiscall*)(void*, bool);
		return (*(original_fn * *)this)[11](this, bEnable);
	}

	void reset_input_state() {
		using original_fn = void(__thiscall*)(void*);
		return (*(original_fn * *)this)[39](this);
	}

	bool is_button_down(int code) {
		using original_fn = bool(__thiscall*)(void*, int);
		return (*(original_fn * *)this)[15](this, code);
	}

	int get_analog_value(analog_code_t code) {
		using original_fn = int(__thiscall*)(void*, analog_code_t);
		return (*(original_fn * *)this)[18](this, code);

	}

	int get_analog_delta(analog_code_t code) {
		using original_fn = int(__thiscall*)(void*, analog_code_t);
		return (*(original_fn * *)this)[19](this, code);
	}

	const char* button_code_to_string(int code) {
		using original_fn = const char* (__thiscall*)(void*, int);
		return (*(original_fn * *)this)[40](this, code);
	}

};