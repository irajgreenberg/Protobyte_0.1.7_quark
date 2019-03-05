/*!  \brief  ProtoQuaternion.h: quaternion implementation
 ProtoQuaternion.h
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

#ifndef PROTO_QUATERNION_h
#define PROTO_QUATERNION_h

#include "ProtoVector3.h"

namespace ijg {

	class ProtoQuaternion;
	typedef ProtoQuaternion Quaternion;

	/*****************************************************/
	/*            Non-Member Ops & Functions             */
	/*****************************************************/
	ProtoQuaternion operator*(const ProtoQuaternion& lhs, const ProtoQuaternion& rhs); // need to implement
	
	class ProtoQuaternion {
    public:
        // fields
        float x, y, z, w;
        
        // constructor
		ProtoQuaternion(const Vec3& axis = Vec3(0, 0, 1), float theta = 0);
        ProtoQuaternion(float x, float y, float z, float w);
        //void rotate(ProtoVector3 v);
		Vec3 getRotate(const Vec3& v); // return
		void rotate(Vec3& v); // update in place
        float mag() const;
        void normalize();
        
       
        void operator*=(const ProtoQuaternion& q); // need to implement
        
		void setAxis(const Vec3& axis);
		const Vec3& getAxis() const;
        
    private:
		Vec3 axis;
        float theta;

    };
    
}

#endif // PROTO_QUATERNION_h
