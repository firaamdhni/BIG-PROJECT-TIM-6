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

        if (pilih == 1) {
            if (total_alat >= MAX_ALAT) {
                printf("Jumlah Alat Lab Mencapai Batas Maksimum.\n");
                continue;
            }
            Alat_Lab alat;
            printf("Masukkan ID Alat: ");
            scanf("%u", &alat.Id_Alat);
            printf("Masukkan Nama Alat: ");
            scanf("%s", alat.Nama_Alat);
            printf("Masukkan Merek: ");
            scanf("%s", alat.Merek);
            printf("Masukkan Model: ");
            scanf("%s", alat.Model);
            printf("Masukkan Tahun Produksi: ");
            scanf("%u", &alat.Tahun_Produksi);
            printf("Masukkan Jumlah Unit: ");
            scanf("%u", &alat.Jumlah_Unit);
            alat.Jumlah_Tersedia = alat.Jumlah_Unit;
            alat_lab[total_alat++] = alat;
            simpan_data();
            printf("Alat Lab Berhasil Ditambahkan.\n");
        } else if (pilih == 2) {
            printf("\n---- Daftar Alat Lab ----\n");
            printf("----------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-15s | %-15s | %-15s | %-12s | %-15s |\n",
            "ID Alat", "Nama Alat", "Merek", "Model", "Tahun Produksi", "Jumlah Unit", "Jumlah Tersedia");  
            printf("----------------------------------------------------------------------------------------------------------------------------\n");
            for (unsigned int i = 0; i < total_alat; i++) {
                printf("| %-10u | %-20s | %-15s | %-15s | %-15u | %-12u | %-15u |\n",
                alat_lab[i].Id_Alat,
                alat_lab[i].Nama_Alat,
                alat_lab[i].Merek,
                alat_lab[i].Model,
                alat_lab[i].Tahun_Produksi,
                alat_lab[i].Jumlah_Unit,
                alat_lab[i].Jumlah_Tersedia);
        }
