#pragma once
#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleCamera;
class ModuleExTriangle;
class Program;
class ModuleTexture;
class ModuleEditor;
class ModuleModelo;
class ModuleIMGUI;

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
	ModuleExTriangle* Triangle = nullptr;
	Program* program = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleModelo* modelo = nullptr;
	ModuleIMGUI* imgui = nullptr;

	void RequestBrowser(const char* route);

private:

	std::list<Module*> modules;

};

extern Application* App;
