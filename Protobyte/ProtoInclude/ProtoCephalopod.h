/*!  \brief  ProtoCephalopod.h: (add brief description)
 ProtoCephalopod.h
 Protobyte Library v02
 
 Created by Ira on 12/12/13.
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

#ifndef PROTO_CEPHALOPOD_H
#define PROTO_CEPHALOPOD_H

#include <iostream>
#include <memory>
#include "ProtoShape3.h"
#include "ProtoGeom3.h"
#include "ProtoGeoSphere.h"
//#include "ProtoTube.h"
#include "ProtoTentacle.h"
#include "ProtoCilia.h"

namespace ijg {
    
    class ProtoCephalopod;
    typedef ProtoCephalopod Cephalopod;
    
    class ProtoCephalopod: public ProtoShape3{
        
    public:
        ProtoCephalopod();
        ProtoCephalopod(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                        const ProtoColor4f& col4, int tentacleCount, long lifespan);
        ProtoCephalopod(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                        const ProtoColor4f& col4, int tentacleCount, long lifespan, const std::string& textureImageURL);
        ~ProtoCephalopod();
        
        //const std::vector<ProtoTentacle>& getTentacles() const;
        void display();
        
        
        const GeoSphere& getBody() const;
        
        void reSpawn();
        
        long getAge() const;
        void setBirthday(long birthday);
        long getBirthday() const;
        
        void setIsSpawnable(bool isSpawnable);
        bool getIsSpawnable() const;
        
        void setLifeSpan(long lifeSpan);
        long getLifeSpan() const;
        
        inline int getRespawnCount() const;
        
    private:
        int tentacleCount;
        // need to be pointers
        std::unique_ptr<GeoSphere> body;
        std::unique_ptr<GeoSphere> shell;
        std::vector<std::unique_ptr<ProtoTentacle> > tentacles;
        std::vector<std::unique_ptr<ProtoTentacle> > tentacleShells;
        void init();
        std::vector<Vec3> offsets; // testing only
        //std::vector<VerletPath> verletPaths;
        
        std::string textureImageURL;
        bool hasCilia;
        long age;
        long birthday;
        long lifeSpan;
        // avoid continuous respawning becasue of fps.
        bool isSpawnable;
        
        double fadeRatio;
        
        int respawnCount;
        
        
    };
    
    
    inline int ProtoCephalopod::getRespawnCount() const{
        return respawnCount;
    }
    
    inline void ProtoCephalopod::setLifeSpan(long lifeSpan){
        this->lifeSpan = lifeSpan;
    }
    
    inline long ProtoCephalopod::getLifeSpan() const{
        return lifeSpan;
    }
    
    inline void ProtoCephalopod::setIsSpawnable(bool isSpawnable){
        this->isSpawnable = isSpawnable;
    }
    
    inline bool ProtoCephalopod::getIsSpawnable() const{
        return isSpawnable;
    }
    
    inline void ProtoCephalopod::setBirthday(long birthday){
        this->birthday = birthday;
    }
    
    inline long ProtoCephalopod::getBirthday()const{
        return birthday;
    }
    
    inline long ProtoCephalopod::getAge()const{
        time_t now = time(0);
        return now-birthday;
    }
    
//    inline const std::vector<ProtoTentacle>& ProtoCephalopod::getTentacles() const
//    {
//        return tentacles;
//    }
    
    inline const ProtoGeoSphere& ProtoCephalopod::getBody() const{
        return *body;
    }
}

#endif // PROTO_CEPHALOPOD_H
