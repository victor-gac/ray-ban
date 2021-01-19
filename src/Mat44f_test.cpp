//
//  Mat44f_test.cpp
//  Renderer
//
//  Created by Victor on 13/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//
#include <iostream>

#include "Mat44f.hpp"
#include "Vec4f.hpp"

void Mat44f_test() {
    Vec4f unitVec(1.0, 1.0, 1.0, 1.0);
    Vec4f e1(1.0, 0.0, 0.0, 0.0);
    Vec4f e2(0.0, 1.0, 0.0, 0.0);
    Vec4f e3(0.0, 0.0, 1.0, 0.0);
    Vec4f e4(0.0, 0.0, 0.0, 1.0);
    
    Mat44f mat1(e1, e2, e3, e4);
    Mat44f mat2(unitVec, unitVec, unitVec, unitVec);
    Mat44f matMul, matAdd;
    
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
