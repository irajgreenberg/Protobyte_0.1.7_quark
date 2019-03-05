/*!  \brief  Protoplasm.h: Base class that encapsulates GLFW/GL
Protoplasm.h
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



#ifndef __PROTO_PLASM_H__
#define __PROTO_PLASM_H__

// set up GL/GL extensions on Win/OSX/Linux

//#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
//#define GLEW_STATIC // link to glew32s instead of including dll
//#include <GL/glew.h>
//#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include "glad/glad.h"
#else
#define GLFW_INCLUDE_GLCOREARB
#endif

//// bring in GLU (shouldn't need)
//#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>

#include <iostream>
#include "ProtoBaseApp.h"

namespace ijg {
    
	static void error_callback(int error, const char* description)
	{
		fputs(description, stderr);
	}

    class ProtoPlasm {
        
    public:
		// Setup Event callbacks pushed through to user ProtoController class
		friend void mouseBtn_callback(GLFWwindow* window, int button, int action, int mods);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void window_size_callback(GLFWwindow* window, int width, int height);
		
        int frameCount;
        float frameRate;
        
        //cstrs
		explicit ProtoPlasm(ProtoBaseApp* baseApp);
        ProtoPlasm(int appWidth, int appHeight, std::string appTitle, ProtoBaseApp* baseApp);
        
    private:
        
		void initGLFW();
        void runGLFW();
        
        // cross-platform SFML Window
        //sf::Window* window;
        GLFWwindow* window;
        
        // Master controller class, manages view, lighting and rendering
        //std::unique_ptr<ProtoWorld> world;
        
        // base app class for user defined app classes
        ProtoBaseApp* baseApp;
        
        int appWidth;
        int appHeight;
        std::string appTitle;

		
    };

	

   
}

#endif // __PROTO_PLASM_H__
