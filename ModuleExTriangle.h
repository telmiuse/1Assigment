#pragma once
#include "Module.h"
#include "Globals.h"
#include <GL/glew.h>
#include "MathGeoLib/Math/float4x4.h"
#include "MathGeoLib/Geometry/Frustum.h"

class ModuleExTriangle : public Module
{
public:
	ModuleExTriangle();
	~ModuleExTriangle();

	bool Init();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	unsigned CreateTriangleVBO();
	void RenderTriangle();
	GLuint program;

private:
	float3 trianglePos;
	Frustum frustum;
	//GLuint program;
	unsigned vbo;
	GLuint vtx_shader;
	GLuint frg_shader;
	void* context;
};


