#include "AuthWindow.h"

#include <iostream>

#include "lv_cpp/core/LvDisplay.h"
#include "lv_cpp/core/LvIndev.h"
#include "lv_cpp/core/LvScr.h"
#include "lv_cpp/misc/LvTimer.h"
#include "lv_cpp/misc/LvAnim.h"
#include "lv_cpp/misc/LvAnimTimeline.h"

using namespace lvglpp;

namespace sol::ui
{
	/* Widgets */
	LvPointerUnique<LvLabel> label;

	/* Globals */
	static int pressed = 0;

	/* Callback for button pressed */
	void ButtonPressedAdd(lv_event_t* e) {
		pressed++;
		label->setTextFmt("%d", pressed);
	}

	/* Callback for button pressed */
	void ButtonPressedSub(lv_event_t* e) {
		if (pressed > 0)
			pressed--;
		label->setTextFmt("%d", pressed);
	}


	/* Callback for Timer pressed */
	static void TimerCb(lv_timer_t* timer) {
		pressed++;
		label->setTextFmt("%d", pressed);
	}

	/* Callback for Animation pressed */
	static void zoominCb(void* var, int32_t v) {
		LvBtn* _btn = static_cast<LvBtn*>(var);
		_btn->setSize(v, static_cast<lv_coord_t>(v * 0.5f));
	}

	/* Callback for Animation pressed */
	static void getoutCb(void* var, int32_t v) {
		LvBtn* _btn = static_cast<LvBtn*>(var);
		_btn->setX(v);
	}
} // namespace sol::ui

using namespace sol::ui;

std::string AuthWindow::templateName()
{
	return "AuthWindow";
}

bool AuthWindow::init()
{
	/* Main container */
	m_mainLayout = Make<LvObj>();
	m_mainLayout->setSize(470, 330).
		align(LV_ALIGN_CENTER, 0, 0).
		setFlexFlow(LV_FLEX_FLOW_COLUMN).
		setFlexAlign(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	m_labelsStyle = Make<LvStyle>();
	m_labelsStyle->init().setTextOpa(LV_OPA_50);

	m_nameLabel = Make<LvLabel>(m_mainLayout.get());
	m_nameLabel->setText("User name").addStyle(m_labelsStyle.get(), 0);

	m_nameTextArea = Make<LvTextarea>(m_mainLayout.get());
	m_nameTextArea->
		setOneLine(true).
		setPlaceholderText("Your name");
		//addEventCb(ta_event_cb, LV_EVENT_ALL, kb);

	m_passLabel = Make<LvLabel>(m_mainLayout.get());
	m_passLabel->setText("Password").addStyle(m_labelsStyle.get(), 0);

	m_passTextArea = Make<LvTextarea>(m_mainLayout.get());
	m_passTextArea->
		setOneLine(true).
		setPasswordMode(true).
		setPlaceholderText("Min. 8 chars.");
	//addEventCb(ta_event_cb, LV_EVENT_ALL, kb);

	m_authBtn = Make<LvBtn>(m_mainLayout.get());
	m_authBtn->setHeight(LV_SIZE_CONTENT);
	m_authBtn->setWidth(150);

	m_authBtnLabel = Make<LvLabel>(m_authBtn.get());
	m_authBtnLabel->setText("Auth").align(LV_ALIGN_CENTER, 0, 0);

	std::cout << "Application created !!!\n";
	return true;
}
