//
//  OSCReceiveListener.cpp
//  ProtoLib
//  From OSCPack
//
//  Created by Ira Greenberg on 10/31/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include <iostream>
#include "OSCReceiveListener.h"


namespace osc{
    

   // sf::Mutex GlobalMutex;
    
    void OSCReceiveListener::ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint ) {
        //std::cout << "here "<< std::endl;
       // sf::Sleep(.05f);
         //GlobalMutex.Lock();
        try{
			// example of parsing single messages. osc::OscPacketListener
			// handles the bundle traversal.
			  if( strcmp( m.AddressPattern(), "/dataForMatt" ) == 0 ){
				// example #1 -- argument stream interface
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
				osc::int32 a1;
                osc::int32 a2;
                float a3;
                float a4;
                
				args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;
                id = a2;
                amp = a4;
                
                std::cout << "received '/test1' message with arguments: "
                << "id = " << a2 << "amp = " << a4 << "\n";                              
            }  
        }catch( osc::Exception& e ){
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: "
            << m.AddressPattern() << ": " << e.what() << "\n";
        }
        // GlobalMutex.Unlock();
        
    }
    
    int OSCReceiveListener::getID() const {
        return id;
    }
    
    float OSCReceiveListener::getAmp() const {
        return amp;
    }
}