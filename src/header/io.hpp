#pragma once
#include "struct.hpp"
#include <vector>
#include <string>
using namespace std;

ParsedData parseOBJ(const string &path);

void exportToObj(const string& filename, const vector<Voxel>& voxels);

void generateCubeVertices(const Voxel& voxel, Vertex out[8]);

void generateCubeFaces(int startIdx, int faces[12][3]);