 /*!  \brief  ProtoSpline3.cpp: Catmull-Rom spline class implementation
 ProtoSpline3.cpp
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

#include "ProtoSpline3.h"
//#include "ProtoQuaternion.h"
#include "ProtoMatrix3.h"


#include <iostream>

using namespace ijg;
//Matrix4 m;;

/**
 * Spline cubic curve class, where curve goes through all points. Curve is
 * specified by 6 points, with a constant specifying tension.
 * <p>
 */


ProtoSpline3::ProtoSpline3() {
}

// requires 4 control points to work

ProtoSpline3::ProtoSpline3(const std::vector<Vec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness) :
ProtoCurve3(controlPts, interpDetail, isCurveClosed), smoothness(smoothness) {
    init();
}


/**
 * Calculate the interpolated curve points populating the uniqueVerts array.
 */
void ProtoSpline3::init() {
    
	//Convenient interleaved primitives array of original curve control points.
	controlPtPrims.clear();
	for (auto i : controlPts) {
		controlPtPrims.push_back(i.x);
		controlPtPrims.push_back(i.y);
		controlPtPrims.push_back(i.z);
		controlPtPrims.push_back(0.0f); //r
		controlPtPrims.push_back(0.0f); //g
		controlPtPrims.push_back(0.0f); //b
		controlPtPrims.push_back(1.0f); //a
	}

	// for (int i = 0; i < controlPts.size(); ++i){
	//	trace("controlPts. =", controlPts.at(i));
	// }
	
	// double up first and last control points for spline calculation
	if (isCurveClosed) {
		controlPts.insert(controlPts.begin(), controlPts.at(0));
		controlPts.push_back(controlPts.at(controlPts.size() - 1));
	}
	else 
	//not closed so double up terminal points
	{
		controlPts.insert(controlPts.begin(), controlPts.at(0));
		controlPts.push_back(controlPts.at(controlPts.size() - 1));
	}

	
    //Calculate Catmull-Rom Spline (t3 = t*t*t;)
	// Help from: http://www.mvps.org/directx/articles/catmull/
	Vec3f v0, v1, v2, v3;
    float t2 = 0, t3 = 0;
    float step = 1.0f / (interpDetail + 1);
    
    for (int i = 0; i < controlPts.size() - 3; i++) {
        v0 = controlPts.at(i);
        v1 = controlPts.at(i + 1);
        v2 = controlPts.at(i + 2);
        v3 = controlPts.at(i + 3);
        
        for (float t = 0; t < 1; t += step) {
            t2 = t*t;

 //NOTE: something is screwy with my overloaded ops (Need to FIX) I think it's fixed now (2/2014)
			//float x = smoothness * (
			//	(2.0f * v1.x) +
			//	(-v0.x + v2.x) * t +
			//	(2.0f * v0.x - 5.0f * v1.x + 4.0f * v2.x - v3.x) * t2 +
			//	(-v0.x + 3.0f * v1.x - 3.0f * v2.x + v3.x) * t3
			//	);
			//float y = smoothness * (
			//	(2.0f * v1.y) +
			//	(-v0.y + v2.y) * t +
			//	(2.0f * v0.y - 5.0f * v1.y + 4.0f * v2.y - v3.y) * t2 +
			//	(-v0.y + 3.0f * v1.y - 3.0f * v2.y + v3.y) * t3
			//	);
			//float z = smoothness * (
			//	(2.0f * v1.z) +
			//	(-v0.z + v2.z) * t +
			//	(2.0f * v0.z - 5.0f * v1.z + 4.0f * v2.z - v3.z) * t2 +
			//	(-v0.z + 3.0f * v1.z - 3.0f * v2.z + v3.z) * t3
			//	);

			//Vec3f v = Vec3(x, y, z);
			
			Vec3f v = smoothness * (
					(2.0f * v1) +
                    (-v0 + v2) * t +
                    (2.0f * v0 - 5.0f * v1 + 4.0f * v2 - v3) * t2 +
                    (-v0 + 3.0f * v1 - 3.0f * v2 + v3) * t3
					);
            verts.push_back(v);
			trace("Controlpoints size =", controlPts.size());
			trace("verts size =", verts.size());
        }
    }
    // add last control point to verts vector
    //verts.push_back(controlPts.at(controlPts.size() - 2));
    
        //for (int i = 0; i < verts.size(); i++) {
        //    trace("verts.at(", i, ") = ", verts.at(i));
        //}
    /* ensure tube section don't flip */
    parallelTransport();

	curveVertsPrims.clear();
		// create convenient interleaved primitives array of vertices for shader based curve rendering
	for (auto i : verts) {
		curveVertsPrims.push_back(i.x);
		curveVertsPrims.push_back(i.y);
		curveVertsPrims.push_back(i.z);
		curveVertsPrims.push_back(.3); //r
		curveVertsPrims.push_back(.6); //g
		curveVertsPrims.push_back(.2); //b
		curveVertsPrims.push_back(.85); //a
	}

	//for (int i = 0; i < verts.size(); i++) {
	//	curveVertsPrims.push_back(verts.at(i).x);
	//	curveVertsPrims.push_back(verts.at(i).y);
	//	curveVertsPrims.push_back(verts.at(i).z);
	//	curveVertsPrims.push_back(0.5); //r
	//	curveVertsPrims.push_back(0.5); //g
	//	curveVertsPrims.push_back(0.5); //b
	//	curveVertsPrims.push_back(1.0); //a
	//}
	//trace("curveVertsPrims.size() =", curveVertsPrims.size());
}

/**
 * Set flag for Curve to be closed
 * overrides
 * @param isCurveClosed
 *            boolean value
 */
void ProtoSpline3::setCurveClosed(bool isCurveClosed) {
    this->isCurveClosed = isCurveClosed;
    init();
}

/**
 * Set flag for Curve at Terminals to be continuous
 *
 * @param isTerminalSmooth
 *            boolean value
 */
void ProtoSpline3::setTerminalSmooth(bool isTerminalSmooth) {
    this->isTerminalSmooth = isTerminalSmooth;
    init();
}

/**
 * Draw the curve.
 *
 */
void ProtoSpline3::display(float strokeWeight, Col4 strokeCol) {
	for (int i = 0; i < curveVertsPrims.size(); i += stride) {
		curveVertsPrims.at(i + 3) = strokeCol.getR();
		curveVertsPrims.at(i + 4) = strokeCol.getG();
		curveVertsPrims.at(i + 5) = strokeCol.getB();
		curveVertsPrims.at(i + 6) = strokeCol.getA();
	}

	//enable2DRendering();
	glBindVertexArray(vaoVertsID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboVertsID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat)* curveVertsPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &curveVertsPrims[0]); // upload the data

	glLineWidth(strokeWeight);
	// closed path
	//if (pathRenderMode){
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawArrays(GL_LINE_LOOP, 0, pathPrims.size() / stride);
	//}
	//// open path
	//else {
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawArrays(GL_LINE_STRIP, 0, pathPrims.size() / stride);
	//}
	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_LINE_STRIP, 0, curveVertsPrims.size() / stride);

	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x); 
	
	

	//disable2DRendering();

	// Disable VAO
	glBindVertexArray(0);
}

/**
 * Draw the control points.
 *
 */
void ProtoSpline3::displayControlPts(float pointSize, Col4 strokeCol) {
    //glDisable(GL_CULL_FACE);
    //glDisable(GL_LIGHTING);
    //glPointSize(pointSize);
    //glColor3f(strokeCol.getR(), strokeCol.getG(), strokeCol.getB());
    //// draw points
    //glBegin(GL_POINTS);
    //for (int i = 0; i < controlPts.size(); i++) {
    //    glVertex3f(controlPts.at(i).x, controlPts.at(i).y, controlPts.at(i).z);
    //}
    //glEnd();

	for (int i = 0; i < controlPtPrims.size(); i += stride) {
		controlPtPrims.at(i + 3) = strokeCol.getR();
		controlPtPrims.at(i + 4) = strokeCol.getG();
		controlPtPrims.at(i + 5) = strokeCol.getB();
		controlPtPrims.at(i + 6) = strokeCol.getA();
	}
	glBindVertexArray(vaoVertsID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboVertsID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof(GLfloat) * controlPtPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &controlPtPrims[0]); // upload the data

	glPointSize(pointSize);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // do I need this anymore?

	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	glDrawArrays(GL_POINTS, 0, curveVertsPrims.size() / stride);

	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	// Disable VAO
	glBindVertexArray(0);
}

/**
 * Draw the interpolated points.
 *
 */
void ProtoSpline3::displayInterpPts(float pointSize, Col4 strokeCol) {
	for (int i = 0; i < curveVertsPrims.size(); i += stride) {
		curveVertsPrims.at(i + 3) = strokeCol.getR();
		curveVertsPrims.at(i + 4) = strokeCol.getG();
		curveVertsPrims.at(i + 5) = strokeCol.getB();
		curveVertsPrims.at(i + 6) = strokeCol.getA();
	}
	glBindVertexArray(vaoVertsID);
	// NOTE::this may not be most efficient - eventually refactor
	glBindBuffer(GL_ARRAY_BUFFER, vboVertsID); // Bind the buffer (vertex array data)
	int vertsDataSize = sizeof (GLfloat)* curveVertsPrims.size();
	glBufferData(GL_ARRAY_BUFFER, vertsDataSize, NULL, GL_STREAM_DRAW);// allocate space
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &curveVertsPrims[0]); // upload the data

	glPointSize(pointSize);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // do I need this anymore?
	
	// turn off lighting
	Vec4f ltRenderingFactors(0.0, 0.0, 0.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);
	
	glDrawArrays(GL_POINTS, 0, curveVertsPrims.size() / stride);
	
	//turn on lighting
	ltRenderingFactors = Vec4f(1.0, 1.0, 1.0, 1.0);
	glUniform4fv(lightRenderingFactors_U, 1, &ltRenderingFactors.x);

	// Disable VAO
	glBindVertexArray(0);
}

/**
 * Draw the Frenet Frames.
 *
 */
void ProtoSpline3::displayFrenetFrames(float len) {
    for (int i = 0; i < verts.size(); i++) {
        frenetFrames.at(i).display(len);
    }
}

/**
 * Draw cross-section extruded along the spline path.
 * Default cross-section is an ellipse
 */
void ProtoSpline3::drawCrossSections() {
    for (int i = 0; i < frenetFrames.size(); i++) {
        // draw cross-section ellipse
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        float th = 0;
        for (int j = 0; j < 6; j++) {
            float x = cos(th)*10;
            float y = sin(th)*10;
            //float z = 0;
            float px = verts.at(i + 1).x + x * frenetFrames.at(i).getN().x + y * frenetFrames.at(i).getB().x;
            float py = verts.at(i + 1).y + x * frenetFrames.at(i).getN().y + y * frenetFrames.at(i).getB().y;
            float pz = verts.at(i + 1).z + x * frenetFrames.at(i).getN().z + y * frenetFrames.at(i).getB().z;
            glVertex3f(px, py, pz);
            th += PI * 2.0 / 6.0;
        }
        glEnd();
    }
    
    glPointSize(4);
    for (int i = 0; i < frenetFrames.size(); i++) {
        // draw cross-section ellipse
        glBegin(GL_POINTS);
        float th = 0;
        for (int j = 0; j < 6; j++) {
            float x = cos(th)*10;
            float y = sin(th)*10;
            //float z = 0;
            float px = verts.at(i + 1).x + x * frenetFrames.at(i).getN().x + y * frenetFrames.at(i).getB().x;
            float py = verts.at(i + 1).y + x * frenetFrames.at(i).getN().y + y * frenetFrames.at(i).getB().y;
            float pz = verts.at(i + 1).z + x * frenetFrames.at(i).getN().z + y * frenetFrames.at(i).getB().z;
            glColor3f(0, 1 - 1 / (j + 1), 1 / (j + 1));
            glVertex3f(px, py, pz);
            th += PI * 2 / 6;
        }
        glEnd();
    }
    
}

/**
 * Set the smoothenss value.
 *
 */
void ProtoSpline3::setSmoothness(float smoothness) {
    this->smoothness = smoothness;
}

/**
 * get the smoothenss value.
 *
 */
float ProtoSpline3::getSmoothness(float smoothness) const {
    return smoothness;
}

/**
 * Calculate a Frenet frame for extrusion (tubes/tendrils).
 * - private access
 */

void ProtoSpline3::parallelTransport() {
    // double up first and last verts
    //verts.insert(verts.begin(), verts.at(0));
    //verts.push_back(verts.at(verts.size() - 1));
    
    //frenetFrames.push_back(FrenetFrame(verts.at(0), Vec3f(1,0,0), Vec3f(0,-1,0), Vec3f(0,0,-1))); // add first vert
    // std::cout << "in createFrenetFrame():  verts.size() = " << verts.size() << std::endl;
    std::vector<Vec3f> tans;
    float theta = 0.0;
    Vec3f cp0, cp1, cp2;
    Vec3f tan, biNorm, norm, nextBiNorm, nextNorm;
    
    
    for (int i = 0; i < verts.size(); i++) {
        if (i == 0) {
            //cp0 = verts[verts.size() - 1];
            cp0 = verts.at(i);
            cp1 = verts.at(i);
            cp2 = verts.at(i + 1);
            
        } else if (i == verts.size() - 1) {
            cp0 = verts.at(i - 1);
            cp1 = verts.at(i);
            cp2 = verts.at(i); // 0, circled back here? changed to i
            
        } else {
            cp0 = verts.at(i - 1);
            cp1 = verts.at(i);
            cp2 = verts.at(i + 1);
            
            //std::cout << "i = = " << i << std::endl;
            //            std::cout << "cp0 " << cp0 << std::endl;
            
            //            std::cout << "cp1 " << cp1 << std::endl;
            //            std::cout << "cp2 " << cp2 << std::endl;
            //            std::cout << "cross(cp1, cp2) " << cross(cp1, cp2) << std::endl;
            //std::cout << "cp2 " << cp2 << std::endl;
        }
        // fill tangents
        tan = cp2 - cp0;
        tan.normalize();
        tans.push_back(tan);
        
        // collect initial frame
        if (i == 1) {
            // fix biNorm for parralel vectors
            biNorm = cp1.cross(cp2);
            
            // uh-oh parallel vecs
            // ! HACK ! avoids problems with orthonormal tubes.
            if (biNorm.mag() == 0) {
                
                if (cp1.x !=0 && cp2.x !=0){
                    biNorm = Vec3f(0, 1, 0);
                }
                if (cp1.y !=0 && cp2.y !=0){
                    biNorm = Vec3f(0, 0, -1);
                }
                if (cp1.z !=0 && cp2.z !=0){
                    biNorm = Vec3f(1, 0, 0);
                }
                
            }
            //std::cout << "biNorm pre = " << biNorm << std::endl;
            //std::cout << "biNorm.mag() = " << biNorm.mag() << std::endl;
            biNorm.normalize();
            //            biNorm.x = 1;
            //            biNorm.y = 0;
            //            biNorm.z = 0;
            //            std::cout << "cp1 " << cp1 << std::endl;
            //            std::cout << "cp2 " << cp2 << std::endl;
            //            std::cout << "biNorm post = " << biNorm << std::endl;
            
            norm = biNorm.cross(tan);
            norm.normalize();
        }
    }
    // rotate frame
    
    //  std::cout << "tans.size() = " << tans.size() << std::endl;
    for (int i = 0; i < tans.size() - 1; i++) {
        
        
        if (biNorm.mag() == 0) {
            nextNorm = norm;
            //frenetFrames.push_back(FrenetFrame(verts.at(i), Vec3f(1,1,1), Vec3f(1,1,1), Vec3f(1,1,1)));
            // std::cout << "norm = " << norm << std::endl;
        } else {
            theta = acos(tans.at(i).dot(tans.at(i + 1)));
            Vec3f axis = tans.at(i);
            //std::cout << "tans.at(i + 1) = " << tans.at(i + 1) << std::endl;
            //std::cout << i << std::endl;
            axis = axis.cross(tans.at(i + 1));
            //std::cout << "axis = " << axis << std::endl;
            axis.normalize();
            
            
            
            ProtoMatrix3f m;
            nextNorm = m.getRotate(theta, axis, norm);
            //std::cout << "axis = " << axis << std::endl;
            
            nextBiNorm = tans.at(i + 1);
            nextBiNorm = nextBiNorm.cross(nextNorm);
            
            
            
            // std::cout << "nextNorm = " << nextNorm << std::endl;
            // std::cout << "norm = " << norm << std::endl;
            
        }
        
        //biNorm.normalize();
        //norm.normalize();
        //        std::cout <<i<<std::endl;
        //        std::cout << "tans.at(i) = " << tans.at(i) << std::endl;
		//        std::cout << "biNorm = " << biNorm << std::endl;
        //        std::cout << "norm = " << norm << std::endl;
        frenetFrames.push_back(ProtoFrenetFrame(verts.at(i), tans.at(i), biNorm, norm));
        norm = nextNorm;
        biNorm = nextBiNorm;
        
        //std::cout << "verts = " << verts.at(i) << std::endl;
    }
    // std::cout << "in createFrenetFrame():  frenetFrames.size() = " << frenetFrames.size() << std::endl;
    
}