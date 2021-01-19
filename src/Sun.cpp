//
//  Sun.cpp
//  Renderer
//
//  Created by Victor on 1/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Sun.hpp"
#include "Ray.hpp"

Sun::Sun() :
    Light()
{
    
}

Sun::Sun(float intensity, Vec3f position, Vec3f color, Vec3f target) :
    Light(intensity, position, color),
    lDirection(target - position)
{
    lDirection.normalize();
    update();
}

void Sun::illuminate(Ray& ray, Vec3f& lightIntensity) const
{
    ray.direction(-1*lDirection);
    ray.t(Ray::tInfinity);
    lightIntensity = lColor*lIntensity;
}

void Sun::update() {
    Vec3f Z(-1*lDirection);
    Z.normalize();
    Vec3f X;
    if (Z.x() == 0 && Z.y() == 0)
        X = Vec3f(1.0, 0.0, 0.0);
    else
        X = Vec3f(-Z.y(), Z.x(), 0.0);
    X.normalize();
    Vec3f Y = Z.cross(X);
    Y.normalize();
    
    lMatToWorld = Mat44f(Vec4f(X.x(), X.y(), X.z(), 0.0),
                         Vec4f(Y.x(), Y.y(), Y.z(), 0.0),
                         Vec4f(Z.x(), Z.y(), Z.z(), 0.0),
                         Vec4f(lPosition.x(), lPosition.y(), lPosition.z(), 1.0));
}