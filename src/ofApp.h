#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxPanel				gui;
		ofParameter<ofVec3f>	colorSphere;
		ofParameter<ofVec3f>	colorCube;

		ofParameter<float>		radius;
		ofParameter<float>		size;

		ofParameter<float>		reflexion_sphere;
		ofParameter<float>		reflexion_cube;
		ofParameter<float>		reflexion_plan;

		ofParameter<float>		intLight;
		ofParameter<ofVec2f>	speLight;
		ofParameter<ofVec3f>	colLight;
		ofParameter<float>		ambient;
		ofParameter<ofVec3f>	posSphere;
		ofParameter<ofVec3f>	posCube;
		ofParameter<ofVec3f>	posLight;

		ofFbo fbo;
		int w, h;
		ofShader trace;
		
};
