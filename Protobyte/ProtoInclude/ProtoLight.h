/*!  \brief  ProtoLight.h: (add brief description)
 ProtoLight.h
 Protobyte Library v02
 
 Created by Ira on 8/26/13.
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

#ifndef PROTO_LIGHT_H
#define PROTO_LIGHT_H

#include <iostream>
#include "ProtoColor4.h"
#include "ProtoVector3.h"

namespace ijg {
    
    class ProtoLight {
    
    public:
        ProtoLight();
		ProtoLight(const Vec3f& position, const Vec3f& intensity);
		
		ProtoLight(const ProtoColor4f& ambient);
        ProtoLight(const Vec3f& position, const ProtoColor4f& diffuse);
        ProtoLight(const Vec3f& position, const ProtoColor4f& diffuse, const ProtoColor4f& ambient, const ProtoColor4f& specular);
        virtual ~ProtoLight();
        
        enum lightPosMode{
            DIRECTIONAL_INFINITE,
            POSITIONAL
        };
        
        void setPosition(const Vec3f& position);
        const Vec3f& getPosition() const;

		void setIntensity(const Vec3f& intensity);
		const Vec3f& getIntensity() const;
        
        void setDiffuse(const ProtoColor4f& diffuse);
        const ProtoColor4f& getDiffuse() const;
        
        void setAmbient(const ProtoColor4f& ambient);
        const ProtoColor4f& getAmbient() const;
        
        void setSpecular(const ProtoColor4f& specular);
        const ProtoColor4f& getSpecular() const;
        
        
        // user controls
        void on();
        void off();
        
        bool getIsOn() const;
        
        
    private:
        Vec3f position;
		Vec3f intensity; // new 5/21
        
        // Note: Perhaps remove this stuff eventually.
		// Sort of too unconventional without enough
		// benefit/purpose.
		// light properties
        ProtoColor4f diffuse, ambient, specular;
        
        bool isOn;
        
        void init();
        
    };
    
    // accessors/mutators
    inline void ProtoLight::setPosition(const Vec3f& position){
        this->position = position;
		// avoid division by 0 error (I think)
		if (this->position.z == 0){
			this->position.z = .0001;
		}
    }
    
    inline const Vec3f& ProtoLight::getPosition() const{
        return position;
    }

	inline void ProtoLight::setIntensity(const Vec3f& intensity){
		this->intensity = intensity;
	}

	inline const Vec3f& ProtoLight::getIntensity() const{
		return intensity;
	}

    inline void ProtoLight::setDiffuse(const ProtoColor4f& diffuse){
        this->diffuse = diffuse;
    }
    
    inline const ProtoColor4f& ProtoLight::getDiffuse() const{
        return diffuse;
    }

    inline void ProtoLight::setAmbient(const ProtoColor4f& ambient){
        this->ambient = ambient;
    }
    
    inline const ProtoColor4f& ProtoLight::getAmbient() const {
        return ambient;
    }
    
    inline void ProtoLight::setSpecular(const ProtoColor4f& specular){
        this->specular = specular;
    }
    inline const ProtoColor4f& ProtoLight::getSpecular() const{
        return specular;
    }
    
    inline void ProtoLight::on(){
        isOn = true;
    }
    
    inline void ProtoLight::off(){
        isOn = false;
    }
    
    inline bool ProtoLight::getIsOn() const{
        return isOn;
    }

}

#endif // PROTO_LIGHT_H
