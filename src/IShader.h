#pragma once
#include "Model.h"
#include "SimpleMath/SimpleMath.h"
#include "PNGImage.h"

namespace Shaders
{
struct IShader
{
    virtual ~IShader()
    {
    }
    virtual DirectX::SimpleMath::Vector3 vertex(int iface, int ivertex, const Model &model) = 0;
    virtual bool fragment(DirectX::SimpleMath::Vector3 bar, DirectX::SimpleMath::Color &color, const PNGImage& albedo) = 0;
};
} // namespace Shaders
