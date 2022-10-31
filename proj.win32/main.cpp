/*
 * PROJECT:   LVGL PC Simulator using Visual Studio
 * FILE:      LVGL.Simulator.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include "resource.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl/lvgl.h"

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#include <stdio.h>

#include "lv_cpp/core/lvglpp.h"

int main()
{
    lv_init();

    auto ms = 1u;

    lvglpp::Init();
    lvglpp::DefaultPeripheral(IDI_LVGL);

#if defined(CONFIG_EXAMPLE_HELLO)
    HelloEx::Create();
    ms = HelloEx::ms;
#endif

#if defined(CONFIG_EXAMPLE_FLEX)
    FlexEx::Create();
    ms = FlexEx::ms;
#endif

    // ----------------------------------
    // Task handler loop
    // ----------------------------------
    while (!lvglpp::HasQuitSignal()) {
        lvglpp::TaskHandler(ms);
        Sleep(1);
    }

    return 0;
}
