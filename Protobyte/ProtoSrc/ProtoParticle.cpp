// NOTE: something is screwy with my overloaded ops (Need to FIX)

/*!  \brief  PROTO_PARTICLE.h: Base Physics class (perhaps)
 ProtoParticle.h
 Protobyte Library v02

 class Created by Ira on 8/5/19.

 Protobyte Library Copyright (c) 2013 Ira Greenberg. All rights reserved.

 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.

 This notice must be retained in any source distribution.

 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */


#include "ProtoParticle.h"

using namespace ijg;


ProtoParticle::ProtoParticle() {
	//init();
}

ProtoParticle::ProtoParticle(const Vec& position, const Vec& rotation, Dim3f size, PartType type, const std::string& icon) :
	position(position), rotation(rotation), size(size), type(type), icon(icon) {
	init();
}

void ProtoParticle::move() {
	position += speed;
}

void ProtoParticle::init() {
	ctx = ProtoContext::getContext();
	
	switch (type) {
	case POINT:
		break;
	case LINE:
		break;
	case RECT:
		partGeom = std::make_unique<Geom3>(new ProtoRectangle(position, size.w, size.h, Col4(0), icon));
		break;
	case ELLIPSE:
		break;
	case BOX:
		break;
	case SPHERE:
		break;

		//default:
	// point is default
	}
}

void ProtoParticle::display() {
	partGeom->display();
}



//void ProtoParticle::collide() {
//
//}
