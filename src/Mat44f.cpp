//
//  Mat44f.cpp
//  Renderer
//
//  Created by Victor on 13/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include <iostream>
#include <cmath>

#include "Mat44f.hpp"

void Mat44f::transpose() {
    
}

void Mat44f::print() {
    for (unsigned int i = 0; i < 4; ++i) {
        tColumns[i].print();
    }
}

Rot44f::Rot44f(int axis, int angleDeg) {
    Rot44f(axis, rad(angleDeg));
}

Rot44f::Rot44f(int axis, float angleRad) {
    switch (axis) {
        case 0 :
            Mat44f(Vec4f(1.0, 0.0, 0.0, 0.0),
                   Vec4f(0.0, cosf(angleRad), sinf(angleRad), 0.0),
                   Vec4f(0.0, -sinf(angleRad), cosf(angleRad), 0.0),
                   Vec4f(0.0, 0.0, 0.0, 1.0));
            break;
            
        case 1 :
            Mat44f(Vec4f(cosf(angleRad), 0.0, -sinf(angleRad), 0.0),
                   Vec4f(0.0, 1.0, 0.0, 0.0),
                   Vec4f(sinf(angleRad), 0.0, cosf(angleRad), 0.0),
                   Vec4f(0.0, 0.0, 0.0, 1.0));
            break;
        
        case 2 :
            Mat44f(Vec4f(cosf(angleRad), sinf(angleRad), 0.0, 0.0),
                   Vec4f(-sinf(angleRad), cosf(angleRad), 0.0, 0.0),
                   Vec4f(0.0, 0.0, 1.0, 0.0),
                   Vec4f(0.0, 0.0, 0.0, 1.0));
            break;
            
        default:
            break;
    }
}

Trans44f::Trans44f(Vec3f translationVec) {
    Mat44f(Vec4f(1.0, 0.0, 0.0, 0.0),
           Vec4f(0.0, 1.0, 0.0, 0.0),
           Vec4f(0.0, 0.0, 1.0, 0.0),
           Vec4f(translationVec.x(), translationVec.y(), translationVec.z(), 1.0));
}

Scale44f::Scale44f(Vec3f scaleVec) {
    Mat44f(Vec4f(scaleVec.x(), 0.0, 0.0, 0.0),
           Vec4f(0.0, scaleVec.y(), 0.0, 0.0),
           Vec4f(0.0, 0.0, scaleVec.z(), 0.0),
           Vec4f(0.0, 0.0, 0.0, 1.0));
}