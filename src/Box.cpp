//
//  Box.cpp
//  Renderer
//
//  Created by Victor on 27/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Box.hpp"

Box::Box() :
    bPosition(0, 0, 0),
    bDim(1, 1, 1)
{
    bBounds[0] = Vec3f(bPosition.x(),
                       bPosition.y(),
                       bPosition.z());
    bBounds[1] = Vec3f(bPosition.x() + bDim.x(),
                       bPosition.y() + bDim.y(),
                       bPosition.z() + bDim.z());
}

Box::Box(Vec3f position, Vec3f dimension) :
    bPosition(position),
    bDim(dimension)
{
    bBounds[0] = Vec3f(bPosition.x(),
                       bPosition.y(),
                       bPosition.z());
    bBounds[1] = Vec3f(bPosition.x() + bDim.x(),
                       bPosition.y() + bDim.y(),
                       bPosition.z() + bDim.z());
}

bool Box::intersect(Ray& ray, const Object*& hitObject, float& tNear) const {
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    
    tmin = (bBounds[ray.sign(0)].x() - ray.origin().x())*ray.invDir().x();
    tmax = (bBounds[1-ray.sign(0)].x() - ray.origin().x())*ray.invDir().x();
    tymin = (bBounds[ray.sign(1)].y() - ray.origin().y())*ray.invDir().y();
    tymax = (bBounds[1-ray.sign(1)].y() - ray.origin().y())*ray.invDir().y();
    
    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    
    tzmin = (bBounds[ray.sign(2)].z() - ray.origin().z())*ray.invDir().z();
    tzmax = (bBounds[1-ray.sign(2)].z() - ray.origin().z())*ray.invDir().z();
    
    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    
    ray.tMin(tmin);
    ray.tMax(tmax);
    
    /*
    if (tmin < tNear) {
        ray.t(tmin);
        hitObject = this;
        tNear = tmin;
    }
    */
    return true;
}

void Box::getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const {
}

void Box::voxelize(Octree* octree, unsigned int depth) const {
    
}

void Box::update() {
    
}