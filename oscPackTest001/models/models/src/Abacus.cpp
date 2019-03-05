//
//  Abacus.cpp
//  ProtoLib
//
//  Created by Ira Greenberg on 10/21/11.
//  Copyright 2011 SMU. All rights reserved.
//

#include <iostream>
#include "Abacus.h"

static int counter55 = 0;
std::ostream& operator<<(std::ostream& output, const Abacus& abacus) {
    output << "(abacus.loc = " <<  abacus.loc.x << ", " << abacus.loc.y <<", " << abacus.loc.z <<")\n" <<
    "(abacus.dim = " <<  abacus.dim.w << ", " << abacus.dim.h <<", " << abacus.dim.d <<")";
    return output;
    
    
}



Abacus::Abacus():
loc(Vector3df()), dim(Dimension3d()), config(Tuple3d(4, 4, 4)), frameDetail(Dimension3d(.03, .03, .03)) {
}

Abacus::Abacus(Vector3df loc, Dimension3d dim):
loc(loc), dim(dim), config(Tuple3d(4, 4, 4)), frameDetail(Dimension3d(.03, .03, .03)) {
    
}

Abacus::Abacus(Vector3df loc, Dimension3d dim, int rows, int cols, int layers):
loc(loc), dim(dim), rows(rows), cols(cols), layers(layers), frameDetail(Dimension3d(.03, .03, .03)) {
    init();
}

Abacus::Abacus(Vector3df loc, Dimension3d dim, int rows, int cols, int layers, Dimension3d frameDetail):
loc(loc), dim(dim), rows(rows), cols(cols), layers(layers), frameDetail(frameDetail) {
    init();
}

Abacus::Abacus(Vector3df loc, Dimension3d dim, Tuple3d config): 
loc(loc), dim(dim), config(config), frameDetail(Dimension3d(.03, .03, .03)) {
    init();
}

Abacus::Abacus(Vector3df loc, Dimension3d dim, Tuple3d config, Dimension3d frameDetail):
loc(loc), dim(dim), config(config), frameDetail(frameDetail) {
    init();
}

Abacus::Abacus(Vector3df loc, Dimension3d dim, Tuple3d config, Dimension3d frameDetail, Toroid* beadDataModel):
loc(loc), dim(dim), config(config), rows(config.elem0), cols(config.elem1), layers(config.elem2), frameDetail(frameDetail), beadDataModel(beadDataModel) {
    init();
}

// destructor - called when object goes out of scope
// overrides default implementation
Abacus::~Abacus() {
    
    delete frame;
    
    // clean up Toroids array
    for(int i=0; i<beadCount; i++){
        delete beads[i];
    }
    delete [] beads;
    
    // clean up slats
    for(int i=0; i<cols; i++){
        delete  slats[i];
    }
    delete [] slats;
    
    delete [] initLocs;
    delete [] initDims;
    
    delete [] initRed;
    delete [] initGreen;
    delete [] initBlue;
    
    // clean up wires
    for(int i=0; i<wiresLen; i++){
        delete  wires[i];
    }
    delete [] wires;
    
    // clean up bead anchors that attach to frame
    for(int i=0; i<beadAnchorsLen; i++){
        delete  beadAnchors[i];
    }
    delete [] beadAnchors;
    
    delete [] ampsPast;
}



// Copy Constructor: create an object that doesn't exit yet from existing object.
/* finish building
 Abacus::Abacus(const Abacus& abacus_src){
 rows = abacus_src.rows;
 cols = abacus_src.cols;
 detail = abacus_src.detail;
 Toroid** beads = new Toroid*[rows*cols];
 
 
 }
 */


// Assignment Operator: copy object to existing object.
/* finish building
 Abacus::Abacus& operator= (const Abacus& abacus_src) {
 rows = abacus_src.rows;
 cols = abacus_src.cols;
 detail = abacus_src.detail;
 Toroid** beads = new Toroid*[rows*cols];
 }
 */

void Abacus::init() {    
    float rowGap = dim.h/(rows-1);
    float colGap = dim.w/(cols-1);
    float layerGap = dim.d/(layers-1);
    beadCount = rows*cols*layers;
    beads = new Toroid*[beadCount];
    beadAnchorsLen = cols*layers*2;
    beadAnchors = new Vector3df*[beadAnchorsLen];
    slatsLen = cols*2;
    slats = new Box*[slatsLen];
    wiresLen = cols*layers * (rows+1);
    wires = new Line3d*[wiresLen];
    bonesLen = cols*(rows+1)*layers;
    bones = new Bone*[bonesLen];
    ampsCount = rows*cols;
    amps = new double[rows*cols];
    ampsPast = new double[rows*cols];
    
    // init bead locations
    initLocs = new Vector3df[beadCount];
    initDims = new Dimension3d[beadCount];
    
    initRed = new float[beadCount];
    initGreen = new float[beadCount];
    initBlue = new float[beadCount];
    
    
    Dimension3d frameDim(dim.w*1.2,dim.h*1.2,dim.d*1.2); 
    frame = new CageFrame(loc, frameDim, frameDetail);
    
    // frames to delay amplitude propagation
    isPropagateReady = false;
    propagateFrameDelay = 15;
    propagateFrameCounter = 0;
    isAmpsRecordable = true; // initial recording
    
    ampBoost = 5.75;
    beadJitterX = .01;
    beadJitterY = .85;
    
    beadScaler = 5.0;
    
    // place beads in 3D abacus
    int l = 0;
    int wireCounter = 0;
    for(int i=0; i<layers; i++){
        for(int j=0; j<cols; j++){
            for(int k=0; k<rows; k++){
                //Toroid::Toroid(Vector3df loc, Dimension3d dim, int detail, int segs, float innerRadius, float outerRadius):
                if (beadDataModel != NULL){
                    beads[l] = new Toroid(Vector3df(-dim.w/2+colGap*j, -dim.h/2 +rowGap*k, dim.d/2-layerGap*i), beadDataModel->dim, 
                                          beadDataModel->getDetail(), beadDataModel->getSegs(), beadDataModel->getInnerRadius(), beadDataModel->getOuterRadius());
                } else {
                    // add default state
                    beads[l] = new Toroid(Vector3df(-dim.w/2+colGap*j, -dim.h/2 +rowGap*k, dim.d/2-layerGap*i), Dimension3d(.15, .17, .15), 20, 20, .1, .3);
                }
                beads[l]->setSpd(Vector3df());
                beads[l]->setAmp(0.0);
                beads[l]->setDrag(.97);
                beads[l]->setFreq(2);
                beads[l]->setColor(.5, .5, .7);
                
                
                // capture initial bead locations
                initLocs[l] = beads[l]->loc;
                initDims[l] = beads[l]->dim;
                initRed[l] = beads[l]->getRed();
                initGreen[l] = beads[l]->getGreen();
                initBlue[l] = beads[l]->getBlue();
                
                l++;
            }
        }
    }
    //std::cout << "rowGap = " << rowGap << std::endl;
    
    // wires between beads
    l=0;
    int beadAnchorCounter = 0;
    for(int i=0; i<layers; i++){
        for(int j=0; j<cols; j++){
            for(int k=0; k<rows; k++){                            
                // do top row attached to frame
                if (k==0){
                    beadAnchors[beadAnchorCounter] = new Vector3df (beads[l]->loc.x, -frameDim.h/2, beads[l]->loc.z);
                    wires[wireCounter++] = new Line3d(beadAnchors[beadAnchorCounter], &beads[l]->loc);
                    beadAnchorCounter++;
                }
                if (k<rows-1){
                    wires[wireCounter++] = new Line3d(&beads[l]->loc,  &beads[l + 1]->loc);
                } else {
                    //Vector3df v(beads[l]->loc.x, -frameDim.h/2, beads[l]->loc.z);
                    beadAnchors[beadAnchorCounter] = new Vector3df (beads[l]->loc.x, frameDim.h/2, beads[l]->loc.z);
                    wires[wireCounter++] = new Line3d(&beads[l]->loc, beadAnchors[beadAnchorCounter]);
                    beadAnchorCounter++;
                }
                
                l++;
            }
        }
    }
    
    //std::cout << "wireCounter = " << wireCounter << std::endl;
    //std::cout << "wiresLen = " << wiresLen << std::endl;
    
    
    
    // create slats to hold abacus strings;
    for(int i=0, j=0; i<slatsLen; i++){
        if (i<cols){
            slats[i] = new Box(Vector3df(-dim.w/2+colGap*i, frameDim.h/2, 0), Dimension3d(.03, .03, frameDim.d));
        } else {
            slats[i] = new Box(Vector3df(-dim.w/2+colGap*j++, -frameDim.h/2, 0), Dimension3d(.03, .03, frameDim.d));
        }
    }
    
    pluckTheta = wobbleTheta = 0.0; // for bead movement
    
}

void Abacus::display() {
    
    // run instrument physics
    pluck();
    
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    
    // draw beads
    for(int i=0; i<beadCount; i++){
        glPushMatrix();
        glTranslatef(beads[i]->loc.x, beads[i]->loc.y, beads[i]->loc.z);
        glScalef(beads[i]->dim.w, beads[i]->dim.h, beads[i]->dim.d);
        glColor3f(beads[i]->getRed(), beads[i]->getGreen(), beads[i]->getBlue());
        beads[i]->display();
        glPopMatrix();
    }
    
    // draw external frame
    glColor3f(.7, .6, .6);
    frame->display();
    
    // draw cross supports
    for(int i=0; i<slatsLen; i++){
        glPushMatrix();
        glTranslatef(slats[i]->loc.x, slats[i]->loc.y, slats[i]->loc.z);
        glScalef(slats[i]->dim.w, slats[i]->dim.h, slats[i]->dim.d);
        slats[i]->display();
        glPopMatrix();
    }
    
    // draw bead wires
    for(int i=0; i<wiresLen; i++){
        glColor3f(1.0, 1.0, 1.0);
        wires[i]->display();
    }
    glPopMatrix();
    
    //propagate();
}


// Move individual beads  on layer 1 only
// based on amplitude data
void Abacus::pluck() {
    // currenlty only targets 1st layer
    // other layers get ampltude data through
    // propagation method.
    for(int i=0; i<beadCount; i++){
        
        // record amps data for eventual propagation
        if (isAmpsRecordable &&  i<ampsCount){
          // ampsPast[i] = beads[i]->getAmp()*1.75;
        }
        //beads[i]->loc.z = initLocs[i].z + cos(pluckTheta)*beads[i]->getAmp()*1.75; // wave
        beads[i]->loc.z = initLocs[i].z + beads[i%81]->getAmp()*ampBoost; // single vector force
        //std::cout<< "beads[i]->getAmp() = " << beads[i]->getAmp() << std::endl;
        beads[i]->loc.x = initLocs[i].x + cos(wobbleTheta)*beads[i%81]->getAmp()*beadJitterX;
        beads[i]->loc.y = initLocs[i].y + sin(wobbleTheta)*beads[i%81]->getAmp()*beadJitterY;
        
        float pulse = beads[i%81]->getAmp()*beadScaler;
        beads[i]->dim.w = initDims[i%81].w + pulse;
        beads[i]->dim.h = initDims[i%81].h + pulse;
        beads[i]->dim.d = initDims[i%81].d + pulse;
        //beads[i]->setColor(initRed[i] + (beads[i]->getAmp()*5.75)*120, initGreen[i], initBlue[i]); // layer 1
        beads[i]->setColor(initRed[i] + beads[i%81]->getAmp()*getRand(5), initGreen[i]+ beads[i%81]->getAmp()*getRand(5), initBlue[i] + beads[i%81]->getAmp()*getRand(5)); // layer 2
        
        // slow down phyics
       beads[i]->dampen();
    }
    pluckTheta += PI/45.0;
    wobbleTheta += PI/2;
    
    isAmpsRecordable = false;
    
    
}



// + DON'T THINK I NEED THIS ANYMORE +
// Constantly streaming from drawing loop in main
// via OSC connection to MAX
void Abacus::setAmplitudeByID(int id, float amp){
    //std::cout<< "id = " << id << std::endl;
    //std::cout<< "amp = " << amp << std::endl;
    
    // NOTE: Values below are hard coded 
    // for Syzergy performance 11/22/11
    // ampsCount = rows * cols 
    // (81) unique frequencies
    // 1 if on, -1 if off
    if (id > -1 && id < ampsCount){
        std::cout << "id = " << id <<  ", amp = " << amp << std::endl;
        
        beads[id]->setAmp(amp);
        pluck();
       // beads[id]->loc.z = initLocs[id].z + amp*1.75; 
    }
}

void Abacus::propagate(){
    if (isPropagateReady){
        for(int i=0; i<ampsCount; i++){
            beads[(ampsCount) + i]->setAmp(ampsPast[i]); // do propagation here
        }
        isPropagateReady = false; // reset to false
    }
    if (propagateFrameCounter++ == propagateFrameDelay){
        isPropagateReady = true;
        isAmpsRecordable = true;
        propagateFrameCounter = 0;
    }
}


void Abacus::setRows(int rows) {
    this->rows = rows;
}

int Abacus::getRows() const {
    return rows;
}

void Abacus::setCols(int cols){
    this->cols = cols;
    
}

int Abacus::getCols() const {
    return cols;
}


int Abacus::getBeadcount() const {
    return beadCount;
}


void Abacus::setDetail(int detail){
    this->detail = detail;
}

int Abacus::getDetail() const {
    return detail;
}

Toroid** Abacus::getBeads() const {
    return beads;
}

void Abacus::setFrameDetail(Dimension3d frameDetail){
    this->frameDetail = frameDetail;
}

Dimension3d Abacus::getFrameDetail() const {
    return frameDetail;
}

void Abacus::setAmps(double* amps){
    this->amps = amps;
}

void Abacus::setBeadDataModel(Dimension3d dim, int detail, int segs, float innerRadius, float outerRadius) {
    beadDataModel->setDim(dim);
    beadDataModel->setDetail(detail);
    beadDataModel->setSegs(segs);
    beadDataModel->setInnerRadius(innerRadius);
    beadDataModel->setOuterRadius(outerRadius);
    
}

void Abacus::setBeadDim(Dimension3d dim) {
    beadDataModel->setDim(dim);
    for (int i=0; i<beadCount; i++){
        initDims[i] = dim;
    }
}
void Abacus::setBeadDetail(int detail) {
    beadDataModel->setDetail(detail);
    for (int i=0; i<beadCount; i++){
        beads[i]->setDetail(detail);
    }
}

void Abacus::setBeadSegs(int segs) {
    beadDataModel->setSegs(segs);
    for (int i=0; i<beadCount; i++){
        beads[i]->setSegs(segs);
    }
}
void Abacus::setBeadInnerRadius(float innerRadius) {
    beadDataModel->setInnerRadius(innerRadius);
    for (int i=0; i<beadCount; i++){
        beads[i]->setInnerRadius(innerRadius);
    }
}
void Abacus::setBeadOuterRadius(float outerRadius) {
    beadDataModel->setOuterRadius(outerRadius);
    for (int i=0; i<beadCount; i++){
       beads[i]->setOuterRadius(outerRadius);
    }
}

void Abacus::setBeadJitterY(double beadJitterY) {
    this->beadJitterY = beadJitterY;
}

void Abacus::setBeadJitterX(double beadJitterX) {
    this->beadJitterX = beadJitterX;
}

void Abacus::setAmpBoost(double ampBoost) {
    this->ampBoost = ampBoost;
}

double Abacus::getBeadJitterY() const{
    return beadJitterY;
}

double Abacus::getBeadJitterX() const{
    return beadJitterX;
}

double Abacus::getAmpBoost() const {
    return ampBoost;
}

void Abacus::setBeadScaler(float beadScaler){
    this->beadScaler = beadScaler;
}

float Abacus::getBeadScaler() const{
    return beadScaler;
}

