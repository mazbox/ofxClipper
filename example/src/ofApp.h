/**
 *  a demo for how to use ofxclipper at oF0.9.8 and mac
 *
 *  it base on the ofxclipper created by Marek Bereza on 18/05/2013.
 *  Add ofPath supported by ryanaltair on 08/02/2017
 *  to use ofPolyline , just change it into ofPath using getPolylinesFromPath()
 */
#pragma once

#include "ofMain.h"
#include "ofxClipper.h"
class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw(); 
    ofPath getSquare(float x, float y,   float length){ // use to make a single square
        ofPath p;
        p.moveTo(x,y);
        p.lineTo(x+length,y);
        p.lineTo(x+length,y+length);
        p.lineTo(x,y+length);
        p.lineTo(x,y);
        p.close();
        return p;
    }
    
    vector<ofPath> paths;
    ofPath multiUnionOutputline;
    ofPath subpath;
    ofPath clippath;
    int linecount=0;
    ofxClipper clipper;
    vector<ofPath> outputline;
};


