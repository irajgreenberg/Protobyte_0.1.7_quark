/*!  \brief  ProtoGeomComposite.cpp: Base class to Combine multiple ProtoGeoms
ProtoGeomComposite.cpp
Protobyte Library v02

Created by Ira on 8/30/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "ProtoGeomComposite.h"
#include "ProtoContext.h"


using namespace ijg;


ProtoGeomComposite::ProtoGeomComposite() {
	
	////trace("ctx =", ctx);
	t = Toroid(12, 12, 125, 45);
	t.setSpecularMaterial({ 1, 0.75, 1, 1 });
	t.setShininess(9);
	t.setDiffuseMap("ship_plate_rainbow.jpg");
	t.setBumpMap("ship_plate_rainbow.jpg");
	//ctx->init();
}

void ProtoGeomComposite::init() {
	ctx = ProtoContext::getContext();
	ctx->init();
}

void ProtoGeomComposite::display() {
	ctx->push();
	ctx->translate(-200, 200, 0);
	ctx->rotate(counter*2.1, Vec3(1, .2, 0));
	t.display();
	ctx->pop();

	ctx->push();
	ctx->translate(200, 200, 0);
	ctx->rotate(counter*1.2, Vec3(1, .75, 0));
	t.display();
	ctx->pop();

	ctx->push();
	ctx->translate(-200, -200, 0);
	ctx->rotate(counter*.5, Vec3(1, .05, 0));
	t.display();
	ctx->pop();

	ctx->push();
	ctx->translate(200, -200, 0);
	ctx->rotate(counter, Vec3(1, 0, 0));
	ctx->rotate(counter, Vec3(0, 1, 0));
	ctx->rotate(counter += 2, Vec3(0, 0, 1));
	t.display();
	ctx->pop();
}

