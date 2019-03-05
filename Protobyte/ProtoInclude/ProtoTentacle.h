/*!  \brief  Tentacle.cpp: 
 Derived from Tube class with Verlet waving

 Utilizes Tube geometry algoirthms and functions
 to change this implementation declare
 calcVerts() and calcInds();
 
 ProtoTentacle.cpp
 Protobyte Library v02
 
 Created by Ira on 12/27/13.
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


#ifndef PROTO_TENTACLE_H
#define PROTO_TENTACLE_H

#include <iostream>
#include "ProtoTube.h"
#include "ProtoCilia.h"

namespace ijg {
    
    // forward declare & create namespace safe shortname
    class ProtoTentacle;
    typedef ProtoTentacle Tentacle;
    
    
    class ProtoTentacle : public ProtoTube {
    public:
        
        // give outer class private  access
        friend class ProtoCephalopod;
        
        friend std::ostream& operator<<(std::ostream& out, const ProtoTentacle& tentacle);
        
        /*!
         * Constructor */
        ProtoTentacle();
        
        /*!
         * Constructor
         */
        ProtoTentacle(const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * with TransformFunction object
         */
        ProtoTentacle(const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * with TransformFunction object
         */
        ProtoTentacle(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * varied thickness*/
        ProtoTentacle(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * varied color*/
        ProtoTentacle(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * varied color and TransformFunction object*/
        ProtoTentacle(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * varied thickness and color */
        ProtoTentacle(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * All */
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * All with TransformFunction obj*/
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * All with varied radii*/
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * all with varied color */
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * all with varied color and TransformFunction obj */
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed = true);
        
        /*!
         * Constructor
         * All with varied thickness and color */
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, long age, bool isClosed = true);
        
        
        
        
        /*!
         * Constructor
         * all with varied color, TransformFunction obj and texture image*/
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed, const std::string& textureImageURL);
        
        /*!
         * Constructor
         * all with single color, TransformFunction obj and texture image*/
        ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed, const std::string& textureImageURL);
        
        
        
        //
        // HERE
        
        
        
        ~ProtoTentacle();

              //void breath();
        void wave();
        void verlet();
        //void live();
        
        // for live states
        //        void setIsSlithering(bool isSlithering);
        //        bool getIsSlithering() const;
        //        void setIsBreathing(bool isBreathing);
        //        bool getIsBreathing() const;
        
        
        
        void setWaveSpeed(float waveSpeed = .1);
        void setWaveFrequency(float waveFrequency = PI/180.0);
        float getWaveSpeed() const;
        float getWaveFrequency() const;
        
        // *****hack for waving FIX PLEASE****
        int waveDirectionID;
        void setWaveDirectionID(int id){
            waveDirectionID = id;
        }
        
        void setAge(long age);
        long getAge() const;
        
        void setHasCilia(bool hasCilia);
        bool getHasCilia() const;
        
        void setLifeSpan(long lifeSpan);
        
        
        
        
    private:
        Spline3 spine;
        std::vector<float> vertexDataCopy;
        std::vector<int> ciliaNodeIDs;
        
        float waveSpeed;
        float waveFrequency;
        //VerletPath verletPath;
        void init(); // don't think this will interfere with base class implementation, as it's only called internally by derived "this"
        // need to override this in base class to easily allow transformation of spine
        void transform(const ProtoMatrix4f& mat4);
        
        // this used to be in its own VerletPath class, oh well...
        // be careful of <<
        //std::vector< std::shared_ptr<VerletBall> > balls;
        //std::vector< std::unique_ptr<VerletStick> > sticks;
        
        std::vector< std::unique_ptr<Cilia> > cilia;
        float waveTheta;
        
        std::string textureImageURL;
        
        struct VecPtrs {
            float *x_p, *y_p, *z_p;
            VecPtrs(float *x_p, float *y_p, float *z_p):
            x_p(x_p), y_p(y_p), z_p(z_p){
            }
        };
        std::vector<VecPtrs> ciliaAnchors;
        
        long age;
        
        bool hasCilia;
        
        long lifeSpan;
        
    };
    
    inline void ProtoTentacle::setLifeSpan(long lifeSpan) {
        this->lifeSpan = lifeSpan;
    }
    
    inline void ProtoTentacle::setHasCilia(bool hasCilia){
        this->hasCilia = hasCilia;
    }
    
    inline bool ProtoTentacle::getHasCilia() const{
        return hasCilia;
    }

    inline void ProtoTentacle::setAge(long age){
        this->age = age;
    }
    
    inline long ProtoTentacle::getAge() const {
        return age;
    }
    
    
    inline void ProtoTentacle::setWaveSpeed(float waveSpeed){
        this->waveSpeed = waveSpeed;
    }
    
    inline void ProtoTentacle::setWaveFrequency(float waveFrequency){
        this->waveFrequency = waveFrequency;
    }
    
    inline float ProtoTentacle::getWaveSpeed() const{
        return waveSpeed;
    }
    
    inline float ProtoTentacle::getWaveFrequency() const{
        return waveFrequency;
    }
    
    // inline getters | setters
    //    inline void ProtoTentacle::setIsSlithering(bool isSlithering) {
    //        this->isSlithering = isSlithering;
    //    }
    //
    //    inline bool ProtoTentacle::getIsSlithering() const {
    //        return isSlithering;
    //    }
    //
    //    inline void ProtoTentacle::setIsBreathing(bool isBreathing) {
    //        this->isBreathing = isBreathing;
    //    }
    //
    //    inline bool ProtoTentacle::getIsBreathing() const {
    //        return isBreathing;
    //    }
    
}

// PROTO_TENTACLE_H
#endif
