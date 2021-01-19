//
//  Scene.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

#include "Object.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Octree.hpp"

class Scene {
    public :
    Scene() :
        sObjects(),
        sCamera(),
        sOctree(),
        sFilename("data.dat"),
        sExportData("data.dat",  std::ios::out | std::ios::binary | std::ios::app) {}
    
    Scene(Camera camera, std::string filename = "data.dat") :
        sObjects(),
        sCamera(camera),
        sOctree(),
        sFilename(filename),
        sExportData(filename,  std::ios::out | std::ios::binary | std::ios::app) {}
    
    ~Scene() { sExportData.close(); }
    
    void voxelize(int depth);
    void render(unsigned int index);
    void addLight(Light* light) { sLights.push_back(std::unique_ptr<Light>(light)); }
    void addObject(Object* object) { sObjects.push_back(std::unique_ptr<Object>(object)); }
    
    private :
    inline float clamp(const float& lo, const float& hi, const float& v) {
        return std::max(lo, std::min(hi, v));
    }
    inline float deg2rad(const float& deg) {
        return deg*M_PI/180;
    }
    bool trace(Ray& ray, const Object*& hitObject);
    Vec3f castRay(Ray ray, unsigned int depth = 0);
    void createCoordinateSystem(const Vec3f& N, Vec3f& Nt, Vec3f& Nb);
    Vec3f uniformSampleHemisphere(const float& r1, const float& r2);
    
    Camera sCamera;
    Octree sOctree;
    unsigned int sDepth;
    std::vector<std::unique_ptr<Object>> sObjects;
    std::vector<std::unique_ptr<Light>> sLights;
    std::ofstream sExportData;
    std::string sFilename;
};

#endif /* Scene_hpp */
