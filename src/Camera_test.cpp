//
//  Camera_test.cpp
//  Renderer
//
//  Created by Victor on 26/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include <iostream>

#include "Camera.hpp"
#include "Vec3f.hpp"
#include "Mat33f.hpp"
#include "Mat44f.hpp"

void Camera_test() {
    std::cout << "CAMERA TEST" << std::endl;
    
    Camera cam(600, 600, Vec3f(10.0, 10.0, 10.0), Vec3f(), 90);
    
    std::cout << "width : " << cam.width() << std::endl;
    std::cout << "height : " << cam.height() << std::endl;
    std::cout << "fov : " << cam.fov() << std::endl;
    std::cout << "camera to world matrix : " << std::endl;
    cam.matrix().print();
    
    Vec3f camToWorld = cam.matrix()*Vec3f(0, 0, 0);
    camToWorld.print();
    
    Vec3f v1 = cam.matrix()*Vec3f(1, 0, -sqrt(300));
    v1.print();
}