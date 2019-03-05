/*!  \brief  ProtoTuple4.h: tuple class with elem0, elem1, elem2, elem3 fields
 ProtoTuple4.h
 Protobyte Library v02
 
 Created by Ira on 3/27/14.
 Copyright (c) 2014 Ira Greenberg. All rights reserved.
 
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

#ifndef PROTO_TUPLE4_H
#define PROTO_TUPLE4_H

#include <iostream>
#include "ProtoVector3.h"

namespace ijg {

	template <class T0, class T1 = T0, class T2 = T0, class T3 = T0>
    class ProtoTuple4 {
    public:
		T0 elem0;
		T1 elem1;
		T2 elem2;
		T3 elem3;
        // T elems[3];

		ProtoTuple4(T0 elem0 = 0, T1 elem1 = 0, T2 elem2 = 0, T3 elem3 = 0) :
			elem0(elem0), elem1(elem1), elem2(elem2), elem3(elem3) {

        }

        // std::ostream& operator<<(std::ostream& out, const ProtoTuple3<T>& tuple3);

    };





    template<typename T>
    std::ostream& operator<<(std::ostream& out, const ProtoTuple4<T>& tuple4) {
		out << tuple4.elem0 << ", " << tuple4.elem1 << ", " << tuple4.elem2 << ", " << tuple4.elem3;
        return out;
    }
        
    // Type name convenience macros
    #define ProtoTuple4i ProtoTuple4<int>
    #define ProtoTuple4f ProtoTuple4<float>
    #define ProtoTuple4d ProtoTuple4<double>
    #define ProtoTuple4v3f ProtoTuple4<ProtoVector3f>
    #define ProtoTuple4b ProtoTuple4<unsigned char>
            
    #define Tup4i ProtoTuple4<int>
    #define Tup4f ProtoTuple4<float>
    #define Tup4d ProtoTuple4<double>
            
    #define Tup4v2f ProtoTuple4<Vec2f>
    #define Tup4v3f ProtoTuple4<Vec3f>
	#define Tup4v3 ProtoTuple4<Vec3f>
	#define Tup4v ProtoTuple4<Vec3f>

}

#endif // PROTO_TUPLE4_H
