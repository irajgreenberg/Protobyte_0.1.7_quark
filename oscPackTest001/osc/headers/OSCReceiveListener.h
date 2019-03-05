//
//  OSCReceiveListener.h
//  ProtoLib
//  From OSCPack
//
//  Created by Ira Greenberg on 10/31/11.
//  Copyright 2011 SMU. All rights reserved.
//

#ifndef ProtoLib_OSCReceiveListener_h
#define ProtoLib_OSCReceiveListener_h

#include "OscReceiveTest.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "OscReceivedElements.h"

#include "UdpSocket.h"
#include "OscPacketListener.h"

namespace osc{
    
    class OSCReceiveListener: public OscPacketListener{
        
    protected:
        void ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint );
        
    private:
        // for syzergy piece
        int id;
        float amp;
        
    public:
        int getID() const;
        float getAmp() const;
        
        void udpReceiveMessage();
        
    };
}



#endif
