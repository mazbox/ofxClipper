
#include "clipper.hpp"
#include "ofMain.h"


typedef vector<vector<ofVec2f> > PolygonList;


class ofxClipper {
public:
	ofxClipper();
	virtual ~ofxClipper();
	
	void doUnion		(PolygonList &inPolys, PolygonList &outPolys);
	void doIntersection (PolygonList &inPolys, PolygonList &outPolys);
	void doXor			(PolygonList &inPolys, PolygonList &outPolys);
	void doDifference	(PolygonList &inPolys, PolygonList &outPolys);

	
private:
	void execute(ClipperLib::ClipType clipType, PolygonList &inPolys, PolygonList &outPolys);
	void findMinMaxOfAll(PolygonList &polys, ofVec2f &minV, ofVec2f &maxV);
	void createClipperPoly(vector<ofVec2f> &poly, ClipperLib::Polygon &p);
	void findMinMax(vector<ofVec2f> &poly, ofVec2f &minv, ofVec2f &maxv);
	void convertBackToOfVec2f(ClipperLib::Polygon &p, vector<ofVec2f> &v);
	ofVec2f minVals;
	ofVec2f maxVals;
	ClipperLib::Clipper clpr;
	ClipperLib::Polygons output;
};