/*!  \brief  ProtoContext.cpp: encapsulates static tranformation matrix/functions
ProtoContext.cpp
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

#include "ProtoContext.h"
using namespace ijg;

float ProtoContext::width{ 0.0f };
float ProtoContext::height{ 0.0f };

// initialize static vars
std::shared_ptr<ProtoContext> ProtoContext::ctx = nullptr;


const std::shared_ptr<ProtoContext> ProtoContext::getContext() {
	if (!ProtoContext::ctx) {
		ProtoContext::ctx = std::shared_ptr<ProtoContext>(new ProtoContext());
	}
	return ProtoContext::ctx;
}

const std::shared_ptr<ProtoContext> ProtoContext::getContext(float width, float height) {
	ProtoContext::width = width;
	ProtoContext::height = height;
	if (!ProtoContext::ctx){
		ProtoContext::ctx = std::shared_ptr<ProtoContext>(new ProtoContext());
	}
	return ProtoContext::ctx;
}


// should only be called by ProtoBaseApp
void ProtoContext::init(){
	static int counter = 0;
	if (counter++ == 0) {// just 1 time
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
		lights.push_back(ProtoLight());
	
	//	ctx->setViewMatrix(glm::lookAt(glm::vec3(0.0, 0.0, 1560), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)));
	//	ctx->concatenateModelViewMatrix();
	//	ctx->createNormalMatrix();

		for (int i = 0; i < 8; ++i){
			std::string pos = "lights[" + std::to_string(i) + "].position"; 
			//trace("pos =", pos);
			lights_U[i].position = glGetUniformLocation(ProtoShader::getID_2(), pos.c_str());

			std::string inten = "lights[" + std::to_string(i) + "].intensity";
			lights_U[i].intensity = glGetUniformLocation(ProtoShader::getID_2(), inten.c_str());

			// eventually get rid of these probably
			std::string diff = "lights[" + std::to_string(i) + "].diffuse";
			lights_U[i].diffuse = glGetUniformLocation(ProtoShader::getID_2(), diff.c_str());

			std::string amb = "lights[" + std::to_string(i) + "].ambient";
			lights_U[i].ambient = glGetUniformLocation(ProtoShader::getID_2(), amb.c_str());

			std::string spec = "lights[" + std::to_string(i) + "].specular";
			lights_U[i].specular = glGetUniformLocation(ProtoShader::getID_2(), spec.c_str());
		}

		// global ambient light
		globalAmbient_U = glGetUniformLocation(ProtoShader::getID_2(), "globalAmbientLight");

		// Get unifrom locations
		model_U = glGetUniformLocation(ProtoShader::getID_2(), "modelMatrix");
		modelView_U = glGetUniformLocation(ProtoShader::getID_2(), "modelViewMatrix");
		modelViewProjection_U = glGetUniformLocation(ProtoShader::getID_2(), "modelViewProjectionMatrix");
		normal_U = glGetUniformLocation(ProtoShader::getID_2(), "normalMatrix");

		// shadow map and light transformation matrix for shadowmapping
		shadowMap_U = glGetUniformLocation(ProtoShader::getID_2(), "shadowMap");
		lightModelViewBiasProjection_U = glGetUniformLocation(ProtoShader::getID_2(), "shadowModelViewBiasProjectionMatrix");

		// new to allow model view concatentation in shader
		LV_U = glGetUniformLocation(ProtoShader::getID_2(), "lightViewMatrix");
		LP_U = glGetUniformLocation(ProtoShader::getID_2(), "lightProjectionMatrix");
		LB_U = glGetUniformLocation(ProtoShader::getID_2(), "lightBiasMatrix");

		// pass shadow map texture to shader
		shaderPassFlag_U = glGetUniformLocation(ProtoShader::getID_2(), "shadowPassFlag");
		glUniform1i(shaderPassFlag_U, 1); // controls render pass in shader
		glUniform1i(shadowMap_U, 5);

		// enable/disable lighting factors for 2D rendering
		// default is all on
		lightRenderingFactors_U = glGetUniformLocation(ProtoShader::getID_2(), "lightRenderingFactors");
		//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);


		//shader_ptr->unbind();
	}
}

void  ProtoContext::setShadowSharpness(int shadowSharpnessWidth, int shadowSharpnessHeight) {
	shadowSharpness_U = glGetUniformLocation(ProtoShader::getID_2(), "shadowSharpness");
	glm::vec2 sharpness = glm::vec2(float(shadowSharpnessWidth), float(shadowSharpnessHeight));
	glUniform2fv(shadowSharpness_U, 1, &sharpness.x);
	//glUniform1i(shadowSharpness_U, shadowSharpnessWidth);
}

// matrix transformation functions, in style of GL 1.0
void ProtoContext::translate(float tx, float ty, float tz){
	model = glm::translate(model, glm::vec3(tx, ty, tz));
	concat();
}
void ProtoContext::translate(const Vec3f& tXYZ){
	model = glm::translate(model, glm::vec3(tXYZ.x, tXYZ.y, tXYZ.z));
	concat();
}
void ProtoContext::rotate(float angle, float axisX, float axisY, float axisZ){
	model = glm::rotate(model, angle, glm::vec3(axisX, axisY, axisZ));
	concat();
}
void ProtoContext::rotate(float angle, const Vec3f& rXYZ){
	model = glm::rotate(model, angle, glm::vec3(rXYZ.x, rXYZ.y, rXYZ.z));
	concat();
}
void ProtoContext::scale(float s){
	model = glm::scale(model, glm::vec3(s, s, s));
	concat();
}
void ProtoContext::scale(float sx, float sy, float sz){
	model = glm::scale(model, glm::vec3(sx, sy, sz));
	concat();
}
void ProtoContext::scale(const Vec3f& xyz){
	model = glm::scale(model, glm::vec3(xyz.x, xyz.y, xyz.z));
	concat();
}
void ProtoContext::scale(const Dim3f& whd) {
	model = glm::scale(model, glm::vec3(whd.w, whd.h, whd.d));
	concat();
}

void ProtoContext::concat(){
	//M = glm::mat4(1.0f);
	//push();
	//modelViewMatrix =  viewMatrix*modelMatrix;
	concatModelView();
	//createNormal();
	//modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
	concatModelViewProjection();
	// update in shader
	glUniformMatrix4fv(model_U, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(modelView_U, 1, GL_FALSE, &modelView[0][0]);
	glUniformMatrix4fv(modelViewProjection_U, 1, GL_FALSE, &modelViewProjection[0][0]);
	glUniformMatrix3fv(normal_U, 1, GL_FALSE, &getNormal()[0][0]);

	// concatenates light view, projection and bias matrices and updates in shader
	updateLightViewMatrices();
	
	//pop();
}

void ProtoContext::push(){
	// push current transformation matrix onto stack
	//matrixStack.push(M);
	matrixStack.push(model);
}

// reset transformation matrix with stored matrix on stack
void ProtoContext::pop(){
	// reset current transformation matrix with one on top of stack
	//M = matrixStack.top();
	model = matrixStack.top();

	// pop transformation matrix off top of stack
	matrixStack.pop();

	// rebuild matrices and update on GPU
	concat();
}

void ProtoContext::printModelMatrix() {
	trace("Model: \n[", model[0][0], model[0][1], model[0][2], model[0][3], "\n",
		model[1][0], model[1][1], model[1][2], model[1][3], "\n",
		model[2][0], model[2][1], model[2][2], model[2][3], "\n",
		model[3][0], model[3][1], model[3][2], model[3][3], "]");
}
void ProtoContext::printViewMatrix() {
	trace("View: \n[", view[0][0], view[0][1], view[0][2], view[0][3], "\n",
		view[1][0], view[1][1], view[1][2], view[1][3], "\n",
		view[2][0], view[2][1], view[2][2], view[2][3], "\n",
		view[3][0], view[3][1], view[3][2], view[3][3], "]");
}
void ProtoContext::printProjectionMatrix() {
	trace("Projection: \n[", projection[0][0], projection[0][1], projection[0][2], projection[0][3], "\n",
		projection[1][0], projection[1][1], projection[1][2], projection[1][3], "\n",
		projection[2][0], projection[2][1], projection[2][2], projection[2][3], "\n",
		projection[3][0], projection[3][1], projection[3][2], projection[3][3], "]");
}
void ProtoContext::printModelViewMatrix() {
	trace("ModelView: \n[",modelView[0][0], modelView[0][1], modelView[0][2], modelView[0][3],"\n",
		modelView[1][0], modelView[1][1], modelView[1][2], modelView[1][3], "\n", 
		modelView[2][0], modelView[2][1], modelView[2][2], modelView[2][3], "\n",
		modelView[3][0], modelView[3][1], modelView[3][2], modelView[3][3], "]");

}
void ProtoContext::printModelViewProjectionMatrix() {
	trace("ModelViewProjection: \n[", modelViewProjection[0][0], modelViewProjection[0][1], modelViewProjection[0][2], modelViewProjection[0][3], "\n",
		modelViewProjection[1][0], modelViewProjection[1][1], modelViewProjection[1][2], modelViewProjection[1][3], "\n",
		modelViewProjection[2][0], modelViewProjection[2][1], modelViewProjection[2][2], modelViewProjection[2][3], "\n",
		modelViewProjection[3][0], modelViewProjection[3][1], modelViewProjection[3][2], modelViewProjection[3][3], "]");
}

void ProtoContext::updateLightViewMatrices() {
	// currently only works for single light source.
	// need to annoyingly convert from ijg math to glm math, sigh!
	glm::vec3 ltPos = glm::vec3(lights.at(0).getPosition().x, lights.at(0).getPosition().y, lights.at(0).getPosition().z);
	lightView = glm::lookAt(ltPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	lightBiasProjection = lightBias * lightProjection;
	
	lightModelViewBiasProjection = lightBiasProjection * lightView * model;
	
	glUniformMatrix4fv(lightModelViewBiasProjection_U, 1, GL_FALSE, &lightModelViewBiasProjection[0][0]);

	// New to allow concatenation in shader
	glUniformMatrix4fv(LV_U, 1, GL_FALSE, &lightView[0][0]);
	glUniformMatrix4fv(LP_U, 1, GL_FALSE, &lightProjection[0][0]);
	glUniformMatrix4fv(LB_U, 1, GL_FALSE, &lightBias[0][0]);
	
}


