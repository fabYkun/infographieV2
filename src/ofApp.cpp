#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	this->hub.Setup(ofGetScreenWidth(), ofGetScreenHeight());
}

//--------------------------------------------------------------
void ofApp::update()
{
	this->hub.Update();
	this->hub.setLastKey(0);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	this->hub.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	this->hub.setLastKey(key);
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
	this->hub.WindowSizeChanged(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
