#pragma once

#include <SimpleMath/SimpleMath.h>
#include <stdexcept>
#include <vector>

enum class Channel
{
    Grey = 1,
    GreyAlpha = 2,
    RGB = 3,
    RGBA = 4
};

class Image
{
  private:
    unsigned int m_width;
    unsigned int m_height;
    Channel m_channels;
    std::vector<unsigned char> m_data;

  public:
    Image() = delete;
    Image(unsigned int width, unsigned int height, Channel channels)
        : m_width(width), m_height(height), m_channels(channels),
          m_data(std::vector<unsigned char>(width * height * static_cast<unsigned int>(channels), 0))
    {
    }
    Image(unsigned int width, unsigned int height, Channel channels, const std::vector<unsigned char> &data)
        : m_width(width), m_height(height), m_channels(channels),
          m_data(std::vector<unsigned char>(data.begin(), data.end()))
    {
        if (data.size() != width * height * static_cast<unsigned int>(channels))
        {
            throw std::invalid_argument("Buffer data has wrong size, must be width*height*channels");
        }
    };

    int SaveToFile(const char *fileName) const;

    void PaintPixel(int x, int y, DirectX::SimpleMath::Color color);
};
