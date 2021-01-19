//
//  Object.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Vec2f.hpp"
#include "Vec3f.hpp"
#include "Ray.hpp"

class Octree;

class Object {
    public :
    Object() :
        oColor(),
        oAlbedo(0.18) {}
    Object(Vec3f color, float albedo = 0.18) :
        oColor(color),
        oAlbedo(albedo) {}
    
    virtual bool intersect(Ray&, const Object*&, float&) const = 0;
    virtual void getSurfaceData(const Vec3f, Vec3f&, Vec2f&, float, float) const = 0;
    virtual void voxelize(Octree*, unsigned int) const = 0;
    
    const Vec3f color() const { return oColor; }
    const float albedo() const { return oAlbedo; }
    
    void color(Vec3f color) { oColor = color; }
    void albedo(float albedo) { oAlbedo = albedo; }
    
    private :
    virtual void update() = 0;
    
    Vec3f oColor;
    float oAlbedo;
};

#endif /* Object_hpp */
