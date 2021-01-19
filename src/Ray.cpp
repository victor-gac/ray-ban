//
//  Ray.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Ray.hpp"

const float Ray::tInfinity = std::numeric_limits<float>::max();

Ray::Ray() :
    rOrigin(),
    rDirection(),
    rInvDir(),
    rT(Ray::tInfinity),
    rTMin(0.0),
    rTMax(Ray::tInfinity)
{
    update();
}

Ray::Ray(Vec3f origin, Vec3f direction, float t, float tMin, float tMax) :
    rOrigin(origin),
    rDirection(direction),
    rInvDir(),
    rT(t),
    rTMin(tMin),
    rTMax(tMax)
{
    update();
}

void Ray::update() {
    rInvDir = Vec3f(1/rDirection.x(), 1/rDirection.y(), 1/rDirection.z());
    
    rSign[0] = (rInvDir.x() < 0);
    rSign[1] = (rInvDir.y() < 0);
    rSign[2] = (rInvDir.z() < 0);
}