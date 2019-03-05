//
//  OSCReceiver.cpp
//  ProtoLib
//
//  Created by Ira Greenberg on 11/21/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include <iostream>
#include "OSCReceiver.h"
//#include "Toroid.h"


OSCReceiver::OSCReceiver() { }

OSCReceiver::OSCReceiver(const char* address) :
	address(address) { }

//OSCReceiver::OSCReceiver(const char* address, Abacus* abacus):
//address(address), abacus(abacus) { }


void OSCReceiver::ProcessMessage( const osc::ReceivedMessage& m, 
                            const IpEndpointName& remoteEndpoint ) {
   
    
    try{
        // example of parsing single messages. osc::OsckPacketListener
        // handles the bundle traversal.
        
        std::cout << "here i m " << std::endl;
        
        if( std::strcmp( m.AddressPattern(), address ) == 0 ){
            // example #1 -- argument stream interface
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            osc::int32 a1;
            osc::int32 id;
            float a3;
            float amp;            
            args >> a1 >> id >> a3 >> amp >> osc::EndMessage;
            
           // this waaaay too specific here in the class
            // make more polymorphic
           // Toroid** beads = abacus->getBeads();
            std::cout << "a1 = " << a1 << std::endl;
            // NOTE remove multiplication here
            /* if (id > -1 && id < abacus->getCols() *  abacus->getRows()){
                 beads[id]->setAmp(amp);
            }*/
            
        } else {   std::cout << "OSC address not found" << std::endl;   }
    }catch( osc::Exception& e ){
        // any parsing errors such as unexpected argument types, or 
        // missing arguments get thrown as exceptions.
        std::cout << "error while parsing message: "
        << m.AddressPattern() << ": " << e.what() << "\n";
    }
}
