#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class Program;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleCamera* Camera = nullptr;
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	Program* program = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
