
#include "ofxClipper.h"

using namespace ClipperLib;

ofxClipper::ofxClipper() {
    cout<<"now we have a clippper"<<endl;
}

ofxClipper::~ofxClipper() {
    
    cout<<"now we delete a clippper"<<endl;
}





 
ofPath ofxClipper::getMultiUnion(vector<ofPath> inPath) {
    ofPath p;
    ofPath inp;
    for(auto &path:inPath){
        inp.append(path);
    }
    p= execute(ctUnion, inp);
    return p;
}
ofPath ofxClipper::getUnion(ofPath subPath,ofPath clipPath) {
    ofPath p;
    p= execute(ctUnion, subPath,clipPath);
    return p;
}
ofPath ofxClipper::getIntersection(ofPath subPath,ofPath clipPath) {
    ofPath p;
    p= execute(ctIntersection, subPath,clipPath);
    return p;
}
ofPath ofxClipper::getXor(ofPath subPath,ofPath clipPath) {
    ofPath p;
    p= execute(ctXor, subPath,clipPath);
    return p;
}
ofPath ofxClipper::getDifference(ofPath subPath,ofPath clipPath) {
    ofPath p;
    p= execute(ctDifference, subPath,clipPath);
    return p;
}

vector<ofPolyline> ofxClipper::getPolylinesFromPath(ofPath inpath){
    vector<ofPolyline> polylines;
    ofPolyline polyline;
    polylines.clear();
    //get commands from path
    vector<ofPath::Command> commands;
    vector<ofPath::Command>& pathCommands = inpath.getCommands();
    cout<<"command count:" << inpath.getCommands().size()<<endl;
    commands.swap(pathCommands);
    int curveResolution = ofGetStyle().curveResolution;
    int arcResolution = inpath.getCircleResolution();
    
    for(int i=0; i<commands.size(); i++)
    {
        switch(commands[i].type)
        {
            case ofPath::Command::moveTo:
                polyline.addVertex(commands[i].to);
                
                break;
            case ofPath::Command::lineTo:
                polyline.addVertex(commands[i].to);
                break;
            case ofPath::Command::curveTo:
                //                polyline.curveTo(commands[i].to);
                polyline.curveTo(commands[i].to, curveResolution);
                break;
            case ofPath::Command::bezierTo:
                //                polyline.bezierTo(commands[i].cp1,commands[i].cp2,commands[i].to);
                polyline.bezierTo(commands[i].cp1,commands[i].cp2,commands[i].to, curveResolution);
                break;
            case ofPath::Command::quadBezierTo:
                polyline.quadBezierTo(commands[i].cp1,commands[i].cp2,commands[i].to, curveResolution);
                //                polyline.quadBezierTo(commands[i].cp1,commands[i].cp2,commands[i].to);
                break;
            case ofPath::Command::arc:
                polyline.arc(commands[i].to,commands[i].radiusX,commands[i].radiusY,commands[i].angleBegin,commands[i].angleEnd, arcResolution);
                //                polyline.arc(commands[i].to,commands[i].radiusX,commands[i].radiusY,commands[i].angleBegin,commands[i].angleEnd);
                
                break;
            case ofPath::Command::arcNegative:
                polyline.arcNegative(commands[i].to,commands[i].radiusX,commands[i].radiusY,commands[i].angleBegin,commands[i].angleEnd, arcResolution);
                
                break;
            case ofPath::Command::close:
                // we won't add any not close line
                polyline.close();
                polylines.push_back(polyline);
                polyline.clear();
                break;
        }
        
    }
    return polylines;
}

ofPath  ofxClipper::getPathFromPolylines(vector<ofPolyline> inpolylines){
    ofPath path;
    for(auto &polyline:inpolylines){
        vector<ofVec2f> points;
        for(auto &p:polyline){
            points.push_back(p);
        }
        path.moveTo(points[0]);
        for(int i=1;i<points.size();i++){
            path.lineTo(points[i]);
        }
        path.close();
    }
    return path;

}


vector<ofVec2f> ofxClipper::getVerticesFromPolyline(ofPolyline polyline){
    vector<ofVec2f> returnVertices;
    
    for(auto &p:polyline){
        returnVertices.push_back(p);
        //  cout<<p<<"\t";
    }
    cout<<endl;
     
    return returnVertices;
}
PolygonList ofxClipper::getPolygonListFromPath(ofPath inpath){
    PolygonList returnPolygons;
    vector<ofPolyline> polylines;
    polylines=getPolylinesFromPath(inpath);
    for (auto &line:polylines) {
        
        returnPolygons.push_back(getVerticesFromPolyline(line));
    }
    return returnPolygons;
}
ofPolyline ofxClipper::getPolylineFromVectices(PolygonList &inPolys){
    ofPolyline polyline;
    for(auto &line:inPolys){
        for(auto &p:line){
            polyline.addVertex(p);
        }
        polyline.close();
    }
    return polyline;
}
 
ClipperLib::Path ofxClipper::getClipperPathFromVecVec2f(vector<ofVec2f> &poly){
    float valXRange = maxVals.x - minVals.x;
    float valYRange = maxVals.y - maxVals.y;
    ClipperLib::Path p;
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
    return p;
}
ClipperLib::Path ofxClipper::getClipperPathFromPolyline(ofPolyline polyline){
    float valXRange = maxVals.x - minVals.x;
    float valYRange = maxVals.y - maxVals.y;
    vector<ofVec2f> poly;
    
    for(auto &p:polyline){
        poly.push_back(p);
    }
    ClipperLib::Path p;
    p=getClipperPathFromVecVec2f(poly);
    return p;
}
ClipperLib::Paths ofxClipper::getClipperPathsFromPath(ofPath inpath){
    vector<ofPolyline> polylines;
    polylines=getPolylinesFromPath(inpath);
    ClipperLib::Paths returnPaths;
    for(auto &line:polylines){
        returnPaths.push_back(getClipperPathFromPolyline(line));
    }
    return returnPaths;
}

ofPath ofxClipper::getofPathFromPolygonList(PolygonList &inPolys){
    ofPath returnPath;
    for(auto &line:inPolys){
        int i=0;
        for(auto &p:line){
            if(i==0){
                returnPath.moveTo(p);
            }else{
                returnPath.lineTo(p);
            }
            i++;
        }
        returnPath.close();
    }
    return returnPath;
    
}
vector<ofVec2f> ofxClipper::getOfVecVec2fFromClipperPath(ClipperLib::Path &p ) {

    vector<ofVec2f> v;
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
    return v;
}
ofPath ofxClipper::getofPathFromClipperPath(ClipperLib::Paths clipPaths){
   PolygonList outPolys;
    for(int i = 0; i < clipPaths.size(); i++) {
        outPolys.push_back(getOfVecVec2fFromClipperPath(clipPaths[i]));
    }
    
    return getofPathFromPolygonList(outPolys);

}
ofPath ofxClipper::execute(ClipperLib::ClipType clipType, ofPath inPath){
    ClipperLib::Paths output;
    ClipperLib::Paths paths=getClipperPathsFromPath(inPath);
    int executeCount=paths.size();
    ClipperLib::Clipper clpr;
    for(int j=1;j<executeCount;j++){
        
        ClipperLib::Path p;
        //add subject piece
        if(j==1) {
            p=paths[0];
            clpr.AddPath(p, ptSubject,true);
            p.clear();
        }else{
            clpr.AddPaths(output, ptSubject, true);
        }
        //add clip piece
        p=paths[j];
        clpr.AddPath(p,ptClip,true);
        p.clear();
        // excute
        clpr.Execute(clipType, output, pftEvenOdd, pftEvenOdd);
        clpr.Clear();
    }
    
    return getofPathFromClipperPath(output);
    
}
ofPath ofxClipper::execute(ClipperLib::ClipType clipType, ofPath subjectPath,ofPath clipPath) {
    ClipperLib::Paths output;
    ClipperLib::Paths subjectP;
    ClipperLib::Paths clipP;
    ClipperLib::Clipper clpr;
    //add subject piece
    subjectP=getClipperPathsFromPath(subjectPath);
    clpr.AddPaths(subjectP, ptSubject,true);
    //add clip piece
    clipP=getClipperPathsFromPath(clipPath);
    clpr.AddPaths(clipP,ptClip,true);
    // excute
    clpr.Execute(clipType, output, pftEvenOdd, pftEvenOdd);
    clpr.Clear();
    
    return getofPathFromClipperPath(output);
    
}
 
