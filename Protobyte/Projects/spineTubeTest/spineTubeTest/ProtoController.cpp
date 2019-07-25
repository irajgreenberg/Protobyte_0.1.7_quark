/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	float w{ 800.0f };
	float gap = w / count;
	for (int i = 0; i < count; i++) {
		float x = -w / 2 + gap * i;
		float y = random(-5, 5);
		float z = random(-5, 5);
		if (i == 0 || i == count-1) y = -10;
		pts.push_back(Vec3(x, y, z));
	}
	
	
	s = Spline(pts, 8, false, ProtoSpline3::CHORDAL);

	tube = Tube(s, 4, 24, false, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg");
	tube.setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f{2, 12}, 12));
	tube.setPerturbation({ 0 });
	tube.setColor({ .1, 0, 0, 1 });
	tube.setDiffuseMaterial(1);
	//tube.setAmbientMaterial(0.05f);
	tube.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
	////tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tube.setTextureScale({ 1.0f, 0.03f });
	tube.setSpecularMaterial(1);
	tube.setShininess(68);

}

void ProtoController::run() {
}

void ProtoController::display() {
	background(127);
	beginArcBall();
	push();
	scale(4);
	s.displayControlPts(7, { 0 });
	//s.display(1, { 200, 200, 0, 1 });
	s.displayFrenetFrames(5);
	s.displayInterpolatedPts(5, { .5,.5, .5, 1 });
	tube.display();
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
	pts[0].y = pts[count-1].y = mouseY-getHeight()/2;
	s = Spline(pts, 6, false);
}

void ProtoController::mouseDragged() {
}

// Window Events
void ProtoController::onResized() {
}

void ProtoController::onClosed() {
}