/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	//glEnable(GL_DEPTH_TEST);
//	trace("In init in ProtoController");
	background(1, 0, 0);
	
	pts.push_back({ -400, 0, 0 });
	pts.push_back({ -300, 0, 0 });
	pts.push_back({ 0, 200, 0 });
	pts.push_back({ 300, 0, 0 });
	pts.push_back({ 400, 0, 0 });

	//r = ProtoRectangle(0, 0, 1418, 1080, Col4f(0, 0,0, 1 ), "crit_background.jpg") ;
	//r.setDiffuseMaterial({ 1.0f, 1, 1 });
	//r.setAmbientMaterial(0);
	////r.createBumpMap("crit_background.jpg");
	//r.setBumpMap("crit_background_normal.jpg");

	//r.setSpecularMaterial({ 1, 1, 1 });
	//r.setShininess(80);
	//r.display();

	//setProjectionType(ORTHOGONAL);
	/*strokeWeight(15);
	beginPath();
	for (Vec v : pts) {
		curveVertex(v);
	}
	endPath(CLOSE);*/
	//background("crit_background.jpg");
	
}

void ProtoController::run() {
}

void ProtoController::display() {
	//background(1, 1, 0);
	//background("iraWrapped_low.jpg");
	//background("crit_background.jpg");
	
	//stroke(1, 0, 0);
	/*push();
	translate(getWidth() / 2, getHeight() / 2, 0);*/
	//rect(-960, 540, 1920, 1080);
	/*pop();*/
	//push();
	//scale(1920, 1080, 1);
	//setProjectionType(ORTHOGONAL);
/*
		float viewAngle = getFrameCount()*PI/180.0f;
		float aspect = float(getWidth()) / float(getHeight());
		float nearDist = 0.1f;
		float farDist = 6000.0f;
		*/
	//setViewAngle(getFrameCount()*PI/180.0f);
	///*ctx->setProjection(glm::perspective(getViewAngle(), getAspectRatio(), getNearDist(), getFarDist()));*/
	/*glDisable(GL_DEPTH_TEST);
	ctx->setProjection(glm::ortho(-getWidth()/2.0f, getWidth() / 2.0f, -getHeight() / 2.0f, getHeight() / 2.0f, 1.0f, 3000.0f));*/


	////-1, 1, -1, 1, 1, -1

	////setProjectionType(PERSPECTIVE);
	////setProjectionType(ORTHOGONAL);
	//
	/*push();
	translate(0, 0, -1000);
	r.display();
	pop();*/

	beginArcBall();
	//glEnable(GL_DEPTH_TEST);
	curveDetail(20);
	strokeWeight(15);
	/*ctx->setProjection(glm::perspective(getViewAngle(), getAspectRatio(), getNearDist(), getFarDist()));*/
	push(); 
	translate(0, 0, 0);
	stroke(1);
	rotate(getFrameCount() * .75 * PI / 180, { 0, 1, 0 });
	beginPath();
	for (Vec v : pts) {
		curveVertex(v);
	}
	endPath(CLOSE);
	pop();
	endArcBall();
}

// Key and Mouse Events
void ProtoController::keyPressed() {
}

void ProtoController::mousePressed() {
}

void ProtoController::mouseRightPressed() {
}

void ProtoController::mouseReleased() {
}

void ProtoController::mouseRightReleased() {
}

void ProtoController::mouseMoved() {
}

void ProtoController::mouseDragged() {
}

// Window Events
void ProtoController::onResized() {
}

void ProtoController::onClosed() {
}