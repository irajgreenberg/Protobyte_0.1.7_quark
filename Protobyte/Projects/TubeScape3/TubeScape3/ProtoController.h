/*
Protobyte Library 0.1.7
Ira Greenberg 2019
*/

#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"

using namespace ijg;

class ProtoController : public ProtoBaseApp {

public:
	void init();
	void run();
	void display();

	// Key and Mouse Events
	void keyPressed();
	void mousePressed();
	void mouseRightPressed();
	void mouseReleased();
	void mouseRightReleased();
	void mouseMoved();
	void mouseDragged();

	// Window Events
	void onResized();
	void onClosed();

	int tubeCount{ 1 };
	std::vector<Spline3> splines;
	std::vector<Tube> tubes;

	int blockCount{ 300 };
	std::vector<ProtoBlock> geoScape;

	std::vector<Vec> pos;
	std::vector<Dim3> sz;
	GroundPlane plane;

	// particles and physics
	int particleCount{500};
	vect<Vec> particles;
	float particleRadius{ 200 };
	vect<Vec> speed;
	vect<float> damping;
	vect<float> gravity;
	vect<float> friction;
	bool collide(Particle& p);
	vect<Particle> parts;




};

#endif //__PROTOCONTROLLER_H__
