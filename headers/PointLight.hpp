//
//  PointLight.hpp
//  Renderer
//
//  Created by Victor on 1/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include "Light.hpp"

class PointLight : public Light {
    public :
    PointLight();
    PointLight(float intensity, Vec3f position = Vec3f(0.0, 0.0, 10.0), Vec3f color = Vec3f(0.3, 0.0, 0.0));
    
    void illuminate(Ray& ray, Vec3f& lightIntensity) const;
    
    private :
    void update();
};

#endif /* PointLight_hpp */
