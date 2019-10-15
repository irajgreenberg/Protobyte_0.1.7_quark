/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	s = Sphere(16, 16, Col4{ 0,0,0,1}, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg");
	s.setDiffuseMaterial({ 1.0f, 1, 1 });
	s.setAmbientMaterial(0.25f);
	s.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", 1.0f);
	s.setTextureScale({.5, .5});

	s.setSpecularMaterial({ 1, 1, 1 });
	s.setShininess(12);
}

void ProtoController::run() {
}

void ProtoController::display() {
	background({ 1 });
	setLight(0, Vec3(0, 0, 100), { 1, .85, .85 });
	setLight(1, Vec3(-200, 200, 100), { 1, .5, .1 });
	
	push();
	translate(-102, 0, 0);
	scale(200, 300, 200);
	s.display();
	pop();

	translate(102, 0, 0);
	scale(200, 300, 200);
	s.display();
}

// Key and Mouse Events
void ProtoController::keyPressed() {
}

void ProtoController::mousePressed() {
}

void ProtoController::mouseRightPressed() {
}

void ProtoController::mouseReleased() {
	save("protoSac", 6);
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