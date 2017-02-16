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
        _16_9   = 16/9,
        _4_3    = 4/3
    };

    class Resolution
    {
    private:
        int iWidth;
        int iHeight;
        float fRatio;
    public:
        Resolution(int w, int h);
        ~Resolution() {};
        int getWidth() const;
        int getHeight() const;
        float getRatio() const;
    };

NE_NAMECLOSE
