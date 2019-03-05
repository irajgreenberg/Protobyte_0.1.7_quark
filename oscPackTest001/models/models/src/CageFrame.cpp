//
//  CageFrame.cpp
//  ProtoLib
//
//  Created by Ira Greenberg on 10/23/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include <iostream>
#include "CageFrame.h"

CageFrame::CageFrame(Vector3df loc, Dimension3d dim):
Geom3d(loc, dim), frameDetail(Dimension3d(.03, .03, .03)) {
    init();
}

CageFrame::CageFrame(Vector3df loc, Dimension3d dim, Dimension3d frameDetail):
Geom3d(loc, dim), frameDetail(frameDetail) {
    init();
}


// copy constructor
/*CageFrame::CageFrame(const CageFrame& CageFrame_src){
}

// overloaded assignemnt operator
CageFrame& CageFrame::operator = (const CageFrame& CageFrame_src){
    return *this;
}*/


void CageFrame::init(){
    vertCount = 64;
    faceCount = 144;
    
    indicesCount = faceCount*3;
    
    allocateMemory();
    createVertices();
    createIndices();
    createFaces();
    createVertexNormals();
    createCoords();
}

void CageFrame::createVertices(){
    float x = -dim.w/2; 
    float y = dim.h/2;
    float z = dim.d/2;
    float railW = frameDetail.w;
    float railH = frameDetail.h;
    float railD = frameDetail.d;
    
    // corner 0
    pts[0][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[0][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[0][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[0][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);
    
    pts[0][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[0][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[0][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[0][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // corner 1
    x = dim.w/2;
    pts[1][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[1][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[1][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[1][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);
    
    pts[1][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[1][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[1][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[1][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // corner 2
    z = -dim.d/2;
    pts[2][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[2][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[2][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[2][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);
    
    pts[2][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[2][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[2][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[2][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // corner 3
    x = -dim.w/2;
    pts[3][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[3][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[3][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[3][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);
    
    pts[3][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[3][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[3][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[3][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // corner 4
    x = -dim.w/2;
    y = -dim.h/2;
    z = dim.d/2;
    pts[4][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[4][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[4][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[4][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);
    
    pts[4][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[4][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[4][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[4][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // corner 5;
    z = -dim.d/2;
    pts[5][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[5][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[5][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[5][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);
    
    pts[5][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[5][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[5][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[5][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // corner 6;
    x = dim.w/2;
    z = -dim.d/2;
    pts[6][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[6][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[6][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[6][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);  
    
    pts[6][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[6][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[6][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[6][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // corner 6;
    z = dim.d/2;
    pts[7][0] = Vector3df(x-railW/2, y+railH/2, z+railD/2);
    pts[7][1] = Vector3df(x+railW/2, y+railH/2, z+railD/2);
    pts[7][2] = Vector3df(x+railW/2, y+railH/2, z-railD/2);
    pts[7][3] = Vector3df(x-railW/2, y+railH/2, z-railD/2);
    
    pts[7][4] = Vector3df(x-railW/2, y-railH/2, z+railD/2);
    pts[7][5] = Vector3df(x-railW/2, y-railH/2, z-railD/2);
    pts[7][6] = Vector3df(x+railW/2, y-railH/2, z-railD/2);
    pts[7][7] = Vector3df(x+railW/2, y-railH/2, z+railD/2);
    
    // pack verts
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            verts[i*8 + j] = pts[i][j];
        }
    }

}

void CageFrame::createIndices(){
    
    /***************************************
              outer frame bars
    ***************************************/
    
    // left front vertical 
    inds.push_back(Tuple3d(4, 0+8*4, 1+8*4));
    inds.push_back(Tuple3d(4, 1+8*4, 7));
    inds.push_back(Tuple3d(7, 1+8*4, 2+8*4));
    inds.push_back(Tuple3d(7, 2+8*4, 6));
    inds.push_back(Tuple3d(6, 2+8*4, 3+8*4));
    inds.push_back(Tuple3d(6, 3+8*4, 5));
    inds.push_back(Tuple3d(5, 3+8*4, 0+8*4));
    inds.push_back(Tuple3d(5, 0+8*4, 4));
    
    // right front vertical 
    inds.push_back(Tuple3d(4+8, 0+8*7, 1+8*7));
    inds.push_back(Tuple3d(4+8, 1+8*7, 7+8));
    inds.push_back(Tuple3d(7+8, 1+8*7, 2+8*7));
    inds.push_back(Tuple3d(7+8, 2+8*7, 6+8));
    inds.push_back(Tuple3d(6+8, 2+8*7, 3+8*7));
    inds.push_back(Tuple3d(6+8, 3+8*7, 5+8));
    inds.push_back(Tuple3d(5+8, 3+8*7, 0+8*7));
    inds.push_back(Tuple3d(5+8, 0+8*7, 4+8));
    
    // right back vertical 
    inds.push_back(Tuple3d(4+8*2, 0+8*6, 1+8*6));
    inds.push_back(Tuple3d(4+8*2, 1+8*6, 7+8*2));
    inds.push_back(Tuple3d(7+8*2, 1+8*6, 2+8*6));
    inds.push_back(Tuple3d(7+8*2, 2+8*6, 6+8*2));
    inds.push_back(Tuple3d(6+8*2, 2+8*6, 3+8*6));
    inds.push_back(Tuple3d(6+8*2, 3+8*6, 5+8*2));
    inds.push_back(Tuple3d(5+8*2, 3+8*6, 0+8*6));
    inds.push_back(Tuple3d(5+8*2, 0+8*6, 4+8*2));
    
    // left back vertical 
    inds.push_back(Tuple3d(4+8*3, 0+8*5, 1+8*5));
    inds.push_back(Tuple3d(4+8*3, 1+8*5, 7+8*3));
    inds.push_back(Tuple3d(7+8*3, 1+8*5, 2+8*5));
    inds.push_back(Tuple3d(7+8*3, 2+8*5, 6+8*3));
    inds.push_back(Tuple3d(6+8*3, 2+8*5, 3+8*5));
    inds.push_back(Tuple3d(6+8*3, 3+8*5, 5+8*3));
    inds.push_back(Tuple3d(5+8*3, 3+8*5, 0+8*5));
    inds.push_back(Tuple3d(5+8*3, 0+8*5, 4+8*3));
    
    // top front horizontal 
    inds.push_back(Tuple3d(1, 7, 4+8));
    inds.push_back(Tuple3d(1, 4+8, 0+8));
    inds.push_back(Tuple3d(7, 6, 5+8));
    inds.push_back(Tuple3d(7, 5+8, 4+8));
    inds.push_back(Tuple3d(6, 2, 3+8));
    inds.push_back(Tuple3d(6, 3+8, 5+8));
    inds.push_back(Tuple3d(1, 0+8, 3+8));
    inds.push_back(Tuple3d(1, 3+8, 2));
    
    // top back horizontal 
    inds.push_back(Tuple3d(1+8*3, 7+8*3, 4+8*2));
    inds.push_back(Tuple3d(1+8*3, 4+8*2, 0+8*2));
    inds.push_back(Tuple3d(7+8*3, 6+8*3, 5+8*2));
    inds.push_back(Tuple3d(7+8*3, 5+8*2, 4+8*2));
    inds.push_back(Tuple3d(6+8*3, 2+8*3, 3+8*2));
    inds.push_back(Tuple3d(6+8*3, 3+8*2, 5+8*2));
    inds.push_back(Tuple3d(1+8*3, 0+8*2, 3+8*2));
    inds.push_back(Tuple3d(1+8*3, 3+8*2, 2+8*3));
    
    // bottom front horizontal 
    inds.push_back(Tuple3d(1+8*4, 7+8*4, 4+8*7));
    inds.push_back(Tuple3d(1+8*4, 4+8*7, 0+8*7));
    inds.push_back(Tuple3d(7+8*4, 6+8*4, 5+8*7));
    inds.push_back(Tuple3d(7+8*4, 5+8*7, 4+8*7));
    inds.push_back(Tuple3d(6+8*4, 2+8*4, 3+8*7));
    inds.push_back(Tuple3d(6+8*4, 3+8*7, 5+8*7));
    inds.push_back(Tuple3d(1+8*4, 0+8*7, 3+8*7));
    inds.push_back(Tuple3d(1+8*4, 3+8*7, 2+8*4));
    
    // bottom back horizontal 
    inds.push_back(Tuple3d(1+8*5, 7+8*5, 4+8*6));
    inds.push_back(Tuple3d(1+8*5, 4+8*6, 0+8*6));
    inds.push_back(Tuple3d(7+8*5, 6+8*5, 5+8*6));
    inds.push_back(Tuple3d(7+8*5, 5+8*6, 4+8*6));
    inds.push_back(Tuple3d(6+8*5, 2+8*5, 3+8*6));
    inds.push_back(Tuple3d(6+8*5, 3+8*6, 5+8*6));
    inds.push_back(Tuple3d(1+8*5, 0+8*6, 3+8*6));
    inds.push_back(Tuple3d(1+8*5, 3+8*6, 2+8*5));
    
    // top left side 
    inds.push_back(Tuple3d(0+8*3, 3+8*0, 2+8*0));
    inds.push_back(Tuple3d(0+8*3, 2+8*0, 1+8*3));
    inds.push_back(Tuple3d(1+8*3, 2+8*0, 6+8*0));
    inds.push_back(Tuple3d(1+8*3, 6+8*0, 7+8*3));
    inds.push_back(Tuple3d(0+8*3, 4+8*3, 5+8*0));
    inds.push_back(Tuple3d(0+8*3, 5+8*0, 3+8*0));
    inds.push_back(Tuple3d(4+8*3, 7+8*3, 6+8*0));
    inds.push_back(Tuple3d(4+8*3, 6+8*0, 5+8*0));
    
    // top right side 
    inds.push_back(Tuple3d(0+8*2, 3+8*1, 2+8*1));
    inds.push_back(Tuple3d(0+8*2, 2+8*1, 1+8*2));
    inds.push_back(Tuple3d(1+8*2, 2+8*1, 6+8*1));
    inds.push_back(Tuple3d(1+8*2, 6+8*1, 7+8*2));
    inds.push_back(Tuple3d(0+8*2, 4+8*2, 5+8*1));
    inds.push_back(Tuple3d(0+8*2, 5+8*1, 3+8*1));
    inds.push_back(Tuple3d(4+8*2, 7+8*2, 6+8*1));
    inds.push_back(Tuple3d(4+8*2, 6+8*1, 5+8*1));
    
    // bottom left side 
    inds.push_back(Tuple3d(0+8*5, 3+8*4, 2+8*4));
    inds.push_back(Tuple3d(0+8*5, 2+8*4, 1+8*5));
    inds.push_back(Tuple3d(1+8*5, 2+8*4, 6+8*4));
    inds.push_back(Tuple3d(1+8*5, 6+8*4, 7+8*5));
    inds.push_back(Tuple3d(0+8*5, 4+8*5, 5+8*4));
    inds.push_back(Tuple3d(0+8*5, 5+8*4, 3+8*4));
    inds.push_back(Tuple3d(4+8*5, 7+8*5, 6+8*4));
    inds.push_back(Tuple3d(4+8*5, 6+8*4, 5+8*4));
    
    // bottom right side 
    inds.push_back(Tuple3d(0+8*6, 3+8*7, 2+8*7));
    inds.push_back(Tuple3d(0+8*6, 2+8*7, 1+8*6));
    inds.push_back(Tuple3d(1+8*6, 2+8*7, 6+8*7));
    inds.push_back(Tuple3d(1+8*6, 6+8*7, 7+8*6));
    inds.push_back(Tuple3d(0+8*6, 4+8*6, 5+8*7));
    inds.push_back(Tuple3d(0+8*6, 5+8*7, 3+8*7));
    inds.push_back(Tuple3d(4+8*6, 7+8*6, 6+8*7));
    inds.push_back(Tuple3d(4+8*6, 6+8*7, 5+8*7));

    /***************************************
                   corners
    ***************************************/
    
    // 0
    inds.push_back(Tuple3d(0+8*0, 1+8*0, 2+8*0));
    inds.push_back(Tuple3d(0+8*0, 2+8*0, 3+8*0));
    inds.push_back(Tuple3d(0+8*0, 3+8*0, 5+8*0));
    inds.push_back(Tuple3d(0+8*0, 5+8*0, 4+8*0));
    inds.push_back(Tuple3d(0+8*0, 4+8*0, 7+8*0));
    inds.push_back(Tuple3d(0+8*0, 7+8*0, 1+8*0));
    
    // 1
    inds.push_back(Tuple3d(0+8*1, 1+8*1, 2+8*1));
    inds.push_back(Tuple3d(0+8*1, 2+8*1, 3+8*1));
    inds.push_back(Tuple3d(1+8*1, 7+8*1, 6+8*1));
    inds.push_back(Tuple3d(1+8*1, 6+8*1, 2+8*1));
    inds.push_back(Tuple3d(0+8*1, 4+8*1, 7+8*1));
    inds.push_back(Tuple3d(0+8*1, 7+8*1, 1+8*1));
    
    // 2
    inds.push_back(Tuple3d(0+8*2, 1+8*2, 2+8*2));
    inds.push_back(Tuple3d(0+8*2, 2+8*2, 3+8*2));
    inds.push_back(Tuple3d(1+8*2, 7+8*2, 6+8*2));
    inds.push_back(Tuple3d(1+8*2, 6+8*2, 2+8*2));
    inds.push_back(Tuple3d(3+8*2, 2+8*2, 6+8*2));
    inds.push_back(Tuple3d(3+8*2, 6+8*2, 5+8*2));
    
    // 3
    inds.push_back(Tuple3d(0+8*3, 1+8*3, 2+8*3));
    inds.push_back(Tuple3d(0+8*3, 2+8*3, 3+8*3));
    inds.push_back(Tuple3d(0+8*3, 3+8*3, 5+8*3));
    inds.push_back(Tuple3d(0+8*3, 5+8*3, 4+8*3));
    inds.push_back(Tuple3d(3+8*3, 2+8*3, 6+8*3));
    inds.push_back(Tuple3d(3+8*3, 6+8*3, 5+8*3));
    
    // 4
    inds.push_back(Tuple3d(5+8*4, 6+8*4, 7+8*4));
    inds.push_back(Tuple3d(5+8*4, 7+8*4, 4+8*4));
    inds.push_back(Tuple3d(0+8*4, 3+8*4, 5+8*4));
    inds.push_back(Tuple3d(0+8*4, 5+8*4, 4+8*4));
    inds.push_back(Tuple3d(0+8*4, 4+8*4, 7+8*4));
    inds.push_back(Tuple3d(0+8*4, 7+8*4, 1+8*4));
    
    // 5
    inds.push_back(Tuple3d(5+8*5, 6+8*5, 7+8*5));
    inds.push_back(Tuple3d(5+8*5, 7+8*5, 4+8*5));
    inds.push_back(Tuple3d(0+8*5, 3+8*5, 5+8*5));
    inds.push_back(Tuple3d(0+8*5, 5+8*5, 4+8*5));
    inds.push_back(Tuple3d(3+8*5, 2+8*5, 6+8*5));
    inds.push_back(Tuple3d(3+8*5, 6+8*5, 5+8*5));
    
    // 6
    inds.push_back(Tuple3d(5+8*6, 6+8*6, 7+8*6));
    inds.push_back(Tuple3d(5+8*6, 7+8*6, 4+8*6));
    inds.push_back(Tuple3d(1+8*6, 7+8*6, 6+8*6));
    inds.push_back(Tuple3d(1+8*6, 6+8*6, 2+8*6));
    inds.push_back(Tuple3d(3+8*6, 2+8*6, 6+8*6));
    inds.push_back(Tuple3d(3+8*6, 6+8*6, 5+8*6));
    
    // 7
    inds.push_back(Tuple3d(5+8*7, 6+8*7, 7+8*7));
    inds.push_back(Tuple3d(5+8*7, 7+8*7, 4+8*7));
    inds.push_back(Tuple3d(1+8*7, 7+8*7, 6+8*7));
    inds.push_back(Tuple3d(1+8*7, 6+8*7, 2+8*7));
    inds.push_back(Tuple3d(0+8*7, 4+8*7, 7+8*7));
    inds.push_back(Tuple3d(0+8*7, 7+8*7, 1+8*7));
}

void CageFrame::setFrameDetail(Dimension3d frameDetail){
    this->frameDetail = frameDetail;
}
Dimension3d CageFrame::getFrameDetail() const {
    return frameDetail;
}

