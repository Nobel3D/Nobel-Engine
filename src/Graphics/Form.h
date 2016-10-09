#pragma once

#include <nedef.h>
#include <Data/Point.h>
#include <Data/VideoMode.h>

NL_NAMEUSING

NE_NAMESTART

    class Form
    {
    private:

        Point* form_pPosition;
        //form
        int form_ID;
        bool form_bActive;
        NString form_sTitle;
        static bool form_bExit;

    public:

        Form();
        ~Form();

        bool Init();

        int Show();
        bool FullScreen();
        bool Windowed(Resolution _res, Point _position);
        bool Windowed(Resolution _res);
        static void Reshape(int x, int y);

    };


NE_NAMECLOSE
