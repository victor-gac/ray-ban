//
//  Scene.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//
#include <random>
#include <fstream>
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>

#include "Scene.hpp"
#include "Vec2f.hpp"
#include "Vec3f.hpp"
#include "Mat44f.hpp"
#include "Mat33f.hpp"
#include "Sphere.hpp"
#include "Box.hpp"
#include "Triangle.hpp"
#include "Mesh.hpp"
#include "Sun.hpp"
#include "PointLight.hpp"
#include "RandomGenerator.hpp"

void Scene::voxelize(int depth) {
    //sOctree.depth(depth);
    sDepth = depth;
    std::vector<std::unique_ptr<Object>>::iterator iter = sObjects.begin();
    
    for (; iter != sObjects.end(); ++iter)
        (**iter).voxelize(&sOctree, depth);
    
    unsigned int d = sOctree.density(depth);
    std::cout << "Density : " << d << " " << d/pow(8, depth) << std::endl;
}

void Scene::render(unsigned int index) {
    Mat44f cameraToWorld = sCamera.matrix();
    Mat33f dirToWorld = cameraToWorld.sub();
    Vec3f *pix = new Vec3f[sCamera.width()*sCamera.height()];
    float scale = tan(deg2rad(sCamera.fov()*0.5));
    
    for (unsigned int j = 0; j < sCamera.height(); ++j) {
        for (unsigned int i = 0; i < sCamera.width(); ++i) {
            float x = (2*(i + 0.5)/(float)sCamera.width() - 1)*sCamera.ratio()*scale;
            float y = (1 - 2*(j + 0.5)/(float)sCamera.height())*scale;
            Vec3f dir = dirToWorld*Vec3f(x, y, -1);
            dir.normalize();
            *(pix++) = castRay(Ray(sCamera.position(), dir));
        }
    }
    
    pix -= sCamera.width()*sCamera.height();
    
    std::ofstream ofs("./scene" + std::to_string(index) + ".ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << sCamera.width() << " " << sCamera.height() << "\n255\n";
    for (unsigned int i = 0; i < sCamera.width()*sCamera.height(); ++i) {
        char r = (char)(255*clamp(0, 1, pix[i].x()));
        char g = (char)(255*clamp(0, 1, pix[i].y()));
        char b = (char)(255*clamp(0, 1, pix[i].z()));
        ofs << r << g << b;
    }
    ofs.close();
    
    delete[] pix;
}

void Scene::createCoordinateSystem(const Vec3f& N, Vec3f& Nt, Vec3f& Nb)
{
    if (std::fabs(N.x()) > std::fabs(N.y()))
        Nt = Vec3f(N.z(), 0, -N.x())/sqrtf(N.x()*N.x() + N.z()*N.z());
    else
        Nt = Vec3f(0, -N.z(), N.y())/sqrtf(N.y()*N.y() + N.z()*N.z());
    Nb = N.cross(Nt);
}

Vec3f Scene::uniformSampleHemisphere(const float& r1, const float& r2)
{
    // cos(theta) = u1 = y
    // cos^2(theta) + sin^2(theta) = 1 -> sin(theta) = srtf(1 - cos^2(theta))
    float sinTheta = sqrtf(1 - r1 * r1);
    float phi = 2 * M_PI * r2;
    float x = sinTheta * cosf(phi);
    float z = sinTheta * sinf(phi);
    return Vec3f(x, r1, z);
}

bool Scene::trace(Ray& ray, const Object*& hitObject) {
    float tNear = Ray::tInfinity;
    
    std::vector<std::unique_ptr<Object>>::const_iterator iter = sObjects.begin();
    
    for (; iter != sObjects.end(); ++iter)
        (**iter).intersect(ray, hitObject, tNear);
     
    //sOctree.intersect(ray, hitObject, tNear);
    
    return (hitObject != nullptr);
}

Vec3f Scene::castRay(Ray ray, unsigned int depth) {
    if (depth > 1) return 0;
    
    Vec3f hitColor(0, 0, 0.3);
    const Object* hitObject = nullptr; // this is a pointer to the hit object
    
    if (trace(ray, hitObject)) {
        Vec3f Phit = ray.origin() + ray.direction()*ray.t();
        Vec3f Nhit;
        Vec2f tex;
        (*hitObject).getSurfaceData(Phit, Nhit, tex, ray.u(), ray.v());
        
        if (true) { // Normal
            Vec3f directLighting = 0;
            for (unsigned int i = 0; i < sLights.size(); ++i) {
                Vec3f lightIntensity;
                Ray shadowRay(Phit);
                const Object* hitByLightObject = nullptr; // this is a pointer to the hit object
                
                (*sLights[i]).illuminate(shadowRay, lightIntensity);
                shadowRay.origin(Phit + Nhit*0.00001);
                bool vis = !trace(shadowRay, hitByLightObject);
                directLighting += vis*lightIntensity*std::max(0.f, Nhit.dot(shadowRay.direction()));
            }
           
            Vec3f indirectLigthing = 0;
            unsigned int N = 32;// / (depth + 1);
            Vec3f Nt, Nb;
            createCoordinateSystem(Nhit, Nt, Nb);
            float pdf = 1/(2*M_PI);
            for (unsigned int n = 0; n < N; ++n) {
                float r1 = RandomGenerator::getInstance().rand();
                float r2 = RandomGenerator::getInstance().rand();
                Vec3f sample = uniformSampleHemisphere(r1, r2);
                Vec3f sampleWorld(sample.x()*Nb.x() + sample.y()*Nhit.x() + sample.z()*Nt.x(),
                                  sample.x()*Nb.y() + sample.y()*Nhit.y() + sample.z()*Nt.y(),
                                  sample.x()*Nb.z() + sample.y()*Nhit.z() + sample.z()*Nt.z());
                Ray RandomRay(Phit + sampleWorld*0.0001, sampleWorld);
                // don't forget to divide by PDF and multiply by cos(theta)
                indirectLigthing += r1*castRay(RandomRay, depth + 1)/pdf;
            }
            // divide by N
            indirectLigthing /= (float)N;
            
            hitColor = (directLighting/M_PI + 2*indirectLigthing)*0.18/*hitObject->albedo*/;
            
            /*
             * For learning purpose export :
             *    ray.origin
             *    ray.direction
             *    (ray.u, ray.v) intersection barycentric coordinates
             *    Phit           intersection absolute coordinates
             *    Nhit           normal at the intersection point
             *    hitColor       final color
             */
            if(/*int(RandomGenerator::getInstance().rand()*100) == 0*/true) {
                for (std::vector<std::unique_ptr<Light>>::iterator itLight = sLights.begin(); itLight != sLights.end(); ++itLight) {
                    sExportData << (**itLight).position().x()  << ",";
                    sExportData << (**itLight).position().y()  << ",";
                    sExportData << (**itLight).position().z()  << ",";
                }
                sExportData << ray.origin().x() << ","
                    << ray.origin().y() << ","
                    << ray.origin().z() << ","
                    << ray.direction().x() << ","
                    << ray.direction().y() << ","
                    << ray.direction().z() << ","
                    << ray.u() << ","
                    << ray.v() << ","
                    << Phit.x() << ","
                    << Phit.y() << ","
                    << Phit.z() << ","
                    << Nhit.x() << ","
                    << Nhit.y() << ","
                    << Nhit.z() << ","
                    << hitColor.x() << ","
                    << hitColor.y() << ","
                    << hitColor.z() << "\n";
            }
        } else { // Debug Bounding Box
            hitColor = std::max(0.f, ray.t())*Vec3f(1, 1, 1);
        }
    }
    
    return hitColor;
}