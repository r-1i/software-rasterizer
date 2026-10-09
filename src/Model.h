#pragma once
#include "SimpleMath/SimpleMath.h"
#include <vector>
struct Model
{
    std::vector<DirectX::SimpleMath::Vector3> v;
    std::vector<DirectX::SimpleMath::Vector3> vt;
    std::vector<DirectX::SimpleMath::Vector3> vn;
    std::vector<unsigned int> f;
};
