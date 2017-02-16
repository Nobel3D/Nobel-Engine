#include "Form.h"

NL_NAMEUSING
NE_NAMEUSING


Form::Form()
{

}

Form::~Form()
{
    glfwTerminate();
}

bool Form::Init(NString _title)
{
    LOGFORM("Starting new Window: " + _title);

	// Initialise GLFW
	if( !glfwInit() )
	{
		ERRORFORM("Failed to initialize GLFW" );
		getchar();
		return NL_FAIL;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    form_sTitle = _title;
}

bool Form::Init()
{
    LOGFORM("Starting new Window: " + NobelLib::Program::getName());

	// Initialise GLFW
	if( !glfwInit() )
	{
		ERRORFORM("Failed to initialize GLFW" );
		getchar();
		return NL_FAIL;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    form_sTitle = NobelLib::Program::getName();

    return NL_OK;
}


bool Form::FullScreen()
{
}

bool Form::Windowed(Resolution _res, Point _position)
{
}


int Form::Show(Resolution _res)
{
    resUsing = new Resolution(_res);
    LOGFORM( "Showing Window: " + form_sTitle)
    form = glfwCreateWindow( resUsing->getWidth(), resUsing->getHeight(), form_sTitle, NULL, NULL);

    if( form == NULL )
    {
		ERRORFORM( "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n" );
		getchar();
		glfwTerminate();
		return NL_FAIL;
	}
    glfwMakeContextCurrent(form);
    // Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
        ERRORFORM( "Failed to initialize GLEW\n" );
		getchar();
		glfwTerminate();
		return NL_FAIL;
	}

	// Ensure we can capture the escape key being pressed below
    glfwSetInputMode(form, GLFW_STICKY_KEYS, GL_TRUE);

    glGenVertexArrays(1, &idVertexArray);
    glBindVertexArray(idVertexArray);

    return NL_OK;
}

bool Form::Frame()
{
    form_fps++;
    return glfwGetKey(form, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(form) == 0;
}

//handles the window's resizing event
void Form::Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return

	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
}

void Form::Swap()
{
    glfwSwapBuffers(form);
}

void Form::BackgroundColor(const Color& color)
{
    glClearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}

void Form::Clear()
{
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
}

Resolution* Form::getResolution()
{
    return resUsing;
}
