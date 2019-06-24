/*!  \brief  ProtoSpline3.h: Catmull-Rom spline class implementation
 Credit: https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
 ProtoSpline3.h
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

#ifndef PROTO_SPLINE3_H
#define PROTO_SPLINE3_H

#include "ProtoCurve3.h"

/**
 * Spline cubic curve class, where curve goes through all points. Curve is
 * specified by 6 points, with a smoothness value specifying tension.
 * <p>
 */

namespace ijg {
    
    // forward declare & create namespace safe shortname
    class ProtoSpline3;
    typedef ProtoSpline3 Spline3;
	typedef ProtoSpline3 Spline;
    
    class ProtoSpline3 : public ProtoCurve3 {
    public:

		/**
		 * Utility for controlling spline alpha setting
		 * 0.0-1.0 (Centripetal, Uniform Chordal)
		 */
		enum SplineType {
			UNIFORM,
			CENTRIPETAL,
			CHORDAL
		};
		
		ProtoSpline3();

		ProtoSpline3(const std::vector<Vec3f>& controlPts, int interpolatedPtCount, 
			bool isCurveClosed, SplineType type = CENTRIPETAL);

        /**
         * Draw the curve.
         */
		void display(float strokeWeight = 1, 
			Col4 strokeCol = { 0.0f, 0.0f, 0.0f, 1.0f });

        /**
         * Draw the control points.
         */
        void displayControlPts(float pointSize = 10, 
			Col4 strokeCol = { 1.0f, 0.0f, 0.0f, 1.0f });

        /**
         * Draw the interpolated points.
         */
        void displayInterpolatedPts(float pointSize = 2,
			Col4 strokeCol = { 0.0f, 0.0f, 1.0f, 1.0f });

        /**
         * Draw the Frenet Frames.
         */
        void displayFrenetFrames(float length = 25, float strokeWeight = 4,
			Col4f TCol = { 1.0f, 0.0f, 0.0f, 1.0f },
			Col4f NCol = { 0.0f, 0.0f, 1.0f, 1.0f },
			Col4f BCol = { 0.0f, 1.0f, 0.0f, 1.0f });

		/**
		* Draw cross-section extruded along the spline path.
		* Default cross-section is an ellipse
		*/
		void drawCrossSections(); // temp

		/**
		* sets flag for terminals included
		*
		*/
		void setAreTerminalPtsIncluded(bool areTerminalPtsIncluded=1);

		/**
		* gets flag for curve closed
		*
		*/
		bool getAreTerminalPtsIncluded() const;


    private:

		
		SplineType type;
		
		/**
		* Controls Uniform, Centripetal or Chordal
		* Spline implementation.
		* Deafult type: Uniform.
		*/
		float splineAlpha{ 0.0f };
		
		/**
		* Curve flags to control curve terminals.
		* Deafult: Terminal Points included.
		*/
		bool areTerminalPtsIncluded{ 1 };

        /**
         * allocate memory and initialize stuff.
         */
        void init();

		/**
		 * Calculate Frenet Frames along spline.
		 */
		void initFrenetFrames();

		/**
		* allocate memory and initialize stuff.
		*/
		float getT(float t, Vec3f p0, Vec3f p1);

        /**
         * Frenet frame is used to calcuate extrusions
         * along spline path (Tubes & Tendrils baby!).
         * Called automatically by init()
         */
        void parallelTransport();

    };

	/**
	* Inline getter/setter implementations
	*/
	inline void ProtoSpline3::setAreTerminalPtsIncluded(bool areTerminalPtsIncluded) {
		this->areTerminalPtsIncluded = areTerminalPtsIncluded;
		//reset state
		init();
	}

	inline bool ProtoSpline3::getAreTerminalPtsIncluded() const {
		return areTerminalPtsIncluded;
	}

}


#endif // PROTO_SPLINE3_H
