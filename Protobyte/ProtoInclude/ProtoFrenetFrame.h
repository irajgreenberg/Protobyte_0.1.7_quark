/*!  \brief  ProtoFrenetFrame.h: Frenet frame class for parallel transport correction
Moving frame implmentation that calculates localized curve orientation
using (x - x-1) for f' and (x+1 - x-1) for f'' calucations.
T = f'' / ||f''||
N = f' x T / ||f' x T||
B = T x N / ||T x N||

 ProtoFrenetFrame.h
 Protobyte Library v02

 Created by Ira on 7/23/13.
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
 This class is templated to allow for varied single collection types
 This class is part of the group common (update)
 \sa NO LINK
 */

#ifndef PROTO_FRENET_FRAME_H
#define PROTO_FRENET_FRAME_H

#include "ProtoVector3.h"
#include "ProtoColor4.h"
#include "ProtoVector4.h"
#include "ProtoShader.h"
#include "ProtoContext.h"
#include <iostream>

 // for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))

namespace ijg {

	class ProtoFrenetFrame;
	typedef ProtoFrenetFrame FrenetFrame;


	class ProtoFrenetFrame {
	private:
		//Vec3f p{}, T{}, N{}, B{};
		Vec3f v0{}, v1{}, v2{};
		std::vector<Vec3f> TNB;

		// Vars and functions for rendering using shader

		/**
		* initialize shader handles and uniforms for rendering
		*/
		void initBuffers();

		/**
		* stride to move through interleaved primitives(x, y, z, r, g, b, a)
		*/
		int stride = 7;

		/**
		* std::vector of interleaved curve primitives (x, y, z, r, g, b, a).
		*/
		std::vector<float> TPrims;
		std::vector<float> NPrims;
		std::vector<float> BPrims;
		std::vector<float> frenetPrims;

		/**
		 * Handle to verts VAO
		*/
		GLuint vaoFrameID;

		/**
		* Handle to verts VBO
		*/
		GLuint vboFrameID;

		/**
		* Handle to shader to disable/enable lighting for curve path/curve vertices rendering
		*/
		GLuint lightRenderingFactors_U;

	public:
		friend std::ostream& operator<<(std::ostream& out, const ProtoFrenetFrame& frame);
		ProtoFrenetFrame();
		ProtoFrenetFrame(const Vec3f& v1, const Vec3f& T, const Vec3f& N, const Vec3f& B);
		/*ProtoFrenetFrame(const Vec3f& T, const Vec3f& N, const Vec3f& B);
		ProtoFrenetFrame(const Vec3f& v1, const Vec3f TNB[3]);*/

		// new and improved approach
		ProtoFrenetFrame(Vec3f v0, Vec3f v1, Vec3f v2);

		void init();

		Vec3f getT() const;
		Vec3f getN() const;
		Vec3f getB() const;
		std::vector<Vec3f> getTNB() const;

		void setT(const Vec3f& T);
		void setN(const Vec3f& N);
		void setB(const Vec3f& B);
		void setTNB(const std::vector<Vec3f>& TNB);

		void display(float length = 25, float strokeWeight = 4,
			Col4f TCol = { 1.0f, 0.0f, 0.0f, 1.0f },
			Col4f NCol = { 0.0f, 0.0f, 1.0f, 1.0f },
			Col4f BCol = { 0.0f, 1.0f, 0.0f, 1.0f }
		);
	};

	// INlinne getter/setter implementations
	inline Vec3f FrenetFrame::getT() const {
		return TNB[0];
	}

	inline Vec3f FrenetFrame::getN() const {
		return TNB[1];
	}

	inline Vec3f FrenetFrame::getB() const {
		return TNB[2];
	}

	inline std::vector<Vec3f> FrenetFrame::getTNB() const {
		return TNB;
	}

	inline void FrenetFrame::setT(const Vec3f& T) {
		TNB[0] = T;
	}
	
	inline void FrenetFrame::setN(const Vec3f& N) {
		TNB[1] = N;
	}
	
	inline void FrenetFrame::setB(const Vec3f& B) {
		TNB[2] = B;
	}

	inline void FrenetFrame::setTNB(const std::vector<Vec3f>& TNB) {
		this->TNB = TNB;
	}
}

#endif // PROTO_FRENET_FRAME_H
