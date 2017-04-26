#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->raysRenderer.Setup(ofGetScreenWidth(), ofGetScreenHeight());
	/*
	
	ofSetFrameRate(150);
	trace.load("shaders/v330/raytracing/vertex.hlsl", "shaders/v330/raymarching/frag.hlsl");
	
	w = ofGetScreenWidth();
	h = ofGetScreenHeight();
	fbo.allocate(w, h);
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();

	gui.setup();
	gui.add(colorSphere.set("color sphere", ofVec3f(0,0.6,0), ofVec3f(0.), ofVec3f(1.)));

	gui.add(reflexion_sphere.set("reflexion sphere", .385, .0, 1.));
	gui.add(reflexion_plan.set("reflexion plan", 0.65, .0, 1.));

	gui.add(radius.set("radius sphere", .8, .0, 10.));
	gui.add(size.set("size cube", 0.3, .0, 10.));

	gui.add(speLight.set("specular light", ofVec2f(3.5, 40), ofVec2f(0., 0.), ofVec2f(100., 100.)));
	gui.add(intLight.set("intensity light", 1.125, .0, 5.));
	gui.add(colLight.set("color light", ofVec3f(0.2, 0.35, 0.35), ofVec3f(0.), ofVec3f(1.)));
	gui.add(ambient.set("ambient light", .06, .0, 1.));
	
	gui.add(posLight.set("position light", ofVec3f(5., 5., -5.), ofVec3f(-5., -5., -5.), ofVec3f(5., 5., 5.)));
	gui.add(posSphere.set("position sphere", ofVec3f(.2, -.05, 1.), ofVec3f(-5., -5., -5.), ofVec3f(5., 5., 5.)));
	gui.add(posCube.set("position cube", ofVec3f(-0.8, 1.6, -1.4), ofVec3f(-5., -5., -5.), ofVec3f(5., 5., 5.)));
	*/
}

//--------------------------------------------------------------
void ofApp::update(){
	//ofSetWindowTitle(ofToString(ofGetFrameRate()));
	this->raysRenderer.Update();
	this->raysRenderer.setLastKey(0);
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->raysRenderer.Draw();
	/*
	ofBackgroundGradient(255, 0);

	trace.begin();

	trace.setUniform1f("u_aspect_ratio", w / static_cast<float>(h));
	trace.setUniform3f("sphere_position", posSphere->x, posSphere->y, posSphere->z);
	trace.setUniform1f("sphere_radius", radius);
	trace.setUniform1f("sphere_reflexion", reflexion_sphere);
	trace.setUniform3f("sphere_color", colorSphere->x, colorSphere->y, colorSphere->z);

	trace.setUniform3f("cube_position", posCube->x, posCube->y, posCube->z);
	trace.setUniform1f("cube_size", size);
	trace.setUniform1f("cube_reflexion", reflexion_cube);
	trace.setUniform3f("cube_color", colorCube->x, colorCube->y, colorCube->z);

	trace.setUniform3f("plane_position", 0., -.5, 0.);
	trace.setUniform3f("plane_normal", 0., 1., 0.043);
	trace.setUniform1f("plane_reflexion", reflexion_plan);

	trace.setUniform1f("light_intensity", intLight);
	trace.setUniform2f("light_specular", speLight->x, speLight->y);
	trace.setUniform3f("light_position", posLight->x, posLight->y, posLight->z);
	trace.setUniform3f("light_color", colLight->x, colLight->y, colLight->z);
	trace.setUniform1f("ambient", ambient);
	trace.setUniform1f("torus_rotation", 1);
	trace.setUniform3f("O", 0., 0., -1.);

	fbo.draw(-100, -100);

	trace.end();
	gui.draw();
	*/
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
void ofApp::windowResized(int w, int h){
	this->raysRenderer.WindowSizeChanged(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
