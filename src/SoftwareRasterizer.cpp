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

    img.SaveToFile("test1.png");

    return 0;
}
