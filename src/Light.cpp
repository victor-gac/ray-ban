//
//  Light.cpp
//  Renderer
//
//  Created by Victor on 28/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Light.hpp"

Light::Light() {
    
}

Light::Light(float intensity, Vec3f position, Vec3f target, Vec3f color) :
    lIntensity(intensity),
    lPosition(position),
    lColor(color)
{
}
