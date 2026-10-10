#pragma once
#include "IShader.h"
#include "Model.h"
#include "SimpleMath/SimpleMath.h"

namespace Shaders
{
struct SimpleShader : IShader
{
    std::vector<DirectX::SimpleMath::Vector3> vx =
        std::vector<DirectX::SimpleMath::Vector3>(3, DirectX::SimpleMath::Vector3(0., 0., 0.));
    std::vector<DirectX::SimpleMath::Vector3> vt =
        std::vector<DirectX::SimpleMath::Vector3>(3, DirectX::SimpleMath::Vector3(0., 0., 0.));
    std::vector<DirectX::SimpleMath::Vector3> vn =
        std::vector<DirectX::SimpleMath::Vector3>(3, DirectX::SimpleMath::Vector3(0., 0., 0.));

    // Inherited via IShader
    DirectX::SimpleMath::Vector3 vertex(int iface, int ivertex, const Model &model) override
    {

        DirectX::SimpleMath::Vector3 vertex = model.v[model.f[iface + ivertex * 3]];
        vertex.x = (vertex.x + 1.0) * 799.0 / 2.0;
        vertex.y = (-vertex.y + 1.0) * 799.0 / 2.0;
        vertex.z = (vertex.z + 1.0) * 799.0 / 2.0;

        DirectX::SimpleMath::Vector3 normal = model.vn[model.f[iface + ivertex * 3 + 2]];

        vx[ivertex] = vertex;
        vn[ivertex] = normal;

        return vertex;
    }

    // Inherited via IShader
    bool fragment(DirectX::SimpleMath::Vector3 bar, DirectX::SimpleMath::Color &color) override
    {
        DirectX::SimpleMath::Vector3 vNormBar = bar.x * vn[0] + bar.y * vn[1] + bar.z * vn[2];
        vNormBar = vNormBar / vNormBar.Length();
        DirectX::SimpleMath::Vector3 light_dir(0.5, 1.0, 1.0);
        light_dir = light_dir / light_dir.Length();
        float intencity = vNormBar.Dot(light_dir);

        color = DirectX::SimpleMath::Color(intencity, intencity, intencity);
        return false;
    }

    ~SimpleShader() = default;
};
} // namespace Shaders
