//
//  Mat33f_test.cpp
//  Renderer
//
//  Created by Victor on 13/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//
#include <iostream>

#include "Mat33f.hpp"
#include "Vec3f.hpp"

void Mat33f_test() {
    Vec3f unitVec(1.0, 1.0, 1.0);
    Vec3f e1(1.0, 0.0, 0.0);
    Vec3f e2(0.0, 1.0, 0.0);
    Vec3f e3(0.0, 0.0, 1.0);
    
    Mat33f mat1(e1, e2, e3);
    Mat33f mat2(unitVec, unitVec, unitVec);
    Mat33f matMul, matAdd;
    
    // MATRIX ADDITION
    std::cout << "MATRIX ADDITION" << std::endl;
    matAdd = mat1 + mat2;
    matAdd.print();
    
    // MATRIX MULTIPLICATION
    std::cout << "MATRIX MULTIPLICATION" << std::endl;
    matMul = mat1*mat2;
    matMul.print();
    matMul *= 2;
    matMul.print();
    matMul /= 2;
    matMul.print();
}