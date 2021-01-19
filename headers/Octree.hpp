//
//  Octree.hpp
//  Renderer
//
//  Created by Victor on 4/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Octree_hpp
#define Octree_hpp

#include <vector>

#include "Triangle.hpp"
#include "Vec3f.hpp"
#include "Box.hpp"

class Object;

class Octree {
    public :
    Octree();
    Octree(unsigned int depth, Vec3f dim = Vec3f(10.0, 10.0, 10.0), Vec3f center = Vec3f());
    
    ~Octree();
    
    unsigned int depth() { return oDepth; }
    Vec3f dim() { return oDim; }
    
    unsigned int xMax() { return oDim.x()/2; }
    unsigned int yMax() { return oDim.y()/2; }
    unsigned int zMax() { return oDim.z()/2; }
     
    unsigned int density(unsigned int depth);
    Octree* octree(unsigned int k, unsigned int l, unsigned int m, unsigned int depth);
    
    void depth(unsigned int depth) { oDepth = depth; }
    void add(Object* object);
    
    bool intersect(Ray& ray, const Object*& hitObject, float& tNear) const;
    
    private :
    Box oBoundingBox;
    unsigned int oDepth;
    Vec3f oDim;
    Vec3f oCenter;
    Octree* oChildren[8];
    std::vector<Object*> oObjects;
};

#endif /* Octree_hpp */
