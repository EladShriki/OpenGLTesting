#include "GLWindow.h"


GLWindow::GLWindow()
{
	mainWindow = NULL;
	width = 800;
	heigth = 600;
	lastX = 0.0f;
	lastY = 0.0f;
	xChange = 0.0f;
	yChange = 0.0f;
	bufferHeight = 0;
	bufferWidth = 0;
	mouseFirstMoved = true;

	for (size_t i = 0; i < 1024; ++i) 
	{
		keys[i] = 0;
	}
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeigth)
{
	mainWindow = NULL;
	width = windowWidth;
	heigth = windowHeigth;
	lastX = 0.0f;
	lastY = 0.0f;
	xChange = 0.0f;
	yChange = 0.0f;
	bufferHeight = 0;
	bufferWidth = 0;
	mouseFirstMoved = true;

	for (size_t i = 0; i < 1024; ++i)
	{
		keys[i] = 0;
	}
}

GLfloat GLWindow::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat GLWindow::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

int GLWindow::Initialise()
{
	// Init glfw
	if (!glfwInit())
	{
		printf("GLFW Init failed!\n");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create Window
	mainWindow = glfwCreateWindow(width, heigth, "OpenGLTest", glfwGetPrimaryMonitor(), NULL);
	if (!mainWindow) {
		printf("GLFW Window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW
	glfwMakeContextCurrent(mainWindow);
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Handle Key + Mouse Input
	createCallbacks();

	// Allow modern extention
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW Init failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

void GLWindow::createCallbacks() 
{
	glfwSetKeyCallback(mainWindow, handlekeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void GLWindow::handlekeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void GLWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

GLWindow::~GLWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}