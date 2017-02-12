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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

/*	ShaderProgram shapro;

	NFile* _vertex = new NFile("SimpleVertexShader.vertexshader");
    NFile* _fragment = new NFile("SimpleFragmentShader.fragmentshader");

    _vertex->Open(Reading);
    _fragment->Open(Reading);

    vertex.Init(ShaderType::Vertex);
    fragment.Init(ShaderType::Fragment);

    vertex.Load(_vertex->ReadAll());
    fragment.Load(_fragment->ReadAll());

    vertex.Compile();
    fragment.Compile();

    shapro.Attach(vertex); shapro.Attach(fragment);
    shapro.Link();

	GLuint programID = LoadShaders(_vertex->ReadAll(), _fragment->ReadAll() );

*/
/*
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

// This will identify our vertex buffer
GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
*/
    tri.Load();


	do{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

//		shapro.Use();
        tri.Draw();
		form->Swap();

	} // Check if the ESC key was pressed or the window was closed
	while( form->Frame() );

//    shapro.Disable();

	tri.Destroy();

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


