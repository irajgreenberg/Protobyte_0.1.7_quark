/*!  \brief  ProtoShader.cpp: class for managing shaders
 ProtoShader.cpp
 Protobyte Library v02
 
 Created by Ira on 7/23/13.
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


#include "ProtoShader.h"
#include <string.h>
#include <iostream>

using namespace ijg;


// initialize static shaderID
GLuint ProtoShader::shader_id_2 = 0;

ProtoShader::ProtoShader() {
	//trace("In Shader default CSTR");
}

ProtoShader::ProtoShader(const std::string& vShader, const std::string& fShader):
vShader(vShader), fShader(fShader){
	//trace("In Shader overloaded CSTR");
	init();
}

ProtoShader::ProtoShader(const ProtoShader& shdr){
	this->vShader = shdr.vShader;
	this->fShader = shdr.fShader;
	this->shader_vp = shdr.shader_vp;
	this->shader_fp = shdr.shader_fp;
	init();
}

ProtoShader& ProtoShader::operator=(const ProtoShader& shdr){
	if (this != &shdr){
		glDetachShader(shader_id, shader_fp);
		glDetachShader(shader_id, shader_vp);

		glDeleteShader(shader_fp);
		glDeleteShader(shader_vp);
		glDeleteProgram(shader_id);

		this->vShader = shdr.vShader;
		this->fShader = shdr.fShader;
		this->shader_vp = shdr.shader_vp;
		this->shader_fp = shdr.shader_fp;
		init();
	}
	return *this;
}

void ProtoShader::init() {
    std::string url = ProtoUtility::getBuildPath();
    
  // std::cout << "path to shaders  url = ," << url << std::endl;

	std::string vShaderURL;
	std::string fShaderURL;

#if defined(_WIN32)
	// use protobyte resources instead of project resources
	vShaderURL = url + "\\..\\..\\..\\Resources\\shaders\\"+vShader;
	fShaderURL = url + "\\..\\..\\..\\Resources\\shaders\\"+fShader;
	//vShaderURL = url + "\\..\\..\\Resources\\shaders\\" + vShader;
	//fShaderURL = url + "\\..\\..\\Resources\\shaders\\" + fShader;
	//trace("vShaderURL =", vShaderURL);
#else
	vShaderURL = url + "/resources/shaders/" + vShader;
	fShaderURL = url + "/resources/shaders/" + fShader;
#endif
    

    std::string vShaderCodeStr = ProtoUtility::load(vShaderURL);
	std::string fShaderCodeStr = ProtoUtility::load(fShaderURL);
    
        shader_vp = 0;
        shader_fp = 0;
        shader_id = 0;
		
    
    const GLchar* vShaderCode = vShaderCodeStr.c_str();
    const GLchar* fShaderCode = fShaderCodeStr.c_str();
    
    
    if (vShaderCode == NULL || fShaderCode == NULL) {
        std::cerr << "Either vertex shader or fragment shader file not found." << std::endl;
        return;
    }
    
    shader_vp = glCreateShader(GL_VERTEX_SHADER);
    if(0==shader_vp){
        std::cerr << "Error creating vertex shader"<< std::endl;
        return;
    }
    
    shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
    if(0==shader_fp){
        std::cerr << "Error creating fragment shader"<< std::endl;
        return;
    }
    
    glShaderSource(shader_vp, 1, &vShaderCode, NULL);
    glShaderSource(shader_fp, 1, &fShaderCode, NULL);
    
    
    glCompileShader(shader_vp);
    glCompileShader(shader_fp);
    
    //Check shader for errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv( shader_vp, GL_COMPILE_STATUS, &shaderCompiled );
    if( shaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile Vertex shader %d!\n\nSource:\n%s\n", shader_vp, vShaderCode );
        //printShaderLog( shader_vp );
        glDeleteShader( shader_vp );
        shader_vp = 0;
    }
    
    glGetShaderiv( shader_fp, GL_COMPILE_STATUS, &shaderCompiled );
    if( shaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile fragment shader %d!\n\nSource:\n%s\n", shader_fp, fShaderCode );
        //printShaderLog( shader_vp );
        glDeleteShader( shader_fp );
        shader_fp = 0;
    }
    
    
    shader_id = glCreateProgram();
	ProtoShader::shader_id_2 = shader_id; // capture id value
    
    glAttachShader(shader_id, shader_vp);
    glAttachShader(shader_id, shader_fp);
    
    glLinkProgram(shader_id);
    
    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(shader_id, GL_LINK_STATUS, &programSuccess );
 //   std::cout << "programSuccess = " << programSuccess << std::endl;
    if( programSuccess != GL_TRUE )
    {
        printf( "Error linking program %d!\n", shader_id);
        printLog(shader_id);
        glDeleteProgram(shader_id);
        shader_id = 0;
    }
    //glUseProgram(shader_id);
}

ProtoShader::~ProtoShader() {
	// clean up attribute and uniform variable locations
	if (attribLocs.size() > 0){
		attribLocs.clear();
	}
	if (uniformLocs.size() > 0){
		uniformLocs.clear();
	}
	glDetachShader(shader_id, shader_fp);
    glDetachShader(shader_id, shader_vp);
    
    glDeleteShader(shader_fp);
    glDeleteShader(shader_vp);
    glDeleteProgram(shader_id);
}

void ProtoShader::printLog(GLuint program){
    int maxLength=0;
    int length=0;
    glGetProgramiv(program,GL_INFO_LOG_LENGTH,&maxLength);
    char* log = new char[maxLength];
    glGetProgramInfoLog(program,maxLength,&length,log);
    std::cout << "program log: " << log << std::endl;
}

void ProtoShader::addAttribute(std::string name){
}
void ProtoShader::addUniform(std::string name){
}

