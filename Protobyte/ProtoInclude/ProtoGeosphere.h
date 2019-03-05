/*!  \brief  ProtoGeoSphere.h: Geodesic Sphere implementation
 Subdivided Icoshahedron
 ProtoGeoSphere.h
 Protobyte Library v02
 
 Created by Ira on 7/23/13.
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

#ifndef PROTO_GEOSPHERE_H
#define	PROTO_GEOSPHERE_H

#include "ProtoGeom3.h"



namespace ijg {
    
    class ProtoGeoSphere : public ProtoGeom3 {
    public:
        
        ProtoGeoSphere();
        
        ProtoGeoSphere(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int subdivisionLevel);
         ProtoGeoSphere(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int subdivisionLevel, const std::string& textureImageURL);
        
        
        // get/sets inlined below class
        void setSubdivisionLevel(int subdivisionLevel);
        int getSubdivisionLevel() const;
        
        
    private:
        int subdivisionLevel;
        
        void calcVerts(); // overrides virtual method in base class
        void calcInds(); // overrides virtual method in base class
    };
    
    
    //inlined gets/sets
    
    inline void ProtoGeoSphere::setSubdivisionLevel(int subdivisionLevel){
        
    }
    inline int ProtoGeoSphere::getSubdivisionLevel() const{
        return subdivisionLevel;
    }
    
   
    typedef ProtoGeoSphere GeoSphere;
    
}

#endif	// PROTO_GEOSPHERE_H

