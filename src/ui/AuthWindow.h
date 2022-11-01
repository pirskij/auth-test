#pragma once

#include "auth/ForwardDeclare.h"
#include "ui/Window.h"
#include <string>

namespace sol::ui 
{
    class AuthWindow : public Window
    {
    public:
        static std::string templateName();

        virtual bool init() override;

        void _onAuthClicked();

    private:
        lvglpp::LvObjSPtr      m_mainLayout;
        lvglpp::LvStyleSPtr    m_labelsStyle;
        lvglpp::LvLabelSPtr    m_nameLabel;
        lvglpp::LvTextareaSPtr m_nameTextArea;
        lvglpp::LvLabelSPtr    m_passLabel;
        lvglpp::LvTextareaSPtr m_passTextArea;
        lvglpp::LvBtnSPtr      m_authBtn;
        lvglpp::LvLabelSPtr    m_authBtnLabel;
        lvglpp::LvLabelSPtr    m_descrLabel;

        auth::AuthorizerSPtr   m_authCntrl;
    };
}
