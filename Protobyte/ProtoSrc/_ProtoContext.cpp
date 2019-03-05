

#include "ProtoContext.h"
using namespace ijg;

// define static fields
ProtoContext* ProtoContext::ctx = nullptr;

//cstr
ProtoContext::ProtoContext(){
}

// singleton pattern construction
ProtoContext* ProtoContext::getContext() {
	if (!ctx)
		ctx = new ProtoContext;
	return ctx;
}

// matrix transformation functions, in style of GL 1.0
void ProtoContext::translate(float tx, float ty, float tz){
	M = glm::translate(M, glm::vec3(tx, ty, tz));
	concat();
}
void ProtoContext::translate(const Vec3f& tXYZ){
	M = glm::translate(M, glm::vec3(tXYZ.x, tXYZ.y, tXYZ.z));
	concat();
}
void ProtoContext::rotate(float angle, float axisX, float axisY, float axisZ){
	M = glm::rotate(M, angle, glm::vec3(axisX, axisY, axisZ));
	concat();
}
void ProtoContext::rotate(float angle, const Vec3f& rXYZ){
	M = glm::rotate(M, angle, glm::vec3(rXYZ.x, rXYZ.y, rXYZ.z));
	concat();
}
void ProtoContext::scale(float s){
	M = glm::scale(M, glm::vec3(s, s, s));
	concat();
}
void ProtoContext::scale(float sx, float sy, float sz){
	M = glm::scale(M, glm::vec3(sx, sy, sz));
	concat();
}
void ProtoContext::scale(const Vec3f& sXYZ){
	M = glm::scale(M, glm::vec3(sXYZ.x, sXYZ.y, sXYZ.z));
	concat();
}

//// concatenate MV, N, and MVP matrices and update values on GPU
void ProtoContext::concat(){
	//M = glm::mat4(1.0f);
	//push();
	/*MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));
	MVP = P * MV;
	// update in shader
	glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);

	glm::vec3 ltPos = glm::vec3(light0.getPosition().x, light0.getPosition().y, light0.getPosition().z);

	L_MV = glm::lookAt(ltPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	L_MVBP = L_BP*L_MV;
	//glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &L_MVBP[0][0]);

	glm::mat4 shaderMat = L_MVBP*M; // new 
	glUniformMatrix4fv(L_MVBP_U, 1, GL_FALSE, &shaderMat[0][0]);*/
	//pop();
}

// implements transform matrix stack
void ProtoContext::push(){
	// push current transformation matrix onto stack
	matrixStack.push(M);

}

// reset transformation matrix with stored matrix on stack
void ProtoContext::pop(){

	// reset current transformation matrix with one on top of stack
	M = matrixStack.top();

	// pop transformation matrix off top of stack
	matrixStack.pop();

	// rebuild matrices and update on GPU
	concat();
}