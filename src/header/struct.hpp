#pragma once
#include <vector>
using namespace std;

struct Vertex {
    float x, y, z;
};

struct Face {
    Vertex v1, v2, v3;
};

struct BoundingBox {
    Vertex minB, maxB;
};

struct ParsedData {
    vector<Face> faces;
    BoundingBox bound;
};

struct Voxel {
    Vertex center;
    float size;
};

struct OctreeNode {
    BoundingBox box;
    int depth;
    bool isLeaf;
    OctreeNode* children[8];
};