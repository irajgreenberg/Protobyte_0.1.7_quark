#pragma once

/*!  \brief  PROTO_EMITTER.h: Emits particles for particle system
 ProtoParticleEmitter.h
 Protobyte Library v02

 class Created by Ira on 8/6/19.

 Protobyte Library Copyright (c) 2013 Ira Greenberg. All rights reserved.

 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.

 This notice must be retained in any source distribution.

 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */


#ifndef PROTO_EMITTER_H
#define PROTO_EMITTER_H

//#include "ProtoCore.h"
//#include <string.h>
//#include <iostream>
//#include <vector>
//#include "ProtoMath.h"
//#include <cmath>
//#include <cassert>
#include "ProtoVector3.h"
//#include "ProtoColor4.h"
//#include "ProtoContext.h"

namespace ijg {


	// forward declaration and namespace safe short names
	class ProtoEmitter;
	typedef  ProtoEmitter Emitter; // common usage
	
	class ProtoEmitter {

	public:
		ProtoEmitter();
		void emit();

	private:
		Vec Position;


	};

} // END ijg namespace
#endif //PROTO_EMITTER_H

