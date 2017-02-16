// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
// Include GLEW
#include <GL/glew.h>
#include <NobelEngine.h>

using namespace NobelLib;
using namespace NobelEngine;
using namespace glm;

Form* form;
Triangles tri( new Point3(-1.0f, -1.0f, 0.0f),
               new Point3(1.0f, -1.0f, 0.0f),
               new Point3(0.0f,  1.0f, 0.0f));

Shader vertex;
Shader fragment;


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

int fps = 0;

void* timer (void* null)
{
    Timer tm;
    tm.Start(1000);
    while(true)
    {
        if(tm.getTime() > 1000)
        {
            std::cout << "FPS: " << form->form_fps << std::endl;
            form->form_fps = 0;
            tm.Reset();
        }
    }

    return nullptr;
}

int main(int argc, char** argv)
{
    Program("Nobel OpenGL Engine", "0.01", argc, argv);

    Thread thread;
    thread.Start(nullptr, timer ,nullptr);

    form = new Form();

    form->Init();

    form->Show(Resolution(800,600));

    // Dark blue background
    Color background(MAX_COLOR / 255, MAX_COLOR / 165, 0, 0.5f);
    form->BackgroundColor(background);

	ShaderProgram shapro;

    Filename* _vertex = new Filename("SimpleVertexShader.vertexshader");
    Filename* _fragment = new Filename("SimpleFragmentShader.fragmentshader");

    vertex.Init(ShaderType::Vertex);
    fragment.Init(ShaderType::Fragment);

    vertex.Load(*_vertex);
    fragment.Load(*_fragment);

    vertex.Compile();
    fragment.Compile();

    shapro.Attach(vertex); shapro.Attach(fragment);
    shapro.Link();

    Camera* camera = new Camera(vec3(4,3,3), vec3(0,0,0), vec3(0,1,0), 0.1f, 100.f);

    mat4 Projection = camera->projection(45.0f,form->getResolution());

    mat4 View = camera->lookAt();

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = shapro.getAttribute("MVP");

    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around


    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
    };

    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
        0.f,  0.f,  1.f, ///
        0.f,  0.f,  1.f,
        0.f,  0.f,  1.f,

        0.f,  1.f,  0.f,
        0.f,  1.f,  0.f,
        0.f,  1.f,  0.f,

        1.f,  0.f,  0.f, //
        0.f,  0.f,  1.f,
        0.f,  0.f,  1.f,

        1.f,  0.f,  0.f, //
        0.f,  0.f,  1.f,
        0.f,  0.f,  1.f,

        1.f,  0.f,  0.f, //
        1.f,  0.f,  0.f,
        1.f,  0.f,  0.f,

        0.f,  1.f,  0.f, //
        0.f,  0.f,  1.f,
        0.f,  0.f,  1.f,

        0.f,  0.f,  1.f, /*Triangolo basso frontale*/
        0.f,  0.f,  1.f,
        0.f,  0.f,  1.f,

        1.f,  0.f,  0.f, /*Triangolo alto lato destro*/
        1.f,  0.f,  0.f,
        1.f,  0.f,  0.f,

        1.f,  0.f,  0.f,
        1.f,  0.f,  0.f,
        1.f,  0.f,  0.f,

        0.f,  1.f,  0.f, /*Triangolo alto superiore*/
        0.f,  1.f,  0.f,
        0.f,  1.f,  0.f,

        0.f,  1.f,  0.f,
        0.f,  1.f,  0.f,
        0.f,  1.f,  0.f,

        0.f,  0.f,  1.f, /*Triangolo alto frontale*/
        0.f,  0.f,  1.f,
        0.f,  0.f,  1.f
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


	do{
        form->Clear();
        shapro.Use();
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


        // 1rst attribute buffer : vertices
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );

                // 2nd attribute buffer : colors
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
                glVertexAttribPointer(
                    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                    3,                                // size
                    GL_FLOAT,                         // type
                    GL_FALSE,                         // normalized?
                    0,                                // stride
                    (void*)0                          // array buffer offset
                );

                // Draw the triangle !
                glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

		form->Swap();

	} // Check if the ESC key was pressed or the window was closed
	while( form->Frame() );

   shapro.Disable();
   glDeleteBuffers(1, &vertexbuffer);
   glDeleteBuffers(1, &colorbuffer);

    return 0;
}

#define COMPARE_FAIL(a,b) { fwrite("\n---", 4 , 1 , stdout); fwrite(&a, 1 , 1 , stdout); fwrite("\n+++", 4 , 1 , stdout); fwrite(&b, 1 , 1 , stdout); }
NString compare(const char* a, const char* b)
{
    int i = 0;
    while(a[i] != '\0' || b[i] != '\0')
    {
        if(a[i] == b[i])
            fwrite(&a[i], 1, 1, stdout);
        else
            COMPARE_FAIL(a[i], b[i])
        i++;
    }
}

GLuint LoadShaders(const char * vertex_file,const char * fragment_file){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream("SimpleVertexShader.vertexshader", std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream("SimpleFragmentShader.fragmentshader", std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	char const * VertexSourcePointer = vertex_file;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	char const * FragmentSourcePointer = fragment_file;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


