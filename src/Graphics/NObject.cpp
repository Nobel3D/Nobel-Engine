#include "NObject.h"
#include <Data/OpenGL.h>

NL_NAMEUSING

NE_NAMESTART

NObject::NObject()
{
    LOGOBJ("Initializating new Object");
}

NObject::~NObject()
{
    LOGOBJ("Destroying Object");
}

int NObject::gl_genBuffer()
{
    LOGOBJ("Creating Object's Buffer");
    ASSERT (gl_aVertex != nullptr);
    ASSERT(gl_aIndex != nullptr);

    //TODO
    glGenBuffers(1, &gl_uVbo);
    glBindBuffer(GL_ARRAY_BUFFER, gl_uVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gl_aVertex[0]) * gl_iVertex, gl_aVertex, GL_STATIC_DRAW);

    glGenBuffers(1, &gl_uIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_uIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gl_aIndex[0]) * gl_iIndex, gl_aIndex, GL_STATIC_DRAW);
}

NE_NAMECLOSE
