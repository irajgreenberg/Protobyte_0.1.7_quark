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
		partGeom = std::move(std::unique_ptr<ProtoRectangle>(new ProtoRectangle(Vec3(0), 1, 1, Col4(1, 1, 1, 1), icon)));
		//partGeom->setColor({ .1, 0, 0, 1 });
		//partGeom->setDiffuseMaterial(1);
		partGeom->setAmbientMaterial(0.05f);
		partGeom->setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
		partGeom->setSpecularMaterial(1);
		partGeom->setShininess(125);
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
	/*ctx->push();
	ctx->translate(position);
	ctx->scale(size);*/
	partGeom->display();
	//ctx->pop();
}



//void ProtoParticle::collide() {
//
//}
