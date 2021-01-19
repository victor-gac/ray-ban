//
//  Light.hpp
//  Renderer
//
//  Created by Victor on 28/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include "Mat44f.hpp"
#include "Vec3f.hpp"
#include "Ray.hpp"

class Light {
    public :
    Light();
    Light(float intensity, Vec3f position = Vec3f(-8.0, -3.0, 5.0), Vec3f target = Vec3f(0.0, 0.0, 0.0), Vec3f color = Vec3f(0.3, 0.0, 0.0));

    const float intensity() { return lIntensity; }
    const Vec3f position() { return lPosition; }
    const Vec3f color() { return lColor; }
    
    void intensity(float intensity) { lIntensity = intensity; }
    void position(const Vec3f position) { lPosition = position; }
    void color(const Vec3f color) { lColor = color; }
    
    virtual void illuminate(Ray& ray, Vec3f& lightIntensity) const = 0;
    
    protected :
    float lIntensity;
    Mat44f lMatToWorld;
    Vec3f lPosition;
    Vec3f lColor;
    
    private :
    virtual void update() = 0;
};

#endif /* Light_hpp */
