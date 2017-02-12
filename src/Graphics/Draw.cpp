#include "Draw.h"
#include <Data/OpenGL.h>

NL_NAMEUSING

NE_NAMESTART

Drawable::Drawable()
{
    LOGOBJ("Initializating new Object");
}

Drawable::~Drawable()
{
    LOGOBJ("Destroying Object");
}

int Drawable::gl_genBuffer(const GLfloat* arrayVertex, INDEX sizeVertex, const GLushort* arrayIndex, INDEX sizeIndex)
{
    ASSERT (arrayVertex != nullptr && sizeVertex > 0);
    ASSERT(arrayIndex != nullptr && sizeIndex > 0);

    LOGOBJ("Creating Object's Buffer");

    //TODO
    glGenBuffers(1, &gl_uVbo);
    glBindBuffer(GL_ARRAY_BUFFER, gl_uVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeVertex, arrayVertex, GL_STATIC_DRAW);

    glGenBuffers(1, &gl_uIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_uIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndex, arrayIndex, GL_STATIC_DRAW);
}

NE_NAMECLOSE
