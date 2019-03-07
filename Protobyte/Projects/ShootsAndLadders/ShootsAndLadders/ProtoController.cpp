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

	// shoots
	int ptCount{ 190 };
	std::vector<Vec3> pts;
	float theta{ 0 }, phi{ 0 };
	for (int i = 0; i < ptCount; i++) {
		float r = random(14, 30);
		r = 100;
		float x = sin(theta) * (r - i);
		float y = 0;
		float z = cos(theta) * (r - i);
		float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;
		pts.push_back(Vec3f(tx, ty, tz));
		phi += TWO_PI / (ptCount * random(.15, 1));
		theta += TWO_PI / ptCount * random(12, 18);
	}
	Spline3 path(pts, 5, true, 1.0);


	tube = Tube(path, 4, 4, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2(.5, 1.9), 24), false, "humanSkin02.jpg");
	tube.setDiffuseMaterial({ 1.0f, 1, 1 });
	tube.setAmbientMaterial(0.15f);
	tube.setBumpMap("humanSkin02.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tube.setTextureScale({ 1, 0.03f });
	tube.setSpecularMaterial({ 1, 1, 1 });
	tube.setShininess(5);


	// ladders
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

	tube.display();
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