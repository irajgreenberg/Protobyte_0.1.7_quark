/*!  \brief  ProtoCilia.cpp: (add brief description)
 ProtoCilia.cpp
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

#include "ProtoCilia.h"

using namespace ijg;

ProtoCilia::ProtoCilia(){
}

ProtoCilia::ProtoCilia(float len, int segments, float tension, const Col4f& col, AnchorMode anchorMode):
len(len), segments(segments), tension(tension),  col(col), anchorMode(anchorMode){
}

ProtoCilia::ProtoCilia(const Spline3& spine, float len, int segments, float tension, const Col4f& col, AnchorMode anchorMode):
spine(spine), len(len), segments(segments), tension(tension), col(col), anchorMode(anchorMode)
{
    init();
}



////not properly implemented yet
//ProtoCilia::ProtoCilia(Vec3f* anchorPt, float len, int segments, float tensionMin, float tensionMax, AnchorMode anchorMode):
//anchorPt(anchorPt), len(len), segments(segments), tension(tensionMax), anchorMode(anchorMode)
//{
//    //init();
//}
//
////not properly implemented yet
//ProtoCilia::ProtoCilia(Vec3f* anchorPt, float len, int segments, const Tup2& edgeTensions, AnchorMode anchorMode):
//anchorPt(anchorPt), len(len), segments(segments), tension(edgeTensions.elem1), anchorMode(anchorMode)
//{
//    //init();
//}
//
//
//ProtoCilia::ProtoCilia(float* x, float* y, float* z, float len, int segments, float tension, AnchorMode anchorMode):
//anchor_u_ptr = std::unique_ptr<Vec3f>(ne Vec3f());
//
//}

// NEW START



void ProtoCilia::init(){
    // in case this has been called before clean storage vectors
    balls.clear();
    sticks.clear();
    
    // initial ball (cilia anchor is based on passed attachment pointer
    
    for(int i = 0; i<spine.getVerts().size()-1; ++i){
        //trace("spine.getVerts().at(i) = ", spine.getVerts().at(i));
        balls.push_back(std::shared_ptr<VerletBall>(new VerletBall(&spine.getVerts().at(i))));
        if (i>0) {
            switch(anchorMode){
                    // Modes:: LEFT,RIGHT,CENTER,ENDS,RANDOM,ALTERNATING,ALL,NONE
                case LEFT:
                    if (i==1){
                        sticks.push_back(std::unique_ptr<VerletStick>(new VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5))));
                    } else {
                        sticks.push_back(std::unique_ptr<VerletStick>(new VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(.25, .75))));
                    }
                    break;
                case RIGHT:
                    if (i==vecs.size()-1){
                        //    sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(.5, 0)));
                    } else {
                        //    sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    }
                    break;
                    //                case CENTER:
                    //                    if (i==(vecs.size()-1)/2){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //                    }
                    //                    break;
                    //                case ENDS:
                    //                    if (i==1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else if (i==vecs.size()-1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(.5, 0)));
                    //                    }
                    //                        else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //                    }
                    //                    break;
                    //                case RANDOM:
                    //                    if (i==1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //
                    //                        break;
                    //                    }
                    //                case ALL:
                    //                    if (i==1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //
                    //                        break;
                    //                    }
                default:
                    //   sticks.push_back(std::unique_ptr<VerletStick>(new VerletStick(std::move(balls.at(i-1)), std::move(balls.at(i)), tension)));
                    break;
            }
        }
        
    }
}

void ProtoCilia::push(const Vec3f& vec){
    *balls.at(balls.size()-1)->pos_ptr += vec;
}


void ProtoCilia::run() {
    for(size_t i = 0; i<balls.size(); ++i){
        balls.at(i)->verlet2();
    }
    
    
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor4f(col.getR(), col.getG(), col.getB(), col.getA());
    for(size_t i = 0; i<sticks.size(); ++i){
        
        sticks.at(i)->constrainLen();
        //sticks.at(i)->display();
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);;
}
