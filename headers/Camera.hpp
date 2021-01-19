//
//  Camera.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <vector>

#include "Mat44f.hpp"
#include "Vec3f.hpp"

void Camera_test();

class Camera {
    public :
    Camera();
    Camera(unsigned int width, unsigned int height, Vec3f position = Vec3f(15.0, 15.0, 15.0), Vec3f target = Vec3f(0.0, 0.0, 0.0), float fov = 51.52);
    
    const unsigned int width() { return cWidth; }
    const unsigned int height() { return cHeight; }
    const float ratio() { return cRatio; }
    const Vec3f position() { return cPosition; }
    const Vec3f direction() { return cDirection; }
    const float fov() { return cfov; }
    Mat44f& matrix() { return cMatToWorld; }
    Mat44f& imatrix() { return cMatFromWorld; }
    
    void position(Vec3f position) { cPosition = position; }
    void fov(float fov) { cfov = fov; }
    
    void focus(Vec3f target);
    
    private :
    void update(); // Update matrices with respect to new params
    
    unsigned int cWidth; // Pixel width
    unsigned int cHeight; // Pixel height
    float cUnitWidth; // 2.0*ratio
    float cUnitHeight; // 2.0
    float cRatio; // width/height
    Vec3f cPosition;
    Vec3f cDirection;
    float cfov;
    Mat44f cMatToWorld;
    Mat44f cMatFromWorld;
};

#endif /* Camera_hpp */
