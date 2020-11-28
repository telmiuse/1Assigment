#include "ModuleRender.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "MolduleIMGUI.h"
#include "ModuleExTriangle.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleModelo.h"
#include "ModuleTexture.h"
#include "SDL/include/SDL.h"
#include "ImGu/imgui_impl_sdl.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(), mouse({ 0, 0 }), mouse_motion({ 0,0 })
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	//RELEASE_ARRAY(keyboard);
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}



// Called each loop iteration
update_status ModuleInput::PreUpdate()
{
	static SDL_Event event;
	scr = SCROOL_STAY;
	mouse_motion = { 0, 0 };
	memset(windowEvents, false, WE_COUNT * sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if (mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}



	while (SDL_PollEvent(&event) != 0)
	{
		ImGui_ImplSDL2_ProcessEvent(&event); //Sendin input to imgui
		switch (event.type)
		{
		case SDL_QUIT:
			windowEvents[WE_QUIT] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				windowEvents[WE_HIDE] = true;
				break;

				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				windowEvents[WE_SHOW] = true;
				break;
			case SDL_WINDOWEVENT_RESIZED:
				App->window->Rescale(event.window.data1, event.window.data2);
				//App->imgui->AddLogInput("Input: Resize window\n");
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				App->window->Rescale(event.window.data1, event.window.data2);
				//App->imgui->AddLogInput("Input: Resize window\n");
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[event.button.button - 1] = KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[event.button.button - 1] = KEY_UP;
			break;

		case SDL_MOUSEMOTION:
			mouse_motion.x = event.motion.xrel / SCREEN_SIZE;
			mouse_motion.y = event.motion.yrel / SCREEN_SIZE;
			mouse.x = event.motion.x / SCREEN_SIZE;
			mouse.y = event.motion.y / SCREEN_SIZE;
			break;

		case SDL_DROPFILE:
			App->imgui->AddLog("FILE DROPPED from:%s\n", event.drop.file);
			//App->imgui->AddLogInput("Input: Drag & Drop File\n");
			dropped_filedir = event.drop.file;
			if (dropped_filedir.substr(dropped_filedir.find_last_of(".") + 1) == "fbx")
			{
				App->imgui->AddLog("MODEL DROPPED from:%s\n", event.drop.file);
				App->modelo->LoadModel(dropped_filedir.c_str());
				for (unsigned int i = 0; i < App->modelo->meshes.size(); i++)
				{
					App->Triangle->SetUpMesh(App->modelo->meshes[i]);
				}
				App->texture->LoadTexture("Textures/checkers.png");
			}
			else if (dropped_filedir.substr(dropped_filedir.find_last_of(".") + 1) == "png")
			{
				App->imgui->AddLog("TEXTURE DROPPED from:%s\n", event.drop.file);
				Texture text = App->texture->LoadTexture(dropped_filedir.c_str());
				for (int i = 0; i < App->modelo->meshes.size(); i++)
				{
					App->modelo->meshes[i].textures.clear();
					App->modelo->meshes[i].textures.push_back(text);
				}

			}
			else
			{
				App->imgui->AddLog("Not Supported file drop");
			}
			SDL_free(event.drop.file);
			break;
		
		case SDL_MOUSEWHEEL:
			if (event.wheel.y < 0) // scroll up
			{
				scr = SCROOL_UP;
			}
			if (event.wheel.y > 0) // scroll down
			{
				scr = SCROOL_DOWN;
				// Put code for handling "scroll down" here!
			}
			break;

		}
	}



	if (GetWindowEvent(EventWindow::WE_QUIT) == true || GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool ModuleInput::GetWindowEvent(EventWindow ev) const
{
	return windowEvents[ev];
}

const float2& ModuleInput::GetMousePosition() const
{
	return mouse;
}



const float2& ModuleInput::GetMouseMotion() const
{
	return mouse_motion;
}
