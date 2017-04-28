#pragma once
#include					<utility>
#include					"ofMain.h"
#include					"ofGLUtils.h"
#include					"ofFbo.h"

class						Scene
{
public:
	Scene();
	~Scene();

	virtual void			Setup(int width, int height) = 0;
	virtual void			Draw() = 0;
	virtual void			Update() = 0;
	virtual void			Quit();
	
	bool					isKeyToLaunch(int) const;
	virtual void			setLastKey(int);
	std::pair<char, char>	getKeysToLaunch() const;
	
	virtual void			WindowSizeChanged(int, int);
	bool					hasQuit = false;
	bool					hasBeenStarted = false;

protected:
	ofFbo					fbo;
	std::pair<char, char>	keysToLaunch; // ascii code
	int						windowWidth;
	int						windowHeight;
	int						lastKeyPressed;
};

