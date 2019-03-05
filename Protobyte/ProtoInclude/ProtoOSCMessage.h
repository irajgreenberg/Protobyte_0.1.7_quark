#include <cstdlib>
#include <cstring>
#include <iostream>


#ifndef PROTO_OSC_MESSAGE_H
#define PROTO_OSC_MESSAGE_H


namespace ijg {

	class ProtoOSCMessage {
		friend std::ostream& operator<<(std::ostream& out, const ProtoOSCMessage& protoOSCMessage) {
			out << "ai = " << protoOSCMessage.a1 <<
				" a3 = " << protoOSCMessage.a3 <<
				" amp = " << protoOSCMessage.amp <<
				" id = " << protoOSCMessage.id;
			return out;
		}
	
	public:
		// specific properties for SYZYGY 2018
		int32_t a1=0, id=0;
		float a3=0.0f, amp=0.0f;
		
		ProtoOSCMessage() {}
		
		// for Syzygy 29=018
		ProtoOSCMessage(int32_t a1, int32_t id, float a3, float amp) :
			a1(a1), id(id), a3(a3), amp(amp) {}
	};
}
#endif /* defined(PROTO_OSC_MESSAGE_H) */

