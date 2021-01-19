//
//  Octree.cpp
//  Renderer
//
//  Created by Victor on 4/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Octree.hpp"

#include <vector>
#include <cmath>

#include "Object.hpp"

Octree::Octree() :
    oDepth(0),
    oDim(10.0, 10.0, 10.0),
    oCenter(0),
    oBoundingBox(Vec3f(-5, -5, -5), Vec3f(10, 10, 10))
{
    for (unsigned int i = 0; i < 8; ++i)
        oChildren[i] = NULL;
}

Octree::Octree(unsigned int depth, Vec3f dim, Vec3f center) :
    oDepth(depth),
    oDim(dim),
    oCenter(center),
    oBoundingBox(center - dim/2, dim)
{
    for (unsigned int i = 0; i < 8; ++i)
        oChildren[i] = NULL;
    
    //oCenter.print();
}

unsigned int Octree::density(unsigned int depth) {
    if (oDepth == depth) {
        return 1;
    }
    
    unsigned int dens = 0;
    
    for (unsigned int i = 0 ; i < 8; ++i) {
        if (oChildren[i] != NULL) {
            dens += (*oChildren[i]).density(depth);
        }
    }
    
    return dens;
}

Octree* Octree::octree(unsigned int k, unsigned int l, unsigned int m, unsigned int depth) {
    if (oDepth == depth) {
        return this;
    }
    
    unsigned int p = pow(2, depth - oDepth - 1);
    // Local coordinates
    int coord[3];
    k/p >= 1 ? coord[0] = 1 : coord[0] = 0;
    l/p >= 1 ? coord[1] = 1 : coord[1] = 0;
    m/p >= 1 ? coord[2] = 1 : coord[2] = 0;
    
    //std::cout << p << " : " << k  << " " << l << " " << m << std::endl;
    //std::cout << p << " : " << coord[0]  << " " << coord[1] << " " << coord[2] << std::endl;
    
    int offset = 4*coord[2] + 2*coord[1] + coord[0];

    if (oChildren[offset] == NULL)
        oChildren[offset] = new Octree(oDepth + 1, oDim/2,
                                       oCenter + Vec3f((2*coord[0] - 1)*oDim.x()/4,
                                                       (2*coord[1] - 1)*oDim.y()/4,
                                                       (2*coord[2] - 1)*oDim.z()/4));
    
    return (*oChildren[offset]).octree(k - coord[0]*p,
                                       l - coord[1]*p,
                                       m - coord[2]*p,
                                       depth);
}


void Octree::add(Object* object) {
    oObjects.push_back(object);
}

bool Octree::intersect(Ray& ray, const Object*& hitObject, float& tNear) const {
    /*if (!oObjects.empty()) {
        std::vector<Object*>::const_iterator itObject = oObjects.begin();
        for (; itObject != oObjects.end(); ++itObject)
            (**itObject).intersect(ray, hitObject, tNear);
    } else {
        for (unsigned int i = 0 ; i < 8; ++i)
            if (oChildren[i] != NULL)
                (*oChildren[i]).intersect(ray, hitObject, tNear);
    }
    
    return (hitObject != NULL);*/
    
    /* v1 Naive
    //if (oBoundingBox.intersect(ray, hitObject, tNear)) {
    if (true) {
        bool leaf = true;
        for (unsigned int i = 0 ; i < 8; ++i) {
            if (oChildren[i] != NULL) {
                leaf = false;
                (*oChildren[i]).intersect(ray, hitObject, tNear);
            }
        }
        
        if (leaf) {
            std::vector<Object*>::const_iterator itObject = oObjects.begin();
            for (; itObject != oObjects.end(); ++itObject) {
                (**itObject).intersect(ray, hitObject, tNear);
            }
        }
        
    }
    
    return (hitObject != NULL);*/
    
    /* v2 Tracing through voxel octree */
    // If it contains objects, then it is a leaf
    // and we can loop over these objects
    if (!oObjects.empty()) {
        //std::cout << oObjects.size() << std::endl;
        //oCenter.print();
        std::vector<Object*>::const_iterator itObject = oObjects.begin();
        for (; itObject != oObjects.end(); ++itObject) {
            (**itObject).intersect(ray, hitObject, tNear);
        }
    } else {
        if (oDepth == 0) {
            if(!oBoundingBox.intersect(ray, hitObject, tNear))
                return false;
        }
        
        // A input intersection point
        Vec3f interA = ray.origin() + ray.tMin()*ray.direction();
        // Relative position from center
        Vec3f relativePos = oCenter - interA;
        
        float dir[3];
        dir[0] = ray.direction().x();
        dir[1] = ray.direction().y();
        dir[2] = ray.direction().z();
        
        // Local coordinates
        int coord[3];
        relativePos.x() > 0 ? coord[0] = 0 : coord[0] = 1;
        relativePos.y() > 0 ? coord[1] = 0 : coord[1] = 1;
        relativePos.z() > 0 ? coord[2] = 0 : coord[2] = 1;
        
        // Intersection distance
        float t[3];
        t[0] = (oCenter.x() - ray.origin().x())*ray.invDir().x();
        t[1] = (oCenter.y() - ray.origin().y())*ray.invDir().y();
        t[2] = (oCenter.z() - ray.origin().z())*ray.invDir().z();
    
        while (true) {
            int offset = 4*coord[2] + 2*coord[1] + coord[0];
            // Process current block
            if (offset >= 0 && offset < 8) {
                if (oChildren[offset] != NULL)
                    (*oChildren[offset]).intersect(ray, hitObject, tNear);
            }
            
            // Holly trick - get the axis of the closest intersection
            unsigned int k = ((t[0] < t[1]) << 2) + ((t[0] < t[2]) << 1) + ((t[1] < t[2]));
            static const unsigned int map[8] = {2, 1, 2, 1, 2, 2, 0, 0};
            unsigned int axis = map[k];
            
            if (dir[axis] > 0)
                coord[axis]++;
            else
                coord[axis]--;
            // Set new tMin as t[axis]
            ray.tMin(t[axis]);
            if (ray.tMin() >= ray.tMax()) break;
            // Reject this axis
            t[axis] = ray.tMax();
        }
    }
    
    return (hitObject != NULL);
}

Octree::~Octree() {
    for (unsigned int i = 0; i < 8; ++i) 
        if (oChildren[i] != NULL)
            delete oChildren[i];
}
