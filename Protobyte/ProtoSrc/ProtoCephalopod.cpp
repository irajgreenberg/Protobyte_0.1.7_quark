/*!  \brief  ProtoCephalopod.cpp: (add brief description)
 ProtoCephalopod.cpp
 Protobyte Library v02
 
 Created by Ira on 12/12/13.
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

#include "ProtoCephalopod.h"

using namespace ijg;


namespace {
    std::vector<ProtoFace3> faces;
    float alpha = .90;
}

// default cstr
ProtoCephalopod::ProtoCephalopod() {
}

// dstr
ProtoCephalopod::~ProtoCephalopod() {
    
}

ProtoCephalopod::ProtoCephalopod(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                                 const ProtoColor4f& col4, int tentacleCount, long lifespan):
ProtoShape3(pos, rot, size, col4), tentacleCount(tentacleCount), lifeSpan(lifespan)
{
    init();
    
}

ProtoCephalopod::ProtoCephalopod(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                                 const ProtoColor4f& col4, int tentacleCount, long lifespan, const std::string& textureImageURL):
ProtoShape3(pos, rot, size, col4), tentacleCount(tentacleCount), lifeSpan(lifespan), textureImageURL(textureImageURL){
    init();
}



void ProtoCephalopod::init(){
    
    respawnCount = 0;
    time_t now = time(0);
    setBirthday(now);
    isSpawnable = true;
    age = 0;
    tentacles.clear();
    tentacleShells.clear();
    //    int coin = int(random(2));;
    //    if(coin == 0){
    //        textureImageURL = "reptile2.jpg";
    //    }
    //    else {
    //        textureImageURL = "vascular.jpg";
    //    }
    body = std::unique_ptr<ProtoGeoSphere>(new ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(4.5, 4.5, 4.5), Col4f(1, .6, .65, .5), 1, textureImageURL));
    body->textureOn();
    
    shell = std::unique_ptr<ProtoGeoSphere>(new ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(4.6, 4.6, 4.6), Col4f(1, .8, .8, .2), 1));
    faces = body->getFaces();
    
    for(size_t i=0; i<faces.size(); ++i){
        //for(size_t i=0; i<8; ++i){
        // 3 post birth
        // 10 for baby
        const int pathCount = 3;
        std::vector<Vec3> vecs;
        float _theta = 0.0;
        float _radius = .2;
        float h = 0;
        for(int j=0; j<pathCount; ++j){
            vecs.push_back(Vec3(sin(_theta)*_radius, h+=.75, cos(_theta)*_radius));
            _theta += PI/9;
            _radius -=.12;
        }
        ProtoSpline3 path(vecs, 4, 0, .5);
        
        float r = random(.5, .8);
        float g = random(.4, .6);
        float b = random(.7, .9);
        float periodCount = random(15, 30);
        float waveDirection = random(4);
        std::unique_ptr<ProtoTentacle> tentacle(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(r, g, b, .95f), path, 1.6, 8, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(.02, getMin(getAge()*.05, 1.9)), periodCount), respawnCount, false, textureImageURL));
        std::unique_ptr<ProtoTentacle> tentacleShell(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(r, g, b, .95f), path, 1.6, 8, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(.01, getMin(getAge()*.05, .1)), periodCount), respawnCount, false, "reptile2.jpg"));        // ***** VERY UGLY HACK - FIX PLEASE *****
        tentacle->setLifeSpan(lifeSpan);
        tentacleShell->setLifeSpan(lifeSpan);
        tentacle->textureOn();
        tentacle->setWaveDirectionID(static_cast<int>(waveDirection));
        
        tentacleShell->textureOn();
        tentacleShell->setWaveDirectionID(static_cast<int>(waveDirection));
        tentacleShell->setHasCilia(false);
        
        ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4((faces.at(i).getCentroid()*.75f), 1));
        tentacle->transform(mat4);
        tentacleShell->transform(mat4);
        tentacles.push_back(std::move(tentacle));
        tentacleShells.push_back(std::move(tentacleShell));
        
        
        
        
        //        if (i%3==0){
        //        std::unique_ptr<ProtoTentacle> tentacle(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(.6, .6, .65, .9), path, 1.6, 16, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(.95, 1.4), random(15, 30)), false, textureImageURL));
        //            // ***** VERY UGLY HACK - FIX PLEASE *****
        //            tentacle->textureOn();
        //            tentacle->setWaveDirectionID(static_cast<int>(random(4)));
        //
        //            ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4((faces.at(i).getCentroid()*.75f), 1));
        //            tentacle->transform(mat4);
        //            tentacles.push_back(std::move(tentacle));
        //        } else if (i%2==0){
        //            std::unique_ptr<ProtoTentacle> tentacle(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(.3, .3, .3, .8), path, 1.6, 16, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(.01, 1), random(55, 10)), false, textureImageURL));
        //            // ***** VERY UGLY HACK - FIX PLEASE *****
        //            tentacle->textureOn();
        //            tentacle->setWaveDirectionID(static_cast<int>(random(4)));
        //
        //            ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4((faces.at(i).getCentroid()*.75f), 1));
        //            tentacle->transform(mat4);
        //            tentacles.push_back(std::move(tentacle));
        //        } else {
        //        std::unique_ptr<ProtoTentacle> tentacle(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(.6, .7, .63, .9), path, 1.6, 16, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(.05, 1.8), random(15, 30)), false, textureImageURL));
        //            // ***** VERY UGLY HACK - FIX PLEASE *****
        //            tentacle->textureOn();
        //            tentacle->setWaveDirectionID(static_cast<int>(random(4)));
        //
        //            ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4((faces.at(i).getCentroid()*.75f), 1));
        //            tentacle->transform(mat4);
        //            tentacles.push_back(std::move(tentacle));
        //        }
        
        
    }
}

void ProtoCephalopod::reSpawn(){
    respawnCount++;
    tentacles.clear();
    tentacleShells.clear();
    
    float bodySizeMin = .5;
    float bodySizeMax = 4.5;
    float shellSizeMin = .55;
    float shellSizeMax = 4.6;
    
    double bodyShrinkRatio = (bodySizeMax-bodySizeMin)/lifeSpan; // lifeSpan = 26
    double shellShrinkRatio = (shellSizeMax-shellSizeMin)/lifeSpan; // lifeSpan = 26
    
    float bodySz = bodySizeMax - bodyShrinkRatio*respawnCount;
    float ShellSz = shellSizeMax - shellShrinkRatio*respawnCount;
    
    body = std::unique_ptr<ProtoGeoSphere>(new ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(bodySz, bodySz, bodySz), Col4f(1, .6, .65, .5), 1, textureImageURL));
    body->textureOn();
    faces = body->getFaces();
    
    shell = std::unique_ptr<ProtoGeoSphere>(new ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(ShellSz, ShellSz, ShellSz), Col4f(1, .8, .8, .2), 1));
    
    // fade
    if(respawnCount>24){
        alpha -= respawnCount*.01875;
    }
    for(size_t i=0; i<faces.size(); ++i){
        
        float pathCountMin = 3;
        float pathCountMax = 40;
        
        double pathLengthRatio = (pathCountMax-pathCountMin)/lifeSpan;
        int pathCount = pathCountMin+round(pathLengthRatio*respawnCount);
        
        std::vector<Vec3> vecs;
        float _theta = 0.0;
        float _radius = .2;
        float h = 0;
        for(int j=0; j<pathCount; ++j){
            vecs.push_back(Vec3(sin(_theta)*_radius, h+=.75, cos(_theta)*_radius));
            _theta += PI/9;
            _radius -=.12;
        }
        ProtoSpline3 path(vecs, 4, 0, .5);
        
        float r = random(.5, .8);
        float g = random(.4, .6);
        float b = random(.7, .9);
        float periodCount = random(15, 30);
        float waveDirection = random(4);
        
        // vascular3.jpg texture
        float tentacleRadiusMin = .05;
        float tentacleRadiusMax = 1.6;
        float tentacleRadiusRatio = (tentacleRadiusMax-tentacleRadiusMin)/lifeSpan;
        float tentacleRadius = tentacleRadiusMin + tentacleRadiusRatio*respawnCount;
        
        // repile2.jpg texture
        float tentacleShellRadiusMin = .001;
        float tentacleShellRadiusMax = 1.7;
        float tentacleShellRadiusRatio = (tentacleShellRadiusMax-tentacleShellRadiusMin)/lifeSpan;
        float tentacleShellRadius = tentacleRadiusMin + tentacleShellRadiusRatio*respawnCount;
        
        // clear creature at end of life
        if(respawnCount == lifeSpan){
            tentacleRadiusMin = tentacleRadius = tentacleShellRadiusMin = tentacleShellRadius = 0;
        }
        
        // trace("thickness = ", thickness);
        
        
        std::unique_ptr<ProtoTentacle> tentacle(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(r, g, b, alpha), path, 1.6, 8, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(tentacleRadiusMin, tentacleRadius), periodCount), respawnCount, false, textureImageURL));
        std::unique_ptr<ProtoTentacle> tentacleShell(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(r, g, b, alpha), path, 1.6, 8, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(tentacleShellRadiusMin, tentacleShellRadius), periodCount), respawnCount, false, "reptile2.jpg"));
        
        // ***** VERY UGLY HACK - FIX PLEASE *****
        tentacle->setLifeSpan(lifeSpan);
        tentacleShell->setLifeSpan(lifeSpan);
        
        tentacle->textureOn();
        tentacle->setWaveDirectionID(static_cast<int>(waveDirection));
        tentacleShell->textureOn();
        tentacleShell->setWaveDirectionID(static_cast<int>(waveDirection));
        tentacleShell->setHasCilia(false);
        
        ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4((faces.at(i).getCentroid()*.75f), 1));
        tentacle->transform(mat4);
        tentacleShell->transform(mat4);
        tentacles.push_back(std::move(tentacle));
        tentacleShells.push_back(std::move(tentacleShell));
        
        isSpawnable = true;
    }
}


void ProtoCephalopod::display(){
    
    //glShadeModel(GL_FLAT);
    
    body->display(SURFACE);
    shell->display(WIREFRAME);
    glShadeModel(GL_SMOOTH);
    
    for(size_t i=0; i<faces.size(); ++i){
        tentacles.at(i)->wave();
        tentacles.at(i)->display(SURFACE);
        
        if (respawnCount > 15){
            tentacleShells.at(i)->wave();
            tentacleShells.at(i)->display(SURFACE);
        }
    }
    
}
