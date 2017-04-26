#include		"ofMain.h"
#include		"ofApp.h"

int				main()
{
	ofGLWindowSettings windowSettings;

	windowSettings.width = 1024;
	windowSettings.height = 768;

	// uncomment to use 120GLSL shader version
	//windowSettings.setGLVersion(2, 1);

	// uncomment to use 330GLSL shader version
	windowSettings.setGLVersion(3, 3);

	ofCreateWindow(windowSettings);
	ofRunApp(new ofApp());
}
