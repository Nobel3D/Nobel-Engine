#pragma once

#include <nedef.h>

class Text : Draw
{
private:
    NString sText;
    COOR x, y;
public:
    Text();
    Text(NString _text, COOR _x, COOR _y);

    void Draw();
    void Destroy();
};
