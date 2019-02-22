#pragma once
#include "pch.h"
#include <string>
#include <unordered_map>
#include <filesystem>
#include <iostream>
namespace fs = std::experimental::filesystem;

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
	void Load(const std::string &directory);//Load all .png files from given directory
	Texture2D GetTexture(const std::string &textureName);
private:
	std::unordered_map<std::string, Texture2D> textures;
};

ResourceLoader::ResourceLoader()
{
	
}

ResourceLoader::~ResourceLoader()
{

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
	}
}

inline Texture2D ResourceLoader::GetTexture(const std::string & textureName)
{
	return textures.find(textureName)->second;
}

