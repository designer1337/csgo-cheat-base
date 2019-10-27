#include "console.hpp"

void console::attach(const char* title) {
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

void console::log_angles(vec3_t angles) {
	console::log("x: %.2f; y: %.2f; z: %.2f", angles.x, angles.y, angles.z);
}

void console::log(const char* format, ...) {
	char buf[1024];
	va_list arguments;

	va_start(arguments, format);
	_vsnprintf_s(buf, sizeof buf, format, arguments);
	va_end(arguments);

	std::cout << buf << std::endl;
}