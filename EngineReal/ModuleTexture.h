#pragma once
#include "Module.h"
#include "SDL.h"
#include "GL/glew.h"
#include "MathGeoLib/MathGeoLib.h"

#include "IL/il.h"
class ModuleTexture :
	public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();

	Texture LoadTexture(const char*);
	Texture texture;
	std::vector<Texture> textures_loaded;
	bool loaded = NULL;
	int width, height, nrChannels;
	ILuint imageName;
	GLuint texture_object;
	GLuint textureID;
	bool CleanUp();

};

