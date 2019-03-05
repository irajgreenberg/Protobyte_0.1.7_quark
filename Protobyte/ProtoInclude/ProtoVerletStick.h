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

#ifndef PROTO_VERLETSTICK_H
#define PROTO_VERLETSTICK_H

// GL
#include <GLFW/glfw3.h> 

#include "ProtoVerletBall.h"
#include "ProtoTuple2.h"
#include <memory>

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoVerletStick;
	typedef ProtoVerletStick VerletStick;

	class ProtoVerletStick {
	private:
		std::shared_ptr<VerletBall> b1, b2;
		float tension;
		Vec3f vecOrig;
		float len;
		Tup2f elasticity;

	public:

		friend std::ostream& operator<< (std::ostream& out, const ProtoVerletStick& stick);
		friend std::ostream& operator<< (std::ostream& out, const std::unique_ptr<ProtoVerletStick>& stick);

		// constructors
		ProtoVerletStick();
		ProtoVerletStick(std::shared_ptr<VerletBall> _b1, std::shared_ptr<VerletBall> _b2, float tension, Tup2f elasticity = Tup2f(.5, .5));

		void nudgeB1(const Vec3f& val);
		void nudgeB2(const Vec3f& val);
		void constrainLen();
		void display();

		VerletBall& getB1();
		VerletBall& getB2() const;

	};

	inline VerletBall& ProtoVerletStick::getB1() {
		return *b1;
	}

	inline VerletBall& ProtoVerletStick::getB2() const {
		return *b2;
	}

	inline void  ProtoVerletStick::nudgeB1(const Vec3f& val){
		b1->pos += val;
	}
	inline void  ProtoVerletStick::nudgeB2(const Vec3f& val){
		b2->pos += val;
	}




}

#endif        /* PROTO_VERLETSTICK_H */