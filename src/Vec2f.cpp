//
//  Vec2f.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//
#include <iostream>
#include <cmath>

#include "Vec2f.hpp"

const float Vec2f::dot(Vec2f rVec) {
    return vX*rVec.x() + vY*rVec.y();
}

const float Vec2f::cross(Vec2f rVec) {
    return vX*rVec.y() - vY*rVec.x();
}

void Vec2f::normalize() {
    float length = sqrt(vX*vX + vY*vY);
    
    vX/=length;
    vY/=length;
}

void Vec2f::print() {
    std::cout << "[" << vX << ", " << vY << "]" << std::endl;
    /*std::cout << "[" << vX << "," << std::endl;
     std::cout << " " << vY << "," << std::endl;
     std::cout << " " << vZ << "]" << std::endl;*/
}