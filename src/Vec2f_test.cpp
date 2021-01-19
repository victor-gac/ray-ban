//
//  Vec2f_test.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Vec2f.hpp"

void Vec2f_test() {
    Vec2f a(1.0, 2.0);
    Vec2f b(1.0, 1.0);
    Vec2f c;
    
    // ADDITION
    std::cout << "ADDITION" << std::endl;
    c = a + b;
    c.print();
    
    // MULTIPLICATION
    std::cout << "MULTIPLICATION" << std::endl;
    c = a*2 + 2*b;
    c.print();
    
    // DOT PRODUCT
    std::cout << "DOT PRODUCT" << std::endl;
    std::cout << a.dot(b) << std::endl;
    
    // NORMALIZATION
    std::cout << "NORMALIZATION" << std::endl;
    b.normalize();
    b.print();
}
