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

	int count{ 3000 };
	std::vector<Vec> pts;
	std::vector<Col4> cols;


	//int count2{ 12 };
	//std::vector<Vec> pts2;

	//int count3{ 12 };
	//std::vector<Vec> pts3;
};

#endif //__PROTOCONTROLLER_H__
