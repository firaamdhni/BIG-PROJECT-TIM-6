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
 printf("----------------------------------------------------------------------------------------------------------------------------\n");

        } else if (pilih == 3) {
            unsigned int Id_Alat;
            printf("Masukkan ID Alat yang Akan Diedit: ");
            scanf("%u", &Id_Alat);
            int exists = 0;
            for (unsigned int i = 0; i < total_alat; i++) {
                if (alat_lab[i].Id_Alat == Id_Alat) {
                    exists = 1;
                   
                  
                    printf("Masukkan Jumlah Unit: ");
                    scanf("%u", &alat_lab[i].Jumlah_Unit);
                    alat_lab[i].Jumlah_Tersedia = alat_lab[i].Jumlah_Unit;
                    simpan_data();
                    printf("Alat Lab Dengan ID %u Berhasil Diedit.\n", Id_Alat);
                    break;
                }
            }
            if (!exists) {
                printf("Alat Lab Dengan ID %u Tidak Ditemukan.\n", Id_Alat);
            }
        } else if (pilih == 4) {
            unsigned int Id_Alat;
            printf("Masukkan ID Alat yang Akan Dihapus: ");
            scanf("%u", &Id_Alat);
            int exists = 0;
            for (unsigned int i = 0; i < total_alat; i++) {
                if (alat_lab[i].Id_Alat == Id_Alat) {
                    exists = 1;
                    for (unsigned int j = i; j < total_alat - 1; j++) {
                        alat_lab[j] = alat_lab[j + 1];
                    }
                    total_alat--;
                    simpan_data();
                    printf("Alat Lab dengan ID %u Berhasil Dihapus.\n", Id_Alat);
                    break;
                }
            }
            if (!exists) {
                printf("Alat Lab dengan id %u Tidak Ditemukan.\n", Id_Alat);
            }
        }
    } while (pilih != 5);
}

// Fungsi untuk pinjam alat
void pinjam_alat() {
    unsigned int id_alat, jumlah;
    printf("Masukkan ID Alat yang ingin dipinjam: ");
    scanf("%u", &id_alat);

    printf("Masukkan jumlah alat yang ingin dipinjam: ");
    scanf("%u", &jumlah);
    

    // Cek apakah alat ada dan tersedia
    int found = 0;
    for (unsigned int i = 0; i < total_alat; i++) {
        if (alat_lab[i].Id_Alat == id_alat) {
            found = 1;
            if (alat_lab[i].Jumlah_Tersedia >= jumlah) {
                // Jika alat tersedia
                peminjaman[total_peminjaman].Id_Alat = id_alat;
                strcpy(peminjaman[total_peminjaman].Nama_Alat, alat_lab[i].Nama_Alat);
                peminjaman[total_peminjaman].Jumlah_Pinjam = jumlah;

                alat_lab[i].Jumlah_Tersedia -= jumlah;
                total_peminjaman++;
                simpan_data();
                printf("Alat berhasil dipinjam.\n");
            } else {
                printf("Jumlah alat yang tersedia tidak cukup.\n");
            }
            break;
        }
    }
    if (!found) {
        printf("Alat dengan ID %u tidak ditemukan.\n", id_alat);
    }
}
