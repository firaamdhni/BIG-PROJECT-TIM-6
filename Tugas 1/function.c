#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Inisialisasi variabel 
Alat_Lab alat_lab[MAX_ALAT];
unsigned int total_alat = 0;
unsigned int total_peminjaman = 0;
Alat_Peminjaman peminjaman[MAX_PEMINJAMAN];

// Fungsi untuk membaca data dari file
void data() {
    FILE *file = fopen("alat_lab.txt", "r");
    if (file == NULL) {
        printf("file tidak ditemukan.\n");
        return;
    }

    while (fscanf(file, "%u %s %s %s %u %u %u", &alat_lab[total_alat].Id_Alat,
                    alat_lab[total_alat].Nama_Alat,
                    alat_lab[total_alat].Merek,
                    alat_lab[total_alat].Model,
                    &alat_lab[total_alat].Tahun_Produksi,
                    &alat_lab[total_alat].Jumlah_Unit,
                    &alat_lab[total_alat].Jumlah_Tersedia) != EOF) {
        total_alat++;
    }
    fclose(file);
}

// Fungsi untuk menyimpan data ke file
void simpan_data() {
    FILE *file = fopen("alat_lab.txt", "w");
    for (unsigned int i = 0; i < total_alat; i++) {
        fprintf(file, "%u %s %s %s %u %u %u\n",
                alat_lab[i].Id_Alat,
                alat_lab[i].Nama_Alat,
                alat_lab[i].Merek,
                alat_lab[i].Model,
                alat_lab[i].Tahun_Produksi,
                alat_lab[i].Jumlah_Unit,
                alat_lab[i].Jumlah_Tersedia);
    }
    fclose(file);
}

// Menu Admin
void admin_menu() {
    int pilih;
    do {
        printf("\n---- Menu Admin ----\n");
        printf("1. Tambah Alat Lab\n");
        printf("2. Lihat Daftar Alat Lab\n");
        printf("3. Edit Alat Lab\n");
        printf("4. Hapus Alat Lab\n");
        printf("5. Keluar\n");
        printf("Pilih Opsi: ");
        scanf("%d", &pilih);

