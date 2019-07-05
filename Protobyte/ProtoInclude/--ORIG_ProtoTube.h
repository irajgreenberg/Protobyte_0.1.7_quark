/*! \Class to extrude a polygon cross-section along spline path
 * Uses parallel transport to avoid twists
 * File:   ProtoTube.h
 * Author: Ira Greenberg
 * Created by Ira on 10/17/12.
 */


#ifndef Protobyte_iig001_ProtoTube_h
#define Protobyte_iig001_ProtoTube_h

#include <iostream>
#include "ProtoGeom3.h"
#include "ProtoSpline3.h"
#include "ProtoCilia.h"
#include "ProtoTransformFunction.h"


namespace ijg {

    // forward declare & create namespace safe shortname
    class ProtoTube;
    typedef ProtoTube Tube;
    
    
    class ProtoTube : public ProtoGeom3 {
    public:

		friend class ProtoJuncusEffusus; // sort of crappy, but I'm in a rush. There is an argument for it as well (sort of)
		friend std::ostream& operator<<(std::ostream& out, const ProtoTube& tube);

        /*!
         * Constructor */
        ProtoTube();
        
        /*!
         * Constructor
         */
        ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed = true);
        
        
        /*!
         * Constructor
         * with texture
         */
        ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

        /*!
         * Constructor 
         * with TransformFunction object
         */
        ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed = true);
        
        /*!
         * Constructor
         * with TransformFunction object & texture
         */
		ProtoTube(const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

        /*!
         * Constructor 
         * with TransformFunction object
         */
        ProtoTube(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed = true);

        /*!
         * Constructor 
         * varied thickness*/
        ProtoTube(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed = true);

        /*!
         * Constructor 
         * varied color*/
        ProtoTube(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed = true);

        /*!
         * Constructor 
         * varied color and TransformFunction object*/
        ProtoTube(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed = true);

        /*!
         * Constructor 
         * varied thickness and color */
        ProtoTube(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed = true);
        
        /*!
         * Constructor 
         * All */
        ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed = true);

        /*!
         * Constructor 
         * All with TransformFunction obj*/
        ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed = true);
        
        // NEW
        /*!
         * Constructor
         * All with TransformFunction obj*/
		ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed, const std::string& textureImageURL, const Vec2f& textureScale = Vec2f(1, 1));

        /*!
         * Constructor 
         * All with varied radii*/
        ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed = true);

        /*!
         * Constructor 
         * all with varied color */
        ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed = true);

        /*!
         * Constructor 
         * all with varied color and TransformFunction obj */
        ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed = true);

        /*!
         * Constructor 
         * All with varied thickness and color */
        ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed = true);
        
        
        // added 12/27/13
        ProtoTube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed = true);

        ~ProtoTube();

        /*! overrides base class virtual functions
         */
        virtual void calcVerts();

        /*! overrides base class virtual functions
         */
        void calcInds();


        /*! getters | setters prototypes
         */
        void setFrenetFrameLength(int frenetFrameLength);
        int getFrenetFrameLength() const;
        void setCrossSectionDetail(int crossSectionDetail);
        int getCrossSectionDetail() const;
        void setRadii(std::vector<float> radii);
        std::vector<float> getRadii() const;
        void setRadius(float radius);
        float getRadius() const;
        void setPath(ProtoSpline3 path);
        ProtoSpline3 getPath() const;
        void setIsClosed(bool isClosed);
        bool isIsClosed() const;
        void setTransFuncObj(ProtoTransformFunction transFuncObj);
        ProtoTransformFunction getTransFuncObj() const;
        void setIsTransformFunction(bool isTransformFunction);
        bool getIsTransformFunction() const;
        void setPerturbation(const Vec3f& perturbation);
        Vec3f getPerturbation() const;
        void rotateY();
        const std::vector<ProtoFrenetFrame>& getFrenetFrames() const;

		// maybe
		//std::vector<float>* getInterleavedPrims();

    protected:
        ProtoSpline3 path;
        float radius;
        std::vector<float> radii;
        int crossSectionDetail;
        int frenetFrameLength;
        bool isClosed;
        ProtoTransformFunction transFuncObj;
        bool isTransformFunction;
        Vec3f perturbation;
        std::vector<Vec3f> crossSectionCentroids;

        // spline stuff
        //VerletSpine vSpine;
        // local frames of reference
        std::vector<ProtoFrenetFrame> ff;
    };

    // inline getters | setters

    inline void ProtoTube::setFrenetFrameLength(int frenetFrameLength) {
        this->frenetFrameLength = frenetFrameLength;
    }

    inline int ProtoTube::getFrenetFrameLength() const {
        return frenetFrameLength;
    }

    inline void ProtoTube::setCrossSectionDetail(int crossSectionDetail) {
        this->crossSectionDetail = crossSectionDetail;
    }

    inline int ProtoTube::getCrossSectionDetail() const {
        return crossSectionDetail;
    }

    inline void ProtoTube::setRadii(std::vector<float> radii) {
        this->radii = radii;
    }

    inline std::vector<float> ProtoTube::getRadii() const {
        return radii;
    }

    inline void ProtoTube::setRadius(float radius) {
        this->radius = radius;
    }

    inline float ProtoTube::getRadius() const {
        return radius;
    }

    inline void ProtoTube::setPath(ProtoSpline3 path) {
        this->path = path;
    }

    inline ProtoSpline3 ProtoTube::getPath() const {
        return path;
    }

    inline void ProtoTube::setIsClosed(bool isClosed) {
        this->isClosed = isClosed;
    }

    inline bool ProtoTube::isIsClosed() const {
        return isClosed;
    }

    inline void ProtoTube::setTransFuncObj(ProtoTransformFunction transFuncObj) {
        this->transFuncObj = transFuncObj;
        setIsTransformFunction(true);
    }

    inline ProtoTransformFunction ProtoTube::getTransFuncObj() const {
        return transFuncObj;
    }

    inline void ProtoTube::setIsTransformFunction(bool isTransformFunction) {
        this->isTransformFunction = isTransformFunction;
    }

    inline bool ProtoTube::getIsTransformFunction() const {
        return isTransformFunction;
    }

    inline void ProtoTube::setPerturbation(const Vec3f& perturbation) {
        this->perturbation = perturbation;
        init();
    }

    inline Vec3f ProtoTube::getPerturbation() const {
        return perturbation;
    }

    inline const std::vector<ProtoFrenetFrame>& ProtoTube::getFrenetFrames() const {
        return ff;
    }
}


#endif
