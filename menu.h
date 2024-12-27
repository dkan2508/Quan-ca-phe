#ifndef MENU_H_
#define MENU_H_
#include "kho.h"

#define MENU_HEADER "tenMon,gia," \
                    "tenNguyenLieu1,tenNguyenLieu2,tenNguyenLieu3,tenNguyenLieu4,tenNguyenLieu5,tenNguyenLieu6,tenNguyenLieu7,tenNguyenLieu8,tenNguyenLieu9,tenNguyenLieu10," \
                    "tenNguyenLieu11,tenNguyenLieu12,tenNguyenLieu13,tenNguyenLieu14,tenNguyenLieu15,tenNguyenLieu16,tenNguyenLieu17,tenNguyenLieu18,tenNguyenLieu19,tenNguyenLieu20," \
                    "donViNguyenLieu1,donViNguyenLieu2.donViNguyenLieu3,donViNguyenLieu4,donViNguyenLieu5,donViNguyenLieu6,donViNguyenLieu7,donViNguyenLieu8,donViNguyenLieu9,donViNguyenLieu10," \
                    "donViNguyenLieu11,donViNguyenLieu12,donViNguyenLieu13,donViNguyenLieu14,donViNguyenLieu15,donViNguyenLieu16,donViNguyenLieu17,donViNguyenLieu18,donViNguyenLieu19,donViNguyenLieu20," \
                    "soLuongNguyenLieu1,soLuongNguyenLieu2,soLuongNguyenLieu3,soLuongNguyenLieu4,soLuongNguyenLieu5,soLuongNguyenLieu6,soLuongNguyenLieu7,soLuongNguyenLieu8,soLuongNguyenLieu9,soLuongNguyenLieu10," \
                    "soLuongNguyenLieu11,soLuongNguyenLieu12,soLuongNguyenLieu13,soLuongNguyenLieu14,soLuongNguyenLieu15,soLuongNguyenLieu16,soLuongNguyenLieu17,soLuongNguyenLieu18,soLuongNguyenLieu19,soLuongNguyenLieu20," \
                    "giaNguyenLieu1,giaNguyenLieu2,giaNguyenLieu3,giaNguyenLieu4,giaNguyenLieu5,giaNguyenLieu6,giaNguyenLieu7,giaNguyenLieu8,giaNguyenLieu9,giaNguyenLieu10," \
                    "giaNguyenLieu11,giaNguyenLieu12,giaNguyenLieu13,giaNguyenLieu14,giaNguyenLieu15,giaNguyenLieu16,giaNguyenLieu17,giaNguyenLieu18,giaNguyenLieu19,giaNguyenLieu20," \
                    "soNguyenLieu\n" 

#define DO_DAI_TEN_MON 50
#define MAX_NGUYEN_LIEU 20
#define MAX_ARRAY_LENGTH_MENU 3000

// Cấu trúc món ăn
typedef struct {
    char tenMon[DO_DAI_TEN_MON];
    float gia;
    NguyenLieu nguyenLieu[MAX_NGUYEN_LIEU];
    int soNguyenLieu;
} MonAn;

int kiemTraSoMonAn(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong mon an trong menu");
        return -1;
    }

    int soMonAn = 0;
    fseek(fptr, sizeof(MENU_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_MENU];
    while(fgets(msg, MAX_ARRAY_LENGTH_MENU, fptr)) {
        soMonAn++;
    }

    fclose(fptr);

    return soMonAn;
}

void saoChepMonAn(MonAn* monAnNhan, MonAn* monAnNguon) {
    // monAnNhan, monAnNguon la dia chi cua nguyen lieu nhan va cho su sao chep.
    // Thuc hien deep copying thay vi shallow copying su dung memcpy hay "="
    strncpy(monAnNhan->tenMon, monAnNguon->tenMon, DO_DAI_TEN_MON - 1);  // khachNhan->tenKhachHang tuong duong (*khachNhan).tenKhachHang
    monAnNhan->tenMon[DO_DAI_TEN_MON - 1] = '\0';
    monAnNhan->gia = monAnNguon->gia;
    monAnNhan->soNguyenLieu = monAnNguon->soNguyenLieu;
    for(int i = 0; i < monAnNguon->soNguyenLieu; i++) {
        saoChepNguyenLieu(&(monAnNhan->nguyenLieu[i]), &(monAnNguon->nguyenLieu[i]));
    }
}

void chuanHoaMonAn(MonAn* monAn, int soMonAn) {
    for (int i = 0; i < soMonAn; i++) {
        // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
        memset(monAn[i].tenMon, '0', 2);
        monAn[i].tenMon[1] = '\0';

        monAn[i].gia = 0;
        monAn[i].soNguyenLieu = 0;

        chuanHoaKho(monAn[i].nguyenLieu, MAX_NGUYEN_LIEU);
    }
}

void themMonAnVaoFile(MonAn monAn, char duongDan[]) {
    // Khac voi ham doc tu file, ham nay nhan du lieu co san nen khong can chuan hoa
    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }
    fprintf(fptr, "%s,%.2f,", monAn.tenMon, monAn.gia);
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%s,", monAn.nguyenLieu[j].tenNguyenLieu);
    }
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%s,", monAn.nguyenLieu[j].donVi);
    }
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%.2f,", monAn.nguyenLieu[j].soLuong);
    }
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%.2f,", monAn.nguyenLieu[j].gia);
    }
    fprintf(fptr, "%d\n", monAn.soNguyenLieu);
    fclose(fptr);
}

int coNhuNhauMonAn(MonAn h1, MonAn h2) {
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(strcmp(h1.tenMon, h2.tenMon) == 0 && h1.gia == h2.gia && h1.soNguyenLieu == h2.soNguyenLieu) {
        for(int i = 0; i < MAX_NGUYEN_LIEU; i++) {
            if(coNhuNhauNguyenLieu(h1.nguyenLieu[i], h2.nguyenLieu[i]) == 0) {
                return 0;
            }
        }
        return 1;
    } 
    return 0;
}

void themNhieuMonAnVaoFile(MonAn danhSachMonAn[], int soMonAn, char duongDan[]) {
    // Su dung ham nay thay cho themMonAnVaoFile khi cap nhat mang du lieu de tranh dong mo file nhieu lan

    FILE* fptr = fopen(duongDan, "a");
    if(!fptr) {
        perror("Khong the them mon an vao file");
        return;
    }

    for(int i = 0; i < soMonAn; i++) {
        fprintf(fptr, "%s,%.2f,", danhSachMonAn[i].tenMon, danhSachMonAn[i].gia);
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", danhSachMonAn[i].nguyenLieu[j].tenNguyenLieu);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", danhSachMonAn[i].nguyenLieu[j].donVi);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", danhSachMonAn[i].nguyenLieu[j].soLuong);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", danhSachMonAn[i].nguyenLieu[j].gia);
        }
        fprintf(fptr, "%d\n", danhSachMonAn[i].soNguyenLieu);
    }

    fclose(fptr);
}

void docFileMenu(char duongDan[], int soMonAnDoc, MonAn danhSachMonAn[]) {
    if(soMonAnDoc == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong mon an trong menu");
        return;
    }

    chuanHoaMonAn(danhSachMonAn, soMonAnDoc);
    char msg[MAX_ARRAY_LENGTH_MENU];
    fseek(fptr, sizeof(MENU_HEADER), SEEK_SET); // Bo qua header

    for (int i = 0; i < soMonAnDoc; i++) {
        // Chu y thu tu cac phan tu duoc gan phai khop voi thu tu cac truong tuong ung trong header
        if (fgets(msg, MAX_ARRAY_LENGTH_MENU - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file menu");
            break;
        }

        msg[MAX_ARRAY_LENGTH_MENU - 1] = '\0'; // Dam bao msg duoc null terminate
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh;

        char* tenMonAn = strtok(msg, NGAN_PHAN_TU_CSV);
        if(tenMonAn) {
            strncpy(danhSachMonAn[i].tenMon, tenMonAn, DO_DAI_TEN_MON - 1);
            danhSachMonAn[i].tenMon[DO_DAI_TEN_MON - 1] = '\0';
        }

        char* giaMon = strtok(NULL, NGAN_PHAN_TU_CSV);
        if(giaMon) {
            danhSachMonAn[i].gia = atof(giaMon);
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char *tenNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (tenNguyenLieu) {
                strncpy(danhSachMonAn[i].nguyenLieu[j].tenNguyenLieu, tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);
                danhSachMonAn[i].nguyenLieu[j].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
            }
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char *donVi = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (donVi) {
                strncpy(danhSachMonAn[i].nguyenLieu[j].donVi, donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
                danhSachMonAn[i].nguyenLieu[j].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';
            }
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char* soLuong = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (soLuong) {
                danhSachMonAn[i].nguyenLieu[j].soLuong = atof(soLuong);
            }
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char* giaNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
            if(giaNguyenLieu) {
                danhSachMonAn[i].nguyenLieu[j].gia = atof(giaNguyenLieu);
            }
        }

        char* soNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
        if(soNguyenLieu) {
            danhSachMonAn[i].soNguyenLieu = atoi(soNguyenLieu);
        }
    }

    fclose(fptr);
}

void xoaMonAnKhoiFile(char tenMonXoa[], char duongDan[]) {
    int soMonFile = kiemTraSoMonAn(duongDan);
    if(soMonFile == 0) {
        printf("File menu trong\n");
        return;
    }

    MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
    docFileMenu(duongDan, soMonFile, menuFile);

    for(int i = 0; i < soMonFile; i++) {
        if(strcmp(menuFile[i].tenMon, tenMonXoa) == 0) {
            for(int j = i; j < soMonFile - 1; j++) {
                menuFile[j] = menuFile[j + 1];
            }
            soMonFile--;
            break;
        }
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file kho de xoa mon an");
        return;
    }

    fprintf(fptr, MENU_HEADER);    
    for(int i = 0; i < soMonFile; i++) {
        fprintf(fptr, "%s,%.2f,", menuFile[i].tenMon, menuFile[i].gia);
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", menuFile[i].nguyenLieu[j].tenNguyenLieu);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", menuFile[i].nguyenLieu[j].donVi);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", menuFile[i].nguyenLieu[j].soLuong);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", menuFile[i].nguyenLieu[j].gia);
        }
        fprintf(fptr, "%d\n", menuFile[i].soNguyenLieu);
    }

    printf("Xoa mon an khoi file thanh cong\n");
    fclose(fptr);
    free(menuFile);
}

#endif