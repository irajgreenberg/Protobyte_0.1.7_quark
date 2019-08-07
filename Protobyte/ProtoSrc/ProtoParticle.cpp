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
	init();
}

ProtoParticle::ProtoParticle(const Vec& position) :
	position(position) {
	init();
}
ProtoParticle::ProtoParticle(const Vec& position, float radius) :
	position(position), radius(radius) {
	init();
}
ProtoParticle::ProtoParticle(const Vec& position, const Col4& col) :
	position(position), col(col) {
	init();
}
ProtoParticle::ProtoParticle(const Vec& position, float radius, const Col4& col) :
	position(position), radius(radius), col(col) {
	init();
}

ProtoParticle::ProtoParticle(const Vec& position, float radius, const std::string& icon) :
	position(position), radius(radius), icon(icon) {
	init();
}

void ProtoParticle::init() {
	ctx = ProtoContext::getContext();
	partPrims[0] = 0;
	partPrims[1] = 0;
	partPrims[2] = 0;
	partPrims[3] = col.r;
	partPrims[4] = col.g;
	partPrims[5] = col.b;
	partPrims[6] = col.a;


	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoPartID); // Create VAO
	glBindVertexArray(vaoPartID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	//GLuint vboID;
	glGenBuffers(1, &vboPartID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboPartID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat);
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &partPrims[0]); // upload the data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_BACK, GL_FILL);

	// draw rect
	glBindBuffer(GL_ARRAY_BUFFER, vboPartID);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(2); // color
	// stride is 7: pos(3) + col(4)
	// (x, y, z, r, g, b, a)
	int stride = 7;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), BUFFER_OFFSET(12)); // col

	// Disable buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ProtoParticle::move() {
	position += speed;
}

void ProtoParticle::display() {
	ctx->push();
	ctx->translate(position);

	// image mapped particle
	if (isIconified) {
	}
	//plain vanilla particle, still lovely though
	else {
		ctx->setLightRenderingFactors({ 0.0, 0.0, 0.0, 1.0 });
		glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);

		glBindVertexArray(vaoPartID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboPartID); // Bind the buffer (vertex array data)

		int partPrimCount = 7;
		int vertsDataSize = sizeof(GLfloat) * partPrimCount;
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &partPrims[0]); // upload the data

		//glDrawArrays(GL_POINTS, 0, ptPrimCount / stride);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(radius * 2);
		glDrawArrays(GL_POINTS, 0, partPrimCount / stride);

		ctx->setLightRenderingFactors({ 1.0, 1.0, 1.0, 0.0 });
		glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);

		// Disable VAO
		glBindVertexArray(0);
	}

	ctx->pop();

}

//void ProtoParticle::collide() {
//
//}
