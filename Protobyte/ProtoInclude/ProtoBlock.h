/*!  \brief  ProtoBlock.h: 3D block implementation
 ProtoBlock.h
 Protobyte Library v02
 
 Created by Ira on 4/06/13.
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

#ifndef ProtoBLOCK_H
#define	ProtoBLOCK_H

#include <iostream>
#include "ProtoGeom3.h"

namespace ijg {

	// forward declare & create namespace safe shortname
	class ProtoBlock;
	typedef ProtoBlock Block;


    class ProtoBlock : public ProtoGeom3 {
    public:
        friend std::ostream& operator<<(std::ostream& out, const ProtoBlock& block);


		enum Registration {
			CENTER,
			TOP,
			BOTTOM,
			RIGHT,
			LEFT,
			FRONT,
			BACK
		};

        /*!
         * Default Constructor */
        ProtoBlock();
        /*!
         * Constructor */
        ProtoBlock(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                const ProtoColor4<float>& col4);
        /*!
         * Constructor */
        ProtoBlock(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const ProtoColor4<float>& col4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1,1));

		/*!
		* Constructor */
		ProtoBlock(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<Col4f>& cols4);
		/*!
		* Constructor */
		ProtoBlock(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const std::vector<Col4f>& cols4, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

		void setRegistration(Registration reg);

	private:

		Registration reg{ CENTER };

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
      

    };
}

#endif	/* ProtoBLOCK_H */

