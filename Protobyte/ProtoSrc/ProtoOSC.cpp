/*!  \brief  ProtoOSC.cpp: OSC implementation
 ProtoOSC.cpp
 Protobyte Library v02

 Created by Ira on 2/17/18.
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

#include "ProtoOSC.h"



#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
	using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif

#include "osc/OscReceivedElements.h"

#include "ip/UdpSocket.h"
#include "osc/OscPacketListener.h"

using namespace ijg;

ProtoOSC::ProtoOSC() {
	// after insatiation create msg pointer
	// which gets sent to listener
	
	msg = new ProtoOSCMessage();
	listener = new ProtoOSCListener(msg);
}


ProtoOSC::~ProtoOSC() {
	stop_thread = true;
	if (the_thread.joinable()) the_thread.join();
}


void ProtoOSC::_init() {
}
void ProtoOSC::send() {
}


void ProtoOSC::runOSC(ijg::ProtoOSCListener* listener) {
	UdpListeningReceiveSocket s(
		IpEndpointName(IpEndpointName::ANY_ADDRESS, port),
		listener);

	std::cout << "listening for input on port " << port << "...\n";
	std::cout << "press ctrl-c to end\n";

	s.RunUntilSigInt();

	std::cout << "finishing.\n";
}

void ProtoOSC::receive(int port) {
	this->port = port;
	
	the_thread = std::thread(&ProtoOSC::runOSC, this, listener);
}


ProtoOSCMessage ProtoOSC::getMsg() {
	return listener->getMsg();
}

