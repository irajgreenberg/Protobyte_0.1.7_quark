/*!  \brief  ProtoJuncusEffusus.h: (add brief description)
ProtoJuncusEffusus.h
Protobyte Library v02

Created by Ira on 03/05/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

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

#include "ProtoJuncusEffusus.h"
using namespace ijg;

// this is nasty fix eventually
namespace {
	float waveTheta = 0;
	float waveRadius = 1.85;


	std::vector<float> waveRadiusVals;
	std::vector<float> waveThetas;
	std::vector<float> waveFreqs;

}

ProtoJuncusEffusus::ProtoJuncusEffusus(){

}

ProtoJuncusEffusus::ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4) : ProtoShape3(pos, rot, size, col4){

}
ProtoJuncusEffusus::ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4, const std::string& textureImageURL1) : ProtoShape3(pos, rot, size, col4), textureImageURL1(textureImageURL1), textureImageURL2(textureImageURL1){
	init();
}

ProtoJuncusEffusus::ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4, const std::string& textureImageURL1, const std::string& textureImageURL2) : ProtoShape3(pos, rot, size, col4), textureImageURL1(textureImageURL1), textureImageURL2(textureImageURL2){
	init();
}

// cstr for printing
ProtoJuncusEffusus::ProtoJuncusEffusus(
	const ProtoColor4f& col4, const std::string& textureImageURL1, const std::string& textureImageURL2, const std::vector<Vec3f>& cps, GeomDetail detail) : ProtoShape3(Vec3f(), Vec3f(), Dim3f(), col4), textureImageURL1(textureImageURL1), textureImageURL2(textureImageURL2), cps(cps), detail(detail){
	init2();
}

// for printing
void ProtoJuncusEffusus::init2(){
	STRIDE = 12;
	//trace("ind =", ind);
	float theta = 0.0f;
	//float tubuleRadius = 4.2;//8.73f;
	float tubuleRadiusMin = .75;//8.73f;
	float tubuleRadiusMax = 4.5; // 3.75;//8.73f;
	float tubuleLen = 2.475;
	int tubuleSegs = 9;
	float tubuleStep = tubuleLen / tubuleSegs;
	int tubuleInterpDetail = 4;//6;
	int tubuleCSDetail = 12;//18;
	int tubuleWrapInterpDetail = 3;
	int tubuleWrapCSDetail = 5;

	tubuleRadiusMin = random(.05, .35);
	tubuleRadiusMax = random(.4, 2.155);

	switch (detail){
	case DRAFT:
		tubuleSegs = 3;
		tubuleInterpDetail = 1;
		tubuleCSDetail = 3;
		tubuleWrapInterpDetail = 1;
		tubuleWrapCSDetail = 3;
		break;
	case LOW:
		tubuleSegs = 6;
		tubuleInterpDetail = 2;
		tubuleCSDetail = 7;
		tubuleWrapInterpDetail = 2;
		tubuleWrapCSDetail = 4;
		break;
	case MEDIUM:
		tubuleSegs = 9;
		tubuleInterpDetail = 4;
		tubuleCSDetail = 12;
		tubuleWrapInterpDetail = 3;
		tubuleWrapCSDetail = 8;
		break;
	case HIGH:
		tubuleSegs = 12;
		tubuleInterpDetail = 5;
		tubuleCSDetail = 16;
		tubuleWrapInterpDetail = 5;
		tubuleWrapCSDetail = 9;
		break;
	case SUPER:
		tubuleSegs = 16;
		tubuleInterpDetail = 7;
		tubuleCSDetail = 24;
		tubuleWrapInterpDetail = 9;
		tubuleWrapCSDetail = 12;
		break;
	}

	// curvey
	tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleCSDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleRadiusMin, tubuleRadiusMax), int(random(2, 12))), true, textureImageURL1);
	tubulePrimsOrig = tubule.getInterleavedPrims();

	tubuleCrossSectionDetail = tubule.getCrossSectionDetail();
	tubuleSpineSegments = tubule.getInterleavedPrims().size() / STRIDE / tubuleCrossSectionDetail;
	//trace("tubule.getInterleavedPrims().size() =", tubule.getInterleavedPrims().size());
	//trace("tubulePrimsOrig.size() =", tubulePrimsOrig.size());
	//trace("tubuleCrossSectionDetail =", tubuleCrossSectionDetail);
	//trace("tubuleSpineSegments =", tubuleSpineSegments);

	tubule.textureOn();
	tubule.setTextureScale(.5);
	//tubule.setShininess(98);
	tubule.setColor(Col4f(1, 1, 1, 1));

	// hack - review
	float freqMax = random(1900, 3500);
	float radiusMax = random(.01, .05);
	tubuleSpine = tubule.getPath();
	for (size_t i = 0; i < tubuleSpine.getVerts().size(); ++i){
		//balls.push_back(std::shared_ptr<VerletBall>(new VerletBall(&spine.getVerts().at(i))));

		waveRadiusVals.push_back((tubuleSpine.getVerts().size() - i)*radiusMax); // HACK --fix
		waveFreqs.push_back(PI / freqMax/*random(PI/1440.0, PI/360.0)*/); // HACK --fix
		waveThetas.push_back(0); // HACK --fix
	}

	//    
	std::vector<Vec3f> pts;
	float tubuleBuldgeMin = random(.085, .65), tubuleBuldgeMax = random(.85, 1.95);

	for (int i = 0; i < tubule.getVertices().size() - 2; ++i){
		pts.push_back(tubule.getVertices().at(i).pos);
	}

	Spline3 s(pts, tubuleWrapInterpDetail, false, .5);
	int id = int(random(4));
	switch (id) {
	case 0:
		tubuleWrap = Tube(s, .03, tubuleWrapCSDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), int(random(3, 10))), true, textureImageURL2);
		break;
	case 1:
		tubuleWrap = Tube(s, .03, tubuleWrapCSDetail, ProtoTransformFunction(ProtoTransformFunction::LINEAR, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), int(random(3, 10))), true, textureImageURL2);
		break;
	case 2:
		tubuleWrap = Tube(s, .03, tubuleWrapCSDetail, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), int(random(3, 10))), true, textureImageURL2);
		break;
	case 3:
		tubuleWrap = Tube(s, .03, tubuleWrapCSDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL_INVERSE, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), int(random(3, 10))), true, textureImageURL2);
		break;
	default:
		tubuleWrap = Tube(s, .03, tubuleWrapCSDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), int(random(3, 10))), true, textureImageURL2);
		break;
	}

	
	tubuleWrapPrims = tubuleWrap.getInterleavedPrims();
	tubuleWrapCrossSectionDetail = tubuleWrap.getCrossSectionDetail();
	tubuleWrapSpineSegments = tubuleWrapPrims.size() / STRIDE / tubuleWrapCrossSectionDetail;

	tubuleWrap.setColor(Col4f(1, 1, 1, 1));
	tubuleWrap.textureOn();
}


// live
void ProtoJuncusEffusus::init(){
	STRIDE = 12;
	//trace("ind =", ind);
	float theta = 0.0f;
	float tubuleRadius = 5.75;//8.73f;

	float tubuleLen = 2.875;
	int tubuleSegs = 9;
	float tubuleStep = tubuleLen / tubuleSegs;
	int tubuleInterpDetail = 2;//6;
	int tubuleDetail = 12;//18;



	std::vector<Vec3f> cps;

	Vec3 pos = Vec3f(0, tubuleLen / 2, 0);
	for (int k = 0; k < tubuleSegs; ++k){
		if (k < 3){
			cps.push_back(Vec3f(pos.x + random(-.22, .22), pos.y - tubuleStep*k, pos.z + random(-.22, .22)));
		}
		else {
			cps.push_back(Vec3f(pos.x + random(-.06, .06), pos.y - tubuleStep*k, pos.z + random(-.06, .06)));
		}
	}
	// tapered
	//            tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(tubuleRadius, .21), 1),true, "reptile3.jpg");

	// curvey
	tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(2.88, tubuleRadius), 6), true, textureImageURL1);
	tubulePrimsOrig = tubule.getInterleavedPrims();
	tubuleCrossSectionDetail = tubule.getCrossSectionDetail();
	tubuleSpineSegments = tubule.getInterleavedPrims().size() / STRIDE / tubuleCrossSectionDetail;
	//trace("tubule.getInterleavedPrims().size() =", tubule.getInterleavedPrims().size());
	//trace("tubulePrimsOrig.size() =", tubulePrimsOrig.size());
	//trace("tubuleCrossSectionDetail =", tubuleCrossSectionDetail);
	//trace("tubuleSpineSegments =", tubuleSpineSegments);

	tubule.textureOn();
	tubule.setTextureScale(1.0);
	//tubule.setShininess(104);
	tubule.setColor(Col4f(1, 1, 1, 1));

	// hack - review
	float freqMax = random(1900, 3500);
	float radiusMax = random(.01, .05);
	tubuleSpine = tubule.getPath();
	for (size_t i = 0; i < tubuleSpine.getVerts().size(); ++i){
		//balls.push_back(std::shared_ptr<VerletBall>(new VerletBall(&spine.getVerts().at(i))));

		waveRadiusVals.push_back((tubuleSpine.getVerts().size() - i)*radiusMax); // HACK --fix
		waveFreqs.push_back(PI / freqMax/*random(PI/1440.0, PI/360.0)*/); // HACK --fix
		waveThetas.push_back(0); // HACK --fix
	}

	//    
	std::vector<Vec3f> pts;
	float tubuleBuldgeMin = .25f, tubuleBuldgeMax = 2.25f;

	for (int i = 0; i < tubule.getVertices().size() - 2; ++i){
		pts.push_back(tubule.getVertices().at(i).pos);
	}

	Spline3 s(pts, 3, false, .5);
	tubuleWrap = Tube(s, .03, 6/*12*/, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleBuldgeMin, random(tubuleBuldgeMax*.85, tubuleBuldgeMax)/*2.1*/), 40), true, textureImageURL2);
	tubuleWrapPrims = tubuleWrap.getInterleavedPrims();
	tubuleWrapPrimsOrig = tubuleWrap.getInterleavedPrims();
	tubuleWrapCrossSectionDetail = tubuleWrap.getCrossSectionDetail();
	tubuleWrapSpineSegments = tubuleWrapPrims.size() / STRIDE / tubuleWrapCrossSectionDetail;

	tubuleWrap.setColor(Col4f(.3f, .25f, .2f, 1));
	tubuleWrap.textureOn();

	tubuleWrapSegs = tubuleWrapPrims.size()/tubuleSpineSegments;

	// for live physics
	for (int i = 0; i < tubuleWrapPrims.size(); ++i){
		primForce.push_back(0);
		primDamping.push_back(.92);
		primFreq.push_back(PI / 180.0f);
		primTheta.push_back(0);
	}

	//trace("tubuleSpine.getVerts().size() =", tubuleSpine.getVerts().size());

	///***********************************************************
	//*                      Begin Physics                       *
	//***********************************************************/
	//// calculate Verlet spine
	////trace("spine pt alpha =", tubule.getVertices().at(0).pos); 
	////trace("spine pt omega =", tubule.getVertices().at(tubule.getVertices().size() - 1).pos);
	//// create verlet spline
	//// stick extrema
	//// 2.7, -2
	//trace("tubuleSpine.getVerts().size() =", tubuleSpine.getVerts().size());
	//float stickGap = 4.7 - (tubuleSpineSegments + 2);

	// calculate verlet balls (spine)
	for (size_t i = 0; i < tubuleSpine.getVerts().size(); ++i){
		//trace("tubuleSpine.getVerts().at(i) =", tubuleSpine.getVerts().at(i));
		balls.push_back(std::shared_ptr<VerletBall>(new ProtoVerletBall(tubuleSpine.getVerts().at(i))));
	}


	for (size_t i = 0; i < balls.size() - 1; ++i){

		// anchor 1
		if (i == 0){
			sticks.push_back(ProtoVerletStick(balls.at(i), balls.at(i + 1), .9, Tup2f(0, .5)));
		}
		// anchor 2
		else if (i == balls.size() - 2){
			sticks.push_back(ProtoVerletStick(balls.at(i), balls.at(i + 1), .9, Tup2f(.5, 0)));
		}
		// body
		else {
			sticks.push_back(ProtoVerletStick(balls.at(i), balls.at(i + 1), .9, Tup2f(.5, .5)));
		}
	}

	//trace("sticks.size() =", sticks.size());

	// calculate distances between each verletBall (Note: functions as spine center) and all the vertices.
	// dists will be used for fall-off calculations for individual vetices based on verlet sticks
	// -> remember: 1 more spline seg than Verlet stick
	for (int h = 0; h < balls.size(); ++h) { // check each ball against all points
		Vec3f v = balls.at(h)->getPos();
		std::vector<float> tempDists;
		for (int i = 0; i < tubuleSpineSegments; ++i) {
			for (int j = 0; j < tubuleCrossSectionDetail*STRIDE; j += STRIDE) {
				int index = i*tubuleCrossSectionDetail*STRIDE + j;
				float d = v.dist(Vec3f(tubulePrimsOrig.at(index), tubulePrimsOrig.at(index + 1), tubulePrimsOrig.at(index + 2)));
				//std::cout << d << ", ";
				tempDists.push_back(d);
			}
		}
		//std::cout << "" << std::endl;
		dists.push_back(tempDists);
	}
	//trace("dists.size() =", dists.size()); // = 23
	//trace("dists.at(0).size() =", dists.at(0).size()); //  = 12
}



std::vector<Tup4v> ProtoJuncusEffusus::getGeomData(bool isTubuleData, bool isTubuleWrapData){
	std::vector<Tup4v> vs;

	if (isTubuleData){
		//std::vector<Vec3> faceVecs;
		for (int i = 0; i < tubule.faces.size(); ++i){
			vs.push_back(Tup4v(tubule.getFaces().at(i).getNorm(), tubule.getFaces().at(i).v0, tubule.getFaces().at(i).v1, tubule.getFaces().at(i).v2));
		}
	}

	if (isTubuleWrapData){
		for (int i = 0; i < tubuleWrap.faces.size(); ++i){
			vs.push_back(Tup4v(tubuleWrap.getFaces().at(i).getNorm(), tubuleWrap.getFaces().at(i).v0, tubuleWrap.getFaces().at(i).v1, tubuleWrap.getFaces().at(i).v2));
		}
	}
	return vs;
}


void ProtoJuncusEffusus::display(RenderMode render1, RenderMode render2, float pointSize1, float pointSize2){
	tubule.display(render1, pointSize1);
	tubuleWrap.display(render2, pointSize2);
}



void ProtoJuncusEffusus::pulse(int ring, float freq, float force){
	//trace("force =", force);
	//// get buffer data form GPU
	glBindBuffer(GL_ARRAY_BUFFER, tubule.getVboID());

	//// move tubule based on verlet chain
	//for (int i = 0; i < tubuleSpineSegments; ++i) {
		for (int j = 0; j < tubuleCrossSectionDetail*STRIDE; j += STRIDE) {
			int index = ring*tubuleCrossSectionDetail*STRIDE + j;
			tubule.interleavedPrims.at(index) = tubulePrimsOrig.at(index)*fmax(1, force);
			tubule.interleavedPrims.at(index + 1) = tubulePrimsOrig.at(index + 1);
			tubule.interleavedPrims.at(index + 2) = tubulePrimsOrig.at(index + 2)*fmax(1, force);
		}
	//}

	//// upload data back to GPU
	int vertsDataSize = sizeof (float)*tubule.interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &tubule.interleavedPrims[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//// tubuleWrap
	//int pts = tubuleWrapPrims.size() / STRIDE;
	//tubuleWrapSegs = pts / tubuleSpineSegments;

	//glBindBuffer(GL_ARRAY_BUFFER, tubuleWrap.getVboID());
	////////// move tubule based on verlet chain
	//for (int i = 0; i < tubuleSpineSegments; ++i) {
	//	for (int j = 0; j < tubuleWrapSegs*STRIDE; j += STRIDE) {
	//		int index = i*tubuleWrapSegs*STRIDE + j;
	//		tubuleWrap.interleavedPrims.at(index) = tubuleWrapPrimsOrig.at(index) + balls.at(i)->pos.x;// *(1.0 / dists.at(i).at(index));
	//		tubuleWrap.interleavedPrims.at(index + 1) = tubuleWrapPrimsOrig.at(index + 1);// +balls.at(i)->pos.y;// *(1.0 / dists.at(i).at(index + 1));
	//		tubuleWrap.interleavedPrims.at(index + 2) = tubuleWrapPrimsOrig.at(index + 2) + balls.at(i)->pos.z;// *(1.0 / dists.at(i).at(index + 2));
	//	}
	//}

	////////// upload data back to GPU
	//vertsDataSize = sizeof (float)*tubuleWrap.interleavedPrims.size();
	//glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &tubuleWrap.interleavedPrims[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void ProtoJuncusEffusus::spring(){
}

// subtract 14 to get ring count form 0-22
void ProtoJuncusEffusus::breath(int ring, float freq, float force){
	//trace("force =", force);
	//// get buffer data form GPU
	glBindBuffer(GL_ARRAY_BUFFER, tubule.getVboID());

	//// move verlet ball at ring 
	if (ring != -1){
		//balls.at(ring - 14)->pos += force*.000001;
		balls.at(ring - 14)->pos += force*.000001;
	}

	//// move tubule based on verlet chain
	for (int i = 0; i < tubuleSpineSegments; ++i) {
		for (int j = 0; j < tubuleCrossSectionDetail*STRIDE; j += STRIDE) {
			int index = i*tubuleCrossSectionDetail*STRIDE + j;
			tubule.interleavedPrims.at(index) = tubulePrimsOrig.at(index) + balls.at(i)->pos.x;// *(1.0 / dists.at(i).at(index));
			tubule.interleavedPrims.at(index + 1) = tubulePrimsOrig.at(index + 1);// +balls.at(i)->pos.y;// *(1.0 / dists.at(i).at(index + 1));
			tubule.interleavedPrims.at(index + 2) = tubulePrimsOrig.at(index + 2) + balls.at(i)->pos.z;// *(1.0 / dists.at(i).at(index + 2));
		}
	}

	//// upload data back to GPU
	int vertsDataSize = sizeof (float)*tubule.interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &tubule.interleavedPrims[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// tubuleWrap
	int pts = tubuleWrapPrims.size() / STRIDE;
	tubuleWrapSegs = pts/tubuleSpineSegments;

	glBindBuffer(GL_ARRAY_BUFFER, tubuleWrap.getVboID());
	//////// move tubule based on verlet chain
	for (int i = 0; i < tubuleSpineSegments; ++i) {
		for (int j = 0; j < tubuleWrapSegs*STRIDE; j+=STRIDE) {
			int index = i*tubuleWrapSegs*STRIDE + j;
			tubuleWrap.interleavedPrims.at(index) = tubuleWrapPrimsOrig.at(index) + balls.at(i)->pos.x;// *(1.0 / dists.at(i).at(index));
			tubuleWrap.interleavedPrims.at(index + 1) = tubuleWrapPrimsOrig.at(index + 1);// +balls.at(i)->pos.y;// *(1.0 / dists.at(i).at(index + 1));
			tubuleWrap.interleavedPrims.at(index + 2) = tubuleWrapPrimsOrig.at(index + 2) + balls.at(i)->pos.z;// *(1.0 / dists.at(i).at(index + 2));
		}
	}

	//////// upload data back to GPU
	vertsDataSize = sizeof (float)*tubuleWrap.interleavedPrims.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &tubuleWrap.interleavedPrims[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (int i = 0; i < tubuleSpineSegments; ++i) {
		// activate verlet integration
		balls.at(i)->verlet();
	}

	//// constrain physics
	for (int i = 0; i < sticks.size(); ++i){
		sticks.at(i).constrainLen();
	}
}