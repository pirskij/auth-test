#pragma once

#include "ui/Window.h"
#include <string>

namespace sol::ui 
{
    class AuthWindow : public Window
    {
    public:
        static std::string templateName();

        virtual bool init() override;

    private:

    };
}
