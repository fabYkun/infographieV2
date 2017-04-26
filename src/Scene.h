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
	virtual void			Quit() = 0;
	
	bool					isKeyToLaunch(int) const;
	void					setLastKey(int);
	
	virtual void			WindowSizeChanged(int, int);  // < -- change window size must be implemented

protected:
	ofFbo					fbo;
	std::pair<char, char>	keysToLaunch; // ascii code
	int						windowWidth;
	int						windowHeight;
	int						lastKeyPressed;
};

