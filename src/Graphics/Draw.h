#pragma once

#include <nedef.h>

#include <Data/Point.h>

NL_NAMEUSING

NE_NAMESTART

    enum Axis { X = 0, Y = 1, Z = -1 };

    class Drawable
    {
    public:
        GLuint gl_uVao;
        GLuint gl_uVbo, gl_uIbo;
        GLfloat* arrayVertex;

        //flags
        bool gl_bLoaded;
        bool gl_bDrawing;

        Drawable();
        ~Drawable();
        virtual void Draw() = 0;
        virtual void Destroy() = 0;
        bool Initialize();
        int gl_genBuffer(const GLfloat* arrayVertex, INDEX sizeVertex, const GLushort* arrayIndex, INDEX sizeIndex);
//			GLuint LoadTexture(Texture bmpTexture);
        void Resize(int w, int h);
        void Rotate(Float alpha, Axis _ax);
    };

NE_NAMECLOSE
