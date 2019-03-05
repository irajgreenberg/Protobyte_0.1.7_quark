//
//  Abacus.h
//  ProtoLib
//
//  Created by Ira Greenberg on 10/21/11.
//  Copyright 2011 SMU. All rights reserved.
//

#ifndef ProtoLib_Abacus_h
#define ProtoLib_Abacus_h

#include "Vector3df.h"
#include "Dimension3d.h"
#include "Toroid.h"
#include "CageFrame.h"
#include "Box.h"
#include "Bone.h"
#include "line3d.h"
#include "OSCObj.h"

//#include <cmath>

class Abacus: public OSCObj {
    
    // overloaded << operator
    friend std::ostream& operator<<(std::ostream& output, const Abacus& abacus);
    
private:
    int rows, cols, layers;
    int beadCount;
    int beadID;
    int detail;
    Toroid* beadDataModel; // memory managed–Do NOT delete from here
    Toroid** beads; // clean up memory
    Vector3df** beadAnchors; // points where wires attach to frame – clean up memory
    int beadAnchorsLen;
    CageFrame* frame; // clean up here
    Dimension3d frameDetail;
    Tuple3d config;
    Box** slats; // clean up memory
    int slatsLen;
    Line3d** wires; // clean up memory
    Bone** bones; // clean up memory
    
    int ampsCount;
    double* amps;
    double* ampsPast;
    
    double beadJitterY, beadJitterX;
    double ampBoost;
    
    float beadScaler;
    
    // init pos of bead locs
    Vector3df* initLocs;
    Dimension3d* initDims; 
    float pluckTheta, wobbleTheta; // for bead movement
    float* initRed;
    float* initGreen;
    float* initBlue;
    
    int wiresLen, bonesLen;
    
    int propagateFrameDelay;
    int propagateFrameCounter;
    bool isPropagateReady;
    bool isAmpsRecordable;
        
    // private methods
    void init();
    void propagate(); // pass pulse through abacus layers
       
public:
    static const int LOW = 0, MEDIUM = 1, HIGH = 2;
    
    Vector3df loc;
    Dimension3d dim;
    
    
    // constructors
    Abacus();
    Abacus(Vector3df loc, Dimension3d dim);
    Abacus(Vector3df loc, Dimension3d dim, int rows = 4, int cols = 4, int layers = 4);
    Abacus(Vector3df loc, Dimension3d dim, Tuple3d config);
    Abacus(Vector3df loc, Dimension3d dim, int rows = 4, int cols = 4, int layers = 4, Dimension3d frameDetail = Dimension3d());
    Abacus(Vector3df loc, Dimension3d dim, Tuple3d config, Dimension3d frameDetail = Dimension3d());
    Abacus(Vector3df loc, Dimension3d dim, Tuple3d config, Dimension3d frameDetail, Toroid* beadDataModel);
    
    // destructor - called when object goes out of scope
    // overrides default implementation
    ~Abacus();
    
    // Copy Constructor: create an object that doesn't exit yet from existing object.
    Abacus(const Abacus& abacus_src);
    
    
    // Assignment Operator: copy object to existing object.
    Abacus& operator= (const Abacus& abacus_src);
   
    void pluck();
    
    void display();
    
    void setAmplitudeByID(int id, float amp);
    
    void setRows(int rows);
    int getRows() const;
    
    void setCols(int cols);
    int getCols() const;
    
    void setDetail(int detail);
    int getDetail() const;
    
    int getBeadcount() const;
    
    Toroid** getBeads() const;
    
    void setFrameDetail(Dimension3d frameDetail);
    Dimension3d getFrameDetail() const;
    
    
    void setAmps(double* amps);
    
    // change bead geom  in real time
    void setBeadDataModel(Dimension3d dim, int detail, int segs, float innerRadius, float outerRadius);
    void setBeadDim(Dimension3d dim);
    
    void setBeadDetail(int detail);
    
    void setBeadSegs(int segs);
    
    void setBeadInnerRadius(float innerRadius);
    void setBeadOuterRadius(float outerRadius);
    
    void setBeadJitterY(double beadJitterY);
    double getBeadJitterY() const;
    
    void setBeadJitterX(double beadJitterX);
    double getBeadJitterX() const;
    
    void setAmpBoost(double ampBoost);
    double getAmpBoost() const;
    
    void setBeadScaler(float beadScaler);
    float getBeadScaler() const;
    
    
};


#endif
