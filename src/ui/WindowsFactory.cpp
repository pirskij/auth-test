#include "WindowsFactory.h"
#include "ui/AuthWindow.h"

using namespace sol::ui;

void WindowsFactory::fillCreators()
{
	lazyAddCreator<AuthWindow>(AuthWindow::templateName());
}
