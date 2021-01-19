//
//  Triangle.cpp
//  Renderer
//
//  Created by Victor on 27/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Triangle.hpp"
#include "Box.hpp"
#include "Octree.hpp"

#include <cmath>

#define CULLING

Triangle::Triangle(Vec3f& A, Vec3f& B, Vec3f& C, Vec3f& ANormal, Vec3f& BNormal, Vec3f& CNormal) :
    tA(A),
    tB(B),
    tC(C),
    tANormal(ANormal),
    tBNormal(BNormal),
    tCNormal(CNormal)
{
    update();
    float epsilon = 0.1;
    float xMax = std::max(std::max(tA.x(), tB.x()), tC.x()) + epsilon;
    float xMin = std::min(std::min(tA.x(), tB.x()), tC.x()) - epsilon;
    float yMax = std::max(std::max(tA.y(), tB.y()), tC.y()) + epsilon;
    float yMin = std::min(std::min(tA.y(), tB.y()), tC.y()) - epsilon;
    float zMax = std::max(std::max(tA.z(), tB.z()), tC.z()) + epsilon;
    float zMin = std::min(std::min(tA.z(), tB.z()), tC.z()) - epsilon;
                          
    tBoundingBox = Box(Vec3f(xMin, yMin, zMin), Vec3f(xMax - xMin, yMax - yMin, zMax - zMin));
}

bool Triangle::intersect(Ray& ray, const Object*& hitObject, float& tNear) const {
    if (true) { // Normal
        float kEpsilon = 10e-10;
        Vec3f AB = tB - tA;
        Vec3f AC = tC - tA;
        Vec3f pvec = ray.direction().cross(AC);
        float det = AB.dot(pvec);
    #ifdef CULLING
        // if the determinant is negative the triangle is backfacing
        // if the determinant is close to 0, the ray misses the triangle
        if (det < kEpsilon) return false;
    #else
        // ray and triangle are parallel if det is close to 0
        if (fabs(det) < kEpsilon) return false;
    #endif
        
        float invDet = 1/det;
        
        Vec3f tvec = ray.origin() - tA;
        ray.u(tvec.dot(pvec)*invDet);
        if (ray.u() < 0 || ray.u() > 1) return false;
        
        Vec3f qvec = tvec.cross(AB);
        ray.v(ray.direction().dot(qvec)*invDet);
        if (ray.v() < 0 || ray.u() + ray.v() > 1) return false;
        
        float t = AC.dot(qvec)*invDet;
        
        if (t < kEpsilon) return false;
        
        if (t < tNear) {
            ray.t(t);
            hitObject = this;
            tNear = t;
        }
        
        return true;
    } else {
        return tBoundingBox.intersect(ray, hitObject, tNear);
    }
}

void Triangle::getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const {
    if (true) { // Normal
        // Nhit = tANormal; // Flat Shading
        Nhit = (1 - v - u)*tANormal + u*tBNormal + v*tCNormal; // Smooth Shading
    }
    else {
        tBoundingBox.getSurfaceData(Phit, Nhit, tex, u, v);
    }
}

void Triangle::voxelize(Octree* octree, unsigned int depth) const {
    //tBoundingBox.voxelize(octree);
    unsigned int kMin, lMin, mMin, kMax, lMax, mMax;
    
    int p = pow(2.0, depth);
    
    Vec3f res = (*octree).dim()/p;
    
    kMin = std::max(int((tBoundingBox.position().x() + (*octree).xMax())/res.x()) - 1, 0);
    lMin = std::max(int((tBoundingBox.position().y() + (*octree).yMax())/res.y()) - 1, 0);
    mMin = std::max(int((tBoundingBox.position().z() + (*octree).zMax())/res.z()) - 1, 0);
    
    kMax = std::min(int((tBoundingBox.position().x() + tBoundingBox.dimension().x() + (*octree).xMax())/res.x()) + 1, p - 1);
    lMax = std::min(int((tBoundingBox.position().y() + tBoundingBox.dimension().y() + (*octree).yMax())/res.y()) + 1, p - 1);
    mMax = std::min(int((tBoundingBox.position().z() + tBoundingBox.dimension().z() + (*octree).zMax())/res.z()) + 1, p - 1);
   
    for (unsigned int k = kMin; k <= kMax; ++k)
        for (unsigned int l = lMin; l <= lMax; ++l)
            for (unsigned int m = mMin; m <= mMax; ++m)
                ((*octree).octree(k, l, m, depth))->add((Object*)this);
                
}

void Triangle::flip() {
    //tNormal*=-1;
}

void Triangle::dump() {
    tANormal.print();
    tBNormal.print();
    tCNormal.print();
}

void Triangle::update() {
    //tNormal = (tB - tA).cross(tC - tA);
    //tNormal.normalize(); // Update normal with respect to its edges
}