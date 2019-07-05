//
//  ProtoBaseApp.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/26/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//


#include "ProtoBaseApp.h"

using namespace ijg;

//NOTE - maybe put all flags in context? and access ctx->

//ProtoBaseApp* ProtoBaseApp::baseApp = 0;

// Default CSTR, implicitly called
// NOTE: called before GL context created
//ProtoBaseApp::ProtoBaseApp() {
//	ProtoBaseApp::baseApp = this; // do I need this?
//}
//
//ProtoBaseApp* ProtoBaseApp::getBaseApp() {
//	return ProtoBaseApp::baseApp;
//}

void ProtoBaseApp::setWindowFrameSize(const Dim2i& windowFrameSize) {
	this->windowFrameSize = windowFrameSize;
}


void ProtoBaseApp::_init() {

	shader3D = ProtoShader("bumpmapping.vs.glsl", "bumpmapping.fs.glsl");
	shader3D.bind();

	// create context and initialize
	ctx = ProtoContext::getContext(width, height);
	ctx->init();

	// default global ambient
	ctx->setGlobalAmbient({ .45f, .45f, .55f });

	// default inital light
	ctx->setLight(0, { 0, 300, 600 }, { 1, 1, 1 });
	ctx->setLight(1, { 0, 0, 1 }, { 0, 0, 0 });
	ctx->setLight(2, { 0, 0, 1 }, { 0, 0, 0 });
	ctx->setLight(3, { 0, 0, 1 }, { 0, 0, 0 });
	ctx->setLight(4, { 0, 0, 1 }, { 0, 0, 0 });
	ctx->setLight(5, { 0, 0, 1 }, { 0, 0, 0 });
	ctx->setLight(6, { 0, 0, 1 }, { 0, 0, 0 });
	ctx->setLight(7, { 0, 0, 1 }, { 0, 0, 0 });

	// initialize mouse vars
	mouseX = mouseY = mouseLastFrameX = mouseLastFrameY = 0;

	//  initialize arcball vars
	arcballRotX = arcballRotY = arcballRotXLast, arcballRotYLast = mouseXIn = mouseYIn = 0;


	// START standard transformation matrices: ModelView / Projection / Normal
	ctx->setModel(glm::mat4(1.0f));
	// only relavent if draw not invoked
	ctx->setView(glm::lookAt(glm::vec3(0.0, 0.0, defaultCameraDepth), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)));

	float viewAngle = 65.0f * PI / 180.0f;
	//float aspect = float(width) / float(height);
	aspectRatio = float(width) / float(height);
	float nearDist = 0.1f;
	float farDist = 3000.0f;
	// perspective
	ctx->setProjection(glm::perspective(viewAngle, aspectRatio, nearDist, farDist));
	// END Model / View / Projection data


	// START Shadow Map Matrices
	ctx->setLightView(glm::lookAt(glm::vec3(ctx->getLight(0).getPosition().x, ctx->getLight(0).getPosition().y, ctx->getLight(0).getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	ctx->setLightProjection(glm::perspective(viewAngle, aspectRatio, nearDist, 5.0f));

	//ctx->concatLightModelViewProjection();
	ctx->setLightBias(glm::mat4(
		glm::vec4(0.5, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.5, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.5, 0.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
	));
	// sets size/edge blur and texture creation
	createShadowMap();

	// for 2D rendering - enables/disables lighting effects
	ctx->setLightRenderingFactors({ 1.0, 1.0, 1.0, 1.0 });

	// default 2D style states
	//fillColor = Col4f(1, 1, 1, 1);
	//strokeColor = Col4f(0, 0, 0, 1);
	isFill = true;
	isStroke = true;
	lineWidth = 1.0;

	// default number of points around ellipse
	ellipseDetail = 36;

	// drawing methods path
	isPathRecording = false;

	// for primitives
	textureScale.x = textureScale.y = 1.0;

	// default no texture
	noDiffuseTexture = Texture("white_tile.jpg", ProtoTexture::DIFFUSE_MAP);
	noBumpTexture = Texture("white_tile.jpg", ProtoTexture::BUMP_MAP);

	//precalculate 2D geometry
	_createRect();
	_createQuad();
	_createEllipse();
	_createPath();
	_createStar();

	//precalculate 3D geometry
	//_createBox();

	//calls init() in derived ProtoController class
	init();

	// shows uniform and attribute locations in shader
	GLSLInfo(&shader3D);
}


// For view matrix
void ProtoBaseApp::setSceneCenter(const Vec3& axis) {
	ctx->setSceneCenter(axis);
}
void ProtoBaseApp::setEyePosition(const Vec3& eyePos) {
	ctx->setEyePosition(eyePos);
}
void ProtoBaseApp::setUpAxis(const Vec3& axis) {
	ctx->setUpAxis(axis);
}


// create default buffers for rect function
void ProtoBaseApp::_createRect() {

	// interleaved float[] (x, y, 0, r, g, b, a) 7*4 pts
	float prims[] = {
		0, 0, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0, 0 - 1, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0 + 1, 0 - 1, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0 + 1, 0, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a
	};
	for (int i = 0; i < 28; ++i) {
		rectPrims[i] = prims[i];
	}

	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoRectID); // Create VAO
	glBindVertexArray(vaoRectID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	//GLuint vboID;
	glGenBuffers(1, &vboRectID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboRectID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * 28;
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &rectPrims[0]); // upload the data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_BACK, GL_FILL);

	// draw rect
	glBindBuffer(GL_ARRAY_BUFFER, vboRectID);

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

// create default buffers for quad function
void ProtoBaseApp::_createQuad() {

	// interleaved float[] (x, y, 0, r, g, b, a) 7*4 pts
	float prims[] = {
		0, 0, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0, 0 - 1, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0 + 1, 0 - 1, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a,
		0 + 1, 0, 0, fillColor.r, fillColor.g, fillColor.b, fillColor.a
	};
	for (int i = 0; i < 28; ++i) {
		quadPrims[i] = prims[i];
	}

	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoQuadID); // Create VAO
	glBindVertexArray(vaoQuadID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	//GLuint vboID;
	glGenBuffers(1, &vboQuadID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboQuadID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * 28;
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &quadPrims[0]); // upload the data

	// fill state is true - need to create this
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	// draw rect
	glBindBuffer(GL_ARRAY_BUFFER, vboQuadID);

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


// create default buffers for ellipse function
void ProtoBaseApp::_createEllipse() {
	float theta = 0.0;
	for (int i = 0; i < ellipseDetail; i++) {
		ellipsePrims.push_back(0 + cos(theta));
		ellipsePrims.push_back(0 + sin(theta));
		ellipsePrims.push_back(0);
		ellipsePrims.push_back(fillColor.r);
		ellipsePrims.push_back(fillColor.g);
		ellipsePrims.push_back(fillColor.b);
		ellipsePrims.push_back(fillColor.a);
		theta += TWO_PI / ellipseDetail;
	}

	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoEllipseID); // Create VAO
	glBindVertexArray(vaoEllipseID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	glGenBuffers(1, &vboEllipseID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboEllipseID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * ellipsePrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &ellipsePrims[0]); // upload the data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

	ellipsePrims.clear();
}

// create default buffers for star function
void ProtoBaseApp::_createStar() {
	int sides = 3;
	float theta = 0.0;
	float innerRadius = .65f;
	float outerRadius = 1.0f;
	int pts = sides * 2;
	for (int i = 0; i < pts; i++) {
		if (i % 2 == 0) {
			starStrokePrims.push_back(cos(theta) * outerRadius);
			starStrokePrims.push_back(sin(theta) * outerRadius);
		}
		else {
			starStrokePrims.push_back(cos(theta) * innerRadius);
			starStrokePrims.push_back(sin(theta) * innerRadius);
		}
		starStrokePrims.push_back(0);
		starStrokePrims.push_back(fillColor.r);
		starStrokePrims.push_back(fillColor.g);
		starStrokePrims.push_back(fillColor.b);
		starStrokePrims.push_back(fillColor.a);
		theta += TWO_PI / pts;
	}

	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoStarID); // Create VAO
	glBindVertexArray(vaoStarID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	glGenBuffers(1, &vboStarID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboStarID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * starStrokePrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &starStrokePrims[0]); // upload the data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

	starStrokePrims.clear();
}

// create default buffers for easy path
// Enables begin/vertex/end immediate mode drawing
// Use ProtoPath2 for higher performance path drawing
void ProtoBaseApp::_createPath() {
	/*int pathDetail = 1;
	float theta = 0.0;
	for (int i = 0; i < pathDetail; i++){
	pathPrims.push_back(0 + cos(theta));
	pathPrims.push_back(0 + sin(theta));
	pathPrims.push_back(0);
	pathPrims.push_back(fillColor.r);
	pathPrims.push_back(fillColor.g);
	pathPrims.push_back(fillColor.b);
	pathPrims.push_back(fillColor.a);
	theta += TWO_PI / ellipseDetail;
	}*/

	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoPathID); // Create VAO
	glBindVertexArray(vaoPathID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	glGenBuffers(1, &vboPathID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboPathID); // Bind the buffer (vertex array data)
	int vertsDataSize = 0;// sizeof (GLfloat)* pathPrims.size();
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);// allocate space
	//glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrims[0]); // upload the data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

// start 3D prmitive funcs
// create default buffers for ellipse function
// TO DO: Finish
void ProtoBaseApp::_createBox() {
	Vec3f boxVecs[8];
	boxVecs[0] = Vec3f(-.5, .5, .5);
	boxVecs[1] = Vec3f(-.5, -.5, .5);
	boxVecs[2] = Vec3f(.5, -.5, .5);
	boxVecs[3] = Vec3f(.5, .5, .5);
	boxVecs[4] = Vec3f(.5, .5, -.5);
	boxVecs[5] = Vec3f(.5, -.5, -.5);
	boxVecs[6] = Vec3f(-.5, -.5, -.5);
	boxVecs[7] = Vec3f(-.5, .5, -.5);

	Tup4i indices[6];
	indices[0] = Tup4i(0, 1, 2, 3); //F
	indices[1] = Tup4i(2, 5, 4, 3); //R
	indices[2] = Tup4i(4, 5, 6, 7); //B
	indices[3] = Tup4i(0, 7, 6, 1); //L
	indices[4] = Tup4i(0, 3, 4, 7); //Top
	indices[5] = Tup4i(1, 6, 5, 2); //Bot

	Vertex3 verts[24];
	Vec3 norms[6];
	Vec3 tans[6];

	// F
	verts[0] = ProtoVertex3(boxVecs[0], fillColor, Tup2f(0.0, 0.0));
	verts[1] = ProtoVertex3(boxVecs[1], fillColor, Tup2f(0.0, 1.0 * textureScale.y));
	verts[2] = ProtoVertex3(boxVecs[2], fillColor, Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts[3] = ProtoVertex3(boxVecs[3], fillColor, Tup2f(1.0 * textureScale.x, 0.0));

	// R
	verts[4] = ProtoVertex3(boxVecs[2], fillColor, Tup2f(0.0, 1.0 * textureScale.y));
	verts[5] = ProtoVertex3(boxVecs[5], fillColor, Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts[6] = ProtoVertex3(boxVecs[4], fillColor, Tup2f(1.0 * textureScale.x, 0.0));
	verts[7] = ProtoVertex3(boxVecs[3], fillColor, Tup2f(0.0, 0.0 * textureScale.y));

	// B
	verts[8] = ProtoVertex3(boxVecs[4], fillColor, Tup2f(0.0, 0.0));
	verts[9] = ProtoVertex3(boxVecs[5], fillColor, Tup2f(0.0, 1.0 * textureScale.y));
	verts[10] = ProtoVertex3(boxVecs[6], fillColor, Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts[11] = ProtoVertex3(boxVecs[7], fillColor, Tup2f(1.0 * textureScale.x, 0.0));

	// L
	verts[12] = ProtoVertex3(boxVecs[0], fillColor, Tup2f(1.0 * textureScale.x, 0.0));
	verts[13] = ProtoVertex3(boxVecs[7], fillColor, Tup2f(0.0, 0.0));
	verts[14] = ProtoVertex3(boxVecs[6], fillColor, Tup2f(0.0, 1.0 * textureScale.y));
	verts[15] = ProtoVertex3(boxVecs[1], fillColor, Tup2f(1.0 * textureScale.x, 1.0));

	// Top
	verts[16] = ProtoVertex3(boxVecs[0], fillColor, Tup2f(0.0, 1.0 * textureScale.y));
	verts[17] = ProtoVertex3(boxVecs[3], fillColor, Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts[18] = ProtoVertex3(boxVecs[4], fillColor, Tup2f(1.0 * textureScale.x, 0.0));
	verts[19] = ProtoVertex3(boxVecs[7], fillColor, Tup2f(0.0, 0.0));

	// Bot
	verts[20] = ProtoVertex3(boxVecs[1], fillColor, Tup2f(0.0, 0.0));
	verts[21] = ProtoVertex3(boxVecs[6], fillColor, Tup2f(0.0, 1.0 * textureScale.y));
	verts[22] = ProtoVertex3(boxVecs[5], fillColor, Tup2f(1.0 * textureScale.x, 1.0 * textureScale.y));
	verts[23] = ProtoVertex3(boxVecs[2], fillColor, Tup2f(1.0 * textureScale.x, 0.0));

	// calc normals and tangents and add to box vertices
	for (int i = 0; i < 6; ++i) {
		Face3 f = Face3(&verts[0 + i * 4], &verts[1 + i * 4], &verts[2 + i * 4]);
		norms[i] = f.getNorm();
		norms[i].normalize();
		tans[i] = f.getTangent();
		tans[i].normalize();

		for (int j = 0; j < 4; ++j) {
			int k = i * 4 + j;
			verts[k].setNormal(norms[i]);
			verts[k].setTangent(tans[i]);
			//trace("verts[",k,"] =", verts[k]);
		}
	}

	// calc prims
	// (x, y, z, nx, ny, nz, r, g, b, a, u, v, tx, ty, tz)
	for (int i = 0, j = 0; i < 24; i++, j += 15) {
		boxPrims[j] = verts[i].pos.x;
		boxPrims[j + 1] = verts[i].pos.y;
		boxPrims[j + 2] = verts[i].pos.z;
		boxPrims[j + 3] = verts[i].getNormal().x;
		boxPrims[j + 4] = verts[i].getNormal().y;
		boxPrims[j + 5] = verts[i].getNormal().z;
		boxPrims[j + 6] = fillColor.r;
		boxPrims[j + 7] = fillColor.g;
		boxPrims[j + 8] = fillColor.b;
		boxPrims[j + 9] = fillColor.a;
		boxPrims[j + 10] = verts[i].getUV().elem0;
		boxPrims[j + 11] = verts[i].getUV().elem1;
		boxPrims[j + 12] = verts[i].getTangent().x;
		boxPrims[j + 13] = verts[i].getTangent().y;
		boxPrims[j + 14] = verts[i].getTangent().z;
	}

	for (int i = 0; i < boxPrimCount; ++i) {
		boxPrimsOrig[i] = boxPrims[i];
	}

	// vert data
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoBoxID); // Create VAO
	glBindVertexArray(vaoBoxID); // Bind VAO (making it active)

	// 2. Create and bind VBO
	// a. Vertex attributes vboID;
	glGenBuffers(1, &vboBoxID); // Create the buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vboBoxID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * boxPrimCount;
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &boxPrims[0]); // upload the data

	// fill state is true - need to create this
	glPolygonMode(GL_FRONT, GL_FILL);

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(1); // normals
	glEnableVertexAttribArray(2); // color
	glEnableVertexAttribArray(3); // uvs
	glEnableVertexAttribArray(4); // tangents

	// (x, y, z, nx, ny, nz, r, g, b, a, u, v, tx, ty, tz)
	const int STRIDE = 15;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(12)); // norm
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(24)); // col
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(40)); // uv
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(48)); // tangent

	// Disable buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// immediate drawing mode lighting and materials
void ProtoBaseApp::setSpecular(const Col4f& spec) {

}
void ProtoBaseApp::setShininess(float shininess) {

}
void ProtoBaseApp::setDiffuseMaterial(const Col4f& diff) {

}
void ProtoBaseApp::setAmbientMaterial(const Col4f& amb) {

}

//bool ProtoBaseApp::createShadowMap(){
//
//	// set up FBO
//	glGenFramebuffers(1, &frameBufferName);
//	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferName);
//	
//	//set up shadow texture object
//	glGenTextures(1, &depthTexture);
//	glBindTexture(GL_TEXTURE_2D, depthTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
//
//	//glActiveTexture(GL_TEXTURE5);
//	GLfloat border[] = { 1.0f, .0f, .0f, .0f };
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
//	
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
//		return false;
//}

bool ProtoBaseApp::createShadowMap() {

	//  (defaults to GLFW window size)
	setShadowMapSize(getWidth(), getHeight());

	// For PCF (default 256 x 256)
	setShadowSharpness(512, 512);

	//set up shadow texture object
	glGenTextures(1, &ctx->getShadowTexture_U());
	//trace("&ctx->getShadowTexture_U()", &ctx->getShadowTexture_U());
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, ctx->getShadowTexture_U());
	GLfloat border[] = { 0.0f, .0f, .0f, .0f };

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//PCF in hardware
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// depth compare in hardware
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);


	// set up FBO
	glGenFramebuffers(1, &ctx->getShadowBuffer_U());
	glBindFramebuffer(GL_FRAMEBUFFER, ctx->getShadowBuffer_U());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ctx->getShadowTexture_U(), 0);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, ctx->getShadowTexture_U(), 0);


	// No color buffer is drawn to.
	glDrawBuffer(GL_NONE);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		// unbind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
	else {
		// unbind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	return false;
}

void ProtoBaseApp::setShadowSharpness(int shadowSharpnessWidth, int shadowSharpnessHeight) {
	this->shadowSharpnessWidth = shadowSharpnessWidth;
	this->shadowSharpnessHeight = shadowSharpnessHeight;
	ctx->setShadowSharpness(shadowSharpnessWidth, shadowSharpnessHeight);
}

void ProtoBaseApp::setShadowMapSize(int shadowMapWidth, int shadowMapHeight) {
	this->shadowMapWidth = shadowMapWidth;
	this->shadowMapHeight = shadowMapHeight;
}

Tup2i ProtoBaseApp::getShadowSharpness() const {
	return { shadowSharpnessWidth, shadowSharpnessHeight };
}

void ProtoBaseApp::_run(const Vec2f& mousePos, const Vec4i& windowCoords/*, int mouseBtn, int key*/) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// NOTE:: reset state - why did I have these calls uncommented?
	//fillColor = Col4f(1, 1, 1, 1); // white fill
	//strokeColor = Col4f(0, 0, 0, 1); // black stroke

	mouseX = mousePos.x;
	mouseY = mousePos.y;

	// mouse is moving/dragging
	if (Vec2(mouseX, mouseY) - Vec2(mouseLastFrameX, mouseLastFrameY) != Vec2(0, 0)) {
		if (isMousePressed) {

			// arcball
			//if (isArcballOn){
			arcballRotY = mouseX - mouseXIn + arcballRotYLast;
			arcballRotX = mouseY - mouseYIn + arcballRotXLast;
			//}

			mouseDragged();
		}
		else {
			mouseMoved();
		}
	}

	// update global ambient for shader
	glUniform3fv(ctx->getGlobalAmbient_U(), 1, &ctx->getGlobalAmbient().r);

	// update all 8 lights for shader
	for (int i = 0; i < 8; ++i) {
		glUniform3fv(ctx->getLight_U(i).position, 1, &ctx->getLight(i).getPosition().x);
		glUniform3fv(ctx->getLight_U(i).intensity, 1, &ctx->getLight(i).getIntensity().x);
	}

	// I thought I needed this to reset matrix each frame?
	// was 18
	ctx->setView(glm::lookAt(glm::vec3(0, 0, defaultCameraDepth), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)));

	// update shadow map texture matrix should light(s) changes position (only for light0 for now)
	/*ctx->setLightView(glm::lookAt(glm::normalize(glm::vec3(ctx->getLight(0).getPosition().x, ctx->getLight(0).getPosition().y, ctx->getLight(0).getPosition().z)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));*/

	ctx->setLightView(glm::lookAt(glm::vec3(ctx->getLight(0).getPosition().x, ctx->getLight(0).getPosition().y, ctx->getLight(0).getPosition().z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

	ctx->setLightBias(glm::mat4(
		glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
	));
	ctx->updateLightViewMatrices();

	// enable  /disable lighting effects ofr 2D rendering
	ctx->setLightRenderingFactors({ 1.0, 1.0, 1.0, 1.0 });

	run(); // calls run in user defined ProtoController class
	render(); // handles 2 pass rendering and transformation matrix reset

	mouseLastFrameX = mouseX;
	mouseLastFrameY = mouseY;
}

// Final function call before user defined display() call
void ProtoBaseApp::render(int x, int y, int scaleFactor) {

	// reset transformation matrix each frame
	ctx->setModel(glm::mat4{ 1.0f });
	float viewAngle = 75.0f * PI / 180.0f;
	//float aspect = float(width) / float(height);
	float nearDist = .5f;
	float farDist = 3000.0f;

	if (areShadowsEnabled) {
		// Make shadow frame buffer active
		glBindFramebuffer(GL_FRAMEBUFFER, ctx->getShadowBuffer_U());
		glClear(GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//set viewport to the shadow map view size
		glViewport(0, 0, shadowMapWidth, shadowMapHeight);

		// enable front face culling for shadowing
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.1, 4.0);

		// Flag controls render pass in shader
		// enable shadow blending
		glUniform1i(ctx->getShaderPassFlag_U(), 1);

		// Pass 1: render depth to FB
		// set Light view matrix
		//viewAngle = 60.0f*PI / 180.0f; //parameterize eventually
		//ctx->setLightProjection(glm::perspective(viewAngle, aspect, -1.0f, 1.0f));
		//ctx->setLightProjection(glm::ortho(-getWidth()/2.0f, getWidth() / 2.0f, -getHeight()/2.0f, getHeight()/2.0f, .1f, 5.0f));
		//ctx->setLightProjection(glm::ortho(-65.0f, 65.0f, -40.0f, 40.0f, .1f, 116.0f));
		//ctx->setLightProjection(glm::frustum(-.25f, .25f, -.145f, .145f, 1.0f, 300.0f));
		ctx->setLightProjection(glm::frustum(-1.0f, 1.0f, -1 / aspectRatio, 1 / aspectRatio, 1.0f, 2000.0f));

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		// call user defined display, renders depth to texture
		display();

		// Pass 2: render scene to FB

		// reset transforamtion matrix for 2nd pass
		ctx->setModel(glm::mat4{ 1.0f });

		// reset backface culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);

		// reset default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Write to a color buffer (not sure which one to optimally use)
		glDrawBuffer(GL_FRONT_LEFT);

		// reset viewport to window view size.
		// includes optional offset for tiling
		glViewport(x * windowFrameSize.w, y * windowFrameSize.h, scaleFactor * windowFrameSize.w, scaleFactor * windowFrameSize.h);
		//glViewport(0, 0, width, height);

		// disable shadowing blending
		glUniform1i(ctx->getShaderPassFlag_U(), 0); // controls render pass in shader

		// enable 3D lighting by default
		enableLights();

		// render scene in second pass
		//float viewAngle = 65.0f*PI/180.0f;
		//float aspect = float(width) / float(height);
		//float nearDist = 0.1f;
		//float farDist = 6000.0f;
		// perspective
		viewAngle = 60.0f * PI / 180.0f; //parameterize eventually
		ctx->setProjection(glm::perspective(viewAngle, aspectRatio, nearDist, farDist));
		// call user defined display
		display();
	}
	// shadows not enabled
	else {

		// flag set to disable shadow implementation in shader
		glUniform1i(ctx->getShaderPassFlag_U(), 0);

		// no shadowing use default run
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// set viewport to window size.
		glViewport(x * windowFrameSize.w, y * windowFrameSize.h, scaleFactor * windowFrameSize.w, scaleFactor * windowFrameSize.h);

		// reset backface culling
		//glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);

		float viewAngle = 65.0f * PI / 180.0f;
		//float aspect = float(width) / float(height);
		float nearDist = 0.1f;
		float farDist = 6000.0f;
		// perspective
		ctx->setProjection(glm::perspective(viewAngle, aspectRatio, nearDist, farDist));

		// call user defined display
		display();
	}
}

// Mouse event behavior
void ProtoBaseApp::setMouseButton(int mouseAction, int mouseButton, int mouseMods) {
	if (mouseAction == 1) {
		isMousePressed = true;

		// arcball
		mouseXIn = mouseX;
		mouseYIn = mouseY;

		mousePressed();
	}
	else if (mouseAction == 0) {
		isMousePressed = false;

		// arcball
		arcballRotXLast = arcballRotX;
		arcballRotYLast = arcballRotY;


		mouseReleased();
	}
	/*this->mouseButton = mouseButton;
	trace("LEFT mouse button pressed");*/
}

// Key event behavior
void ProtoBaseApp::setKeyEvent(int key, int scancode, int action, int mods) {
	this->key = key;
	this->scancode = scancode;
	this->action = action;
	keyPressed();
}

//arcball
void ProtoBaseApp::arcballBegin() {
	//isArcballOn = true;
	push();
	rotate(arcballRotX * PI / 180.0f, 1, 0, 0);
	rotate(arcballRotY * PI / 180.0f, 0, 1, 0);
}

void ProtoBaseApp::arcballEnd() {
	//isArcballOn = false;
	pop();
}

// gen funcs
// overloaded background
void ProtoBaseApp::setBackground(float r, float g, float b) {
	bgColor.setR(r);
	bgColor.setG(g);
	bgColor.setB(b);
	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void ProtoBaseApp::setBackground(float c) {
	setBackground(c, c, c);
}

void ProtoBaseApp::setBackground(const Col3f& col) {
	setBackground(col.getR(), col.getG(), col.getB());
}

void ProtoBaseApp::setBackground(const Col4f& col) {
	setBackground(col.getR(), col.getG(), col.getB());
}

// END background

//LIGHTS
void ProtoBaseApp::lightsOn() {
	//	glEnable(GL_LIGHTING);

}
void ProtoBaseApp::lightsOff() {
	//	glDisable(GL_LIGHTING);
}
//END LIGHTS

// window details
void ProtoBaseApp::setWidth(int canvasWidth) {
	this->canvasWidth = canvasWidth;
	width = canvasWidth;
	windowFrameSize.w = width;
}

void ProtoBaseApp::setHeight(int canvasHeight) {
	this->canvasHeight = canvasHeight;
	height = canvasHeight;
	windowFrameSize.h = height;
}

void ProtoBaseApp::setSize(const Dim2i& canvasSize) {
	this->canvasSize = canvasSize;
}


int ProtoBaseApp::getWidth() const {
	return width;
}

int ProtoBaseApp::getHeight() const {
	return height;
}

Dim2i ProtoBaseApp::getSize()const {
	return canvasSize;
}

int ProtoBaseApp::getCanvasWidth() const {
	return canvasWidth;
}

int ProtoBaseApp::getCanvasHeight() const {
	return canvasHeight;
}

Dim2i ProtoBaseApp::getCanvasSize() const {
	return canvasSize;
}

Dim2i ProtoBaseApp::getWindowFrameSize() const {
	return windowFrameSize;
}

// Load Image
// don't think this used??
void ProtoBaseApp::loadImage(std::string imageName) {
	// START for relative resource loading
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cout << "error loading from relative directory" << std::endl;
		//return errno;
	}
	// NOTE - workspace project relative instead of using default derivedData path in Library
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
	std::string cp = cCurrentPath; //cast char[] to string
	std::cout << "current path = " << cp << std::endl;
	std::string pathExtension = "/resources/imgs";
	std::string imgName = "/" + imageName;
	std::string url = cp + pathExtension + imgName;
	//    sf::Texture texture;
	//    if (!texture.loadFromFile(url))
	//    {
	//        // error...
	//    }
}

// END window details

// 2D api 
void ProtoBaseApp::GLSLInfo(ProtoShader* shader) {
	// START get all uniform shaders
	GLint nUniforms, maxLen;

	glGetProgramiv(shader->getID_2(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(shader->getID_2(), GL_ACTIVE_UNIFORMS, &nUniforms);

	GLchar* name = (GLchar*)malloc(maxLen);

	GLint size, location;
	GLsizei written;
	GLenum type;
	printf("\n Location | Name\n");
	printf("--------------------------------------------------\n");
	for (int i = 0; i < nUniforms; ++i) {
		glGetActiveUniform(shader->getID_2(), i, maxLen, &written, &size, &type, name);
		location = glGetUniformLocation(shader->getID_2(), name);
		printf(" %-8d | %s\n", location, name);
	}
	free(name);
	// END get all uniform shaders

	// get info about renderers
	trace("renderer =", glGetString(GL_RENDERER));
	trace("vendor =", glGetString(GL_VENDOR));
	trace(" version =", glGetString(GL_VERSION));
	trace("glslVersion =", glGetString(GL_SHADING_LANGUAGE_VERSION));

	trace("vertexPosition Location =", glGetAttribLocation(shader->getID_2(), "vertexPosition"));
	trace("vertexNormal Location =", glGetAttribLocation(shader->getID_2(), "vertexNormal"));
	trace("vertexColor Location =", glGetAttribLocation(shader->getID_2(), "vertexColor"));
	trace("vertexTextureCoords Location =", glGetAttribLocation(shader->getID_2(), "vertexTextureCoords"));
	trace("vertexTangent Location =", glGetAttribLocation(shader->getID_2(), "vertexTangent"));
}


/***********BEGIN************
2D Automatic Procedural API
***************************/

// flag  enable/disable 2D lighting
void ProtoBaseApp::enable2DRendering() {
	//ltRenderingFactors = Vec4f(0.0, 0.0, 0.0, 1.0);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	ctx->setLightRenderingFactors({ 0.0, 0.0, 0.0, 1.0 });
	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);
}
void ProtoBaseApp::disable2DRendering() {
	//ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 0.0);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	ctx->setLightRenderingFactors({ 1.0, 1.0, 1.0, 0.0 });
	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);
}


// Styles API
void ProtoBaseApp::fill(const Col4f& col) {
	isFill = true;
	fillColor = col;
	//ltRenderingFactors = Vec4f(0.0, 0.0, 0.0, 1.0);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	ctx->setLightRenderingFactors({ 0.0, 0.0, 0.0, 1.0 });
	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);
}
void ProtoBaseApp::fill(float gray) {
	isFill = true;
	fillColor = Col4f(gray, gray, gray, 1);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);
}
void ProtoBaseApp::fill(float gray, float a) {
	isFill = true;
	fillColor = Col4f(gray, gray, gray, a);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);
}
void ProtoBaseApp::fill(float r, float g, float b) {
	isFill = true;
	fillColor = Col4f(r, g, b, 1);
	//ltRenderingFactors = Vec4f(0.0, 0.0, 0.0, 1.0);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	ctx->setLightRenderingFactors({ 0.0, 0.0, 0.0, 1.0 });
	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);
}
void ProtoBaseApp::fill(float r, float g, float b, float a) {
	isFill = true;
	fillColor = Col4f(r, g, b, a);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);
}
void ProtoBaseApp::noFill() {
	isFill = false;

}
// begin STROKE
void ProtoBaseApp::stroke(const Col4f& col) {
	isStroke = true;
	strokeColor = col;
}
void ProtoBaseApp::stroke(float gray) {
	isStroke = true;
	strokeColor = Col4f(gray, gray, gray, 1);
}
void ProtoBaseApp::stroke(float gray, float a) {
	isStroke = true;
	strokeColor = Col4f(gray, gray, gray, a);
}
void ProtoBaseApp::stroke(float r, float g, float b) {

	isStroke = true;
	strokeColor = Col4f(r, g, b, 1);
}
void ProtoBaseApp::stroke(float r, float g, float b, float a) {
	isStroke = true;
	strokeColor = Col4f(r, g, b, a);

	/*ctx->setLightRenderingFactors({ 0.0, 0.0, 0.0, 1.0 });
	glUniform4fv(ctx->getLightRenderingFactors_U(), 1, &ctx->getLightRenderingFactors().x);*/
}
void ProtoBaseApp::noStroke() {
	isStroke = false;
}
void ProtoBaseApp::strokeWeight(float lineWidth) {
	this->lineWidth = lineWidth;
}


//TEXTURES
void ProtoBaseApp::noTexture() {
	diffuseMapLocation = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMap");
	glUniform1i(boxDiffuseMapLoc, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, noDiffuseTexture.getTextureID());

	bumpMapLocation = glGetUniformLocation(ProtoShader::getID_2(), "bumpMap");
	glUniform1i(boxBumpMapLoc, 1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, noBumpTexture.getTextureID());

}
void ProtoBaseApp::diffuseTexture(const ProtoTexture& diffuseTexture) {
	diffuseMapLocation = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMap");
	glUniform1i(boxDiffuseMapLoc, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture.getTextureID());
}
void ProtoBaseApp::bumpTexture(const ProtoTexture& bumpTexture) {
	bumpMapLocation = glGetUniformLocation(ProtoShader::getID_2(), "bumpMap");
	glUniform1i(boxBumpMapLoc, 1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpTexture.getTextureID());
}


//PRIMITIVES
void ProtoBaseApp::rect(float x, float y, float z, float w, float h, Registration reg) {

	float _x = 0, _y = 0;

	switch (reg) {
	case CENTER:
		_x = x - w / 2;
		_y = y + h / 2;
		break;
	case CORNER:
		_x = x;
		_y = y;
		break;
	case CORNER_TR:
		_x = x - w;
		_y = y;
		break;
	case CORNER_BR:
		_x = x - w;
		_y = y + h;
		break;
	case CORNER_BL:
		_x = x;
		_y = y + h;
		break;
	case RANDOM:
		// to do
		break;

	}

	rectPrims[0] = _x;
	rectPrims[1] = _y;
	rectPrims[2] = z;
	rectPrims[3] = fillColor.r;
	rectPrims[4] = fillColor.g;
	rectPrims[5] = fillColor.b;
	rectPrims[6] = fillColor.a;
	rectPrims[7] = _x;
	rectPrims[8] = _y - h;
	rectPrims[9] = z;
	rectPrims[10] = fillColor.r;
	rectPrims[11] = fillColor.g;
	rectPrims[12] = fillColor.b;
	rectPrims[13] = fillColor.a;
	rectPrims[14] = _x + w;
	rectPrims[15] = _y - h;
	rectPrims[16] = z;
	rectPrims[17] = fillColor.r;
	rectPrims[18] = fillColor.g;
	rectPrims[19] = fillColor.b;
	rectPrims[20] = fillColor.a;
	rectPrims[21] = _x + w;
	rectPrims[22] = _y;
	rectPrims[23] = z;
	rectPrims[24] = fillColor.r;
	rectPrims[25] = fillColor.g;
	rectPrims[26] = fillColor.b;
	rectPrims[27] = fillColor.a;

	int stride = 7;
	int rectPrimCount = 28;

	if (isFill) {
		for (int i = 0; i < rectPrimCount; i += stride) {
			rectPrims[i + 3] = fillColor.r;
			rectPrims[i + 4] = fillColor.g;
			rectPrims[i + 5] = fillColor.b;
			rectPrims[i + 6] = fillColor.a;
		}

		enable2DRendering();
		glBindVertexArray(vaoRectID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboRectID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * rectPrimCount;
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &rectPrims[0]); // upload the data

		glDrawArrays(GL_TRIANGLE_FAN, 0, rectPrimCount / stride);
		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}
	if (isStroke) {
		for (int i = 0; i < rectPrimCount; i += stride) {
			rectPrims[i + 3] = strokeColor.r;
			rectPrims[i + 4] = strokeColor.g;
			rectPrims[i + 5] = strokeColor.b;
			rectPrims[i + 6] = strokeColor.a;
		}

		enable2DRendering();
		glBindVertexArray(vaoRectID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboRectID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * rectPrimCount;
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &rectPrims[0]); // upload the data

		glLineWidth(lineWidth);
		glDrawArrays(GL_LINE_LOOP, 0, rectPrimCount / stride);

		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}
}


void ProtoBaseApp::rect(float x, float y, float w, float h, Registration reg) {
	rect(x, y, 0, w, h, reg);

}

void ProtoBaseApp::rect(const Vec2& pt0, const Vec2& pt1, Registration reg) {
	rect(pt0.x, pt0.y, pt1.x - pt0.x, pt1.y - pt0.y, reg);
}
void ProtoBaseApp::rect(float radius1, float radius2, Registration reg) {
	rect(0, 0, radius1, radius2, reg);
}

// point order: tl, bl, br, tr
void ProtoBaseApp::quad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, Registration reg) {
	Vec2f sz = Vec2f(getMax(x3, x2) - getMin(x1, y0), getMax(y0, y3) - getMin(y1, y2));
	switch (reg) {
	case CENTER:
		quadPrims[0] = x0 - sz.x / 2;
		quadPrims[1] = y0 + sz.y / 2;
		quadPrims[2] = 0;
		quadPrims[7] = x1 - sz.x / 2;
		quadPrims[8] = y1 + sz.y / 2;
		quadPrims[9] = 0;
		quadPrims[14] = x2 - sz.x / 2;
		quadPrims[15] = y2 + sz.y / 2;
		quadPrims[16] = 0;
		quadPrims[21] = x3 - sz.x / 2;
		quadPrims[22] = y3 + sz.y / 2;
		quadPrims[23] = 0;
		break;
	case CORNER:
		quadPrims[0] = x0;
		quadPrims[1] = y0;
		quadPrims[2] = 0;
		quadPrims[7] = x1;
		quadPrims[8] = y1;
		quadPrims[9] = 0;
		quadPrims[14] = x2;
		quadPrims[15] = y2;
		quadPrims[16] = 0;
		quadPrims[21] = x3;
		quadPrims[22] = y3;
		quadPrims[23] = 0;
		break;
	case CORNER_TR:
		quadPrims[0] = x0 - sz.x;
		quadPrims[1] = y0;
		quadPrims[2] = 0;
		quadPrims[7] = x1 - sz.x;
		quadPrims[8] = y1;
		quadPrims[9] = 0;
		quadPrims[14] = x2 - sz.x;
		quadPrims[15] = y2;
		quadPrims[16] = 0;
		quadPrims[21] = x3 - sz.x;
		quadPrims[22] = y3;
		quadPrims[23] = 0;
		break;
	case CORNER_BR:
		quadPrims[0] = x0 - sz.x;
		quadPrims[1] = y0 + sz.y;
		quadPrims[2] = 0;
		quadPrims[7] = x1 - sz.x;
		quadPrims[8] = y1 + sz.y;
		quadPrims[9] = 0;
		quadPrims[14] = x2 - sz.x;
		quadPrims[15] = y2 + sz.y;
		quadPrims[16] = 0;
		quadPrims[21] = x3 - sz.x;
		quadPrims[22] = y3 + sz.y;
		quadPrims[23] = 0;
		break;
	case CORNER_BL:
		quadPrims[0] = x0;
		quadPrims[1] = y0 + sz.y;
		quadPrims[2] = 0;
		quadPrims[7] = x1;
		quadPrims[8] = y1 + sz.y;
		quadPrims[9] = 0;
		quadPrims[14] = x2;
		quadPrims[15] = y2 + sz.y;
		quadPrims[16] = 0;
		quadPrims[21] = x3;
		quadPrims[22] = y3 + sz.y;
		quadPrims[23] = 0;
		break;
	case RANDOM:
		// to do
		break;
	}

	int stride = 7;
	int quadPrimCount = 28;

	if (isFill) {
		for (int i = 0; i < quadPrimCount; i += stride) {
			quadPrims[i + 3] = fillColor.r;
			quadPrims[i + 4] = fillColor.g;
			quadPrims[i + 5] = fillColor.b;
			quadPrims[i + 6] = fillColor.a;
		}

		enable2DRendering();
		glBindVertexArray(vaoQuadID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboQuadID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * quadPrimCount;
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &quadPrims[0]); // upload the data

		glDrawArrays(GL_POLYGON, 0, quadPrimCount / stride);
		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}
	if (isStroke) {
		for (int i = 0; i < quadPrimCount; i += stride) {
			quadPrims[i + 3] = strokeColor.r;
			quadPrims[i + 4] = strokeColor.g;
			quadPrims[i + 5] = strokeColor.b;
			quadPrims[i + 6] = strokeColor.a;
		}

		enable2DRendering();
		glBindVertexArray(vaoQuadID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboQuadID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * quadPrimCount;
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &quadPrims[0]); // upload the data

		glLineWidth(lineWidth);
		glDrawArrays(GL_LINE_LOOP, 0, quadPrimCount / stride);

		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}
}

void ProtoBaseApp::quad(const Vec2& pt0, const Vec2& pt1, const Vec2& pt2, const Vec2& pt3, Registration reg) {
	quad(pt0.x, pt0.y, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y, reg);
}

void ProtoBaseApp::ellipse(float x, float y, float z, float w, float h, Registration reg) {
	if (ellipsePrims.size() > 0) {
		ellipsePrims.clear();
	}

	float _x = 0, _y = 0;

	/* CENTER,
	CORNER, // assumed top left
	CORNER_TR,
	CORNER_BR,
	CORNER_BL,
	RANDOM
	*/

	switch (reg) {
	case CENTER:
		_x = x;
		_y = y;
		break;
	case CORNER: // TL
		_x = x + w / 2;
		_y = y - h / 2;
		break;
	case CORNER_TR:
		_x = x - w / 2;
		_y = y - h / 2;
		break;
	case CORNER_BR:
		_x = x - w / 2;
		_y = y + h / 2;
		break;
	case CORNER_BL:
		_x = x + w / 2;
		_y = y + h / 2;
		break;
	case RANDOM:
		// to do
		break;
	}

	int stride = 7;
	float theta = 0.0;
	for (int i = 0; i < ellipseDetail; i++) {
		ellipsePrims.push_back(_x + cos(theta) * w / 2.0);
		ellipsePrims.push_back(_y + sin(theta) * h / 2.0);
		ellipsePrims.push_back(z);
		ellipsePrims.push_back(fillColor.r);
		ellipsePrims.push_back(fillColor.g);
		ellipsePrims.push_back(fillColor.b);
		ellipsePrims.push_back(fillColor.a);
		theta += TWO_PI / ellipseDetail;
	}

	if (isFill) {
		for (int i = 0; i < ellipsePrims.size(); i += stride) {
			ellipsePrims.at(i + 3) = fillColor.r;
			ellipsePrims.at(i + 4) = fillColor.g;
			ellipsePrims.at(i + 5) = fillColor.b;
			ellipsePrims.at(i + 6) = fillColor.a;
		}

		enable2DRendering();
		glBindVertexArray(vaoEllipseID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboEllipseID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * ellipsePrims.size();
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &ellipsePrims[0]); // upload the data

		glDrawArrays(GL_POLYGON, 0, ellipsePrims.size() / stride);
		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}
	if (isStroke) {
		for (int i = 0; i < ellipsePrims.size(); i += stride) {
			ellipsePrims.at(i + 3) = strokeColor.r;
			ellipsePrims.at(i + 4) = strokeColor.g;
			ellipsePrims.at(i + 5) = strokeColor.b;
			ellipsePrims.at(i + 6) = strokeColor.a;
		}

		enable2DRendering();
		glBindVertexArray(vaoEllipseID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboEllipseID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * ellipsePrims.size();
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &ellipsePrims[0]); // upload the data

		glLineWidth(lineWidth);
		glDrawArrays(GL_LINE_LOOP, 0, ellipsePrims.size() / stride);

		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}
}


void ProtoBaseApp::ellipse(float x, float y, float w, float h, Registration reg) {
	ellipse(x, y, 0, w, h, reg);
}
void ProtoBaseApp::ellipse(float r, Registration reg) {
	ellipse(0, 0, r, r, reg);
}
void ProtoBaseApp::ellipse(float r0, float r1, Registration reg) {
	ellipse(0, 0, r0, r1, reg);
}
void ProtoBaseApp::ellipse(float x, float y, float r, Registration reg) {
	ellipse(x, y, r, r, reg);
}
void ProtoBaseApp::triangle(const Vec2& pt0, const Vec2& pt1, const Vec2& pt2) {
}
void ProtoBaseApp::triangle(float x0, float y0, float x1, float y1, float x2, float y2) {
}
void ProtoBaseApp::poly(int sides, float radius) {
}
void ProtoBaseApp::poly(int sides, float radius1, float radius2) {
}
void ProtoBaseApp::star(int sides, float innerRadius, float outerRadius, Registration reg) {
	if (starPrims.size() > 0) {
		starPrims.clear();
	}

	if (starStrokePrims.size() > 0) {
		starStrokePrims.clear();
	}

	float x = 0, y = 0;
	float _x = 0, _y = 0;

	/* CENTER,
	CORNER, // assumed top left
	CORNER_TR,
	CORNER_BR,
	CORNER_BL,
	RANDOM
	*/

	switch (reg) {
	case CENTER:
		_x = x;
		_y = y;
		break;
	case CORNER: // TL
		_x = x + outerRadius / 2;
		_y = y - outerRadius / 2;
		break;
	case CORNER_TR:
		_x = x - outerRadius / 2;
		_y = y - outerRadius / 2;
		break;
	case CORNER_BR:
		_x = x - outerRadius / 2;
		_y = y + outerRadius / 2;
		break;
	case CORNER_BL:
		_x = x + outerRadius / 2;
		_y = y + outerRadius / 2;
		break;
	case RANDOM:
		// to do
		break;

	}

	//Calculate p2t points and tessellate:
	std::vector<p2t::Point*> polyline;

	int stride = 7;
	float theta = 0.0;
	int pts = sides * 2;

	for (int i = 0; i < pts; i++) {
		if (i % 2 == 0) {
			polyline.push_back(new p2t::Point(_x + cos(theta) * outerRadius, _y + sin(theta) * outerRadius));

			// Required for outline
			starStrokePrims.push_back(_x + cos(theta) * outerRadius);
			starStrokePrims.push_back(_y + sin(theta) * outerRadius);
		}
		else {
			polyline.push_back(new p2t::Point(_x + cos(theta) * innerRadius, _y + sin(theta) * innerRadius));

			// Required for outline
			starStrokePrims.push_back(_x + cos(theta) * innerRadius);
			starStrokePrims.push_back(_y + sin(theta) * innerRadius);
		}

		// Required for outline
		starStrokePrims.push_back(0); //z
		starStrokePrims.push_back(fillColor.r);
		starStrokePrims.push_back(fillColor.g);
		starStrokePrims.push_back(fillColor.b);
		starStrokePrims.push_back(fillColor.a);

		theta += TWO_PI / pts;
	}

	//Tessellate for fill
	p2t::CDT* cdt = new p2t::CDT(polyline);
	cdt->Triangulate();

	// Get triangles
	std::vector<p2t::Triangle*> triangles;
	triangles = cdt->GetTriangles();

	// TO DO: refactor (too many loops)
	// populate primitives arr
	for (int i = 0; i < triangles.size(); i++) {
		for (int j = 0; j < 3; j++) {
			float x = triangles.at(i)->GetPoint(j)->x;
			float y = triangles.at(i)->GetPoint(j)->y;
			starPrims.push_back(x);
			starPrims.push_back(y);
			starPrims.push_back(0); //z
			starPrims.push_back(fillColor.r);
			starPrims.push_back(fillColor.g);
			starPrims.push_back(fillColor.b);
			starPrims.push_back(fillColor.a);
		}
	}

	if (isFill) {
		for (int i = 0; i < starPrims.size(); i += stride) {
			starPrims.at(i + 3) = fillColor.r;
			starPrims.at(i + 4) = fillColor.g;
			starPrims.at(i + 5) = fillColor.b;
			starPrims.at(i + 6) = fillColor.a;
		}

		enable2DRendering();
		glBindVertexArray(vaoStarID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboStarID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * starPrims.size();
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &starPrims[0]); // upload the data

		glDrawArrays(GL_TRIANGLES, 0, starPrims.size() / stride);
		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}
	if (isStroke) {
		for (int i = 0; i < starStrokePrims.size(); i += stride) {
			starStrokePrims.at(i + 3) = strokeColor.r;
			starStrokePrims.at(i + 4) = strokeColor.g;
			starStrokePrims.at(i + 5) = strokeColor.b;
			starStrokePrims.at(i + 6) = strokeColor.a;
		}
		// note: reusing star id's with different collection of primitives
		enable2DRendering();
		glBindVertexArray(vaoStarID);
		// NOTE::this may not be most efficient - eventually refactor
		glBindBuffer(GL_ARRAY_BUFFER, vboStarID); // Bind the buffer (vertex array data)
		int vertsDataSize = sizeof(GLfloat) * starStrokePrims.size();
		glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &starStrokePrims[0]); // upload the data

		glLineWidth(lineWidth);
		glDrawArrays(GL_LINE_LOOP, 0, starStrokePrims.size() / stride);

		disable2DRendering();

		// Disable VAO
		glBindVertexArray(0);
	}

	// clean up heap, from poly2tri tessellation
	for (int i = 0; i < polyline.size(); i++) {
		delete polyline.at(i);
	}
	delete cdt;
}

void ProtoBaseApp::star(int sides, const Vec2& radiusAndRatio) {
}

// PATH
void ProtoBaseApp::beginPath(PathRenderMode pathRenderMode) {
	//trace("beginPath hit");
	this->pathRenderMode = pathRenderMode;
	isPathRecording = true;
	pathVerticesAll.size() > 0 ? pathVerticesAll.clear() : 0;
	pathPrimsFill.size() > 0 ? pathPrimsFill.clear() : 0;
	pathPrimsStroke.size() > 0 ? pathPrimsStroke.clear() : 0;

	curveDetails.size() > 0 ? curveDetails.clear() : 0;
	curveTensions.size() > 0 ? curveTensions.clear() : 0;
	curveBiases.size() > 0 ? curveBiases.clear() : 0;
	pathStrokeWeights.size() > 0 ? pathStrokeWeights.clear() : 0;
	// keeps track of insertion points of curveVertices in path
	//curveVertexInsertionIndices.clear();
	//pathInds.clear();
}



void ProtoBaseApp::vertex(const Vec2f& vec) {
	vertex(vec.x, vec.y, 0);
}
void ProtoBaseApp::vertex(const Vec3f& vec) {
	vertex(vec.x, vec.y, vec.z);
}
void ProtoBaseApp::vertex(float x, float y) {
	vertex(x, y, 0);
}
void ProtoBaseApp::vertex(float x, float y, float z) {
	if (isPathRecording) {
		//trace("strokeColor=", strokeColor);
		//trace("fillColor=", fillColor);
		pathVerticesAll.push_back(
			std::tuple<Vec3f, char, Col4f, Col4f, float>(Vec3f(x, y, z), 'v', fillColor, strokeColor, lineWidth));
		//pathStrokeWeights.push_back(lineWidth);
	}
	else {
		trace("Path Recording Failure: You must precede vertex() calls with beginPath()");
	}
}

// Catmull-Rom implementation
void ProtoBaseApp::curveVertex(const Vec2f& vec) {
	curveVertex(vec.x, vec.y, 0);
}
void ProtoBaseApp::curveVertex(const Vec3f& vec) {
	curveVertex(vec.x, vec.y, vec.z);
}
void ProtoBaseApp::curveVertex(float x, float y) {
	curveVertex(x, y, 0);
}
void ProtoBaseApp::curveVertex(float x, float y, float z) {
	if (isPathRecording) {
		pathVerticesAll.push_back(std::tuple<Vec3f, char, Col4f, Col4f, float>(Vec3f(x, y, z), 'c', fillColor, strokeColor, lineWidth));
		curveDetails.push_back(_curveDetail);
		curveTensions.push_back(_curveTension);
		curveBiases.push_back(_curveBias);

	}
	else {
		trace("Path Recording Failure: You must precede curveVertex() calls with beginPath()");
	}
}

void ProtoBaseApp::curveDetail(int curveDetail) {
	_curveDetail = curveDetail;
}

void ProtoBaseApp::curveTension(float curveTension) {
	_curveTension = curveTension;
}

void ProtoBaseApp::curveBias(float curveBias) {
	_curveBias = curveBias;
}

// HERE
//void ProtoBaseApp::hermite() {
//	/*
//   Tension: 1 is high, 0 normal, -1 is low
//   Bias: 0 is even,
//		 positive is towards first segment,
//		 negative towards the other
//*/
///*	float HermiteInterpolate(
//		float y0, float y1,
//		float y2, float y3,
//		float mu,
//		float tension,
//		float bias)
//	{
//		*/
//	float mu = 0.0f;
//
//	for (int i = 0; i < pathVerticesAll.size(); ++i) {
//		if (i > 1 && i < pathVerticesAll.size() - 2) {
//			float m0, m1, mu2, mu3;
//			float a0, a1, a2, a3;
//			
//			auto v = pathVerticesAll.at(i - 1);
//			Vec y0 = std::get<0>(v);
//			Col4 c0 = std::get<3>(v);
//			float wt0 = std::get<4>(v);
//
//			v = pathVerticesAll.at(i);
//			Vec y1 = std::get<0>(v);
//			Col4 c1 = std::get<3>(v);
//			float wt1 = std::get<4>(v);
//
//			v = pathVerticesAll.at(i+1);
//			Vec y2 = std::get<0>(v);
//			Col4 c1 = std::get<3>(v);
//			float wt1 = std::get<4>(v);
//
//			v = pathVerticesAll.at(i+2);
//			Vec y3 = std::get<0>(v);
//			Col4 c1 = std::get<3>(v);
//			float wt1 = std::get<4>(v);
//			
//
//			mu2 = mu * mu;
//			mu3 = mu2 * mu;
//			m0 = (y1 - y0) * (1 + bias) * (1 - tension) / 2;
//			m0 += (y2 - y1) * (1 - bias) * (1 - tension) / 2;
//			m1 = (y2 - y1) * (1 + bias) * (1 - tension) / 2;
//			m1 += (y3 - y2) * (1 - bias) * (1 - tension) / 2;
//			a0 = 2 * mu3 - 3 * mu2 + 1;
//			a1 = mu3 - 2 * mu2 + mu;
//			a2 = mu3 - mu2;
//			a3 = -2 * mu3 + 3 * mu2;
//		}
//	}
//
//	//return(a0 * y1 + a1 * m0 + a2 * m1 + a3 * y2);
//	//}
//
//}


void ProtoBaseApp::endPath(PathEnd pathEnd) {
	isPathRecording = false;

	auto test = pathVerticesAll.at(0);
	std::get<0>(test);

	//trace("pathVerticesAll.at(2)=", std::get<2>(test));
	//trace("pathVerticesAll.at(3)=", std::get<3>(test));

	// eventually parameterize these
	//int interpDetail = 3;
	//float smoothness = .7;

	//Calculate p2t points and tessellate:
	//std::vector<p2t::Point*> polyline;  // TO DO
	//p2t::CDT* cdt;

	if (pathVerticesAll.size() > 0) {
		//if (pathVerticesAll.size() < 3) {
		//	//	pathRenderMode = LINE_STRIP;
		//}

		// complete loop adding:
		// before
		//curveVertex(pts.at(pts.size() - 2));
		//curveVertex(pts.at(pts.size()-1));
		// after
		//curveVertex(pts.at(0));
		//curveVertex(pts.at(1));
		if (pathEnd == CLOSE_SMOOTH) {
			//trace("here");
			//local var for convenience
			auto p = pathVerticesAll;
			//trace("p.size() before=", p.size());
			// get tuples to copy
			auto vMinus2 = p.at(p.size() - 2);
			auto vMinus1 = p.at(p.size() - 1);
			auto vZero = p.at(0);
			auto it = p.insert(p.begin(), vMinus1);
			p.insert(it, vMinus2);
			it = p.end();
			p.insert(it, vZero);
			pathVerticesAll = p;

			//curve details
			auto d = curveDetails;
			
			// get ints to copy
			int m2 = d.at(d.size() - 2);
			int m1 = d.at(d.size() - 1);
			int zero = d.at(0);

			// get iterator of int
			auto i = d.insert(d.begin(), m1);
			d.insert(i, m2);
			i = d.end();
			d.insert(i, zero);
			curveDetails = d;

			//curve Tensions
			auto t = curveTensions;

			// get floats to copy
			int tm2 = t.at(t.size() - 2);
			int tm1 = t.at(t.size() - 1);
			int tZero = t.at(0);

			// get iterator of float
			auto id = t.insert(t.begin(), tm1);
			t.insert(id, tm2);
			id = t.end();
			t.insert(id, tZero);
			curveTensions = t;

			//curve Biases
			auto b = curveBiases;

			// get floats to copb
			int bm2 = b.at(b.size() - 2);
			int bm1 = b.at(b.size() - 1);
			int bZero = b.at(0);

			// get iterator of float
			auto ib = b.insert(b.begin(), bm1);
			b.insert(ib, bm2);
			ib = b.end();
			b.insert(ib, bZero);
			curveBiases = b;

		}
		
		for (int i = 1; i < pathVerticesAll.size()-1; ++i) {

			// detected curve vertex: create spline segment
			Col4f c1, c2;
			float wt1, wt2;
			auto c = pathVerticesAll.at(i);
			char flag = std::get<1>(c);
			if (flag == 'c') {  // Curve request detected
				Vec3f v0, v1, v2, v3;
				float t2 = 0, t3 = 0;
				float step = 1.0 / (curveDetails.at(i) + 1);
				if (i > 0 && i < pathVerticesAll.size() - 2) {
					// calc Hermite algorithm vars
					auto v = pathVerticesAll.at(i - 1); // Note: will reuse v
					v0 = std::get<0>(v);
					c1 = std::get<3>(v);
					wt1 = std::get<4>(v);

					v = pathVerticesAll.at(i);
					v1 = std::get<0>(v);
					c2 = std::get<3>(v);
					wt2 = std::get<4>(v);

					
					v = pathVerticesAll.at(i + 1);
					v2 = std::get<0>(v);

					v = pathVerticesAll.at(i + 2);
					v3 = std::get<0>(v);

					// NOTE: add overloaded op func at some point
					//Col4f deltaCol = c2 - c1;
					// stroke only at present
					float deltaR = (c2.r - c1.r) / (curveDetails.at(i) + 1);
					//trace("deltaR =", deltaR);
					float deltaG = (c2.g - c1.g) / (curveDetails.at(i) + 1);
					float deltaB = (c2.b - c1.b) / (curveDetails.at(i) + 1);
					float deltaA = (c2.a - c1.a) / (curveDetails.at(i) + 1);

					float deltaWeight = (wt2 - wt1) / (curveDetails.at(i) + 1);

					// hermite implementation
					//float curveTension = -3;
					//float bias = 0;
					float a0, a1, a2, a3;
					Vec3f m0, m1;

					for (float t = 0; t < 1; t += step) {
						t2 = t * t;
						t3 = t * t2;
						float tf = 1.0f;
						// from: http://www.mvps.org/directx/articles/catmull/

						// Catmull-Rom (working)
						//Vec3f v = 0.5f * (
						//	(2.0f * v1) +
						//	(-v0 + v2) * t +
						//	(2.0f * v0 - 5.0f * v1 + 4.0f * v2 - v3) * t2 +
						//	(-v0 + 3.0f * v1 - 3.0f * v2 + v3) * t3
						//	);

						// Catmull-Rom with tightness factor (screwed up for some reaon ;-{)
						/*Vec3f v = v1 +
							(-tf*v0 + tf*v2) * t +
							(2*tf*v0 + (tf-3)*v1 + (3-2*tf)*v2 - tf*v3) * t2 +
							(tf*v0 + (2-tf)*v1 + (tf-2)*v2 + tf*v3) * t3;*/

						// Hermite Implementation from Master Bourke (who else?)
						// http://paulbourke.net/miscellaneous/interpolation/
						m0 = (v1 - v0) * (1 + curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
						m0 += (v2 - v1) * (1 - curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
						m1 = (v2 - v1) * (1 + curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
						m1 += (v3 - v2) * (1 - curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
						a0 = 2 * t3 - 3 * t2 + 1;
						a1 = t3 - 2 * t2 + t;
						a2 = t3 - t2;
						a3 = -2 * t3 + 3 * t2;

						Vec3f v = a0 * v1 + a1 * m0 + a2 * m1 + a3 * v2;

						//trace("c1.r + deltaR*t =", c1.r + deltaR*t);
						strokeWeight(wt1 + deltaWeight * t);
						Col4f sc(c1.r + deltaR * t, c1.g + deltaG * t, c1.b + deltaB * t, c1.a + deltaA * t);
						//trace(sc);

						// for tessellation -problem I think with duplicate points
						//polyline.push_back(new p2t::Point(v.x, v.y));
						/*pathPrimsFill.push_back(PathPrims(v.x, v.y, v.z, fillColor.r, fillColor.b, fillColor.g, fillColor.a));*/
						pathPrimsStroke.push_back(PathPrims(v.x, v.y, v.z, sc.r, sc.g, sc.b, sc.a));
					}
				}
				else {

					// begin linear plot

					/*auto v = pathVerticesAll.at(i);
					v0 = std::get<0>(v);
					c1 = std::get<3>(v);
					c2 = std::get<3>(v); */


					// detected linear vertex
					auto v = pathVerticesAll.at(i);
					//trace("pathVerticesAll.at(2)=", std::get<2>(v));
					//trace("pathVerticesAll.at(3)=", std::get<3>(v));

					//trace(std::get<3>(v));
					// for tessellation
					//polyline.push_back(new p2t::Point((float)std::get<0>(v).x, (float)std::get<0>(v).y));

					pathPrimsFill.push_back(PathPrims(std::get<0>(v).x, std::get<0>(v).y, std::get<0>(v).z,
						std::get<2>(v).r, std::get<2>(v).g, std::get<2>(v).b, std::get<2>(v).a));
					//trace(std::get<2>(v).r, std::get<2>(v).g, std::get<2>(v).b);
					//trace("std::get<2>(v)=", std::get<2>(v));
					pathPrimsStroke.push_back(PathPrims(std::get<0>(v).x, std::get<0>(v).y, std::get<0>(v).z,
						std::get<3>(v).r, std::get<3>(v).g, std::get<3>(v).b, std::get<3>(v).a));
					//trace(std::get<3>(v).r, std::get<3>(v).g, std::get<3>(v).b, std::get<3>(v).a);
					/*pathPrimsStroke.push_back(PathPrims(std::get<0>(v).x, std::get<0>(v).y, std::get<0>(v).z,
						1.0, .5f, 0, std::get<2>(v).a));*/
				}
			}
		}


		//// rotate geometry prior to tesslelation
		////1. get face normal
		//p2t::Point p0 = *polyline.at(0);
		//p2t::Point p1 = *polyline.at(1);
		//p2t::Point p2 = *polyline.at(2);
		//p2 -= p0;
		//p1 -= p0;
		//p2.Normalize();
		//p1.Normalize();



		//Vec3 rot_axis = normalize(cross(axis_z, triangle_normal))
		//	the rot_angle that you already calculated :

		//rot_angle = acos(dot(axis_z, triangle_normal))





		//Tessellate for fill
		//cdt = new p2t::CDT(polyline);
		//cdt->Triangulate();

		// Get triangles
		/*
		std::vector<p2t::Triangle*> triangles;
		triangles = cdt->GetTriangles();
		for (int i = 0; i <  triangles.size(); i++) {
			for (int j = 0; j < 3; j++) {
				//trace("triangle:", i, ",pts:", j, " = ", triangles.at(i)->GetPoint(j)->x, ",", triangles.at(i)->GetPoint(j)->y);
				pathPrimsFill.push_back(PathPrims(triangles.at(i)->GetPoint(j)->x, triangles.at(i)->GetPoint(j)->y, 0, fillColor.r, fillColor.b, fillColor.g, fillColor.a));
			}
		}

		*/


		switch (pathRenderMode) {
		case POLYGON:
			enable2DRendering(); // turn off 3D lighting
			glBindVertexArray(vaoPathID);
			// NOTE::this may not be most efficient - eventually refactor
			glBindBuffer(GL_ARRAY_BUFFER, vboPathID); // Bind the buffer (vertex array data)
			if (isFill) {
				// using struct prims for coding tersity
				int vertsDataSize = sizeof(PathPrims) * pathPrimsFill.size();
				glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
				glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrimsFill[0].x); // upload the data

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glDrawArrays(GL_TRIANGLES, 0, pathPrimsFill.size());

			}
			if (isStroke) {
				// using struct prims for coding tersity
				int vertsDataSize = sizeof(PathPrims) * pathPrimsStroke.size();
				glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
				glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrimsStroke[0].x); // upload the data

				glLineWidth(lineWidth);

				// closed path
				if (pathEnd == CLOSE) {
					//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glDrawArrays(GL_LINE_LOOP, 0, pathPrimsStroke.size());
				}
				// open path
				else if(pathEnd == OPEN || pathEnd == CLOSE_SMOOTH) {
					//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					//trace("here", "here", "here");
					glDrawArrays(GL_LINE_STRIP, 0, pathPrimsStroke.size());
				}
			}

			disable2DRendering(); // turn on 3D lighting
			// Disable VAO
			glBindVertexArray(0);

			break;
		case TRIANGLES:
			//glDrawArrays(GL_TRIANGLES, 0, pathPrims.size() / stride);
			glDrawArrays(GL_TRIANGLES, 0, pathPrimsFill.size());
			break;
		case TRIANGLE_STRIP:
			//glDrawArrays(GL_TRIANGLE_STRIP, 0, pathPrims.size() / stride);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, pathPrimsFill.size());
			break;
		case TRIANGLE_FAN:
			//glDrawArrays(GL_TRIANGLE_FAN, 0, pathPrims.size() / stride);
			glDrawArrays(GL_TRIANGLE_FAN, 0, pathPrimsFill.size());
			break;
		default:
			//glDrawArrays(GL_POLYGON, 0, pathPrims.size() / stride);
			glDrawArrays(GL_TRIANGLE_FAN, 0, pathPrimsFill.size());

		}

		// reenable 3D lighting
		disable2DRendering();

		// clean up vectors between each frame
		pathPrimsStroke.clear();
		pathPrimsFill.clear();
		pathVerticesAll.clear();

		// clean up heap
		// clean up heap, from poly2tri tessellation
		/*
		for (int i = 0; i < polyline.size(); i++) {
			delete polyline.at(i);
		}
		delete cdt;
		*/
	}
}



	//void ProtoBaseApp::endPath(bool isClosed) {
	//	isPathRecording = false;
	//
	//	auto test = pathVerticesAll.at(0);
	//	std::get<0>(test);
	//
	//	//trace("pathVerticesAll.at(2)=", std::get<2>(test));
	//	//trace("pathVerticesAll.at(3)=", std::get<3>(test));
	//
	//	// eventually parameterize these
	//	//int interpDetail = 3;
	//	//float smoothness = .7;
	//
	//	//Calculate p2t points and tessellate:
	//	//std::vector<p2t::Point*> polyline;  // TO DO
	//	//p2t::CDT* cdt;
	//
	//	if (pathVerticesAll.size() > 0) {
	//		if (pathVerticesAll.size() < 3) {
	//			//	pathRenderMode = LINE_STRIP;
	//		}
	//
	//		for (int i = 0; i < pathVerticesAll.size(); ++i) {
	//
	//			// detected curve vertex: create spline segment
	//			Col4f c1, c2;
	//			float wt1, wt2;
	//			auto c = pathVerticesAll.at(i);
	//			char flag = std::get<1>(c);
	//			if (flag == 'c') {
	//				Vec3f v0, v1, v2, v3;
	//				float t2 = 0, t3 = 0;
	//				float step = 1.0 / (curveDetails.at(i) + 1);
	//				if (i > 0) {
	//					// within bounds
	//					auto v = pathVerticesAll.at(i - 1);
	//					v0 = std::get<0>(v);
	//					c1 = std::get<3>(v);
	//					wt1 = std::get<4>(v);
	//				}
	//				else {
	//					// will exceed left bounds so double up
	//					auto v = pathVerticesAll.at(i);
	//					v0 = std::get<0>(v);
	//					c1 = std::get<3>(v);
	//					c2 = std::get<3>(v);
	//
	//					wt1 = std::get<4>(v);
	//					wt2 = std::get<4>(v);
	//
	//				}
	//
	//				// within bounds
	//				auto v = pathVerticesAll.at(i);
	//				v1 = std::get<0>(v);
	//				c2 = std::get<3>(v);
	//				wt2 = std::get<4>(v);
	//				if (i < pathVerticesAll.size() - 2) {
	//					// still at safe rigt bounds
	//					auto v = pathVerticesAll.at(i + 1);
	//					v2 = std::get<0>(v);
	//					//c2 = std::get<3>(v);
	//
	//					v = pathVerticesAll.at(i + 2);
	//					v3 = std::get<0>(v);
	//				}
	//				else if (i < pathVerticesAll.size() - 1) {
	//					// will exceed right bounds so double up
	//					auto v = pathVerticesAll.at(i + 1);
	//					v2 = std::get<0>(v);
	//					//c2 = std::get<3>(v);
	//
	//					v3 = std::get<0>(v);
	//				}
	//				else {
	//					// will exceed right bounds so triple up
	//					auto v = pathVerticesAll.at(i);
	//					v2 = std::get<0>(v);
	//					c2 = std::get<3>(v);
	//					wt2 = std::get<4>(v);
	//
	//					v3 = std::get<0>(v);
	//				}
	//				//trace("c1 =", c1);
	//				//trace("c2 =", c2);
	//				// NOTE: add overloaded op func at some point
	//				//Col4f deltaCol = c2 - c1;
	//				// stroke only at present
	//				float deltaR = (c2.r - c1.r) / (curveDetails.at(i) + 1);
	//				//trace("deltaR =", deltaR);
	//				float deltaG = (c2.g - c1.g) / (curveDetails.at(i) + 1);
	//				float deltaB = (c2.b - c1.b) / (curveDetails.at(i) + 1);
	//				float deltaA = (c2.a - c1.a) / (curveDetails.at(i) + 1);
	//
	//				float deltaWeight = (wt2 - wt1) / (curveDetails.at(i) + 1);
	//
	//				// hermite implementation
	//				//float curveTension = -3;
	//				//float bias = 0;
	//				float a0, a1, a2, a3;
	//				Vec3f m0, m1;
	//
	//				for (float t = 0; t < 1; t += step) {
	//					t2 = t * t;
	//					t3 = t * t2;
	//					float tf = 1.0f;
	//					// from: http://www.mvps.org/directx/articles/catmull/
	//
	//					// Catmull-Rom (working)
	//					//Vec3f v = 0.5f * (
	//					//	(2.0f * v1) +
	//					//	(-v0 + v2) * t +
	//					//	(2.0f * v0 - 5.0f * v1 + 4.0f * v2 - v3) * t2 +
	//					//	(-v0 + 3.0f * v1 - 3.0f * v2 + v3) * t3
	//					//	);
	//
	//					// Catmull-Rom with tightness factor (screwed up for some reaon ;-{)
	//					/*Vec3f v = v1 +
	//						(-tf*v0 + tf*v2) * t +
	//						(2*tf*v0 + (tf-3)*v1 + (3-2*tf)*v2 - tf*v3) * t2 +
	//						(tf*v0 + (2-tf)*v1 + (tf-2)*v2 + tf*v3) * t3;*/
	//
	//						// Hermite Implementation from Master Bourke (who else?)
	//						// http://paulbourke.net/miscellaneous/interpolation/
	//					m0 = (v1 - v0) * (1 + curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
	//					m0 += (v2 - v1) * (1 - curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
	//					m1 = (v2 - v1) * (1 + curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
	//					m1 += (v3 - v2) * (1 - curveBiases.at(i)) * (1 - curveTensions.at(i)) / 2.0f;
	//					a0 = 2 * t3 - 3 * t2 + 1;
	//					a1 = t3 - 2 * t2 + t;
	//					a2 = t3 - t2;
	//					a3 = -2 * t3 + 3 * t2;
	//
	//					Vec3f v = a0 * v1 + a1 * m0 + a2 * m1 + a3 * v2;
	//
	//					//trace("c1.r + deltaR*t =", c1.r + deltaR*t);
	//					strokeWeight(wt1 + deltaWeight * t);
	//					Col4f sc(c1.r + deltaR * t, c1.g + deltaG * t, c1.b + deltaB * t, c1.a + deltaA * t);
	//					//trace(sc);
	//
	//					// for tessellation -problem I think with duplicate points
	//					//polyline.push_back(new p2t::Point(v.x, v.y));
	//					/*pathPrimsFill.push_back(PathPrims(v.x, v.y, v.z, fillColor.r, fillColor.b, fillColor.g, fillColor.a));*/
	//					pathPrimsStroke.push_back(PathPrims(v.x, v.y, v.z, sc.r, sc.g, sc.b, sc.a));
	//				}
	//
	//				// linear plot
	//			}
	//			else {
	//
	//				/*auto v = pathVerticesAll.at(i);
	//				v0 = std::get<0>(v);
	//				c1 = std::get<3>(v);
	//				c2 = std::get<3>(v); */
	//
	//
	//				// detected linear vertex
	//				auto v = pathVerticesAll.at(i);
	//				//trace("pathVerticesAll.at(2)=", std::get<2>(v));
	//				//trace("pathVerticesAll.at(3)=", std::get<3>(v));
	//
	//				//trace(std::get<3>(v));
	//				// for tessellation
	//				//polyline.push_back(new p2t::Point((float)std::get<0>(v).x, (float)std::get<0>(v).y));
	//
	//				pathPrimsFill.push_back(PathPrims(std::get<0>(v).x, std::get<0>(v).y, std::get<0>(v).z,
	//					std::get<2>(v).r, std::get<2>(v).g, std::get<2>(v).b, std::get<2>(v).a));
	//				//trace(std::get<2>(v).r, std::get<2>(v).g, std::get<2>(v).b);
	//				//trace("std::get<2>(v)=", std::get<2>(v));
	//				pathPrimsStroke.push_back(PathPrims(std::get<0>(v).x, std::get<0>(v).y, std::get<0>(v).z,
	//					std::get<3>(v).r, std::get<3>(v).g, std::get<3>(v).b, std::get<3>(v).a));
	//				//trace(std::get<3>(v).r, std::get<3>(v).g, std::get<3>(v).b, std::get<3>(v).a);
	//				/*pathPrimsStroke.push_back(PathPrims(std::get<0>(v).x, std::get<0>(v).y, std::get<0>(v).z,
	//					1.0, .5f, 0, std::get<2>(v).a));*/
	//			}
	//		}
	//	}
	//
	//
	//	//// rotate geometry prior to tesslelation
	//	////1. get face normal
	//	//p2t::Point p0 = *polyline.at(0);
	//	//p2t::Point p1 = *polyline.at(1);
	//	//p2t::Point p2 = *polyline.at(2);
	//	//p2 -= p0;
	//	//p1 -= p0;
	//	//p2.Normalize();
	//	//p1.Normalize();
	//
	//
	//
	//	//Vec3 rot_axis = normalize(cross(axis_z, triangle_normal))
	//	//	the rot_angle that you already calculated :
	//
	//	//rot_angle = acos(dot(axis_z, triangle_normal))
	//
	//
	//
	//
	//
	//	//Tessellate for fill
	//	//cdt = new p2t::CDT(polyline);
	//	//cdt->Triangulate();
	//
	//	// Get triangles
	//	/*
	//	std::vector<p2t::Triangle*> triangles;
	//	triangles = cdt->GetTriangles();
	//	for (int i = 0; i <  triangles.size(); i++) {
	//		for (int j = 0; j < 3; j++) {
	//			//trace("triangle:", i, ",pts:", j, " = ", triangles.at(i)->GetPoint(j)->x, ",", triangles.at(i)->GetPoint(j)->y);
	//			pathPrimsFill.push_back(PathPrims(triangles.at(i)->GetPoint(j)->x, triangles.at(i)->GetPoint(j)->y, 0, fillColor.r, fillColor.b, fillColor.g, fillColor.a));
	//		}
	//	}
	//
	//	*/
	//
	//
	//	switch (pathRenderMode) {
	//	case POLYGON:
	//		enable2DRendering(); // turn off 3D lighting
	//		glBindVertexArray(vaoPathID);
	//		// NOTE::this may not be most efficient - eventually refactor
	//		glBindBuffer(GL_ARRAY_BUFFER, vboPathID); // Bind the buffer (vertex array data)
	//		if (isFill) {
	//			// using struct prims for coding tersity
	//			int vertsDataSize = sizeof(PathPrims) * pathPrimsFill.size();
	//			glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	//			glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrimsFill[0].x); // upload the data
	//
	//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//			glDrawArrays(GL_TRIANGLES, 0, pathPrimsFill.size());
	//
	//		}
	//		if (isStroke) {
	//			// using struct prims for coding tersity
	//			int vertsDataSize = sizeof(PathPrims) * pathPrimsStroke.size();
	//			glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	//			glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &pathPrimsStroke[0].x); // upload the data
	//
	//			glLineWidth(lineWidth);
	//
	//			// closed path
	//			if (isClosed) {
	//				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//				glDrawArrays(GL_LINE_LOOP, 0, pathPrimsStroke.size());
	//			}
	//			// open path
	//			else {
	//				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//				//trace("here", "here", "here");
	//				glDrawArrays(GL_LINE_STRIP, 0, pathPrimsStroke.size());
	//			}
	//		}
	//
	//		disable2DRendering(); // turn on 3D lighting
	//		// Disable VAO
	//		glBindVertexArray(0);
	//
	//		break;
	//	case TRIANGLES:
	//		//glDrawArrays(GL_TRIANGLES, 0, pathPrims.size() / stride);
	//		glDrawArrays(GL_TRIANGLES, 0, pathPrimsFill.size());
	//		break;
	//	case TRIANGLE_STRIP:
	//		//glDrawArrays(GL_TRIANGLE_STRIP, 0, pathPrims.size() / stride);
	//		glDrawArrays(GL_TRIANGLE_STRIP, 0, pathPrimsFill.size());
	//		break;
	//	case TRIANGLE_FAN:
	//		//glDrawArrays(GL_TRIANGLE_FAN, 0, pathPrims.size() / stride);
	//		glDrawArrays(GL_TRIANGLE_FAN, 0, pathPrimsFill.size());
	//		break;
	//	default:
	//		//glDrawArrays(GL_POLYGON, 0, pathPrims.size() / stride);
	//		glDrawArrays(GL_TRIANGLE_FAN, 0, pathPrimsFill.size());
	//
	//	}
	//
	//	// reenable 3D lighting
	//	disable2DRendering();
	//
	//	// clean up vectors between each frame
	//	pathPrimsStroke.clear();
	//	pathPrimsFill.clear();
	//	pathVerticesAll.clear();
	//
	//	// clean up heap
	//	// clean up heap, from poly2tri tessellation
	//	/*
	//	for (int i = 0; i < polyline.size(); i++) {
	//		delete polyline.at(i);
	//	}
	//	delete cdt;
	//	*/
	//}

	void ProtoBaseApp::line(float x1, float y1, float x2, float y2) {
		beginShape();
		vertex(x1, y1);
		vertex(x2, y2);
		endShape();
	}
	void ProtoBaseApp::line(float x1, float y1, float z1, float x2, float y2, float z2) {
		beginShape();
		vertex(x1, y1, z1);
		vertex(x2, y2, z2);
		endShape();
	}

	void ProtoBaseApp::point(float x, float y, float z) {
		glDisable(GL_DITHER);
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		glHint(GL_POINT_SMOOTH, GL_DONT_CARE);
		glHint(GL_LINE_SMOOTH, GL_DONT_CARE);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
#define GL_MULTISAMPLE_ARB 0x809D
		glDisable(GL_MULTISAMPLE_ARB);
		noStroke();
		if (lineWidth < 2) {
			rect(x, y, z, 1, 1);
		}
		else {
			ellipse(x, y, z, lineWidth, lineWidth);
		}
		stroke(strokeColor);
		glEnable(GL_DITHER);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POINT_SMOOTH, GL_NICEST);
		glHint(GL_LINE_SMOOTH, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
#define GL_MULTISAMPLE_ARB 0x809D
		glEnable(GL_MULTISAMPLE_ARB);

	}

	void ProtoBaseApp::point(float x, float y) {
		point(x, y, 0);
	}


	/****END 2D API****/
	//3D
	void ProtoBaseApp::box(float sz, Registration reg) {
		box(sz, sz, sz, CENTER);
	}

	void ProtoBaseApp::box(float w, float h, float d, Registration reg) {
		//float _x = 0, _y = 0;

		///* CENTER,
		//CORNER, // assumed top left
		//CORNER_TR,
		//CORNER_BR,
		//CORNER_BL,
		//RANDOM
		//*/

		//switch (reg){
		//case CENTER:
		//	_x = x;
		//	_y = y;
		//	break;
		//case CORNER: // TL
		//	_x = x + w / 2;
		//	_y = y - h / 2;
		//case CORNER_BR:
		//	break;
		//case CORNER_TR:
		//	_x = x - w / 2;
		//	_y = y - h / 2;
		//	break;
		//	_x = x - w / 2;
		//	_y = y + h / 2;
		//	break;
		//case CORNER_BL:
		//	_x = x + w / 2;
		//	_y = y + h / 2;
		//	break;
		//case RANDOM:
		//	// to do
		//	break;

		//}



		int stride = 15;

		for (int i = 0; i < boxPrimCount; i += stride) {
			boxPrims[i] = boxPrimsOrig[i] * w;
			boxPrims[i + 1] = boxPrimsOrig[i + 1] * h;
			boxPrims[i + 2] = boxPrimsOrig[i + 2] * d;
		}
		//for (int i = 0; i < boxPrimCount; i+=15){
		//	boxPrims[i] *= w;
		//	boxPrims[i + 1] *= h;
		//	boxPrims[i + 2] *= d;
		//}

		if (isFill) {

			//GLuint diffMap = boxDiffuseMapTexture.getTextureID();
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, diffMap);

			//GLuint bumpMap = boxBumpMapTexture.getTextureID();
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, bumpMap);


			for (int i = 0; i < boxPrimCount; i += stride) {
				boxPrims[i + 6] = fillColor.r;
				boxPrims[i + 7] = fillColor.g;
				boxPrims[i + 8] = fillColor.b;
				boxPrims[i + 9] = fillColor.a;
			}

			//enable2DRendering();
			glBindVertexArray(vaoBoxID);
			// NOTE::this may not be most efficient - eventually refactor
			glBindBuffer(GL_ARRAY_BUFFER, vboBoxID); // Bind the buffer (vertex array data)
			int vertsDataSize = sizeof(GLfloat) * boxPrimCount;
			glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &boxPrims[0]); // upload the data
			glPolygonMode(GL_FRONT, GL_FILL);
			glDrawArrays(GL_QUADS, 0, boxPrimCount / stride);
			//disable2DRendering();

			// Disable VAO
			glBindVertexArray(0);
		}




		if (isStroke) {
			//trace("in here");
			for (int i = 0; i < boxPrimCount; i += stride) {
				boxPrims[i + 6] = strokeColor.r;
				boxPrims[i + 7] = strokeColor.g;
				boxPrims[i + 8] = strokeColor.b;
				boxPrims[i + 9] = strokeColor.a;
			}

			enable2DRendering();
			glBindVertexArray(vaoBoxID);
			// NOTE::this may not be most efficient - eventually refactor
			glBindBuffer(GL_ARRAY_BUFFER, vboBoxID); // Bind the buffer (vertex array data)
			int vertsDataSize = sizeof(GLfloat) * boxPrimCount;
			glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &boxPrims[0]); // upload the data

			glLineWidth(lineWidth);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_QUADS, 0, boxPrimCount / stride);

			disable2DRendering();

			// Disable VAO
			glBindVertexArray(0);
		}
	}



	//void ProtoBaseApp::render(int scaleFactor){}; // "should be" overridden in derived classes

	// was working
	//void ProtoBaseApp::export(std::vector<Tup4v> vs, Format type){
	//#if defined (_WIN32) || defined(_WIN64)
	//	time_t now = time(0);
	//	tm ltm;
	//	localtime_s(&ltm, &now);
	//#else // os x uses localtime instead of localtime_s
	//	time_t now = time(0);
	//	tm* ltm = localtime(&now);
	//#endif
	//
	//	//trace("geomData.size() =", faces.size());
	//
	//	std::stringstream stream;
	//	stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
	//
	//	std::string url = ProtoUtility::getPathToOutput();
	//	std::string directory = url + "data" + "_" + stream.str();
	//	CreateDirectory(directory.c_str(), 0);
	//
	//	std::ofstream myfile;
	//	myfile.open(directory + "/geomdata" + stream.str() + ".stl");
	//
	//	myfile << "solid protobyte\n";
	//	for (int i = 0; i < vs.size() - 4; i++) {
	//		//trace("allFaces.at(i).v0_p->pos =", allFaces.at(i).getVert0_ptr()->pos);
	//		myfile << "\tfacet normal " <<
	//			vs.at(i).elem0.x << " " << vs.at(i).elem0.y << " " << vs.at(i).elem0.z << "\n" <<
	//			"\t\touter loop\n" <<
	//			"\t\t\tvertex " << vs.at(i).elem1.x << " " << vs.at(i).elem1.y << " " << vs.at(i).elem1.z << "\n" <<
	//			"\t\t\tvertex " << vs.at(i).elem2.x << " " << vs.at(i).elem2.y << " " << vs.at(i).elem2.z << "\n" <<
	//			"\t\t\tvertex " << vs.at(i).elem3.x << " " << vs.at(i).elem3.y << " " << vs.at(i).elem3.z << "\n" <<
	//			"\t\tendloop\n" <<
	//			"\tendfacet\n";
	//	}
	//	myfile << "endsolid protobyte\n";
	//
	//	myfile.close();
	//	std::cout << "stl file successfully written" << std::endl;
	//}






	//template<typename First, typename ... Rest>
	//void ProtoBaseApp::export(Format type, First first, Rest ... rest) {
	//#if defined (_WIN32) || defined(_WIN64)
	//	time_t now = time(0);
	//	tm ltm;
	//	localtime_s(&ltm, &now);
	//#else // os x uses localtime instead of localtime_s
	//	time_t now = time(0);
	//	tm* ltm = localtime(&now);
	//#endif
	//
	//	//trace("geomData.size() =", faces.size());
	//
	//	std::stringstream stream;
	//	stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
	//
	//	std::string url = ProtoUtility::getPathToOutput();
	//	std::string directory = url + "data" + "_" + stream.str();
	//	CreateDirectory(directory.c_str(), 0);
	//
	//	std::ofstream myfile;
	//	myfile.open(directory + "/geomdata" + stream.str() + ".stl");
	//
	//	myfile << "solid protobyte\n";
	//	for (int i = 0; i < vs.size() - 4; i++) {
	//		//trace("allFaces.at(i).v0_p->pos =", allFaces.at(i).getVert0_ptr()->pos);
	//		myfile << "\tfacet normal " <<
	//			vs.at(i).elem0.x << " " << vs.at(i).elem0.y << " " << vs.at(i).elem0.z << "\n" <<
	//			"\t\touter loop\n" <<
	//			"\t\t\tvertex " << vs.at(i).elem1.x << " " << vs.at(i).elem1.y << " " << vs.at(i).elem1.z << "\n" <<
	//			"\t\t\tvertex " << vs.at(i).elem2.x << " " << vs.at(i).elem2.y << " " << vs.at(i).elem2.z << "\n" <<
	//			"\t\t\tvertex " << vs.at(i).elem3.x << " " << vs.at(i).elem3.y << " " << vs.at(i).elem3.z << "\n" <<
	//			"\t\tendloop\n" <<
	//			"\tendfacet\n";
	//	}
	//	myfile << "endsolid protobyte\n";
	//
	//	myfile.close();
	//	std::cout << "stl file successfully written" << std::endl;
	//
	//}

	void ProtoBaseApp::save(std::string name, int scaleFactor) {
		//trace("ProtoUtility::getPathToOutput() =", ProtoUtility::getPathToOutput());
		//if (getFrameCount() < 1){

		//ProtoBaseApp pba;
		//std::thread t(&ProtoBaseApp::threadSave, &pba, name, scaleFactor);
		//t.join();



#if defined (_WIN32) || defined(_WIN64)
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
#else // os x uses localtime instead of localtime_s
		time_t now = time(0);
		tm* ltm = localtime(&now);
#endif

		// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
		std::stringstream stream;
		stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;



		std::string url = ProtoUtility::getPathToOutput();
		std::string directory = url + name + "_" + stream.str();
		//trace("directory = ", directory);
		CreateDirectory(directory.c_str(), 0);


		/*trace("width =", width);
		trace("height =", height);*/
		for (int i = 0; i < scaleFactor; ++i) {
			for (int j = 0; j < scaleFactor; ++j) {
				//trace("in drawToFrameBuffer");
				//glClearColor(0, 0, 0, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				//From: http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl

				//glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
				//if (i == 0) trace("scaleFactor =", scaleFactor);
				render(-i, -j, scaleFactor);
				//trace(" in loop, in save");
				/*glReadPixels(0, 0, WIDTH, HEIGHT, GL_BGR, GL_BYTE, pixels);
				FIBITMAP Image = FreeImage_ConvertFromRawBits(pixels, WIDTH, HEIGHT, 3WIDTH, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
				FreeImage_Save(FIF_BMP, Image, "test.bmp", 0)*/


				//after drawing
				std::vector<uint8_t> data(width * height * 3);
				glReadBuffer(GL_BACK);
				//glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);
				//glPixelStorei(GL_PACK_ALIGNMENT, 1);
				glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);

				//std::vector<std::uint8_t> data(width*height * 4);
				//glReadBuffer(GL_BACK);
				//glReadPixels(0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, &data[0]);



#if defined (_WIN32) || defined(_WIN64)
				time_t now = time(0);
				tm ltm;
				localtime_s(&ltm, &now);
#else // os x uses localtime instead of localtime_s
				time_t now = time(0);
				tm* ltm = localtime(&now);
#endif


				// FROM http://stackoverflow.com/questions/5844858/how-to-take-screenshot-in-opengl
				// Convert to FreeImage format & save to file
				FIBITMAP* image = FreeImage_ConvertFromRawBits(&data[0], width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
				// FreeImage_ConvertFromRawBits(pixels, WIDTH, HEIGHT, 3WIDTH, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);


				// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
				//std::stringstream stream;
#if defined (_WIN32) || defined(_WIN64)
			// stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
			// c++ 11 conversion form num to string
			//std::string url = "\\Users\\Ira\\Desktop\\ProtoJucnusEffusus01_stills\\" + name + "_" + std::to_string(i*scaleFactor+j) + ".jpg";

			// ensure no single digit nums, for easy sorting
				std::string imgNum;

				if (i * scaleFactor + j < 10) {
					imgNum = "00" + std::to_string(i * scaleFactor + j);
				}
				else if (i * scaleFactor + j < 100) {
					imgNum = "0" + std::to_string(i * scaleFactor + j);
				}
				else {
					imgNum = std::to_string(i * scaleFactor + j);
				}

				std::string tileURL = directory + "\\" + name + "_" + imgNum + ".jpg";
#else
			// stream << (ltm->tm_year + 1900) << "_" << (ltm->tm_mon + 1) << "_" << ltm->tm_mday << "_" << ltm->tm_hour << "_" << ltm->tm_min << "_" << ltm->tm_sec;
			// c++ 11 conversion form num to string
				std::string url = "/Users/33993405/Desktop/ProtoJucnusEffusus01_stills/" + namme + "_" + std::to_string(i * scaleFactor + j) + ".jpg";
#endif

				FreeImage_Save(FIF_JPEG, image, tileURL.c_str(), JPEG_QUALITYSUPERB);
				//trace("-i = ", -i, "-j =", -j);

				// Free resources
				FreeImage_Unload(image);


				// Return to onscreen rendering:
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			}
		}
		//trace("ProtoUtility::getPath() =", ProtoUtility::getPath());
		bool isOk = stitchTiles(directory, scaleFactor);
		//}
	}

	//void ProtoBaseApp::threadSave(std::string name, int scaleFactor){
	//	//mtx.lock();
	//#if defined (_WIN32) || defined(_WIN64)
	//	time_t now = time(0);
	//	tm ltm;
	//	localtime_s(&ltm, &now);
	//#else // os x uses localtime instead of localtime_s
	//	time_t now = time(0);
	//	tm* ltm = localtime(&now);
	//#endif
	//
	//	// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
	//	std::stringstream stream;
	//	stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
	//
	//
	//
	//	std::string url = ProtoUtility::getPathToOutput();
	//	std::string directory = url + name + "_" + stream.str();
	//	CreateDirectory(directory.c_str(), 0);
	//
	//
	//	for (int i = 0; i < scaleFactor; ++i){
	//		for (int j = 0; j < scaleFactor; ++j){
	//			
	//			//trace("in drawToFrameBuffer");
	//			//glClearColor(0, 0, 0, 1.0f);
	//			trace("width = ", width);
	//			trace("height = ", height);
	//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//			//From: http://stackoverflow.com/questions/12157646/how-to-render-offscreen-on-opengl
	//
	//			glViewport(-i*width, -j*height, scaleFactor * width, scaleFactor * height);
	//			//this->render();
	//			render();
	//
	//			//after drawing
	//			std::vector<uint8_t> data(width * height * 3);
	//			mtx.lock(); 
	//			glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);
	//			mtx.unlock();
	//
	//
	//
	//#if defined (_WIN32) || defined(_WIN64)
	//			time_t now = time(0);
	//			tm ltm;
	//			localtime_s(&ltm, &now);
	//#else // os x uses localtime instead of localtime_s
	//			time_t now = time(0);
	//			tm* ltm = localtime(&now);
	//#endif
	//
	//
	//			// FROM http://stackoverflow.com/questions/5844858/how-to-take-screenshot-in-opengl
	//			// Convert to FreeImage format & save to file
	//			FIBITMAP* image = FreeImage_ConvertFromRawBits(&data[0], width, height, 3 * width, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
	//
	//
	//			// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
	//			//std::stringstream stream;
	//#if defined (_WIN32) || defined(_WIN64)
	//			// stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
	//			// c++ 11 conversion form num to string
	//			//std::string url = "\\Users\\Ira\\Desktop\\ProtoJucnusEffusus01_stills\\" + name + "_" + std::to_string(i*scaleFactor+j) + ".jpg";
	//
	//			// ensure no single digit nums, for easy sorting
	//			std::string imgNum;
	//
	//			if (i*scaleFactor + j < 10){
	//				imgNum = "00" + std::to_string(i*scaleFactor + j);
	//			}
	//			else if (i*scaleFactor + j < 100){
	//				imgNum = "0" + std::to_string(i*scaleFactor + j);
	//			}
	//			else {
	//				imgNum = std::to_string(i*scaleFactor + j);
	//			}
	//
	//			std::string tileURL = directory + "\\" + name + "_" + imgNum + ".jpg";
	//#else
	//			// stream << (ltm->tm_year + 1900) << "_" << (ltm->tm_mon + 1) << "_" << ltm->tm_mday << "_" << ltm->tm_hour << "_" << ltm->tm_min << "_" << ltm->tm_sec;
	//			// c++ 11 conversion form num to string
	//			std::string url = "/Users/33993405/Desktop/ProtoJucnusEffusus01_stills/" + namme + "_" + std::to_string(i*scaleFactor + j) + ".jpg";
	//#endif
	//
	//			FreeImage_Save(FIF_JPEG, image, tileURL.c_str(), 0);
	//
	//			// Free resources
	//			FreeImage_Unload(image);
	//
	//
	//			// Return to onscreen rendering:
	//			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	//			
	//		}
	//	}
	//
	//	//trace("ProtoUtility::getPath() =", ProtoUtility::getPath());
	//	bool isOk = stitchTiles(directory, scaleFactor);
	//
	//	//mtx.unlock();
	//}

	bool ProtoBaseApp::stitchTiles(std::string url, int tiles) {
		trace(" url =", url);
		url += "\\";
		std::vector<std::string> fileNames = ProtoUtility::getFileNames(url);
		for (size_t i = 0; i < fileNames.size(); ++i) {
			//trace(fileNames.at(i));
		}
		// composite image creation
		// procedure
		// 1. grab all file names in directory and store in store in vector
		// 2. sort by name
		// 3. grab images by names
		// 4. copy and paste tiles into composite image
		// 5. save image back to disk.

		FIBITMAP* compositeImg = FreeImage_Allocate(width * tiles, height * tiles, 24, 0xFF0000, 0x00FF00, 0x0000FF);
		//FreeImage_Allo




		for (int i = 0; i < tiles; ++i) {
			for (int j = 0; j < tiles; ++j) {

				int id = i * tiles + j;

				//image format
				FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
				//pointer to the image, once loaded
				FIBITMAP* img(0);
				//pointer to the image data
				BYTE* imageData(0);
				//image width and height
				unsigned int width(0), height(0);
				//OpenGL's image ID to map to
				GLuint gl_texID;

				//check the file signature and deduce its format

				std::string path = url + fileNames.at(id);
				const char* fileURL = path.c_str();
				fif = FreeImage_GetFileType(fileURL, 0);
				//if still unknown, try to guess the file format from the file extension
				if (fif == FIF_UNKNOWN)
					fif = FreeImage_GetFIFFromFilename(fileURL);
				//if still unkown, return failure
				if (fif == FIF_UNKNOWN)
					return false;

				//check that the plugin has reading capabilities and load the file
				if (FreeImage_FIFSupportsReading(fif))
					img = FreeImage_Load(fif, fileURL);
				//if the image failed to load, return failure
				if (!img)
					return false;

				//retrieve the image data
				imageData = FreeImage_GetBits(img);
				//get the image width and height
				width = FreeImage_GetWidth(img);
				height = FreeImage_GetHeight(img);
				//std::cout << "image width = " << width << std::endl;
				//std::cout << "image height = " << height << std::endl;
				//if this somehow one of these failed (they shouldn't), return failure
				if ((imageData == 0) || (width == 0) || (height == 0))
					return false;

				// copy and paste bits
				FIBITMAP* piece = FreeImage_Copy(img, 0, height, width, 0);
				FreeImage_Paste(compositeImg, piece, width * i, (height * (tiles - 1)) - height * j, 255);


				//Free FreeImage's copy of the data
				FreeImage_Unload(img);
			}
		}

		// cleanup Memory
		if (compositeImg) {
			// bitmap successfully created!

			//#if defined (_WIN32) || defined(_WIN64)
			//		time_t now = time(0);
			//		tm ltm;
			//		localtime_s(&ltm, &now);
			//#else // os x uses localtime instead of localtime_s
			//		time_t now = time(0);
			//		tm* ltm = localtime(&now);
			//#endif
			//
			//		// thanks: http://stackoverflow.com/questions/191757/c-concatenate-string-and-int, DannyT
			//		std::stringstream stream;
			//		stream << (ltm.tm_year + 1900) << "_" << (ltm.tm_mon + 1) << "_" << ltm.tm_mday << "_" << ltm.tm_hour << "_" << ltm.tm_min << "_" << ltm.tm_sec;
			//
			//
			//
			//		std::string folder = url + "ProtoJuncusEffusus01_" + stream.str();
			//		CreateDirectory(folder.c_str(), 0);
			std::string compositeName = url + "\\ProtoJuncusEffusus01.jpg";
			FreeImage_Save(FIF_JPEG, compositeImg, compositeName.c_str(), 0);
			FreeImage_Unload(compositeImg);
		}


		return true;
	}

	// matrix transformation functions, in style of GL 1.0
	void ProtoBaseApp::translate(float tx, float ty, float tz) {
		ctx->translate(tx, ty, tz);
	}

	void ProtoBaseApp::translate(const Vec3f & tXYZ) {
		ctx->translate(tXYZ);
	}

	void ProtoBaseApp::translate(const Vec2f & tXY) {
		translate(tXY.x, tXY.y);
	}

	void ProtoBaseApp::rotate(float angle, float axisX, float axisY, float axisZ) {
		ctx->rotate(angle, axisX, axisY, axisZ);
	}

	void ProtoBaseApp::rotate(float angle, const Vec3f & rXYZ) {
		ctx->rotate(angle, rXYZ);
	}

	void ProtoBaseApp::scale(float s) {
		ctx->scale(s);
	}

	void ProtoBaseApp::scale(float sx, float sy, float sz) {
		ctx->scale(sx, sy, sz);
	}

	void ProtoBaseApp::scale(const Vec3f & sXYZ) {
		ctx->scale(sXYZ);
	}

	void ProtoBaseApp::push() {
		ctx->push();
	}

	void ProtoBaseApp::pop() {
		ctx->pop();
	}

	float ProtoBaseApp::radians(float degs) {
		return glm::radians(degs);
	}



	// Mouse & Key Events
	void ProtoBaseApp::keyPressed() {}
	void ProtoBaseApp::mousePressed() {}
	void ProtoBaseApp::mouseRightPressed() {}
	void ProtoBaseApp::mouseReleased() {}
	void ProtoBaseApp::mouseRightReleased() {}
	void ProtoBaseApp::mouseMoved() {}
	void ProtoBaseApp::mouseDragged() {}

	// Window Events
	void ProtoBaseApp::onResized() {}
	void ProtoBaseApp::onClosed() {}

