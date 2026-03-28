# Tucil2_13524128
Voxelization Objek 3D menggunakan Octree

## **Deskripsi Program**

Program ini mengimplementasikan proses **voxelization** untuk mengubah model 3D dalam format `.obj` menjadi representasi berbasis voxel (kubus-kubus kecil) menggunakan pendekatan **Divide and Conquer** dengan struktur data **Octree**.

Algoritma bekerja dengan cara:

* Membaca model `.obj` (vertex dan face)
* Membentuk bounding box objek
* Membagi ruang secara rekursif menjadi 8 bagian (octree)
* Menyimpan voxel pada leaf node dengan depth maksimum yang berinteraksi dengan permukaan objek
* Menghasilkan file `.obj` baru berupa kumpulan voxel

Output program:

* File `.obj` hasil voxelization
* Statistik jumlah voxel, vertex, face
* Statistik node octree
* Waktu eksekusi program

---

## **Requirement**

* Compiler C++ (disarankan **g++ / MinGW / GCC**)
* Sistem operasi: Windows / Linux / MacOS
* Tidak membutuhkan library eksternal tambahan

---

## **Cara Kompilasi**

```bash
g++ src/main.cpp src/implementation/io.cpp src/implementation/octree.cpp -o bin/main
```

---

## **Cara Menjalankan Program**

```bash
./bin/main
```

---

## **Cara Penggunaan**

1. Jalankan program
2. Masukkan:

   * Path file `.obj` (contoh: `test/teapot.obj`)
   * Kedalaman maksimum octree (misal: `3`, `4`, dst)
3. Program akan:

   * Memproses voxelization
   * Menampilkan statistik di CLI
   * Menghasilkan file `.obj` hasil voxelization

---

## **Author**

* Nama: **Safira Berlianti**
* NIM: **13524128**

---

