#pragma once

#include <nedef.h>

NL_NAMEUSING

NE_NAMESTART

    enum Axis { X = 0, Y = 1, Z = -1 };

    class NObject
    {
    public:
        GLuint gl_uVao;
        GLuint	gl_uVbo, gl_uIbo;
        const GLfloat* gl_aVertex;
        const GLushort* gl_aIndex;
        int gl_iVertex;
        int gl_iIndex;

        //flags
        bool gl_bLoaded;
        bool gl_bDrawing;

        NObject();
        ~NObject();
        virtual void Draw() = 0;
        virtual void Destroy() = 0;
        bool Initialize();
        int gl_genBuffer();
//			GLuint LoadTexture(Texture bmpTexture);
        void Resize(int w, int h);
        void Rotate(Float alpha, Axis _ax);
    };

NE_NAMECLOSE
