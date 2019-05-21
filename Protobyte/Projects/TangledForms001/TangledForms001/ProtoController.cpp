/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"

std::vector<Vec3f> rots;

void ProtoController::init() {

	setBackground({ 1.0 });
	//shadowsOn();
	setShadowSharpness(512, 512);

	// shoots
	int ptCount{ 50 };
	std::vector<Vec3> pts;
	float theta{ 0 }, phi{ 0 };
	for (int i = 0; i < ptCount; i++) {
		float r = random(20, 40);
		r = i + 12 + random(3, 9);
		float x = sin(theta) * (r + i);
		float y = 0;
		float z = cos(theta) * (r + i);
		float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;
		pts.push_back(Vec3f(tx, ty, tz));
		phi += TWO_PI / ptCount * random(1.4, 6);
		theta += TWO_PI / ptCount * random(12, 18);
	}
	Spline3 path(pts, 6, true, 1.0);


	tube = Tube(path, 4, 13, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(.75, 9.5), 12), false, "humanSkin02.jpg");
	tube.setDiffuseMaterial({ 1.0f, 1, 1 });
	tube.setAmbientMaterial(0.05f);
	tube.setBumpMap("humanSkin02.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tube.setTextureScale({ 1, 0.03f });
	tube.setSpecularMaterial({ 1, 1, 1 });
	tube.setShininess(30);



	ptCount = 60;
	pts.clear();
	theta = phi = 0;
	for (int i = 0; i < ptCount; i++) {
		float r = 170 + random(13, 23);
		float x = sin(theta) * (r + i/2);
		float y = 0;
		float z = cos(theta) * (r + i/2);
		float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;
		pts.push_back(Vec3f(tx, ty, tz));
		phi += TWO_PI / (ptCount * random(.12, 1));
		theta += TWO_PI / ptCount * random(8, 28);
	}
	path = Spline3(pts, 9, true, 1.0);


	yellowTendril = Tube(path, 4, 12, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(.85, 2.85), 50), false, "gold01.jpg");
	yellowTendril.setDiffuseMaterial({ 1.0f, 1, 1 });
	yellowTendril.setAmbientMaterial(0.03f);
	yellowTendril.setBumpMap("gold01.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	yellowTendril.setTextureScale({ 1, 0.003f });
	yellowTendril.setSpecularMaterial({ 1, 1, 1 });
	yellowTendril.setShininess(40);
	

}

void ProtoController::run() {
}

void ProtoController::display() {
	setLight(0, Vec3(sin(radians(getFrameCount() * .25f)) * 2, 0, 600), { 1, 1, 1 });
	beginArcBall();
	scale(.45f);
	int i = 0;
	/*for (ProtoBlock b : blocks) {
		push();
		rotate( rots.at(i).x, {1, 0, 0} );
		rotate( rots.at(i).y, { 0, 1, 0 } );
		rotate( rots.at(i).z, { 0, 0, 1 } );
		i++;
		b.display();
		pop();
	}*/

	push(); 
	tube.display();
	pop();

	push();
	//translate(-350, 300, -400);
	yellowTendril.display();
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
	save("Tube_Spiral", 10);
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