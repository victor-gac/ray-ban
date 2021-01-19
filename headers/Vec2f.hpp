//
//  Vec2f.hpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Vec2f_hpp
#define Vec2f_hpp

#include <iostream>

void Vec2f_test();

class Vec2f {
    public :
    Vec2f() {
        vX = .0;
        vY = .0;
    }
    
    Vec2f(float x, float y) {
        vX = x;
        vY = y;
    }
    
    Vec2f(const Vec2f& vec) {
        vX = vec.vX;
        vY = vec.vY;
    }
    
    const float x() const { return vX; }
    const float y() const { return vY; }
    
    void x(float x) { vX = x; }
    void y(float y) { vY = y; }
   
    Vec2f& operator +=(const Vec2f& rVec) {
        (*this).vX += rVec.vX;
        (*this).vY += rVec.vY;
        
        return *this;
    }
    
    Vec2f& operator -=(const Vec2f& rVec) {
        (*this).vX -= rVec.vX;
        (*this).vY -= rVec.vY;
        
        return *this;
    }
    
    Vec2f& operator *=(const float factor) {
        (*this).vX *= factor;
        (*this).vY *= factor;
        
        return *this;
    }
    
    Vec2f& operator /=(const float factor) {
        if (factor != 0.0) {
            (*this).vX /= factor;
            (*this).vY /= factor;
        }
        return *this;
    }
    
    const float dot(Vec2f rVec);
    const float cross(Vec2f rVec);
    void normalize();
    
    void print();
    
    private :
    float vX;
    float vY;
};

inline Vec2f operator +(Vec2f lVec, const Vec2f& rVec) {
    lVec += rVec;
    return lVec;
}

inline Vec2f operator -(Vec2f lVec, const Vec2f& rVec) {
    lVec -= rVec;
    return lVec;
}

inline Vec2f operator *(Vec2f lVec, float factor) {
    lVec*=factor;
    return lVec;
}

inline Vec2f operator *(float factor, Vec2f rVec) {
    rVec*=factor;
    return rVec;
}

inline Vec2f operator /(Vec2f lVec, float factor) {
    lVec/=factor;
    return lVec;
}

#endif /* Vec2f_hpp */
