//
//  Sun.hpp
//  Renderer
//
//  Created by Victor on 1/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Sun_hpp
#define Sun_hpp

#include "Light.hpp"

class Sun : public Light {
    public :
    Sun();
    Sun(float intensity, Vec3f position = Vec3f(0.0, 0.0, 50.0), Vec3f color = Vec3f(0.3, 0.0, 0.0), Vec3f target = Vec3f(0.0, 0.0, 0.0));
    
    Vec3f direction() { return lDirection; }
    
    void direction(const Vec3f direction) { lDirection = direction; }
    
    void illuminate(Ray& ray, Vec3f& lightIntensity) const;
    
    private :
    void update();
    
    Vec3f lDirection;
};

#endif /* Sun_hpp */
