/*
Protobyte Library 0.1.7
Ira Greenberg 2019

// random 3D picking on sphere
// http://mathworld.wolfram.com/SpherePointPicking.html
*/

#include "ProtoController.h"

void ProtoController::init() {
	setLight(0, { 900, 0, 400 }, { 1 });
	float radius{ 400.0f };
	for (int i = 0; i < pts; i++) {
		//r = (i * 2) + 250 - abs(sin(theta2) * 60);

		float t = random(TWO_PI);
		float u = random(-1, 1);
		float x = sqrt(1.0 - u * u) * cos(t);
		float y = sqrt(1.0 - u * u) * sin(t);
		float z = u;
		float a = random(radius * .25);
		vs.push_back({ x * radius+a, y * radius + a, z * radius + a });
	}


	s1 = Spline(vs, 8, false);

	tube = Tube(s1, 5, 12, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(.15, 8.5), 460), false, "gold01.jpg");
	//tube.setPerturbation({ random(3.2), random(1.5), random(1.2) });
	tube.setColor({ .2, .2, .05, 1 });
	//tube.setDiffuseMaterial(1);
	////tube.setAmbientMaterial(0.05f);
	tube.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", 1.5f);
	////tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tube.setTextureScale({ .9f, 0.003f });
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
	//scale(10);
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