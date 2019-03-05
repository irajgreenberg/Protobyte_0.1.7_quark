/*!  \brief  ProtoOSCListener.cpp: OSC Listener
 ProtoOSCListener.cpp
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

#include "ProtoOSCListener.h"



using namespace ijg;


ProtoOSCListener::ProtoOSCListener() {}

// overloaded cstr
ProtoOSCListener::ProtoOSCListener(ProtoOSCMessage* msg) :
	msg(msg) {
}


void ijg::ProtoOSCListener::ProcessMessage(const osc::ReceivedMessage& m,
	const IpEndpointName& remoteEndpoint) {

	(void)remoteEndpoint; // suppress unused parameter warning

					  // a more complex scheme involving std::map or some other method of
					  // processing address patterns could be used here 
					  // (see MessageMappingOscPacketListener.h for example). however, the main
					  // purpose of this example is to illustrate and test different argument
					  // parsing methods

	try {
		// argument stream, and argument iterator, used in different
		// examples below.
		osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
		osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();

		if (std::strcmp(m.AddressPattern(), "/dataForMatt") == 0) {

			// parse an expected format using the argument stream interface:
			osc::int32 a1, a2;
			float a3, a4;
			

			// osc::int32 a1;
			// osc::int32 id;
			// float a3;
			// float amp;            
			// args >> a1 >> id >> a3 >> amp >> osc::EndMessage;


			// populate vars with passed values
			args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;

			msg->a1 = a1;
			msg->id = a2;
			msg->a3 = a3;
			msg->amp = a4;

			//if (msg->amp > 0) {
			//	std::cout << "a1 = " << msg->a1 << std::endl;
			//	std::cout << "id = " << msg->id << std::endl;
			//	std::cout << "a3 = " << msg->a3 << std::endl;
			//	std::cout << "amp = " << msg->amp << std::endl;
			//	
			//	//std::cout << msg->amp << std::endl;
			//}


		}
		else if (std::strcmp(m.AddressPattern(), "/test2") == 0) {

			// example #2:
			// parse an expected format using the argument iterator interface
			// this is a more complicated example of doing the same thing
			// as above.
			bool a1 = (arg++)->AsBool();
			int a2 = (arg++)->AsInt32();
			float a3 = (arg++)->AsFloat();
			const char *a4 = (arg++)->AsString();
			if (arg != m.ArgumentsEnd())
				throw osc::ExcessArgumentException();

			std::cout << "received '/test2' message with arguments: "
				<< a1 << " " << a2 << " " << a3 << " " << a4 << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/test3") == 0) {

			// example #3:
			// parse a variable argument format using the argument iterator
			// interface. this is where it is necessary to use
			// argument iterators instead of streams.
			// When messages may contain arguments of varying type, you can
			// use the argument iterator interface to query the types at
			// runtime. this is more flexible that the argument stream
			// interface, which requires each argument to have a fixed type

			if (arg->IsBool()) {
				bool a = (arg++)->AsBoolUnchecked();
				std::cout << "received '/test3' message with bool argument: "
					<< a << "\n";
			}
			else if (arg->IsInt32()) {
				int a = (arg++)->AsInt32Unchecked();
				std::cout << "received '/test3' message with int32 argument: "
					<< a << "\n";
			}
			else if (arg->IsFloat()) {
				float a = (arg++)->AsFloatUnchecked();
				std::cout << "received '/test3' message with float argument: "
					<< a << "\n";
			}
			else if (arg->IsString()) {
				const char *a = (arg++)->AsStringUnchecked();
				std::cout << "received '/test3' message with string argument: '"
					<< a << "'\n";
			}
			else {
				std::cout << "received '/test3' message with unexpected argument type\n";
			}

			if (arg != m.ArgumentsEnd())
				throw osc::ExcessArgumentException();


		}
		else if (std::strcmp(m.AddressPattern(), "/no_arguments") == 0) {

			args >> osc::EndMessage;
			std::cout << "received '/no_arguments' message\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_bool") == 0) {

			bool a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_bool' message: " << a << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/nil") == 0) {

			std::cout << "received '/nil' message\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/inf") == 0) {

			std::cout << "received '/inf' message\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/an_int") == 0) {

			osc::int32 a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/an_int' message: " << a << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_float") == 0) {

			float a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_float' message: " << a << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_char") == 0) {

			char a;
			args >> a >> osc::EndMessage;
			char s[2] = { 0 };
			s[0] = a;
			std::cout << "received '/a_char' message: '" << s << "'\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/an_rgba_color") == 0) {

			osc::RgbaColor a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/an_rgba_color' message: " << a.value << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_midi_message") == 0) {

			osc::MidiMessage a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_midi_message' message: " << a.value << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/an_int64") == 0) {

			osc::int64 a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/an_int64' message: " << a << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_time_tag") == 0) {

			osc::TimeTag a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_time_tag' message: " << a.value << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_double") == 0) {

			double a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_double' message: " << a << "\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_string") == 0) {

			const char *a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_string' message: '" << a << "'\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_symbol") == 0) {

			osc::Symbol a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_symbol' message: '" << a.value << "'\n";

		}
		else if (std::strcmp(m.AddressPattern(), "/a_blob") == 0) {

			osc::Blob a;
			args >> a >> osc::EndMessage;
			std::cout << "received '/a_blob' message\n";

		}
		else {
			std::cout << "unrecognised address pattern: "
				<< m.AddressPattern() << "\n";
		}

	}
	catch (osc::Exception& e) {
		std::cout << "error while parsing message: "
			<< m.AddressPattern() << ": " << e.what() << "\n";
	}
}




ProtoOSCMessage ProtoOSCListener::getMsg() {
	return *msg;
}