
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "PNGImage.h"
#include "stb_image_write.h"
#include <algorithm>

int PNGImage::SaveToFile(const char *fileName) const
{
    if (m_data.size() == 0)
        throw std::runtime_error("m_data.size() if Image is not valid");
    return stbi_write_png(fileName, m_width, m_height, static_cast<unsigned int>(m_channels), &m_data[0],
                          m_width * static_cast<unsigned int>(m_channels));
}

int PNGImage::FloatToUnorm8(float v)
{
    return std::clamp<int>(v * 255, 0, 255);
}

void PNGImage::Fill(const DirectX::SimpleMath::Color &color)
{
    int colUnorm8[4] = {};
    for (int c = 0; c < 4; ++c)
    {
        colUnorm8[c] = FloatToUnorm8(color[c]);
    }

    for (int i = 0; i < m_width * m_height; ++i)
    {
        for (int c = 0; c < static_cast<int>(m_channels); ++c)
        {
            m_data[i * static_cast<int>(m_channels) + c] = colUnorm8[c];
        }
    }
}

void PNGImage::PaintPixel(int x, int y, const DirectX::SimpleMath::Color &color)
{
    if (static_cast<unsigned int>(x) >= m_width || x < 0 || static_cast<unsigned int>(y) >= m_height || y < 0)
    {
        throw std::invalid_argument("Wrong xy coordinates");
    }

    for (int i = 0; i < static_cast<int>(m_channels); ++i)
    {
        // (0, 0) -> 0, 1, 2, 3
        // (1, 0) -> 4, 5, 6, 7
        m_data[x * static_cast<unsigned int>(m_channels) + (y * m_width * static_cast<unsigned int>(m_channels)) + i] =
            FloatToUnorm8(color[i]);
    }
}
