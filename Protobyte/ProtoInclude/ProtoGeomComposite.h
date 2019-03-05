/*!  \brief  ProtoGeomComposite.h: Base class to Combine multiple ProtoGeoms
ProtoGeomComposite.h
Protobyte Library v02

Created by Ira on 8/30/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

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

#ifndef PROTO_GEOM_COMPOSITE_H
#define	PROTO_GEOM_COMPOSITE_H

#include "ProtoContext.h"
#include "ProtoToroid.h"

namespace ijg {

	class ProtoGeomComposite {
	protected:
		std::shared_ptr<ProtoContext> ctx;
	
		Toroid t;
	public:
		ProtoGeomComposite();
		void display();
		void init();

		float counter{ 0.0f };

	};
}
#endif // PROTO_GEOM_COMPOSITE_H