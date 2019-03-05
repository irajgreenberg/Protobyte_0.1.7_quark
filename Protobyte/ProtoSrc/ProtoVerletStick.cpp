/*!  \brief  ProtoVerletStick.h: Verlet Stick class
ProtoVerletStick.h
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

This notice must be retained in any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "ProtoVerletStick.h"


namespace ijg {
	std::ostream& operator<< (std::ostream& out, const ProtoVerletStick& stick){
		out << "b1.pos: " << stick.b1->pos << ", b2.pos: " << stick.b2->pos << ", tension: " << stick.tension << ", elasticity: " << stick.elasticity;
		return out;
	}

	std::ostream& operator<< (std::ostream& out, const std::unique_ptr<ProtoVerletStick>& stick){
		out << "b1.pos: " << stick->b1->pos << ", b2.pos: " << stick->b2->pos << ", tension: " << stick->tension << ", elasticity: " << stick->elasticity;
		return out;
	}
}

using namespace ijg;


ProtoVerletStick::ProtoVerletStick() {
}

ProtoVerletStick::ProtoVerletStick(std::shared_ptr<VerletBall> b1, std::shared_ptr<VerletBall> b2, float tension, Tup2f elasticity) : b1(b1), b2(b2), tension(tension), elasticity(elasticity)
{
	//vecOrig = *(b2->getPos_ptr()) - *(b1->getPos_ptr());
	//len = b2->getPos_ptr()->dist(*b1->getPos_ptr());
	// trace("*(b1->getPos_ptr()) = " , *(b1->getPos_ptr()));
	// trace("*(b2->getPos_ptr()) = " , *(b2->getPos_ptr()));

	    vecOrig = b2->getPos() - b1->getPos();
	    len = b2->pos.dist(b1->pos);
}



void ProtoVerletStick::constrainLen() {
	//trace("Here in constrainLen");

	//for (int i = 0; i < 1; i++) {
	//	Vec3f delta = *b2->getPos_ptr() - *b1->getPos_ptr();
	//	float deltaLength = delta.mag();

	//	float difference = ((deltaLength - len) / deltaLength);

	//	*b1->pos_ptr += delta * elasticity.elem0 * tension * difference;
	//	*b2->pos_ptr -= delta * elasticity.elem1 * tension * difference;
	//}

	    for (int i = 0; i < 1; i++) {
	        Vec3f delta = b2->getPos() - b1->getPos();
	        float deltaLength = delta.mag();
	        
	        float difference = ((deltaLength - len) / deltaLength);
	        
	        b1->pos += delta * elasticity.elem0 * tension * difference;
	        b2->pos -= delta * elasticity.elem1 * tension * difference;
	    }

}

void ProtoVerletStick::display(){
	//    glDisable(GL_LIGHTING);
	//    glDisable(GL_TEXTURE_2D);
	//    glColor4f(.8, .8, .9, .175);
	glBegin(GL_LINE_STRIP);
	glVertex3f(b1->getPos_ptr()->x, b1->getPos_ptr()->y, b1->getPos_ptr()->z);
	glVertex3f(b2->getPos_ptr()->x, b2->getPos_ptr()->y, b2->getPos_ptr()->z);
	glEnd();
	//    glEnable(GL_TEXTURE_2D);
	//    glEnable(GL_LIGHTING);


	//    glColor3f(1, .5, 0);
	//    glBegin(GL_LINE_STRIP);
	//    glVertex3f(b1->getPos().x, b1->getPos().y, b1->getPos().z);
	//    glVertex3f(b2->getPos().x, b2->getPos().y, b2->getPos().z);
	//    glEnd();
}