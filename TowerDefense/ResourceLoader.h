#pragma once

#include "pch.h"

namespace fs = std::experimental::filesystem;
/*Summary
Singleton class to keep resources and load when required
*/
class ResourceLoader
{
public:
	static ResourceLoader& GetInstance()
	{
		static ResourceLoader instance;
		return instance;
	}
	ResourceLoader(ResourceLoader const&) = delete;
	void operator=(ResourceLoader const&) = delete;
	void Load(const std::string &directory);//Load all .png files from given directory
	Texture2D& GetTexture(const std::string &textureName);//Get Texture2D by name
private:
	std::unordered_map<std::string, Texture2D> textures;
	ResourceLoader() {};
};


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

inline Texture2D& ResourceLoader::GetTexture(const std::string & textureName)
{
	return textures.find(textureName)->second;
}

