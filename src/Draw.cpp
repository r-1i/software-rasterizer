#include "Draw.h"

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

void Draw::FillTriangle(const DirectX::SimpleMath::Vector3 &v1, const DirectX::SimpleMath::Vector3 &v2,
                        const DirectX::SimpleMath::Vector3 &v3, PNGImage &img, const DirectX::SimpleMath::Color &color)
{
    // Get bbox
    DirectX::SimpleMath::Vector2 bBoxMin(min(min(v1.x, v2.x), v3.x), min(min(v1.y, v2.y), v3.y));
    DirectX::SimpleMath::Vector2 bBoxMax(max(max(v1.x, v2.x), v3.x), max(max(v1.y, v2.y), v3.y));
    bBoxMin = DirectX::SimpleMath::Vector2(max(bBoxMin.x, 0), max(bBoxMin.y, 0));
    bBoxMax = DirectX::SimpleMath::Vector2(min(bBoxMax.x, img.GetWidth() - 1), min(bBoxMax.y, img.GetHeight() - 1));

    // Lambda for cross
    auto cross = [](DirectX::SimpleMath::Vector2 a, DirectX::SimpleMath::Vector2 b) -> float {
        return a.x * b.y - a.y * b.x;
    };

    DirectX::SimpleMath::Vector2 AB = DirectX::SimpleMath::Vector2(v2) - DirectX::SimpleMath::Vector2(v1);
    DirectX::SimpleMath::Vector2 AC = DirectX::SimpleMath::Vector2(v3) - DirectX::SimpleMath::Vector2(v1);
    DirectX::SimpleMath::Vector2 BC = DirectX::SimpleMath::Vector2(v3) - DirectX::SimpleMath::Vector2(v2);

    float areaTotal2 = cross(AB, BC);

    if (areaTotal2 == 0)
        return;

    for (int x = bBoxMin.x; x <= bBoxMax.x; ++x)
    {
        for (int y = bBoxMin.y; y <= bBoxMax.y; ++y)
        {
            DirectX::SimpleMath::Vector2 P(x + 0.5f, y + 0.5f);

            // Barycentric coordinates
            DirectX::SimpleMath::Vector2 PB = DirectX::SimpleMath::Vector2(v2) - P;
            float areaA2 = cross(PB, BC);
            DirectX::SimpleMath::Vector2 PC = DirectX::SimpleMath::Vector2(v3) - P;
            float areaB2 = cross(PC, -AC);
            DirectX::SimpleMath::Vector2 PA = DirectX::SimpleMath::Vector2(v1) - P;
            float areaC2 = cross(PA, AB);

            DirectX::SimpleMath::Vector3 barycentric(areaA2 / areaTotal2, areaB2 / areaTotal2, areaC2 / areaTotal2);

            if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0)
                continue;

            img.PaintPixel(x, y, color);
        }
    }
}
