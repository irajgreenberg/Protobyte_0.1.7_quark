/*!  \brief  ProtoGeomSet.h: utility container to group verteices with their linked faces
 main use is for calculating vertex normals
 ProtoGeomSet.h
 Protobyte Library v02
 
 Created by Ira on 11/6/13.
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

#ifndef PROTO_GEOMSET_H
#define PROTO_GEOMSET_H

#include <iostream>
#include "ProtoFace3.h"

namespace ijg {
    
    class ProtoGeomSet {
    
    public:
        ProtoGeomSet();
        ProtoGeomSet(ProtoVertex3* sharedVert, std::vector<ProtoFace3*> linkedFaces);
        
        ProtoVertex3* getSharedVert() const;
        std::vector<ProtoFace3*> getLinkedFaces() const;
        Vec3f getVertexNormal() const;
        
    private:
        ProtoVertex3* sharedVert;
        std::vector<ProtoFace3*> linkedFaces;
        
    };
    
    inline ProtoGeomSet::ProtoGeomSet(){}
    inline ProtoGeomSet::ProtoGeomSet(ProtoVertex3* sharedVert, std::vector<ProtoFace3*> linkedFaces):
    sharedVert(sharedVert), linkedFaces(linkedFaces)
    {}
    
    inline ProtoVertex3* ProtoGeomSet::getSharedVert() const{
        return sharedVert;
    }
    inline std::vector<ProtoFace3*> ProtoGeomSet::getLinkedFaces() const{
        return linkedFaces;
    }
    
    inline Vec3f ProtoGeomSet::getVertexNormal() const{
        Vec3f temp;
        for(int i=0; i<linkedFaces.size(); ++i){
            linkedFaces.at(i)->calcNorm();
            temp += linkedFaces.at(i)->getNorm();
        }
        temp.normalize();
        return temp;
    }

}

#endif /* defined(PROTO_GEOMSET_H) */
