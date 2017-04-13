
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
    switch (inPath.size()) {
        case 0:
            return p;
            break;
        case 1:
            return inPath[0];
            break;
        default:
            break;
    }
    p=getUnion(inPath[0],inPath[1]);
    for(int i=2; i<inPath.size();i++){
        p=getUnion(p,inPath[i]);
        
    }
    
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
ClipperLib::Paths ofxClipper::getClipperPathsFromofPathNew(ofPath inpath){
    ClipperLib::Paths returnClipperPaths;
    ClipperLib::Path clipperPath;
    // get commands faster
    vector<ofPath::Command> commands;
    vector<ofPath::Command>& pathCommands = inpath.getCommands();
    cout<<"command count:" << inpath.getCommands().size()<<endl;
    commands.swap(pathCommands);
    
    for(int i=0; i<commands.size(); i++)
    {
        switch(commands[i].type)
        {
            case ofPath::Command::moveTo:
                clipperPath.push_back(IntPoint(commands[i].to.x, commands[i].to.y));//polyline.addVertex(commands[i].to);
                break;
            case ofPath::Command::lineTo:
                clipperPath.push_back(IntPoint(commands[i].to.x, commands[i].to.y));// polyline.addVertex(commands[i].to);
                break;
            case ofPath::Command::curveTo:
                break;
            case ofPath::Command::bezierTo:
                break;
            case ofPath::Command::quadBezierTo:
                break;
            case ofPath::Command::arc:
                break;
            case ofPath::Command::arcNegative:
                
                break;
            case ofPath::Command::close:
                
                returnClipperPaths.push_back(clipperPath);
                clipperPath.clear();
                break;
        }
        
    }
    
    
    
    return returnClipperPaths;
}

ofPath ofxClipper::getofPathFromClipperPathNew(ClipperLib::Paths clipPaths){
    ofPath returnPath;
    for(int i = 0; i < clipPaths.size(); i++) {
        auto p=clipPaths[i];
        if(p.size()>0){
            returnPath.moveTo(ofVec2f(p[0].X, p[0].Y));
            for(int ii = 1; ii < p.size(); ii++) {
                returnPath.lineTo(ofVec2f(p[ii].X, p[ii].Y));
            }
        }
        returnPath.close();
        
    }
    return returnPath;
    
    
}

ofPath ofxClipper::execute(ClipperLib::ClipType clipType, ofPath subjectPath,ofPath clipPath) {
    
    ClipperLib::Clipper clpr;
    //add subject piece
    
    ClipperLib::Paths subjectP;
    subjectP=getClipperPathsFromofPathNew(subjectPath);
    clpr.AddPaths(subjectP, ptSubject,true);
    //add clip piece
    ClipperLib::Paths clipP;
    clipP=getClipperPathsFromofPathNew(clipPath);
    clpr.AddPaths(clipP,ptClip,true);
    // excute
    ClipperLib::Paths output;
    clpr.Execute(clipType, output, pftEvenOdd, pftEvenOdd);
    clpr.Clear();
    
    return getofPathFromClipperPathNew(output);
    
}
// ofPath in
// ofPath -> ofPolyline |
// ofPath -> getCommands -> ofPolyline |getPolylinesFromPath
// ofPolyline ->polyPoints-> clipper::paths |getClipperPathFromPolyline
// clipper::path out
// execute

