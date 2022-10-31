#include "ui/UIManager.h"
#include "ui/Window.h"

using namespace sol::ui;
using namespace sol::utils;

UIManager::UIManager()
{
	m_windowsFactory = std::make_unique<WindowsFactory>();
	m_windowsFactory->fillCreators();
}

bool UIManager::init()
{
	return true;
}

void UIManager::registerWindow(WindowSPtr const& wnd)
{
	if (!wnd)
		return;

	auto bHas = false;
	for (auto _wnd : m_vecWindows)
	{
		if (_wnd.get() == wnd.get())
		{
			bHas = true;
			break;
		}
	}

	if (!bHas)
		m_vecWindows.push_back(wnd);
}

void UIManager::unregisterWindow(WindowSPtr const& wnd)
{
	if (!wnd)
		return;

	for (auto itr = std::begin(m_vecWindows); itr != std::end(m_vecWindows); ++itr)
	{
		if ((*itr).get() == wnd.get())
		{
			m_vecWindows.erase(itr);
			break;
		}
	}
}

WindowSPtr UIManager::openWindow(std::string_view id)
{
	if (m_windowsFactory)
	{
		auto wnd = m_windowsFactory->createObjectPtr(id.data());
		if (wnd && wnd->init())
		{
			wnd->setName(id);
			registerWindow(wnd);
			return wnd;
		}
	}

	return nullptr;
}

void UIManager::closeWindow(WindowSPtr const& wnd)
{
	if (!wnd)
		return;

	unregisterWindow(wnd);

	wnd->closeWindow();
}

void UIManager::closeAllWindows()
{
	for (auto itr = std::begin(m_vecWindows); itr != std::end(m_vecWindows);)
	{
		(*itr)->closeWindow();
		itr = m_vecWindows.erase(itr);
	}
}

bool UIManager::hasOpenedWindows() const noexcept
{
	return !m_vecWindows.empty();
}

bool UIManager::hasOpenedWindow(std::string_view id) const noexcept
{
	for (auto ndx = m_vecWindows.size(); ndx > 0u; --ndx)
	{
		auto wnd = m_vecWindows[ndx - 1];
		if (wnd->name() == id)
			return true;
	}

	return false;
}

WindowSPtr UIManager::getTopWindow() const noexcept
{
	if (m_vecWindows.empty())
		return nullptr;

	return m_vecWindows.back();
}

WindowSPtr UIManager::getOpenedWindow(std::string_view id) const noexcept
{
	for (auto ndx = m_vecWindows.size(); ndx > 0u; --ndx)
	{
		auto wnd = m_vecWindows[ndx - 1];
		if (wnd->name() == id)
			return wnd;
	}

	return nullptr;
}
