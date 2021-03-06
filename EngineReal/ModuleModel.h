#pragma once
#include "Module.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include <string>
#include <IOStream.hpp>
#include <IOSystem.hpp>
#include <DefaultLogger.hpp>

using namespace Assimp;

class ModuleModel :
	public Module
{
public:
	ModuleModel();
	~ModuleModel();
	//bool Init();



	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;

	void LogInfo(const std::string& pMessage);
	void LogError(const std::string& pMessage);

	void LoadModel(const char*);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh*, const aiScene*);
	std::vector<Texture> loadTextures(aiMaterial*, aiTextureType, char*);
	void UpdateTexture(Texture& textToUpdate);
	bool FileExists(const char*);
	const char* directory = nullptr;
	std::string modelPath = "Models/";
	std::string myTexturesPath = "Textures/";
	std::string finalPath = "";


	aiVector3D position;
	aiQuaternion rotation;
	aiVector3D scale;

	Mesh theMesh;
	float3 modelPos = { 0, 0, 0 };
	float maxRadius = 7.0f;
	AABB boundingBox = { float3::zero, float3::zero };
	float3 centerPoint = { 0, 0, 0 };
	float3 centerOffset = { 0, 0, 0 };
	int numVertices = 0;
	int numIndices = 0;
	int numFaces = 0;
	//bool CleanUp();
};

