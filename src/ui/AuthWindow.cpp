#include "AuthWindow.h"
#include "auth/Authorizer.h"
#include "lv_cpp/core/lvglpp.h"
#include "lv_cpp/core/LvDisplay.h"
#include "lv_cpp/core/LvIndev.h"
#include "lv_cpp/core/LvObj.h"
#include "lv_cpp/core/LvScr.h"
#include "lv_cpp/misc/LvStyle.h"
#include "lv_cpp/misc/LvTimer.h"
#include "lv_cpp/misc/LvAnim.h"
#include "lv_cpp/misc/LvAnimTimeline.h"
#include "lv_cpp/widgets/LvWidgets.h"
#include "utils/Memory.h"

using namespace lvglpp;
using namespace sol::utils;

namespace sol::ui
{
	void internal_onAuthClicked(lv_event_t* e)
	{
		if (!e || !e->user_data)
			return;

		auto wnd = reinterpret_cast<AuthWindow*>(e->user_data);
		if (!wnd)
			return;

		wnd->_onAuthClicked();
	}
};

using namespace sol::ui;

std::string AuthWindow::templateName()
{
	return "AuthWindow";
}

bool AuthWindow::init()
{
	/* Main container */
	m_mainLayout = sol_make_shared<LvObj>();
	m_mainLayout->setSize(470, 330).
		align(LV_ALIGN_CENTER, 0, 0).
		setFlexFlow(LV_FLEX_FLOW_COLUMN).
		setFlexAlign(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	m_labelsStyle = sol_make_shared<LvStyle>();
	m_labelsStyle->init().setTextOpa(LV_OPA_50);

	m_nameLabel = sol_make_shared<LvLabel>(m_mainLayout.get());
	m_nameLabel->setText("User name").addStyle(m_labelsStyle.get(), 0);

	m_nameTextArea = sol_make_shared<LvTextarea>(m_mainLayout.get());
	m_nameTextArea->
		setOneLine(true).
		setPlaceholderText("Your name");
		//addEventCb(ta_event_cb, LV_EVENT_ALL, kb);

	m_passLabel = sol_make_shared<LvLabel>(m_mainLayout.get());
	m_passLabel->setText("Password").addStyle(m_labelsStyle.get(), 0);

	m_passTextArea = sol_make_shared<LvTextarea>(m_mainLayout.get());
	m_passTextArea->
		setOneLine(true).
		setPasswordMode(true).
		setPlaceholderText("Min. 8 chars.");
	//addEventCb(ta_event_cb, LV_EVENT_ALL, kb);

	m_authBtn = sol_make_shared<LvBtn>(m_mainLayout.get());
	m_authBtn->setHeight(LV_SIZE_CONTENT);
	m_authBtn->setWidth(150);

	m_authBtn->addEventCb(internal_onAuthClicked, LV_EVENT_PRESSED, this);

	m_authBtnLabel = sol_make_shared<LvLabel>(m_authBtn.get());
	m_authBtnLabel->setText("Auth").align(LV_ALIGN_CENTER, 0, 0);

	m_descrLabel = sol_make_shared<LvLabel>(m_mainLayout.get());
	m_descrLabel->setText("Please Authorize!").addStyle(m_labelsStyle.get(), 0);

	return true;
}

void AuthWindow::_onAuthClicked()
{
	if (!m_nameTextArea || !m_passTextArea)
		return;

	std::string name = m_nameTextArea->getText();
	std::string pass = m_passTextArea->getText();

	if (name.empty() || pass.empty())
	{
		m_descrLabel->setText("Authorization FAILED!!!!");
		return;
	}

	if (!m_authCntrl)
		m_authCntrl = sol_make_shared<auth::Authorizer>();

	auto token = m_authCntrl->autorize(name, pass);
	if (token)
		m_descrLabel->setText("Authorization SUCCESS!!!!");
	else
		m_descrLabel->setText("Authorization FAILED!!!!");
}
