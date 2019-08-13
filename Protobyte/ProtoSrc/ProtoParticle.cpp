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
	//init();
}

ProtoParticle::ProtoParticle(const Vec& position, const Vec& rotation, Dim3f size, PartType type, const std::string& icon) :
	position(position), rotation(rotation), size(size), type(type), icon(icon) {
	init();
}

ProtoParticle::ProtoParticle(const Vec& position, const Vec& rotation, Dim3f size, PartType type, const Col4& col) :
	position(position), rotation(rotation), size(size), type(type), col(col) {
	init(); 
}

void ProtoParticle::init() {
	ctx = ProtoContext::getContext();
	switch (type) {
	case POINT:
		// vert data
		// 1. Create and bind VAO
		glGenVertexArrays(1, &vaoPtID); // Create VAO
		glBindVertexArray(vaoPtID); // Bind VAO (making it active)

		// 2. Create and bind VBO
		// a. Vertex attributes vboID;
		//GLuint vboID;
		glGenBuffers(1, &vboPtID); // Create the buffer ID
		glBindBuffer(GL_ARRAY_BUFFER, vboPtID); // Bind the buffer (vertex array data)
		
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &ptPrims[0]); // upload the data

		// fill state is true - need to create this
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glPolygonMode(GL_BACK, GL_FILL);

		// draw rect
		glBindBuffer(GL_ARRAY_BUFFER, vboPtID);

		glEnableVertexAttribArray(0); // vertices
		glEnableVertexAttribArray(2); // color
		// stride is 7: pos(3) + col(4)
		// (x, y, z, r, g, b, a)
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), BUFFER_OFFSET(0)); // pos
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), BUFFER_OFFSET(12)); // col

		// Disable buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	case LINE:
		break;
	case RECT:
		partGeom = std::move(std::unique_ptr<ProtoRectangle>(new ProtoRectangle(position, size.w, size.h, Col4(.5, .5, .5, 1), icon)));
		//partGeom->setColor({ .1, 0, 0, 1 });
		//partGeom->setDiffuseMaterial(1);
		partGeom->setAmbientMaterial(0.05f);
		partGeom->setBumpMap("STG_Flesh/Normal_Maps/STG_Flesh_27-normal.jpg", .1f);
		partGeom->setSpecularMaterial(1);
		partGeom->setShininess(125);
		break;
	case ELLIPSE:
		break;
	case BOX:
		break;
	case SPHERE:
		break;

		//default:
	// point is default
	}
}

void ProtoParticle::move() {
	speed.y += gravity;
	if (type == POINT) {
		position += speed;
		//trace("speed", speed.y);
	}
	else {
		partGeom->getPosition() += speed;
	}
	
}



void ProtoParticle::display() {


	if (type == POINT) {
		ptPrims[0] = 0;
		ptPrims[1] = 0;
		ptPrims[2] = 0;
		ptPrims[3] = col.r;
		ptPrims[4] = col.g;
		ptPrims[5] = col.b;
		ptPrims[6] = col.a;
		ctx->push();
		ctx->translate(position);
		
		// disable 3D lighting
		ctx->setLightRenderingFactors({ 0.0, 0.0, 0.0, 1.0 });
		glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);

		glBindVertexArray(vaoPtID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboPtID); // Bind the buffer (vertex array data)

		int ptPrimCount = 7;
		int vertsDataSize = sizeof(GLfloat) * ptPrimCount;
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &ptPrims[0]); // upload the data

		//glDrawArrays(GL_POINTS, 0, ptPrimCount / stride);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(size.w);
		glDrawArrays(GL_POINTS, 0, 1);
		
		// reenable 3D lighting
		ctx->setLightRenderingFactors({ 1.0, 1.0, 1.0, 0.0 });
		glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);

		// Disable VAO
		glBindVertexArray(0);
		ctx->pop();
	}
	else {
		// transformations handled internally
		partGeom->display();
	}
}



//void ProtoParticle::collide() {
//
//}
