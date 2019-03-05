/*!  \brief  ProtoCilia.h: (add brief description)
 ProtoCilia.h
 Protobyte Library v02
 
 Created by Ira on 12/26/13.
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

#ifndef Protobyte_dev_ProtoCilia_cpp
#define Protobyte_dev_ProtoCilia_cpp

#include <iostream>
#include <memory>
#include "ProtoCore.h"
#include "ProtoColor4.h"
#include "ProtoSpline3.h"
#include "ProtoVerletStick.h"

namespace ijg {
    
    class ProtoCilia;
    typedef ProtoCilia Cilia;
    
    class ProtoCilia {
    
    public:
        
        friend std::ostream& operator<<(std::ostream& out, const ProtoCilia& path);
        
        enum AnchorMode {
            LEFT,
            RIGHT,
            CENTER,
            ENDS,
            RANDOM,
            ALTERNATING,
            ALL,
            NONE
        };
        
        
        ProtoCilia();
        ProtoCilia(float len, int segments, float tension, const Col4f& col, AnchorMode anchorMode=LEFT); // no coords
        ProtoCilia(const Spline3& spine, float len, int segments, float tension, const Col4f& col, AnchorMode anchorMode=LEFT);
        
        
        // setters/getters
        Vec3f getAnchorPt() const;
        void setAnchorPt(int nodeID, const Vec3f& vec);
        void setAnchorPt(const Vec3f& vec);
        void setLen(float len);
        float getLen() const;
        void setSegments(int segments);
        int getSegments() const;
        float getTension(); // get single tension for entire path
        void setTension(float tension); // set single tension for entire path
        float getTension(int node); // get tension for individual node on path
        void setTension(int node, float tension); // set tension for individual node on path
        
        Col4f getColor() const;
        void setColor(const Col4f& col);
        
        
        Tup2 getEdgeTensions(); // tensions at path ends
        void setEdgeTensions(const Tup2& edgeTensions); // tensions at path ends
        std::vector<float>& getTensions(); // get unique tensions along path
        void setTensions(const std::vector<float>& tensions); // set unique tensions along path
        AnchorMode getAnchorMode();
        void setAnchorMode(const AnchorMode& anchorMode);
        
        // Start Verlet Integration
        void run();
        void push(const Vec3& vec);
        
        //update head to moving anchor point
        // latest hack
        //void update(float* x, float* y, float* z);
        
    private:
        
        Spline3 spine;
        
        // new approach
        // let's cilia calculate vertex geom
        std::unique_ptr<Vec3f> anchor_u_ptr;
        Vec3f anchorPt;
        Vec3f* anchorPt_p;
        float len;
        int segments;
        Col4f col;

        float tension; // tension for entire path
        float tensionMin, tensionMax; // tension for entire path
        Tup2 edgeTensions; // tensions at path ends
        std::vector<float> tensions; // all tensions along path
        AnchorMode anchorMode;
        
        std::vector<Vec3f> vecs; // vertices
        std::vector<std::shared_ptr<ProtoVerletBall> > balls;
        std::vector<std::unique_ptr<ProtoVerletStick> > sticks;
        
        void init();
    
    };
    
    inline Vec3f ProtoCilia::getAnchorPt() const{
        return anchorPt;
    }
    
    inline void ProtoCilia::setAnchorPt(int nodeID, const Vec3f& vec){
        *(balls.at(nodeID)->pos_ptr) = vec;
    }
    
    inline void ProtoCilia::setAnchorPt(const Vec3f& vec){
        *(balls.at(0)->pos_ptr) = vec;
    }
    
    inline void ProtoCilia::setLen(float len){
        this->len = len;
    }
    
    inline float ProtoCilia::getLen() const{
        return len;
    }
    
    inline void ProtoCilia::setSegments(int segments){
        this->segments = segments;
    }
    
    inline int ProtoCilia::getSegments() const{
        return segments;
    }
    
    
    // add more useful output to this eventually
    inline std::ostream& operator<<(std::ostream& out, const ProtoCilia& path){
        out << "address@"<< &path;
        return out;
    }
    
    inline float ProtoCilia::getTension(){
        return tension;
    }
    
    inline void ProtoCilia::setTension(float tension){
        this->tension = tension;
    }
    
    inline float ProtoCilia::getTension(int node){
        return tensions.at(node);
    }
    
    inline void ProtoCilia::setTension(int node, float tension){
        tensions.at(node) = tension;
    }
    
    inline Tup2 ProtoCilia::getEdgeTensions(){
        return edgeTensions;
    }
    
    inline void ProtoCilia::setEdgeTensions(const Tup2& edgeTensions){
        this->edgeTensions = edgeTensions;
    }
    inline std::vector<float>& ProtoCilia::getTensions(){
        return tensions;
    }
    
    inline void ProtoCilia::setTensions(const std::vector<float>& tensions){
        
    }
    
    inline Col4f ProtoCilia::getColor() const{
        return col;
    }
    inline void ProtoCilia::setColor(const Col4f& col){
        this->col = col;
    }
    
    
    inline ProtoCilia::AnchorMode ProtoCilia::getAnchorMode(){
        return anchorMode;
    }
    inline void ProtoCilia::setAnchorMode(const AnchorMode& anchorMode){
        this->anchorMode = anchorMode;
    }
}

#endif // Protobyte_dev_ProtoCilia_cpp
