#pragma once
#include "struct.hpp"

void subdivide(const BoundingBox& parent, BoundingBox child[8]);

bool intersect(const BoundingBox& b, const Face& f);

void buildOctree(OctreeNode* node, const vector<Face>& faces, int curDepth, int maxDepth, vector<int>& nodesCreated, vector<int>& nodesSkipped, vector<Voxel>& voxels);