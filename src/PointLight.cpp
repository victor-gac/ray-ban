//
//  PointLight.cpp
//  Renderer
//
//  Created by Victor on 1/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "PointLight.hpp"

PointLight::PointLight() :
Light()
{
    
}

PointLight::PointLight(float intensity, Vec3f position, Vec3f color) :
    Light(intensity, position, color)
{
    update();
}

void PointLight::illuminate(Ray& ray, Vec3f& lightIntensity) const {
    Vec3f dir = ray.origin() - lPosition;
    ray.direction(-1*dir); // Automaticcaly normalized
    ray.t(dir.norm());
    // avoid division by 0
    lightIntensity = lColor*lIntensity/(4*M_PI*ray.t()*ray.t());
}

void PointLight::update() {
    lMatToWorld = Mat44f(Vec4f(0.0, 0.0, 0.0, 0.0),
                         Vec4f(0.0, 0.0, 0.0, 0.0),
                         Vec4f(0.0, 0.0, 0.0, 0.0),
                         Vec4f(lPosition.x(), lPosition.y(), lPosition.z(), 1.0));
}