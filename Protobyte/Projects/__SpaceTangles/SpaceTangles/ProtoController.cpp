/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#include "ProtoController.h"


void ProtoController::init() {
	//setShadowsOn(1);
	// shoots
	int ptCount{ 40 };
	std::vector<Vec3> pts;
	float ht = 1000.0f;
	float htInterval = ht/ ptCount;
	float theta{ 0 }, phi{ 0 };
	for (int i = 0; i < ptCount; i++) {
		float r = 200;
		//r = i + 12 + random(3, 9);
		float x = sin(theta) * (r + i);
		float y = -ht/2 + htInterval * i;
		float z = cos(theta) * (r + i);
		/*float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;*/
		//pts.push_back(Vec3f(x, y, z));
		pts.push_back(Vec3f(random(-700,700), random(-700,700), random(-600,600)));
		//phi += TWO_PI / ptCount * random(1.4, 6);
		theta += TWO_PI / ptCount;
	}
<<<<<<< HEAD
	Spline3 path(pts, 15, true, 1.0);


	tangles = Tube(path, 4, 16, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(7.75, 35.5), 80), false, "STG_Flesh/Diffuse_Maps/STG_Flesh_15-diffuse02.jpg");
	tangles.setDiffuseMaterial({ 1.0f, 1, 1 });
	tangles.setAmbientMaterial(0.05f);
	tangles.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_15-normal.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tangles.setTextureScale({ 1.1, .01f });
	
=======
	path = Spline3(pts, 12, true, 1.0);


	tangles = Tube(path, 4, 18, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL,
		Tup2(35.75, 99.5), 2), true, "STG_Flesh/Diffuse_Maps/STG_Flesh_27-diffuse.jpg");
	tangles.setDiffuseMaterial({ 1.0f, 1, 1 });
	tangles.setAmbientMaterial(0.05f);
	tangles.setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tangles.setTextureScale({ 1, 0.3f });
>>>>>>> tmp
	tangles.setSpecularMaterial({ 1, 1, 1 });
	tangles.setShininess(40);


	// dot tangles
	ptCount = 5;
	pts.clear();
	theta = phi = 0;
	for (int i = 0; i < ptCount; i++) {
		float r = 200;
		//r = i + 12 + random(3, 9);
		float x = sin(theta) * (r + i);
		float y = 0;
		float z = cos(theta) * (r + i);
		/*float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;*/
		//pts.push_back(Vec3f(x, y, z));
		pts.push_back(Vec3f(random(-700, 700), random(-700, 700), random(-600, 600)));
		//phi += TWO_PI / ptCount * random(1.4, 6);
		theta += TWO_PI / ptCount;
	}
	path = Spline3(pts, 15, true, 1.0);


	tangles2 = Tube(path, 4, 16, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL_RANDOM,
		Tup2(17.75, 50.5), 80), false, "yellow.jpg");
	tangles2.setDiffuseMaterial({ 1.0f, 1, 1 });
	tangles2.setAmbientMaterial(0.05f);
	tangles2.setBumpMap("skin03.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tangles2.setTextureScale({ 1.1, .01f });

	tangles2.setSpecularMaterial({ 1, 1, 1 });
	tangles2.setShininess(40);



	// wireframe tangles
	ptCount = 5;
	pts.clear();
	theta = phi = 0;
	for (int i = 0; i < ptCount; i++) {
		float r = 200;
		//r = i + 12 + random(3, 9);
		float x = sin(theta) * (r + i);
		float y = 0;
		float z = cos(theta) * (r + i);
		/*float tx = x;
		float ty = cos(phi) * y - sin(phi) * z;
		float tz = sin(phi) * y + cos(phi) * z;*/
		//pts.push_back(Vec3f(x, y, z));
		pts.push_back(Vec3f(random(-700, 700), random(-700, 700), random(-600, 600)));
		//phi += TWO_PI / ptCount * random(1.4, 6);
		theta += TWO_PI / ptCount;
	}
	path = Spline3(pts, 15, true, 1.0);


	tangles3 = Tube(path, 4, 16, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL_RANDOM,
		Tup2(7.75, 65.5), 80), false, "reptile2_invert.jpg");
	tangles3.setDiffuseMaterial({ 1.0f, 1, 1 });
	tangles3.setAmbientMaterial(.87f);
	tangles3.setBumpMap("reptile2_invert.jpg", 1.0f);
	//tube.loadBumpMapTexture("vascular3_normal2.jpg");
	tangles3.setTextureScale({ 351.1, .01f });
	tangles3.setSpecularMaterial({ 1, 1, 1 });
	tangles3.setShininess(22);
}

void ProtoController::run() {
}

void ProtoController::display() {
	background({ 1 });
	//stroke({ 0,0,0,1 });
	setLight(0, Vec3(0, 0, 100), { .8, .8, .6 });
	setLight(1, Vec3(-200, 200, 100), { .5, .8, .8});
	beginArcBall();
<<<<<<< HEAD
	scale(.11f);
	int i = 0;
	
	push();
	
	tangles.display();
	tangles2.display(POINTS, 4);
	tangles3.display(WIREFRAME, 1.5);
=======
	scale(.18f);
	int i = 0;
	
	push();
	tangles.display(WIREFRAME, 1);
	//path.display();
>>>>>>> tmp
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
	save("Tendrils", 4);
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