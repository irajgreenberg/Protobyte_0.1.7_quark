/*!  \brief  ProtoShader.h: class for managing shaders
ProtoShader.h
Protobyte Library v02

Created by Ira on 7/23/13.
Revised 12/5/2015
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
This class is templated to allow for varied single collection types
This class is part of the group common (update)
\sa NO LINK
*/

#ifndef PROTO_SHADER_H
#define PROTO_SHADER_H

//#if defined(_WIN32) || defined(__linux__)
//#define GLEW_STATIC
//#include <GL/glew.h>
//#else
//#include <OpenGL/gl.h>
//#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include "glad/glad.h"
#endif

#include <stdlib.h>
#include <string>
#include "ProtoUtility.h"

#include <sstream>
#include <fstream>

// include GLM
//#include "glm/gtc/type_ptr.hpp" // matrix copying
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtx/transform2.hpp"


namespace ijg {



	class ProtoShader {
	public:
		ProtoShader();
		ProtoShader(const std::string& vShader, const std::string& fShader);
		ProtoShader(const ProtoShader& shdr);
		ProtoShader& operator=(const ProtoShader& shdr);
		~ProtoShader();

		void init();

		void bind();
		void unbind();

		GLuint getID();
		GLuint shader_id;

		// encapsulate passing shader loacations 
		// for attribute and uniform vars
		void addAttribute(std::string name);
		void addUniform(std::string name);

		const GLuint static getID_2();
		static void setVertexShader(const std::string& vShaderURL);
		static void setFragmentShader(const std::string& fShaderURL);
		static void setGeometryShader(const std::string& gShaderURL);
		void setShaders(const std::string& vShaderURL, const std::string& fShaderURL);

		/******/#define setVertShader setVertexShader;
		/******/#define setFragShader setFragmentShader;
		/******/#define setGeomShader setGeometryShader;

		bool   isLinked();

		void   bindAttribLocation(GLuint location, const char * name);
		void   bindFragDataLocation(GLuint location, const char * name);


		// from Opengl 4.0 Cookbook
		//void   setUniform(const char *name, const glm::vec3 & v);
		//void   setUniform(const char *name, const glm::vec4 & v);
		//void   setUniform(const char *name, const glm::mat4 & m);
		//void   setUniform(const char *name, const glm::mat3 & m);
		//void   setUniform(const char *name, float val);
		//void   setUniform(const char *name, int val);
		//void   setUniform(const char *name, bool val);

		void   printActiveUniforms();
		void   printActiveAttribs();


	private:
		// must initialize these before using!!!
		std::string vShader, fShader;
		GLuint shader_vp;
		GLuint shader_fp;
		GLuint shader_gp;
		void printLog(GLuint program);

		// vector for attribute and uniform locations
		std::vector<GLuint> attribLocs, uniformLocs;

		// used for access in Geom3 class
		// Shader object is essentily a singleton, so the id will remain unchanged throughout program
		static GLuint shader_id_2;

	};

	inline GLuint ProtoShader::getID() {
		return shader_id;
	}

	inline const GLuint ProtoShader::getID_2() {
		return shader_id_2;
	}

	inline void ProtoShader::bind() {
		//trace("in ProtoShader::bind()");
		glUseProgram(shader_id);
	}

	inline void ProtoShader::unbind() {
		//trace("in ProtoShader::unbind()");
		glUseProgram(0);
	}

	inline void ProtoShader::setShaders(const std::string& vShaderURL, const std::string& fShaderURL){
		vShader = vShaderURL;
		fShader = fShaderURL;
		init();
	}

}


#endif //PROTO_SHADER_H