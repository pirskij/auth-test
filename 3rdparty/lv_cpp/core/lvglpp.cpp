/*
 * lvglpp.cpp
 *
 *  Created on: Jul 19, 2021
 *      Author: fstuffdev
 */

#include "lvglpp.h"
#include "LvDisplay.h"
#include "LvIndev.h"
#if USE_WIN32DRV
#include "lv_drivers/win32drv/win32drv.h"
#endif

namespace lvglpp {

LvPointerUnique<LvDisplay> Display;
LvPointerUnique<LvInput> Input;

/* Init lvgl */
void Init() {
	lv_init();
}

void DefaultPeripheral(int winIco) {

#if USE_WIN32DRV
	if (!lv_win32_init(
		GetModuleHandleW(NULL),
		SW_SHOW,
		800,
		480,
		LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(winIco))))
	{
		return;
	}

	lv_win32_add_all_input_devices_to_group(NULL);
#else
	/* Create Default Display */
	if (Display.get() == nullptr)
		Display = Make<LvDisplay>();

	/* Create Default Input */
	if (Input.get() == nullptr)
		Input = Make<LvInput>();
#endif
}

bool HasQuitSignal()
{
#if USE_WIN32DRV
	return lv_win32_quit_signal;
#else
	return false;
#endif
}

uint32_t TaskHandler(unsigned int ms) {
#if !LV_TICK_CUSTOM
	lv_tick_inc(ms);
#endif
	return lv_task_handler();
}

}

