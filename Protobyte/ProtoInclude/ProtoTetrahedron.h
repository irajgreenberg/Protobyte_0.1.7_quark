/*!  \brief  ProtoTetrahedron.h: Tetrahedron implementation
ProtoTetrahedron.h
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

#ifndef PROTO_TETRAHEDRON_H
#define	PROTO_TETRAHEDRON_H

#include "ProtoGeom3.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoTetrahedron;
	typedef ProtoTetrahedron Tetrahedron;

	class ProtoTetrahedron : public ProtoGeom3 {
	public:

		ProtoTetrahedron();
		ProtoTetrahedron(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4);
		ProtoTetrahedron(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4,const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));


	private:
		void calcVerts(); // overrides virtual method in base class
		void calcInds(); // overrides virtual method in base class
	};

}


#endif	// PROTO_TETRAHEDRON_H

