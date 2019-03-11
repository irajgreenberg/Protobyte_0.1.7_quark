/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	for (int i = 0; i < 6; i++) {
		blocks[i] = Block({},  {}, {}, Col4f(1, .5, 1));
	}
}

void ProtoController::run() {
}

void ProtoController::display() {
	rotate(PI / 4, { .34, .5, .75 });
	beginArcBall();
	push();
	///*translate(0, 1, 1);*/
	//scale(100);
	//blocks[0].display(WIREFRAME);
	//pop(); 
	push();
	translate(0, 100, 0);
	scale(100);
	blocks[1].display(WIREFRAME);
	pop();
	push();
	translate(0, -100, 0);
	scale(100);
	blocks[2].display(WIREFRAME);
	pop();
	push();
	translate(-100, 0, 0);
	scale(100);
	blocks[3].display(WIREFRAME);
	pop();
	push();
	translate(100, 0, 0);
	scale(100);
	blocks[4].display(WIREFRAME);
	pop();

	push();
	translate(0, 0, -100);
	scale(100);
	blocks[5].display(WIREFRAME);
	pop();
	push();
	translate(0, 0, 100);
	scale(100);
	blocks[0].display(WIREFRAME);
	pop();
	
	endArcBall();
	//blocks[0].display();
	//blocks[0].display();
	//blocks[0].display();
	//blocks[0].display();
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