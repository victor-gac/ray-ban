//
//  Vec4f.cpp
//  Renderer
//
//  Created by Victor on 13/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//
#include <iostream>
#include <cmath>

#include "Vec4f.hpp"

const float Vec4f::dot(Vec4f rVec) {
    return vX*rVec.x() + vY*rVec.y() + vZ*rVec.z() + vT*rVec.t();
}

void Vec4f::normalize() {
    float length = sqrt(vX*vX + vY*vY + vZ*vZ + vT*vT);
    
    vX/=length;
    vY/=length;
    vZ/=length;
    vT/=length;
}

void Vec4f::print() {
    std::cout << "[" << vX << ", " << vY << ", " << vZ << ", " << vT << "]" << std::endl;
    /*std::cout << "[" << vX << "," << std::endl;
     std::cout << " " << vY << "," << std::endl;
     std::cout << " " << vZ << "]" << std::endl;*/
}