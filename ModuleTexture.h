#pragma once
#include "Module.h"
#include "Globals.h"
#include <GL/glew.h>
#include "MathGeoLib/Math/float4x4.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_main.h>
#include "IL/il.h"

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
	unsigned int LoadTexture(const char* path);

private:
	SDL_Event event;
	//ILuint texid;
	unsigned int imageID;
	ILboolean success;
//	GLuint image;
	int finished;
	void* context;
};

