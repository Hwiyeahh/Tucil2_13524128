#include <vector>
#include <algorithm>
#include "../header/octree.hpp"
using namespace std;

void subdivide(const BoundingBox& parent, BoundingBox child[8]) {
    Vertex mid;
    mid.x = (parent.minB.x + parent.maxB.x)/2;
    mid.y = (parent.minB.y + parent.maxB.y)/2;
    mid.z = (parent.minB.z + parent.maxB.z)/2;

    float xs[] = {parent.minB.x, mid.x, parent.maxB.x};
    float ys[] = {parent.minB.y, mid.y, parent.maxB.y};
    float zs[] = {parent.minB.z, mid.z, parent.maxB.z};

    int idx = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                child[idx].minB = {xs[i], ys[j], zs[k]};
                child[idx].maxB = {xs[i+1], ys[j+1], zs[k+1]};
                idx++;
            }
        }
    }
}

bool intersect(const BoundingBox& b, const Face& f) {
    float tMinX = min({f.v1.x, f.v2.x, f.v3.x});
    float tMaxX = max({f.v1.x, f.v2.x, f.v3.x});
    float tMinY = min({f.v1.y, f.v2.y, f.v3.y});
    float tMaxY = max({f.v1.y, f.v2.y, f.v3.y});
    float tMinZ = min({f.v1.z, f.v2.z, f.v3.z});
    float tMaxZ = max({f.v1.z, f.v2.z, f.v3.z});

    return (b.minB.x <= tMaxX && b.maxB.x >= tMinX) && (b.minB.y <= tMaxY && b.maxB.y >= tMinY) && (b.minB.z <= tMaxZ && b.maxB.z >= tMinZ);
}

void buildOctree(OctreeNode* node, const vector<Face>& faces, int curDepth, int maxDepth, vector<int>& nodesCreated, vector<int>& nodesSkipped, vector<Voxel>& voxels) {
    nodesCreated[curDepth]++;

    if (curDepth == maxDepth) {
        node->isLeaf = true;

        Voxel vox;
        const Vertex& min = node->box.minB;
        const Vertex& max = node->box.maxB;
        vox.center = {(min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2};
        vox.size = max.x - min.x;
        voxels.push_back(vox);

        return;
    }
    else node->isLeaf = false;

    for (int i = 0; i < 8; i++) {
        node->children[i] = nullptr;
    }
    
    BoundingBox childBox[8];
    subdivide(node->box, childBox);
    
    for (int i = 0; i < 8; i++) {
        vector<Face> relevant;

        for (const auto& f : faces) {
            if (intersect(childBox[i], f)) {
                relevant.push_back(f);
            }
        }
        
        if (relevant.empty()) {
            nodesSkipped[curDepth+1]++;
            continue;
        }
        
        OctreeNode* childNode = new OctreeNode();
        childNode->box = childBox[i];
        childNode->depth = curDepth + 1;
        childNode->isLeaf = false;
        node->children[i] = childNode;

        buildOctree(childNode, relevant, curDepth + 1, maxDepth, nodesCreated, nodesSkipped, voxels);
    }
}