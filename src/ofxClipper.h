/********************************************************************************
 *                                                                              *
 * Author    :  Ryanaltair                                                      *
 * Version   :  1.0                                                             *
 * Date      :  8 Feb 2017                                                      *
 * Github    :  https://github.com/ryanaltair/ofxClipper                        *
 *                                                                              *
 * License:                                                                     *
 * Use, modification & distribution is subject to Boost Software License Ver 1. *
 * http://www.boost.org/LICENSE_1_0.txt                                         *
 *                                                                              *
 * Attributions:                                                                *
 * The code in a wrapper for clipper by Angus Johnson                           *
 * it based on the Marek Bereza ofxClipper,                                     *
 * https://github.com/mazbox/ofxClipper                                         *
 * but lots changes for example the clipper version update to 6.4.0             *
 * and now we can use ofpath to excute bool operation                           *
 * it also have a quick way to exchange between ofPath and ofPolyline           *
 * so it could be okay to use clipper  with ofPolyline                          *
 * Website   :  http://www.angusj.com                                           *
 *                                                                              *
 *******************************************************************************/
#include "clipper.hpp"
#include "ofMain.h"


typedef vector<vector<ofVec2f> > PolygonList;

class ofxClipper {
public:
	ofxClipper();
	virtual ~ofxClipper();
    ofPath getMultiUnion(vector<ofPath> inPath );
    ofPath getUnion(ofPath subjectPath,ofPath clipPath );
    ofPath getIntersection(ofPath subjectPath,ofPath clipPath );
    ofPath getXor(ofPath subjectPath,ofPath clipPath );
    ofPath getDifference(ofPath subjectPath,ofPath clipPath );
    
    vector<ofPolyline>  getPolylinesFromPath(ofPath inpath);
    ofPath  getPathFromPolylines(vector<ofPolyline> inpolylines);

    
	
private:
     /**
     used for multible union only

     @param clipType cliptype it should be ctUnion
     @param inPath the sub and clip in one path
     @return answer
     */
    ofPath execute(ClipperLib::ClipType clipType, ofPath inPath);
    
    /**
     used for union difference xor intersection

     @param clipType clipType
     @param subjectPath subjectPath in ofPath
     @param clipPath clipPath in ofPath
     @return answer as one ofPath
     */
    ofPath execute(ClipperLib::ClipType clipType, ofPath subjectPath,ofPath clipPath);
    vector<ofVec2f> getVerticesFromPolyline(ofPolyline polyline);
    PolygonList getPolygonListFromPath(ofPath inpath);
    ofPolyline getPolylineFromVectices(PolygonList &inPolys);
    ClipperLib::Path getClipperPathFromVecVec2f(vector<ofVec2f> &poly);
    ClipperLib::Path getClipperPathFromPolyline(ofPolyline polyline);
    ClipperLib::Paths  getClipperPathsFromPath(ofPath inpath);
    ofPath getofPathFromPolygonList(PolygonList &inPolys);
    vector<ofVec2f> getOfVecVec2fFromClipperPath(ClipperLib::Path &p );
	ofVec2f minVals;
	ofVec2f maxVals;
	ClipperLib::Clipper clpr;
 	
   
    
};
