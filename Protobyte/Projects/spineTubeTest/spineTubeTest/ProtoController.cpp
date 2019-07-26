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
		float r1{ random(15, 45) };
		Vec loc(cos(random(TWO_PI)) * random(25, 85), random(-15, 15), sin(random(TWO_PI)) * random(25, 85));
		ht = random(400, 500);
		for (int j = 0; j < pointCount; j++) {
			float x = y = z = 0.0;
			int toggle = static_cast<int>(random(8));
			if (toggle % 8 == 0) {
				x = loc.x + cos(t1) * -r1 * random(3);
				y = loc.y + ht / 2 - step * j + random(-3, 3);
				z = loc.z + sin(t1 * random(2, 6)) * -r1 * random(3);
			}
			else {
				x = loc.x + sin(t1) * r1 * random(3);
				y = loc.y + ht / 2 - step * j + random(-3, 3);
				z = loc.z + cos(t1 * random(2, 6)) * r1 * random(3);
			}

			pts2D.at(i).push_back(Vec3(x, y, z));
			t1 += PI / 2;
			r1 *= random(.95, .99);
			//trace("r1 = ", r1);
		}
		splines.push_back(Spline(pts2D.at(i), 8, false, CHORDAL));
		int textureIndex = static_cast<int>(random(6));
		std::string randTexture = textures.at(textureIndex);
		tubes.push_back(Tube(splines.at(i), random(1, 2), 30, false, randTexture));
		tubes.at(i).setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::LINEAR, Tup2f{ 0, random(15, 25) }, random(1)));
		tubes.at(i).setPerturbation({ random(random(2)) });
		//tube.setColor({ .1, 0, 0, 1 });
		tubes.at(i).setDiffuseMaterial(1);
		tubes.at(i).setAmbientMaterial(0.05f);
		tubes.at(i).setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .5f);
		//tubes.at(i).loadBumpMapTexture("vascular3_normal2.jpg");
		tubes.at(i).setTextureScale({ 1, .05f});
		tubes.at(i).setSpecularMaterial(1);
		tubes.at(i).setShininess(34);
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
	scale(1.65);
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
	save("handForm.jpg", 4);
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