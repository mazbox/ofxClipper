#include "testApp.h"
#include "ofxClipper.h"

ofxClipper clipper;
//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

void getCircleCoords(ofVec2f centre, float radius, vector<ofVec2f> &out) {
	for(float i = 0; i < PI*2; i += PI/200.f) {
		ofVec2f v(radius, 0);
		v.rotateRad(i);
		v += centre;
		out.push_back(v);
	}
}

void drawPoly(vector<ofVec2f> &poly) {
	
	ofBeginShape();
	for(int i = 0; i < poly.size(); i++) {
		//mesh.addVertex(poly[i]);
		ofVertex(poly[i].x, poly[i].y);
	}
	ofEndShape();
}


//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0);
	ofSetColor(255);
	
	vector<ofVec2f> a, b;
	getCircleCoords(ofVec2f(200, 200), 50, a);
	getCircleCoords(ofVec2f(250, 200), 50, b);
	ofSetHexColor(0x990000);
	drawPoly(a);
	ofSetHexColor(0x66FFFF);
	drawPoly(b);
	float t = ofGetElapsedTimef();
	
	vector<vector<ofVec2f> > polys;
	polys.push_back(a);
	polys.push_back(b);



	vector<vector<ofVec2f> > out;
	clipper.doDifference(polys, out);
	
	
	glPushMatrix();
	glTranslatef(400,0,0);
	for(int i = 0; i < out.size(); i++) {
		drawPoly(out[i]);
	}
	glPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}