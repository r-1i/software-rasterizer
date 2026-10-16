#pragma once
#include "IShader.h"
#include "Model.h"
#include "SimpleMath/SimpleMath.h"

namespace Shaders
{
struct SimpleShader : IShader
{

    std::vector<DirectX::SimpleMath::Vector4> vx =
        std::vector<DirectX::SimpleMath::Vector4>(3, DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
    std::vector<DirectX::SimpleMath::Vector3> vt =
        std::vector<DirectX::SimpleMath::Vector3>(3, DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
    std::vector<DirectX::SimpleMath::Vector3> vn =
        std::vector<DirectX::SimpleMath::Vector3>(3, DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));

    // Matrices
    DirectX::SimpleMath::Matrix worldMatrix;

    DirectX::SimpleMath::Matrix cameraPosMatrix;
    DirectX::SimpleMath::Matrix cameraMatrix;

    DirectX::SimpleMath::Matrix projMatrix;
    float hFov = DirectX::XMConvertToRadians(90.0f);
    float aspectRatio = 1.0f;
    float nearPlane = 0.3f;
    float farPlane = 10.0f;

    SimpleShader()
    {
        worldMatrix = DirectX::SimpleMath::Matrix(1.0f, 0.0f, 0.0f, 0.0f, 
                                                  0.0f, 1.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 1.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, 1.0f);

        cameraPosMatrix = DirectX::SimpleMath::Matrix(1.0f, 0.0f, 0.0f, 0.0f, // scale*rotation x
                                                      0.0f, 1.0f, 0.0f, 0.0f,
                                                      0.0f, 0.0f, 1.0f, 0.0f,
                                                      0.0f, 0.0f, -1.0f, 1.0f); // camera pos (transform)

        cameraMatrix = cameraPosMatrix;

        float e = 1 / tan(hFov / 2.0f);

        projMatrix = DirectX::SimpleMath::Matrix(e, 0.0f, 0.0f, 0.0f,
                                                 0.0f, e/aspectRatio, 0.0f, 0.0f,
                                                 0.0f, 0.0f, -(farPlane+nearPlane)/(farPlane-nearPlane), -1.0f,
                                                 0.0f, 0.0f, (- 2.0f * farPlane * nearPlane) / (farPlane - nearPlane), 0.0f);

    }

    // Inherited via IShader
    DirectX::SimpleMath::Vector3 vertex(int iface, int ivertex, const Model &model) override
    {
        DirectX::SimpleMath::Vector3 v3 = model.v[model.f[iface + ivertex * 3]];
        DirectX::SimpleMath::Vector4 vertex(v3.x, v3.y, v3.z, 1.0);


        // From Model space to World space
        vertex = DirectX::SimpleMath::Vector4::Transform(vertex, worldMatrix);

        // From World space to Camera space
        vertex = DirectX::SimpleMath::Vector4::Transform(vertex, cameraMatrix);

        // From Camera space to NDC
        vertex = DirectX::SimpleMath::Vector4::Transform(vertex, projMatrix);
        vertex.x = vertex.x / vertex.w;
        vertex.y = vertex.y / vertex.w;
        vertex.z = vertex.z / vertex.w;

        // Viewport NDC (Old code)
        vertex.x = (vertex.x + 1.0) * 799.0 / 2.0;
        vertex.y = (-vertex.y + 1.0) * 799.0 / 2.0;
        vertex.z = (vertex.z + 1.0) * 799.0 / 2.0;

        DirectX::SimpleMath::Vector3 normal = model.vn[model.f[iface + ivertex * 3 + 2]];

        vx[ivertex] = vertex;
        vn[ivertex] = normal;
        
        v3 = DirectX::SimpleMath::Vector3(vertex.x, vertex.y, vertex.z);
        return v3;
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
