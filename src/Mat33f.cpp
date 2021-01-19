//
//  Mat33f.cpp
//  Renderer
//
//  Created by Victor on 13/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//
#include <iostream>

#include "Mat33f.hpp"

void Mat33f::print() {
    for (unsigned int i = 0; i < 3; ++i) {
        tColumns[i].print();
    }
}