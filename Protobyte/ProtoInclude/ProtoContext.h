/*!  \brief  ProtoContext.h: encapsulates static tranformation matrix/functions
ProtoContext.h
Protobyte Library

Copyright (c) 2015 Ira Greenberg. All rights reserved.

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

#ifndef __PROTO_CONTEXT_H__
#define __PROTO_CONTEXT_H__

// OpenGL drivers
//#if defined (_WIN32) || defined(_WIN64)
//#define GLEW_STATIC // link to glew32s instead of including dll
//#include <GL/glew.h>
//#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include "glad/glad.h"
#endif

#include <iostream>
#include <stack>
#include <memory>

#include "ProtoDimension3.h"
#include "ProtoVector3.h"
#include "ProtoVector4.h"
#include "ProtoShader.h"
#include "ProtoLight.h"
#include "ProtoColor3.h"

// include GLM
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"




namespace ijg {

	class ProtoContext {

	private:

		static float width;
		static float height;
		ProtoContext() {} // private cstr for singleton pattern
		static std::shared_ptr<ProtoContext> ctx;

		std::stack <glm::mat4> matrixStack;

		//Lighting
		GLint glLights[8];
		enum Light {
			LIGHT_0,
			LIGHT_1,
			LIGHT_2,
			LIGHT_3,
			LIGHT_4,
			LIGHT_5,
			LIGHT_6,
			LIGHT_7
		};
		std::vector<ProtoLight> lights;

		// perspective view 
		float viewAngle{ float(65.0f*PI/180.0f) };
		float aspect{ 0.0f };
		float nearDist{ .1f };
		float farDist{ 1500.0f };

		// look at
		Vec3 eyePos, sceneCenter, axis;

		// orthogonal view 
		float left, right, bottom, top;


		enum ProjectionType {
			PERSPECTIVE,
			ORTHOGONAL
		};
		void setProjection(ProjectionType projType = PERSPECTIVE);


	public:
		static const std::shared_ptr<ProtoContext> getContext(float width = 1024.0f, float height = 768.0f);
		void init();

		/*** Geometry Matrices ***/
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 modelView;
		glm::mat4 projection;
		glm::mat4 modelViewProjection;
		glm::mat3 normal;

		// Geometry Matrix set
		void setModel(const glm::mat4& model);
		void setView(const glm::mat4& view);
		void setProjection(const glm::mat4& projection);
		void concatModelView();
		void concatModelViewProjection();
		//void createNormalMatrix();
		
		// Geometry Matrix get
		const glm::mat4& getModel();
		const glm::mat4& getView();
		const glm::mat4& getModelView();
		const glm::mat4& getProjection();
		const glm::mat4& getModelViewProjection();
		const glm::mat3& getNormal();

		// Print info about matrices
		void printModelMatrix();
		void printViewMatrix();
		void printProjectionMatrix();
		void printModelViewMatrix();
		void printModelViewProjectionMatrix();

		/*** Shadow Map Matrices ***/
		glm::mat4 lightView; // Light View
		glm::mat4 lightModelView; // Light ModelView
		glm::mat4 lightProjection; // Light Projection
		glm::mat4 lightModelViewProjection; // Light MVP
		glm::mat4 lightBias; // Light Bias
		glm::mat4 lightBiasProjection; // Light BiasProjection (depth bias)
		glm::mat4 lightModelViewBiasProjection;// Light ModelViewBiasProjection
		glm::mat4 shadow;
		/*** Matrices (3x3) ***/
		// Normal

		// for shadow detail/sharpness
		GLuint shadowSharpness_U;
		void setShadowSharpness(int shadowSharpnessWidth, int shadowSharpnessHeight);
		

		// flags for shader locations
		GLuint globalAmbient_U;
		GLuint model_U, view_U, modelView_U, projection_U, modelViewProjection_U, normal_U;
		
		GLuint getModel_U();
		GLuint getView_U();
		GLuint getModelView_U();
		GLuint getProjection_U();
		GLuint getModelViewProjection_U();
		GLuint getNormal_U();
	
		GLuint LV_U, LP_U, LB_U; // Need to do model view concatenation in shader
		GLuint L_MVBP_U, lightModelViewBiasProjection_U; // only for Light perspective
		GLuint shaderPassFlag_U;
		const GLuint& getShaderPassFlag_U();
		void setShaderPassFlag_U(const GLuint& shaderPassFlag_U);

		// Uniform Shadow Map
		GLuint shadowMap_U;
		const GLuint& getShadowMap_U();
		void setShadowMap_U(const GLuint& shadowMap_U);

		// Uniform Lighting factors
		// enable/disable lighting factors for 2D rendering
		Vec4f lightRenderingFactors;
		GLuint lightRenderingFactors_U;
		const Vec4f& getLightRenderingFactors();
		void setLightRenderingFactors(const Vec4f& lightRenderingFactors);
		const GLuint& getLightRenderingFactors_U();
		void setLightRenderingFactors_U(const GLuint& lightRenderingFactors_U);

		void updateLightViewMatrices();

		// shadow mapping texture id's
		GLuint shadowBuffer_U, shadowTexture_U;
		void setShadowBuffer_U(const GLuint& shadowBuffer_U);
		//const GLuint& getShadowBuffer_U();
		GLuint& getShadowBuffer_U();
		void setShadowTexture_U(const GLuint& shadowTexture_U);
		GLuint& getShadowTexture_U();

		// flag for shadowing
		bool areShadowsEnabled;

		//const int SHADOWMAP_WIDTH = 4096, SHADOWMAP_HEIGHT = 4096;

		bool areShadowsOn;
		void setShadowsOn(bool areShadowsOn);
		void shadowsOn();
		void shadowOff();

		Col3f globalAmbient; // make private

		
		// Light Matrix Functions (for shadow map)
		void setLightView(const glm::mat4& lightView);
		void setLightBias(const glm::mat4& lightBias);
		void setLightProjection(const glm::mat4& lightProjection);
		//void concatLightModelView(); //L_MV
		//void concatLightModelViewProjection(); // L_MVP
		//void concatenateDepthBiasProjectionMatrix();
		//void concatLightModelViewBiasProjection();

		//void concatenateShadowMatrix();
		const glm::mat4& getShadow();

		const glm::mat4& getLightView();
		const glm::mat4& getLightModelView();
		const glm::mat4& getLightProjection();
		const glm::mat4& getLightBias();
		const glm::mat4& getLightModelViewBiasProjection();



		// lighting
		void setGlobalAmbient(const Col3f& globalAmbient);
		const Col3f& getGlobalAmbient();
		const GLuint& getGlobalAmbient_U();
		void setLight(int index, const Vec3& pos, const Vec3& intensity);
		const ProtoLight& getLight(int index);

		// Uniform Lighting location vars
		struct Light_U {
			GLuint position;
			GLuint intensity;
			GLuint diffuse;
			GLuint ambient;
			GLuint specular;;
		};

		Light_U lights_U[8];


		const Light_U& getLight_U(int index);
		const GLuint getLightModelViewBiasProjection_U();


		// look at
		void setSceneCenter(const Vec3& axis);
		void setEyePosition(const Vec3& eyePos);
		void setUpAxis(const Vec3& axis);

		// perspective view
		void setViewAngle(float viewAngle);
		void setAspect(float aspect);
		void setNearDist(float nearDist);
		void setFarDist(float farDist);

		// orthoonal view
		void setLeft(float left);
		void setRight(float right);
		void setBottom(float bottom);
		void setTop(float top);

		// transform functions
		void translate(float tx, float ty, float tz);
		void translate(const Vec3f& tXYZ);
		void rotate(float angle, float axisX, float axisY, float axisZ);
		void rotate(float angle, const Vec3f& rXYZ);
		void scale(float s);
		void scale(float sx, float sy, float sz);
		void scale(const Vec3f& xyz);
		void scale(const Dim3& whd);
		
		//implements transform matrix stack
		void concat();
		void push();
		void pop();
	};

	// Geometry matrix set/get functions
	inline void ProtoContext::setModel(const glm::mat4& model) {
		this->model = model;
		glUniformMatrix4fv(model_U, 1, GL_FALSE, &model[0][0]);
		concat();
	}

	inline void ProtoContext::setView(const glm::mat4& view) {
		this->view = view;
		glUniformMatrix4fv(view_U, 1, GL_FALSE, &view[0][0]);
		concat();
	}

	inline void ProtoContext::setProjection(const glm::mat4& projection) {
		this->projection = projection;
		glUniformMatrix4fv(projection_U, 1, GL_FALSE, &projection[0][0]);
		concat();
	}

	// Matrix concatenations functions
	// MV Mat4
	inline void ProtoContext::concatModelView() {
		modelView = view * model;
		glUniformMatrix4fv(modelView_U, 1, GL_FALSE, &modelView[0][0]);
	}

	// MVP Mat4
	inline void ProtoContext::concatModelViewProjection() {
		modelViewProjection = projection * modelView;
		glUniformMatrix4fv(modelViewProjection_U, 1, GL_FALSE, &modelViewProjection[0][0]);
	}

	// matrix locations (don't currently need all these)
	inline GLuint ProtoContext::getModel_U() {
		return model_U;
	}

	inline GLuint ProtoContext::getView_U() {
		return view_U;
	}

	inline GLuint ProtoContext::getModelView_U() {
		return modelView_U;
	}

	inline GLuint ProtoContext::getProjection_U() {
		return projection_U;
	}

	inline GLuint ProtoContext::getModelViewProjection_U() {
		return modelViewProjection_U;
	}

	inline GLuint ProtoContext::getNormal_U() {
		return normal_U;
	}

	// shadow map
	inline void ProtoContext::setLightView(const glm::mat4& lightView) {
		this->lightView = lightView;
		updateLightViewMatrices();
	}

	inline void ProtoContext::setLightBias(const glm::mat4& lightBias) {
		this->lightBias = lightBias;
		updateLightViewMatrices();
	}

	inline void ProtoContext::setLightProjection(const glm::mat4& lightProjection) {
		this->lightProjection = lightProjection;
		updateLightViewMatrices();
	}

	// geometry matrices
	inline const glm::mat4& ProtoContext::getModel() {
		return model;
	}

	inline const glm::mat4& ProtoContext::getView() {
		return view;
	}

	inline const glm::mat4& ProtoContext::getModelView() {
		return modelView;
	}

	inline const glm::mat4& ProtoContext::getProjection() {
		return projection;
	}

	inline const glm::mat4& ProtoContext::getModelViewProjection() {
		return modelViewProjection;
	}

	// return computed normal
	inline const glm::mat3& ProtoContext::getNormal() {
		return glm::transpose(glm::inverse(glm::mat3(modelView)));
	}

	// light matrices (for shadow map)
	inline const glm::mat4& ProtoContext::getLightView() {
		return lightView;
	}

	inline const glm::mat4& ProtoContext::getLightModelView() {
		return lightModelView;
	}

	inline const glm::mat4& ProtoContext::getLightProjection() {
		return lightProjection;
	}

	inline const glm::mat4& ProtoContext::getLightBias() {
		return lightBias;
	}

	inline const glm::mat4& ProtoContext::getLightModelViewBiasProjection() {
		return lightModelViewBiasProjection;
	}

	inline const glm::mat4& ProtoContext::getShadow() {
		return shadow;
	}


	// Lighting
	inline const Col3f&  ProtoContext::getGlobalAmbient() {
		return globalAmbient;
	}

	inline const GLuint& ProtoContext::getGlobalAmbient_U() {
		return globalAmbient_U;
	}

	inline const ProtoContext::Light_U& ProtoContext::getLight_U(int index) {
		return lights_U[index];
	}


	// N Mat3
	//inline void ProtoContext::createNormalMatrix() {
	//	normal = glm::transpose(glm::inverse(glm::mat3(modelView)));
	//}

	// lighting
	inline void ProtoContext::setGlobalAmbient(const Col3f& globalAmbient) {
		this->globalAmbient = globalAmbient;
		glUniform3fv(globalAmbient_U, 1, &globalAmbient.r);
	}

	inline void ProtoContext::setLight(int index, const Vec3& pos, const Vec3& intensity) {
		lights[index].setPosition(pos);
		lights[index].setIntensity(intensity);
		glUniform3fv(lights_U[index].position, 1, &lights[index].getPosition().x);
		glUniform3fv(lights_U[index].intensity, 1, &lights[index].getIntensity().x);

		// update shadow map view matrix
		setLightView(glm::lookAt(glm::vec3(getLight(0).getPosition().x, getLight(0).getPosition().y, getLight(0).getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

		updateLightViewMatrices();
	}

	inline const ProtoLight& ProtoContext::getLight(int index) {
		return lights.at(index);
	}

	inline const GLuint ProtoContext::getLightModelViewBiasProjection_U() {
		return lightModelViewBiasProjection_U;
	}

	inline const Vec4f& ProtoContext::getLightRenderingFactors() {
		return lightRenderingFactors;
	}

	inline void ProtoContext::setLightRenderingFactors(const Vec4f& lightRenderingFactors) {
		this->lightRenderingFactors = lightRenderingFactors;
		glUniform4fv(getLightRenderingFactors_U(), 1, &lightRenderingFactors.x);
	}

	inline const GLuint& ProtoContext::getLightRenderingFactors_U() {
		return lightRenderingFactors_U;
	}

	inline void ProtoContext::setLightRenderingFactors_U(const GLuint& lightRenderingFactors_U) {
		this->lightRenderingFactors_U = lightRenderingFactors_U;
	}

	inline const GLuint& ProtoContext::getShadowMap_U() {
		return shadowMap_U;
	}

	inline void ProtoContext::setShadowMap_U(const GLuint& shadowMap_U) {
		this->shadowMap_U = shadowMap_U;
	}

	inline const GLuint& ProtoContext::getShaderPassFlag_U() {
		return shaderPassFlag_U;
	}

	inline void ProtoContext::setShaderPassFlag_U(const GLuint& shaderPassFlag_U) {
		this->shaderPassFlag_U = shaderPassFlag_U;
	}

	inline void ProtoContext::setShadowBuffer_U(const GLuint& shadowBuffer_U) {
		this->shadowBuffer_U = shadowBuffer_U;
	}

	//inline const GLuint& ProtoContext::getShadowBuffer_U() {
	//	return shadowBuffer_U;
	//}

	inline GLuint& ProtoContext::getShadowBuffer_U() {
		return shadowBuffer_U;
	}

	inline void ProtoContext::setShadowTexture_U(const GLuint& shadowTexture_U) {
		this->shadowTexture_U = shadowTexture_U;
	}

	inline GLuint& ProtoContext::getShadowTexture_U() {
		//trace("&shadowTexture_U", &shadowTexture_U);
		return shadowTexture_U;
	}



	inline void ProtoContext::setSceneCenter(const Vec3& axis) {

	}
	inline void ProtoContext::setEyePosition(const Vec3& eyePos) {

	}
	inline void ProtoContext::setUpAxis(const Vec3& axis) {

	}
}

// close ijg namespace

#endif // __PROTO_CONTEXT_H__
