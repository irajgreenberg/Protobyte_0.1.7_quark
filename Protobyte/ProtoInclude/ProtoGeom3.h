/*!  \brief  ProtoGeom3.h: Abstact Base Geometry class
 ProtoGeom3.h
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
 This class is part of the group common (update)
 \sa NO LINK
 */

#ifndef PROTO_GEOM3_H
#define PROTO_GEOM3_H

// for image path to texture
#if defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "ProtoShader.h" // includes GL 4
#include "ProtoVector2.h"
#include "ProtoVector3.h"
#include "ProtoVector4.h"
#include "ProtoFace3.h"
#include "ProtoTuple3.h"
#include "ProtoDimension2.h"
#include "ProtoDimension3.h"
#include "ProtoColor4.h"
#include "ProtoTexture.h"
#include "ProtoContext.h"
//#include "ProtoGLInfo.h"
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "ProtoShape3.h"
#include "ProtoGeomSet.h"



namespace ijg {


    // for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))
    
    class ProtoGeom3: public ProtoShape3{
        
        friend class ProtoVertex3;
    
    protected:
       
		std::shared_ptr<ProtoContext> ctx;
		// called from cstr's
		virtual void init();
		virtual void update();
        
		// primitive pipeline CPU - > GPU
		// Utilizes VBO's/VAO
		virtual void calcVerts() = 0;
        virtual void calcInds() = 0;
        virtual void calcFaces(); // probably not necessary to override
        virtual void calcVertexNorms();
        virtual void calcPrimitives();

		// textures
		ProtoTexture diffuseMapTexture, bumpMapTexture, reflectionMapTexture, refractionMapTexture, specularMapTexture;

		// by default, diffusion Map Texture - set at construction
		std::string diffuseMapImage, bumpMapImage, reflectionMapImage, refractionMapImage, specularMapImage;

		GLint diffuseMapLoc, bumpMapLoc;
		std::vector<std::string> diffuseTextureImageURLs; // multi-texturing -> not sure I want this anymore
		
		//float textureScale;
		Vec2f textureScale;
		
		// create Textures - accessed in Fragment Shader
		virtual void createDiffuseMapTexture(const std::string& diffuseMapImage); // loc 0 (default)
		//virtual void createBumpMapTexture(const std::string& bumpMapImage); // loc 1 // dynamically build normal map
		virtual void createBumpMapTexture(const std::string& bumpMapImage, float intensity); // loc 1 // dynamically build normal map
		virtual void createReflectionMapTexture(const std::string& reflectioneMapImage); // loc 2
		virtual void createRefractionMapTexture(const std::string& refractionMapImage); // loc 3
		virtual void createSpecularMapTexture(const std::string& specularMapImage); // loc 4

        
       // std::vector<Vec2f> uvs;
        
        // composite guts
        std::vector<ProtoVertex3> verts;
        //std::vector<ProtoVertex3*> verts;
       // std::vector<ProtoFace3> faces; //experiment making this public
        std::vector< ProtoTuple3<int> > inds;

        //primitive guts
        std::vector<float> vertPrims;
        std::vector<unsigned int> indPrims;
        std::vector<float> normPrims;
		std::vector<float> tangentPrims; // added 4/16/14
        std::vector<float> colorPrims;
        std::vector<float> texturePrims;

		// currently interleaving all attributes
		// Note: may want to use multiple VBOs and a VAO instead
		//static const int STRIDE = 15;
		enum { STRIDE = 15 };
        std::vector<float> interleavedPrims;
        
        // Display List var
        GLuint displayListIndex;
        
		// Buffer control
		// VAO
		GLuint vaoID;
		// VBO stuff
        GLuint vboID, indexVboID;
        
        //shared memory pointer for dynamic VBO's
        float* sharedMemPointer;
        
        // Utility for extension support
        // ProtoGLInfo glInfo;
        
        std::vector<ProtoGeomSet> geomSets;
        
        // material properties
		struct Material {
			Col4f diffuse;
			Col4f ambient;
			Col4f specular;
			Col4f emissive;
			float shininess;

			// cstrs
			Material(){}
			Material(const Col4f& diffuse, const Col4f& ambient, const Col4f& specular, const Col4f& emissive, float shininess):
				diffuse(diffuse), ambient(ambient), specular(specular), emissive(emissive), shininess(shininess){}
		};

		Material materials;

		// material uniform locations 
		GLuint diffuse_loc_U, ambient_loc_U, specular_loc_U, emissive_loc_U, shininess_loc_U;
		
		// default lighting set on
		/**
		* Handle to shader to disable/enable lighting for curve path/curve vertices rendering
		*/
		//GLuint lightRenderingFactors_U;
        
        
        bool isTextureEnabled;
		void updateBuffer(); // currently used for texture scale only.
        void updateTextureBuffer(); // new one

		// update buffers for GPU - need to do for all relevant fields
		void updateColorBuffer();

		/*std::string createFullShaderURL(const std::string& shaderName);*/

		void clearVectors();// called from init to reset all vectors.

		// set Shader
		const ProtoShader* shader;
		void setShader(const ProtoShader* shader);
        
        
    public:
//     
		// experiment making this public
		std::vector<float> packedFaces;
		std::vector<ProtoFace3> faces;
		std::vector<ProtoFace3> faces2;
		
//		enum renderMode {
//            POINTS,
//            WIREFRAME, // begin at 0
//            SURFACE
//        };
        
        ProtoGeom3();
        
		ProtoGeom3(const Vec3f& pos); 
		
		ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
                   const ProtoColor4f col4);
        
        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
                   const std::vector< ProtoColor4f > col4s);
        
        
        // with textureImageURL
		//ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& diffuseTextureImage);
        
		//ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const std::vector< ProtoColor4f > col4s, const std::string& diffuseTextureImage);
        
		ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& diffuseTextureImage, const Vec2f& textureScale = Vec2f(1, 1));

        ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
			const std::vector< ProtoColor4f > col4s, const std::string& diffuseTextureImage, const Vec2f& textureScale = Vec2f(1, 1));

		// multi-texturing
		ProtoGeom3(const Dim3f& size, const Col4f& col4, const std::vector<std::string>& textureImageURLs, const Vec2f& textureScale = Vec2f(1, 1));
		ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f& size, const Col4f& col4, const std::vector<std::string>& textureImageURLs, const Vec2f& textureScale = Vec2f(1, 1));
        
        
        
        virtual ~ProtoGeom3();
        
        virtual void move(const Vec3f& v);
        virtual void rotate(const Vec3f& r);
        virtual void scale(const ProtoDimension3f& s);
        
        virtual void transform(const ProtoMatrix4f& mat4);
        
        
        // vertex arrays are implemented by default
        virtual void display(RenderMode render = SURFACE, float pointSize = .5f);

		virtual void displayTBN();
        
        // setters/getters
       // overload Shape3 methods
		virtual void setPosition(const Vec3f& pos);
        virtual void setRotation(const Vec3f& rot);
        virtual void setSize(const ProtoDimension3f size);
        virtual void setColor(const ProtoColor4f col4);
        
        virtual Vec3f& getPosition();
        virtual Vec3f& getRotation();
        virtual ProtoDimension3f& getSize();
        virtual ProtoColor4f& getColor();
        
        // a bit dangerous to return references, so be careful
        // justification, you got no 3d if you delete this stuff
        
        std::vector<ProtoFace3>& getFaces();
        std::vector<ProtoVertex3>& getVertices();
        std::vector<float>& getInterleavedPrims();
        
        
        virtual void sortFaces();
        
		void setTextureScale(const Vec2f& textureScale);
		Vec2f getTextureScale() const;
        
		// public interface for setting maps
		void setBumpMap(const std::string& bumpMapImage, float intenisty = 0.25f);
		void createBumpMap(const std::string& bumpMapImage, float intensity = 0.3f);
		void loadBumpMapTexture(const std::string& bumpMapImage); // loc 1 // pre-made normal map
		void setDiffuseMap(const std::string& diffuseMapImage);
		void setReflectionMap(const std::string& reflectionMapImage);
		void setRefractionMap(const std::string& refractionMapImage);
		void setSpecularMap(const std::string& specularMapImage);

		// normal map - created based on texture ---> probably lose this
		void enableNormalMap(float depth = .5f);
		void disableNormalMap();
        
        // stl exporter
        // void exportSTL();
		std::vector<Tup4v> getGeomData();
        
        // required by ProtobteRenderer
        GLuint getVboID() const;
        GLuint getIndexVboID() const;
        int getIndicesSize() const;


		// set/get materials
		void setDiffuseMaterial(const Col4f& diffuseMaterial);
		void setAmbientMaterial(const Col4f& ambientMaterial);
		void setSpecularMaterial(const Col4f& specularMaterial);
		void setEmissiveMaterial(const Col4f& emissiveMaterial);
		void setShininess(float shininess);

		const Col4f& getDiffuseMaterial() const;
		const Col4f& getAmbientMaterial() const;
		const Col4f& getSpecularMaterial() const;
		const Col4f& getEmissiveMaterial() const;
		float getShininess();

		void setMaterials(const Material& materials);
		const Material& getMaterials() const;
		// END Materials
        
        // ensure unique id for each texture per geom obj - this needs to be rethought eventually.
        static GLuint textureID;
       // ProtoTexture getTexture()const;
        void textureOn();
        void textureOff();
        
        
    };
    
    
    // setters/getters
    inline void ProtoGeom3::setPosition(const Vec3f& pos) {
        this->pos = pos;
		init();
    }
    
    inline void ProtoGeom3::setRotation(const Vec3f& rot) {
        this->rot = rot;
		init();
    }
    
    inline void ProtoGeom3::setSize(const ProtoDimension3f size) {
        this->size = size;
		init();
    }
    
    inline void ProtoGeom3::setColor(const ProtoColor4f col4) {
        this->col4 = col4;
		if (col4s.size() > 0){
			for (int i = 0; i < col4s.size(); ++i){
				col4s.at(i) = col4;
			}
		}
		// need to update primitives for GPU
		updateColorBuffer();
    }
    
    inline Vec3f& ProtoGeom3::getPosition() {
        return pos;
    }
    
    inline Vec3f& ProtoGeom3::getRotation() {
        return rot;
    }
    
    inline ProtoDimension3f& ProtoGeom3::getSize() {
        return size;
    }
    
    inline ProtoColor4f& ProtoGeom3::getColor() {
        return col4;
    }
    
    inline std::vector<ProtoFace3>& ProtoGeom3::getFaces() {
        return faces;
    }
    
    inline std::vector<ProtoVertex3>& ProtoGeom3::getVertices() {
        return verts;
    }
    
    inline  std::vector<float>& ProtoGeom3::getInterleavedPrims(){
        return interleavedPrims;
    }
    
	inline void ProtoGeom3::setTextureScale(const Vec2f& textureScale) {
        this->textureScale = textureScale;
		updateTextureBuffer();
    }
    
    inline Vec2f ProtoGeom3::getTextureScale() const {
        return textureScale;
    }
    
    inline GLuint ProtoGeom3::getVboID() const {
        return vboID;
    }
    
    inline GLuint ProtoGeom3::getIndexVboID() const {
        return indexVboID;
    }
    
    inline int ProtoGeom3::getIndicesSize() const{
        return static_cast<int>(inds.size());
    }
    
    // materials
	inline void ProtoGeom3::setDiffuseMaterial(const Col4f& diffuseMaterial){
		materials.diffuse = diffuseMaterial;
		
		diffuse_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMaterial");
		//init();
	}

	inline void ProtoGeom3::setAmbientMaterial(const Col4f& ambientMaterial){
		materials.ambient = ambientMaterial;
		
		ambient_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "ambientMaterial");
		//init();
	}
	inline void ProtoGeom3::setSpecularMaterial(const Col4f& specularMaterial){
		materials.specular = specularMaterial;

		specular_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "specularMaterial");
		//init();
	}

	inline void ProtoGeom3::setEmissiveMaterial(const Col4f& emissiveMaterial){
		materials.emissive = emissiveMaterial;

		emissive_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "emissiveMaterial");
		//init();
	}

	inline void ProtoGeom3::setShininess(float shininess){
		materials.shininess = shininess;
		//init();
	}

	inline const Col4f& ProtoGeom3::getDiffuseMaterial() const{
		return materials.diffuse;
	}
	inline const Col4f& ProtoGeom3::getAmbientMaterial() const{
		return materials.ambient;
	}
	inline const Col4f& ProtoGeom3::getSpecularMaterial() const{
		return materials.specular;
	}
	inline const Col4f& ProtoGeom3::getEmissiveMaterial() const{
		return materials.emissive;
	}
	inline float ProtoGeom3::getShininess(){
		return materials.shininess;
	}

	inline void ProtoGeom3::setMaterials(const Material& materials){
		this->materials = materials;
	}
	inline const ProtoGeom3::Material& ProtoGeom3::getMaterials() const{
		return materials;
	}

    
}

#define Geom3 ProtoGeom3
#endif /* defined(PROTO_GEOM3_H) */
