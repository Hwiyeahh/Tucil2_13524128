#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../header/io.hpp"

ParsedData parseOBJ(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Failed to open file\n";
        exit(1);
    }

    ParsedData res;
    vector<Vertex> vertices;
    vector<Face> face;
    BoundingBox box;
    box.minB = {3.40282347e+38, 3.40282347e+38, 3.40282347e+38};
    box.maxB = {-3.40282e+38, -3.40282e+38, -3.40282e+38};

    string line;
    while (getline(file, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }

        stringstream ss(line);
        string type;
        ss >> type;

        if (type == "v") {
            Vertex v;
            if (ss >> v.x >> v.y >> v.z) {
                vertices.push_back(v);

                if (v.x < box.minB.x) box.minB.x = v.x;
                if (v.y < box.minB.y) box.minB.y = v.y;
                if (v.z < box.minB.z) box.minB.z = v.z;

                if (v.x > box.maxB.x) box.maxB.x = v.x;
                if (v.y > box.maxB.y) box.maxB.y = v.y;
                if (v.z > box.maxB.z) box.maxB.z = v.z;
            }
        } 
        else if (type == "f") {
            int a, b, c;
            if (ss >> a >> b >> c) {
                if (a > 0 && a <= vertices.size() && b > 0 && b <= vertices.size() && c > 0 && c <= vertices.size()) {
                    Face f = {vertices[a-1], vertices[b-1], vertices[c-1]};
                    face.push_back(f);
                }
            }
        }
        else continue;
    }

    float maxSide = max({box.maxB.x - box.minB.x, box.maxB.y - box.minB.y, box.maxB.z - box.minB.z});
    Vertex center = {(box.minB.x + box.maxB.x) / 2, (box.minB.y + box.maxB.y) / 2, (box.minB.z + box.maxB.z) / 2};
    float halfSide = maxSide/2;
    box.minB = {center.x - halfSide, center.y - halfSide, center.z - halfSide};
    box.maxB = {center.x + halfSide, center.y + halfSide, center.z + halfSide};

    res.faces = face;
    res.bound = box;
    return res;
}

void exportToObj(const string& filename, const vector<Voxel>& voxels) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return;
    }

    int startIdx = 1;
    for (const auto& vox : voxels) {
        Vertex v[8];
        generateCubeVertices(vox, v);
        for (int i = 0; i < 8; i++) {
            outFile << "v " << v[i].x << " " << v[i].y << " " << v[i].z << "\n";
        }

        int faces[12][3];
        generateCubeFaces(startIdx, faces);
        for (int i = 0; i < 12; i++) {
            outFile << "f " << faces[i][0] << " " << faces[i][1] << " " << faces[i][2] << "\n";
        }

        startIdx += 8;
    }

    outFile.close();
    cout << "File " << filename << " berhasil ditulis." << endl;
}

void generateCubeVertices(const Voxel& voxel, Vertex out[8]) {
    float h = voxel.size/2;

    out[0] = {voxel.center.x - h, voxel.center.y - h, voxel.center.z - h};
    out[1] = {voxel.center.x + h, voxel.center.y - h, voxel.center.z - h};
    out[2] = {voxel.center.x + h, voxel.center.y + h, voxel.center.z - h};
    out[3] = {voxel.center.x - h, voxel.center.y + h, voxel.center.z - h};
    out[4] = {voxel.center.x - h, voxel.center.y - h, voxel.center.z + h};
    out[5] = {voxel.center.x + h, voxel.center.y - h, voxel.center.z + h};
    out[6] = {voxel.center.x + h, voxel.center.y + h, voxel.center.z + h};
    out[7] = {voxel.center.x - h, voxel.center.y + h, voxel.center.z + h};
}

void generateCubeFaces(int startIdx, int faces[12][3]) {
    static const int pattern[12][3] = {
        {0, 2, 1}, {0, 3, 2},
        {4, 5, 6}, {4, 6, 7},
        {0, 1, 5}, {0, 5, 4},
        {3, 6, 2}, {3, 7, 6},
        {0, 7, 3}, {0, 4, 7},
        {1, 2, 6}, {1, 6, 5}
    };
    
    for (int i = 0; i < 12; i++) {
        faces[i][0] = startIdx + pattern[i][0];
        faces[i][1] = startIdx + pattern[i][1];
        faces[i][2] = startIdx + pattern[i][2];
    }
}