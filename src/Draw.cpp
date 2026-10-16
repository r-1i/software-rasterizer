#include "Draw.h"
#include "IShader.h"
#include <iostream>

void Draw::Line(int x0, int y0, int x1, int y1, PNGImage &image, const DirectX::SimpleMath::Color &color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;

    int derror2 = std::abs(dy) * 2;
    int error2 = 0;

    int y = y0;

    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            image.PaintPixel(y, x, color);
        }
        else
        {
            image.PaintPixel(x, y, color);
        }

        error2 += derror2;

        if (error2 >= dx)
        {
            error2 -= dx * 2;
            y += (y1 > y0 ? 1 : -1);
        }
    }
}

void Draw::FillTriangle(Shaders::IShader &shader, int itr, PNGImage &img, std::vector<float> &zbuffer,
                        const Model &model, const PNGImage& albedo)
{
    // World space
    DirectX::SimpleMath::Vector3 a = shader.vertex(itr, 0, model);
    DirectX::SimpleMath::Vector3 b = shader.vertex(itr, 1, model);
    DirectX::SimpleMath::Vector3 c = shader.vertex(itr, 2, model);

    // Get bbox
    DirectX::SimpleMath::Vector2 bBoxMin(min(min(a.x, b.x), c.x), min(min(a.y, b.y), c.y));
    DirectX::SimpleMath::Vector2 bBoxMax(max(max(a.x, b.x), c.x), max(max(a.y, b.y), c.y));
    bBoxMin = DirectX::SimpleMath::Vector2(max(bBoxMin.x, 0), max(bBoxMin.y, 0));
    bBoxMax = DirectX::SimpleMath::Vector2(min(bBoxMax.x, img.GetWidth() - 1), min(bBoxMax.y, img.GetHeight() - 1));

    // Lambda for cross
    auto cross = [](DirectX::SimpleMath::Vector2 a, DirectX::SimpleMath::Vector2 b) -> float {
        return a.x * b.y - a.y * b.x;
    };

    DirectX::SimpleMath::Vector2 AB = DirectX::SimpleMath::Vector2(b) - DirectX::SimpleMath::Vector2(a);
    DirectX::SimpleMath::Vector2 AC = DirectX::SimpleMath::Vector2(c) - DirectX::SimpleMath::Vector2(a);
    DirectX::SimpleMath::Vector2 BC = DirectX::SimpleMath::Vector2(c) - DirectX::SimpleMath::Vector2(b);

    float areaTotal2 = cross(AB, BC);

    if (areaTotal2 == 0)
        return;

    for (int x = bBoxMin.x; x <= bBoxMax.x; ++x)
    {
        for (int y = bBoxMin.y; y <= bBoxMax.y; ++y)
        {
            DirectX::SimpleMath::Vector3 P(x + 0.5f, y + 0.5f, 1.0);

            // Barycentric coordinates
            DirectX::SimpleMath::Vector2 PB = DirectX::SimpleMath::Vector2(b) - P;
            float areaA2 = cross(PB, BC);
            DirectX::SimpleMath::Vector2 PC = DirectX::SimpleMath::Vector2(c) - P;
            float areaB2 = cross(PC, -AC);
            DirectX::SimpleMath::Vector2 PA = DirectX::SimpleMath::Vector2(a) - P;
            float areaC2 = cross(PA, AB);

            DirectX::SimpleMath::Vector3 barycentric(areaA2 / areaTotal2, areaB2 / areaTotal2, areaC2 / areaTotal2);

            if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0)
                continue;

            P.z = barycentric.Dot(DirectX::SimpleMath::Vector3(a.z, b.z, c.z) /
                                  DirectX::SimpleMath::Vector3(a.z, b.z, c.z).Length());
            // P.z: -1..1 -> 0..799
            // std::cout << P.z << " " << a.z << " " << b.z << " " << c.z << std::endl;
            // P.z = ((P.z + 1.0) * 799) / 2.0;
            // std::cout << P.z << std::endl;

            // Call fragment shader

            DirectX::SimpleMath::Vector3 baryCoords = barycentric.x * a + barycentric.y * b + barycentric.z * c;
            P.z = baryCoords.z;

            int idx = x + y * img.GetWidth();
            if (zbuffer[idx] > P.z)
            {
                zbuffer[idx] = P.z;
                DirectX::SimpleMath::Color colorPixel;
                shader.fragment(barycentric, colorPixel, albedo);
                // DirectX::SimpleMath::Color testDepth(P.z, P.z, P.z);

                img.PaintPixel(x, y, colorPixel);
            }
        }
    }
}
