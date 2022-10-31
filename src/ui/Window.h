#pragma once

#include "ForwardDeclare.h"
#include <string_view>

namespace sol::ui
{
	class Window
	{
	public:
		virtual ~Window();

		virtual bool init();

		void setName(std::string_view wndName);
		std::string_view name() const noexcept { return m_name; }

		virtual void closeWindow();

	protected:
		std::string m_name;
	};
} // namespace sol::ui
