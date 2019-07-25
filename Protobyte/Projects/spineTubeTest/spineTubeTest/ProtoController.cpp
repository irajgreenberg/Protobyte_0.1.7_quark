/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {

	float ht{ 500 };
	int step = ht / pointCount;
	for (int i = 0; i < tubeCount; i++) {
		std::vector<Vec> v;
		pts2D.push_back(v);
		float x{ 0 }, y{ 0 }, z{ 0 };
		float t1{ 0 };
		float r1{ random(20, 50) };
		Vec loc(random(-15, 15), random(-5, 5), random(-15, 15));
		for (int j = 0; j < pointCount; j++) {
			float x = sin(t1) * r1 * random(3);
			float y = ht/2 - step*j + random(-3, 3);
			float z = cos(t1 * random(2, 6)) * r1*random(3);
			pts2D.at(i).push_back(Vec3(x, y, z)+loc);
			t1 += PI / 2 ;
			r1 *= .9;
		}
		splines.push_back(Spline(pts2D.at(i), 4, false, CHORDAL));
		tubes.push_back(Tube(splines.at(i), 1, 24, false, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg"));
		tubes.at(i).setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::LINEAR, Tup2f{ 2, 20 }, random(1, 12)));
		tubes.at(i).setPerturbation({ random(5) });
		//tube.setColor({ .1, 0, 0, 1 });
		tubes.at(i).setDiffuseMaterial(1);
		tubes.at(i).setAmbientMaterial(0.05f);
		//tube.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
		tubes.at(i).loadBumpMapTexture("vascular3_normal2.jpg");
		tubes.at(i).setTextureScale({ 1, .1f});
		tubes.at(i).setSpecularMaterial(1);
		tubes.at(i).setShininess(68);
	}


	//float w{ 800.0f };
	//float gap = w / count;
	//for (int i = 0; i < count; i++) {
	//	float x = -w / 2 + gap * i;
	//	float y = cos(i*75*PI/180)*75;
	//	float z = i;
	//	if (i == 0 || i == count-1) y = -10;
	//	pts.push_back(Vec3(x, y, z));
	//}
	//
	//
	//s = Spline(pts, 8, false, CHORDAL);

	//tube = Tube(s, 1, 24, false, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg");
	//tube.setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::LINEAR, Tup2f{2, 6}, 1));
	//tube.setPerturbation({ 0 });
	//tube.setColor({ .1, 0, 0, 1 });
	//tube.setDiffuseMaterial(1);
	////tube.setAmbientMaterial(0.05f);
	//tube.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
	//////tube.loadBumpMapTexture("vascular3_normal2.jpg");
	//tube.setTextureScale({ 1.0f, 0.03f });
	//tube.setSpecularMaterial(1);
	//tube.setShininess(68);

}

void ProtoController::run() {
}

void ProtoController::display() {
	background(127);
	beginArcBall();
	//push();
	scale(2);
	//s.displayControlPts(7, { 0 });
	////s.display(1, { 200, 200, 0, 1 });
	//s.displayFrenetFrames(5);
	//s.displayInterpolatedPts(5, { .5,.5, .5, 1 });
	//tube.display();
	//pop();

	for (int i = 0; i < tubeCount; i++) {

		for (int j = 0; j < pointCount; j++) {
			tubes.at(i).display();
		}
	}
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
	//pts[0].y = pts[count-1].y = mouseY-getHeight()/2;
	//s = Spline(pts, 6, false);
}

void ProtoController::mouseDragged() {
}

// Window Events
void ProtoController::onResized() {
}

void ProtoController::onClosed() {
}