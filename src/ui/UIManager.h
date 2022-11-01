#pragma once

#include "ui/ForwardDeclare.h"
#include "ui/WindowsFactory.h"
#include <string_view>
#include <vector>

namespace sol::ui
{
	class UIManager
	{
	public:
		UIManager();
		~UIManager();

		bool init();

		void registerWindow(WindowSPtr const& wnd);
		void unregisterWindow(WindowSPtr const& wnd);

		WindowSPtr openWindow(std::string_view id);

		void closeWindow(WindowSPtr const& wnd);
		void closeAllWindows();

		bool hasOpenedWindows() const noexcept;
		bool hasOpenedWindow(std::string_view id) const noexcept;

		WindowSPtr getTopWindow() const noexcept;
		WindowSPtr getOpenedWindow(std::string_view id) const noexcept;

	private:
		WindowsFactorySPtr m_windowsFactory;
		std::vector<WindowSPtr> m_vecWindows;
	};
} // namespace sol::ui
