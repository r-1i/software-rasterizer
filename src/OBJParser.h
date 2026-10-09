#pragma once
#include "Model.h"
#include "SimpleMath/SimpleMath.h"
#include <fstream>
#include <sstream>
#include <string>

namespace OBJParser
{
Model Load(const char *filePath);

}; // namespace OBJParser
