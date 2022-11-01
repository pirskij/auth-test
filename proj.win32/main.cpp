#include "resource.h"
#include "Application.h"

int main()
{
    auto app = sol::Application::createUnique();

    if (!app || !app->init(IDI_LVGL))
        return -1;

    return app->exec();
}
