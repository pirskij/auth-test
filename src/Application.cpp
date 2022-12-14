#include "Application.h"
#include "ui/AuthWindow.h"
#include "ui/UIManager.h"
#include "utils/Memory.h"
#include "lv_cpp/core/lvglpp.h"
#if _WIN32
#include <Windows.h>
#endif

#include <assert.h> 

using namespace sol;
using namespace sol::utils;

ApplicationSPtr Application::createUnique()
{
    return std::shared_ptr<Application>(Application::getInstance(), [](Application* app)
        {
           Application::purgeInstance();
        });
}

bool Application::init(int arg)
{
    auto ms = 5u;

    lvglpp::Init();
    lvglpp::DefaultPeripheral(arg);

    m_uiManager = sol_make_shared<ui::UIManager>();

    if (!m_uiManager || !m_uiManager->init())
    {
        assert(false);
        return false;
    }

    auto wnd = m_uiManager->openWindow(sol::ui::AuthWindow::templateName());
    if (!wnd)
        return false;

    std::cout << "Application created !!!\n";

    return true;
}

int Application::exec()
{
    auto ms = 5u;
    // ----------------------------------
    // Task handler loop
    // ----------------------------------
    while (!lvglpp::HasQuitSignal()) {
        lvglpp::TaskHandler(ms);
#if _WIN32
        Sleep(1);
#endif
    }

    return 1;
}
