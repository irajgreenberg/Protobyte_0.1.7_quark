/*!  \brief  ProtoException.cpp
ProtoException.cpp
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


#include "ProtoException.h"

using namespace ijg;
ProtoException::ProtoException() : 
	std::runtime_error("Maximum light count is 8. Use index values 0-7") {}

