//
//  Mat33f.hpp
//  Renderer
//
//  Created by Victor on 13/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Mat33f_hpp
#define Mat33f_hpp

#include <vector>

#include "Vec3f.hpp"

void Mat33f_test();

class Mat33f {
    public :
    Mat33f() :
        tColumns(3) {}
    Mat33f(const Vec3f col1, const Vec3f col2, const Vec3f col3) :
        tColumns(3) {
        tColumns[0] = col1;
        tColumns[1] = col2;
        tColumns[2] = col3;
    }
    
    Vec3f column(unsigned int i) const { return tColumns[i]; };
    
    Mat33f operator +=(const Mat33f& rMat) {
        (*this).tColumns[0] += rMat.column(0);
        (*this).tColumns[1] += rMat.column(1);
        (*this).tColumns[2] += rMat.column(2);
        
        return *this;
    }
    
    Mat33f operator -=(const Mat33f& rMat) {
        (*this).tColumns[0] -= rMat.column(0);
        (*this).tColumns[1] -= rMat.column(1);
        (*this).tColumns[2] -= rMat.column(2);
        
        return *this;
    }
    
    Mat33f operator *=(const float factor) {
        (*this).tColumns[0]*=factor;
        (*this).tColumns[1]*=factor;
        (*this).tColumns[2]*=factor;
        
        return *this;
    }
    
    Mat33f operator /=(const float factor) {
        if (factor != 0.0) {
            (*this).tColumns[0]/=factor;
            (*this).tColumns[1]/=factor;
            (*this).tColumns[2]/=factor;
        }
        
        return *this;
    }

    
    void print();
    
    private :
    std::vector<Vec3f> tColumns;
};

inline Vec3f operator *(const Mat33f& mat, const Vec3f& rVec) {
    float x = 0.0, y = 0.0, z = 0.0;

    x = mat.column(0).x()*rVec.x() + mat.column(1).x()*rVec.y() + mat.column(2).x()*rVec.z();
    y = mat.column(0).y()*rVec.x() + mat.column(1).y()*rVec.y() + mat.column(2).y()*rVec.z();
    z = mat.column(0).z()*rVec.x() + mat.column(1).z()*rVec.y() + mat.column(2).z()*rVec.z();
    
    return Vec3f(x, y, z);
}

inline Mat33f operator *(const Mat33f& lMat, const Mat33f& rMat) {
    Vec3f col1, col2, col3;
    
    col1 = lMat*rMat.column(0);
    col2 = lMat*rMat.column(1);
    col3 = lMat*rMat.column(2);
    
    return Mat33f(col1, col2, col3);
}

inline Mat33f operator +(Mat33f lMat, const Mat33f& rMat) {
    lMat += rMat;
    return lMat;
}

inline Mat33f operator -(Mat33f lMat, const Mat33f& rMat) {
    lMat -= rMat;
    return lMat;
}

inline Mat33f operator *(Mat33f lMat, float factor) {
    lMat*=factor;
    return lMat;
}

inline Mat33f operator *(float factor, Mat33f lMat) {
    lMat*=factor;
    return lMat;
}

inline Mat33f operator /(Mat33f lMat, float factor) {
    lMat/=factor;
    return lMat;
}

#endif /* Mat33f_hpp */
