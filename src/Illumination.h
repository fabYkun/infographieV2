#pragma once
#include					"ofMain.h"
#include					"ofxGui.h"
#include					"ofxAssimpModelLoader.h"
#include					"Scene.h"

enum						ObjectType
{
	AMBIANTLIGHT = 0,
	POINTLIGHT,
	DIRECTIONLIGHT,
	SPOTLIGHT,
	TEAPOT,
	BOX
};

class						Illumination : public Scene
{
public:
	Illumination();
	~Illumination();

	void					Setup(int width, int height);
	void					Draw();
	void					Update();

private:
	void					SelectAmbiantLight(ObjectType);
	void					SelectLight(ObjectType);
	void					SelectAdvancedLight(ObjectType);
	void					SelectObject(ObjectType);
	void					LightsOn();
	void					LightsOff();

	ofColor					*lightAmbient;
	ofLight					*lightDirectional;
	ofLight					*lightPoint;
	ofLight					*lightSpot;

	ofQuaternion			*dl_quaternion;
	ofQuaternion			*sl_quaternion;
	ofQuaternion			*tp_quaternion;
	ofQuaternion			*bx_quaternion;

	ofMaterial				*material1;
	ofMaterial				*material2;
	ofMaterial				*material3;

	ofxAssimpModelLoader	*teapot;

	ObjectType				selectedObject;

	ofxPanel				*activeGUI;
	ofxPanel				guiAmbiantLight;
	ofxPanel				guiLight;
	ofxPanel				guiAdvancedLight;
	ofxPanel				guiObject;

	// ambiant light
	ofParameter<ofColor>	al_color;

	// point light
	ofParameter<ofVec3f>	pl_position;
	ofParameter<ofVec3f>	pl_color;
	ofParameter<float>		pl_attenuation;

	// direction light
	ofParameter<ofVec3f>	dl_rotation;
	ofParameter<ofVec3f>	dl_color;

	// spot light
	ofParameter<ofVec3f>	sl_position;
	ofParameter<ofVec3f>	sl_rotation;
	ofParameter<ofVec3f>	sl_color;
	ofParameter<float>		sl_attenuation;

	// teapot
	ofParameter<ofVec3f>	tp_position;
	ofParameter<ofVec3f>	tp_rotation;
	ofParameter<ofVec3f>	tp_scale;
	ofParameter<bool>		tp_material1;
	ofParameter<bool>		tp_material2;
	ofParameter<bool>		tp_material3;

	// box
	ofParameter<ofVec3f>	bx_position;
	ofParameter<ofVec3f>	bx_rotation;
	ofParameter<float>		bx_scale;
	ofParameter<bool>		bx_material1;
	ofParameter<bool>		bx_material2;
	ofParameter<bool>		bx_material3;
};

