#include				"Illumination.h"

Illumination::Illumination()
{
	this->keysToLaunch.first = 'i';
	this->keysToLaunch.second = 'I';
}

Illumination::~Illumination()
{
	if (!this->hasBeenStarted) return;

	delete this->lightAmbient;
	delete this->lightDirectional;
	delete this->lightPoint;
	delete this->lightSpot;

	delete this->material1;
	delete this->material2;
	delete this->material3;

	delete this->teapot;
}

void					Illumination::Setup(int width, int height)
{
	if (this->hasBeenStarted)
	{
		fbo.begin();
		ofClear(0, 0, 0, 0);
		fbo.end();
		return;
	}
	
	dl_quaternion = new ofQuaternion();
	sl_quaternion = new ofQuaternion();
	tp_quaternion = new ofQuaternion();
	bx_quaternion = new ofQuaternion();
	teapot = new ofxAssimpModelLoader();
	teapot->loadModel("models/teapot.obj");

	lightAmbient = new ofColor();
	lightDirectional = new ofLight();
	lightPoint = new ofLight();
	lightSpot = new ofLight();

	material1 = new ofMaterial();
	material2 = new ofMaterial();
	material3 = new ofMaterial();

	// configuration materiaux
	material1->setAmbientColor(ofColor(63, 63, 63));
	material1->setDiffuseColor(ofColor(127, 0, 0));
	material1->setEmissiveColor(ofColor(31, 0, 0));
	material1->setSpecularColor(ofColor(127, 127, 127));
	material1->setShininess(16.0f);

	material2->setAmbientColor(ofColor(63, 63, 63));
	material2->setDiffuseColor(ofColor(191, 63, 0));
	material2->setEmissiveColor(ofColor(0, 31, 0));
	material2->setSpecularColor(ofColor(255, 255, 64));
	material2->setShininess(8.0f);

	material3->setAmbientColor(ofColor(63, 63, 63));
	material3->setDiffuseColor(ofColor(63, 0, 63));
	material3->setEmissiveColor(ofColor(0, 0, 31));
	material3->setSpecularColor(ofColor(191, 191, 191));
	material3->setShininess(8.0f);

	// configurer la lumière directionnelle
	lightDirectional->setDiffuseColor(ofColor(31, 255, 31));
	lightDirectional->setSpecularColor(ofColor(191, 191, 191));
	lightDirectional->setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
	lightDirectional->setDirectional();

	// configurer la lumière ponctuelle
	lightPoint->setDiffuseColor(ofColor(255, 255, 255));
	lightPoint->setSpecularColor(ofColor(191, 191, 191));
	lightPoint->setAttenuation(0, 0, 0.0001);
	lightPoint->setPointLight();

	// configurer la lumière projecteur
	lightSpot->setDiffuseColor(ofColor(191, 191, 191));
	lightSpot->setSpecularColor(ofColor(191, 191, 191));
	lightSpot->setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
	lightSpot->setSpotConcentration(2);
	lightSpot->setSpotlightCutOff(30);
	lightSpot->setAttenuation(0, 0, 0.0001);
	lightSpot->setSpotlight();

	// GUI
	this->selectedObject = AMBIANTLIGHT; // default

	this->guiAmbiantLight.setup("Ambiant");
	this->guiLight.setup("Light");
	this->guiAdvancedLight.setup("AdvancedLight");
	this->guiObject.setup("Object");

	this->al_color = ofColor(50);

	this->pl_position = ofVec3f(576, 275, 408);
	this->pl_color = ofVec3f(255, 0, 0);
	this->pl_attenuation = 0.0001;

	this->dl_rotation = ofVec3f(78, 0, 0);
	this->dl_color = ofVec3f(0, 255, 0);

	this->sl_position = ofVec3f(510, 326, 525);
	this->sl_rotation = ofVec3f(78, 0, 0);
	this->sl_color = ofVec3f(0, 0, 255);
	this->sl_attenuation = 0.0001;

	this->tp_position = ofVec3f(510, 390, 560);
	this->tp_rotation = ofVec3f(0, 0, 0);
	this->tp_scale = ofVec3f(0.07, 0.07, 0.07);
	this->tp_material1 = true;
	this->tp_material2 = false;
	this->tp_material3 = false;

	this->bx_position = ofVec3f(510, 390, 550);
	this->bx_rotation = ofVec3f(0);
	this->bx_scale = 15;
	this->bx_material1 = false;
	this->bx_material2 = true;
	this->bx_material3 = false;
	this->SelectAmbiantLight(this->selectedObject);
}

static string			getObjectString(ObjectType type)
{
	string				objectNames[] = {	"AmbiantLight", "PointLight",
											"DirectionLight", "SpotLight",
											"Teapot", "Box" };
	return (objectNames[type]);
}

void					Illumination::SelectAmbiantLight(ObjectType type)
{
	this->guiAmbiantLight.clear();
	this->guiAmbiantLight.add(al_color.set("ambiant light color", al_color, ofColor(0), ofColor(255)));
	this->activeGUI = &this->guiAmbiantLight;
}

void					Illumination::SelectLight(ObjectType type)
{
	this->guiLight.clear();
	
	if (type == POINTLIGHT)
	{
		this->guiLight.add(pl_position.set("point light position", pl_position, ofVec3f(0), ofVec3f(1000)));
		this->guiLight.add(pl_color.set("point light color", pl_color, ofVec3f(0, 0, 0), ofVec3f(1, 1, 1)));
		this->guiLight.add(pl_attenuation.set("attenuation", pl_attenuation, 0.00001, 0.001));
	}
	else if (type == DIRECTIONLIGHT)
	{
		this->guiLight.add(dl_rotation.set("direction light rotation", dl_rotation, ofVec3f(-180), ofVec3f(180)));
		this->guiLight.add(dl_color.set("direction light color", dl_color, ofVec3f(-5, -5, -5), ofVec3f(1, 1, 1)));
	}
	this->activeGUI = &this->guiLight;
}

void					Illumination::SelectAdvancedLight(ObjectType type)
{
	this->guiAdvancedLight.clear();
	this->guiAdvancedLight.add(sl_position.set("spot light position", sl_position, ofVec3f(0), ofVec3f(1000)));
	this->guiAdvancedLight.add(sl_rotation.set("spot light rotation", sl_rotation, ofVec3f(-180), ofVec3f(180)));
	this->guiAdvancedLight.add(sl_color.set("spot light color", sl_color, ofVec3f(-5, -5, -5), ofVec3f(5, 5, 5)));
	this->guiAdvancedLight.add(sl_attenuation.set("spot light attenuation", sl_attenuation, 0.00001, 0.001));
	this->activeGUI = &this->guiAdvancedLight;
}

void					Illumination::SelectObject(ObjectType type)
{
	this->guiObject.clear();
	if (type == TEAPOT)
	{
		this->guiObject.add(tp_position.set("Teapot position ", tp_position, ofVec3f(0), ofVec3f(1000)));
		this->guiObject.add(tp_rotation.set("Teapot rotation", tp_rotation, ofVec3f(-180), ofVec3f(180)));
		this->guiObject.add(tp_scale.set("Teapot scale", tp_scale, ofVec3f(0), ofVec3f(15)));
		this->guiObject.add(tp_material1);
		this->guiObject.add(tp_material2);
		this->guiObject.add(tp_material3);
	}
	else if (type == BOX)
	{
		this->guiObject.add(bx_position.set("Box position ", bx_position, ofVec3f(0), ofVec3f(1000)));
		this->guiObject.add(bx_rotation.set("Box rotation", bx_rotation, ofVec3f(-180), ofVec3f(180)));
		this->guiObject.add(bx_scale.set("Box scale", bx_scale, 0, 15));
		this->guiObject.add(bx_material1);
		this->guiObject.add(bx_material2);
		this->guiObject.add(bx_material3);
	}
	this->activeGUI = &this->guiObject;
}

void					Illumination::Update()
{
	ofSetWindowTitle("Illumination demo (" + getObjectString(this->selectedObject) + " selected, press \"A\", \"P\", \"D\", \"S\", \"T\", \"B\" to select another object and \"Q\" to quit)");
	*lightAmbient = this->al_color;

	ofPushMatrix();
	dl_quaternion->makeRotate(dl_rotation->x, ofVec3f(1, 0, 0), dl_rotation->y, ofVec3f(0, 1, 0), dl_rotation->z, ofVec3f(0, 0, 1));
	lightDirectional->setPosition(0,0,0);
	lightDirectional->setOrientation(*dl_quaternion);

	lightPoint->setPosition(this->pl_position);
	lightPoint->setAttenuation(0, 0, this->pl_attenuation);

	sl_quaternion->makeRotate(sl_rotation->x, ofVec3f(1, 0, 0), sl_rotation->y, ofVec3f(0, 1, 0), sl_rotation->z, ofVec3f(0, 0, 1));
	lightSpot->setOrientation(*sl_quaternion);
	lightSpot->setPosition(sl_position->x, sl_position->y, sl_position->z);
	lightSpot->setAttenuation(0, 0, this->sl_attenuation);
	ofPopMatrix();

	// keys
	if (this->lastKeyPressed == 0) return;
	switch (this->lastKeyPressed)
	{
	case 'a': case 'A': 
		this->SelectAmbiantLight(AMBIANTLIGHT);
		break;
	case 'p': case 'P':
		this->SelectLight(POINTLIGHT);
		break;
	case 'd': case 'D':
		this->SelectLight(DIRECTIONLIGHT);
		break;
	case 's': case 'S':
		this->SelectAdvancedLight(SPOTLIGHT);
		break;
	case 't': case 'T': // I have NO idea why this call provoques a warning
		this->SelectObject(TEAPOT);
		break;
	case 'b': case 'B': // same here
		this->SelectObject(BOX);
		break;
	default:
		break;
	}
	if (this->lastKeyPressed == static_cast<int>('Q') || this->lastKeyPressed == static_cast<int>('q')) this->Quit();
}

void					Illumination::LightsOn()
{
	ofSetGlobalAmbientColor(*this->lightAmbient);
	lightDirectional->enable();
	lightPoint->enable();
	lightSpot->enable();
}

void					Illumination::LightsOff()
{
	ofSetGlobalAmbientColor(ofColor(0, 0, 0));
	lightDirectional->disable();
	lightPoint->disable();
	lightSpot->disable();
}

void					Illumination::Draw()
{
	ofMaterial			*tmp = material1; // default

	this->fbo.begin();
	ofBackground(0);

	ofPushMatrix();// afficher un repère visuel pour les lumières
	lightPoint->draw();
	lightDirectional->draw();
	lightSpot->draw();
	ofPopMatrix();

	ofPushMatrix();
	// position
	ofTranslate(bx_position);
	ofEnableLighting();
	LightsOn();
	// activer le matériau
	
	if (bx_material1) tmp = material1;
	if (bx_material2) tmp = material2;
	if (bx_material3) tmp = material3;
	tmp->begin();
	ofDrawBox(0, 0, 0, this->bx_scale);
	tmp->end();
	LightsOff();
	// désactiver l'éclairage dynamique
	ofDisableLighting();
	ofPopMatrix();

	ofPushMatrix();

	// position
	teapot->setPosition(tp_position->x, tp_position->y, tp_position->z);
	// rotation locale
	//teapot->setRotation(0, ofGetFrameNum() * -1.0f, 0, 1, 0);
	// dimension
	teapot->setScale(tp_scale->x, tp_scale->y, tp_scale->y);
	teapot->disableMaterials();

	// activer l'éclairage dynamique
	ofEnableLighting();
	// activer les lumières
	LightsOn();

	if (tp_material1) tmp = material1;
	if (tp_material2) tmp = material2;
	if (tp_material3) tmp = material3;
	// activer le matériau
	tmp->begin();
	teapot->draw(OF_MESH_FILL);
	tmp->end();

	// désactiver les lumières
	LightsOff();

	// désactiver l'éclairage dynamique
	ofDisableLighting();

	ofPopMatrix();

	this->fbo.end();
	this->fbo.draw(0,0);
	this->activeGUI->draw();
}