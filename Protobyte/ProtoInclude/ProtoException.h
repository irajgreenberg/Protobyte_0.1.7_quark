/*!  \brief  ProtoException.h: Ensure light index within range 0-7
ProtoException.h
Protobyte Library v02

Created by Ira on 9/6/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

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


#ifndef _PROTO_EXCEPTION_H_
#define _PROTO_EXCEPTION_H_

#include <iostream>
#include <stdexcept>

namespace ijg {
	class ProtoException : public std::runtime_error {
	public:
		ProtoException::ProtoException();
	};

}
#endif //_PROTO_EXCEPTION_H_

