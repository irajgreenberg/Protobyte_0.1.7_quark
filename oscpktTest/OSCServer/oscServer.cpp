/*
This is a lame ping-ping demo for oscpkt
*/

#define OSCPKT_OSTREAM_OUTPUT
#include "oscpkt.hh"
#include "udp.hh"
#include <stdint.h>

//using std::cout;
//using std::cerr;

using namespace oscpkt;

const int PORT_NUM = 9109;

void runServer() {
	UdpSocket sock;
	sock.bindTo(PORT_NUM);
	if (!sock.isOk()) {
		std::cerr << "Error opening port " << PORT_NUM << ": " << sock.errorMessage() << "\n";
	}
	else {
		std::cout << "Server started, will listen to packets on port " << PORT_NUM << std::endl;
		PacketReader pr;
		PacketWriter pw;
		while (sock.isOk()) {
			if (sock.receiveNextPacket(30 /* timeout, in ms */)) {
				pr.init(sock.packetData(), sock.packetSize());
				oscpkt::Message *msg;
				while (pr.isOk() && (msg = pr.popMessage()) != 0) {
					int iarg;
					if (msg->match("/ping").popInt32(iarg).isOkNoMoreArgs()) {
						std::cout << "Server: received /ping " << iarg << " from " << sock.packetOrigin() << "\n";
						//Message repl; repl.init("/pong").pushInt32(iarg + 1);
						Message repl; repl.init("/pong").pushInt32(79);
						pw.init().addMessage(repl);
						sock.sendPacketTo(pw.packetData(), pw.packetSize(), sock.packetOrigin());
					}
					else {
						std::cout << "Server: unhandled message: " << *msg << "\n";
					}
				}
			}
		}
	}
}


int main(int argc, char **argv) {

	//if (argc > 1 && strcmp(argv[1], "--serv") == 0) {
		runServer();
	//}
}
