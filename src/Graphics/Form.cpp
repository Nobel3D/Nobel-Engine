#include "Form.h"
#include <GL/glew.h>
#include <GL/glut.h>

NL_NAMEUSING
NE_NAMEUSING

Form::Form()
{

}

Form::~Form()
{

}

bool Form::Init()
{
    glutInit(Program::getNumberArg(), Program::getArgument());
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    form_sTitle = Program::getName();
    ASSERT(!form_sTitle.Null());
}

bool Form::FullScreen()
{
    glutFullScreen();
}

bool Form::Windowed(Resolution _res, Point _position)
{
    glutInitWindowSize(_res.getWidth(), _res.getHeight()); //set window size
    glutInitWindowPosition(_position.x.toInt(), _position.y.toInt()); //set window position on screen
}
bool Form::Windowed(Resolution _res)
{

    glutInitWindowSize(_res.getWidth(), _res.getHeight()); //set window size
    glutInitWindowPosition(0,0); //set window position on screen
}

int Form::Show()
{
    form_ID = glutCreateWindow(form_sTitle);
    glutReshapeFunc(Reshape);
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


/*
bool Form::form_bExit;
Point Form::scr_cPosition;
RECT Form::WindowRect;
Input* Form::form_xInput;
void (*Form::form_Input)();
ScreenMode Form::scr_nMode;

Form::Form()
{
	hDC = NULL;
	hRC = NULL;
	hWnd = NULL;
}

Form::~Form()
{
	Destroy();
}

void Form::Destroy()
{
	if (scr_nMode == FULLSCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}

	if (hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
		hRC = NULL;
	}

	if (hDC)
	{
		ReleaseDC(hWnd, hDC);
		hDC = NULL;
	}

	if (hWnd)
	{
		DestroyWindow(hWnd);
		hWnd = NULL;
	}

	UnregisterClass(NString(CLASSNAME), hInst);
	hInst = NULL;

	form_bActive = false;
	form_bExit = true;
}

bool Form::createGLWindow(NString title, void(*funcInput)())
{
	if (form_bActive)
	{
		DWORD		dwExStyle;
		DWORD		dwStyle;
		WNDCLASS	wc;

		int	width = scr_cResolution.scr_iWidth;
		int	height = scr_cResolution.scr_iHeight;
		form_sTitle = title;
		form_xInput = new Input;
		form_Input = funcInput;

		scr_cPosition = Point(scr_cNative.scr_iWidth / 2 - width / 2, scr_cNative.scr_iHeight / 2 - height / 2);

		int	x = !scr_nMode ? 0 : scr_cPosition.x;
		int	y = !scr_nMode ? 0 : scr_cPosition.y;

		WindowRect.left = (long)x;
		WindowRect.right = (long)x + width;
		WindowRect.top = (long)y;
		WindowRect.bottom = (long)y + height;

		hInst = GetModuleHandle(NULL);							// Grab current instance for window
		wc.style = CS_OWNDC;									// Own DC for window.
		wc.lpfnWndProc = (WNDPROC)WindowProcess;						// WinProc handles messages
		wc.cbClsExtra = 0;										// Extra window data
		wc.cbWndExtra = 0;										// Extra window data
		wc.hInstance = hInst;									// Copying instance
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// Loading icon from resource file
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);				// Loading the arrow pointer
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // Background is not required for opengl
		wc.lpszMenuName = NULL;									// Setting menu
		wc.lpszClassName = NString(CLASSNAME);					// Setting class name

		if (!RegisterClass(&wc))
		{
			Error("NobelLib::Graphics::Form::createGLForm impossible register this class on windows", 75, false);
			Destroy();
			return false;
		}


		if (scr_nMode == FULLSCREEN)
		{
			DEVMODE dm;
			memset(&dm, 0, sizeof(dm));
			dm.dmSize = sizeof(dm);
			dm.dmPelsWidth = width;
			dm.dmPelsHeight = height;
			dm.dmBitsPerPel = gl_iBit;
			dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
			ShowCursor(false);
		}
		else
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU;
			ShowCursor(true);
		}

		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

		hWnd = CreateWindow(					// Extended Style For The Window
			NString(CLASSNAME),					// Class Name
			form_sTitle,						// Window Title (Use DefWindowProcW or will be truncated)
			dwStyle | WS_CAPTION |				// Window Style
			WS_POPUPWINDOW | WS_VISIBLE,		// Window Style
			WindowRect.left, WindowRect.top,    // Window Position
			WindowRect.right - WindowRect.left, // Window Width
			WindowRect.bottom - WindowRect.top,	// Window Height
			NULL,								// No Parent Window
			NULL,								// No Menu
			hInst,								// Current Instance
			NULL);								// Dont Pass Anything To WM_CREATE

		if (!hWnd)
		{
			Error("NobelLib::Graphics::Form::createGLWindow failed to create window, handler gave error!", 76, false);
			Destroy();
			return false;
		}

		//RECT rcClient, rcWind;
		//GetClientRect(hWnd, &rcClient);
		//GetWindowRect(hWnd, &rcWind);
		//borderWidth = 2 * ((rcWind.right - rcWind.left) - rcClient.right) / 2;
		//borderHeight = 2 * ((rcWind.bottom - rcWind.top) - rcClient.bottom) / 2;
		initGL();
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		return true;
	}
	else
	{
		Error("NobelLib::Graphics::Form::createGLWindow() cannot start because form isn't initializated!", 74, false);
		return false;
	}
}
int Form::initGL()
{

		if (!(hDC = GetDC(hWnd)))							// Did we get a Device Context?
		{
			Error("NobelLib::Graphics::Form::initGL() Cannot create a GL Device Context", 77, false);
			Destroy();
			return -1;
		}

		PIXELFORMATDESCRIPTOR _pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd
		1,                     // version number
		PFD_DRAW_TO_WINDOW |   // support window
		PFD_SUPPORT_OPENGL |   // support OpenGL
		PFD_DOUBLEBUFFER,      // double buffered
		PFD_TYPE_RGBA,         // RGBA type
		gl_iBit,               // bit rate color depth
		0, 0, 0, 0, 0, 0,      // color bits ignored
		0,                     // no alpha buffer
		0,                     // shift bit ignored
		0,                     // no accumulation buffer
		0, 0, 0, 0,            // accum bits ignored
		16,                    // 16-bit z-buffer
		0,                     // no stencil buffer
		0,                     // no auxiliary buffer
		PFD_MAIN_PLANE,        // main layer
		0,                     // reserved
		0, 0, 0                // layer masks ignored
	};

	if (!(PixelFormat = ChoosePixelFormat(hDC, &_pfd))) //attempts to match an appropriate pixel format supported by a device context to a given pixel format specification.
	{
		Error("NobelLib::Graphics::Form::initGL() Cannot find a suitable PixelFormat", 78, false);
		Destroy();
		return -1;
	}


	if (!SetPixelFormat(hDC, PixelFormat, &_pfd))		// Are we able to set the Pixel Format?
	{
		Error("NobelLib::Graphics::Form::initGL() Cannot set PixelFormat", 79, false);
		Destroy();
		return -1;
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are we able to get a Rendering Context?
	{
		Error("NobelLib::Graphics::Form::initGL() Cannot create a rendering context", 80, false);
		Destroy();
		return -1;
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try to activate the Rendering Context
	{
		Error("NobelLib::Graphics::Form::initGL() Cannot activate a rendering context", 81,false);
		Destroy();
		return -1;
	}
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Background
	glClearDepth(1.0f);									// Depth buffer setup
	glEnable(GL_DEPTH_TEST);							// Enables depth testing
	glDepthFunc(GL_LEQUAL);								// Depth testing
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Nice perspective

	GLenum err = glewInit();
	if (!err)
		return -1;
	PFD = _pfd;
	return 0;
}


bool Form::Initialize()
{
	form_bActive = true;
	scr_nMode = FULLSCREEN; //debug only

	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &nativeMode); //Function intrusive
	//Auto detect native resolution for your window
	scr_cNative = Resolution(nativeMode.dmPelsWidth, nativeMode.dmPelsHeight);
	scr_cResolution = Resolution(nativeMode.dmPelsWidth, nativeMode.dmPelsHeight);
	return true;
}
bool Form::Initialize(Resolution useRes, ScreenMode numMod)
{
	form_bActive = true;
	scr_nMode = numMod;

	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &nativeMode); //Function intrusive
	scr_cNative = Resolution(nativeMode.dmPelsWidth, nativeMode.dmPelsHeight);
	scr_cResolution = useRes;
	return true;
}

void Form::Draw()
{
	if (form_bActive)
	{
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		ShowWindow(hWnd,
			SW_SHOW);
		UpdateWindow(hWnd);
	}
	else
	{
		Error("NobelLib::Graphics::Form::Draw() cannot start because form isn't initializated!", 73, false);
	}
}

void Form::gl_Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Form::Resize(int w, int h)
{
	int	x = !scr_nMode ? 0 : scr_cPosition.x;
	int	y = !scr_nMode ? 0 : scr_cPosition.y;

	WindowRect.left = (long)x;
	WindowRect.right = (long)x + w;
	WindowRect.top = (long)y;
	WindowRect.bottom = (long)y + h;
}

void Form::Load(void * null)
{
}

bool NobelLib::Graphics::Form::winLoop(MSG* msg)
{
	if(getStatus())
	{
		if (PeekMessage(msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg->message == WM_QUIT)
			{
				Destroy();
				return false;
			}
		}
		else
		{
			TranslateMessage(msg);
			DispatchMessage(msg);
		}
		return true;
	}
	return false;
}

int Form::getStatus()
{ //eventually add status return code (appear error n...) like int ForceQuit (int nError)
	if (form_bExit)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

Lint CALLBACK Form::WindowProcess(HWND handle, uint message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_QUIT:
		return 0;
	case WM_ACTIVATE:
		return 0;
	case WM_CREATE:
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		return 0;
	case WM_LBUTTONUP:
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	case WM_SIZE:
		Form::Resize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_GETMINMAXINFO:
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		form_xInput->keyboard.keyDown((byte)wParam);
		form_Input();
		return 0;
	case WM_KEYUP:
		form_xInput->keyboard.keyUp((byte)wParam);
		return 0;
	case WM_NCLBUTTONDOWN:
		return 0;
	case WM_NCLBUTTONUP:
		return 0;
	case WM_TIMER:
		return 0;
	case WM_EXITSIZEMOVE:
		return 0;
	case WM_SETCURSOR:
		return 0;
	case WM_CANCELMODE:
		return 0;
	case WM_MOUSEWHEEL:
		return 0;
	default:
		return DefWindowProcW(handle, message, wParam, lParam);
	}
}
*/
