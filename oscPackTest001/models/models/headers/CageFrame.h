//
//  CageFrame.h
//  ProtoLib
//
//  Created by Ira Greenberg on 10/23/11.
//  Copyright 2011 SMU. All rights reserved.
//

#ifndef ProtoLib_CageFrame_h
#define ProtoLib_CageFrame_h

#include "Geom3d.h"


class CageFrame: public Geom3d {
    
private:
    Vector3df pts[8][8];
    //int indexList[72][4];
    Dimension3d frameDetail;
    
    // overriden methods from superclass
    void init();
    void createVertices();
    void createIndices();


public:
    
    CageFrame(Vector3df loc, Dimension3d dim);
    CageFrame(Vector3df loc, Dimension3d dim, Dimension3d frameDetail);
    
    // copy constructor
    //CageFrame(const CageFrame& CageFrame_src);
    
    // overloaded assignemnt operator
   // CageFrame& operator = (const CageFrame& CageFrame_src);
    
    void setFrameDetail(Dimension3d frameDetail);

    Dimension3d getFrameDetail() const;


};


#endif
