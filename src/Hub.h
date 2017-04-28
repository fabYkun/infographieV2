#pragma once
#include					<map>
#include					"ofxGui.h"
#include					"Scene.h"

class						Hub : public Scene
{
public:
	Hub();
	~Hub();

	void					Setup(int width, int height);
	void					Update();
	void					Draw();
	void					Quit();

	void					setLastKey(int);
	void					WindowSizeChanged(int newWidth, int newHeight);

private:
	std::map<char, Scene *>	scenes;
	Scene					*activeScene;
};