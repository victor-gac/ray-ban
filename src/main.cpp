//
//  main.cpp
//  Renderer
//
//  Created by Victor on 12/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include <iostream>
#include <chrono>

#include "Scene.hpp"
#include "Mat33f.hpp"
#include "Mat44f.hpp"
#include "Vec2f.hpp"
#include "Vec3f.hpp"
#include "Camera.hpp"
#include "RandomGenerator.hpp"
#include "PointLight.hpp"
#include "Mesh.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

void buildDataSet(unsigned int);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //Vec2f_test();
    //Vec3f_test();
    //Mat33f_test();
    //Mat44f_test();
    //Camera_test();
    
    if (argc > 1) {
        std::cout << atoi(argv[1]) << std::endl;
        buildDataSet(atoi(argv[1]));
    }
    else
        buildDataSet(1);
    
    
    return 0;
}

void buildDataSet(unsigned int nb_scenes) {
    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::duration<double> time_span;
    for (unsigned int i = 0; i < nb_scenes; ++i) {
        Camera cam1(600, 600, Vec3f(RandomGenerator::getInstance().rand()*20 - 10,
                                    RandomGenerator::getInstance().rand()*20 - 10,
                                    RandomGenerator::getInstance().rand()*4 + 1), Vec3f(), 51);
        Scene mainScene(cam1);
        mainScene.addLight(new PointLight(1000.0, Vec3f(RandomGenerator::getInstance().rand()*10 - 5,
                                                        RandomGenerator::getInstance().rand()*10 - 5,
                                                        RandomGenerator::getInstance().rand()*5)));
        mainScene.addLight(new PointLight(1000.0, Vec3f(RandomGenerator::getInstance().rand()*10 - 5,
                                                        RandomGenerator::getInstance().rand()*10 - 5,
                                                        RandomGenerator::getInstance().rand()*5)));
        mainScene.addObject(new Mesh("plane_cubes.obj"));
        t1 = std::chrono::high_resolution_clock::now();
        //mainScene.voxelize(0);
        t2 = std::chrono::high_resolution_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        std::cout << "Voxelization time : " << time_span.count() << " seconds." << std::endl;
        mainScene.render(i);
        t1 = std::chrono::high_resolution_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t2);
        std::cout << "Render time : " << time_span.count() << " seconds." << std::endl;
    }
}
