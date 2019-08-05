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


ProtoParticle::ProtoParticle(){
}

ProtoParticle::ProtoParticle(const Vec& position) :
	position(position) {

}
ProtoParticle::ProtoParticle(const Vec& position, float radius) :
	position(position), radius(radius) {

}
ProtoParticle::ProtoParticle(const Vec& position, const Col4& col) :
	position(position), col(col) {

}
ProtoParticle::ProtoParticle(const Vec& position, float radius, const Col4& col) :
	position(position), radius(radius), col(col) {
}

ProtoParticle::ProtoParticle(const Vec& position, float radius, const std::string& icon) :
	position(position), radius(radius), icon(icon) {
}


void ProtoParticle::move() {
	position += speed;

}

void ProtoParticle::display() {
	ProtoContext::getContext()->push();
	ProtoContext::getContext()->translate(position);
	ProtoContext::getContext()->pop();

}
//void ProtoParticle::collide() {
//
//}
