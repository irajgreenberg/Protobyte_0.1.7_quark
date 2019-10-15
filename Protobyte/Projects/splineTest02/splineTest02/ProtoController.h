/*
Protobyte Library 0.1.6
Ira Greenberg 2016
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


	//new custom members
	//bool areTerminalsReached{ 1 };
	//bool isCurveClosed{ 0 };
	//float ptCount = 30.0f;
	////set from 0-1
	//float alpha = .5f;
	//void catmulRom();
	//float getT(float t, Vec3f p0, Vec3f p1);
	//int controlPtCount = 36;
	//std::vector<Vec3f> pts;
	//std::vector<Vec3f> newPts;
	int ptCount = 23;
	std::vector<Vec3f> vecs;
	Spline3 s, s2, s3;
	Tube tendril;

};

#endif //__PROTOCONTROLLER_H__
