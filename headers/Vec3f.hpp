//
//  Vec3f.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Vec3f_hpp
#define Vec3f_hpp

#include <iostream>

void Vec3f_test();

class Vec3f {
    public :
    Vec3f() {
        vX = .0;
        vY = .0;
        vZ = .0;
    }
    
    Vec3f(float v) {
        vX = v;
        vY = v;
        vZ = v;
    }
    
    Vec3f(float x, float y, float z) {
        vX = x;
        vY = y;
        vZ = z;
    }

    Vec3f(const Vec3f& vec) {
        vX = vec.vX;
        vY = vec.vY;
        vZ = vec.vZ;
    }
    
    const float x() const { return vX; }
    const float y() const { return vY; }
    const float z() const { return vZ; }
   
    void x(float x) { vX = x; }
    void y(float y) { vY = y; }
    void z(float z) { vZ = z; }
    
    Vec3f& operator +=(const Vec3f& rVec) {
        (*this).vX += rVec.vX;
        (*this).vY += rVec.vY;
        (*this).vZ += rVec.vZ;
        
        return *this;
    }
    
    Vec3f& operator -=(const Vec3f& rVec) {
        (*this).vX -= rVec.vX;
        (*this).vY -= rVec.vY;
        (*this).vZ -= rVec.vZ;
        
        return *this;
    }
    
    Vec3f& operator *=(const float factor) {
        (*this).vX *= factor;
        (*this).vY *= factor;
        (*this).vZ *= factor;
        
        return *this;
    }
    
    Vec3f& operator /=(const float factor) {
        if (factor != 0.0) {
            (*this).vX /= factor;
            (*this).vY /= factor;
            (*this).vZ /= factor;
        }
        return *this;
    }
    
    const float dot(Vec3f rVec) const;
    const Vec3f cross(Vec3f rVec) const;
    void normalize();
    const float norm();
    
    void print() const;
    
    private :
    float vX;
    float vY;
    float vZ;
};

inline Vec3f operator +(Vec3f lVec, const Vec3f& rVec) {
    lVec += rVec;
    return lVec;
}

inline Vec3f operator -(Vec3f lVec, const Vec3f& rVec) {
    lVec -= rVec;
    return lVec;
}

inline Vec3f operator *(Vec3f lVec, float factor) {
    lVec*=factor;
    return lVec;
}

inline Vec3f operator *(float factor, Vec3f rVec) {
    rVec*=factor;
    return rVec;
}

inline Vec3f operator /(Vec3f lVec, float factor) {
    lVec/=factor;
    return lVec;
}

#endif /* Vec3f_hpp */
