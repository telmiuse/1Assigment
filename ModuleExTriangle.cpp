#include "ModuleExTriangle.h"
#include "GL/glew.h"
#include "Application.h"
#include "program.h"
#include "ModuleTexture.h"
#include "IL/il.h"
#include "MathGeoLib/Math/float4x4.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModuleModelo.h"


void __stdcall OurOpenGLErrorFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	const char* tmp_source = "", * tmp_type = "", * tmp_severity = "";
	switch (source) {
	case GL_DEBUG_SOURCE_API: tmp_source = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: tmp_source = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: tmp_source = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: tmp_source = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION: tmp_source = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER: tmp_source = "Other"; break;
	};
	switch (type) {
	case GL_DEBUG_TYPE_ERROR: tmp_type = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: tmp_type = "Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: tmp_type = "Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY: tmp_type = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: tmp_type = "Performance"; break;
	case GL_DEBUG_TYPE_MARKER: tmp_type = "Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP: tmp_type = "Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP: tmp_type = "Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER: tmp_type = "Other"; break;
	};
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH: tmp_severity = "high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: tmp_severity = "medium"; break;
	case GL_DEBUG_SEVERITY_LOW: tmp_severity = "low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: tmp_severity = "notification"; break;
	};
	LOG("<Source:%s> <Type:%s> <Severity:%s> <ID:%d> <Message:%s>\n", tmp_source, tmp_type, tmp_severity, id, message);

}




ModuleExTriangle::ModuleExTriangle()
{

}

// Destructor
ModuleExTriangle::~ModuleExTriangle()
{
	glDeleteBuffers(1, &vbo);
}

// Called before render is available
bool ModuleExTriangle::Init()
{

	LOG("Creating Renderer context");

//	SDL_GL_CreateContext(App->window->window);
	glDebugMessageCallback(&OurOpenGLErrorFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
	
	vbo = CreateTriangleVBO();
	vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, (App->program->LoadShaderSource("vertex.glsl")));
	frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, (App->program->LoadShaderSource("fragment.glsl")));
	program = App->program->CreateProgram(vtx_shader, frg_shader);
	

	//glUseProgram(program);

	return true;
}


unsigned ModuleExTriangle:: CreateTriangleVBO() {
	
	float buffer_data[] = {
		-1.0f, -1.0f, 0.0f, // ← v0 pos
		 1.0f, -1.0f, 0.0f, // ← v1 pos
		 0.0f, 1.0f, 0.0f, // ← v2 pos
		 0.0f, 0.0f, // ← v0 texcoord
		 1.0f, 0.0f, // ← v1 texcoord
		 0.5f, 1.0f // ← v2 texcoord
	};
	unsigned vbo;
	glGenBuffers(1, &vbo); //creates memory in graphic card
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	return vbo;
}
update_status ModuleExTriangle::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleExTriangle::Update()
{
	App->modelo->Draw();
	return UPDATE_CONTINUE;
}

// Called every draw update
void ModuleExTriangle::RenderTriangle()
{
/*
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 1 triangle to draw = 3 vertices
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(float) * 3 * 3));// buffer offset






	glUseProgram(program);
	float4x4 proj = App->Camera->GetProjection();
	float4x4 view = App->Camera->GetView();
	float4x4 model = float4x4::identity;



	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]); //GL_TRUE transpose the matrix
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &proj[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, App->texture->image);
	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
		*/

	App->modelo->Draw();
}

update_status ModuleExTriangle::PostUpdate()
{

	//SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleExTriangle::CleanUp()
{
	LOG("Destroying renderer");
	glDeleteBuffers(1, &vbo);
	//Destroy window


	return true;
}