#ifndef _PROTO_CONTEXT_H_
#define _PROTO_CONTEXT_H_

#if defined (_WIN32) || defined(_WIN64)
#define GLEW_STATIC // link to glew32s instead of including dll
#include <GL/glew.h>
#include <Windows.h>
#include <stdio.h>
#endif


// include GLM
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"

#include "ProtoColor4.h"
#include "ProtoVector3.h"
#include "ProtoVector4.h"

// for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))

#include <iostream>
#include <stack>

// singleton pattern

namespace ijg {

	class ProtoContext {

	private:
		static ProtoContext* ctx;

		// disallow direct instantiation
		ProtoContext();

	public:

		static ProtoContext* getContext();

		/***********************************
		*           GLSL UNIFORMS          *
		***********************************/
		// using initials ONLY for matrices
		// Uniform Camera Matrices
		glm::mat4 M;
		//glm::mat4 V, MV, P, MVP;

		// Uniform Transformation Matrices
		glm::mat4 T, R, S;

		// Uniform Shadow Map Matrices
		//glm::mat4 L_V, L_MV, L_P, L_B, L_BP, L_MVBP;

		//glm::mat4 L_MVS[8];
		//glm::mat4 shadM[8];

		// Uniform Normal Matrix
		//glm::mat3 N;

		// flags for shader locations
		GLuint M_U;
		//GLuint V_U, MV_U, P_U, MVP_U, N_U;
		//GLuint T_U, R_U, S_U;
		//GLuint L_MVBP_U; // only for Light perspective
		//GLuint shaderPassFlag_U;

		//// Uniform Shadow Map
		//GLuint shadowMap_U;

		//// Uniform Lighting factors
		//// enable/disable lighting factors for 2D rendering
		//Vec4f ltRenderingFactors;
		//GLuint lightRenderingFactors_U;

		//// color flags/fields for immediate mode drawing
		//bool isStroke, isFill;
		//Col4f fillColor, strokeColor;
		//float lineWidth;


		//// shadow mapping texture id's
		//GLuint shadowBufferID, shadowTextureID;

		//// flag for shadowing
		//bool areShadowsEnabled;

		//const int SHADOWMAP_WIDTH = 4096, SHADOWMAP_HEIGHT = 4096;

		std::stack <glm::mat4> matrixStack;



		// Uniform Lighting location vars
		//struct Light_U {
		//	GLuint position;
		//	GLuint intensity;
		//	GLuint diffuse;
		//	GLuint ambient;
		//	GLuint specular;;
		//};
		//Light_U lights_U[8];

		//GLuint globalAmbient_U;



		// OSC obj 
		//ProtoOSC listener;


		/************************************
		**********   FUNCTIONS   ***********
		***********************************/
		// switched from pure virtual above to enable thread to call member functions
		/*	virtual void init(){}
		virtual void run(){}*/

		//virtual bool ProtoBaseApp::createShadowMap();

		// frame values
		//void setFrameRate(float frameRate);
		//float getFrameRate() const;
		////setFrameCount() moved to private - bw
		////void setFrameCount(float frameCount);
		//int getFrameCount() const;


		//bool areShadowsOn;
		//void setShadowsOn(bool areShadowsOn);
		//void shadowsOn();
		//void shadowOff();

		//// create traditional interface for GPU controlled transforms
		void translate(float tx, float ty, float tz);
		void translate(const Vec3f& tXYZ);
		void rotate(float angle, float axisX, float axisY, float axisZ);
		void rotate(float angle, const Vec3f& rXYZ);
		void scale(float s);
		void scale(float sx, float sy, float sz);
		void scale(const Vec3f& sXYZ);
		//implements transform matrix stack
		void push();
		void pop();
		void concat();

		// WORLD
		//void printMatrix(Matrix m = MODEL_VIEW);
	};


}
#endif // _PROTO_CONTEXT_H_