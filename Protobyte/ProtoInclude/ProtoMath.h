/*!  \brief  ProtMath.h: Protobyte Library math constants and random functions
 - all static
 ProtoMath.h
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

#ifndef PROTO_MATH_H
#define	PROTO_MATH_H

#include <cmath>
#include <ctime>
#include <cstdlib>

namespace ijg {
    
    // static fields - initialized in .cpp
    static const double PI = 3.14159265358979;
    static const double HALF_PI = 1.5707963267949;
    static const double QUARTER_PI = 0.785398163397448;
    static const double TWO_PI = 6.28318530717958;
    static const double THREE_PI = 9.42477796077;
    
    
    // eventually replace these with Mersenne twister algorithm
    // from http://stackoverflow.com/a/686373
    float random(float max=1.0f);
    float random(float min, float max);
	float getMin(float val0, float val1);
	float getMax(float val0, float val1);
    float constrain(float val, float min, float max);
//    float dist(Vec3f, Vec3f);
//    float dist(float x1, float y1, float z1, float x2, float y3, float z4);
 
    
#define H_PI HALF_PI
#define Q_PI QUARTER_PI
#define DOUBLE_PI TWO_PI
#define TRI_PI THREE_PI
    
}


#endif	// PROTO_MATH_H

