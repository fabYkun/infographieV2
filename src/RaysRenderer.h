#pragma once
#include					"ofxGui.h"
#include					"Scene.h"

enum						Shaders
{
	RAYTRACING = 0,
	RAYMARCHING
};

class						RaysRenderer : public Scene
{
public:
	RaysRenderer();
	~RaysRenderer();

	void					Setup(int width, int height);
	void					Draw();
	void					Update();
	void					Quit();

	ofxPanel				guiRaytracer;
	ofxPanel				guiRaymarching;

private:
	Shaders					activeShader;
	ofShader				*shader;

	ofShader				*shaderRaytracing;
	ofShader				*shaderRaymarching;

	string					shaderVersion;
	string					currentShaderName() const;

	int						glVersionMajor;
	int						glVersionMinor;

	void					SwitchDemo();

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

	ofParameter<float>		torusRotation;
};

