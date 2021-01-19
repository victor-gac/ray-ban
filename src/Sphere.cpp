//
//  Sphere.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Sphere.hpp"

#include <cmath>

#include "Object.hpp"

bool Sphere::solveQuadric(const float &a, const float &b, const float &c, float &x0, float &x1) const {
    float discr = b*b - 4*a*c;
    
    if (discr < 0) return false;
    else if (discr == 0) x0 = x1 = - 0.5*b/a;
    else {
        float q = (b > 0) ?
        -0.5*(b + sqrt(discr)) :
        -0.5*(b - sqrt(discr));
        x0 = q/a;
        x1 = c/q;
    }
    
    if (x0 > x1) std::swap(x0, x1);
    
    return true;
}

bool Sphere::intersect(Ray& ray, const Object*& hitObject, float& tNear) const {
    /*float t0, t1;
    
    Vec3f L = sCenter - ray.origin();
    float a = ray.direction().dot(ray.direction());
    float b = 2*ray.direction().dot(L);
    float c = L.dot(L) - sRadius;
    
    if (!solveQuadric(a, b, c, t0, t1)) return false;
    
    if (t0 > t1) std::swap(t0, t1);
    
    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return false; // both t0 and t1 are negative
    }*/
    
    Vec3f L = sCenter - ray.origin();
    float t0, t1;
    float b = L.dot(ray.direction());
    
    if (b < 0) return false;
    
    float d2 = L.dot(L) - b*b;
    
    if (d2 > sRadius*sRadius) return false;
    
    float d1 = sqrt(sRadius*sRadius - d2);
    
    t0 = b - d1;
    t1 = b + d1;
    
    if (t0 > t1) std::swap(t0, t1);
    
    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }
    
    ray.t(t0);
    hitObject = this;
    
    return true;
}

void Sphere::getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const {
    Nhit = Phit - sCenter;
    Nhit.normalize();
    // In this particular case, the normal is simular to a point on a unit sphere
    // centred around the origin. We can thus use the normal coordinates to compute
    // the spherical coordinates of Phit.
    // atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
    // acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
    //tex.x((1 + atan2(Nhit.z(), Nhit.x())/M_PI)*0.5);
    //tex.y(acosf(Nhit.y())/M_PI);
}

void Sphere::update() {
    
}
