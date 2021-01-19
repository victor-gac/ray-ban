//
//  RandomGenerator.hpp
//  Renderer
//
//  Created by Victor on 3/4/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef RandomGenerator_hpp
#define RandomGenerator_hpp

#include <random>

class RandomGenerator {
    public :
    RandomGenerator() {
        std::random_device rd;
        rGenerator = std::mt19937(rd());
        rDistribution = std::uniform_real_distribution<>(0, 1);
    }
    
    std::mt19937& getGen() { return rGenerator; }
    float rand() { return rDistribution(rGenerator); }
    
    static RandomGenerator& getInstance() {
        static RandomGenerator instance;
        
        return instance;
    }
    
    private :
    std::mt19937 rGenerator;
    std::uniform_real_distribution<> rDistribution;
};

#endif /* RandomGenerator_hpp */
