//
//  Vec4f.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Vec4f_hpp
#define Vec4f_hpp

#include <iostream>

void Vec4f_test();

class Vec4f {
    public :
    Vec4f() {
        vX = .0;
        vY = .0;
        vZ = .0;
        vT = .0;
    }
    
    Vec4f(float x, float y, float z, float t) {
        vX = x;
        vY = y;
        vZ = z;
        vT = t;
    }
    
    Vec4f(const Vec4f& vec) {
        vX = vec.vX;
        vY = vec.vY;
        vZ = vec.vZ;
        vT = vec.vT;
    }
    
    const float x() const { return vX; }
    const float y() const { return vY; }
    const float z() const { return vZ; }
    const float t() const { return vT; }
    
    void x(float x) { vX = x; }
    void y(float y) { vY = y; }
    void z(float z) { vZ = z; }
    void t(float t) { vT = t; }
    
    Vec4f& operator +=(const Vec4f& rVec) {
        (*this).vX += rVec.vX;
        (*this).vY += rVec.vY;
        (*this).vZ += rVec.vZ;
        (*this).vT += rVec.vT;
        
        return *this;
    }
    
    Vec4f& operator -=(const Vec4f& rVec) {
        (*this).vX -= rVec.vX;
        (*this).vY -= rVec.vY;
        (*this).vZ -= rVec.vZ;
        (*this).vT -= rVec.vT;
        
        return *this;
    }
    
    Vec4f& operator *=(float factor) {
        (*this).vX*=factor;
        (*this).vY*=factor;
        (*this).vZ*=factor;
        (*this).vT*=factor;
        
        return *this;
    }
    
    Vec4f& operator /=(float factor) {
        if (factor != 0.0) {
            (*this).vX/=factor;
            (*this).vY/=factor;
            (*this).vZ/=factor;
            (*this).vT/=factor;
        }
        return *this;
    }
    
    const float dot(Vec4f rVec);
    void normalize();
    
    void print();
    
    private :
    float vX;
    float vY;
    float vZ;
    float vT;
};

inline Vec4f operator +(Vec4f lVec, const Vec4f& rVec) {
    lVec += rVec;
    return lVec;
}

inline Vec4f operator -(Vec4f lVec, const Vec4f& rVec) {
    lVec -= rVec;
    return lVec;
}

inline Vec4f operator *(Vec4f lVec, float factor) {
    lVec*=factor;
    return lVec;
}

inline Vec4f operator *(float factor, Vec4f rVec) {
    rVec*=factor;
    return rVec;
}

inline Vec4f operator /(Vec4f lVec, float factor) {
    lVec/=factor;
    return lVec;
}

inline Vec4f operator /(float factor, Vec4f rVec) {
    rVec/=factor;
    return rVec;
}

#endif /* Vec4f_hpp */
