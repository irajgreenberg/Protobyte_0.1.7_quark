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

#include "ProtoTentacle.h"


namespace ijg {
    
    
    std::ostream& operator<<(std::ostream& out, const ProtoTentacle& tentacle) {
        out << "\n\tpos = " << tentacle.pos << "\n" << ""
        "\trot = " << tentacle.rot << "\n" <<
        "\tsize = " << tentacle.size << "\n" <<
        "\tcol4 = " << tentacle.col4 << "\n" <<
        "\tradius = " << tentacle.radius << "\n" <<
        "\tcrossSectionDetail = " << tentacle.crossSectionDetail << "\n" <<
        "\tisClosed = " << tentacle.isClosed << "\n" <<
        "\tfrenetFrameLength = " << tentacle.frenetFrameLength << "\n" <<
        "\tspd = " << tentacle.spd << "\n" <<
        "\trotSpd = " << tentacle.rotSpd << "\n" <<
        "\tisTransformFunction = " << tentacle.isTransformFunction;
        
        return out;
    }
}

using namespace ijg;



// this is nasty fix eventually
namespace {
    
    float waveTheta = 0;
    float waveRadius = 1.85;
    
    
    std::vector<float> waveRadiusVals;
    std::vector<float> waveThetas;
    std::vector<float> waveFreqs;
    
}

// default cstr

ProtoTentacle::ProtoTentacle() {
    std::cout << "ProtoTentacle CSTR default" << std::endl;
}

// overloaded cstr 1
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radius, crossSectionDetail, isClosed), age(age) {
    init();
}

/*!
 * Constructor 02
 * with TransformFunction object*/
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radius, crossSectionDetail, transFuncObj, isClosed), age(age) {
    init();
}

// Constructor 03 (calls Tube cstr 14)
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radii, crossSectionDetail, transFuncObj, isClosed), age(age) {
    init();
}

/*!
 * Constructor 04
 * varied thickness*/
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, long age, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radii, crossSectionDetail, isClosed), age(age) {
    init();
}

/*!
 * Constructor 05
 * varied color*/
ProtoTentacle::ProtoTentacle(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s, path, radius, crossSectionDetail, isClosed), age(age) {
    init();
}

/*!
 * Constructor 06
 * varied color and TransformFunction object*/
ProtoTentacle::ProtoTentacle(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s, path, radius, crossSectionDetail, transFuncObj, isClosed), age(age) {
    init();
}

/*!
 * Constructor 07
 * varied thickness and color */
ProtoTentacle::ProtoTentacle(const std::vector< ProtoColor4f >& col4s, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, long age, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s, path, radii, crossSectionDetail, isClosed), age(age)  {
    init();
}

/*!
 * Constructor 08
 * All */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed) :
Tube(pos, rot, size, col4, path, radius, crossSectionDetail, isClosed), age(age) {
    init();
}

/*!
 * Constructor 09
 * varied thickness */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, long age, bool isClosed) : // varied thickness
Tube(pos, rot, size, col4, path, radii, crossSectionDetail, isClosed), age(age) {
    init();
}

/*!
 * Constructor 10
 * varied color */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
                             const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, long age, bool isClosed) : // varied color
Tube(pos, rot, size, col4s, path, radius, crossSectionDetail, isClosed), age(age) {
    init();
}

/*!
 * Constructor 11
 * varied thickness and color */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
                             const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, std::vector<float>& radii,
                             int crossSectionDetail, long age, bool isClosed) : // varied thickness & color
Tube(pos, rot, size, col4s, path, radii, crossSectionDetail, isClosed), age(age) {
    init();
}

/*!
 * Constructor 12
 * All with TransformFunction obj*/
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed) : Tube(pos, rot, size, col4, path, radius, crossSectionDetail, transFuncObj, isClosed), age(age) {
    init();
}

/*!
 * Constructor 13
 * all with varied color and TransformFunction obj */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed) : Tube(pos, rot, size, col4s, path, radius, crossSectionDetail, transFuncObj, isClosed), age(age)      {
    init();
    
}

// 12 b image
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed, const std::string& textureImageURL): Tube(pos, rot, size, col4s, path, radius, crossSectionDetail, transFuncObj, isClosed), age(age), textureImageURL(textureImageURL) {
    init();
}


ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, long age, bool isClosed, const std::string& textureImageURL): Tube(pos, rot, size, col4, path, radius, crossSectionDetail, transFuncObj, isClosed, textureImageURL), age(age), textureImageURL(textureImageURL)
{
    init();
}


ProtoTentacle::~ProtoTentacle() {
    //std::cout << "in ProtoTentacle destructor" << std::endl;
}



void ProtoTentacle::init(){
    setHasCilia(true);
    //trace("In ProtoTentacle::init()");
    // set defaults
    setWaveSpeed();
    setWaveFrequency();
    
    // calculate internal verlet spine
    // get Tube internal Spline3 path
    spine = getPath();
    //balls.clear();
    
    float freqMax = random(900, 1500);
    float radiusMax = random(.05, .112);
    //trace("radiusMax = ", radiusMax);
    //radiusMax = .1;
    //    float freqMax = 900;
    //    float radiusMax = .4;
    
    waveRadiusVals.clear();
    waveFreqs.clear();
    waveThetas.clear();
    
    
    for(size_t i=0; i<spine.getVerts().size(); ++i){
        //balls.push_back(std::shared_ptr<VerletBall>(new VerletBall(&spine.getVerts().at(i))));
        
        waveRadiusVals.push_back(i*radiusMax); // HACK --fix
        waveFreqs.push_back(PI/freqMax/*random(PI/1440.0, PI/360.0)*/); // HACK --fix
        waveThetas.push_back(0); // HACK --fix
    }
    //sticks.clear();
    //    for(size_t i=1; i<balls.size(); ++i){
    //        if(i==1){
    //            sticks.push_back(std::unique_ptr<VerletStick> (new VerletStick(balls.at(i-1), balls.at(i), .876, Tup2f(0, .5))));
    //        } else {
    //            sticks.push_back(std::unique_ptr<VerletStick> (new VerletStick(balls.at(i-1), balls.at(i), .876, Tup2f(.5, .5))));
    //        }
    //        waveTheta = 0;
    ////    }
    
    //    for(size_t i=0; i<getVertices().size(); ++i){
    //        if(i%(1+static_cast<int>(random(22)))==0){
    //           // cilia.push_back(std::unique_ptr<Cilia>(new Cilia(20.0, 7, .9)));
    //        }
    //    }
    
    // trace(" age = " , getAge());
    
}

// transform VBO primitives using glBufferSubData
// Must be called (perhaps)
void ProtoTentacle::transform(const ProtoMatrix4f& mat4){
    cilia.clear();
    ciliaNodeIDs.clear(); // not used I believe
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
   
    
    float ciliaDensityMinMin = 6;
    float ciliaDensityMinMax = 12;//12;
    float ciliaDensityMaxMin = 26;
    float ciliaDensityMaxMax = 36;//48;
    
//    trace("lifeSpan = " , lifeSpan);
//    trace("age = " , age);
    
    float ciliaDensityMinRatio = (ciliaDensityMinMax-ciliaDensityMinMin)/lifeSpan;
    float ciliaDensityMaxRatio = (ciliaDensityMaxMax-ciliaDensityMaxMin)/lifeSpan;
    
    float ciliaLengthMin = -50;
    float ciliaLengthMax = 22;
    float ciliaLengthRatio = (ciliaLengthMax-ciliaLengthMin)/lifeSpan;
    
    int _min = ciliaDensityMinMin + ciliaDensityMinRatio*age;
    int _max = ciliaDensityMaxMin + ciliaDensityMaxRatio*age;
    
    
    for (int i = 0; i < interleavedPrims.size(); i += 12) {// transform verts
        
        Vec4 v4(interleavedPrims.at(i), interleavedPrims.at(i+1), interleavedPrims.at(i+2), 1);
        Vec3 v3  = mat4*v4;
        
        // corrode form
        if(age>20){
            interleavedPrims.at(i) = v3.x+random(-.005, .005)*age;
            interleavedPrims.at(i+1) = v3.y+random(-.005, .005)*age;
            interleavedPrims.at(i+2) = v3.z+random(-.005, .005)*age;
        } else {
            interleavedPrims.at(i) = v3.x;;
            interleavedPrims.at(i+1) = v3.y;;
            interleavedPrims.at(i+2) = v3.z;;
        }
        
        // NOTE: use updated transformed vals for convenience here
        // eventually just update here OR transform pre calculated vecs (?)
        
        if(i%static_cast<int>(random(_min, _max))==0 && i<interleavedPrims.size()-36){
            ciliaNodeIDs.push_back(i); // record cilia attachment
            //trace("getAge() = ",  getAge());
            float len = getMax(1, ciliaLengthMax - ciliaLengthRatio*age);
            float segs = 6;
            float segStep = len/(segs-1);
            std::vector<Vec3f> vecs;
            for(int j=0; j<segs; ++j){
                vecs.push_back(Vec3f(v3.x+segStep*j, v3.y, v3.z));
            }
            cilia.push_back(std::unique_ptr<Cilia>(new Cilia(Spline3(vecs, 5, false, true), random(2, 30), 4, .999, Col4f(1, random(), random(.65, 1), random(.02, .18)))));
        } else {
            ciliaNodeIDs.push_back(-1); // record no cilia attachment
        }
        
        
        // transform vnorms
        // there's a better way to transform v norms (so fix it eventually!)
        ProtoMatrix4f m = mat4;
        m.transpose();
        Vec4 v4n(interleavedPrims.at(i+3), interleavedPrims.at(i+4), interleavedPrims.at(i+5), 1);
        Vec3 v3n = m*v4n;
        interleavedPrims.at(i+3) = v3n.x;
        interleavedPrims.at(i+4) = v3n.y;
        interleavedPrims.at(i+5) = v3n.z;
        
    }
    int vertsDataSize = sizeof (float) *interleavedPrims.size();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // transform spine
    //std::vector<Vec3> tempVecs = spine.getVerts(); //local copy
    //    for(size_t i=0; i<balls.size(); ++i){
    //        Vec4 tempV(*balls.at(i)->pos_ptr, 1); //local
    //        *balls.at(i)->pos_ptr = mat4*tempV;
    //        balls.at(i)->posOld = *balls.at(i)->pos_ptr; // update
    //    }
    // update spine and verletPath
    //spine.setVerts(tempVecs); //update member field spine with local vecs
    //verletPath = ProtoVerletPath(spine.getVerts(), .9); // shallow copy with trasnformed spine vecs
    
    // update verletPath spine
    //verletPath.setVecs(tempVecs);
    
    //verletPath.push(Vec3(.02, .01, .01));
    
    // move end
    //*balls.at(balls.size()-1)->pos_ptr += Vec3f(4.02, 4.03, 4.04);
    
    vertexDataCopy = interleavedPrims;
}


void ProtoTentacle::wave(){
    
    int spineSegments = interleavedPrims.size()/12/crossSectionDetail;
    int stride = 12;
    int crossSection = crossSectionDetail;
    
    // waving test
    //static float waveTheta = 0;
    //static float waveRadius = 1.85;
    // wave test of tendrils
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    float t = PI / 360.0;
    float x = 0;
    float y = 0;
    float z = 0;
    float ny = 0;
    int cntr = 0;
    
    int xCntr = 0;
    for (int i = 0; i < spineSegments; ++i) {
        for (int j = 0; j < crossSection; ++j) {
            for (int k = 0; k < stride; ++k) {
                if (k==1){
                    x = vertexDataCopy.at(cntr-1);
                    z = vertexDataCopy.at(cntr+1);
                    int index = i*crossSection+j;
                    switch(waveDirectionID){
                            
                        case 0:
                            y = vertexDataCopy.at(cntr) + cos( waveThetas.at(i))*waveRadiusVals.at(i);
                            ny = vertexDataCopy.at(cntr+3) + cos( waveThetas.at(i))*waveRadiusVals.at(i);
                            if (ciliaNodeIDs.at(index) != -1){
                                cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
                            }
                            break;
                        case 1:
                            y = vertexDataCopy.at(cntr) + sin( waveThetas.at(i))*waveRadiusVals.at(i);
                            ny = vertexDataCopy.at(cntr+3) + sin( waveThetas.at(i))*waveRadiusVals.at(i);
                            if (ciliaNodeIDs.at(index) != -1){
                                cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
                            }
                            break;
                        case 2:
                            y = vertexDataCopy.at(cntr) - cos( waveThetas.at(i))*waveRadiusVals.at(i);
                            ny = vertexDataCopy.at(cntr+3) - cos( waveThetas.at(i))*waveRadiusVals.at(i);
                            if (ciliaNodeIDs.at(index) != -1){
                                cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
                            }
                            break;
                        case 3:
                            y = vertexDataCopy.at(cntr) - sin( waveThetas.at(i))*waveRadiusVals.at(i);
                            ny = vertexDataCopy.at(cntr+3) - sin( waveThetas.at(i))*waveRadiusVals.at(i);
                            if (ciliaNodeIDs.at(index) != -1){
                                cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
                            }
                            break;
                    }
                    interleavedPrims.at(cntr) = y;
                    
                }
                
                
                //interleavedPrims.at(cntr+3) = ny;
                
                
                //                if(ciliaNodeIDs.at(cntr) != -1){
                //                    cilia.at(cntr)->setAnchorPt(Vec3f(*ciliaAnchors.at(cntr).x_p, *ciliaAnchors.at(cntr).y_p, *ciliaAnchors.at(cntr).z_p));
                //                }
                
                
                //vnorms
                //ny = vertexDataCopy.at(i + 4) + cos(waveTheta)*waveRadius;
                //interleavedPrims.at(i + 4) = ny;
                cntr++;
            }
        }
        //if(age>20){
          //  waveThetas.at(i) += waveFreqs.at(i)*(.99-age*.01);
       // } else {
            waveThetas.at(i) += waveFreqs.at(i);
        //}
    }
    
    int primsID = interleavedPrims.size()-14;
    int nodeID = interleavedPrims.size()/12/crossSectionDetail/spineSegments - 24;
    
    
    int vertsDataSize = sizeof (float) *interleavedPrims.size();
    // upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // move cilia
    if (getHasCilia()){
        for(size_t i = 0; i<cilia.size(); ++i){
            if (age<lifeSpan){
                cilia.at(i)->run();
            }
            
        }
    }
    
}
