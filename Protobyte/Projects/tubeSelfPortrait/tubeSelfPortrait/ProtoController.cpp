/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	setLight(0, { 900, 0, 400 }, { 1, 1, 1 });
	float theta{ 0.0f };
	float r{ 240.0f };
	float theta2{ 0 };
	for (int i = 0; i < pts; i++) {
		r = (i * 2) + 250 - abs(sin(theta2) * 60);
		vs.push_back(Vec(sin(theta) * r, cos(-theta2) * -370 + i * 23, cos(theta) * r));

		//vs.push_back({ cos(theta) * r, sin(theta) * r, 0 });
		//theta += TWO_PI * 6 / pts;
		theta += TWO_PI / pts;
		theta2 += TWO_PI / pts;
	}


	s1 = Spline(vs, 8, false);
	tube = Tube(s1, 3, 12, false, "yellow.jpg");
	tube.setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL_RANDOM, Tup2f{ 20, 20 }, 2));
	tube.setPerturbation({ random(3.2), random(1.5), random(1.2) });
	//tube.setColor({ .1, 0, 0, 1 });
	//tube.setDiffuseMaterial(1);
	////tube.setAmbientMaterial(0.05f);
	tube.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
	////tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tube.setTextureScale({ 1.0f, 0.3f });
	tube.setSpecularMaterial(1);
	tube.setShininess(125);
}

void ProtoController::run() {
}

void ProtoController::display() {
	//background("iraWrapped_low.jpg");
	background(.35, .35, .385);
	arcBallBegin();
	//tube.display(WIREFRAME);
	tube.display();
	arcBallEnd();
}

// Key and Mouse Events
void ProtoController::keyPressed() {

}

void ProtoController::mousePressed() {

}

void ProtoController::mouseRightPressed() {
}

void ProtoController::mouseReleased() {
	//save("wrap", 4);
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