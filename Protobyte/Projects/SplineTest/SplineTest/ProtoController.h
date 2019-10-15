/*
Protobyte Library 0.1.6
Ira Greenberg 2016
*/

#ifndef __PROTOCONTROLLER_H__
#define __PROTOCONTROLLER_H__

#include <iostream>
#include "ProtoBaseApp.h"

using namespace ijg;

struct CubicPoly;
void InitCubicPoly(float x0, float x1, float t0, float t1, CubicPoly& p);
void InitCatmullRom(float x0, float x1, float x2, float x3, CubicPoly& p);
void InitNonuniformCatmullRom(float x0, float x1, float x2, float x3, float dt0, float dt1, float dt2, CubicPoly& p);
float VecDistSquared(const Vec3f& p, const Vec3f& q);
void InitCentripetalCR(const Vec3f& p0, const Vec3f& p1, const Vec3f& p2, const Vec3f& p3, CubicPoly& px, CubicPoly& py);

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

	

};

#endif //__PROTOCONTROLLER_H__
