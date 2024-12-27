#ifndef BILL_H_
#define BILL_H_
#include "customer.h"

#define MAX_MON 30
#define HOA_DON_HEADER "tenKhachHang,soDienThoai,diemTichLuyKhach," \
                       "ngayNhap,thangNhap,namNhap," \
                       "soMon1,soMon2,soMon3,soMon4,soMon5,soMon6,soMon7,soMon8,soMon9,soMon10," \
                       "soMon11,soMon12,soMon13,soMon14,soMon15,soMon16,soMon17,soMon18,soMon19,soMon20," \
                       "soMon21,soMon22,soMon23,soMon24,soMon25,soMon26,soMon27,soMon28,soMon29,soMon30," \
                       "tenMon1,tenMon2,tenMon3,tenMon4,tenMon5,tenMon6,tenMon7,tenMon8,tenMon9,tenMon10," \
                       "tenMon11,tenMon12,tenMon13,tenMon14,tenMon15,tenMon16,tenMon17,tenMon18,tenMon19,tenMon20," \
                       "tenMon21,tenMon22,tenMon23,tenMon24,tenMon25,tenMon26,tenMon27,tenMon28,tenMon29,tenMon30," \
                       "giaMon1,giaMon2,giaMon3,giaMon4,giaMon5,giaMon6,giaMon7,giaMon8,giaMon9,giaMon10," \
                       "giaMon11,giaMon12,giaMon13,giaMon14,giaMon15,giaMon16,giaMon17,giaMon18,giaMon19,giaMon20," \
                       "giaMon21,giaMon22,giaMon23,giaMon24,giaMon25,giaMon26,giaMon27,giaMon28,giaMon29,giaMon30," \
                       "soMonGoi,tongTien,tienThua,tienNguyenLieu\n"
#define MAX_ARRAY_LENGTH_HOA_DON 3000
#define AMOUNT_BILL_ATTR 100
#define MAX_DO_DAI_TEN_MON 50

typedef struct {
    KhachHang khachHang;
    Ngay ngayNhapDon;
    int soLuongMon[MAX_MON];
    char tenMonGoi[MAX_MON][MAX_DO_DAI_TEN_MON]; 
    float giaMonGoi[MAX_MON];
    int soMonGoi;
    float tongTien;
    float tienThua;
    float tienNguyenLieu;
} HoaDon;

void chuanHoaHoaDon(HoaDon* hoaDon, int soHoaDon) {
    // Cai dat gia tri mac dinh cho mang tenMonGoi va soLuongMon cho mot vat hoac mot mang hoa don
    // Su dung sau khi tao va dien gia tri thu cong cho mot struct HoaDon (vd, khi thanh toan) de tranh gia tri rac cho cac gia tri cua mang
    for (int i = 0; i < soHoaDon; i++) {
        for(int j = 0; j < MAX_MON; j++) {
            memset(hoaDon[i].tenMonGoi[j], '0', 2); // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
            hoaDon[i].tenMonGoi[j][1] = '\0';
        }

        memset(hoaDon[i].soLuongMon, 0, sizeof(hoaDon[i].soLuongMon));

        memset(hoaDon[i].giaMonGoi, 0, sizeof(hoaDon[i].giaMonGoi));

        memset(hoaDon[i].khachHang.tenKhachHang, '0', 2);
        hoaDon[i].khachHang.tenKhachHang[1] = '\0';

        memset(hoaDon[i].khachHang.soDienThoai, '0', 2);
        hoaDon[i].khachHang.soDienThoai[1] = '\0';

        hoaDon[i].khachHang.diemTichLuy = 0;

        hoaDon[i].ngayNhapDon.ngay = 0;
        hoaDon[i].ngayNhapDon.thang = 0;
        hoaDon[i].ngayNhapDon.nam = 0;

        hoaDon[i].soMonGoi = 0;
        hoaDon[i].tienThua = 0;
        hoaDon[i].tongTien = 0;
        hoaDon[i].tienNguyenLieu = 0;
    }
}

void saoChepHoaDon(HoaDon* hoaDonNhan, HoaDon* hoaDonNguon) {
    saoChepKhachHang(&(hoaDonNhan->khachHang), &(hoaDonNguon->khachHang));
    saoChepNgay(&(hoaDonNhan->ngayNhapDon), &(hoaDonNguon->ngayNhapDon));

    for(int i = 0; i < MAX_MON; i++) {
        strncpy(hoaDonNhan->tenMonGoi[i], hoaDonNguon->tenMonGoi[i], MAX_DO_DAI_TEN_MON - 1);
        hoaDonNhan->tenMonGoi[i][MAX_DO_DAI_TEN_MON - 1] = '\0';
        hoaDonNhan->soLuongMon[i] = hoaDonNguon->soLuongMon[i];
        hoaDonNhan->giaMonGoi[i] = hoaDonNhan->giaMonGoi[i];
    }

    hoaDonNhan->soMonGoi = hoaDonNhan->soMonGoi;
    hoaDonNhan->tongTien = hoaDonNguon->tongTien;
    hoaDonNhan->tienThua = hoaDonNguon->tienThua;
    hoaDonNhan->tienNguyenLieu = hoaDonNguon->tienNguyenLieu;
}

void themHoaDonVaoFile(HoaDon hoaDon, char duongDan[]) {
    // Them mot hoa don vao file
    // Khac voi ham doc tu file, ham nay nhan du lieu co san nen khong can chuan hoa

    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them hoa don vao file");
        return;
    }
    fprintf(fptr, "%s,%s,%d,%d,%d,%d,", hoaDon.khachHang.tenKhachHang, hoaDon.khachHang.soDienThoai, hoaDon.khachHang.diemTichLuy,
                                     hoaDon.ngayNhapDon.ngay, hoaDon.ngayNhapDon.thang, hoaDon.ngayNhapDon.nam);
    for(int i = 0; i < MAX_MON; i++) {
        fprintf(fptr, "%d,", hoaDon.soLuongMon[i]);
    }
    for(int i = 0; i < MAX_MON; i++) {
        fprintf(fptr, "%s,", hoaDon.tenMonGoi[i]);
    }
    for(int i = 0; i < MAX_MON; i++) {
        fprintf(fptr, "%.2f,", hoaDon.giaMonGoi[i]);
    }
    fprintf(fptr, "%d,%.2f,%.2f,%.2f\n", hoaDon.soMonGoi, hoaDon.tongTien, hoaDon.tienThua, hoaDon.tienNguyenLieu);
    fclose(fptr);
}

int kiemTraSoHoaDon(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong hoa don");
        return -1;
    }

    int soHoaDon = 0;
    fseek(fptr, sizeof(HOA_DON_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_HOA_DON];
    while(fgets(msg, MAX_ARRAY_LENGTH_HOA_DON, fptr)) {
        soHoaDon++;
    }

    fclose(fptr);

    return soHoaDon;
}

int coNhuNhauHoaDon(HoaDon h1, HoaDon h2) {
    // Kiem tra xem hai hoa don co cung thuoc tinh khong.
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(coNhuNhauKhachHang(h1.khachHang, h2.khachHang) && coNhuNhauNgay(h1.ngayNhapDon, h2.ngayNhapDon) && h1.soMonGoi == h2.soMonGoi
                            && h1.tongTien == h2.tongTien && h1.tienThua == h2.tienThua && h1.tienNguyenLieu == h2.tienNguyenLieu) {
        for(int i = 0; i < MAX_MON; i++) {
            if((h1.soLuongMon[i] != h2.soLuongMon[i])
            || (strcmp(h1.tenMonGoi[i], h2.tenMonGoi[i]) != 0)
            || h1.giaMonGoi[i] != h2.giaMonGoi[i]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void docFileHoaDon(char duongDan[], int soHoaDon, HoaDon danhSachHoaDon[]) {
    // Do lon cua mang file hoa don can lon hon hoac bang so hoa don doc
    if(soHoaDon == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong hoa don");
        return;
    }

    chuanHoaHoaDon(danhSachHoaDon, soHoaDon);
    char msg[MAX_ARRAY_LENGTH_HOA_DON];

    // Bo qua header
    fseek(fptr, sizeof(HOA_DON_HEADER), SEEK_SET);

    for(int i = 0; i < soHoaDon; i++) {
        if (fgets(msg, MAX_ARRAY_LENGTH_HOA_DON - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file hoa don");
            break;
        }

        msg[MAX_ARRAY_LENGTH_HOA_DON - 1] = '\0';
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh

        char *tenKhachHang = strtok(msg, NGAN_PHAN_TU_CSV);
        if (tenKhachHang) {
            strncpy(danhSachHoaDon[i].khachHang.tenKhachHang, tenKhachHang, DO_DAI_TEN_KHACH - 1);
            danhSachHoaDon[i].khachHang.tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
        }

        char *soDienThoai = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soDienThoai) {
            strncpy(danhSachHoaDon[i].khachHang.soDienThoai, soDienThoai, DO_DAI_SO_DIEN_THOAI - 1);
            danhSachHoaDon[i].khachHang.soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
        }

        char* diemTichLuy = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (diemTichLuy) {
            danhSachKhachHang[i].diemTichLuy = atoi(diemTichLuy);
        }

        char *ngay = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (ngay) {
            danhSachHoaDon[i].ngayNhapDon.ngay = atoi(ngay);
        }

        char *thang = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (thang) {
            danhSachHoaDon[i].ngayNhapDon.thang = atoi(thang);
        }

        char *nam = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (nam) {
            danhSachHoaDon[i].ngayNhapDon.nam = atoi(nam);
        }

        for(int j = 0; j < MAX_MON; j++) {
            char *soMon = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (soMon) {
                danhSachHoaDon[i].soLuongMon[j] = atoi(soMon);
            }
        }

        for(int j = 0; j < MAX_MON; j++) {
            char *tenMon = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (tenMon) {
                strncpy(danhSachHoaDon[i].tenMonGoi[j], tenMon, MAX_DO_DAI_TEN_MON - 1);
                danhSachHoaDon[i].tenMonGoi[j][MAX_DO_DAI_TEN_MON - 1] = '\0';
            }
        }

        for(int j = 0; j < MAX_MON; j++) {
            char *giaMon = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (giaMon) {
                danhSachHoaDon[i].giaMonGoi[j] = atof(giaMon);
            }
        }

        char *soMonGoi = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soMonGoi) {
            danhSachHoaDon[i].soMonGoi = atoi(soMonGoi);
        }

        char *tongTien = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (tongTien) {
            danhSachHoaDon[i].tongTien = atof(tongTien);
        }

        char *tienThua = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (tienThua) {
            danhSachHoaDon[i].tienThua = atof(tienThua);
        }

        char *tienNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (tienNguyenLieu) {
            danhSachHoaDon[i].tienNguyenLieu = atof(tienNguyenLieu);
        }
    }

    fclose(fptr);
}

void xoaHoaDonKhoiFile(HoaDon hoaDonXoa, char duongDan[]) {
    int soHoaDonFile = kiemTraSoHoaDon(duongDan);
    if(soHoaDonFile == 0) {
        printf("File khong co hoa don\n");
        return;
    }

    // Xoa mot khach hang co spec tuong tu khachXoa khoi file
    HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
    docFileHoaDon(duongDan, soHoaDonFile, danhSachHoaDonFile);

    for(int i = 0; i < soHoaDonFile; i++) {
        if(coNhuNhauHoaDon(danhSachHoaDonFile[i], hoaDonXoa) == 1) {
            for(int j = i; j < soHoaDonFile - 1; j++) {
                danhSachHoaDonFile[j] = danhSachHoaDonFile[j + 1];
            }
            soHoaDonFile--;
            break;
        }
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file de xoa hoa don");
        return;
    }
        
    fprintf(fptr, HOA_DON_HEADER);
    for(int i = 0; i < soHoaDonFile; i++) {
        fprintf(fptr, "%s,%s,%d,%d,%d,%d,", danhSachHoaDonFile[i].khachHang.tenKhachHang, danhSachHoaDonFile[i].khachHang.soDienThoai, danhSachHoaDon[i].khachHang.diemTichLuy,
                                     danhSachHoaDonFile[i].ngayNhapDon.ngay, danhSachHoaDonFile[i].ngayNhapDon.thang, danhSachHoaDonFile[i].ngayNhapDon.nam);
        for(int i = 0; i < MAX_MON; i++) {
            fprintf(fptr, "%d,", danhSachHoaDonFile[i].soLuongMon[i]);
        }
        for(int i = 0; i < MAX_MON; i++) {
            fprintf(fptr, "%s,", danhSachHoaDonFile[i].tenMonGoi[i]);
        }
        for(int i = 0; i < MAX_MON; i++) {
            fprintf(fptr, "%.2f,", danhSachHoaDonFile[i].giaMonGoi[i]);
        }
        fprintf(fptr, "%d,%.2f,%.2f,%.2f\n", danhSachHoaDonFile[i].soMonGoi, danhSachHoaDonFile[i].tongTien, danhSachHoaDonFile[i].tienThua, danhSachHoaDonFile[i].tienNguyenLieu);
    }

    printf("Xoa hoa don khoi file thanh cong\n");
    fclose(fptr);
    free(danhSachHoaDonFile);
}


#endif