// SoftwareRasterizer.cpp : Defines the entry point for the application.

#include "SoftwareRasterizer.h"

#include <vector>

#include "Draw.h"
#include "OBJParser.h"
#include "PNGImage.h"

int main()
{
    PNGImage img(800, 800, Channel::RGB);

    Model model = OBJParser::Load("assets/african_head/african_head.obj");

    std::cout << model.v.size() << " " << model.vt.size() << " " << model.vn.size() << " " << model.f.size() / 9
              << std::endl;

    DirectX::SimpleMath::Color c_white(1.0, 1.0, 1.0);

    for (int i = 0; i < model.f.size(); i += 9)
    {
        DirectX::SimpleMath::Vector3 v_1 = model.v[model.f[i]];
        // DirectX::SimpleMath::Vector3 vt_1 = model.v[model.f[i + 1]];
        // DirectX::SimpleMath::Vector3 vn_1 = model.v[model.f[i + 2]];

        DirectX::SimpleMath::Vector3 v_2 = model.v[model.f[i + 3]];
        // DirectX::SimpleMath::Vector3 vt_2 = model.v[model.f[i + 4]];
        // DirectX::SimpleMath::Vector3 vn_2 = model.v[model.f[i + 5]];

        DirectX::SimpleMath::Vector3 v_3 = model.v[model.f[i + 6]];
        // DirectX::SimpleMath::Vector3 vt_3 = model.v[model.f[i + 7]];
        // DirectX::SimpleMath::Vector3 vn_3 = model.v[model.f[i + 8]];

        // -1..1 -> 0..800
        v_1.x = ((v_1.x + 1.0) / 2.0) * 799;
        v_1.y = ((-v_1.y + 1.0) / 2.0) * 799;

        v_2.x = ((v_2.x + 1.0) / 2.0) * 799;
        v_2.y = ((-v_2.y + 1.0) / 2.0) * 799;

        v_3.x = ((v_3.x + 1.0) / 2.0) * 799;
        v_3.y = ((-v_3.y + 1.0) / 2.0) * 799;

        // Wireframe
        Draw::Line(v_1.x, v_1.y, v_2.x, v_2.y, img, c_white);
        Draw::Line(v_1.x, v_1.y, v_3.x, v_3.y, img, c_white);
        Draw::Line(v_2.x, v_2.y, v_3.x, v_3.y, img, c_white);

        DirectX::SimpleMath::Color rand_color(v_1.x / static_cast<float>(799), v_2.x / static_cast<float>(799),
                                              v_3.x / static_cast<float>(799));

        Draw::FillTriangle(v_1, v_2, v_3, img, rand_color);

        //
    }

    img.SaveToFile("test1.png");

    return 0;
}
