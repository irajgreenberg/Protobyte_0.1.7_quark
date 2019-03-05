/*
This is a lame ping-ping demo for oscpkt
*/

#define OSCPKT_OSTREAM_OUTPUT
#include "oscpkt.hh"
#include "udp.hh"
#include <stdint.h>

using namespace oscpkt;

const int PORT_NUM = 9109;


void runClient() {
	UdpSocket sock;
	sock.connectTo("localhost", PORT_NUM);
	if (!sock.isOk()) {
		std::cerr << "Error connection to port " << PORT_NUM << ": " << sock.errorMessage() << "\n";
	}
	else {
		std::cout << "Client started, will send packets to port " << PORT_NUM << std::endl;
		int iping = 1;
		while (sock.isOk()) {
			Message msg("/ping"); msg.pushInt32(iping);
			PacketWriter pw;
			pw.startBundle().startBundle().addMessage(msg).endBundle().endBundle();
			bool ok = sock.sendPacket(pw.packetData(), pw.packetSize());
			std::cout << "Client: sent /ping " << iping++ << ", ok=" << ok << "\n";
			// wait for a reply ?
			if (sock.receiveNextPacket(30 /* timeout, in ms */)) {
				PacketReader pr(sock.packetData(), sock.packetSize());
				Message *incoming_msg;
				while (pr.isOk() && (incoming_msg = pr.popMessage()) != 0) {
					std::cout << "Client: received " << *incoming_msg << "\n";
				}
			}
		}
		std::cout << "sock error: " << sock.errorMessage() << " -- is the server running?\n";
	}
}

int main(int argc, char **argv) {
	//if (argc > 1 && strcmp(argv[1], "--cli") == 0) {
		runClient();
	//}

}
