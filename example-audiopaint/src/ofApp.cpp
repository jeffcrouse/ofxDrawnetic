#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    inputbufferSize = 256;
    
    buffer = new float[inputbufferSize];
    
    soundStream.setup(this, 0, 2, 44100, inputbufferSize, 2);
    
    path = new ofxSuperPath();
    path->reset();
    
    marking = NULL;
    brush = NULL;
    paint = NULL;
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < markings.size(); i++)
    {
        markings[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    for(int i = 0; i < markings.size(); i++)
    {
        markings[i]->draw();
    }
    
    if(marking != NULL)
    {
        marking->draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    for(int i = 0; i < markings.size(); i++)
    {
        delete markings[i];
    }
    markings.clear();
    
    if(marking != NULL)
    {
        delete marking;
    }
    delete[] buffer;
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
    paint = new ofxAudioPaint(path, ofColor(ofRandom(255),ofRandom(255),ofRandom(255)), buffer, inputbufferSize);
    paint->setEffectHue(true);
    paint->setRange(50);
    
    brush = new ofxKineticBrush(path, paint);
    brush->setDynamic(true);
    brush->setSpeed(6);
    brush->setUseAcceleration(false);
    
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

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels)
{
    for (int i = 0; i < bufferSize; i++)
    {
        buffer[i] = input[i*nChannels] + input[i*nChannels +1];
    }
}
