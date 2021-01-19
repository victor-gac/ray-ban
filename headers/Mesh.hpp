//
//  Mesh.hpp
//  Renderer
//
//  Created by Victor on 28/3/16.
//  Copyright © 2016 Victor. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>

#include "Object.hpp"
#include "Triangle.hpp"

class Mesh : public Object {
    public :
    typedef typename std::vector<Triangle>::iterator iterator;
    typedef typename std::vector<Triangle>::const_iterator const_iterator;
    
    Mesh();
    Mesh(std::string filename);
    //Mesh(std::vector<Vec3f> vertices, std::vector<Vec3f> uvs, std::vector<Vec3f> normals);
    
    iterator begin() { return mTriangles.begin(); }
    const_iterator begin() const { return mTriangles.begin(); }
    iterator end() { return mTriangles.end(); }
    const_iterator end() const { return mTriangles.end(); }
    
    virtual bool intersect(Ray& ray, const Object*& hitObject, float& tNear) const;
    virtual void getSurfaceData(const Vec3f Phit, Vec3f& Nhit, Vec2f& tex, float u, float v) const;
    virtual void voxelize(Octree* octree, unsigned int depth) const;
    
    private :
    void loadOBJ(std::string filename);
    void update();
    
    std::vector<Triangle> mTriangles;
    std::vector<Vec3f> mVertices;
    std::vector<Vec3f> mUVs;
    std::vector<Vec3f> mNormals;
    
};

#endif /* Mesh_hpp */
