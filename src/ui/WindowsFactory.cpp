#include "WindowsFactory.h"
#include "ui/AuthWindow.h"

using namespace sol::ui;

void WindowsFactory::fillCreators()
{
	addCreator<AuthWindow>(AuthWindow::templateName());
}
