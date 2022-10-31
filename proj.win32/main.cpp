/*
 * PROJECT:   LVGL PC Simulator using Visual Studio
 * FILE:      LVGL.Simulator.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */
#include "resource.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#include "Application.h"

int main()
{
    auto app = sol::Application::createUnique();

    if (!app || !app->init(IDI_LVGL))
        return -1;

    return app->exec();
}
