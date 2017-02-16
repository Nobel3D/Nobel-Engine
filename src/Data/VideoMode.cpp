#include "VideoMode.h"

NL_NAMEUSING
NE_NAMEUSING

Resolution::Resolution(int w, int h)
{
    fRatio = float(w) / float(h);
    iWidth = w; iHeight = h;
};

int Resolution::getWidth() const { return iWidth; }
int Resolution::getHeight() const { return iHeight; }
float Resolution::getRatio() const { return fRatio; }
