/*!  \brief  ProtoFrenetFrame.cpp: Frenet frame class for parallel transport correction
 ProtoFrenetFrame.cpp
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


#include "ProtoFrenetFrame.h"
#include <iostream>



namespace ijg {

    std::ostream& operator<<(std::ostream& out, const ProtoFrenetFrame& frame) {
        std::cout << "T = " << frame.getT() <<", B = " << frame.getB()<<", N = " << frame.getN();
        return out;
    }
}

using namespace ijg;

ProtoFrenetFrame::ProtoFrenetFrame() {
}

ProtoFrenetFrame::ProtoFrenetFrame(const Vec3f& p, const Vec3f& T, const Vec3f& B, const Vec3f& N) :
p(p), T(T), B(B), N(N) {
}

ProtoFrenetFrame::ProtoFrenetFrame(const Vec3f TBN[3]) {
    T = TBN[0];
    B = TBN[1];
    N = TBN[2];
}

ProtoFrenetFrame::ProtoFrenetFrame(Vec3f v0, Vec3f v1, Vec3f v2) :
	v0{ v0 }, v1{ v1 }, v2{ v2 } {
	init();
}

void ProtoFrenetFrame::init() {
	// calulate frame and define vector TNB
	
	// Used for 1st deriviatve 
	Vec3f vel = v1 - v0;
	vel.normalize();

	// Used for 2nd deriviatve to calculate Tangent vector
	TNB.at(0) = v2 - v0;
	TNB.at(0).normalize();

	// (v' x v'')cross product to calculate Binormal vector
	TNB.at(2) = TNB.at(0).cross(vel);
	TNB.at(2).normalize();

	// (T x B)cross product to calculate Normal vector
	TNB.at(1) = TNB.at(2).cross(TNB.at(0));
	TNB.at(1).normalize();

	// Required for displaying Frenet Frame
	TPrims.push_back(TNB.at(0).x);
	TPrims.push_back(TNB.at(0).y);
	TPrims.push_back(TNB.at(0).z);
	TPrims.push_back(0.0f);
	TPrims.push_back(0.0f);
	TPrims.push_back(0.0f);
	TPrims.push_back(0.0f);

	NPrims.push_back(TNB.at(1).x);
	NPrims.push_back(TNB.at(1).y);
	NPrims.push_back(TNB.at(1).z);
	NPrims.push_back(0.0f);
	NPrims.push_back(0.0f);
	NPrims.push_back(0.0f);
	NPrims.push_back(0.0f);
	
	BPrims.push_back(TNB.at(2).x);
	BPrims.push_back(TNB.at(2).y);
	BPrims.push_back(TNB.at(2).z);
	BPrims.push_back(0.0f);
	BPrims.push_back(0.0f);
	BPrims.push_back(0.0f);
	BPrims.push_back(0.0f);
}


void ProtoFrenetFrame::display(float length, float strokeWeight, Col4f TCol, Col4f NCol, Col4f BCol) {
	
	for (int i = 0; i < stride; i++) {
		if (i < 3) {
			TPrims.at(i) *= length;
			NPrims.at(i) *= length;
			BPrims.at(i) *= length;
		}
		else {
			TPrims.at(i) = TCol[i - 3];
			NPrims.at(i) = NCol[i - 3];
			BPrims.at(i) = BCol[i - 3];
		}
	}


	glBindVertexArray(vaoVertsID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboVertsID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * TPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &TPrims[0]); // upload the data

	glPointSize(strokeWeight);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // do I need this anymore?

	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glDrawArrays(GL_LINES, 0, TPrims.size() / stride);

	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	// Disable VAO
	glBindVertexArray(0);
}