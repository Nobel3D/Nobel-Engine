#pragma once

#include <nedef.h>
#include <Data/Point.h>
#include <Data/VideoMode.h>
#include <Data/OpenGL.h>
#include <Data/Color.h>

NL_NAMEUSING

NE_NAMESTART

    class Form
    {
    private:

        Point* form_pPosition;
        Resolution* resUsing;
        //form
        Window* form;
        bool form_bActive;
        NString form_sTitle;
        static bool form_bExit;
        //GL
        GLuint idVertexArray;

    public:

        Form();
        ~Form();

        bool Init();
        bool Init(NString _title);

        int Show(Resolution _res);
        bool Frame();
        bool FullScreen();
        bool Windowed(Resolution _res, Point _position);
        static void Reshape(int x, int y);
        void Swap();

        void BackgroundColor(const Color& color);
        void Clear();


        Resolution* getResolution();
        int form_fps=0;
    };


NE_NAMECLOSE
