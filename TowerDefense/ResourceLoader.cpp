#include "pch.h"
#include "ResourceLoader.h"

void ResourceLoader::Load(const std::string & directory)
{
	for (const auto & entry : fs::directory_iterator(directory))//iterate over files
	{
		std::string path = entry.path().string();
		std::string fileName = entry.path().filename().string();
		fileName = fileName.substr(0, fileName.find('.'));
		Image image = LoadImage(path.c_str());
		Texture2D texture = LoadTextureFromImage(image);
		textures.insert({ fileName, texture });
		UnloadImage(image);
	}
}

Texture2D* ResourceLoader::GetTexture(const std::string & textureName)
{
	return &textures.find(textureName)->second;
}