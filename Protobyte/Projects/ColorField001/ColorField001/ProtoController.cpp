/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#include "ProtoController.h"

void ProtoController::init() {
	setSize(Dim2i(900, 200));
	float t = 0.0f;
	float r = 100.0f;
	for (int i = 0; i < count; ++i) {
		if (i < 1000) {
			// blue
			cols.push_back(Col4(random(.25), random(.3), random(.75, 1), random(.35, .7)));
			pts.push_back(
				Vec(random(-400, 200),
					random(-400, 200),
					random(-400, 200))
			);
		}
		else if (i < 2000) {
			//purple
			cols.push_back(Col4(random(.75, 1), random(.1, .2), random(.75, 1), random(.35, .7)));
			pts.push_back(
				Vec(random(-100, 400),
					random(-100, 400),
					random(-400, 200))
			);

		}
		else if (i < 3000) {
			//cyan
			cols.push_back(Col4(random(.125, .3), random(.4, .65), random(.75, 1), random(.35, .7)));
			pts.push_back(
				Vec(random(-400, 400),
					random(-400, 400),
					random(-400, 200))
			);

		}
		else if (i < 5000) {
			//orange-yellow
			cols.push_back(Col4(random(.85, 1), random(.45, .8), random(.1, .2), random(.35, .7)));
			pts.push_back(
				Vec(random(-400, 400),
					random(-400, 400),
					random(-400, 200))
			);

		}
		else if (i < 9000) {
			// ambient red noise
			cols.push_back(Col4(random(.85, 1), random(.05, .1), random(.05, .1), random(.25, .4)));
			pts.push_back(
				Vec(random(-500, 500),
					random(-500, 500),
					random(-400, 100))
			);

		}
		else {
			// white
			cols.push_back(Col4(1, 1, 1, random(.55,.85)));
			pts.push_back(
				Vec(random(-500, 500),
					random(-500, 500),
					random(-400, 100))
			);
		}
	}
	//for (int i = 0; i <count; ++i) {
	//	cols.push_back(Col4(random(1), random(1), random(1), 1.0));
	//	pts.push_back(
	//		Vec(cos(t)*r, sin(t)*r, 0)
	//	);
	//	t += TWO_PI / count;
	//}


}

void ProtoController::run() {
}

void ProtoController::display() {
	background(1);
	noFill();
	
	beginArcBall();

	push();
	//translate(-100, 0, 0);
	curveDetail(30);
	curveBias(0);
	beginPath();
	strokeWeight(3);
	int i{ 0 };
	for (Vec v : pts) {
		/*if (i < 5000) {
			strokeWeight(2);
		}
		else {
			strokeWeight(6);
		}*/
		stroke(cols.at(i));
		curveVertex(v);
		i++;
	}
	endPath(CLOSE_SMOOTH);
	pop();

	/*translate(200, 0, 0);
	beginArcBall();
	curveDetail(0);
	curveBias(100);
	beginPath();
	for (Vec v : pts) {
		curveVertex(v);
	}
	endPath(CLOSE);*/

	endArcBall();
}

// Key and Mouse Events
void ProtoController::keyPressed() {
	// 79 is 'o' (output) key
	if (key == 79) {
		save("colorField001", 6);
	}
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