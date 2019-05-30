/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"


void ProtoController::init() {
	// shoots
	int ptCount{ 8 };
	std::vector<Vec3> pts;
	float ht = 1000.0f;
	float htInterval = ht/ ptCount;
	float theta{ 0 }, phi{ 0 };
	for (int i = 0; i < ptCount; i++) {
		float r = 200;
		//r = i + 12 + random(3, 9);
		float x = sin(theta) * (r + i);
		float y = -ht/2 + htInterval * i;
		float z = cos(theta) * (r + i);
		/*float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;*/
		pts.push_back(Vec3f(x, y, z));
		//phi += TWO_PI / ptCount * random(1.4, 6);
		theta += TWO_PI / ptCount;
	}
	path = Spline3(pts, 12, true, 1.0);


	tangles = Tube(path, 4, 18, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(35.75, 99.5), 2), true, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg");
	tangles.setDiffuseMaterial({ 1.0f, 1, 1 });
	tangles.setAmbientMaterial(0.05f);
	tangles.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tangles.setTextureScale({ 1, 0.3f });
	tangles.setSpecularMaterial({ 1, 1, 1 });
	tangles.setShininess(30);
}

void ProtoController::run() {
}

void ProtoController::display() {
	setLight(0, Vec3(sin(radians(getFrameCount() * .25f)) * 2, 0, 600), { 1, 1, 1 });
	beginArcBall();
	scale(.18f);
	int i = 0;
	
	push();
	tangles.display(WIREFRAME, 1);
	//path.display();
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