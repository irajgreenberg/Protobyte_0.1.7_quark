//
//  OSCReceiver.h
//  ProtoLib
//
//  Created by Ira Greenberg on 11/21/11.
//  Copyright 2011 SMU. All rights reserved.
//

#ifndef ProtoLib_OSCReceiver_h
#define ProtoLib_OSCReceiver_h



#include <iostream>
#include <cstring>

#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

#include "OSCObj.h"
#include "Abacus.h"


class OSCReceiver : public osc::OscPacketListener {

private:

    const char* address;
    
    // implement this eventually polymorphically!
    // (switc to OSCObj)
    Abacus* abacus; // memory managed by main

protected:
    virtual void ProcessMessage( const osc::ReceivedMessage& m, 
                                const IpEndpointName& remoteEndpoint );
    
public:
    
    OSCReceiver();
    OSCReceiver(const char* address, Abacus* abacus);
};


#endif
