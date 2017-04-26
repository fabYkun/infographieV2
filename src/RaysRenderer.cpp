#include				"RaysRenderer.h"


RaysRenderer::RaysRenderer()
{
	this->keysToLaunch.first = 'r';
	this->keysToLaunch.second = 'R';
}

RaysRenderer::~RaysRenderer()
{}

void					RaysRenderer::Setup(int width, int height)
{
	cubeMap.loadImages(	"textures/cubemaps/cubemap1.png",
		"textures/cubemaps/cubemap4.png",
		"textures/cubemaps/cubemap3.png",
		"textures/cubemaps/cubemap6.png",
		"textures/cubemaps/cubemap5.png",
		"textures/cubemaps/cubemap2.png");

	this->fbo.allocate(width, height);
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();

	if (ofIsGLProgrammableRenderer())
	{
		this->glVersionMajor = 3;
		this->glVersionMinor = 3;
	}
	else
	{
		this->glVersionMajor = 2;
		this->glVersionMinor = 1;
	}

	this->shaderRaymarching = new ofShader();
	this->shaderRaytracing = new ofShader();
	this->shaderVersion = this->glVersionMajor == 3 ? "V330" : "V120";
	this->shaderRaymarching->load(
		"shaders/" + this->shaderVersion + "/raymarching/vertex.hlsl",
		"shaders/" + this->shaderVersion + "/raymarching/frag.hlsl");
	this->shaderRaytracing->load(
		"shaders/" + this->shaderVersion + "/raytracing/vertex.hlsl",
		"shaders/" + this->shaderVersion + "/raytracing/frag.hlsl");
	this->activeShader = Shaders::RAYMARCHING;
	this->shader = this->shaderRaymarching;

	this->guiRaytracer.setup();
	this->guiRaytracer.add(colorSphere.set("color sphere", ofVec3f(0, 0.6, 0), ofVec3f(0.), ofVec3f(1.)));
	this->guiRaytracer.add(reflexion_sphere.set("reflexion sphere", .385, .0, 1.));
	this->guiRaytracer.add(reflexion_plan.set("reflexion plan", 0.65, .0, 1.));
	this->guiRaytracer.add(radius.set("radius sphere", .8, .0, 10.));
	this->guiRaytracer.add(size.set("size cube", 0.3, .0, 10.));
	this->guiRaytracer.add(speLight.set("specular light", ofVec2f(3.5, 40), ofVec2f(0., 0.), ofVec2f(100., 100.)));
	this->guiRaytracer.add(intLight.set("intensity light", 1.125, .0, 5.));
	this->guiRaytracer.add(colLight.set("color light", ofVec3f(0.2, 0.35, 0.35), ofVec3f(0.), ofVec3f(1.)));
	this->guiRaytracer.add(ambient.set("ambient light", .06, .0, 1.));
	this->guiRaytracer.add(posLight.set("position light", ofVec3f(5., 5., -5.), ofVec3f(-5., -5., -5.), ofVec3f(5., 5., 5.)));
	this->guiRaytracer.add(posSphere.set("position sphere", ofVec3f(.2, -.05, 1.), ofVec3f(-5., -5., -5.), ofVec3f(5., 5., 5.)));

	this->guiRaymarching.setup();
	this->guiRaymarching.add(posLight.set("position light", ofVec3f(5., 5., -5.), ofVec3f(-5., -5., -5.), ofVec3f(5., 5., 5.)));
	this->guiRaymarching.add(colLight.set("color light", ofVec3f(0.2, 0.35, 0.35), ofVec3f(0.), ofVec3f(1.)));
	this->guiRaymarching.add(torusRotation.set("rotation torus", 1, -2., 2.));
	this->guiRaymarching.add(posSphere.set("position sphere", ofVec3f(.2, -.05, 1.), ofVec3f(-5., -5., -5.), ofVec3f(5., 5., 5.)));
	this->guiRaymarching.add(reflexion.set("reflexion", 1, .0, 1.));
}

string					RaysRenderer::currentShaderName() const
{
	string				shaderNames[] = { "Raymarching", "Raytracing" };

	return (shaderNames[this->activeShader]);
}

void					RaysRenderer::SwitchDemo()
{
	this->shader = (this->activeShader == Shaders::RAYMARCHING) ? this->shaderRaytracing : this->shaderRaymarching;
	this->activeShader = (this->activeShader == Shaders::RAYMARCHING) ? Shaders::RAYTRACING : Shaders::RAYMARCHING;
}

void					RaysRenderer::Update()
{
	ofSetWindowTitle(this->currentShaderName() + " demo (" + this->shaderVersion + ") (press \"S\" to switch and \"Q\" to quit)");
	if (this->lastKeyPressed == static_cast<int>('S') || this->lastKeyPressed == static_cast<int>('s')) this->SwitchDemo();
	if (this->lastKeyPressed == static_cast<int>('Q') || this->lastKeyPressed == static_cast<int>('q')) this->Quit();
}

void					RaysRenderer::Draw()
{
	if (this->activeShader == Shaders::RAYMARCHING)
		cubeMap.bind();
	this->shader->begin();

	this->shader->setUniform1f("u_aspect_ratio", this->windowWidth / static_cast<float>(this->windowHeight));
	this->shader->setUniform3f("sphere_position", posSphere->x, posSphere->y, posSphere->z);
	this->shader->setUniform3f("light_position", posLight->x, posLight->y, posLight->z);
	this->shader->setUniform3f("light_color", colLight->x, colLight->y, colLight->z);
	this->shader->setUniform3f("O", 0., 0., -2.);

	if (this->activeShader == Shaders::RAYTRACING)
	{
		this->shader->setUniform1f("sphere_radius", radius);
		this->shader->setUniform1f("sphere_reflexion", reflexion_sphere);
		this->shader->setUniform3f("sphere_color", colorSphere->x, colorSphere->y, colorSphere->z);

		this->shader->setUniform3f("cube_position", ofVec3f(-0.8, 1.6, -1.4));
		this->shader->setUniform1f("cube_size", size);

		this->shader->setUniform3f("plane_position", 0., -.5, 0.);
		this->shader->setUniform3f("plane_normal", 0., 1., 0.043);
		this->shader->setUniform1f("plane_reflexion", reflexion_plan);

		this->shader->setUniform1f("light_intensity", intLight);
		this->shader->setUniform2f("light_specular", speLight->x, speLight->y);

		this->shader->setUniform1f("ambient", ambient);
		fbo.draw(-100, -100);
		this->shader->end();
		this->guiRaytracer.draw();
	}
	else
	{
		this->shader->setUniform1f("torus_rotation", torusRotation);
		this->shader->setUniform1i("envMap", 0);
		this->shader->setUniform1f("time", ofGetElapsedTimeMillis() / 3000.0);
		this->shader->setUniform1f("reflexion", CLAMP((reflexion * -1.0) + 1, 0, 1));
		fbo.draw(-100, -100);
		this->shader->end();
		cubeMap.unbind();
		this->guiRaymarching.draw();
	}
}

void					RaysRenderer::Quit()
{
	/*
	delete this->shaderRaymarching;
	delete this->shaderRaytracing;
	*/
}