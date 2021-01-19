//
//  Camera.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include <cmath>

#include "Camera.hpp"

Camera::Camera() :
    cWidth(640),
    cHeight(480),
    cUnitWidth(2.0*640/480),
    cUnitHeight(2.0),
    cRatio(640/480),
    cPosition(5, 15, 15),
    cDirection(-5, -15, -15),
    cfov(51.52)
{
    cDirection.normalize();
    update();
}

Camera::Camera(unsigned int width, unsigned int height, Vec3f position, Vec3f target, float fov) :
    cWidth(width),
    cHeight(height),
    cUnitWidth(2.0*width/height),
    cUnitHeight(2.0),
    cRatio(width/height),
    cPosition(position),
    cDirection(target - position),
    cfov(fov)
{
    cDirection.normalize();
    update();
}

void Camera::focus(Vec3f target) {
    cDirection = target - cPosition;
    cDirection.normalize();
    update();
}

void Camera::update() {
    Vec3f Z(-1*cDirection);
    Z.normalize();
    Vec3f X;
    if (Z.x() == 0 && Z.y() == 0)
        X = Vec3f(1.0, 0.0, 0.0);
    else
        X = Vec3f(-Z.y(), Z.x(), 0.0);
    X.normalize();
    Vec3f Y = Z.cross(X);
    Y.normalize();
    
    cMatToWorld = Mat44f(Vec4f(X.x(), X.y(), X.z(), 0.0),
                         Vec4f(Y.x(), Y.y(), Y.z(), 0.0),
                         Vec4f(Z.x(), Z.y(), Z.z(), 0.0),
                         Vec4f(cPosition.x(), cPosition.y(), cPosition.z(), 1.0));
    
    cMatFromWorld = Mat44f(Vec4f(X.x(), Y.x(), Z.x(), 0.0),
                           Vec4f(X.y(), Y.y(), Z.y(), 0.0),
                           Vec4f(X.z(), Y.z(), Z.z(), 0.0),
                           Vec4f(-cPosition.dot(X), -cPosition.dot(Y), -cPosition.dot(Z), 1.0));
}