#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Barang {
    int id;
    string nama;
    int stok;
    double harga;
};

vector<Barang> daftarBarang;

void simpanKeFile() {
    ofstream file("inventaris.txt");
    for (const auto& b : daftarBarang) {
        file << b.id << "," << b.nama << "," << b.stok << "," << b.harga << "\n";
    }
    file.close();
}

void muatDariFile() {
    ifstream file("inventaris.txt");
    if (!file.is_open()) return;

    daftarBarang.clear();
    Barang b;
    char delimiter;
    while (file >> b.id >> delimiter && getline(file, b.nama, ',') && file >> b.stok >> delimiter >> b.harga) {
        daftarBarang.push_back(b);
    }
    file.close();
}

void tampilkanBarang() {
    cout << "\n======================================================\n";
    cout << left << setw(5) << "ID" << setw(20) << "Nama Barang" << setw(10) << "Stok" << setw(15) << "Harga (Rp)" << "\n";
    cout << "======================================================\n";

    if (daftarBarang.empty()) {
        cout << "            (Belum ada data barang)                   \n";
    } else {
        for (const auto& b : daftarBarang) {
            cout << left << setw(5) << b.id << setw(20) << b.nama << setw(10) << b.stok << setw(15) << fixed << setprecision(0) << b.harga << "\n";
        }
    }
    cout << "======================================================\n";
}

void tambahBarang() {
    Barang b;
    b.id = daftarBarang.empty() ? 1 : daftarBarang.back().id + 1;

    cout << "\n--- Tambah Barang Baru ---\n";
    cout << "Nama Barang : ";
    cin.ignore();
    getline(cin, b.nama);
    cout << "Jumlah Stok : ";
    cin >> b.stok;
    cout << "Harga (Rp)  : ";
    cin >> b.harga;

    daftarBarang.push_back(b);
    simpanKeFile();
    cout << ">> Barang berhasil ditambahkan!\n";
}

void cariBarang() {
    if (daftarBarang.empty()) {
        cout << "\nData barang masih kosong!\n";
        return;
    }

    string kataKunci;
    cout << "\n--- Cari Barang ---\n";
    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, kataKunci);

    bool ditemukan = false;
    cout << "\n======================================================\n";
    cout << left << setw(5) << "ID" << setw(20) << "Nama Barang" << setw(10) << "Stok" << setw(15) << "Harga (Rp)" << "\n";
    cout << "======================================================\n";

    for (const auto& b : daftarBarang) {
        if (b.nama.find(kataKunci) != string::npos) {
            cout << left << setw(5) << b.id << setw(20) << b.nama << setw(10) << b.stok << setw(15) << fixed << setprecision(0) << b.harga << "\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "            (Barang tidak ditemukan)                 \n";
    }
    cout << "======================================================\n";
}

void hapusBarang() {
    if (daftarBarang.empty()) {
        cout << "\nData barang masih kosong!\n";
        return;
    }

    int idHapus;
    cout << "\n--- Hapus Barang ---\n";
    cout << "Masukkan ID Barang yang ingin dihapus: ";
    cin >> idHapus;

    bool ditemukan = false;
    for (auto it = daftarBarang.begin(); it != daftarBarang.end(); ++it) {
        if (it->id == idHapus) {
            daftarBarang.erase(it);
            simpanKeFile();
            cout << ">> Barang berhasil dihapus!\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << ">> ID Barang tidak ditemukan!\n";
    }
}

int main() {
    muatDariFile();
    int pilihan;

    do {
        cout << "\n=== APLIKASI INVENTARIS BARANG ===\n";
        cout << "1. Lihat Daftar Barang\n";
        cout << "2. Tambah Barang\n";
        cout << "3. Cari Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tampilkanBarang(); break;
            case 2: tambahBarang(); break;
            case 3: cariBarang(); break;
            case 4: hapusBarang(); break;
            case 5: cout << "Terima kasih! Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    return 0;
}
