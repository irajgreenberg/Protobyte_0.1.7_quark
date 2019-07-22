/*!  \brief  Protoplasm.cpp: Base class that encapsulates GLFW/GL
Protoplasm.cpp
Protobyte Library

Copyright (c) 2013 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained in any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/


#include "ProtoPlasm.h"

namespace ijg {
	void mouseBtn_callback(GLFWwindow* window, int button, int action, int mods) {

		ProtoBaseApp* ba = (ProtoBaseApp*)glfwGetWindowUserPointer(window);
		ba->setMouseButton(action, button, mods);
	}

	void  key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		ProtoBaseApp* ba = (ProtoBaseApp*)glfwGetWindowUserPointer(window);
	

		// detect press 1x
		if (action == GLFW_PRESS) {
			ba->setKeyEvent(key, scancode, action, mods);
		}
	}

	void window_size_callback(GLFWwindow* window, int width, int height) {
		ProtoBaseApp* ba = (ProtoBaseApp*)glfwGetWindowUserPointer(window);
		ba->setWindowFrameSize(Dim2i(width, height));
	}
}

using namespace ijg;

ProtoPlasm::ProtoPlasm(ProtoBaseApp* baseApp) :
baseApp(baseApp), appWidth(1920), appHeight(1080), appTitle("Protobyte App")
{
	// init app and call init() and run() to activate functions in user defined BaseApp derived class
	initGLFW();
	runGLFW();
}

ProtoPlasm::ProtoPlasm(std::string appTitle, ProtoBaseApp* baseApp) :
	appWidth(1920), appHeight(1080), appTitle(appTitle), baseApp(baseApp) {
	// this->baseApp = baseApp;
	baseApp->setWidth(appWidth);
	baseApp->setHeight(appHeight);
	baseApp->setSize(Dim2i(appWidth, appHeight));

	// Create GL context and call init() and run() to activate functions in user defined BaseApp derived class
	initGLFW();
	runGLFW();
}

ProtoPlasm::ProtoPlasm(int appWidth, int appHeight, std::string appTitle, ProtoBaseApp* baseApp) :
appWidth(appWidth), appHeight(appHeight), appTitle(appTitle), baseApp(baseApp){

	

	// this->baseApp = baseApp;
	baseApp->setWidth(appWidth);
	baseApp->setHeight(appHeight);
	baseApp->setSize(Dim2i(appWidth, appHeight));

	// Create GL context and call init() and run() to activate functions in user defined BaseApp derived class
	initGLFW();
	runGLFW();
}


void ProtoPlasm::initGLFW(){

	baseApp->setFrameCount(0);
	baseApp->setFrameRate(60.0f);

	// seed random function
	srand(static_cast <unsigned> (time(0)));

	// catch start-up failures
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	// OS X, for modern GL
#if defined(__APPLE__)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	// set number of multi-samples for anti-aliasing
	// the more samples,the worse performance
	// PRotobyte has a bias toward high quality over
	// performance, which may be overrided with
	// setMultiSamples(int samples) - still needs to be implemented
	glfwWindowHint(GLFW_SAMPLES, 8);


	// genereate sized GLFW window with title
	window = glfwCreateWindow(appWidth, appHeight, appTitle.c_str(), nullptr, nullptr);

	// full size     
	//window = glfwCreateWindow(appWidth, appHeight, appTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);


	// connected monitors
	int monitors;
	GLFWmonitor** mons = glfwGetMonitors(&monitors);

	// Position window for different montior configurations
	//  -- primary monitor resolution :
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// for Syzygy 2018, turned off
	switch (monitors){
	case 1:
		glfwSetWindowPos(window, (mode->width - appWidth) / 2, (mode->height - appHeight) / 2);
//#if defined(_WIN32) || defined(_WIN64)
//		HWND hWnd = GetConsoleWindow();
//		MoveWindow(hWnd, 100, 100, 300, 400, TRUE);
//#endif
		break;
	case 2:
		glfwSetWindowPos(window, (mode->width - appWidth) / 2, (mode->height - appHeight) / 2);
		break;
	case 3:
		glfwSetWindowPos(window, (mode->width - appWidth) / 2, (mode->height - appHeight) / 2);
		break;
	case 4:
		/* Centers in top monitor
		   in 1/3 configuration:
		       [x]
		    [ ][ ][ ]
		*/
		glfwSetWindowPos(window, (mode->width - appWidth) / 2, -mode->height + (mode->height-appHeight) / 2);
		break;
	case 6:
		/* Centers in top monitor
		in 1/3 configuration:
		[ ][x][ ]
		[ ][ ][ ]
		*/
		glfwSetWindowPos(window, (mode->width - appWidth) / 2, -mode->height + (mode->height - appHeight) / 2);
		break;
	default:
		glfwSetWindowPos(window, (mode->width - appWidth) / 2, (mode->height - appHeight) / 2);
	}
	//HERE, HERE, HERE, HERE
	// ONLY for SYZYGY
	//glfwSetWindowPos(window, 1850, 0);


	glfwSetWindowUserPointer(window, baseApp); // enable callback funcs to speak to baseApp
	
	// register callbacks
	glfwSetWindowSizeCallback(window, window_size_callback); // change viewport on resize
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseBtn_callback);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);

	// load GL extensions via glad
#if defined(_WIN32) || defined (_WIN64) || defined(__linux__) 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
	}
#endif

	// end GLFW/window setup

	// Set gl states
	//glClearColor(.46f, .485f, .575f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glFrontFace(GL_CCW); // default
	////glFrontFace(GL_CW);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glDisable(GL_CULL_FACE);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glEnable(GL_COLOR_MATERIAL); // incorporates per vertex color with lights
	// let glColor control diffues and ambient material values
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//
	//glEnable(GL_BLEND);
	////glBlendFunc(GL_DST_COLOR,GL_ZERO);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_DST_COLOR,GL_ZERO);
	//glBlendFunc (GL_ONE, GL_ONE);

	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER,0.0f);

	// for best antialiasing
	// http://bankslab.berkeley.edu/members/chris/AntiAliasing/AntiAliasingInOpenGL.html
	//glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_POLYGON_SMOOTH);
	//glEnable(GL_POINT_SMOOTH);
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	
	glClearStencil(0); // clear stencil buffer
	glClearDepth(1.0f); // 0 is near, 1 is far
	
	glDepthMask(GL_TRUE); 
	glDepthFunc(GL_LEQUAL);


	//glDepthFunc(GL_LESS);
	//glDepthRange(0.0f, 1.0f);

	// For MSAA (anti-aliasing)
	glEnable(GL_MULTISAMPLE);

	int w = 0, h = 0;
	glfwGetFramebufferSize(window, &w, &h);

	// get version of GL and hardware
	char *GL_version = (char *)glGetString(GL_VERSION);
	char *GL_vendor = (char *)glGetString(GL_VENDOR);
	char *GL_renderer = (char *)glGetString(GL_RENDERER);
	trace("Thank you for flying Protobyte.");
	trace("GL_version =", GL_version);
	trace("GL_vendor =", GL_vendor);
	trace("GL_renderer =", GL_renderer);

	// Activate init function in user derived class.n.
	baseApp->_init(); // base class
}

// activate animation thread and run() function in user defined BaseApp derived class
void ProtoPlasm::runGLFW(){

	// Activate derived user class implementations of events:
	/*
	 • run
	 • mouse
	 • keyboard
	 */

	// clear screen
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int mouseBtn = 0;
	
	while (!glfwWindowShouldClose(window))
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(1,1,0,1);
		/*
		 TO DO – fix timing issues with control for users:
		 From: http://stackoverflow.com/questions/2182675/how-do-you-make-sure-the-speed-of-opengl-animation-is-consistent-on-different-ma
		 */


		//capture mouse button
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		//baseApp->_setMousePos(mouseX, mouseY);


		//// capture key 
		//int key;
		//glfwGetKey(window, key);


		// Activate derived user class implementation.
		baseApp->setFrameCount(frameCount);
		//baseApp->runWorld();

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		baseApp->_run(Vec2f(float(mouseX), float(mouseY)/*, mouseBtn, key*/)); // called in base class
		//baseApp->run(); // called in derived class


		// handle GLFW events

		// clear the buffers
		/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
		


		// end the current frame (internally swaps the front and back buffers)
		//window->display();
		glfwSwapBuffers(window);

		glfwPollEvents();




		// test for window context resizing
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		frameCount++;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

