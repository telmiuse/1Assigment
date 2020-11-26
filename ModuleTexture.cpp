#include "ModuleTexture.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_main.h>
#include <IL/il.h>
#include <GL/gl.h>
#include <GL/glew.h>
#include "MathGeoLib/Geometry/Frustum.h"

ModuleTexture::ModuleTexture()
{

}

// Destructor
ModuleTexture::~ModuleTexture()
{
}


unsigned int ModuleTexture::LoadTexture(const char* path) {

	///ilInit(); /* Initialization of DevIL */
	ilGenImages(1, &texid); /* Generation of one image name */
	ilBindImage(texid); /* Binding of image name */
	success = ilLoadImage(path); /* Loading of image "image.jpg" */
	ILenum Error;
	while ((Error = ilGetError()) != IL_NO_ERROR) {
		//LOG("%d: s/n ", Error, gluErrorString(Error));
	}

	if (success) /* If no error occured: */
	{
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into
		  unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		if (!success)
		{
			/* Error occured */
			SDL_Quit();
			return -1;
		}
		glGenTextures(1, &image); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, image); /* Binding of texture name */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear
		  interpolation for magnification filter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear
		  interpolation for minifying filter */
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
			ilGetData()); /* Texture specification */
	}
	else {
		return false;
	}
	ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data
	 // we can release memory used by image. */
	return image;
}
// Called before render is available
bool ModuleTexture::Init()
{

	ilInit(); /* Initialization of DevIL */
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	
	return true;
}

update_status ModuleTexture::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleTexture::Update()
{
	



	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleTexture::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(App->window->window);

	return true;
}



