#pragma once

#include "ui/Window.h"
#include "lv_cpp/core/lvglpp.h"
#include "lv_cpp/core/LvObj.h"
#include "lv_cpp/misc/LvStyle.h"
#include "lv_cpp/widgets/LvWidgets.h"
#include <string>

namespace sol::ui 
{
    class AuthWindow : public Window
    {
    public:
        static std::string templateName();

        virtual bool init() override;

    private:
        lvglpp::LvPointerUnique<lvglpp::LvObj>      m_mainLayout;
        lvglpp::LvPointerUnique<lvglpp::LvStyle>    m_labelsStyle;
        lvglpp::LvPointerUnique<lvglpp::LvLabel>    m_nameLabel;
        lvglpp::LvPointerUnique<lvglpp::LvTextarea> m_nameTextArea;
        lvglpp::LvPointerUnique<lvglpp::LvLabel>    m_passLabel;
        lvglpp::LvPointerUnique<lvglpp::LvTextarea> m_passTextArea;
        lvglpp::LvPointerUnique<lvglpp::LvBtn>      m_authBtn;
        lvglpp::LvPointerUnique<lvglpp::LvLabel>    m_authBtnLabel;
    };
}
