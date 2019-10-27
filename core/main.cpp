#include "../dependencies/common_includes.hpp"
#include "features/features.hpp"
#include "menu/fgui_renderer.hpp"
#include "menu/fgui_input.hpp"
#include "menu/fgui_menu.hpp"

DWORD WINAPI initialize(void* instance) {
	while (!GetModuleHandleA("serverbrowser.dll"))
		Sleep(200);

#ifdef debug_build
	console::attach("csgo-cheat console");
#endif

	try {
		interfaces::initialize();
		hooks::initialize();
		fgui_input::initialize();
		fgui_renderer::initialize();
		gui::initialize();
		render::setup();
	}

	catch (const std::runtime_error & error) {
		MessageBoxA(NULL, error.what(), "csgo-cheat error!", MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	}

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

BOOL WINAPI release() {
	hooks::release();

#ifdef debug_build
	console::release();
#endif

	return TRUE;
}

BOOL APIENTRY DllMain(void* instance, uintptr_t reason, void* reserved) {
	DisableThreadLibraryCalls(static_cast<HMODULE>(instance));

	switch (reason) {
	case DLL_PROCESS_ATTACH:
		if (auto handle = CreateThread(NULL, NULL, initialize, instance, NULL, NULL))
			CloseHandle(handle);
		break;

	case DLL_PROCESS_DETACH:
		release();
		break;
	}

	return true;
}