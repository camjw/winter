#ifndef WINTER_UI_WIDGET_H
#define WINTER_UI_WIDGET_H

#include <imgui/imgui.h>

class UIWidget
{
public:
    inline void draw_if_active()
    {
        if (is_active)
        {
            draw();
        }
    }

    bool is_active = false;

private:
    virtual void draw() = 0;
};

#endif // WINTER_UI_WIDGET_H
