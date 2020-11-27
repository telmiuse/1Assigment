#ifndef __Program_H__
#define __Program_H__

#include "Module.h"
#include "Globals.h"
#include <GL/glew.h>


class Application;
class Program : public Module
{

public:

	Program();
	~Program();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);


	GLuint program;
	GLuint ProgramID;

};
#endif // __Program_H__