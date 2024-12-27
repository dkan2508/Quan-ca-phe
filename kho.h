#ifndef KHO_H_
#define KHO_H_
#include "bill.h"

#define KHO_HEADER "tenNguyenLieu,donVi,soLuong,gia\n"
#define MAX_DO_DAI_TEN_NGUYEN_LIEU 50
#define MAX_DO_DAI_CHUOI_DON_VI 15
#define MAX_ARRAY_LENGTH_KHO 70

typedef struct {
    char tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU];
    char donVi[MAX_DO_DAI_CHUOI_DON_VI];  //kg, hộp, trái, gói
    float soLuong; 
    float gia; // Tinh tren mot don vi 
} NguyenLieu;

void chuanHoaKho(NguyenLieu* kho, int soNguyenLieu) {
    for (int i = 0; i < soNguyenLieu; i++) {
        // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
        memset(kho[i].tenNguyenLieu, '0', 2);
        kho[i].tenNguyenLieu[1] = '\0';

        memset(kho[i].donVi, '0', 2);
        kho[i].donVi[1] = '\0';

        kho[i].soLuong = 0;
        kho[i].gia = 0;
    }
}

void saoChepNguyenLieu(NguyenLieu* nguyenLieuNhan, NguyenLieu* nguyenLieuNguon) {
    // nguyenLieuNhan, nguyenLieuNguon la dia chi cua nguyen lieu nhan va cho su sao chep.
    // Thuc hien deep copying thay vi shallow copying su dung memcpy hay "="
    strncpy(nguyenLieuNhan->tenNguyenLieu, nguyenLieuNguon->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);  // khachNhan->tenKhachHang tuong duong (*khachNhan).tenKhachHang
    nguyenLieuNhan->tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
    strncpy(nguyenLieuNhan->donVi, nguyenLieuNguon->donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
    nguyenLieuNhan->donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';
    nguyenLieuNhan->soLuong = nguyenLieuNguon->soLuong;
    nguyenLieuNhan->gia = nguyenLieuNguon->gia;
}

void themNguyenLieuVaoFile(NguyenLieu nguyenLieu, char duongDan[]) {
    // Khac voi ham doc tu file, ham nay nhan du lieu co san nen khong can chuan hoa
    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }
    fprintf(fptr, "%s,%s,%.2f,%.2f\n", nguyenLieu.tenNguyenLieu, nguyenLieu.donVi, nguyenLieu.soLuong, nguyenLieu.gia);
    fclose(fptr);
}

void themNhieuNguyenLieuVaoFile(NguyenLieu danhSachNguyenLieu[], int soNguyenLieu, char duongDan[]) {
    // Su dung ham nay thay cho themNguyenLieuVaoFile khi cap nhat mang du lieu de tranh dong mo file nhieu lan

    FILE* fptr = fopen(duongDan, "a");
    if(!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }

    for(int i = 0; i < soNguyenLieu; i++) {
        fprintf(fptr, "%s,%s,%.2f,%.2f\n", danhSachNguyenLieu[i].tenNguyenLieu, danhSachNguyenLieu[i].donVi, danhSachNguyenLieu[i].soLuong, danhSachNguyenLieu[i].gia);
    }

    fclose(fptr);
}

int kiemTraSoNguyenLieu(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong nguyen lieu");
        return -1;
    }

    int soNguyenLieu = 0;
    fseek(fptr, sizeof(KHO_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_KHO];
    while(fgets(msg, MAX_ARRAY_LENGTH_KHO, fptr)) {
        soNguyenLieu++;
    }

    fclose(fptr);

    return soNguyenLieu;
}

int coNhuNhauNguyenLieu(NguyenLieu h1, NguyenLieu h2) {
    // Kiem tra xem hai nguyen lieu co cung thuoc tinh khong.
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(strcmp(h1.tenNguyenLieu, h2.tenNguyenLieu) == 0 && strcmp(h1.donVi, h2.donVi) == 0 && h1.soLuong == h2.soLuong && h1.gia == h2.gia) {
        return 1;
    } 
    return 0;
}

void docFileKho(char duongDan[], int soNguyenLieu, NguyenLieu kho[]) {
    if(soNguyenLieu == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong nguyen lieu");
        return;
    }

    chuanHoaKho(kho, soNguyenLieu);
    char msg[MAX_ARRAY_LENGTH_KHO];
    fseek(fptr, sizeof(KHO_HEADER), SEEK_SET); // Bo qua header

    for (int i = 0; i < soNguyenLieu; i++) {
        if (fgets(msg, MAX_ARRAY_LENGTH_KHO - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file nguyen lieu");
            break;
        }

        msg[MAX_ARRAY_LENGTH_KHO - 1] = '\0';
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh;

        char *tenNguyenLieu = strtok(msg, NGAN_PHAN_TU_CSV);
        if (tenNguyenLieu) {
            strncpy(kho[i].tenNguyenLieu, tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);
            kho[i].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
        }

        char *donVi = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (donVi) {
            strncpy(kho[i].donVi, donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
            kho[i].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';
        }

        char* soLuong = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soLuong) {
            kho[i].soLuong = atof(soLuong);
        }

        char* gia = strtok(NULL, NGAN_PHAN_TU_CSV);
        if(gia) {
            kho[i].gia = atof(gia);
        }
    }

    fclose(fptr);
}

void xoaNguyenLieuKhoiFile(char tenNguyenLieuXoa[], char duongDan[]) {
    int soNguyenLieuFile = kiemTraSoNguyenLieu(duongDan);
    if(soNguyenLieuFile == 0) {
        printf("Kho trong\n");
        return;
    }

    NguyenLieu* khoFile = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soNguyenLieuFile);
    docFileKho(duongDan, soNguyenLieuFile, khoFile);

    for(int i = 0; i < soNguyenLieuFile; i++) {
        if(strcmp(khoFile[i].tenNguyenLieu, tenNguyenLieuXoa) == 0) {
            for(int j = i; j < soNguyenLieuFile - 1; j++) {
                khoFile[j] = khoFile[j + 1];
            }
            soNguyenLieuFile--;
            break;
        }
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file kho de xoa nguyen lieu");
        return;
    }
        
    fprintf(fptr, KHO_HEADER);
    for(int i = 0; i < soNguyenLieuFile; i++) {
        fprintf(fptr, "%s,%s,%.2f,%.2f\n", khoFile[i].tenNguyenLieu, khoFile[i].donVi, khoFile[i].soLuong, khoFile[i].gia);
    }

    printf("Xoa nguyen lieu khoi file kho thanh cong\n");
    fclose(fptr);
    free(khoFile);
}


#endif