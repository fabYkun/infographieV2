#include						"Hub.h"
#include						"RaysRenderer.h"
#include						"Illumination.h"

Hub::Hub() : activeScene(NULL)
{}

Hub::~Hub()
{}

void							Hub::Setup(int width, int height)
{
	Scene						*Raytracer = new RaysRenderer();
	Scene						*IlluminationRenderer = new Illumination();

	this->scenes[Raytracer->getKeysToLaunch().first] = Raytracer;
	this->scenes[Raytracer->getKeysToLaunch().second] = Raytracer;
	this->scenes[IlluminationRenderer->getKeysToLaunch().first] = IlluminationRenderer;
	this->scenes[IlluminationRenderer->getKeysToLaunch().second] = IlluminationRenderer;

	this->windowWidth = width;
	this->windowHeight = height;
}

void							Hub::Update()
{
	if (this->activeScene == NULL && this->scenes[this->lastKeyPressed])
	{
		this->activeScene = this->scenes[this->lastKeyPressed];
		this->activeScene->Setup(this->windowWidth, this->windowHeight);
	}
	if (this->activeScene != NULL)
		if (this->activeScene->hasQuit)
		{
			this->activeScene->hasQuit = false;
			this->activeScene = NULL;
		}
		else
			return this->activeScene->Update();
}

void							Hub::Draw()
{
	if (this->activeScene != NULL) return this->activeScene->Draw();
	this->fbo.begin();
	ofClear(25, 22, 23);
	ofSetColor(238, 57, 135);
	ofDrawBitmapString("Press the following buttons to access scenes", 30, 30);
	ofSetColor(192, 192, 192);
	ofDrawBitmapString("R : Raytracing/Raymarching scene", 45, 60);
	ofDrawBitmapString("I : Illumination scene", 45, 80);
	this->fbo.end();
	this->fbo.draw(0,0);
}

void							Hub::setLastKey(int newKey)
{
	this->lastKeyPressed = newKey;
	for (std::map<char, Scene *>::iterator it = this->scenes.begin(); it != this->scenes.end(); ++it)
		if (it->second != NULL) it->second->setLastKey(this->lastKeyPressed);
}

void							Hub::Quit()
{
	Scene						*scene;

	for (std::map<char, Scene *>::iterator it = this->scenes.begin(); it != this->scenes.end(); ++it)
		if ((scene = it->second) != NULL)
		{
			if (scene && !scene->hasQuit) scene->Quit();
			this->scenes[scene->getKeysToLaunch().first] = NULL;
			this->scenes[scene->getKeysToLaunch().second] = NULL;
			delete scene;
		}
	this->hasQuit = true;
}

void							Hub::WindowSizeChanged(int newWidth, int newHeight)
{
	this->windowWidth = newWidth;
	this->windowHeight = newHeight;
	for (std::map<char, Scene *>::iterator it = this->scenes.begin(); it != this->scenes.end(); ++it)
		if (it->second != NULL) it->second->WindowSizeChanged(this->windowWidth, this->windowHeight);
}