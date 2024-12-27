#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include "general.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARRAY_LENGTH_KHACH_HANG 75
#define KHACH_HANG_HEADER "tenKhachHang,soDienThoai,diemTichLuy\n"
#define AMOUNT_CUSTOMER_ATTR 2
#define DO_DAI_TEN_KHACH 50
#define DO_DAI_SO_DIEN_THOAI 15

// Cấu trúc khách hàng
typedef struct {
    char tenKhachHang[DO_DAI_TEN_KHACH];
    char soDienThoai[DO_DAI_SO_DIEN_THOAI];
    int diemTichLuy;
} KhachHang;

void chuanHoaKhachHang(KhachHang* khachHang, int soKhachHang) {
    for (int i = 0; i < soKhachHang; i++) {
        // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
        memset(khachHang[i].tenKhachHang, '0', 2);
        khachHang[i].tenKhachHang[1] = '\0';

        memset(khachHang[i].soDienThoai, '0', 2);
        khachHang[i].soDienThoai[1] = '\0';

        khachHang[i].diemTichLuy = 0;
    }
}

void saoChepKhachHang(KhachHang* khachNhan, KhachHang* khachNguon) {
    // khachNhan, khachNguon la dia chi cua khach nhan va cho su sao chep.
    // Thuc hien deep copying thay vi shallow copying su dung memcpy hay "="
    strncpy(khachNhan->tenKhachHang, khachNguon->tenKhachHang, DO_DAI_TEN_KHACH - 1);  // khachNhan->tenKhachHang tuong duong (*khachNhan).tenKhachHang
    khachNhan->tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
    strncpy(khachNhan->soDienThoai, khachNguon->soDienThoai, DO_DAI_SO_DIEN_THOAI - 1);
    khachNhan->soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
    khachNhan->diemTichLuy = khachNguon->diemTichLuy;
}

void themKhachHangVaoFile(KhachHang khach, char duongDan[]) {
    // Them mot khach hang vao file
    // Khac voi ham doc tu file, ham nay nhan du lieu co san nen khong can chuan hoa
    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them khach hang vao file");
        return;
    }
    fprintf(fptr, "%s,%s,%d\n", khach.tenKhachHang, khach.soDienThoai, khach.diemTichLuy);
    fclose(fptr);
}

int kiemTraSoKhachHang(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong khach hang");
        return -1;
    }

    int soKhachHang = 0;
    fseek(fptr, sizeof(KHACH_HANG_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_KHACH_HANG];
    while(fgets(msg, MAX_ARRAY_LENGTH_KHACH_HANG, fptr)) {
        soKhachHang++;
    }

    fclose(fptr);

    return soKhachHang;
}

int coNhuNhauKhachHang(KhachHang k1, KhachHang k2) {
    // Kiem tra xem hai khach hang co cung thuoc tinh khong.
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(strcmp(k1.tenKhachHang, k2.tenKhachHang) == 0 && strcmp(k1.soDienThoai, k2.soDienThoai) == 0 && k1.diemTichLuy == k2.diemTichLuy) {
        return 1;
    } 
    return 0;
}

void docFileKhachHang(char duongDan[], int soKhachHangDoc, KhachHang danhSachKhachHang[]) {
    if(soKhachHangDoc == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong khach hang");
        return;
    }

    chuanHoaKhachHang(danhSachKhachHang, soKhachHangDoc);
    char msg[MAX_ARRAY_LENGTH_KHACH_HANG];
    fseek(fptr, sizeof(KHACH_HANG_HEADER), SEEK_SET); // Bo qua header

    for (int i = 0; i < soKhachHangDoc; i++) {
        if (fgets(msg, MAX_ARRAY_LENGTH_KHACH_HANG - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file khach hang");
            break;
        }

        msg[MAX_ARRAY_LENGTH_KHACH_HANG - 1] = '\0'; // Dam bao msg duoc null terminate
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh;

        char *tenKhachHang = strtok(msg, NGAN_PHAN_TU_CSV);
        if (tenKhachHang) {
            strncpy(danhSachKhachHang[i].tenKhachHang, tenKhachHang, DO_DAI_TEN_KHACH - 1);
            danhSachKhachHang[i].tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
        }

        char *soDienThoai = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soDienThoai) {
            strncpy(danhSachKhachHang[i].soDienThoai, soDienThoai, DO_DAI_SO_DIEN_THOAI - 1);
            danhSachKhachHang[i].soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
        }

        char* diemTichLuy = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (diemTichLuy) {
            danhSachKhachHang[i].diemTichLuy = atoi(diemTichLuy);
        }
    }

    fclose(fptr);
}

void xoaKhachKhoiFile(KhachHang khachXoa, char duongDan[]) {
    int soKhachHangFile = kiemTraSoKhachHang(duongDan);
    if(soKhachHangFile == 0) {
        printf("File khong co khach hang\n");
        return;
    }

    // Xoa mot khach hang co spec tuong tu khachXoa khoi file
    KhachHang* danhSachKhachHangFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachHangFile);
    docFileKhachHang(duongDan, soKhachHangFile, danhSachKhachHangFile);

    int coMat = 0;
    for(int i = 0; i < soKhachHangFile; i++) {
        if(coNhuNhauKhachHang(danhSachKhachHangFile[i], khachXoa) == 1) {
            for(int j = i; j < soKhachHangFile - 1; j++) {
                danhSachKhachHangFile[j] = danhSachKhachHangFile[j + 1];
            }
            soKhachHangFile--;
            coMat = 1;
            break;
        }
    }
    if(coMat == 0) {
        printf("Khach hang khong co trong file\n");
        free(danhSachKhachHangFile);
        return;
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file khach hang de xoa khach hang");
        return;
    }
        
    fprintf(fptr, KHACH_HANG_HEADER);
    for(int i = 0; i < soKhachHangFile; i++) {
        fprintf(fptr, "%s,%s,%d\n", danhSachKhachHangFile[i].tenKhachHang, danhSachKhachHangFile[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
    }

    printf("Xoa khach hang khoi file thanh cong\n");
    fclose(fptr);
    free(danhSachKhachHangFile);
}


#endif