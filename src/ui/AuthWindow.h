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
        lvglpp::LvObjSPtr      m_mainLayout;
        lvglpp::LvStyleSPtr    m_labelsStyle;
        lvglpp::LvLabelSPtr    m_nameLabel;
        lvglpp::LvTextareaSPtr m_nameTextArea;
        lvglpp::LvLabelSPtr    m_passLabel;
        lvglpp::LvTextareaSPtr m_passTextArea;
        lvglpp::LvBtnSPtr      m_authBtn;
        lvglpp::LvLabelSPtr    m_authBtnLabel;
    };
}
