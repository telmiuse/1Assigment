#pragma once
#include "Module.h"
#include <vector>
#include "DefaultImGuiWindow.h"
#include <scene.h>
#include <material.h>
#include "ModuleMalla.h"


class ModuleMalla :
	public Module
{

public:
	ModuleMalla();
	~ModuleMalla();

	//bool Init();
	//update_status PreUpdate();
	//update_status Update();
	//update_status PostUpdate();
	//bool CleanUp();


	void CreateVAO();
	void LoadEBO(const aiMesh* mesh);
	void LoadVBO(const aiMesh* mesh);
	void Draw(const std::vector<unsigned>& model_textures);
	int num_indices;
	int num_vertices;


private:
	unsigned vao;
	unsigned vbo;
	unsigned ebo;
	int material_index;
	std::string texture_path;


};

