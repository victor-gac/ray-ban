//
//  Vec3f.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//
#include <iostream>
#include <cmath>

#include "Vec3f.hpp"

const float Vec3f::dot(Vec3f rVec) const {
    return vX*rVec.x() + vY*rVec.y() + vZ*rVec.z();
}

const Vec3f Vec3f::cross(Vec3f rVec) const {
    return Vec3f(vY*rVec.z()-vZ*rVec.y(), vZ*rVec.x() - vX*rVec.z(), vX*rVec.y() - vY*rVec.x());
}

void Vec3f::normalize() {
    float length = sqrt(vX*vX + vY*vY + vZ*vZ);
    
    vX/=length;
    vY/=length;
    vZ/=length;
}

const float Vec3f::norm() {
    return sqrt(vX*vX + vY*vY + vZ*vZ);;
}

void Vec3f::print() const {
    std::cout << "[" << vX << ", " << vY << ", " << vZ << "]" << std::endl;
    /*std::cout << "[" << vX << "," << std::endl;
    std::cout << " " << vY << "," << std::endl;
    std::cout << " " << vZ << "]" << std::endl;*/
}