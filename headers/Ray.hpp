//
//  Ray.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include "Vec3f.hpp"

class Ray {
    public :
    static const float tInfinity;
    
    Ray();
    Ray(Vec3f origin, Vec3f direction = Vec3f(0, 0, 1), float t = Ray::tInfinity, float tMin = 0.0, float tMax = Ray::tInfinity);
    
    Vec3f origin() const { return rOrigin; }
    Vec3f direction() const { return rDirection; }
    Vec3f invDir() const { return rInvDir; }
    int sign(int coord) { return rSign[coord]; }
    const float tMin() const { return rTMin; }
    const float tMax() const { return rTMax; }
    const float t() const { return rT; }
    const float u() { return rU; }
    const float v() { return rV; }
    
    void origin(Vec3f origin) { rOrigin = origin; }
    void direction(Vec3f direction) {
        rDirection = direction;
        update(); }
    void tMin(float tMin) { rTMin = tMin; }
    void tMax(float tMax) { rTMax = tMax; }
    void t(float t) { rT = t; }
    void u(float u) { rU = u; }
    void v(float v) { rV = v; }
    
    private :
    void update();
    
    Vec3f rOrigin;
    Vec3f rDirection;
    Vec3f rInvDir;
    int rSign[3];
    float rT;
    float rTMin;
    float rTMax;
    float rU;
    float rV;
};

#endif /* Ray_hpp */
