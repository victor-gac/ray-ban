//
//  Mesh.cpp
//  Renderer
//
//  Created by Victor on 28/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#include "Mesh.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Vec3f.hpp"

Mesh::Mesh() {
    
}

Mesh::Mesh(std::string filename) {
    loadOBJ(filename);
}

bool Mesh::intersect(Ray& ray, const Object*& hitObject, float& tNear) const {
    for (const_iterator itTriangle = mTriangles.begin(); itTriangle != mTriangles.end(); ++itTriangle)
        (*itTriangle).intersect(ray, hitObject, tNear);
    
    return (hitObject != nullptr);
}

void Mesh::getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const {
    
}

void Mesh::voxelize(Octree* octree, unsigned int depth) const {
    for (const_iterator itTriangle = mTriangles.begin(); itTriangle != mTriangles.end(); ++itTriangle)
        (*itTriangle).voxelize(octree, depth);
}

void Mesh::loadOBJ(std::string filename) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    
    std::ifstream file(filename, std::ios::in);
    
    if (!file) {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(1);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0,2) == "v ") {
            std::istringstream s(line.substr(2));
            float x, y, z;
            s >> x;
            s >> y;
            s >> z;
            mVertices.push_back(Vec3f(x, y, z));
        } else if (line.substr(0,3) == "vt ") {
            std::istringstream s(line.substr(3));
            float u, v, w;
            s >> u;
            s >> v;
            s >> w;
            mUVs.push_back(Vec3f(u, v, w));
        } else if (line.substr(0,3) == "vn ") {
            std::istringstream s(line.substr(3));
            float x, y, z;
            s >> x;
            s >> y;
            s >> z;
            Vec3f v(x, y, z);
            v.normalize();
            mNormals.push_back(v);
        } else if (line.substr(0,2) == "f ") {
            std::istringstream s(line.substr(2));
            std::string e[3];
            s >> e[0];
            s >> e[1];
            s >> e[2];
            
            for (unsigned int i = 0; i < 3; ++i) {
                std::string items[3];
                std::stringstream s(e[i]);
                
                for (unsigned int j = 0; j < 3; ++j)
                    std::getline(s, items[j], '/');
               
                vertexIndices.push_back(items[0].empty() ? -1 : std::stoi(items[0]) - 1);
                uvIndices.push_back(items[1].empty() ? -1 : std::stoi(items[1]) - 1);
                normalIndices.push_back(items[2].empty() ? -1 : std::stoi(items[2]) - 1);
                
            }
        } else if (line[0] == '#') {
            /* comments */
        }
        else {
            /* errors */
        }
    }
    
    file.close();
    
    for (unsigned int i = 0; i < vertexIndices.size()/3; ++i) {
        Triangle t(mVertices[vertexIndices[3*i]],
                   mVertices[vertexIndices[3*i + 1]],
                   mVertices[vertexIndices[3*i + 2]],
                   mNormals[normalIndices[3*i]],
                   mNormals[normalIndices[3*i + 1]],
                   mNormals[normalIndices[3*i + 2]]);
        //t.dump();
        mTriangles.push_back(t);
    }
}

void Mesh::update() {
    
}