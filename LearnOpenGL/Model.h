#pragma once
#include <vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public: Model(std::string const &path);
	  ~Model();

public: 
	void LoadModel(std::string const& path);
	void Draw(Shader* shader);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLint TextureFromFile(const char* path, std::string directory);
public:
	std::vector<Mesh> meshes;
	std::string directory;
	
};

