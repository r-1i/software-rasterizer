#pragma once

#include "IShader.h"
#include "Model.h"
#include "PNGImage.h"
#include <iostream>

namespace Draw
{

void Line(int x1, int y1, int x2, int y2, PNGImage &image, const DirectX::SimpleMath::Color &color);
void FillTriangle(Shaders::IShader &shader, int itr, PNGImage &img, std::vector<float> &zbuffer, const Model &model);

}; // namespace Draw
