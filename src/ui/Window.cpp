#include "Window.h"

using namespace sol::ui;

Window::~Window() = default;

bool Window::init()
{
	return true;
}

void Window::setName(std::string_view wndName)
{
	m_name = wndName;
}

void Window::closeWindow()
{
}
