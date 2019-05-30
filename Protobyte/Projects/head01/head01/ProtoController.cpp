/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

void ProtoController::init() {
	//setShadowsOn(1);
	// shoots
	int ptCount{ 20 };
	std::vector<Vec3> pts;
	float theta{ 0 }, phi{ 0 };
	for (int i = 0; i < ptCount; i++) {
		float r = 200;
		//r = i + 12 + random(3, 9);
		float x = sin(theta) * (r + i);
		float y = -ptCount*40/2+i*40;
		float z = cos(theta) * (r + i);
		/*float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;*/
		//pts.push_back(Vec3f(x, y, z));
		pts.push_back(Vec3f(x, y, z));
		//phi += TWO_PI / ptCount * random(1.4, 6);
		theta += TWO_PI / ptCount;
	}
	
		path = Spline3(pts, 1, true, 1.0);
	// need to fix this
	head = Tube(path, 4, 18, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL_INVERSE,
		Tup2(9.75, 19.5), 31), true, "humanSkin02.jpg");
	head.setDiffuseMaterial({ 1.0f, 1, 1 });
	head.setAmbientMaterial(0.05f);
	head.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_15-normal.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	head.setTextureScale({ 1.1, .1f });

	head.setSpecularMaterial({ 1, 1, 1 });
	head.setShininess(40);

	strokeWeight(5);

	for (const auto i : path.getControlPts())
		trace( i);
	
}

void ProtoController::run() {
}

void ProtoController::display() {
	background({ 1 });
	//stroke({ 0,0,0,1 });
	//setLight(0, Vec3(0, 0, 100), { .8, .8, .6 });
	//setLight(1, Vec3(-200, 200, 100), { .5, .8, .8 });
	beginArcBall();
	scale(.25);
	int i = 0;

	push();

	//head.display();
	//head.display(POINTS, 4);
	//tangles3.display(WIREFRAME, 1.5);
	pop();
	//path.display;
	stroke(0);

	//path.display(2);
	stroke(1, 0, 0);
	//path.displayInterpPts(7);
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
	//save("Tendrils", 4);
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