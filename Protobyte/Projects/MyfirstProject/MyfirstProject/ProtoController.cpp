/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	setLight(0, Vec3(0, 0, 100), { 1, .85, .85 });
	setLight(1, Vec3(-200, 200, 100), { 1, .5, .1 });
	s = Sphere(36, 24, Col4(0), "corroded_red.jpg");
	s.setDiffuseMaterial({ 1, 1, 1 });
	s.setAmbientMaterial(.25);
	s.createBumpMap("corroded_red.jpg");
	s.setTextureScale({ .5, .5 });

	s.setSpecularMaterial({ 1, 1, 1 });
	s.setShininess(50);
	for (int i = 0; i < starCount; i++) {
		starLocs.push_back(Vec(random(-getWidth()/2, getWidth()/2), random(-getHeight()/2, getHeight()/2), random(-500, -100)));
	}
}

void ProtoController::run() {
}

void ProtoController::display() {
	background(0);
	noStroke();
	for (int i = 0; i < starCount; i++) {
		fill(random(1));
		rect(starLocs.at(i).x, starLocs.at(i).y, starLocs.at(i).z, 2, 2);
	}

	scale(300);
	rotate(radians(15), Vec(0, 0, 1)),
	rotate(radians(getFrameCount()*.2), Vec(0, .875, 0)), 
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