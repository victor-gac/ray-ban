//
//  Vector.hpp
//  Renderer
//
//  Created by Victor on 12/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <vector>
#include <algorithm>
#include <functional>

void Vector_test();

template<typename T>
class Vector {
    public :
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    Vector(unsigned int size) :
        vData(size) {}
    
    Vector(const Vector<T>& vec) {
        std::copy(vec.begin(), vec.end(), vData.begin());
    }
    
    T &operator[](unsigned int index) { return vData[index]; }
    
    Vector<T>& operator +=(const Vector& rVec) {
        std::transform(vData.begin(), vData.end(), rVec.begin(), vData.begin(), std::plus<T>());
        
        return *this;
    }
    
    Vector<T>& operator -=(const Vector& rVec) {
        std::transform(vData.begin(), vData.end(), rVec.begin(), vData.begin(), std::minus<T>());
        
        return *this;
    }
    
    Vector<T>& operator *=(const float factor) {
        for (iterator itElem = vData.begin(); itElem != vData.end(); ++itElem)
            (*itElem) *= factor;
        
        return *this;
    }
    
    Vector<T>& operator /=(const float factor) {
        if (factor != 0.0)
            for (iterator itElem = vData.begin(); itElem != vData.end(); ++itElem)
                (*itElem) /= factor;
                
        return *this;
    }
    
    iterator begin() { return vData.begin(); }
    const_iterator begin() const { return vData.begin(); }
    iterator end() { return vData.end(); }
    const_iterator end() const { return vData.end(); }
    
    protected :
    std::vector<T> vData;
};

template<typename T>
inline Vector<T> operator +(Vector<T> lVec, const Vector<T>& rVec) {
    lVec += rVec;
    return lVec;
}

template<typename T>
inline Vector<T> operator -(Vector<T> lVec, const Vector<T>& rVec) {
    lVec -= rVec;
    return lVec;
}

template<typename T>
inline Vector<T> operator *(Vector<T> lVec, float factor) {
    lVec*=factor;
    return lVec;
}

template<typename T>
inline Vector<T> operator *(float factor, Vector<T> rVec) {
    rVec*=factor;
    return rVec;
}

template<typename T>
inline Vector<T> operator /(Vector<T> lVec, float factor) {
    lVec/=factor;
    return lVec;
}

#endif /* Vector_hpp */
