#include "ModuleCarga.h"
#include "ModuleExTriangle.h"
#include "GL/glew.h"
#include "Globals.h"
#include "Application.h"
#include "program.h"
#include "ModuleTexture.h"
#include "IL/il.h"
#include "MathGeoLib/Math/float4x4.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <postprocess.h>
#include <cimport.h>



ModuleCarga::ModuleCarga()
{

}

// Destructor
ModuleCarga::~ModuleCarga()
{

}

void ModuleCarga::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		// TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);
		// TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		//LOG("Error loading %s: %s", file, aiGetErrorString());
	}
}



void ModuleCarga::LoadMaterials(const aiScene* scene)
{
	aiString file;
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->textures->Load(file.data));
		}
	}
}

void Mesh::LoadVBO(const aiMesh* mesh)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
	unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);
	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	num_vertices = mesh->mNumVertices;
}
// Called before render is available
bool ModuleCarga::Init()
{



	return true;
}



update_status ModuleCarga::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleCarga::Update()
{

	return UPDATE_CONTINUE;
}

// Called every draw update


update_status ModuleCarga::PostUpdate()
{

	//SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCarga::CleanUp()
{


	return true;
}