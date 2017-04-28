#include "Scene.h"

Scene::Scene() {}
Scene::~Scene() {}

bool						Scene::isKeyToLaunch(int key) const
{
	return (static_cast<int>(this->keysToLaunch.first) == key || static_cast<int>(this->keysToLaunch.second) == key);
}

void						Scene::WindowSizeChanged(int newWidth, int newHeight)
{
	this->windowWidth = newWidth;
	this->windowHeight = newHeight;
}

void						Scene::setLastKey(int newKey)
{
	this->lastKeyPressed = newKey;
}

std::pair<char, char>		Scene::getKeysToLaunch() const
{
	return this->keysToLaunch;
}

void						Scene::Quit()
{
	this->hasQuit = true;
}