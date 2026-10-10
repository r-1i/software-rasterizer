// SoftwareRasterizer.cpp : Defines the entry point for the application.

#include "SoftwareRasterizer.h"

#include <vector>

#include "Draw.h"
#include "OBJParser.h"
#include "PNGImage.h"

Model model;

int main()
{
    PNGImage img(800, 800, Channel::RGB);

    model = OBJParser::Load("assets/african_head/african_head.obj");

    std::cout << model.v.size() << " " << model.vt.size() << " " << model.vn.size() << " " << model.f.size() / 9
              << std::endl;

    DirectX::SimpleMath::Color c_white(1.0, 1.0, 1.0);

    auto dot = [](DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b) -> float {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    };

    std::vector<int> zbuffer(img.GetWidth() * img.GetHeight(), -9999999);

    for (int i = 0; i < model.f.size(); i += 9)
    {
        DirectX::SimpleMath::Vector2 screenCoords[3];
        DirectX::SimpleMath::Vector3 worldCoords[3];

        DirectX::SimpleMath::Vector3 v_1 = model.v[model.f[i]];
        // DirectX::SimpleMath::Vector3 vt_1 = model.v[model.f[i + 1]];
        // DirectX::SimpleMath::Vector3 vn_1 = model.v[model.f[i + 2]];

        DirectX::SimpleMath::Vector3 v_2 = model.v[model.f[i + 3]];
        // DirectX::SimpleMath::Vector3 vt_2 = model.v[model.f[i + 4]];
        // DirectX::SimpleMath::Vector3 vn_2 = model.v[model.f[i + 5]];

        DirectX::SimpleMath::Vector3 v_3 = model.v[model.f[i + 6]];
        // DirectX::SimpleMath::Vector3 vt_3 = model.v[model.f[i + 7]];
        // DirectX::SimpleMath::Vector3 vn_3 = model.v[model.f[i + 8]];

        screenCoords[0] =
            DirectX::SimpleMath::Vector2((v_1.x + 1.0) * img.GetWidth() / 2.0, (v_1.y + 1.0) * img.GetHeight() / 2.0);
        worldCoords[0] = v_1;
        screenCoords[1] =
            DirectX::SimpleMath::Vector2((v_2.x + 1.0) * img.GetWidth() / 2.0, (v_2.y + 1.0) * img.GetHeight() / 2.0);
        worldCoords[1] = v_2;
        screenCoords[2] =
            DirectX::SimpleMath::Vector2((v_3.x + 1.0) * img.GetWidth() / 2.0, (v_3.y + 1.0) * img.GetHeight() / 2.0);
        worldCoords[2] = v_3;

        // -1..1 -> 0..800
        v_1.x = ((v_1.x + 1.0) / 2.0) * 799;
        v_1.y = ((-v_1.y + 1.0) / 2.0) * 799;
        v_1.z = ((v_1.z + 1.0) / 2.0) * 799;

        v_2.x = ((v_2.x + 1.0) / 2.0) * 799;
        v_2.y = ((-v_2.y + 1.0) / 2.0) * 799;
        v_2.z = ((v_2.z + 1.0) / 2.0) * 799;

        v_3.x = ((v_3.x + 1.0) / 2.0) * 799;
        v_3.y = ((-v_3.y + 1.0) / 2.0) * 799;
        v_3.z = ((v_3.z + 1.0) / 2.0) * 799;

        // Wireframe
        // Draw::Line(v_1.x, v_1.y, v_2.x, v_2.y, img, c_white);
        // Draw::Line(v_1.x, v_1.y, v_3.x, v_3.y, img, c_white);
        // Draw::Line(v_2.x, v_2.y, v_3.x, v_3.y, img, c_white);
        // 0..155

        DirectX::SimpleMath::Vector3 n_lightDir(1.0, 1.0, 0.0);
        n_lightDir = n_lightDir / n_lightDir.Length();
        DirectX::SimpleMath::Vector3 n = (v_2 - v_1).Cross(v_3 - v_2);
        n = n / n.Length();

        float intencity = dot(n_lightDir, n);

        DirectX::SimpleMath::Color rand_color(((rand() % 255) / 255.0), ((rand() % 255) / 255.0),
                                              ((rand() % 255) / 255.0));

        DirectX::SimpleMath::Color intencity_color(intencity, intencity, intencity);

        // std::cout << intencity << std::endl;
        Draw::SimpleShader shader;
        Draw::FillTriangle(shader, i, img, intencity_color, zbuffer, model);
    }

    img.SaveToFile("test1.png");

    return 0;
}
