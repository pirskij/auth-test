#pragma once

#include "ui/ForwardDeclare.h"
#include "ForwardDeclare.h"
#include "utils/Singleton.h"

namespace sol
{
	class Application : public sol::utils::Singleton<Application>
	{
	public:
		static ApplicationSPtr createUnique();

		bool init(int arg);

		int exec();

		ui::UIManagerUPtr const& getUIManager() const noexcept { return m_uiManager; }

	protected:
		ui::UIManagerUPtr m_uiManager;
	};
}
