#pragma once

#include "pch.h"

namespace fs = std::experimental::filesystem;
/*Summary
Singleton class to keep resources and load when required
*/
class ResourceLoader
{
public:
	void Load(const std::string &directory);//Load all .png files from given directory
	Texture2D& GetTexture(const std::string &textureName);//Get Texture2D by name
	static ResourceLoader* GetInstance();
private:
	std::unordered_map<std::string, Texture2D> textures;
	ResourceLoader();
	~ResourceLoader();
	static ResourceLoader* _instance;
};

ResourceLoader* ResourceLoader::_instance = 0;

ResourceLoader::ResourceLoader()
{
	//
}

ResourceLoader::~ResourceLoader()
{
	delete _instance;
}


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

inline ResourceLoader * ResourceLoader::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new ResourceLoader();
	}
	return _instance;
}

