#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    path = new ofxSuperPath();
    path->reset();
    
    marking = NULL;
    brush = NULL;
    paint = NULL;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(marking != NULL)
    {
        marking->update();
    }
    
    for(int i = 0; i < markings.size(); i++)
    {
        markings[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    if(marking != NULL)
    {
        marking->draw();
    }
    
    for(int i = 0; i < markings.size(); i++)
    {
        markings[i]->draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit()
{
    for(int i = 0; i < markings.size(); i++)
    {
        delete markings[i];
    }
    markings.clear();
    
    if(marking != NULL)
    {
        delete marking;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    path->lineTo(x,y,0, ofFloatColor(0), ofGetFrameNum(), 0);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    path = new ofxSuperPath();
    paint = new ofxPaint(path, ofColor(255), 100);
    brush = new ofxKineticBrush(path, paint);
    brush->setDynamic(true);
    brush->setSpeed(6);
    brush->setUseAcceleration(false);
    brush->setSpeedIncrement(1.0);
    
    marking = new ofxMarking(path, paint, brush);
    path->reset();
    path->lineStart(x,y,0, ofFloatColor(0), ofGetFrameNum(), 0);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    path->lineEnd(x,y,0, ofGetFrameNum(), -1, 0);
    marking->pathFinished();
    markings.push_back(marking);
    marking = NULL;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
