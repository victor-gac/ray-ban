//
//  Triangle.hpp
//  Renderer
//
//  Created by Victor on 27/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include "Object.hpp"
#include "Vec3f.hpp"
#include "Box.hpp"

class Triangle : public Object {
    public :
    Triangle(Vec3f& A, Vec3f& B, Vec3f& C, Vec3f& ANormal, Vec3f& BNormal, Vec3f& CNormal);
    
    virtual bool intersect(Ray& ray, const Object*& hitObject, float& tNear) const;
    virtual void getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const;
    virtual void voxelize(Octree* octree, unsigned int depth) const;
    void flip();
    
    //DEBUG
    void dump();
    
    private :
    virtual void update();
    
    Vec3f& tA;
    Vec3f& tB;
    Vec3f& tC;
    Vec3f& tANormal;
    Vec3f& tBNormal;
    Vec3f& tCNormal;
    Box tBoundingBox;
};

#endif /* Triangle_hpp */
