#include "Triangles.h"

#include <GL/glew.h>

NL_NAMEUSING
NE_NAMEUSING

Triangles::Triangles(Point3* _1, Point3* _2, Point3* _3) : Drawable()
{
	ASSERT (_1 != _2 && _1 != _3 && _2 != _3);
	geo_pTriangle1 = _1;
	geo_pTriangle2 = _2;
	geo_pTriangle3 = _3;
}


Triangles::~Triangles()
{
	Destroy();
}


void Triangles::Draw()
{
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, gl_uVbo);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

}

void Triangles::Load()
{

    glGenVertexArrays(1, &gl_uVao);
	glBindVertexArray(gl_uVao);

	const GLfloat triangleVertex[] = {
		geo_pTriangle1->x, geo_pTriangle1->y, geo_pTriangle1->z,
		geo_pTriangle2->x, geo_pTriangle2->y, geo_pTriangle2->z,
		geo_pTriangle3->x, geo_pTriangle3->y, geo_pTriangle3->z
	};

    // Generate 1 buffer, put the resulting identifier in gl_uVbo
    glGenBuffers(1, &gl_uVbo);
    // The following commands will talk about our 'gl_uVbo' buffer
    glBindBuffer(GL_ARRAY_BUFFER, gl_uVbo);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertex), triangleVertex, GL_STATIC_DRAW);

}

void Triangles::Destroy()
{
    	// Cleanup VBO
	glDeleteBuffers(1, &gl_uVbo);
    glDeleteVertexArrays(1, &gl_uVao);
	delete[] geo_pTriangle1;
	delete[] geo_pTriangle2;
	delete[] geo_pTriangle3;
}
