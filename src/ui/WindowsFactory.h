#pragma once

#include "ForwardDeclare.h"
#include "utils/AbstractFactory.h"

namespace sol::ui
{
	class WindowsFactory : public sol::utils::AbstractFactory<Window, WindowSPtr>
	{
	public:
		virtual void fillCreators() override;
	};
} // namespace sol::ui
