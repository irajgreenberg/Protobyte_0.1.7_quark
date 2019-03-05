/*!  \brief  ProtoOSC.h: Simple OSC implementaiton built on top of oscpack
 ProtoOSC.h
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

#ifndef PROTO_OSC_H
#define PROTO_OSC_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "ProtoGeom3.h"
#include "ProtoOSCMessage.h"

#include "ProtoOSCListener.h"
#include "osc/OscReceivedElements.h"
#include "ip/UdpSocket.h"
#include "osc/OscPacketListener.h"
#include <thread>

namespace ijg {

	

	class ProtoOSC {
	
	private:
		int port;
		void _init();
		void runOSC(ijg::ProtoOSCListener* listener);

		//need seperate thread for osc so doesn't block GLFW draw loop
		std::thread the_thread;
		bool stop_thread = false;
		ijg::ProtoOSCListener* listener;
		ProtoOSCMessage* msg;

	public:
		//friend std::ostream& operator<<(std::ostream& output, const ProtoOSC& oscObj);

		// default cstr
		ProtoOSC();
		
		
		// lame ass approach
		//ProtoOSC();


		// need to stop thread
		~ProtoOSC();
		
		void receive(int port); // client
		void send(); // server

		ProtoOSCMessage getMsg();

	};
}

#endif /* defined(PROTO_OSC_H) */
