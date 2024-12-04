#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALAT 100
#define MAX_PEMINJAMAN 100

typedef struct {
    unsigned int Id_Alat;
    char Nama_Alat[50];
    char Merek[50];
    char Model[50];
    unsigned int Tahun_Produksi;
    unsigned int Jumlah_Unit;
    unsigned int Jumlah_Tersedia;
} Alat_Lab;

typedef struct {
    unsigned int Id_Alat;
    char Nama_Alat[50];
    unsigned int Jumlah_Pinjam;
} Alat_Peminjaman;
