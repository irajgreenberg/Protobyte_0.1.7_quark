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
	
	class ProtoParticle  {

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
		
		void move();
		void display();

	/*	void collide();*/
		void setPosition(const Vec& position);
		Vec& getPosition();
		void setSpeed(const Vec& speed);
		Vec& getSpeed();
		void setJitter(const Vec& jitter);
		Vec& getJitter();
		void setRadius(float radius);
		float getRadius();
		void setColor(const Col4& col);
		Col4& getColor();

		

	private:
		Vec position{ 0 };
		Vec rotation{ 0 };
		Vec speed{ 0 };
		Vec jitter{ 0 };
		Dim3f size{ 0 };
		float radius{ 0.0f };
		Col4 col{ 0 };
		std::string icon;
		PartType type;
		float gravity{ .03f };
		float damping{ .789f };

		void init();


		// call transformations within the class 
		std::shared_ptr<ProtoContext> ctx;

		/*bool isIconified{ 0 };*/

		std::unique_ptr<Geom3> partGeom;
	};

	//inline
	inline void ProtoParticle::setPosition(const Vec& position) {
		this->position = position;
	}

	inline Vec& ProtoParticle::getPosition() {
		return position;
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

	inline void ProtoParticle::setRadius(float radius) {
		this->radius = radius;
	}

	inline float ProtoParticle::getRadius() {
		return radius;
	}

	inline void ProtoParticle::setColor(const Col4& col) {
		this->col = col;
	}

	inline Col4& ProtoParticle::getColor() {
		return col;
	}

}  // END ijg namespace

#endif // PROTO_PARTICLE_H

