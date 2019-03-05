/*!  \brief  ProtoEllipse.h: Simple Ellipse
ProtoEllipse.h
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

#ifndef PROTO_ELLIPSE_H
#define	PROTO_ELLIPSE_H

#include "ProtoGeom3.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoEllipse;
	typedef ProtoEllipse Ellipse;

	class ProtoEllipse : public ProtoGeom3 {
	public:
		friend std::ostream& operator<<(std::ostream& out, const ProtoEllipse& Ellipse);

		ProtoEllipse();
		ProtoEllipse(const Vec3f& pos, const Vec3f& rot, const Dim2f& size,
			const Col4f& col4, int detail);

		void calcVerts(); // overrides virtual method in base class
		void calcInds(); // overrides virtual method in base class

	private:
		int detail;

	};

}

#endif	/* PROTO_ELLIPSE_H */

