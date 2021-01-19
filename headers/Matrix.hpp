#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <iterator>
#include <cassert>
#include <stdexcept>
#include <vector>

template<typename T>
class Matrix {
    public:
        typedef typename std::vector<T>::iterator iterator;
        typedef typename std::vector<T>::const_iterator const_iterator;

        Matrix();

        bool empty() const { return mData.empty(); }
        unsigned int size() { return mDimX * mDimY; }
        inline virtual void reserve(unsigned int x, unsigned int y = 1);
        inline virtual void resize(unsigned int x, unsigned int y = 1, const T& value = T());
        inline virtual void assign(unsigned int x, unsigned int y, const T& value);
        inline virtual void clear();

        iterator begin() { return mData.begin(); }
        const_iterator begin() const { return mData.begin(); }
        iterator end() { return mData.end(); }
        const_iterator end() const { return mData.end(); }

        inline typename std::vector<T>::reference operator ()(unsigned int i, unsigned int j);
        inline typename std::vector<T>::const_reference operator ()(unsigned int i, unsigned int j) const;
        inline typename std::vector<T>::reference operator ()(unsigned int index);
        inline typename std::vector<T>::const_reference operator ()(unsigned int index) const;
        typename std::vector<T>::reference at(unsigned int i, unsigned int j) { return mData.at(j*mDimX + i); }
        typename std::vector<T>::const_reference at(unsigned int i, unsigned int j) const { return mData.at(j*mDimX + i); }
        typename std::vector<T>::reference at(unsigned int index) { return mData.at(index); }
        typename std::vector<T>::const_reference at(unsigned int index) const { return mData.at(index); }

        void dump();

        virtual ~Matrix();

    protected:

    private:
        unsigned int mDimX;
        unsigned int mDimY;
        std::vector<T> mData;
};

template<typename T>
Matrix<T>::Matrix() {
    mDimX = 1;
    mDimY = 1;
}

template<typename T>
void Matrix<T>::reserve(unsigned int x, unsigned int y) {
    mDimX = x;
    mDimY = y;
    mData.reserve(size());
}

template<typename T>
void Matrix<T>::resize(unsigned int x, unsigned int y, const T& value) {
    mDimX = x;
    mDimY = y;
    mData.resize(size(), value);
}

template<typename T>
void Matrix<T>::assign(unsigned int x, unsigned int y, const T& value) {
    mDimX = x;
    mDimY = y;
    mData.assign(size(), value);
}

template<typename T>
void Matrix<T>::clear() {
    mDimX = 0;
    mDimY = 0;
    mData.clear();
}

template <class T>
typename std::vector<T>::reference Matrix<T>::operator ()(unsigned int i, unsigned int j) {
    assert(i < mDimX);
    assert(j < mDimY);

    return mData[j*mDimX + i];
}

template <class T>
typename std::vector<T>::const_reference Matrix<T>::operator ()(unsigned int i, unsigned int j) const {
    assert(i < mDimX);
    assert(j < mDimY);

    return mData[j*mDimX + i];
}

template <class T>
typename std::vector<T>::reference Matrix<T>::operator ()(unsigned int index) {
    assert(index < mData.size());

    return mData[index];
}

template <class T>
typename std::vector<T>::const_reference Matrix<T>::operator ()(unsigned int index) const {
    assert(index < mData.size());

    return mData[index];
}

template<typename T>
void Matrix<T>::dump() {
    for (iterator it = mData.begin(); it != mData.end(); ++it)
        std::cout << (*it) << " ";
    std::cout << std::endl;
}

template<typename T>
Matrix<T>::~Matrix() {
    clear();
}

#endif // Matrix_H
