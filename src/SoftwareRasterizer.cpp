// SoftwareRasterizer.cpp : Defines the entry point for the application.

#include "SoftwareRasterizer.h"

#include <vector>

#include "Draw.h"
#include "OBJParser.h"
#include "PNGImage.h"
#include "Shaders.h"
#include <limits>

int main()
{
    PNGImage img(800, 800, Channel::RGB);

    Model model = OBJParser::Load("assets/african_head/african_head.obj");
    PNGImage albedo("assets/african_head/dimon_head.png");

    std::cout << model.v.size() << " " << model.vt.size() << " " << model.vn.size() << " " << model.f.size() / 9
              << std::endl;

    DirectX::SimpleMath::Color c_white(1.0, 1.0, 1.0);

    auto dot = [](DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b) -> float {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    };

    std::vector<float> zbuffer(img.GetWidth() * img.GetHeight(), (std::numeric_limits<float>::max)());

    

    Shaders::SimpleShader shader;

    for (int i = 0; i < model.f.size(); i += 9)
    {

        // Wireframe
        // Draw::Line(v_1.x, v_1.y, v_2.x, v_2.y, img, c_white);
        // Draw::Line(v_1.x, v_1.y, v_3.x, v_3.y, img, c_white);
        // Draw::Line(v_2.x, v_2.y, v_3.x, v_3.y, img, c_white);

        Draw::FillTriangle(shader, i, img, zbuffer, model, albedo);
    }

    img.SaveToFile("test1.png");

    return 0;
}
