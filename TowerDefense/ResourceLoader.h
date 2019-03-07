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
	Texture2D* GetTexture(const std::string &textureName);//Get Texture2D by name
private:
	std::unordered_map<std::string, Texture2D> textures;
	ResourceLoader() {};
};


