/*!  \brief  ProtoMath.cpp: (add brief description)
 ProtoMath.cpp
 Protobyte Library v02
 
 Created by Ira on 9/2/13.
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

#include "ProtoMath.h"





// eventually replace these with Mersenne twister algorithm

// from http://stackoverflow.com/a/686373
namespace ijg {
    
    float random(float max) {
        return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/max));
    }
    
    float random(float min, float max) {
        return min + static_cast <float> (rand()) /(static_cast <float> (RAND_MAX/(max-min)));
    }
    
    
    float getMax(float val0, float val1){
        return val0>val1?val0:val1;
    }
    
    float getMin(float val0, float val1){
        return val0<val1?val0:val1;
    }
    
    float constrain(float val, float min, float max){
        if(val>=min && val <=max){
            return val;
        } else if(val<min){
            return min;
        } else {
            return max;
        }
    }
}







