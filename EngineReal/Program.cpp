#include "Program.h"
#include <GL/glew.h>
#include "ModuleWindow.h"
#include "SDL.h"
#include "ModuleIMGUI.h"
#include "Application.h"
#include "ModuleExTriangle.h"
#include "Leaks.h"
using namespace std;


Program::Program()
{

}

// Destructor
Program::~Program()
{
}

// Called before render is available
bool Program::Init()
{
	return true;
}

update_status Program::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status Program::Update()
{
	return UPDATE_CONTINUE;
}

update_status Program::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool Program::CleanUp()
{

	return true;


}




char* Program::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}


unsigned Program::CompileShader(unsigned type, const char* source)
{
	GLuint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
			LOG("Log Info: %s", info);
			free(info);
		}
	}
	delete source;
	return shader_id;
}


unsigned Program::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vtx_shader);
	glAttachShader(ProgramID, frg_shader);
	glLinkProgram(ProgramID);
	int res;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(program, len, &written, info);
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);


	return ProgramID;
}
