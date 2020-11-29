#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__

#include "Module.h"
#include "Point.h"

#include "SDL/include/SDL_scancode.h"

#define NUM_MOUSE_BUTTONS 5

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum MouseWheel
{
	SCROOL_UP = 0,
	SCROOL_DOWN,
	SCROOL_STAY
};

class ModuleInput : public Module
{

public:


	ModuleInput();
	virtual ~ModuleInput();
	bool Init();
	bool Start();

	update_status PreUpdate();

	bool CleanUp();
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	MouseWheel GetScrool() const
	{
		return scr;
	}

	bool GetWindowEvent(EventWindow code) const;

	// Get mouse / axis position
	const float2& GetMousePosition() const;
	const float2& GetMouseMotion() const;
	std::string dropped_filedir;

private:
	bool		windowEvents[WE_COUNT];
	KeyState*	keyboard;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	float2 mouse_motion;
	float2 mouse;
	MouseWheel scr;
};

#endif // __MODULEINPUT_H__