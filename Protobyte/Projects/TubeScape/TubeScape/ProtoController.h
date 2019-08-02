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

	int blockCount{ 900 };
	std::vector<ProtoBlock> geoScape;

};

#endif //__PROTOCONTROLLER_H__
