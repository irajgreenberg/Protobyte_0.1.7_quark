/*!  \brief  ProtoSphere.cpp: sphere implementation
 ProtoSphere.cpp
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

#include "ProtoSphere.h"

using namespace ijg;

ProtoSphere::ProtoSphere() {
    
}

ProtoSphere::ProtoSphere(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f size,
                         const ProtoColor4f col4, const std::string& textureImageURL, float textureScale, int spines, int spineNodes) :
ProtoGeom3(pos, rot, size, col4, textureImageURL, textureScale), spines(spines), spineNodes(spineNodes) {
    init();
}

ProtoSphere::ProtoSphere(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f size,
                         const ProtoColor4f col4, int spines, int spineNodes) :
ProtoGeom3(pos, rot, size, col4), spines(spines), spineNodes(spineNodes) {
    init();
}

ProtoSphere::ProtoSphere(const Vec3f& pos, const Vec3f& rot, const Dim3f size,
	const ProtoColor4f col4, const std::string& textureImageURL, float textureScale, int spines, int spineNodes, const Vec3f& chaos) :
	ProtoGeom3(pos, rot, size, col4), spines(spines), spineNodes(spineNodes), chaos(chaos) {
	init();
}

// new 7/23/15
ProtoSphere::ProtoSphere(int spines, int spineNodes, const ProtoColor4f col4, const std::string& textureImageURL, float textureScale) :
ProtoGeom3(Vec3f(), Vec3f(), Dim3f(), col4, textureImageURL, textureScale), spines(spines), spineNodes(spineNodes) {
	init();
}

//void ProtoSphere::init() {
//    calcVerts();
//    calcInds();
//    calcFaces();
//    calcVertexNorms();
//    calcPrimitives();
//    fillDisplayLists();
//}

void ProtoSphere::calcVerts2() {
    
    verts.resize((spineNodes - 2) * spines + 2);
    float x = 0, y = 0, z = 0, u = 0.0, v = 0.0;
    float tempX = 0, tempZ = 0;
    float theta = -PI / 2.0, phi = 0.0;
    int counter = 0;
    //int radiusX = size.w / 2.0;
    //int radiusY = size.w / 2.0;
    
	float theta3 = 0;
    // always 1 more segment than points along spline
    for (int i = 0; i < spineNodes; i++) {
        // z rotation
       /* x = cos(theta) * *.5;
        y = sin(theta) * .5;*/

		x = cos(theta) * .5 * (1+random(chaos.x));
		y = sin(theta) * .5 * (1+random(chaos.y));
        z = 0.0;
        phi = 0.0;
		theta3 += TWO_PI / 180.0;
        for (int j = 0; j < spines; j++) {
            
            // y rotation
            tempZ = cos(phi) * z - sin(phi) * x;
            tempX = sin(phi) * z + cos(phi) * x;
            
            // UV mapping expressions form:
            //http://en.wikipedia.org/wiki/UV_mapping
            Vec3f tmp(tempX, y, tempZ);
            tmp.normalize();
            u = .5 + atan2(tmp.z, tmp.x) / (2 * PI);
            v = .5 - 2.0 * asin(tmp.y) / (2 * PI);
            
            // top vertex
            if (i == 0 && j == 0) {
                verts.at(counter++) = ProtoVertex3(Vec3f(tempX, y, tempZ),
                                                   ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()),
                                                   ProtoTuple2f(u, v));
                // body vertices
            } else if (i > 0 && i < spineNodes - 1) {
                verts.at(counter++) = ProtoVertex3(Vec3f(tempX, y, tempZ),
                                                   ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()),
                                                   ProtoTuple2f(u, v));
                // bottom vertex
            } else if (i == spineNodes - 1 && j == 0) {
                verts.at(counter++) = ProtoVertex3(Vec3f(tempX, y, tempZ),
                                                   ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()),
                                                   ProtoTuple2f(u, v));
            }
            phi -= PI * 2.0 / spines;
        }
        theta -= PI / (spineNodes - 1);
    }
    // std::cout << "verts.size() = " << counter << std::endl;
}

/*Note: p = Pi
 q as the angle  on X axis (0 <= q <= 2p)
 f as the angle from the Z axis (0.0 <= f <= p).
 
 X = R sin (f) * cos (q) = R sin (pv) * cos (2pu) where f/p = v (0.0 <= v <= 1.0)
 Y = R sin (f) * sin (q) = R sin (pv) * sin (2pu) where q/2p = u (0.0 <= u <= 1.0))
 Z = R cos (f) = R cos (pv)
 
 u = [arccos ( X/R sin (pv) ) ] / 2p
 v = f/p = arccos (Z/R) / p
 */

/*!
 * Implementation Notes:
 * Verts packed 1 dimensionally as top PT = 0, body, bottom PT = size()-1
 *
 * Created on April 25, 2013, 1:47 PM
 */
//  FIX NEED MORE FACES

void ProtoSphere::calcInds2() {
    //int ctr = 0;
    ProtoTuple3i t0;
    
    // body faces
    for (int i = 0; i < spineNodes; ++i) {
        for (int j = 0; j < spines; ++j) {
            //TOP
            if (i == 0 && j < spines - 1) {
                t0 = ProtoTuple3i(0, j + 1, j + 2);
                inds.push_back(t0);
                //std::cout << "top = " << t0 << std::endl;
                //TOP CLOSE
            } else if (i == 0 && j == spines - 1) {
                t0 = ProtoTuple3i(0, j + 1, 1);
                inds.push_back(t0);
                //std::cout << "top close = " << t0 << std::endl;
                // BODY
            } else if (i > 0 && i < spineNodes - 2 && j < spines - 1) { // HERE
                t0 = ProtoTuple3i((i - 1) * spines + j + 1, i * spines + j + 1, (i - 1) * spines + j + 2);
                inds.push_back(t0);
                //std::cout << "middle 1 = " << t0 << std::endl;
                
                t0 = ProtoTuple3i((i - 1) * spines + j + 2, i * spines + j + 1, i * spines + j + 2);
                inds.push_back(t0);
                //std::cout << "middle 2 = " << t0 << std::endl;
                // BODY CLOSE
            } else if (i > 0 && i < spineNodes - 2 && j == spines - 1) {
                t0 = ProtoTuple3i((i - 1) * spines + j + 1, i * spines + j + 1, (i - 1) * spines + 1);
                inds.push_back(t0);
                //std::cout << "middle 1 = " << t0 << std::endl;
                
                t0 = ProtoTuple3i((i - 1) * spines + 1, i * spines + j + 1, i * spines + 1);
                inds.push_back(t0);
                //std::cout << "middle 2 = " << t0 << std::endl;
                // BOTTOM
            } else if (i == spineNodes - 1 && j < spines - 1) {
                t0 = ProtoTuple3i(static_cast<int>(verts.size()) - 1, (i - 2) * spines + j + 2, (i - 2) * spines + j + 1);
                inds.push_back(t0);
                //std::cout << "bottom = " << t0 << std::endl;
                //BOTTOM CLOSE
            } else if (i == spineNodes - 1 && j == spines - 1) {
                t0 = ProtoTuple3i(static_cast<int>(verts.size()) - 1, (i - 2) * spines + 1, (i - 2) * spines + j + 1);
                inds.push_back(t0);
                //std::cout << "bottom close = " << t0 << std::endl;
            }
            
            
        }
    }
    //std::cout << "inds.size() = " << inds.size() << std::endl;
    //std::cout << "ctr = " << ctr << std::endl;
}


void ProtoSphere::calcVerts() {
    spines+=1;
    
    verts.resize(spineNodes * spines);
    float x = 0, y = 0, z = 0, u = 0.0, v = 0.0;
    float tempX = 0, tempZ = 0;
    float theta = -PI / 2.0, phi = 0.0;
    // int counter = 0;
	//NEW
	float xi = 0;
    
    // untransformed UNit sphere
    float radiusX = .5;
    float radiusY = .5;
    
    // always 1 more segment than points along spline
    for (int i = 0; i < spineNodes; i++) {
        // z rotation
        //x = cos(theta) * size.w/2;
        //y = sin(theta) * size.h/2;

		//x = cos(theta) * .5 * (1 + random(-chaos.x, chaos.x));
		//y = sin(theta) * .5 * (1 + random(-chaos.y, chaos.y));
		
		x = cos(theta) * size.w / 2 * (1 + random(-chaos.x, chaos.x));
		y = sin(theta) * size.h / 2 * (1 + random(-chaos.y, chaos.y));
        z = 0.0;
        phi = 0.0;
        for (int j = 0; j < spines; j++) {
            
            // y rotation
			tempZ = cos(phi) * (z + random(-chaos.z, chaos.z)) - sin(phi) * (x + random(-chaos.x, chaos.x));
			tempX = sin(phi) * (z + random(-chaos.z, chaos.z)) + cos(phi) * (x + random(-chaos.x, chaos.x));
            
            // test
            //std::cout << "radiusX = " << radiusX << std::endl;
            //std::cout << "radiusY = " << radiusY << std::endl;
//             std::cout << "z = " << z << std::endl;
//             std::cout << "tempX = " << tempX << std::endl;
//             std::cout << "tempZ = " << tempZ << std::endl;
            
            
            // UV mapping expressions form:
            //http://en.wikipedia.org/wiki/UV_mapping
            Vec3f tmp(tempX, y, tempZ);
            tmp.normalize();
            u = .5 + atan2(tmp.z, tmp.x) / (2 * PI);
           // v = .5 - 2.0 * asin(tmp.y) / (2 * PI);
			v = .5 - asin(tmp.y) / (PI);
            
            verts.at(spines*i + j) = ProtoVertex3(Vec3f(tempX, y, tempZ),
                                                  ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()),
                                                  ProtoTuple2f(u, v));
            //std::cout << "ProtoTuple2f(u, v) = " << ProtoTuple2f(u, v) << std::endl;
            
            phi += PI * 2.0 / (spines-4); // ****NOTE*** technically should be spines-1
            //std::cout << "phi = " << (phi*180.0/PI)  << std::endl;
        }
        theta -= PI / (spineNodes - 1);// ****NOTE*** technically should be spineNodes-2
    }
}

void ProtoSphere::calcInds() {
    ProtoTuple3i t0;
    
    // body faces
    for (int i = 0; i < spineNodes - 1; ++i) {
        for (int j = 0; j < spines - 1; ++j) {
            t0 = ProtoTuple3i(i * spines + j, (i + 1) * spines + j + 1, (i + 1) * spines + j);
            inds.push_back(t0);
            //std::cout << "inds open1 = " << t0 << std::endl;
            
            t0 = ProtoTuple3i(i * spines + j, i * spines + j + 1, (i + 1) * spines + j + 1);
            inds.push_back(t0);
            //std::cout << "inds open2 = " << t0 << std::endl;
            
            
        }
    }
    // std::cout << "inds.size() = " << inds.size() << std::endl;
}



