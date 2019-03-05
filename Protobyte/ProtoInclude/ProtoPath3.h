/*!  \brief  ProtoPath3.h: General path (open or closed) with no guarantee of convexity
Used interanlly by procedural convenience drawing functions.

ProtoPath3.h
Protobyte Library v02

Created by Ira on 9/10/14.
Copyright (c) 2013 Ira Greenberg. All rights reserved.

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

#ifndef PROTO_PATH_H
#define	PROTO_PATH_H

#include "ProtoGeom3.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoPath3;
	typedef ProtoPath3 Path3;

	class ProtoPath3 {
	protected:
		Col4f col4;
			
			
		// called from cstr's
		virtual void init();

		// primitive pipeline CPU - > GPU
		// Utilizes VBO's/VAO

		virtual void calcPrimitives();

		//shader loc
		GLuint colorLoc_U;

		// composite guts
		std::vector<ProtoVertex3> verts;
		std::vector< ProtoTuple3<int> > inds;

		//primitive guts
		std::vector<float> vertPrims;
		std::vector<unsigned int> indPrims;
		std::vector<float> colorPrims;

		// currently interleaving all attributes
		// Note: may want to use multiple VBOs and a VAO instead
		//static const int STRIDE = 7;
		enum { STRIDE = 7 };
		std::vector<float> interleavedPrims;

		// Buffer control
		// VAO
		GLuint vaoID;
		// VBO stuff
		GLuint vboID, indexVboID;

		//shared memory pointer for dynamic VBO's
		float* sharedMemPointer;

		// Utility for extension support
		// ProtoGLInfo glInfo;


		// update buffers for GPU - need to do for all relevant fields
		//void updateColorBuffer();

		/*std::string createFullShaderURL(const std::string& shaderName);*/

		void clearVectors();// called from init to reset all vectors.

	

public:
		friend std::ostream& operator<<(std::ostream& out, const ProtoPath3& Path);

		ProtoPath3();

		ProtoPath3(const Col4f& col4, const std::vector<Vec3f>& pathVecs);

		enum RenderMode {
			POINTS, // begin at 0
			WIREFRAME
		};
		
		// vertex arrays are implemented by default
		virtual void display(RenderMode render = WIREFRAME, float pointSize = .5f);


	private:
		std::vector<Vec3f> pathVecs;
	};

}

#endif	/* PROTO_PATH_H */

