// SoftwareRasterizer.cpp : Defines the entry point for the application.

#include "SoftwareRasterizer.h"

#include <vector>

#include "Image.h"

int main()
{
    Image img(200, 100, Channel::RGB);
    for (int x = 0; x < 200; ++x)
    {
        for (int y = 0; y < 100; ++y)
        {
            DirectX::SimpleMath::Color color;
            if (x < 50)
                color.R(1.0);
            else
                color.R(0.0);
            if (y < 50)
                color.G(1.0);
            else
                color.G(0.0);
            color.B(0.5);

            img.PaintPixel(x, y, color);
        }
    }
    img.Fill(DirectX::SimpleMath::Color(1.0, 0.0, 0.0));
    img.SaveToFile("test1.png");
    return 0;
}
