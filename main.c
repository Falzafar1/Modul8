/** EL2208 Praktikum Pemecahan Masalah dengan C 2023/2024
 *   Modul               : 8 – Advanced Algorithms
 *   Hari dan Tanggal    : Kamis, 2 Mei 2024
 *   Nama (NIM)          : Naufal Afiq Muzaffar (13222025)
 *   Nama File           : main.c
 *   Deskripsi           : Menentukan jalur mana yang harus dipilih supaya value input dapat bernilai maksimal
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char namaFile[100];
    int BesarMatriks =0;
    char *TextFile;
    int kekuatan = 2;
    int X = 0;
    int Y = 0;
    int Kanan = 0;
    int Bawah = 0;
    int gagal = 0;
    char jalur[10];

    printf("Masukkan peta: ");
    scanf("%s", namaFile);
    FILE *file = fopen(namaFile, "r");
    // Cek apakah file ada
    if (file == NULL) {
        printf("Level tidak ada!\n");
        return 0;
    }

    char line[100];
    fgets(line, 100, file);
    BesarMatriks = atoi(line);

    int **MatriksKekuatan;

    MatriksKekuatan = (int **)malloc(BesarMatriks * sizeof(int *)); 

    for (int i = 0; i < BesarMatriks; ++i)
        MatriksKekuatan[i] = (int *)malloc(BesarMatriks * sizeof(int)); 

    for ( int i = 0; i < BesarMatriks; i++){
        fgets(line, 100, file);
        TextFile= strtok(line," ");
        MatriksKekuatan[i][0] = atoi(TextFile);

        for (int j = 1; j < BesarMatriks; j++){
            TextFile= strtok(NULL," ");
            MatriksKekuatan[i][j] = atoi(TextFile);
        }
    }
    fclose(file);

    kekuatan = kekuatan + MatriksKekuatan[0][0];

    int perulangan = BesarMatriks + (BesarMatriks-1);

    for (int i = 0; i < perulangan; i++){
        if(X < BesarMatriks-1 && Y < BesarMatriks-1 && gagal!=1){
            Kanan = MatriksKekuatan[X][Y+1];
            Bawah = MatriksKekuatan[X+1][Y];

            if(kekuatan >= Kanan && Bawah <= Kanan){
                kekuatan = kekuatan + Kanan;
                Y = Y+1;
                strcpy(jalur,"Kanan");
            }
            else if (kekuatan >= Bawah && Kanan <= Bawah){
                kekuatan = kekuatan + Bawah;
                X = X+1;
                strcpy(jalur,"Bawah");
            }

            else if (kekuatan >= Kanan && Bawah > kekuatan){
                kekuatan = kekuatan + Kanan;
                Y = Y+1;
                strcpy(jalur,"Kanan");
            }
            else if (kekuatan < Kanan && kekuatan < Bawah){
                kekuatan = kekuatan-MatriksKekuatan[X][Y];

                if (strcmp(jalur,"Bawah")==0){
                    Kanan = MatriksKekuatan[X-1][Y+1];
                    kekuatan = kekuatan +Kanan;
                    X = X-1;
                    Y = Y+1;
                    strcpy(jalur,"Kanan");
                }
                else if (strcmp(jalur,"Bawah")==0){
                    Bawah = MatriksKekuatan[X+1][Y-1];
                    kekuatan = kekuatan +Bawah;
                    X = X+1;
                    Y = Y-1;
                    strcpy(jalur,"Bawah");
                }
            }
        }
        else if(X == BesarMatriks-1 && Y < BesarMatriks-1 && gagal !=1){

            Kanan = MatriksKekuatan[X][Y+1];

            if (kekuatan <Kanan){
                gagal =  1;
            }
            else{
                kekuatan = kekuatan + Kanan;
                Y = Y+1;
                strcpy(jalur,"Kanan");
            }

        }
        else if(X < BesarMatriks-1 && Y == BesarMatriks-1 && gagal != 1){
            Bawah = MatriksKekuatan[X+1][Y];

            if (kekuatan < Bawah){
                gagal = 1;
            }
            else{
                kekuatan = kekuatan + Bawah;
                X = X+1;
                strcpy(jalur,"Bawah");
            }
        }
    }
    
    // Menampilkan hasil
        if (gagal ==0){
        printf("Power terakhir pemain: %d poin.\n", kekuatan);
        printf("Pemain berhasil mengalahkan Boss!\n");
        }
        else{
            printf("Power terakhir pemain: %d poin.\n", kekuatan);
            printf("Pemain tidak mungkin mengalahkan Boss, Perkuat Dirimu!\n");
        }

    return 0;
}