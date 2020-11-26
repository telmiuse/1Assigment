#include "ModuleModelo.h"
#include "Application.h"
#include "ModuleMalla.h"
#include "program.h"
#include "ModuleTexture.h"
#include <scene.h>
#include <material.h>
#include "ModuleCamera.h"
#include <mesh.h>
#include <postprocess.h>
#include "cimport.h"     // Plain-C interface        // Output data structure  // Post processing flags

ModuleModelo::ModuleModelo()
{

}

// Destructor
ModuleModelo::~ModuleModelo()
{

}

void ModuleModelo::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene) {
		LoadTextures(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else {
		LOG("Error loadingf %s: %s", file_name, aiGetErrorString());
	}
	aiReleaseImport(scene);
}

void ModuleModelo::LoadTextures(aiMaterial** const nMaterials, unsigned int mNumMaterials) {
	aiString file;
	materials.reserve(mNumMaterials);
	for (unsigned i = 0; i < mNumMaterials; ++i) {
		if (nMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) {
			materials.push_back(App->texture->LoadTexture(file.data));
		}
	}
}


void ModuleModelo::Draw() {
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i].Draw(materials);
	}
}

std::string nameAsPNG(aiString name) {
	std::string stringName = name.C_Str();
	return stringName + ".png";
}



void ModuleModelo::LoadMeshes(aiMesh** const mMeshes , unsigned int mNumMeshes)
{
	meshes.reserve(mNumMeshes);
	for (unsigned i = 0; i < mNumMeshes; ++i)
	{
		meshes.push_back(ModuleMalla());
		meshes[i].LoadVBO(mMeshes[i]);
		meshes[i].LoadEBO(mMeshes[i]);
		meshes[i].CreateVAO();
	}
}

unsigned int ModuleModelo::GetNumVertices() {
	unsigned int total_vertices = 0;
	for (unsigned int i = 0; i < meshes.size(); i++) {
		total_vertices += meshes[i].num_indices;
	}
	return total_vertices;
}


// Called before render is available
bool ModuleModelo::Init()
{

	Load("BakerHouse.fbx");

	return true;
}



update_status ModuleModelo::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleModelo::Update()
{
	
	return UPDATE_CONTINUE;
}

// Called every draw update


update_status ModuleModelo::PostUpdate()
{

	//SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleModelo::CleanUp()
{


	return true;
}