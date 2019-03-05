/*!  \brief  ProtoLathe.h: Lathe implementation
ProtoLathe.h
Protobyte Library v02

Created by Ira on 10/14/18.
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

#ifndef PROTO_LATHE_H
#define	PROTO_LATHE_H

#include "ProtoGeom3.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoLathe;
	typedef ProtoLathe Lathe;

	class ProtoLathe : public ProtoGeom3 {
	public:

		ProtoLathe();

		ProtoLathe(const std::vector<Vec3f>& profile, int latheDetail, float latheRadius);

		ProtoLathe(const Vec3f& pos, const Vec3f& rot, const ProtoColor4<float>& col4,
			const std::vector<Vec3f>& profile, int latheDetail, float latheRadius);
		ProtoLathe(const Vec3f& pos, const Vec3f& rot, const ProtoColor4<float>& col4,
			const std::vector<Vec3f>& profile, int latheDetail, float latheRadius, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));


		// get/sets inlined below class
		void setProfile(const std::vector<Vec3f>& profile);
		std::vector<Vec3f>getProfile() const;
		void setLatheDetail(int  latheDetail);
		int getLatheDetail() const;
		void setLatheRadius(float latheRadius);
		float getLatheRadius() const;

		void update();

	private:


		std::vector<Vec3f>& profile;
		int latheDetail{ 12 };
		float latheRadius{ 1.0f };
		

		void calcVerts(); // overrides virtual method in base class
		void calcInds(); // overrides virtual method in base class
	};


	//inlined gets/sets

	inline void ProtoLathe::setProfile(const std::vector<Vec3f>& profile) {
		this->profile = profile;
		update();
	}

	inline std::vector<Vec3f> ProtoLathe::getProfile() const {
		return profile;
	}

	inline void ProtoLathe::setLatheDetail(int  latheDetail) {
		this->latheDetail = latheDetail;
		update();
	}

	inline int ProtoLathe::getLatheDetail() const {
		return latheDetail;
	}

	inline void ProtoLathe::setLatheRadius(float latheRadius) {
		this->latheRadius = latheRadius;
		update();
	}

	inline float ProtoLathe::getLatheRadius() const {
		return latheRadius;
	}


}


#endif	// PROTO_Lathe_H

