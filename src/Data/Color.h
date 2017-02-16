#pragma once

#include <nedef.h>

NE_NAMESTART

#define MAX_COLOR 255

class Color
{
private:
    float R;
    float G;
    float B;
    float A;
public:
    Color(float _R, float _G, float _B, float _A);


    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    float getAlpha() const;

    void setRed(float _R);
    void setGreen(float _G);
    void setBlue(float _B);
    void setAlpha(float _A);

};

NE_NAMECLOSE
