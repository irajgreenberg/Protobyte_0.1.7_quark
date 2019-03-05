/*!  \brief  ProtoCylinder.h: (add brief description)
 ProtoCylinder.h
 Protobyte Library v02

 Created by Ira on 12/23/13.
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

#ifndef Protobyte_dev_ProtoCylinder_cpp
#define Protobyte_dev_ProtoCylinder_cpp

#include <iostream>
#include "ProtoGeom3.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoCylinder;
	typedef ProtoCylinder Cylinder;
	
	class ProtoCylinder : public ProtoGeom3 {

	public:
		enum Registration {
			TOP,
			CENTER,
			BOTTEM
		};

		// critical params

		// Significant params: position, size, detail, texture
		ProtoCylinder();
		ProtoCylinder(int detail, Registration reg=CENTER);
		ProtoCylinder(const Vec3& pos, int detail, Registration reg = CENTER);
		ProtoCylinder(const Dim3f& size, int detail, Registration reg = CENTER);
		ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, Registration reg = CENTER);
		ProtoCylinder(int detail, const std::string& textureImageURL, Registration reg = CENTER);
		ProtoCylinder(const Vec3& pos, int detail, const std::string& textureImageURL, Registration reg = CENTER);
		ProtoCylinder(const Dim3f& size, int detail, const std::string& textureImageURL, Registration reg = CENTER);
		ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, const std::string& textureImageURL, Registration reg = CENTER);
		ProtoCylinder(const Vec3& pos, const Dim3f& size, int detail, const Col4f& col, const std::string& textureImageURL, Registration reg = CENTER);
		

		void setDetail(int sides);
		int getDetail() const;

	private:
		// fields
		int detail;
		Registration registration;

		// methods
		void calcVerts(); // overrides virtual method in base class
		void calcInds(); // overrides virtual method in base class
	};

	//implement getters/setters inline
	inline void ProtoCylinder::setDetail(int detail){
		this->detail = detail;

		// need to call init or reset here
	}

	inline int ProtoCylinder::getDetail() const{
		return detail;
	}
}

#endif // Protobyte_dev_ProtoCylinder_cpp
