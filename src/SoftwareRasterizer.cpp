// SoftwareRasterizer.cpp : Defines the entry point for the application.

#include "SoftwareRasterizer.h"

#include <vector>

#include "Draw.h"
#include "PNGImage.h"

int main()
{
    PNGImage img(200, 200, Channel::RGB);
    for (int x = 0; x < 200; ++x)
    {
        for (int y = 0; y < 200; ++y)
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
    DirectX::SimpleMath::Color color(1.0, 1.0, 1.0);
    Draw::Line(100, 100, 190, 100, img, color);
    Draw::Line(100, 100, 190, 145, img, color);
    Draw::Line(100, 100, 190, 190, img, color);
    Draw::Line(100, 100, 145, 190, img, color);
    Draw::Line(100, 100, 100, 190, img, color);
    Draw::Line(100, 100, 55, 190, img, color);
    Draw::Line(100, 100, 10, 190, img, color);
    Draw::Line(100, 100, 10, 145, img, color);
    Draw::Line(100, 100, 10, 100, img, color);
    Draw::Line(100, 100, 10, 55, img, color);
    Draw::Line(100, 100, 10, 10, img, color);
    Draw::Line(100, 100, 55, 10, img, color);
    Draw::Line(100, 100, 100, 10, img, color);
    Draw::Line(100, 100, 145, 10, img, color);
    Draw::Line(100, 100, 190, 10, img, color);
    Draw::Line(100, 100, 190, 55, img, color);
    img.SaveToFile("test1.png");
    return 0;
}
