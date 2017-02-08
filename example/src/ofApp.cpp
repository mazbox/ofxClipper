#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    //prepare polygon for multi Union and add random color
    for (int i=1; i< 5; i++)
    {
        for (int j=1; j<5; j++)
        {
            paths.push_back(getSquare(i*50, j*40+i*10,  60));
        }
        
    }
    
    for(auto &p:paths){
        ofColor color = ofColor( ofRandom(0, 255),
                                ofRandom(0, 255),
                                ofRandom(0, 255)
                                );
        p.setFillColor(color);
    }
    //prepare polygon for single bool like  union difference xor intersection
    //and add color
    for (int i=1; i< 3; i++)
    {
        for (int j=1; j<2; j++)
        {
            subpath.append(getSquare(i*50, j*40+i*10,  60));
        }
        
    }
    
    for (int i=3; i< 5; i++)
    {
        for (int j=1; j<2; j++)
        {
            clippath.append(getSquare(i*50, j*40+i*10,  60));
        }
        
    }
    subpath.setFillColor(ofColor::orangeRed);
    clippath.setFillColor(ofColor::lawnGreen);
    
    // prepare end
    
    // excute the bool operation and add color
    outputline.push_back( clipper.getUnion(subpath,clippath));
    outputline.push_back( clipper.getIntersection(subpath,clippath));
    outputline.push_back( clipper.getXor(subpath,clippath));
    outputline.push_back(clipper.getDifference(subpath,clippath));
    for(auto &polygon:outputline){
        polygon.setFillColor(ofColor::blueSteel);
    }
    
    multiUnionOutputline=clipper.getMultiUnion(paths);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle("ofxclipperDemo");
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(20, 20, 0);
    // single bool answer draw
    ofPushMatrix();
    subpath.draw();
    clippath.draw();
    for(auto &polygon:outputline){
        ofTranslate(0, 80, 0);
        polygon.draw();
    }
    ofPopMatrix();
    
    // multi bool  answer draw
    // union only
    ofPushMatrix();
    ofTranslate(300, 0, 0);
    for(auto &polygon:paths){
        polygon.draw();
    }
    ofTranslate(0, 240, 0);
    multiUnionOutputline.draw();
    ofPopMatrix();
}

