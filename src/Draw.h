#pragma once

#include "PNGImage.h"

namespace Draw
{

void Line(int x1, int y1, int x2, int y2, PNGImage &image, const DirectX::SimpleMath::Color &color);
void FillTriangle(const DirectX::SimpleMath::Vector3 &v1, const DirectX::SimpleMath::Vector3 &v2,
                  const DirectX::SimpleMath::Vector3 &v3, PNGImage &img, const DirectX::SimpleMath::Color &color);

}; // namespace Draw
