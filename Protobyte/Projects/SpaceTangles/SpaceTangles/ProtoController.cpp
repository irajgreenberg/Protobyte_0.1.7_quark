/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	// shoots
	int ptCount{ 8 };
	std::vector<Vec3> pts;
	float theta{ 0 }, phi{ 0 };
	for (int i = 0; i < ptCount; i++) {
		float r = 200;
		//r = i + 12 + random(3, 9);
		float x = sin(theta) * (r + i);
		float y = 0;
		float z = cos(theta) * (r + i);
		/*float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;*/
		pts.push_back(Vec3f(x, y, z));
		//phi += TWO_PI / ptCount * random(1.4, 6);
		theta += TWO_PI / ptCount;
	}
	Spline3 path(pts, 12, true, 1.0);


	// need to fix this
	tangles = Tube(path, 4, 18, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(2.75, 39.5), 4), true, "humanSkin02.jpg");
	tangles.setDiffuseMaterial({ 1.0f, 1, 1 });
	tangles.setAmbientMaterial(0.05f);
	tangles.setBumpMap("humanSkin02.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tangles.setTextureScale({ 1, 0.03f });
	tangles.setSpecularMaterial({ 1, 1, 1 });
	tangles.setShininess(30);
}

void ProtoController::run() {
}

void ProtoController::display() {
	setLight(0, Vec3(sin(radians(getFrameCount() * .25f)) * 2, 0, 600), { 1, 1, 1 });
	beginArcBall();
	scale(.45f);
	int i = 0;
	
	push();
	tangles.display();
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