/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {

	setLight(0, { 900, 0, 400 }, { 1, 1, 1 });
	float theta{ 0.0f }, theta2{ 0 };
	float r{ 240.0f };
	//float theta2{ 0 };

	for (int i = 0; i < tubeCount; i++) {

		// generate points that will be consumed by Spline
		int pointCount{ (int)random(20, 30) };
		std::vector<Vec3> pts;
		for (int j = 0; j < pointCount; j++) {
			pts.push_back({
				cos(theta) * (getWidth() / 1.3f), //x
				-600+sin(theta2) * 125,  //y
				sin(theta ) * (getWidth() / 5.3f)  //z
				});
			theta += TWO_PI * 2 / pointCount;
			theta2 += PI / 20;
		}

		//create spline
		splines.push_back(Spline3(pts, 5, false));

		// create Tubes
		tubes.push_back(Tube(splines.at(i), 8, 18, false, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg"));
		tubes.at(i).setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f{ 10, 24 }, 4));
		tubes.at(i).setPerturbation({ random(3.2), random(1.5), random(1.2) });
		//tube.setColor({ .1, 0, 0, 1 });
		//tube.setDiffuseMaterial(1);
		////tube.setAmbientMaterial(0.05f);
		tubes.at(i).setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
		////tube.loadBumpMapTexture("vascular3_normal2.jpg");
		tubes.at(i).setTextureScale({ 1.0f, 0.03f });
		tubes.at(i).setSpecularMaterial(1);
		tubes.at(i).setShininess(125);
	}

}

void ProtoController::run() {
}

void ProtoController::display() {
	background(1, 1, 0);
	arcBallBegin();
	translate(0, 0, -1500);
	for (int i = 0; i < tubeCount; i++) {
		tubes.at(i).display();
	}
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