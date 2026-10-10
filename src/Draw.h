#pragma once

#include "Model.h"
#include "PNGImage.h"
#include <iostream>

namespace Draw
{

struct IShader
{
    virtual ~IShader() {};
    virtual DirectX::SimpleMath::Vector3 vertex(int iface, int ivertex, const Model &model) = 0;
    virtual bool fragment(DirectX::SimpleMath::Vector3 bar, DirectX::SimpleMath::Color &color) = 0;
};

struct SimpleShader : IShader
{
    std::vector<DirectX::SimpleMath::Vector3> vx;
    std::vector<DirectX::SimpleMath::Vector3> vt;
    std::vector<DirectX::SimpleMath::Vector3> vn;
    int total = 0;

    // Inherited via IShader
    DirectX::SimpleMath::Vector3 vertex(int iface, int ivertex, const Model &model) override
    {
        DirectX::SimpleMath::Vector3 vertex = model.v[model.f[iface + ivertex * 3]];
        vertex.x = (vertex.x + 1.0) * 799.0 / 2.0;
        vertex.y = (-vertex.y + 1.0) * 799.0 / 2.0;
        vertex.z = (vertex.z + 1.0) * 799.0 / 2.0;

        DirectX::SimpleMath::Vector3 normal = model.vn[model.f[iface + ivertex * 3 + 2]];

        vx.push_back(vertex);
        vn.push_back(normal);

        total++;

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

void Line(int x1, int y1, int x2, int y2, PNGImage &image, const DirectX::SimpleMath::Color &color);
void FillTriangle(IShader &shader, int itr, PNGImage &img, const DirectX::SimpleMath::Color &color,
                  std::vector<int> &zbuffer, const Model &model);

}; // namespace Draw
