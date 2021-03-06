#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleIMGUI.h"
#include "ModuleCamera.h"
#include "Leaks.h"
ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	App->imgui->AddLog("Init SDL window & surface\n");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		App->imgui->AddLog("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window

		flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
		SDL_DisplayMode disMode;
		SDL_GetCurrentDisplayMode(0, &disMode);
		disScreenWidthMax = disMode.w;
		disScreenHeightMax = disMode.w;
		disScreenWidthMin = width = disMode.w / aspect;
		disScreenHeightMin = height = disMode.h / aspect;

		if (FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == NULL)
		{
			App->imgui->AddLog("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface

			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

void ModuleWindow::Rescale(unsigned int newWidth, unsigned int newHeight)
{
	width = newWidth;
	height = newHeight;
}


// Called before quitting
bool ModuleWindow::CleanUp()
{
	App->imgui->AddLog("Destroying SDL window and quitting all SDL systems\n");

	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

