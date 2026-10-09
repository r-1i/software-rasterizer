#include "OBJParser.h"

Model OBJParser::Load(const char *filePath)
{
    Model model;

    std::ifstream file(filePath);
    if (!file)
    {
        throw std::runtime_error("Cannot open file");
    }
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream ss(line);

        std::string tag;
        ss >> tag;
        if (tag == "v")
        {
            DirectX::SimpleMath::Vector3 point;
            ss >> point.x >> point.y >> point.z;
            model.v.push_back(point);
        }
        else if (tag == "vt")
        {
            DirectX::SimpleMath::Vector3 point;
            ss >> point.x >> point.y >> point.z;
            model.vt.push_back(point);
        }
        else if (tag == "vn")
        {

            DirectX::SimpleMath::Vector3 point;
            ss >> point.x >> point.y >> point.z;
            model.vn.push_back(point);
        }
        else if (tag == "f")
        {
            std::string word;
            while (ss >> word)
            {
                std::istringstream ws(word);
                std::string part;
                int elems[3] = {-1, -1, -1};
                int i = 0;
                while (std::getline(ws, part, '/'))
                {

                    if (part.size() == 0)
                    {
                        i++;
                        continue;
                    }
                    elems[i] = std::stoi(part) - 1;
                    i++;
                }
                for (int i = 0; i < 3; ++i)
                {
                    model.f.push_back(elems[i]);
                }
            }
        }
    }

    return model;
}
