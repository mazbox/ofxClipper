/**
 *  ofxClipper.cpp
 *
 *  Created by Marek Bereza on 18/05/2013.
 */


#include "ofxClipper.h"

using namespace ClipperLib;

ofxClipper::ofxClipper() {
}

ofxClipper::~ofxClipper() {
}




void ofxClipper::doUnion(PolygonList &inPolys, PolygonList &outPolys) {
	execute(ctUnion, inPolys, outPolys);
}

void ofxClipper::doIntersection(PolygonList &inPolys, PolygonList &outPolys) {
	execute(ctIntersection, inPolys, outPolys);
}

void ofxClipper::doXor(PolygonList &inPolys, PolygonList &outPolys) {
	execute(ctXor, inPolys, outPolys);
}

void ofxClipper::doDifference(PolygonList &inPolys, PolygonList &outPolys) {
	execute(ctDifference, inPolys, outPolys);
}

void ofxClipper::findMinMaxOfAll(PolygonList &polys, ofVec2f &minV, ofVec2f &maxV) {
	minV.x = FLT_MAX;
	minV.y = FLT_MAX;
	maxV.x = FLT_MIN;
	maxV.y = FLT_MIN;
	for(int i = 0; i < polys.size(); i++) {
		findMinMax(polys[i], minV, maxV);
	}
	
	// printf("%.2f, %.2f     %.2f, %.2f\n", minV.x, minV.y, maxV.x, maxV.y);
}

void ofxClipper::findMinMax(vector<ofVec2f> &poly, ofVec2f &minv, ofVec2f &maxv) {
	for(int i = 0; i < poly.size(); i++) {
		if(poly[i].x<minv.x) minv.x = poly[i].x;
		if(poly[i].y<minv.y) minv.y = poly[i].y;

		if(poly[i].x>maxv.x) maxv.x = poly[i].x;
		if(poly[i].y>maxv.y) maxv.y = poly[i].y;
	}
}

void ofxClipper::createClipperPoly(vector<ofVec2f> &poly, ClipperLib::Polygon &p) {
	float valXRange = maxVals.x - minVals.x;
	float valYRange = maxVals.y - maxVals.y;
	
	p.reserve(poly.size());
	
	for(int i = 0; i < poly.size(); i++) {
		float x = (poly[i].x - minVals.x)/valXRange;
		float y = (poly[i].y - minVals.y)/valYRange;
		/*
		p.push_back(IntPoint( x * LONG_MAX,
							 y * LONG_MAX
		));*/
		p.push_back(IntPoint(poly[i].x, poly[i].y));
	}
}

void ofxClipper::convertBackToOfVec2f(ClipperLib::Polygon &p, vector<ofVec2f> &v) {
	
	float valXRange = maxVals.x - minVals.x;
	float valYRange = maxVals.y - maxVals.y;
	
	v.reserve(p.size());
	
	for(int i = 0; i < p.size(); i++) {
		/*float x = p[i].X/LONG_MAX;
		float y = p[i].Y/LONG_MAX;
		x *= valXRange;
		y *= valYRange;
		x += minVals.x;
		y += minVals.y;*/
		v.push_back(ofVec2f(p[i].X, p[i].Y));
	}
}

void ofxClipper::execute(ClipperLib::ClipType clipType, PolygonList &inPolys, PolygonList &outPolys) {
	
	clpr.Clear();
	output.clear();
	//findMinMaxOfAll(minVals, maxVals);
	
	for(int i = 0; i < inPolys.size(); i++) {
		ClipperLib::Polygon p;
		createClipperPoly(inPolys[i], p);
		if(i==0) clpr.AddPolygon(p, ptSubject);
		else clpr.AddPolygon(p,ptClip);
	}
	clpr.Execute(clipType, output, pftEvenOdd, pftEvenOdd);
	//printf("Output: %d\n", outp.size());
	// convert back to float ofVec2fs
	for(int i = 0; i < output.size(); i++) {
		outPolys.push_back(vector<ofVec2f>());
		convertBackToOfVec2f(output[i], outPolys.back());
	}
	
}