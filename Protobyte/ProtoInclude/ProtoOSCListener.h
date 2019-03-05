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

#ifndef PROTO_OSC_LISTENER_H
#define PROTO_OSC_LISTENER_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "ProtoOSCMessage.h"

#include "osc/OscReceivedElements.h"

#include "ip/UdpSocket.h"
#include "osc/OscPacketListener.h"

#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
	using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif

namespace ijg {

	//class ProtoOSCMessage {
	//public:
	//	
	//	int32_t a1, id;
	//	float a3, amp;
	//	ProtoOSCMessage() {}
	//	ProtoOSCMessage(int32_t a1, int32_t id, float a3, float amp):
	//		a1(a1), id(id), a3(a3), amp(amp) {}
	//};
		
	
		class ProtoOSCListener : public osc::OscPacketListener {

	private:
		int port;

	protected:
		void ProcessMessage(const osc::ReceivedMessage& m,
			const IpEndpointName& remoteEndpoint);
	public:
		ProtoOSCMessage* msg;
			
			//friend std::ostream& operator<<(std::ostream& output, const ProtoOSC& oscObj);

		// default cstr
		ProtoOSCListener();

		// overloaded cstr
		ProtoOSCListener(ProtoOSCMessage* msg);


		ProtoOSCMessage getMsg();

		//void receive(int port);


		//void init();
		//void receive(); // client
		//void send(); // server


	};
}

#endif /* defined(PROTO_OSC_LISTENER_H) */
