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


#ifndef PROTO_VERLETBALL_H
#define        PROTO_VERLETBALL_H

#include "ProtoVector3.h"
#include "ProtoMath.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoVerletBall;
	typedef ProtoVerletBall VerletBall;

	// overloaded non-member ops
	Vec3f operator+(const ProtoVerletBall& lhs, const ProtoVerletBall& rhs);
	Vec3f operator-(const ProtoVerletBall& lhs, const ProtoVerletBall& rhs);

	class ProtoVerletBall {
		//private:
	public:
		Vec3f pos, posOld;
		Vec3f* pos_ptr;

		ProtoVerletBall();
		ProtoVerletBall(const Vec3f& pos);
		ProtoVerletBall(Vec3f* pos_ptr);


		//float dist(const ProtoVerletBall& b);

		void verlet();
		void verlet2();
		void verlet_p(); // alt name for nerlet2

		//getters / setters
		Vec3f getPos() const;
		Vec3f* getPos_ptr() const;
		void setPos(const Vec3f& pos);

		// overloaded member ops
		ProtoVerletBall& operator+=(const ProtoVerletBall& vb);
		ProtoVerletBall& operator-=(const ProtoVerletBall& vb);


	};


	//getters / setters

	inline Vec3f ProtoVerletBall::getPos() const {
		return pos;
	}

	inline Vec3f* ProtoVerletBall::getPos_ptr() const {
		return pos_ptr;
	}

	inline void ProtoVerletBall::setPos(const Vec3f& pos) {
		this->pos = pos;
	}

	inline ProtoVerletBall& ProtoVerletBall::operator+=(const ProtoVerletBall& vb) {
		pos += vb.pos;
		return *this;
	}

	inline ProtoVerletBall& ProtoVerletBall::operator-=(const ProtoVerletBall& vb) {
		pos -= vb.pos;
		return *this;
	}

	// non member ops

	inline Vec3f operator+(const ProtoVerletBall& lhs, const ProtoVerletBall& rhs) {
		return lhs.getPos() + rhs.getPos();
	}

	inline Vec3f operator-(const ProtoVerletBall& lhs, const ProtoVerletBall& rhs) {
		return lhs.getPos() - rhs.getPos();
	}
}

#endif        /* PROTO_VERLETBALL_H */