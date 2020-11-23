#pragma once
#include "Module.h"
#include <vector>
#include "DefaultImGuiWindow.h"
#include <assimp/scene.h>
#include <assimp/material.h>



class ModuleCarga :
	public Module
{

public:
	ModuleCarga();
	~ModuleCarga();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void Load(const char* file_name);
	void LoadMaterials(const aiScene* scene);

private:
	

};

