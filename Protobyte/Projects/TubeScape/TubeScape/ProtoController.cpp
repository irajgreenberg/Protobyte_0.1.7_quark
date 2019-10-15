/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	//shadowsOn();
	setLight(0, { -400, -200, 500 }, { 1, 1, 1 });
	float theta{ 0.0f }, theta2{ 0 };
	float r{ 240.0f };
	//float theta2{ 0 };

	//for (int i = 0; i < tubeCount; i++) {

	//	// generate points that will be consumed by Spline
	//	int pointCount{ (int)random(20, 30) };
	//	std::vector<Vec3> pts;
	//	for (int j = 0; j < pointCount; j++) {
	//		pts.push_back({
	//			cos(theta) * (getWidth() / 1.3f), //x
	//			-600+sin(theta2) * 125,  //y
	//			sin(theta ) * (getWidth() / 5.3f)  //z
	//			});
	//		theta += TWO_PI * 2 / pointCount;
	//		theta2 += PI / 20;
	//	}

	//	//create spline
	//	splines.push_back(Spline3(pts, 5, false));

	//	// create Tubes
	//	tubes.push_back(Tube(splines.at(i), 8, 18, false, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg"));
	//	tubes.at(i).setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f{ 10, 24 }, 4));
	//	tubes.at(i).setPerturbation({ random(3.2), random(1.5), random(1.2) });
	//	//tube.setColor({ .1, 0, 0, 1 });
	//	//tube.setDiffuseMaterial(1);
	//	////tube.setAmbientMaterial(0.05f);
	//	tubes.at(i).setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
	//	////tube.loadBumpMapTexture("vascular3_normal2.jpg");
	//	tubes.at(i).setTextureScale({ 1.0f, 0.03f });
	//	tubes.at(i).setSpecularMaterial(1);
	//	tubes.at(i).setShininess(125);
	//}

	plane = GroundPlane(Vec{0}, Vec{0}, Dim2f{},Col4{ 1, 1, 1, 1},10, 10);
	plane.setDiffuseMaterial(1);
	plane.setSpecularMaterial(1);
	plane.setShininess(15);
	for (int i = 0; i < blockCount; i++) {
		pos.push_back(Vec(random(-getWidth()*1.5, getWidth()*1.5),
			0,
			random(-4500)
		));
		float h{};
		if (i % 27 == 0) { 
			h = random(625, 1295); 
		}
		else if (i % 329 == 0) {
			h = random(900, 2600);
		} else {
			h = random(2, 490);
		}
		sz.push_back(Dim3(
			random(60, 460),
			h,
			random(60, 460)
		));
	}

	for (int i = 0; i < 1; i++) {
		geoScape.push_back(
			Block(
				{},
				{},
				{},
				Col4(.2, .2, .2, 1))
		);

		//	tubes.push_back(Tube(splines.at(i), 8, 18, false, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg"));
		//geoScape.at(i).setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f{ 10, 24 }, 4));
		//geoScape.at(i).setPerturbation({ random(3.2), random(1.5), random(1.2) });
		//geoScape.at(i).setColor({ .1, 0, 0, 1 });
		geoScape.at(i).setDiffuseMaterial(1);
		geoScape.at(i).setAmbientMaterial(0.0f);
		//geoScape.at(i).setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
		//geoScape.at(i).loadBumpMapTexture("vascular3_normal2.jpg");
		geoScape.at(i).setTextureScale({ 1.0f, 1.0f });
		geoScape.at(i).setSpecularMaterial(1);
		geoScape.at(i).setShininess(70);

	}

	// particles
	for (int i = 0; i < particleCount; i++) {
		particles.push_back({0, 1500, random(-1000,-200)});
		speed.push_back({random(-4, 4), 0, random(-4, 4) });
		gravity.push_back(-.5);
		damping.push_back(.925);
		friction.push_back(.965);
	}

}

void ProtoController::run() {
	for (int i = 0; i < particleCount; i++) {
		speed.at(i).y += gravity.at(i);
		particles.at(i) += speed.at(i);
		if (collide(particles.at(i))) {
			speed.at(i).y *= -1;
		}
	}

}

bool ProtoController::collide(const Vec& p) {
	for (int i = 0; i < blockCount; i++) {
		if (pos.at(i).dist(p) < 125) {
			return true;
		}
	}
	return false;
}

void ProtoController::display() {
	background(0);
	arcBallBegin();
	
	// ground plane
	push();
	translate(0, -500, 0);
	scale(5000, 1, 5000);
	//rotate(PI, { 1, 0, 0 });
	plane.display();
	pop();

	// geometric block
	translate(0, -500, 0);
	for (int i = 0; i < blockCount; i++) {
		push();
		translate(pos.at(i));
		scale(sz.at(i));
		geoScape.at(0).display();
		pop();
	}

	// particles
	for (int i = 0; i < particleCount; i++) {
		push();
		translate(particles.at(i));
		strokeWeight(5);
		stroke(1, .5, 0, 1);
		point(0, 0, 0);
		pop();
		/*gravity.push_back(-.03);
		damping.push_back(.925);
		friction.push_back(.965);*/
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