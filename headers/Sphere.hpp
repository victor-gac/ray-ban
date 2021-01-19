//
//  Sphere.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include "Object.hpp"
#include "Vec2f.hpp"
#include "Vec3f.hpp"
#include "Ray.hpp"

class Sphere : public Object {
    public :
    Sphere() :
        Object(),
        sCenter(),
        sRadius() {}
    
    Sphere(Vec3f center, float radius = 0.5, Vec3f color = Vec3f(0.5, 0.5, 0.5)) :
        Object(color),
        sCenter(center),
        sRadius(radius) {}
    
    const Vec3f center() { return sCenter; }
    const float radius() { return sRadius; }
    
    void center(Vec3f center) { sCenter = center; }
    void radius(float radius) { sRadius = radius; }
    
    bool solveQuadric(const float &a, const float &b, const float &c, float &x0, float &x1) const;
    virtual bool intersect(Ray& ray, const Object*& hitObject, float& tNear) const;
    virtual void getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const;
    virtual void voxelize(Octree* octree, unsigned int depth) const {}
    
    private :
    void update();
    
    Vec3f sCenter;
    float sRadius;
};

#endif /* Sphere_hpp */
