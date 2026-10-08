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
