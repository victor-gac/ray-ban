//
//  Box.hpp
//  Renderer
//
//  Created by Victor on 27/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include "Object.hpp"
#include "Vec3f.hpp"

class Box : public Object {
    public :
    Box();
    Box(Vec3f position, Vec3f dimension = Vec3f(1, 1, 1));
    
    Vec3f position() const { return bPosition; }
    Vec3f dimension() const { return bDim; }
    
    virtual bool intersect(Ray& ray, const Object*& hitObject, float& tNear) const;
    virtual void getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const;
    virtual void voxelize(Octree* octree, unsigned int depth) const;
    
    private :
    void update();
    
    Vec3f bPosition;
    Vec3f bDim;
    Vec3f bBounds[2];
};

#endif /* Box_hpp */
