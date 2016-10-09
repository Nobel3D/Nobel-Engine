#pragma once

#include <nedef.h>

NL_NAMEUSING

NE_NAMESTART

    enum ScreenMode
    {
        FULLSCREEN = 0,
        WINDOWED = 1,
        BORDERLESS = 2 //Programming
    };

    enum ScreenRatio
    {
        _16_9   = 0,
        _4_3    = 1
    };

    class Resolution
    {
    private:
        int scr_iWidth;
        int scr_iHeight;
        ScreenRatio scr_Ratio;
    public:
        Resolution(int w, int h);
        ~Resolution() {};
        int getWidth() const;
        int getHeight() const;
        ScreenRatio getRatio() const;
    };

NE_NAMECLOSE
