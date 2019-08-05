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


	plane = GroundPlane(Vec{ 0 }, Vec{ 0 }, Dim2f{}, Col4{ 1, 1, 1, 1 }, 10, 10);
	plane.setDiffuseMaterial(1);
	plane.setSpecularMaterial(1);
	plane.setShininess(15);
	for (int i = 0; i < blockCount; i++) {
		float h{};
		if (i % 27 == 0) {
			h = random(625, 1295);
		}
		else if (i % 329 == 0) {
			h = random(900, 2600);
		}
		else {
			h = random(2, 490);
		}

		geoScape.push_back(
			Block(
				Vec(
					random(-getWidth() * 1.5, getWidth() * 1.5),
					0,
					random(-2500)
				),
				{},
				Dim3(
					random(30, 260),
					h,
					random(30, 260)
				),
				Col4(.2, .2, .2, 1)
			)
		);

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
		particles.push_back({ 0, 1500, random(-2000,-300) });
		speed.push_back({ random(-14, 14), 0, random(-4, 4) });
		gravity.push_back(-.5);
		damping.push_back(.525);
		friction.push_back(.465);
	}

}

void ProtoController::run() {
	for (int i = 0; i < particleCount; i++) {
		speed.at(i).y += gravity.at(i);
		particles.at(i) += speed.at(i);
		if (collide(particles.at(i))) {
			speed.at(i).y *= -1;
			speed.at(i).y *= damping.at(i);
			speed.at(i).x *= friction.at(i);
			speed.at(i).z *= friction.at(i);

		}
	}

}

bool ProtoController::collide(Vec& p) {
	for (int i = 0; i < blockCount; i++) {
		if (p.y < geoScape.at(i).getPosition().y + geoScape.at(i).getSize().h / 2 + particleRadius &&
			p.x > geoScape.at(i).getPosition().x - geoScape.at(i).getSize().w / 2 &&
			p.x < geoScape.at(i).getPosition().x + geoScape.at(i).getSize().w / 2 &&
			p.z > geoScape.at(i).getPosition().z - geoScape.at(i).getSize().d / 2 &&
			p.z < geoScape.at(i).getPosition().z + geoScape.at(i).getSize().d / 2 &&
			p.y > geoScape.at(i).getPosition().y + geoScape.at(i).getSize().h / 16) {

			p.y = geoScape.at(i).getPosition().y + geoScape.at(i).getSize().h / 2 + particleRadius;

			return true;
		}
		else if (p.y < plane.getPosition().y + particleRadius) {
			p.y = plane.getPosition().y + particleRadius;

			return true;
		}

		/*if (geoScape.at(i).getPosition().dist(p) < 125) {
			return true;
		}*/
	}
	return false;
}

void ProtoController::display() {
	background(0);
	arcBallBegin();
	
	translate(0, -500, 0);
	
	// ground plane
	push();
	scale(5000, 1, 5000);
	//rotate(PI, { 1, 0, 0 });
	plane.display();
	pop();

	// geometric block
	
	for (int i = 0; i < blockCount; i++) {
		push();
		//translate(pos.at(i));
		//scale(sz.at(i));
		geoScape.at(i).display();
		pop();
	}

	// particles
	for (int i = 0; i < particleCount; i++) {
		push();
		translate(particles.at(i));
		strokeWeight(particleRadius*2);
		stroke(1, .5, 0, 1);
		//if(abs(speed.at(i).y)<.01)
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