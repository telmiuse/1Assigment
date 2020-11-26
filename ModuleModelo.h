#pragma once
#include "Module.h"
#include <vector>
#include <GL/glew.h>
#include "DefaultImGuiWindow.h"
#include "Assimp/include/assimp/scene.h"
#include "Assimp/include/assimp/material.h"
#include "ModuleMalla.h"
#include "Assimp/include/assimp/cimport.h"

class ModuleModelo :
	public Module
{

public:
	ModuleModelo();
	~ModuleModelo();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	bool CleanUp();
	void Load(const char* file_name);
	unsigned int GetNumVertices();
	void LoadTextures(aiMaterial** const nMaterials, unsigned int mNumMaterials);
	void LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes);
	void Draw();


private:

	std::vector<ModuleMalla> meshes;
	std::vector<unsigned int> materials;
	unsigned int program; 
	GLuint vtxshader;
	GLuint frgshader;
};

