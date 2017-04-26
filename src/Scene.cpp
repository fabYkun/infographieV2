#include "Scene.h"

Scene::Scene() {}
Scene::~Scene() {}

bool				Scene::isKeyToLaunch(int key) const
{
	return (static_cast<int>(this->keysToLaunch.first) == key || static_cast<int>(this->keysToLaunch.second) == key);
}

void				Scene::WindowSizeChanged(int newWidth, int newHeight)
{
	this->windowHeight = newHeight;
	this->windowWidth = newWidth;
}

void				Scene::setLastKey(int newKey)
{
	this->lastKeyPressed = newKey;
}