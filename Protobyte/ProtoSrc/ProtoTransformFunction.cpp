
/*! File:   ProtoTransformFunction.cpp
 * Author: Ira Greenberg
 *
 * Created on May 19, 2013, 2:33 PM
 * Copyright (c) 2013 Ira Greenberg. All rights reserved.
 */

#include "ProtoTransformFunction.h"
#include <iostream>



namespace ijg {
	std::ostream& operator<<(std::ostream& out, const TransformFunction& func){
		out << "@: " << &func << ", functionType: " << func.functionType << ", minValue: " << func.minValue <<
			", maxValue: " << func.maxValue << ", vectorRange: " << func.vectorRange << ", scalerRange: " << func.scalerRange <<
			", periodCount: " << func.periodCount << ", isVectorRange: " << func.isVectorRange << ", isScalerRange: " << func.isScalerRange;
		return out;
	}
}

using namespace ijg;

ProtoTransformFunction::ProtoTransformFunction() {
	minValue = maxValue = 0;
    isVectorRange = isScalerRange = false;
    vectorRange.elem0 = Vec3f(0,0,0);
    vectorRange.elem1 = Vec3f(1,1,1);

	//unsigned char functionType;
	//float minValue, maxValue;
	//ProtoTuple2<Vec3f> vectorRange;
	//ProtoTuple2f scalerRange;
	//// bool isRandom;
	//short periodCount;
	//bool isVectorRange, isScalerRange;
}

ProtoTransformFunction::ProtoTransformFunction(FunctionType functionType, /*bool isRandom = 0, */short periodCount) :
functionType(functionType), /*isRandom(isRandom), */periodCount(periodCount) {
    isVectorRange = isScalerRange = false;
    vectorRange.elem0 = Vec3f(0,0,0);
    vectorRange.elem1 = Vec3f(1,1,1);
}

ProtoTransformFunction::ProtoTransformFunction(FunctionType functionType, ProtoTuple2v3f vectorRange, /*bool isRandom = 0, */short periodCount) :
functionType(functionType), vectorRange(vectorRange), /*isRandom(isRandom), */periodCount(periodCount) {
    isVectorRange = true;
    isScalerRange = false;
}

ProtoTransformFunction::ProtoTransformFunction(FunctionType functionType, Tup2f scalerRange, /*bool isRandom = 0, */short periodCount) :
functionType(functionType), scalerRange(scalerRange), /*isRandom(isRandom), */periodCount(periodCount) {
    isVectorRange = false;
    isScalerRange = true;
    
    vectorRange.elem0 = Vec3f(scalerRange.elem0, scalerRange.elem0, scalerRange.elem0);
    vectorRange.elem1 = Vec3f(scalerRange.elem1, scalerRange.elem1, scalerRange.elem1);
}

ProtoTransformFunction::ProtoTransformFunction(FunctionType functionType, float maxValue, /*bool isRandom = 0, */short periodCount) :
functionType(functionType), maxValue(maxValue), /*isRandom(isRandom), */periodCount(periodCount) {
    isVectorRange = false;
    isScalerRange = false;
    vectorRange.elem0 = Vec3f(0, 0, 0);
    vectorRange.elem1 = Vec3f(maxValue, maxValue, maxValue);
}