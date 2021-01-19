//
//  Mat44f.hpp
//  Renderer
//
//  Created by Victor on 13/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Mat44f_hpp
#define Mat44f_hpp

#include <vector>
#include <cmath>

#include "Mat33f.hpp"
#include "Vec4f.hpp"
#include "Vec3f.hpp"

void Mat44f_test();

class Mat44f {
    public :
    Mat44f() :
        tColumns(4) {}
    Mat44f(const Vec4f col1, const Vec4f col2, const Vec4f col3, const Vec4f col4) :
        tColumns(4) {
        tColumns[0] = col1;
        tColumns[1] = col2;
        tColumns[2] = col3;
        tColumns[3] = col4;
    }
    
    Vec4f column(unsigned int i) const { return tColumns[i]; };
    Mat33f sub() { return Mat33f(Vec3f(tColumns[0].x(), tColumns[0].y(), tColumns[0].z()),
                                 Vec3f(tColumns[1].x(), tColumns[1].y(), tColumns[1].z()),
                                 Vec3f(tColumns[2].x(), tColumns[2].y(), tColumns[2].z())); }
    
    void transpose();
    
    Mat44f operator +=(const Mat44f& rMat) {
        (*this).tColumns[0] += rMat.column(0);
        (*this).tColumns[1] += rMat.column(1);
        (*this).tColumns[2] += rMat.column(2);
        (*this).tColumns[3] += rMat.column(3);
        
        return *this;
    }
    
    Mat44f operator -=(const Mat44f& rMat) {
        (*this).tColumns[0] -= rMat.column(0);
        (*this).tColumns[1] -= rMat.column(1);
        (*this).tColumns[2] -= rMat.column(2);
        (*this).tColumns[3] -= rMat.column(3);
        
        return *this;
    }
    
    Mat44f operator *=(const float factor) {
        (*this).tColumns[0]*=factor;
        (*this).tColumns[1]*=factor;
        (*this).tColumns[2]*=factor;
        (*this).tColumns[3]*=factor;
        
        return *this;
    }
    
    Mat44f operator /=(const float factor) {
        if (factor != 0.0) {
            (*this).tColumns[0]/=factor;
            (*this).tColumns[1]/=factor;
            (*this).tColumns[2]/=factor;
            (*this).tColumns[3]/=factor;
        }
        
        return *this;
    }
    
    
    void print();
    
    private :
    std::vector<Vec4f> tColumns;
};

inline Vec4f operator *(const Mat44f& mat, const Vec4f& rVec) {
    float x = 0.0, y = 0.0, z = 0.0, t = 0.0;
    
    for (unsigned int i = 0; i < 4; ++i) {
        x += mat.column(i).x()*rVec.x();
        y += mat.column(i).y()*rVec.y();
        z += mat.column(i).z()*rVec.z();
        t += mat.column(i).t()*rVec.t();
    }
    
    return Vec4f(x, y, z, t);
}

inline Vec3f operator *(const Mat44f& mat, const Vec3f& rVec) {
    float x = 0.0, y = 0.0, z = 0.0;

    x = mat.column(0).x()*rVec.x() + mat.column(1).x()*rVec.y() + mat.column(2).x()*rVec.z() + mat.column(3).x();
    y = mat.column(0).y()*rVec.x() + mat.column(1).y()*rVec.y() + mat.column(2).y()*rVec.z() + mat.column(3).y();
    z = mat.column(0).z()*rVec.x() + mat.column(1).z()*rVec.y() + mat.column(2).z()*rVec.z() + mat.column(3).z();
    
    return Vec3f(x, y, z);
}

inline Mat44f operator *(const Mat44f& lMat, const Mat44f& rMat) {
    Vec4f col1, col2, col3, col4;
    
    col1 = lMat*rMat.column(0);
    col2 = lMat*rMat.column(1);
    col3 = lMat*rMat.column(2);
    col4 = lMat*rMat.column(3);
    
    return Mat44f(col1, col2, col3, col4);
}

inline Mat44f operator +(Mat44f lMat, const Mat44f& rMat) {
    lMat += rMat;
    return lMat;
}

inline Mat44f operator -(Mat44f lMat, const Mat44f& rMat) {
    lMat -= rMat;
    return lMat;
}

inline Mat44f operator *(Mat44f lMat, float factor) {
    lMat*=factor;
    return lMat;
}

inline Mat44f operator *(float factor, Mat44f lMat) {
    lMat*=factor;
    return lMat;
}

inline Mat44f operator /(Mat44f lMat, float factor) {
    lMat/=factor;
    return lMat;
}

/*
 * Generate rotation matrix with respect to axis axis.
 */
class Rot44f : public Mat44f {
    public :
    Rot44f(int axis, int angleDeg);
    Rot44f(int axis, float angleRad);
    
    private :
    float rad(int degres) { return M_PI*degres/180; }
    
    int mAngleDeg;
    float mAngleRad;
};

class Trans44f : public Mat44f {
    public :
    Trans44f(Vec3f translationVec);
    
    private :
    Vec3f mTranslationVec;
};

class Scale44f : public Mat44f {
    public :
    Scale44f(Vec3f scaleVec);
    
    private :
    Vec3f mScaleFactor;
};

class Id44f : public Mat44f {
    
};

class Unit44f : public Mat44f {
    
};

#endif /* Mat44f_hpp */
