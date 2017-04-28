#pragma once
#include					"ofxGui.h"
#include					"ofxCubeMap.h"
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

	ofxPanel				guiRaytracer;
	ofxPanel				guiRaymarching;

private:
	Shaders					activeShader;
	ofShader				*shader;
	ofShader				*shaderRaytracing;
	ofShader				*shaderRaymarching;
	string					shaderVersion;
	string					currentShaderName() const;

	ofxCubeMap				cubeMap;

	int						glVersionMajor;
	int						glVersionMinor;

	void					SwitchDemo();

	ofParameter<ofVec3f>	colorSphere;

	ofParameter<float>		radius;
	ofParameter<float>		size;

	ofParameter<float>		reflexion_sphere;
	ofParameter<float>		reflexion_cube;
	ofParameter<float>		reflexion_plan;
	ofParameter<float>		reflexion;

	ofParameter<float>		intLight;
	ofParameter<ofVec2f>	speLight;
	ofParameter<ofVec3f>	colLight;
	ofParameter<float>		ambient;
	ofParameter<ofVec3f>	posSphere;
	ofParameter<ofVec3f>	posLight;

	ofParameter<float>		torusRotation;
};

