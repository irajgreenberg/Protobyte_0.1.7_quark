/*!  \brief  ProtoVerletBall.h: Verlet Ball implementation
Protobyte Library v02

Created by Ira on 6/5/13.
Copyright (c) 2013 Ira Greenberg. All rights reserved.

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

#include "ProtoVerletBall.h"


using namespace ijg;

ProtoVerletBall::ProtoVerletBall() {
}

ProtoVerletBall::ProtoVerletBall(const Vec3f& pos) {
	this->pos = pos;
	posOld = pos;
}

ProtoVerletBall::ProtoVerletBall(Vec3f* pos_ptr) {
	this->pos_ptr = pos_ptr;
	posOld = *pos_ptr;
}



//float VerletBall::dist(const VerletBall& b) {
//
//}

void ProtoVerletBall::verlet() {
	Vec3f posTemp = pos;
	pos += (pos - posOld);
	//std::cout << "in VerletBall verlet(), pos = " << pos << std::endl;
	posOld = posTemp;
}

void ProtoVerletBall::verlet2() {
	Vec3f posTemp = *pos_ptr;
	*pos_ptr += (*pos_ptr - posOld);
	posOld = posTemp;
}

// better name eventually–if I even need this.
void ProtoVerletBall::verlet_p() {
	Vec3f posTemp = *pos_ptr;
	*pos_ptr += (*pos_ptr - posOld);
	//std::cout << "in VerletBall verlet(), pos = " << pos << std::endl;
	posOld = posTemp;
}