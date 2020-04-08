#include "console.hpp"

void console::initialize(const char* title) {
	AllocConsole();

	freopen_s((_iobuf * *)__acrt_iob_func(0), "conin$", "r", (_iobuf*)__acrt_iob_func(0));
	freopen_s((_iobuf * *)__acrt_iob_func(1), "conout$", "w", (_iobuf*)__acrt_iob_func(1));
	freopen_s((_iobuf * *)__acrt_iob_func(2), "conout$", "w", (_iobuf*)__acrt_iob_func(2));

	SetConsoleTitleA(title);
}

void console::release() {
	fclose((_iobuf*)__acrt_iob_func(0));
	fclose((_iobuf*)__acrt_iob_func(1));
	fclose((_iobuf*)__acrt_iob_func(2));

	FreeConsole();
}