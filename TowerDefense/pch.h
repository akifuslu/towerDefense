// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here

#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>

#define GETTEXTURE(x) ResourceLoader::GetInstance().GetTexture(x)
#define LOG(x) std::cout << x << std::endl;


#endif //PCH_H
