#include "VideoMode.h"

NL_NAMEUSING
NE_NAMEUSING

Resolution::Resolution(int w, int h)
{
	if(float(w) / float(h) == float(16/9))
        scr_Ratio = ScreenRatio::_16_9;
    else if (float(w) / float(h) == float(4/3))
        scr_Ratio = ScreenRatio::_4_3;
    else
    {
        scr_Ratio = ScreenRatio::_4_3;
        w = 800; h = 600;
    }

	scr_iWidth = w; scr_iHeight = h;
};

int Resolution::getWidth() const { return scr_iWidth; }
int Resolution::getHeight() const { return scr_iHeight; }
ScreenRatio Resolution::getRatio() const { return scr_Ratio; }
