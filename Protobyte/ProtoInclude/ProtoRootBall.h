/*!  \brief  ProtoRootBall.h: 
ProtoRootBall.h
Protobyte Library v02

Created by Ira on 04/30/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

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

#ifndef PROTO_ROOTBALL_H
#define PROTO_ROOTBALL_H

#include <iostream>
#include "ProtoShape3.h"
#include "ProtoTube.h"

namespace ijg {

	class ProtoRootBall;
	typedef ProtoRootBall RootBall;

	class ProtoRootBall : public ProtoShape3{

	private:
	
		int rootCount;
		float turbulence;
		int rootSegments;
		Tup2f rootRadii;
		std::vector<std::string> textureURLs;
		std::vector<Vec2f> textureScales;
		std::vector<Tube> roots;

		// unparameterized in cstr's
		ProtoTransformFunction transform;
		std::vector<Spline3> rootSplines;


		void init();
		void update(); // called internally after setter invoked
	
	public:
		ProtoRootBall();

		// no texture
		ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const ProtoColor4f& col4, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii);

		// no texture, multi colors
		ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii);
		
		// texture
		ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const ProtoColor4f& col4, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::string& textureURL, const Vec2f& textureScale);

		// texture, multi-colors
		ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::string& textureURL, const Vec2f& textureScale);

		// multi-textures, multi-colors
		ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::vector<std::string>& textureURLs, const Vec2f& textureScale);

		// multi-textures, multi-colors, multi-texture scales
		ProtoRootBall(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<ProtoColor4f>& col4s, int rootCount, int rootSegments, float turbulence, const Tup2f& rootRadii, const std::vector<std::string>& textureURLs, std::vector<Vec2f> textureScales);

		void display(Geom3::RenderMode render = SURFACE, float pointSize = .5);
		// getters / setters
		void setRootCount(int rootCount);
		int getRootCount() const;

		void setRootSegments(int rootSegments);
		int getRootSegments() const;

		void setTurbulence(float turbulence);
		float getTurbulence() const;

		void setRootRadii(const Tup2f& rootRadii);
		const Tup2f& getRootRadii() const; // const 

		void setTextureURL(const std::string& textureURL); // set 1st tex
		void setTextureURLs(const std::string& textureURL); // set all texs
		void setTextureURLs(const std::vector<std::string>& textureURLs);
		
		const std::string& getTextureURL() const; 
		const std::vector<std::string>& getTextureURLs() const;

		void setTextureScale(const Vec2f& textureScale); // set 1st tex scl
		void setTextureScales(const Vec2f& textureScale); // set all tex scls
		void setTextureScales(const std::vector<Vec2f>& textureScales);
		
		Vec2f getTextureScale() const;
		const std::vector<Vec2f>& getTextureScales() const;

		void setTransformFunction(const TransformFunction& transform);
		const TransformFunction& getTransformFunction() const;

		void setRootSpline(const Spline3& rootSpline);
		const Spline3& getRootSpline() const; 
		
		void setRootSplines(const std::vector<Spline3>& rootSplines);
		const std::vector<Spline3>& getRootSplines() const;

		std::vector<Tup4v> getGeomData();

		void setBumpMap(const std::string& bumpMapImageURL);
		void setBumpMaps(const std::vector<std::string>& bumpMapImageURLs);

	};

	// getters / setters
	inline void ProtoRootBall::setRootCount(int rootCount){
		this->rootCount = rootCount;
	}
	inline int ProtoRootBall::getRootCount() const{
		return rootCount;
	}

	inline void ProtoRootBall::setRootSegments(int rootSegments){
		this->rootSegments = rootSegments;
	}

	inline int ProtoRootBall::getRootSegments() const{
		return rootSegments;
	}

	inline void ProtoRootBall::setTurbulence(float turbulence){
		this->turbulence = turbulence;
	}
	inline float ProtoRootBall::getTurbulence() const{
		return turbulence;
	}

	inline void ProtoRootBall::setRootRadii(const Tup2f& rootRadii){
		this->rootRadii = rootRadii;
	}

	inline const Tup2f& ProtoRootBall::getRootRadii() const{
		return rootRadii;
	}

	inline void ProtoRootBall::setTextureURL(const std::string& textureURL){
		// 1 texture passed in
		for (int i = 0; i < rootCount; ++i){
			if (i == 0)
				textureURLs.push_back(textureURL);
			else
				textureURLs.push_back("white_tile.jpg");
		}
	}
	
	inline void ProtoRootBall::setTextureURLs(const std::string& textureURL){
		// 1 texture passed in
		for (int i = 0; i < rootCount; ++i){
				textureURLs.push_back(textureURL);
		}
	}

	inline void ProtoRootBall::setTextureURLs(const std::vector<std::string>& textureURLs){
		this->textureURLs = textureURLs;
	}

	inline const std::string& ProtoRootBall::getTextureURL() const{
		return textureURLs.at(0);
	}

	inline const std::vector<std::string>& ProtoRootBall::getTextureURLs() const{
		return textureURLs;
	}

	inline void ProtoRootBall::setTextureScale(const Vec2f& textureScale){
		for (int i = 0; i < rootCount; ++i){
			if (i == 0)
				textureScales.push_back(textureScale);
			else 
				textureScales.push_back(Vec2f(1));
		}
	}

	inline void ProtoRootBall::setTextureScales(const Vec2f& textureScale){
		for (int i = 0; i < rootCount; ++i){
				textureScales.push_back(textureScale);
		}
	}

	inline void ProtoRootBall::setTextureScales(const std::vector<Vec2f>& textureScales){
		this->textureScales = textureScales;
	}

	inline Vec2f ProtoRootBall::getTextureScale() const{
		return textureScales.at(0);
	}

	inline const std::vector<Vec2f>& ProtoRootBall::getTextureScales() const{
		return textureScales;
	}

	inline void ProtoRootBall::setTransformFunction(const TransformFunction& transform){
		this->transform = transform;
		update(); // recalculate roots
	}

	inline const TransformFunction& ProtoRootBall::getTransformFunction() const{
		return transform;
	}

	inline void ProtoRootBall::setRootSpline(const Spline3& rootSpline){
		for (int i = 0; i < rootCount; ++i){
			rootSplines.push_back(rootSpline);
		}
		update(); // recalculate roots
	}

	inline const Spline3& ProtoRootBall::getRootSpline() const{
		return rootSplines.at(0);
	}

	inline void ProtoRootBall::setRootSplines(const std::vector<Spline3>& rootSplines){
		this->rootSplines = rootSplines;
		update(); // recalculate roots
	}

	inline const std::vector<Spline3>& ProtoRootBall::getRootSplines() const{
		return rootSplines;
	}
}

#endif // PROTO_ROOTBALL_H