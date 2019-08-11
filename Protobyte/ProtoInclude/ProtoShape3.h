/*!  \brief  ProtoShape3.h: Abstact Base Shape class
 ProtoShape3.h
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

#ifndef PROTO_SHAPE3_H
#define	PROTO_SHAPE3_H

#include <iostream>
//#include <algorithm>
#include "ProtoCore.h"
#include "ProtoUtility.h"
#include <vector>
#include "ProtoMath.h"
#include "ProtoVector3.h"
#include "ProtoDimension3.h"
#include "ProtoTuple4.h"
#include "ProtoColor4.h"
#include "ProtoMatrix3.h"
#include "ProtoMatrix4.h"

#include <memory>
#include <sstream>


// preproc dir for relative resource loading
// from http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
// http://www.daniweb.com/software-development/cpp/threads/202937/ifdef-with-boolean-and-or
#include <stdio.h>  /* defines FILENAME_MAX */
#if defined (_WIN32) || defined (_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
// end relative loading proproc dir

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoShape3;
	typedef ProtoShape3 Shape3;

    class ProtoShape3 {
    public:
        
        friend std::ostream& operator<<(std::ostream& out, const ProtoShape3& shape);
        
        enum RenderMode {
            POINTS,
            WIREFRAME, // begin at 0
            SURFACE
        };

        
        /*!
         * Default Constructor */
        ProtoShape3();

        /*!
         * Constructor */
        ProtoShape3(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                const ProtoColor4f& col4);
        
        /*!
         * Constructor */
        ProtoShape3(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                const std::vector< ProtoColor4f >& col4s);

        virtual ~ProtoShape3();

        // setters
        virtual void setPosition(const Vec3f& pos);
        virtual void setRotation(const Vec3f& rot);
        virtual void setSize(const ProtoDimension3f& size);
        virtual void setColor(const ProtoColor4f& col4);
        virtual void setRotSpd(const Vec3f& rotSpd);
        virtual void setSpd(const Vec3f& spd);

        // getters
        virtual Vec3f getPosition() const;
        virtual Vec3f getRotation() const;
        virtual ProtoDimension3f getSize() const;
        virtual ProtoColor4f getColor() const;
        virtual Vec3f getRotSpd() const;
        virtual Vec3f getSpd() const;
        
        // convenience ops
        ProtoShape3& operator+=(const Vec3f v);
        ProtoShape3& operator-=(const Vec3f v);
        ProtoShape3& operator+=(float s);
        ProtoShape3& operator-=(float s);
		Vec3f pos, rot;
    protected:
       // Vec3f pos, rot;
        Dim3f size;
        ProtoColor4f col4;
        std::vector< ProtoColor4f > col4s;
        Vec3f spd, rotSpd;


    private:
        // nothing  here yet

    };

    // setters

    inline void ProtoShape3::setPosition(const Vec3f& pos) {
        this->pos = pos;
    }

    inline void ProtoShape3::setRotation(const Vec3f& rot) {
        this->rot = rot;
    }

    inline void ProtoShape3::setSize(const Dim3f& size) {
        this->size = size;
    }

    inline void ProtoShape3::setColor(const ProtoColor4f& col4) {
        this->col4 = col4;
    }

    inline void ProtoShape3::setRotSpd(const Vec3f& rotSpd) {
        this->rotSpd = rotSpd;
    }

    inline void ProtoShape3::setSpd(const Vec3f& spd) {
        this->spd = spd;
    }

    // getters

    inline Vec3f ProtoShape3::getPosition() const {
        return pos;
    }

    inline Vec3f ProtoShape3::getRotation() const {
        return rot;
    }

    inline ProtoDimension3f ProtoShape3::getSize() const {
        return size;
    }

    inline ProtoColor4f ProtoShape3::getColor() const {
        return col4;
    }

    inline Vec3f ProtoShape3::getRotSpd() const {
        return rotSpd;
    }

    inline Vec3f ProtoShape3::getSpd() const {
        return spd;
    }
    
    // ops
    
    inline ProtoShape3& ProtoShape3::operator+=(const Vec3f v) {
        pos+=v;
        return *this;
    }
    
    inline ProtoShape3& ProtoShape3::operator-=(const Vec3f v){
        pos-=v;
        return *this;
    }
    
    inline ProtoShape3& ProtoShape3::operator+=(float s){
        pos+=s;
        return *this;
    }
    
    inline ProtoShape3& ProtoShape3::operator-=(float s){
        pos-=s;
        return *this;
    }

}

#endif	/* PROTO_SHAPE3_H */

