/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

std::vector<Vec3f> rots;

void ProtoController::init() {

	setBackground({ .125f, .125f, .125f, 1.0f });
	shadowsOn();
	setShadowSharpness(512, 512);

	for (int i = 0; i < 60; i++) {
		rots.push_back({ random(PI), random(PI) , random(PI) });
		float d = random(2, 20);
		blocks.push_back(
			ProtoBlock(
				Vec3f( random(-200, 200), random(-200, 200) , random(-50, 50) ),
				Vec3f(random(PI), random(PI) , random(PI) ),
				Dim3f(d, random(50, 340) , d ),
				Col4f( random(), random() , random(), 1.0 )
			)
		);
	}
}

void ProtoController::run() {
}

void ProtoController::display() {
	setLight(0, Vec3(sin(radians(getFrameCount()*.25f)) * 2, 0, 600), { 1, 1, 1 });
	beginArcBall();
	translate(0, 0, -200);
	int i = 0;
	for (ProtoBlock b : blocks) {
		push();
		rotate( rots.at(i).x, {1, 0, 0} );
		rotate( rots.at(i).y, { 0, 1, 0 } );
		rotate( rots.at(i).z, { 0, 0, 1 } );
		i++;
		b.display();
		pop();
	}
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