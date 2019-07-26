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

	int tubeCount{ 24 };
	int pointCount{ 30 };
	std::vector< std::vector<Vec3>> pts2D;
	std::vector<Spline> splines;
	std::vector <Tube> tubes;
	std::vector<std::string> textures {
		"jellySkin.jpg", 
		"meat01.jpg", 
		"humanSkin02.jpg", 
		"vascular.jpg", 
		"STG_Flesh//Diffuse_Maps//STG_Flesh_27-diffuse.jpg", 
		"STG_Flesh//Diffuse_Maps//STG_Flesh_22-diffuse.jpg" 
	};

};

#endif //__PROTOCONTROLLER_H__
