/*!  \brief  ProtoPath2.h: Class for drawing methods, moveTo, lineTo, curveTo...
ProtoPath2.h
Protobyte Library v02

Created by Ira on 1/2/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef PROTO_PATH2_H
#define PROTO_PATH2_H

// brings in GL header
//#if defined (_WIN32) || defined(_WIN64)
//#define GLEW_STATIC // link to glew32s instead of including dll
//#include <GL/glew.h>
//#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include "glad/glad.h"
#endif

#include "ProtoColor4.h"
#include "ProtoVector2.h"
//#include "ProtoShader.h""


namespace ijg {

	// for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))

	namespace {
		static const int OPEN = 0; 
		static const int CLOSE = 1;
	}
	
	
	
	// forward declare to access renderer/shader
	// eventually examine this design, maybe looking
	// at some type of interface solution.
	class ProtoBaseApp;

	class ProtoPath2 {
	private:

		//ProtoShader shader;
		GLuint vaoPathID, vboPathID, indexVboPathID;
		std::vector<Vec2f> pathVecs; 
		std::vector<float> pathPrims;
		std::vector<int> pathInds;
		bool isFill, isStroke;
		Col4f fillCol, strokeCol;
		std::vector<Col4f> fillCols, strokeCols;
		int pathEndState;

		void init();

		ProtoBaseApp* baseApp;
	
	public:
		enum TessellationMode{
			POLY,
			TRI,
			TRI_FAN,
			TRI_STRIP,
			LINES,
			LINE_STRIP,
			LINE_LOOP
		};
		
		ProtoPath2();
		ProtoPath2(ProtoBaseApp* baseApp);
		ProtoPath2(const std::vector<Vec2f>& path);
		ProtoPath2(const std::vector<Vec2f>& path, const std::vector<Col4f>& cols);
		~ProtoPath2();

		// set Shader
		//const ProtoShader* shader;
		//void setShader(const ProtoShader* shader);

		/*bool isClosed;*/

		void moveTo(float x, float y);
		void moveTo(const Vec2f& v);
		void lineTo(float x, float y); 
		void lineTo(const Vec2f& v);
		void curveTo(float x, float y); 
		void curveTo(const Vec2f& v);
		void end(int pathEndState = CLOSE);

		void fill(const Col4f& col);
		void fill(float r, float g, float b, float a);
		void fill(float r, float g, float b);
		void fill(const std::vector<Col4f>& cols);
		void stroke(const Col4f& col);
		void stroke(float r, float g, float b, float a);
		void stroke(float r, float g, float b);
		void stroke(const std::vector<Col4f>& cols);
		void noFill();
		void noStroke();

		void display();

		void setBaseApp(ProtoBaseApp* baseApp);
	};
}

#endif //PROTO_PATH2_H
