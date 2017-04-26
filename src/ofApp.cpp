#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	this->raysRenderer.Setup(ofGetScreenWidth(), ofGetScreenHeight());
}

//--------------------------------------------------------------
void ofApp::update()
{
	this->raysRenderer.Update();
	this->raysRenderer.setLastKey(0);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	this->raysRenderer.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	this->raysRenderer.setLastKey(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	this->raysRenderer.WindowSizeChanged(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
