/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	int ptCount{ 40 };
	setShadowsOn(1);
	float tendrilLen{ 100.0f };
	float segLen{ tendrilLen / ptCount };
	std::vector<Vec3> pts;
	float theta{ 0 }, phi{ 0 };

	//for (int i = 0; i < ptCount; i++) {
	//	float r = 100;
	//	//r = i + 12 + random(3, 9);
	//	float x = sin(theta) * (r);
	//	float y = segLen * i;
	//	float z = cos(theta) * (r);
	//	/*float tx = x;
	//	float ty = cos(phi) * y - sin(phi) * z;
	//	float tz = sin(phi) * y + cos(phi) * z;*/
	//	//pts.push_back(Vec3f(x, y, z));
	//	pts.push_back(Vec3f(x, y, z));
	//	//trace(pts.at(i));
	//	//phi += TWO_PI / ptCount * random(1.4, 6);
	//	theta += TWO_PI / ptCount;
	//}

	//path = Spline3(pts, 3, true, 1.0);

	float u{ 0.0f };
	for (int i = 0; i < ptCount; i++) {
		float x = 41 * cos(u) - 18 * sin(u) - 83 * cos(2 * u) - 83 * sin(2 * u) - 11 * cos(3 * u) + 27 * sin(3 * u);
		float y = 36 * cos(u) + 27 * sin(u) - 113 * cos(2 * u) + 30 * sin(2 * u) + 11 * cos(3 * u) - 27 * sin(3 * u);
		float z = 45 * sin(u) - 30 * cos(2 * u) + 113 * sin(2 * u) - 11 * cos(3 * u) + 27 * sin(3 * u);
		pts.push_back(Vec3f(x*.5f, y * .5f, z * .5f));
		u += TWO_PI / ptCount;
	}
	path = Spline3(pts, 3, true, 1.0);


	//// need to fix this
	tendril = Tube(path, 4, 18, ProtoTransformFunction(ProtoTransformFunction::LINEAR, Tup2(19.5, 0.15f), 1), true, "corroded_red.jpg");
	tendril.setDiffuseMaterial({ 1.0f, 1, 1 });
	tendril.setAmbientMaterial(0.05f);
	tendril.setBumpMap("corroded_red.jpg", 1.0f);
	////tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tendril.setTextureScale({ 1.1, .1f });

	tendril.setSpecularMaterial({ 1, 1, 1 });
	tendril.setShininess(12);

	//strokeWeight(5);

	//for (const auto i : path.getControlPts())
	//	trace(i);

}

void ProtoController::run() {
}

void ProtoController::display() {
	background({ 1, 1, 1, 1 });
	beginArcBall();
	stroke(200, 100, 0);
	path.display(4, { 1.0f, .7f, 0 });
	path.displayControlPts();
	path.displayInterpPts(6);
	tendril.display(WIREFRAME, 1.0f);
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