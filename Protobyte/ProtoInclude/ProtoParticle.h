#pragma once

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

#ifndef PROTO_PARTICLE_H
#define PROTO_PARTICLE_H

//#include "ProtoCore.h"
//#include <string.h>
//#include <iostream>
//#include <vector>
//#include "ProtoMath.h"
//#include <cmath>
//#include <cassert>
#include "ProtoVector3.h"
#include "ProtoColor4.h"
//#include <iostream>
#include <memory>
#include "ProtoContext.h"
#include "ProtoGeom3.h"
#include "ProtoRectangle.h"

// for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))

namespace ijg {

	// forward declaration and namespace safe short names
	class ProtoParticle;
	typedef ProtoParticle Particle;
	typedef ProtoParticle Part; // common usage
	
	class ProtoParticle {

	public:

		enum PartType {
			POINT,
			LINE,
			RECT,
			ELLIPSE,
			BOX,
			SPHERE
		};


		ProtoParticle();
		//ProtoParticle(const Vec& position);
		//ProtoParticle(const Vec& position, float radius);
		//ProtoParticle(const Vec& position, const Col4& col);
		//ProtoParticle(const Vec& position, float radius, const Col4& col);
		ProtoParticle(const Vec& position, const Vec& rotation, Dim3f size, PartType type, const std::string& icon);
		ProtoParticle(const Vec& position, const Vec& rotation, Dim3f size, PartType type, const Col4& col);
		
		void move();
		void display();

	/*	void collide();*/
		void setPosition(const Vec& position);
		Vec& getPosition();
		void setSpeed(const Vec& speed);
		Vec& getSpeed();
		void setJitter(const Vec& jitter);
		Vec& getJitter();
		void setSize(const Dim3f& sz);
		Dim3f& getSize();
		void setColor(const Col4& col);
		Col4& getColor();

		Vec position{ 0 }; // used by POINT
		

	private:
		
		Vec rotation{ 0 };
		Vec speed{ 0 };
		Vec jitter{ 0 };
		Dim3f size{ 0 };
		float radius{ 0.0f };
		Col4 col{ 0 };
		std::string icon;
		PartType type;
		float gravity{ -1.3f };
		float damping{ .789f };

		void init();


		// call transformations within the class 
		std::shared_ptr<ProtoContext> ctx;

		/*bool isIconified{ 0 };*/

		std::unique_ptr<Geom3> partGeom;

		// point buffer ids
		float ptPrims[7];
		GLuint vaoPtID, vboPtID;
		int stride{ 7 };
		int vertsDataSize{ sizeof(GLfloat) };
	};

	//inline
	inline void ProtoParticle::setPosition(const Vec& position) {
		if (type == POINT) {
			this->position = position;
		}
		else {
			partGeom->setPosition(position);
		}
	}

	inline Vec& ProtoParticle::getPosition() {
		if (type == POINT) {
			return position;
		} 
		// if not POINT or LINE type returns ProtoGeom3 type
		return partGeom->getPosition();
	}

	inline void ProtoParticle::setSpeed(const Vec& speed) {
		this->speed = speed;
	}

	inline Vec& ProtoParticle::getSpeed() {
		return speed;
	}

	inline void ProtoParticle::setJitter(const Vec& jitter) {
		this->jitter = jitter;
	}

	inline Vec& ProtoParticle::getJitter() {
		return jitter;
	}

	inline void ProtoParticle::setSize(const Dim3& sz) {
		if (type == POINT) {
			size = sz;
		}
		else {
			partGeom->setSize(sz);
		}
	}

	inline Dim3& ProtoParticle::getSize() {
		if (type == POINT) {
			return size;
		}
		return partGeom->getSize();
	}

	inline void ProtoParticle::setColor(const Col4& col) {
		this->col = col;
	}

	inline Col4& ProtoParticle::getColor() {
		return col;
	}

}  // END ijg namespace

#endif // PROTO_PARTICLE_H

