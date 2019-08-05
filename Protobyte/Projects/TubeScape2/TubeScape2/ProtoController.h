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

	int blockCount{ 800 };
	std::vector<ProtoBlock> geoScape;

	std::vector<Vec> pos;
	std::vector<Dim3> sz;
	GroundPlane plane;

	// particles and physics
	int particleCount{ 2000 };
	vect<Vec> particles;
	int particleRadius{ 6 };
	vect<Vec> speed;
	vect<float> damping;
	vect<float> gravity;
	vect<float> friction;
	bool collide(Vec& p);




};

#endif //__PROTOCONTROLLER_H__
