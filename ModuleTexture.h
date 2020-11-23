#pragma once
#include "Module.h"
#include "Globals.h"
#include <GL/glew.h>
#include "MathGeoLib/Math/float4x4.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include <IL/il.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_main.h>
#include <IL/il.h>

#include <GL/gl.h>
class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	GLuint image;
	ILuint texid;
private:
	SDL_Event event;
	//ILuint texid;
	ILboolean success;
	//GLuint image;
	int finished;
	void* context;
};

