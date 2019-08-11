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

	
	plane = GroundPlane(Vec( 0, 0, -100 ), Vec{ 0 }, Dim2f( 5000, 3000 ), Col4{ .2, .2, .2, 1 }, 10, 10);
	plane.setDiffuseMaterial(1);
	plane.setSpecularMaterial(1);
	plane.setShininess(15);
	
	for (int i = 0; i < blockCount; i++) {
		float h{};
		if (i % 27 == 0) {
			h = random(5, 875);
		}
		else if (i % 329 == 0) {
			h = random(560, 945);
		}
		else {
			h = random(30, 295);
		}

		geoScape.push_back(
			Block(
				//pos
				Vec(
					random(-1500, 1500),
					0,
					random(-1300, 500)
				),
				//rot
				{},
				//size
				Dim3(
					random(20, 230),
					h,
					random(20, 230)
				),
				Col4(.5, .3, .25, 1)
			)
		);

		//geoScape.at(i).setTransFuncObj(ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f{ 10, 24 }, 4));
		//geoScape.at(i).setPerturbation({ random(3.2), random(1.5), random(1.2) });
		//geoScape.at(i).setColor({ .1, 0, 0, 1 });
		geoScape.at(i).setDiffuseMaterial({ .25, .25, .25, 1 });
		geoScape.at(i).setAmbientMaterial(0.0f);
		//geoScape.at(i).setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
		//geoScape.at(i).loadBumpMapTexture("vascular3_normal2.jpg");
		geoScape.at(i).setTextureScale({ 1.0f, 1.0f });
		geoScape.at(i).setSpecularMaterial(1);
		geoScape.at(i).setShininess(70);

		geoScape.at(i).setRegistration(Block::BOTTOM);
	}


	// particles
	for (int i = 0; i < particleCount; i++) {
		parts.push_back(
			Particle(
				Vec{ random(-400, 400), 900, random(-1000, 0) },
				Vec{ 0,0,0 }, 
				Dim3f(20, 20, 0),
				Particle::RECT, 
				"iraWrapped_low.jpg"
			));

		parts.at(i).setSpeed(Vec( random(-2, 2), 0, random(-1, 1) ));
		gravity.push_back(-.85);
		damping.push_back(random(.55, .65));
		friction.push_back(.565);


		//particles.push_back({ 0, 1500, random(-2000,-300) });
		//speed.push_back({ random(-14, 14), 0, random(-4, 4) });
		//gravity.push_back(-.5);
		//damping.push_back(.525);
		//friction.push_back(.465);
	}

}

void ProtoController::run() {
	for (int i = 0; i < particleCount; i++) {
		parts.at(i).move();
		/*parts.at(i).getSpeed().y += gravity.at(i);
		parts.at(i).getPosition() += parts.at(i).getSpeed();*/
		if (collide(parts.at(i))) {
			parts.at(i).getSpeed().y *= -1;
			parts.at(i).getSpeed().y *= damping.at(i);
			parts.at(i).getSpeed().x *= friction.at(i);
			parts.at(i).getSpeed().z *= friction.at(i);

		}
		
	}
	
}

bool ProtoController::collide(Particle& p) {
	//trace("p = ", p);
	for (int i = 0; i < blockCount; i++) {
		if (p.getPosition().y < geoScape.at(i).getPosition().y + geoScape.at(i).getSize().h + p.getSize().h / 2 &&
			p.getPosition().x > geoScape.at(i).getPosition().x - geoScape.at(i).getSize().w / 2 &&
			p.getPosition().x < geoScape.at(i).getPosition().x + geoScape.at(i).getSize().w / 2 &&
			p.getPosition().z > geoScape.at(i).getPosition().z - geoScape.at(i).getSize().d / 2 &&
			p.getPosition().z < geoScape.at(i).getPosition().z + geoScape.at(i).getSize().d / 2 &&
			p.getPosition().y > geoScape.at(i).getPosition().y + geoScape.at(i).getSize().h / 16) {

			p.getPosition().y = geoScape.at(i).getPosition().y + geoScape.at(i).getSize().h + p.getSize().h / 2;

			return true;
		}
		else if (p.getPosition().y < plane.getPosition().y + p.getSize().h / 2) {
			p.getPosition().y = plane.getPosition().y + p.getSize().h / 2;
			return true;
		}

		//	/*if (geoScape.at(i).getPosition().dist(p) < 125) {
		//		return true;
		//	}*/
		//}
		//return false;
	}

	//trace("p.getRadius()*2=", p.getRadius() * 2);
		/*if (p.getPosition().y < plane.getPosition().y + p.getSize().h/2) {
			p.getPosition().y = plane.getPosition().y + p.getSize().h/2;
			return true;
		}*/
	return false;
}

void ProtoController::display() {
	background(0);
	arcBallBegin();

	translate(0, -500, -400);

	// ground plane
	plane.display();

	// geometric block
	for (int i = 0; i < blockCount; i++) {
		geoScape.at(i).display();
	}

	// particles
	for (int i = 0; i < particleCount; i++) {
		parts.at(i).display();

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