/*!  \brief  ProtoGeom3.cpp: Abstact Base Geometry class
 ProtoGeom3.cpp
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
 This class is part of the group common (update)
 \sa NO LINK
 */


#include "ProtoGeom3.h"

#define STRIDE ijg::ProtoGeom3::STRIDE


using namespace ijg;

GLuint ProtoGeom3::textureID = 0;

ProtoGeom3::ProtoGeom3() :
	ProtoShape3(Vec3f(), Vec3f(), Dim3f(1, 1, 1), Col4f(.6, 0.0, .65, 1.0)), diffuseMapImage("white_tile.jpg"), textureScale(Vec2f(1, 1)) {
	diffuseTextureImageURLs.push_back(diffuseMapImage);
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos) :
	ProtoShape3(pos, Vec3f(), Dim3f(1, 1, 1), Col4f(.6, 0.0, .65, 1.0)), diffuseMapImage("white_tile.jpg"), textureScale(Vec2f(1, 1)) {
	diffuseTextureImageURLs.push_back(diffuseMapImage);
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4) :
	ProtoShape3(pos, rot, size, col4), diffuseMapImage("white_tile.jpg"), textureScale(Vec2f(1, 1)) {
	diffuseTextureImageURLs.push_back(diffuseMapImage);
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const std::vector< ProtoColor4f > col4s) :
	ProtoShape3(pos, rot, size, col4s), diffuseMapImage("white_tile.jpg"), textureScale(Vec2f(1, 1)) {
	diffuseTextureImageURLs.push_back(diffuseMapImage);
}


// with textures
//ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& diffuseMapImage) :
//ProtoShape3(pos, rot, size, col4), diffuseMapImage(diffuseMapImage) {
//	diffuseTextureImageURLs.push_back(diffuseMapImage);
//}

//ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const std::vector< ProtoColor4f > col4s, const std::string& diffuseMapImage) :
//ProtoShape3(pos, rot, size, col4s), diffuseMapImage(diffuseMapImage) {
//	diffuseTextureImageURLs.push_back(diffuseMapImage);
//}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size, const ProtoColor4f col4, const std::string& diffuseMapImage, const Vec2f& textureScale) :
	ProtoShape3(pos, rot, size, col4), diffuseMapImage(diffuseMapImage), textureScale(textureScale) {
	diffuseTextureImageURLs.push_back(diffuseMapImage);
}

ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
	const std::vector< ProtoColor4f > col4s, const std::string& diffuseMapImage, const Vec2f& textureScale) :
	ProtoShape3(pos, rot, size, col4s), diffuseMapImage(diffuseMapImage), textureScale(textureScale) {
	diffuseTextureImageURLs.push_back(diffuseMapImage);
}


// multi-texturing
ProtoGeom3::ProtoGeom3(const Dim3f& size, const Col4f& col4, const std::vector<std::string>& diffuseTextureImageURLs, const Vec2f& textureScale) :
	ProtoShape3(Vec3f(), Vec3f(), size, col4), diffuseTextureImageURLs(diffuseTextureImageURLs), textureScale(textureScale) {
}
ProtoGeom3::ProtoGeom3(const Vec3f& pos, const Vec3f& rot, const Dim3f& size, const Col4f& col4, const std::vector<std::string>& diffuseTextureImageURLs, const Vec2f& textureScale) :
	ProtoShape3(pos, rot, size, col4s), diffuseTextureImageURLs(diffuseTextureImageURLs), textureScale(textureScale) {
}


ProtoGeom3::~ProtoGeom3() {
	// glDeleteLists(displayListIndex, 1);
	// trace("in Geom3 dstr");

	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif
}


void ProtoGeom3::init() {
	ctx = ProtoContext::getContext();
	clearVectors(); // empty all vectors in case called by setter
	createDiffuseMapTexture(diffuseMapImage); // set default diffuse color texture
	loadBumpMapTexture("white_tile_normal.jpg"); // set default
	calcVerts();
	calcInds();
	calcFaces();
	calcVertexNorms();
	calcPrimitives();

	// set default material settings
	materials = Material(Col4f(.7f, .7f, .7f, 1.0f), Col4f(.125f, .125f, .125f, 1.0f), Col4f(.2, .2, .2, 1.0f), Col4f(.0f, .0f, .0f, 1.0f), 8);

	// set material memory locations for GPU
	diffuse_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMaterial");
	ambient_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "ambientMaterial");
	specular_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "specularMaterial");
	emissive_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "emissiveMaterial");
	shininess_loc_U = glGetUniformLocation(ProtoShader::getID_2(), "shininess");

	// Special thanks to:
	// http://stackoverflow.com/questions/8704801/glvertexattribpointer-clarification
	// http://www.swiftless.com/tutorials/opengl4/4-opengl-4-vao.html
	/***************************************/
	/*       Setup VAO/VBO buffers         */
	/***************************************/
	// 1. Create and bind VAO
	glGenVertexArrays(1, &vaoID); // Create VAO
	glBindVertexArray(vaoID); // Bind VAO (making it active)
	//2. Create and bind VBO
	// a. Vertex attributes
	glGenBuffers(1, &vboID); // Create VBO ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind vertex attributes VBO
	int vertsDataSize = sizeof(float) * static_cast<int>(interleavedPrims.size());
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW); // allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data

	// b. Indices  uses ELEMENT_ARRAY_BUFFER
	glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind indices VBO
	int indsDataSize = static_cast<int>(inds.size()) * 3 * sizeof(GL_UNSIGNED_INT);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &indPrims[0]); // upload the data

	for (int i = 0; i < 5; i++) {
		glEnableVertexAttribArray(i);
	}
	// STRIDE is 15: pos(3) + norm(3) + col(4) + uv(2) + tang(3)
	// (x, y, z, nx, ny, nz, r, g, b, a, u, v, tx, ty, tz)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(12)); // norm
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(24)); // col
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(40)); // uv
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(48)); // tangent

	// Disable VAO
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// set default texture enabled state
	isTextureEnabled = true;
}

void ProtoGeom3::update() {

	//createDiffuseMapTexture(diffuseMapImage); // set default diffuse color texture
	int len = verts.size();
	std::vector<ProtoVertex3> vertsTemp = verts;
	verts.clear(); // empty all vectors in case called by setter
	calcVerts();
	if (len == verts.size()) {
		verts = vertsTemp;
		return;
	}
	else {
		if (diffuseTextureImageURLs.size() > 0) {
			diffuseTextureImageURLs.clear();
		}

		if (inds.size() > 0) {
			inds.clear();
		}

		if (vertPrims.size() > 0) {
			vertPrims.clear();
		}

		if (indPrims.size() > 0) {
			indPrims.clear();
		}

		if (normPrims.size() > 0) {
			normPrims.clear();
		}

		if (tangentPrims.size() > 0) {
			tangentPrims.clear();
		}

		if (colorPrims.size() > 0) {
			colorPrims.clear();
		}

		if (texturePrims.size() > 0) {
			texturePrims.clear();
		}

		if (interleavedPrims.size() > 0) {
			interleavedPrims.clear();
		}

		if (geomSets.size() > 0) {
			geomSets.clear();
		}

		if (packedFaces.size() > 0) {
			packedFaces.clear();
		}

		if (faces.size() > 0) {
			faces.clear();
		}

		if (faces2.size() > 0) {
			faces2.clear();
		}
	}
	calcInds();
	calcFaces();
	calcVertexNorms();
	calcPrimitives();

	// Special thanks to:
	// http://stackoverflow.com/questions/8704801/glvertexattribpointer-clarification
	// http://www.swiftless.com/tutorials/opengl4/4-opengl-4-vao.html
	/***************************************/
	/*       Setup VAO/VBO buffers         */
	/***************************************/
	// 1. Create and bind VAO
	//glGenVertexArrays(1, &vaoID); // Create VAO
	glBindVertexArray(vaoID); // Bind VAO (making it active)
	//2. Create and bind VBO
	// a. Vertex attributes
	//glGenBuffers(1, &vboID); // Create VBO ID
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind vertex attributes VBO
	int vertsDataSize = sizeof(float)* static_cast<int>(interleavedPrims.size());
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW); // allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data

	// b. Indices  uses ELEMENT_ARRAY_BUFFER
	//glGenBuffers(1, &indexVboID); // Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVboID); // Bind indices VBO
	int indsDataSize = static_cast<int>(inds.size()) * 3 * sizeof(GL_UNSIGNED_INT);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsDataSize, NULL, GL_STATIC_DRAW); // allocate
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indsDataSize, &indPrims[0]); // upload the data

	//for (int i = 0; i < 5; i++) {
	//	glEnableVertexAttribArray(i);
	//}
	// STRIDE is 15: pos(3) + norm(3) + col(4) + uv(2) + tang(3)
	// (x, y, z, nx, ny, nz, r, g, b, a, u, v, tx, ty, tz)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(0)); // pos
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(12)); // norm
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(24)); // col
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(40)); // uv
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), BUFFER_OFFSET(48)); // tangent

	// Disable VAO
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	// set default texture enabled state
	isTextureEnabled = true;
}


void ProtoGeom3::clearVectors() {
	if (diffuseTextureImageURLs.size() > 0) {
		diffuseTextureImageURLs.clear();
	}

	if (verts.size() > 0) {
		verts.clear();
	}

	if (inds.size() > 0) {
		inds.clear();
	}

	if (vertPrims.size() > 0) {
		vertPrims.clear();
	}

	if (indPrims.size() > 0) {
		indPrims.clear();
	}

	if (normPrims.size() > 0) {
		normPrims.clear();
	}

	if (tangentPrims.size() > 0) {
		tangentPrims.clear();
	}

	if (colorPrims.size() > 0) {
		colorPrims.clear();
	}

	if (texturePrims.size() > 0) {
		texturePrims.clear();
	}

	if (interleavedPrims.size() > 0) {
		interleavedPrims.clear();
	}

	if (geomSets.size() > 0) {
		geomSets.clear();
	}

	if (packedFaces.size() > 0) {
		packedFaces.clear();
	}

	if (faces.size() > 0) {
		faces.clear();
	}

	if (faces2.size() > 0) {
		faces2.clear();
	}
}

void ProtoGeom3::setShader(const ProtoShader* shader) {
	this->shader = shader;
}

// public interface for texture generation
void ProtoGeom3::setDiffuseMap(const std::string& diffuseMapImage) {
	createDiffuseMapTexture(diffuseMapImage);
}
void ProtoGeom3::setBumpMap(const std::string& bumpMapImage, float intensity) {
	createBumpMapTexture(bumpMapImage, intensity);
}
void ProtoGeom3::createBumpMap(const std::string& bumpMapImage, float intensity) {
	createBumpMapTexture(bumpMapImage, intensity);
}

void ProtoGeom3::setReflectionMap(const std::string& reflectionMapImage) {
}
void ProtoGeom3::setRefractionMap(const std::string& refractionMapImage) {
}
void ProtoGeom3::setSpecularMap(const std::string& specularMapImage) {
}

// begin internal texture implementation
void ProtoGeom3::createDiffuseMapTexture(const std::string& diffuseMapImage) {// create default texture for diffuseMap
	diffuseMapTexture = ProtoTexture(diffuseMapImage, ProtoTexture::DIFFUSE_MAP, GL_RGB, GL_RGB, 0, 0);
	diffuseMapLoc = glGetUniformLocation(ProtoShader::getID_2(), "diffuseMap");
	glUniform1i(diffuseMapLoc,0); 
}

void ProtoGeom3::createBumpMapTexture(const std::string& bumpMapImage, float intensity) {
	bumpMapTexture = ProtoTexture(bumpMapImage, ProtoTexture::BUMP_MAP, GL_RGB, GL_RGB, 0, 0, intensity);
	bumpMapLoc = glGetUniformLocation(ProtoShader::getID_2(), "bumpMap");
	//bumpMapIntensityLoc = glGetUniformLocation(ProtoShader::getID_2(), "bumpIntensity");
	glUniform1i(bumpMapLoc, 1); 
	//glUniform1i(bumpMapIntensityLoc, 1);
}

void ProtoGeom3::loadBumpMapTexture(const std::string& bumpMapImage) {
	bumpMapTexture = ProtoTexture(bumpMapImage, ProtoTexture::NORMAL_MAP, GL_RGB, GL_RGB, 0, 0);
	bumpMapLoc = glGetUniformLocation(ProtoShader::getID_2(), "bumpMap"); // changed from bumpmap
	glUniform1i(bumpMapLoc, 1); 
}
void ProtoGeom3::createReflectionMapTexture(const std::string& reflectionMapImage) {
}// loc 2
void ProtoGeom3::createRefractionMapTexture(const std::string& refractionMapImage) {
}// loc 3
void ProtoGeom3::createSpecularMapTexture(const std::string& specularMapImage) {
}// loc 4


void ProtoGeom3::calcFaces() {
	if (faces.size() > 0) {
		faces.clear();
	}
	// pass vertex addresses
	for (int i = 0; i < inds.size(); i++) {
		faces.push_back(ProtoFace3(&verts.at(inds.at(i).elem0), &verts.at(inds.at(i).elem1),
			&verts.at(inds.at(i).elem2)));
	}
}


// calculates vertex normals and tangents (for bump mapping)
void ProtoGeom3::calcVertexNorms() {

	// calculate initial vertex normals and fill geomsets with vertex face association
	// to enable easier runtime vertex normal calcs
	if (geomSets.size() > 0) {
		geomSets.clear();
	}

	for (int i = 0; i < verts.size(); i++) {
		Vec3f n; // for normals
		Vec3f t; // for tangents

		std::vector<ProtoFace3*> fs;
		// check if face contains verts
		for (int j = 0; j < faces.size(); j++) {
			if (&verts.at(i) == faces.at(j)[0] ||
				&verts.at(i) == faces.at(j)[1] ||
				&verts.at(i) == faces.at(j)[2]) {
				//std::cout << "i = " << i << ", " << "face " << j << std::endl;
				n += faces.at(j).getNorm();
				t += faces.at(j).getTangentBM();
				fs.push_back(&faces.at(j));
			}
		}
		// NOTE: not updating normals to geoSets 
		geomSets.push_back(ProtoGeomSet(&verts.at(i), fs));
		//std::cout << "vertex has this many linked faces: " << geomSets.at(i).getLinkedFaces().size() << std::endl;
		n.normalize();
		t.normalize();
		//trace("n=",n,"t=",t);
		verts.at(i).setNormal(n);
		verts.at(i).setTangent(t);
	}
}



void ProtoGeom3::sortFaces() {
	bool swapped = true;
	int j = 0;
	//ProtoFace3 tmp;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < faces.size() - j; i++) {
			if (faces.at(i).getCentroid().z > faces.at(i + 1).getCentroid().z) {
				ProtoFace3 tmp = faces.at(i);
				faces.at(i) = faces.at(i + 1);
				faces.at(i + 1) = tmp;
				swapped = true;
			}
		}
	}
}

void ProtoGeom3::calcPrimitives() {
	if (interleavedPrims.size() > 0) interleavedPrims.clear();
	if (indPrims.size() > 0) indPrims.clear();

	// fill interleaved primitive arrays
	for (int i = 0; i < verts.size(); i++) {
		interleavedPrims.push_back(verts.at(i).pos.x);
		interleavedPrims.push_back(verts.at(i).pos.y);
		interleavedPrims.push_back(verts.at(i).pos.z);

		interleavedPrims.push_back(verts.at(i).getNormal().x);
		interleavedPrims.push_back(verts.at(i).getNormal().y);
		interleavedPrims.push_back(verts.at(i).getNormal().z);

		interleavedPrims.push_back(verts.at(i).getColor().getR());
		interleavedPrims.push_back(verts.at(i).getColor().getG());
		interleavedPrims.push_back(verts.at(i).getColor().getB());
		interleavedPrims.push_back(verts.at(i).getColor().getA());

		interleavedPrims.push_back(verts.at(i).getUV().elem0);
		interleavedPrims.push_back(verts.at(i).getUV().elem1);

		interleavedPrims.push_back(verts.at(i).getTangent().x);
		interleavedPrims.push_back(verts.at(i).getTangent().y);
		interleavedPrims.push_back(verts.at(i).getTangent().z);
	}

	// explode inds arrays to primitives
	for (int i = 0, j = 0; i < inds.size(); i++) {
		indPrims.push_back(inds.at(i).elem0);
		indPrims.push_back(inds.at(i).elem1);
		indPrims.push_back(inds.at(i).elem2);
	}
}

void ProtoGeom3::textureOn() {
	//glEnable(GL_TEXTURE_2D);
	isTextureEnabled = true;
}

void ProtoGeom3::textureOff() {
	isTextureEnabled = false;
}

void ProtoGeom3::enableNormalMap(float depth) {

}

void ProtoGeom3::disableNormalMap() {

}

// for STL output, for 3D printing
std::vector<Tup4v> ProtoGeom3::getGeomData() {
	std::vector<Tup4v> vs;
	for (int i = 0; i < faces.size(); ++i) {
		vs.push_back(Tup4v(getFaces().at(i).getNorm(), getFaces().at(i).v0, getFaces().at(i).v1, getFaces().at(i).v2));
	}
	return vs;
}

// Includes multiple display implementations

/* NOTE:: Drawing will/MAY eventually get delegated to a
 world type class, to enable aggregate face sorting and
 and primitive processing*/
void ProtoGeom3::display(RenderMode render, float pointSize) {
	// call update to enable real-time changes to geometry.
	// this will need further refactoring
	// including potentially a geometry shader implementation
	//update();
	ctx->push();
	ctx->translate(pos);
	ctx->scale(size);
	//ctx->rotate(rot);
	GLuint d = diffuseMapTexture.getTextureID();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, d);

	GLuint b = bumpMapTexture.getTextureID();
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, b);

	// update material values in GPU
	glUniform4fv(diffuse_loc_U, 1, &materials.diffuse.r);
	glUniform4fv(ambient_loc_U, 1, &materials.ambient.r);
	glUniform4fv(specular_loc_U, 1, &materials.specular.r);
	glUniform4fv(emissive_loc_U, 1, &materials.emissive.r);
	glUniform1f(shininess_loc_U, materials.shininess);

	//turn on default lighting for all 3D forms
	//Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	//glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	switch (render) {
	case POINTS:
		//glDisable(GL_CULL_FACE);
		//glDisable(GL_LIGHTING);
		glPointSize(pointSize);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;

	case WIREFRAME:
		//glDisable(GL_CULL_FACE);
		//glDisable(GL_LIGHTING);
		glLineWidth(pointSize);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	case SURFACE:
		//glDisable(GL_CULL_FACE);
		//glEnable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glPolygonMode(GL_FRONT, GL_FILL);
		break;
	}


	//sortFaces();
	/* NOTE:: sorting here is not solving self-overlap highlighting with alpha
	 possible solution will be doing manual rotations on geometry
	 (as coampdre to modelview matrix transformation) and then sorting faces.
	 * See note above above delegating this to a world type class.*/


	 // VAO manages VBO's
	glBindVertexArray(vaoID);
	if (render == POINTS) {
		glDrawElements(GL_POINTS, static_cast<int>(inds.size()) * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	}
	else {
		glDrawElements(GL_TRIANGLES, static_cast<int>(inds.size()) * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	}
	glBindVertexArray(0);

	ctx->pop();
}


void ProtoGeom3::displayTBN() {
	glUseProgram(0);
	glBegin(GL_POINTS);
	for (int i = 0; i < interleavedPrims.size(); i += 15) {
		float vx = interleavedPrims.at(i);
		float vy = interleavedPrims.at(i + 1);
		float vz = interleavedPrims.at(i + 2);
		float nx = interleavedPrims.at(i + 3);
		float ny = interleavedPrims.at(i + 4);
		float nz = interleavedPrims.at(i + 5);
		float tx = interleavedPrims.at(i + 12);
		float ty = interleavedPrims.at(i + 13);
		float tz = interleavedPrims.at(i + 14);

	 
		glLineWidth(2);
		glPointSize(20);
		glColor3f(.5, .5, 1.0);
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(vx, vy, vz);
		glVertex3f(vx + nx * 300, vy + ny * 300, vz + nz * 300);
		
	}
	glEnd();
	glUseProgram(ProtoShader::getID_2());
}

void ProtoGeom3::move(const Vec3f& v) {
	pos += v;
}

void ProtoGeom3::rotate(const Vec3f& r) {
	rot += r;
}

void ProtoGeom3::scale(const ProtoDimension3f& s) {
	size += s;
}

// transform VBO primitives using glBufferSubData
void ProtoGeom3::transform(const ProtoMatrix4f& mat4) {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	for (int i = 0; i < interleavedPrims.size(); i += STRIDE) {// transform verts
		Vec4 v4(interleavedPrims.at(i), interleavedPrims.at(i + 1), interleavedPrims.at(i + 2), 1);
		Vec3 v3 = mat4*v4;
		interleavedPrims.at(i) = v3.x;
		interleavedPrims.at(i + 1) = v3.y;
		interleavedPrims.at(i + 2) = v3.z;

		// transform vnorms
		// there's a better way to transform v norms (so fix it eventually!)
		ProtoMatrix4f m = mat4;
		m.transpose();
		Vec4 v4n(interleavedPrims.at(i + 3), interleavedPrims.at(i + 4), interleavedPrims.at(i + 5), 1);
		Vec3 v3n = m*v4n;
		interleavedPrims.at(i + 3) = v3n.x;
		interleavedPrims.at(i + 4) = v3n.y;
		interleavedPrims.at(i + 5) = v3n.z;

	}
	int vertsDataSize = sizeof(float) *interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void ProtoGeom3::updateColorBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	//trace("col4s.size() =", col4s.size());
	//trace("interleavedPrims.size()/12 =", interleavedPrims.size() / 12);
	for (int i = 0, colCounter = 0; i < interleavedPrims.size(); i += STRIDE) {// transform verts
		// NOTE:: this needs work!!!
		if (col4s.size() > 0) {
			interleavedPrims.at(i + 6) = col4s.at(colCounter).getR();
			interleavedPrims.at(i + 7) = col4s.at(colCounter).getG();
			interleavedPrims.at(i + 8) = col4s.at(colCounter).getB();
			interleavedPrims.at(i + 9) = col4s.at(colCounter).getA();
		}
		else {
			interleavedPrims.at(i + 6) = col4.getR();
			interleavedPrims.at(i + 7) = col4.getG();
			interleavedPrims.at(i + 8) = col4.getB();
			interleavedPrims.at(i + 9) = col4.getA();
		}

	}
	int vertsDataSize = sizeof(float)*interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ProtoGeom3::updateTextureBuffer() {
	//trace("textureScale =", textureScale);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	for (int i = 0; i < interleavedPrims.size(); i += STRIDE) {// transform verts
		interleavedPrims.at(i + 10) *= 1.0 / textureScale.x;
		interleavedPrims.at(i + 11) *= 1.0 / textureScale.y;

	}
	int vertsDataSize = sizeof(float)*interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ProtoGeom3::updateBuffer() {

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	for (int i = 0; i < interleavedPrims.size(); i += STRIDE) {// transform verts
		interleavedPrims.at(i + 10) *= 1.0 / textureScale.x;
		interleavedPrims.at(i + 11) *= 1.0 / textureScale.y;
		//interleavedPrims.at(i + 12) *= 1.0/textureScale;

	}
	int vertsDataSize = sizeof(float)*interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}





