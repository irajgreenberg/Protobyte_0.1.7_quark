/*!  \brief  ProtoTexture.h: 2D texture class with w,h fields
 ProtoTexture.h
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
 Inspiration and assistance from: http://subversion.assembla.com/svn/184/src/LoadImage.cpp

 // FreeImage implementaiont from:
 // Singleton Texture Manager class
 // Written by Ben English
 // benjamin.english@oit.edu

 \sa NO LINK
 */

#ifndef TEXTURE_H
#define	TEXTURE_H

// #if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
//#define GLEW_STATIC
//#include <GL/glew.h>
//#else
//#include <OpenGL/gl.h>
//#endif

 #if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
 #include "glad/glad.h"
 #endif


//thanks http://stackoverflow.com/questions/16186300/linking-freeimage-as-a-static-library-in-vs2010
//#define  FREEIMAGE_LIB
#include "FreeImage.h"
//#include<SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "ProtoVector3.h"
#include <stdio.h> // for File input

namespace ijg {

    // NOTE to do: add multiple maps to each texture: diffuse, bump and gloss at least.
	
	class ProtoTexture;
	typedef ProtoTexture Texture;
	
	class ProtoTexture {

		friend class ProtoGeom2;
		friend class ProtoGeom3;
	private:
		// used by ProtoGeom3 only
		/*enum TextureMapType{
			DIFFUSE_MAP,
			BUMP_MAP,
			NORMAL_MAP,
			REFLECTION_MAP,
			REFRACTION_MAP,
			SPECULAR_MAP
		};*/

		//TextureMapType textureMapType;

		std::string textureMapImage;
		GLenum image_format;
		GLint internal_format;
		GLint level;
		GLint border;

		GLuint w;
		GLuint h;
		bool isWrap;
		GLuint textureID;
		float bumpIntensity;

		bool init();

		//FIBITMAP* normalMap;

		// calculate normal map from height map
		//bool createNormalMap();

		//static bool createNormalMap(const std::string& textureURL, GLuint textureID); 
	
	public:

		// used by ProtoGeom3 only
		enum TextureMapType{
			DIFFUSE_MAP,
			BUMP_MAP,
			NORMAL_MAP,
			REFLECTION_MAP,
			REFRACTION_MAP,
			SPECULAR_MAP
		};

		TextureMapType textureMapType;
        
        friend std::ostream& operator<<(std::ostream& output, const ProtoTexture& texture);

        ProtoTexture(); // default

		// overloaded: assumption: image_format:RGB, internal_Forma:RGB, level:0, border0
		ProtoTexture(const std::string& textureMapImage, TextureMapType textureMapType, GLenum image_format = GL_RGB, GLint internal_format = GL_RGB, GLint level = 0, GLint border = 0, float bumpIntensity = 0.35f); // initialized
    
//        ProtoTexture(const std::string& textureURL, GLuint w, GLuint h, bool isWrap);
//        ProtoTexture(unsigned char*& data, GLuint w, GLuint h, bool isWrap);
//        ProtoTexture(std::vector<unsigned char>& data, GLuint w, GLuint h, bool isWrap);
//        ProtoTexture(const int* packedData32, GLuint w, GLuint h, bool isWrap);

        // getters/setters
        void setH(GLuint h);
        GLuint getH() const;
        void setW(GLuint w);
        GLuint getW() const;
        //void setTextureURL(std::string textureURL);
        //std::string getTextureURL() const;
        void setTextureID(GLuint textureID);
        GLuint getTextureID() const;
		




   
    };

    inline void ProtoTexture::setH(GLuint h) {
        this->h = h;
    }

    inline GLuint ProtoTexture::getH() const {
        return h;
    }

    inline void ProtoTexture::setW(GLuint w) {
        this->w = w;
    }

    inline GLuint ProtoTexture::getW() const {
        return w;
    }

    //inline void ProtoTexture::setTextureURL(std::string textureURL) {
    //    this->textureURL = textureURL;
    //}

    //inline std::string ProtoTexture::getTextureURL() const {
    //    return textureURL;
    //}

    inline void ProtoTexture::setTextureID(GLuint textureID) {
        this->textureID = textureID;
    }

    inline GLuint ProtoTexture::getTextureID() const {
        return textureID;
    }

}

#endif	// TEXTURE_H

