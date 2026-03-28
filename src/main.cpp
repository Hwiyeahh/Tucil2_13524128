#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "header/struct.hpp"
#include "header/io.hpp"
#include "header/octree.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    string pathIn, pathOut;
    int maxDepth;
    cout << "Path file .obj: ";
    getline(cin, pathIn);
    cout << "Nama file output (.obj): ";
    getline(cin, pathOut);
    cout << "Input max depth: ";
    cin >> maxDepth;

    auto start = high_resolution_clock::now();

    ParsedData data = parseOBJ(pathIn);
    if (data.faces.empty()) {
        cout << "Gagal membaca file atau model tidak valid." << endl;
    }

    vector<int> nodesCreated(maxDepth + 1, 0);
    vector<int> nodesSkipped(maxDepth + 1, 0);
    vector<Voxel> voxels;

    OctreeNode* root = new OctreeNode();
    root->box = data.bound;
    root->depth = 0;

    buildOctree(root, data.faces, 0, maxDepth, nodesCreated, nodesSkipped, voxels);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (!voxels.empty()) {
        exportToObj(pathOut, voxels); 
        cout << "File " << pathOut << " berhasil dibuat dengan " << voxels.size() << " titik." << endl;
    } else {
        cout << "Voxel kosong, tidak ada yang diekspor." << endl;
    }

    cout << "\n================ STATISTIK ================" << endl;
    cout << "Banyaknya voxel yang terbentuk: " << voxels.size() << endl;
    cout << "Banyaknya vertex yang terbentuk: " << voxels.size() * 8 << endl;
    cout << "Banyaknya faces yang terbentuk: " << voxels.size() * 12 << endl;
    
    cout << "\nStatistik node octree yang terbentuk:" << endl;
    for (int i = 1; i <= maxDepth; i++) {
        cout << i << " : " << nodesCreated[i] << endl;
    }

    cout << "\nStatistik node yang tidak perlu ditelusuri:" << endl;
    for (int i = 1; i <= maxDepth; i++) {
        cout << i << " : " << nodesSkipped[i] << endl;
    }

    cout << "\nKedalaman octree: " << maxDepth << endl;
    cout << "Lama waktu program berjalan: " << duration.count() << " ms" << endl;
    cout << "Path file .obj: " << pathOut << endl;
    cout << "===========================================" << endl;

    return 0;
}