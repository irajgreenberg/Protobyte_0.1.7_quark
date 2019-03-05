/*!  \brief  ProtoFace3.h: 3 sided polygon class
 ProtoFace3.h
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

#ifndef PROTO_FACE3_H
#define PROTO_FACE3_H

// for immediate mode GL
#include <GLFW/glfw3.h>

// eventually use this
//#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
//#include "glad/glad.h"
//#endif

#include <vector>
#include "ProtoVertex3.h"
#include "ProtoVector2.h"
#include "ProtoMatrix3.h"
#include <cmath>
#include <iostream>

namespace ijg {
    
	class ProtoFace3;
	typedef ProtoFace3 Face3;
	
	class ProtoFace3 {
    private:
        //ProtoVector3 vecs[3];
        //Vec3f v0, v1, v2;
        ProtoVertex3 vecs[3];
        //ProtoVertex3 v0, v1, v2;
        //ProtoVertex3 *v0_p, *v1_p, *v2_p;
        Vec3f norm, centroid, biNorm, tangent, biTangent;
		Vec3f tangentBM;
        
        void init();
        
    public:
        friend std::ostream& operator<<(std::ostream& output, const ProtoFace3& face3);
        
		// default cstr
		ProtoFace3();
		// overloaded cstr
		ProtoFace3(ProtoVertex3* v0_p, ProtoVertex3* v1_p, ProtoVertex3* v2_p);
        void display();
        
        Vec3f& getNorm();
        Vec3f& getCentroid();
        
        Vec3f getBiNorm();
		Vec3f getTangent();
		Vec3f getTangentBM(); // tangent for bump mapping
		Vec3f getBiTangent() const; // for bump mapping
        
        
        const Vec3f& getNorm() const ;
        //        const Vec3f& getBiNorm() const ;
        //        const Vec3f& getTangent() const ;
        const Vec3f& getCentroid() const ;
        Mat3 getTNBFrame();
        
        
        //const ProtoVertex3& operator[](int index);
        const ProtoVertex3* operator[](int index);
        
        ProtoVertex3 *v0_p, *v1_p, *v2_p;
        
        ProtoVertex3* getVert0_ptr();
        ProtoVertex3* getVert1_ptr();
        ProtoVertex3* getVert2_ptr();
        
        void calcNorm();
        void calcCentroid();

		// hack for retrieval for stl export (fix eventually 
		Vec3f v0, v1, v2, n;
        
    };
    
    
    // const versions
    inline const Vec3f& ProtoFace3::getNorm() const{
        return norm;
    }
    
    inline const Vec3f& ProtoFace3::getCentroid() const {
        return centroid;
    }
    
    //    inline const Vec3f& ProtoFace3::getBiNorm() const{
    //        Vec3 B = norm.cross(getTangent());
    //        return B;
    //    }
    //
    //    inline const Vec3f& ProtoFace3::getTangent() const{
    //        std::cout<< "v2_p->pos = " << v2_p->pos << std::endl;
    //        std::cout<< "v1_p->pos = " << v1_p->pos << std::endl;
    //
    //        Vec3 T = (v1_p->pos - v0_p->pos);
    //        return T;
    //    }
    
    // non const versions
    inline Vec3f& ProtoFace3::getNorm(){
        return norm;
    }
    
    inline Vec3f& ProtoFace3::getCentroid() {
        return centroid;
    }
    
    inline Vec3f ProtoFace3::getBiNorm(){
        Vec3 N = getNorm();
        Vec3 T = getTangent();
        //N.normalize();
        Vec3 B = N.cross(T);
        //trace("B = ", B);
        return B;
    }
    
    // returns normalized face edge as tangent
    inline Vec3f ProtoFace3::getTangent(){
        Vec3 T = v1_p->pos - v0_p->pos;
        T.normalize();
        return T;
    }



	inline Vec3f ProtoFace3::getBiTangent() const{
		return biTangent;
	}
    
    inline Mat3 ProtoFace3::getTNBFrame(){
        // this can be MUCH more efficient
        Vec3 N = getNorm();
        Vec3 T = getTangent();
        Vec3 B = N.cross(T);
        return Mat3(T, N, B);
    }
    
    inline ProtoVertex3* ProtoFace3::getVert0_ptr(){
        return v0_p;
    }
    inline ProtoVertex3* ProtoFace3::getVert1_ptr(){
        return v1_p;
    }
    inline ProtoVertex3* ProtoFace3::getVert2_ptr(){
        return v2_p;
    }
}

#endif /* defined(PROTO_FACE3_H) */
