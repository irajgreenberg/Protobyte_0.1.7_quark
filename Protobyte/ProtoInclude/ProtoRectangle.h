/*!  \brief  ProtoRectangle.h: Rectangle implementation
ProtoRectangle.h
Protobyte Library v02

Created by Ira on 6/25/15.
Copyright (c) 2015 Ira Greenberg. All rights reserved.

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

#ifndef _PROTO_RECTANGLE_H
#define	_PROTO_RECTANGLE_H

#include <iostream>
#include "ProtoGeom3.h"

namespace ijg {

	class ProtoRectangle;
	typedef ProtoRectangle Rect;

	class ProtoRectangle : public ProtoGeom3 {
	
	public:
		friend std::ostream& operator<<(std::ostream& out, const ProtoRectangle& rectangle);
		
		/*!
		* Default Constructor */
		ProtoRectangle();
		
		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos, const Dim2f& size, const ProtoColor4<float>& col4);

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, const Dim2f& size, const ProtoColor4<float>& col4);
		
		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos, const Dim2f& size, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, const Dim2f& size, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos, const Dim2f& size,
			const std::vector<Col4f>& cols4);

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, const Dim2f& size,
			const std::vector<Col4f>& cols4);
		
		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos,  const Dim2f& size, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, const Dim2f& size, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		// w, h
		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos, float w, float h, const ProtoColor4<float>& col4);

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, float w, float h, const ProtoColor4<float>& col4);

		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos, float w, float h, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, float w, float h, const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos, float w, float h,
			const std::vector<Col4f>& cols4);

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, float w, float h,
			const std::vector<Col4f>& cols4);

		/*!
		* Constructor */
		ProtoRectangle(const Vec2f& pos, float w, float h, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		/*!
		* Constructor */
		ProtoRectangle(float x, float y, float w, float h, const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));



		/*!
		* Declared pure virtual in GeomBase base class
		* and must be implemented in all derived classes.
		*
		* Generates all vertices.*/
		void calcVerts();


		/*!
		* Declared pure virtual in GeomBase base class
		* and must be implemented in all derived classes:
		*
		* Generates indices to group vertices to triangle faces.*/
		void calcInds();

		void setX(float x);
		float getX();
		void setY(float y);
		float getY();
		void setW(float w);
		float getW();
		void setH(float h);
		float getH();


	};

	/*!
	* conveninece inline primitive getters/setters */
	inline void ProtoRectangle::setX(float x){ pos.x = x; }
	inline float  ProtoRectangle::getX(){ return pos.x; }
	inline void  ProtoRectangle::setY(float y){ pos.y = y; }
	inline float  ProtoRectangle::getY(){ return pos.y; }
	inline void  ProtoRectangle::setW(float w){ size.w = w; }
	inline float  ProtoRectangle::getW(){ return size.w; }
	inline void  ProtoRectangle::setH(float h){ size.h = h; }
	inline float  ProtoRectangle::getH(){ return size.h; }
}

#endif	/* _PROTO_RECTANGLE_H */

