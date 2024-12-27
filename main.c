#include "menu.h"

#include <stdio.h>
#include <string.h>

#define PLACEHOLDER_QUAN_LY "<placeholder>\n"
#define SO_DOI_TUONG_LAM_VIEC 4 // kho, khach, hoa don, menu

#define MAX_KHACH_HANG 100
#define MAX_HOA_DON 100
#define MAX_FILE_PATH_LENGTH 200
#define MAX_DONG_DU_LIEU 1000

#define LUA_CHON_KHACH_HANG 1
#define LUA_CHON_HOA_DON 2
#define LUA_CHON_KHO 3
#define LUA_CHON_MENU 4

#define MANAGING_FILE "./pathFile.txt"

// Khai báo các mảng để lưu menu, danh sách khách hàng và hóa đơn
MonAn menuMacDinh[MAX_MON] = {
    {"Ca phe den", 25.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Duong", "kg", 0.01, 13.00}}, 2},
    {"Ca phe sua", 30.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Sua dac", "hop", 0.01, 15.00}}, 2},
    {"Tra sua", 35.0, {{"Tra den", "kg", 0.01, 10.00}, {"Sua tuoi", "lit", 0.01, 20.00}}, 2},
    {"Ca phe da xay", 40.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Da vien", "kg", 0.1, 5.00}}, 2},
    {"Nuoc cam", 20.0, {{"Cam tuoi", "kg", 0.25, 25.00}}, 1},
    {"Sinh to dua hau", 35.0, {{"Dua hau", "kg", 0.3, 10.00}, {"Sua dac", "hop", 0.02, 15.00}}, 2},
    {"Banh mi op la", 50.0, {{"Bot banh mi", "kg", 0.15, 20.00}, {"Trung ga", "qua", 1, 5.00}}, 2},
    {"Banh mi que", 20.0, {{"Bot banh mi", "kg", 0.1, 20.00}, {"Pate gan", "hop", 0.02, 30.00}}, 2},
    {"Banh bao nhan thit", 25.0, {{"Bot banh bao", "kg", 0.2, 18.00}, {"Thit heo xay", "kg", 0.1, 50.00}}, 2},
    {"Nuoc ep tao", 30.0, {{"Tao tuoi", "kg", 0.3, 15.00}, {"Duong", "kg", 0.01, 13.00}}, 2}
};

int soMonMacDinh = 10;

NguyenLieu khoNguyenLieuMacDinh[MAX_NGUYEN_LIEU] = {
    {"Ca phe bot", "kg", 10.0, 200.0},       // Price per kg
    {"Sua dac", "hop", 20.0, 15.0},         // Price per can
    {"Sua tuoi", "lit", 15.0, 12.0},        // Price per liter
    {"Duong", "kg", 8.0, 10.0},             // Price per kg
    {"Tra den", "kg", 5.0, 150.0},          // Price per kg
    {"Tran chau", "kg", 7.0, 50.0},         // Price per kg
    {"Da vien", "kg", 50.0, 5.0},           // Price per kg
    {"Cam tuoi", "kg", 12.0, 25.0},         // Price per kg
    {"Dua hau", "kg", 20.0, 10.0},          // Price per kg
    {"Bot banh mi", "kg", 25.0, 18.0},      // Price per kg
    {"Thit heo xay", "kg", 10.0, 120.0},    // Price per kg
    {"Bot banh bao", "kg", 15.0, 22.0},     // Price per kg
    {"Trung ga", "qua", 30.0, 3.0},         // Price per egg
    {"Bo", "kg", 5.0, 80.0},                // Price per kg
    {"Pate gan", "hop", 10.0, 20.0},        // Price per can
    {"Tao tuoi", "kg", 18.0, 30.0},         // Price per kg
    {"Tuong ot", "chai", 12.0, 10.0},       // Price per bottle
    {"Dau an", "lit", 10.0, 25.0},          // Price per liter
    {"Hanh tay", "kg", 8.0, 12.0},          // Price per kg
    {"Mayonnaise", "chai", 10.0, 15.0}      // Price per bottle
};


KhachHang danhSachKhachHang[MAX_KHACH_HANG];
HoaDon danhSachHoaDon[MAX_HOA_DON];
int soKhachHang = 0, soHoaDon = 0;

// Cac ham lam viec voi menu va thanh toan
void hienThiMenu(MonAn menu[], int soMon);
void themMon(MonAn menu[], int *soMon, NguyenLieu kho[], int soNguyenLieu);
void xoaMonAn(MonAn menu[], int* soMonAn, char tenMonXoa[]);
void suaMon(MonAn menu[], int soMon, NguyenLieu kho[], int soNguyenLieuKho);
void nhapThongTinMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho);
void chuanHoaMonAn(MonAn* monAn, int soLuongMonAn);
void thanhToan(MonAn menu[], int soMon, HoaDon danhSachHoaDon[], int *soHoaDon, 
                KhachHang danhSachKhachHang[], int *soKhachHang, NguyenLieu kho[], int soNguyenLieuKho);

// Cac ham lam viec voi hoa don
void luuHoaDon(HoaDon danhSachHoaDon[], int *soHoaDon, HoaDon hoaDon);
void xemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon);
void timKiemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon);
void xoaHoaDon(HoaDon danhSach[], int* soLuong, HoaDon hoaDonXoa);
void nhapThongTinHoaDon(HoaDon* hoaDon, MonAn menu[], int soMon);

// Cac ham lam viec voi khach hang
void themKhachHang(KhachHang danhSachKhachHang[], int *soKhachHang, KhachHang khachHangMoi);
void xemDanhSachKhachHang(KhachHang danhSachKhachHang[], int soKhachHang);
void timKiemKhachHang(KhachHang danhSachKhachHang[], int soKhachHang);
void xoaKhachHang(KhachHang danhSachKhach[], int* soLuong, KhachHang khachXoa);
void nhapThongTinKhach(KhachHang* khachHang);

// Cac ham lam viec voi kho
void hienThiKho(NguyenLieu kho[], int soLuong);
void themNguyenLieu(NguyenLieu kho[], int* soLuong);
void xoaNguyenLieu(NguyenLieu kho[], int* soLuong, char tenNguyenLieuXoa[]);
void xoaNguyenLieuBangSTT(NguyenLieu kho[], int* soLuong);
void layNguyenLieu(NguyenLieu kho[], int soNguyenLieuKho, NguyenLieu nguyenLieuSuDung, int soMon);
void timKiemNguyenLieu(NguyenLieu kho[], int soNguyenLieu);
void nhapThongTinNguyenLieu(NguyenLieu* nguyenLieu);

// Cac ham ho tro quan li file
void docFileQuanLi(int luatChon, char duongDan[]);
void capNhatFileQuanLi(int luaChon, char duongDanMoi[]);
void saferScanf(char formatString[], void* addr);

// Ham chuc nang chung
void clearBuffer();

int main() {
    // Tao mot file luu dia chi cua file quan li hoa don va khach hang; file luu duong dan o dang file .txt, duong dan file khach hang o dong tren
    // va duong dan file hoa don o dong duoi. Cac duong dan ket thuc bang '\n'
    // TAT CA DUONG DAN SE THONG NHAT SU DUNG "/" THAY CHO "\\"

    // Chu y: strcspn se crash chuong trinh neu chuoi duoc tim (chuoi argument dau) la rong
    // Nen clearBuffer() truoc khi bat dau nhan du lieu moi. vd case 4 (xoa khach hang), muc khach hang

    FILE* pathFile;
    char fileQuanLiChung[MAX_FILE_PATH_LENGTH]; // Xau hung du lieu tu docFileQuanLi() cho ba doi tuong: khach hang, hoa don, kho

    pathFile = fopen(MANAGING_FILE, "r");
    if(pathFile) { // Tep ton tai
        fclose(pathFile); // ham docFileQuanLi() se tu mo file nen phai dong file da mo o tren truoc
    } else { // Tep khong ton tai
        printf("Chu y, ban can cai dat duong dan den file quan li khach hang va hoa don!\n");
        pathFile = fopen(MANAGING_FILE, "w");
        if (!pathFile) {
            perror("Khon the tao file luu tru duong dan");
        } else {
            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                fprintf(pathFile, PLACEHOLDER_QUAN_LY);         // Quan trong, xay dung cau truc cho file quan ly
            }
            fclose(pathFile);
        }
    }

    // Cap nhat kho nguyen lieu tu du lieu trong file kho neu co du lieu trong file kho
    NguyenLieu* khoNguyenLieuSuDung;
    int soLuongNguyenLieuSuDung;
    int canFreeKhoNguyenLieu = 0;

    docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
    int soLuongNguyenLieu = kiemTraSoNguyenLieu(fileQuanLiChung);
    if(soLuongNguyenLieu != -1 && soLuongNguyenLieu != 0) { 
        khoNguyenLieuSuDung = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soLuongNguyenLieu);
        if(khoNguyenLieuSuDung) {
            docFileKho(fileQuanLiChung, soLuongNguyenLieu, khoNguyenLieuSuDung);
            soLuongNguyenLieuSuDung = soLuongNguyenLieu;
            canFreeKhoNguyenLieu = 1;
        } else {
            printf("Khong the khoi tao mang dong cho kho nguyen lieu\n");
            printf("Su dung du lieu mac dinh\n");
            khoNguyenLieuSuDung = khoNguyenLieuMacDinh;
            soLuongNguyenLieuSuDung = MAX_NGUYEN_LIEU;
        }
    } else { // Khong the mo file hoac file trong
        printf("Su dung du lieu mac dinh\n");
        khoNguyenLieuSuDung = khoNguyenLieuMacDinh;
        soLuongNguyenLieuSuDung = MAX_NGUYEN_LIEU;
    }   

    // Cap nhat du lieu menu tu file
    MonAn* menuSuDung;
    int soMonSuDung;
    int canFreeMenu = 0;

    docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
    int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
    if(soMonFile != -1 && soMonFile != 0) {
        menuSuDung = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
        if(menuSuDung) {
            docFileMenu(fileQuanLiChung, soMonFile, menuSuDung);
            soMonSuDung = soMonFile;
            canFreeMenu = 1;
        } else {
            printf("Khong the khoi tao mang dong cho menu\n");
            printf("Su dung du lieu mac dinh\n");
            menuSuDung = menuMacDinh;
            soMonSuDung = soMonMacDinh;
        }
    } else {
        printf("Su dung du lieu mac dinh\n");
        menuSuDung = menuMacDinh;
        soMonSuDung = soMonMacDinh;
    }

    int luaChon = -1, luaChonCon = -1, luaChonCon2 = -1; // Gan mot gia tri khong phai la mot trong nx lua chon switch-case ben duoi.
                                                         // Bat buoc de dam bao gia tri khong hop le co the duoc xu li dung cach
    do {
        printf("\n--- MENU QUAN CA PHE ---\n");
        printf("1. Menu\n");
        printf("2. Thanh toan\n");
        printf("3. Hoa don\n");
        printf("4. Khach hang\n");
        printf("5. Kho\n");
        printf("6. Thong ke\n");
        printf("7. Xu li file\n");
        printf("8. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);
        
        switch (luaChon) {
            case 1:
                do {
                    printf("\n--- MENU ---\n");
                    printf("1. Xem danh sach mon\n");
                    printf("2. Them mon\n");
                    printf("3. Xoa mon\n");
                    printf("4. Sua mon\n");
                    printf("5. Cap nhat file menu\n");
                    printf("6. Xoa du lieu menu\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");
                    scanf("%d", &luaChonCon);
                    
                    switch (luaChonCon) {
                        case 1: {
                            while(getchar() != '\n');
                            int luaChonXem;
                            printf("Xem menu hien tai (1) hay xem menu tu file (2): ");
                            saferScanf("%d", &luaChonXem);
                            if(luaChonXem != 1 && luaChonXem != 2) {
                                printf("Lua chon khong hop le.\n");
                            } else if(luaChonXem == 1) {
                                hienThiMenu(menuSuDung, soMonSuDung);
                            } else if(luaChonXem == 2) {
                                docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                                int soMonAnFile = kiemTraSoMonAn(fileQuanLiChung);
                                if(soMonAnFile == 0) {
                                    printf("Chua co mon an trong file\n");
                                    break;
                                }

                                MonAn* danhSachMonAnFile = (MonAn*) malloc(sizeof(MonAn) * soMonAnFile);
                                if(!danhSachMonAnFile) {
                                    printf("Khong the khoi tao mang dong de xem menu\n");
                                    break;
                                }

                                docFileMenu(fileQuanLiChung, soMonAnFile, danhSachMonAnFile);
                                hienThiMenu(danhSachMonAnFile, soMonAnFile);
                                free(danhSachMonAnFile);
                            }
                            break;
                        }
                        case 2: {
                            while(getchar() != '\n');
                            int luaChonThem;
                            printf("Them nguyen lieu vao mang kho hien tai (1) hay them nguyen lieu vao file (2): ");
                            saferScanf(" %d", &luaChonThem);

                            if(luaChonThem != 1 && luaChonThem != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonThem == 1) {
                                if(soMonSuDung >= MAX_MON) {
                                    printf("Da day, khong the them mon\n");
                                    break;
                                }
                                MonAn monMoi;
                                nhapThongTinMonAn(&monMoi, khoNguyenLieuSuDung, soLuongNguyenLieuSuDung); 

                                int thoat = 0;
                                for(int i = 0; i < soMonSuDung; i++) {
                                    if(strcmp(menuSuDung[i].tenMon, monMoi.tenMon) == 0) {
                                        printf("Mon an da co trong menu\n");
                                        thoat = 1;
                                        break;
                                    }
                                }
                                if(thoat == 1) {
                                    break;
                                }
                                saoChepMonAn(&menuSuDung[soMonSuDung], &monMoi);
                                soMonSuDung++;
                            } else if(luaChonThem == 2) {
                                docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                                int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                                if(soMonFile >= MAX_MON) {   // De dam bao tinh dong nhat, file kho cung khong the chua qua MAX_NGUYEN_LIEU nguyen lieu
                                    printf("Da day, khong the cho mon vao file\n");
                                    break;
                                }
                                MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
                                if(!menuFile) {
                                    printf("Khong the khoi tao mang dong de them them mon an\n");
                                    break;
                                }
                                docFileMenu(fileQuanLiChung, soMonFile, menuFile);
            
                                MonAn monMoi;
                                nhapThongTinMonAn(&monMoi, khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);

                                // Kiem tra xem mon an da co trong file chua
                                int thoat = 0;
                                for(int i = 0; i < soMonFile; i++) {
                                    if(strcmp(menuFile[i].tenMon, monMoi.tenMon) == 0) {
                                        printf("Mon an da co trong file\n");
                                        free(menuFile);
                                        thoat = 1;
                                        break;
                                    }
                                }
                                if(thoat == 1) {
                                    break;
                                }

                                themMonAnVaoFile(monMoi, fileQuanLiChung);
                                free(menuFile);
                            }
                            printf("Mon an da duoc them\n");
                            break;
                        }
                        case 3: {
                            while(getchar() != '\n');
                            int luaChonXoaBo;

                            printf("Xoa mon an trong menu hien tai (1) hay xoa mon an trong file kho (2) ");
                            saferScanf("%d", &luaChonXoaBo);

                            if(luaChonXoaBo != 1 && luaChonXoaBo != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }

                            char tenMonXoa[MAX_DO_DAI_TEN_MON];
                            printf("Ten mon an xoa: ");
                            fgets(tenMonXoa, MAX_DO_DAI_TEN_MON - 1, stdin);     //MARK: STR_PRO
                            tenMonXoa[MAX_DO_DAI_TEN_MON - 1] = '\0';
                            tenMonXoa[strcspn(tenMonXoa, "\n")] = '\0';
                            
                            if(luaChonXoaBo == 1) {
                                xoaMonAn(menuSuDung, &soMonSuDung, tenMonXoa);
                            } else {
                                docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                                xoaMonAnKhoiFile(tenMonXoa, fileQuanLiChung);
                            }

                            break;
                        }
                        case 4: {
                            while(getchar() != '\n');
                            int luaChonSua;
                            printf("Sua mon trong menu hien tai (1) hay sua mon trong file menu tu file (2): ");
                            saferScanf("%d", &luaChonSua);

                            if(luaChonSua != 1 && luaChonSua != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }
                
                            char monThayDoi[MAX_DO_DAI_TEN_MON];
                            hienThiMenu(menuSuDung, soMonSuDung);
                            printf("Nhap ten mon an can thay doi: ");
                            fgets(monThayDoi, MAX_DO_DAI_TEN_MON - 1, stdin); //BREAK
                            monThayDoi[strcspn(monThayDoi, "\n")] = '\0';
                            
                            int timThayMon = 0;
                            int viTriMonCanSua = 0; // Index mon can sua trong menu
                            
                            if(luaChonSua == 1) {
                                for(int i = 0; i < soMonSuDung; i++) {
                                    if(strcmp(monThayDoi, menuSuDung[i].tenMon) == 0) {
                                        timThayMon = 1;
                                        viTriMonCanSua = i;
                                        break;
                                    }
                                }
                                if(timThayMon == 0) {
                                    printf("Menu khong co mon: %s\n", monThayDoi);
                                    printf("Co le ban da danh thua dau cach?\n");
                                    break;
                                }

                                printf("Nhap thong tin moi cho mon can sua\n");
                                nhapThongTinMonAn(&menuSuDung[viTriMonCanSua], khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);
                            } else {
                                docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                                int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                                MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
                                if(!menuFile) {
                                    perror("Khong the tao mang dong de sua mon trong file");
                                    break;
                                }

                                for(int i = 0; i < soMonFile; i++) {
                                    if(strcmp(monThayDoi, menuFile[i].tenMon) == 0) {
                                        timThayMon = 1;
                                        viTriMonCanSua = i;
                                        break;
                                    }
                                }
                                if(timThayMon == 0) {
                                    printf("Menu khong co mon: %s\n", monThayDoi);
                                    printf("Co le ban da danh thua dau cach?\n");
                                    break;
                                }

                                printf("Nhap thong tin moi cho mon can sua\n");
                                nhapThongTinMonAn(&menuFile[viTriMonCanSua], khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);
                                free(menuFile);
                            }

                            printf("Mon an da duoc sua\n");

                            break;
                        }
                        case 5: {
                            while(getchar() != '\n');
                            int luaChonCapNhat;

                            printf("Cap nhat thong tin tu file vao mang (1) hay tu mang vao file (2) ");
                            saferScanf("%d", &luaChonCapNhat);

                            if(luaChonCapNhat != 1 && luaChonCapNhat != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }
                            
                            docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                            int soMonAnFile = kiemTraSoMonAn(fileQuanLiChung);
                            MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * soMonAnFile);
                            if(!menuFile) {
                                printf("Khong the khoi tao mang dong de cap nhat menu\n");
                                break;
                            }
                            docFileMenu(fileQuanLiChung, soMonAnFile, menuFile);

                            if(luaChonCapNhat == 1) {
                                // Them mon tu file vao mang dam bao dieu kien khong bi lap va khong vuot qua so mon an cho phep
                                // Cac mon an cu khong bi xoa bo. Tuy nhien, mon an cung ten nhung khac gia tri vx co the duoc update                   
                                int coMat = 0;
                                for (int i = 0; i < soMonAnFile; i++) {
                                    coMat = 0;
                                    if (soMonSuDung >= MAX_MON) {
                                        printf("Mang da day\n");
                                        break;
                                    }

                                    for(int j = 0; j < soMonSuDung; j++) {
                                        if(strcmp(menuFile[i].tenMon, menuSuDung[j].tenMon) == 0) {
                                            // Cap nhat du lieu cho nguyen lieu cung ten nhung khac thuoc tinh
                                            // Khong tang so nguyen lieu
                                            saoChepMonAn(&menuSuDung[j], &menuFile[i]); 
                                            coMat = 1;
                                            break;
                                        }
                                    }

                                    if(coMat == 0) {
                                        saoChepMonAn(&menuSuDung[soMonSuDung], &menuFile[i]);
                                        soMonSuDung++;
                                    }
                                }
                            } else if(luaChonCapNhat == 2) {
                                // Tranh lap. Mon an trong file trung ten voi trong mang nhung thuoc tinh khac thi thuoc tinh cua mon an file se duoc cap nhat
                                // File bi gioi han so luong mon an ve MAX_MON de dam bao dong nhat. Dieu nay khac voi file hoa don va khach hang va tuong tu voi file hoa don
                                int coMat = 0;
                                MonAn menuMoi[MAX_MON]; // Chu y khong the dung mang dong o tren de hung nguyen lieu moi duoc do size co the se it hon so nguyen lieu hien co trong mang
                                chuanHoaMonAn(menuMoi, MAX_MON);
                                for (int i = 0; i < soMonSuDung; i++) {
                                    coMat = 0;
                                    if (soMonAnFile >= MAX_NGUYEN_LIEU) {
                                        printf("File da day\n");
                                        break;
                                    }

                                    for(int j = 0; j < soMonAnFile; j++) {
                                        if(strcmp(menuFile[j].tenMon, menuSuDung[i].tenMon) == 0) {
                                            // Cap nhat du lieu cho mon an cung ten nhung khac thuoc tinh
                                            // Khong tang so mon an
                                            saoChepMonAn(&menuMoi[j], &menuSuDung[i]);
                                            coMat = 1;
                                            break;
                                        }
                                    }

                                    if(coMat == 0) {
                                        saoChepMonAn(&menuMoi[soMonAnFile], &menuSuDung[i]);
                                        soMonAnFile++;
                                    }
                                }
                                // Cap nhat du lieu vao lai file
                                // Don sach thong tin cu cua file
                                FILE* fptr = fopen(fileQuanLiChung, "w");
                                if(!fptr) {
                                    perror("Khong the mo file de cap nhat thong tin");
                                    break;
                                }
                                fprintf(fptr, MENU_HEADER);
                                fclose(fptr); // Dong file de tranh xung dot khi them nguyen lieu ben duoi
                                themNhieuMonAnVaoFile(menuMoi, soMonAnFile, fileQuanLiChung);
                            }
                            free(menuFile);
                            printf("Cap nhat du lieu thanh cong\n");
                            break;
                        }
                        case 6: {
                            while(getchar() != '\n');
                            int canhCao;
                            printf("CANH BAO: VIEC NAY SE XOA TOAN BO DU LIEU CUA BAN VA KHONG THE BI DAO NGUOC. TIEP TUC? (1) ");
                            saferScanf("%d", &canhCao);
                            if(canhCao != 1) {
                                break;
                            }

                            int luaChonXoa;
                            printf("Xoa du lieu kho hien tai (1) hay xoa du lieu file kho (2) ");
                            saferScanf("%d", &luaChonXoa);
                            
                            if(luaChonXoa != 1 && luaChonXoa != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonXoa == 1) {
                                soMonSuDung = 0;
                                printf("Mang menu da duoc reset\n");
                            } else {
                                docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                                FILE* fptr = fopen(fileQuanLiChung, "w");
                                if(!fptr) {
                                    perror("Xoa du lieu that bai");
                                    break;
                                }

                                // Viet lai header vao file
                                fprintf(fptr, MENU_HEADER);
                                fclose(fptr);
                                printf("Xoa du lieu file thanh cong!\n");
                            }
                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long chon lai.\n");
                            clearBuffer();
                            
                    }
                } while (luaChonCon != 7);
                break;
            case 2: {
                clearBuffer();
                thanhToan(menuSuDung, soMonSuDung, danhSachHoaDon, &soHoaDon, danhSachKhachHang, &soKhachHang, khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);
                break;
            }
            case 3:
                do {
                    printf("\n--- HOA DON ---\n");
                    printf("1. Xem danh sach hoa don\n");
                    printf("2. Tim kiem hoa don\n");
                    printf("3. Them hoa don vao file\n");
                    printf("4. Xoa hoa don\n");
                    printf("5. Cap nhat file hoa don\n");
                    printf("6. Xoa du lieu hoa don\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");
                    scanf("%d", &luaChonCon);
            
                    switch (luaChonCon) {
                        case 1: {
                            while(getchar() != '\n');
                            int luaChonXem;
                            printf("Xem hoa don hien tai (1) hay xem hoa don tu file (2): ");
                            saferScanf("%d", &luaChonXem);
                            if(luaChonXem != 1 && luaChonXem != 2) {
                                printf("Lua chon khong hop le.\n");
                            } else if(luaChonXem == 1) {
                                xemHoaDon(danhSachHoaDon, soHoaDon);
                            } else if(luaChonXem == 2) {
                                docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                                int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                                if(soHoaDonFile == 0) {
                                    printf("Chua co hoa don trong file\n");
                                    break;
                                }

                                HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                                if(!danhSachHoaDonFile) {
                                    printf("Khong the khoi tao mang dong de xem danh sach hoa don\n");
                                    break;
                                }

                                docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);
                                xemHoaDon(danhSachHoaDonFile, soHoaDonFile);
                                free(danhSachHoaDonFile);
                            }
                            break;
                        }
                        case 2: {
                            while(getchar() != '\n');
                            int luaChonTimKiem;
                            printf("Tim kiem hoa don hien tai (1) hay tim kiem hoa don trong file (2): ");
                            saferScanf("%d", &luaChonTimKiem);
                            if(luaChonTimKiem == 1) {
                                timKiemHoaDon(danhSachHoaDon, soHoaDon);
                            } else if(luaChonTimKiem == 2) {
                                docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                                int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                                HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                                if(!danhSachHoaDonFile) {
                                    printf("Khong the khoi tao mang dong de tim kiem hoa don\n");
                                    break;
                                }

                                docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);
                                timKiemHoaDon(danhSachHoaDonFile, soHoaDonFile);
                                free(danhSachHoaDonFile);
                            } else {
                                printf("Lua chon khong hop le.\n");
                            }
                            break;
                        }
                        case 3: {
                            while(getchar() != '\n');
                            HoaDon hoaDonMoi;
                            nhapThongTinHoaDon(&hoaDonMoi, menuSuDung, soMonSuDung);

                            // Kiem tra xem hoa don da co trong file chua. Neu chua, them hoa don vao file
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                            docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);
                            if(!danhSachHoaDonFile) {
                                perror("Khong the tao mang dong");
                                break;
                            }

                            int coMat = 0;
                            for(int i = 0; i < soHoaDonFile; i++) {
                                if(coNhuNhauHoaDon(hoaDonMoi, danhSachHoaDonFile[i]) == 1) {
                                    printf("Hoa don da co trong file\n");
                                    coMat = 1;
                                    break;
                                }
                            }
                            if(coMat == 0) {
                                themHoaDonVaoFile(hoaDonMoi, fileQuanLiChung);  //MARK: LAP_FILE
                                printf("Hoa don da duoc luu vao file\n");   
                            }
                            free(danhSachHoaDonFile);
                            break;
                        }
                        case 4: {
                            while(getchar() != '\n');
                            int luaChonXoaBo;

                            printf("Xoa hoa don trong mang (1) hay xoa hoa don trong file (2) ");
                            saferScanf("%d", &luaChonXoaBo);

                            if(luaChonXoaBo != 1 && luaChonXoaBo != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonXoaBo == 1) {
                                if(soHoaDon == 0) {
                                    printf("Khong co hoa don\n");
                                    break;
                                }
                                HoaDon hoaDonXoa;
                                nhapThongTinHoaDon(&hoaDonXoa, menuSuDung, soMonSuDung);   
                                xoaHoaDon(danhSachHoaDon, &soHoaDon, hoaDonXoa);    // MARK: LAP_MANG
                            } else if(luaChonXoaBo == 2){
                                docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                                if(kiemTraSoHoaDon(fileQuanLiChung) == 0) {
                                    printf("Khong co hoa don\n");
                                    break;
                                }
                                HoaDon hoaDonXoa;
                                nhapThongTinHoaDon(&hoaDonXoa, menuSuDung, soMonSuDung);   
                                xoaHoaDonKhoiFile(hoaDonXoa, fileQuanLiChung);  // MARK: LAP_FILE
                            }
                            break;
                        }
                        case 5: {
                            while(getchar() != '\n');
                            int luaChonCapNhat;

                            printf("Cap nhat thong tin tu file vao mang (1) hay tu mang vao file (2) ");
                            saferScanf("%d", &luaChonCapNhat);

                            if(luaChonCapNhat != 1 && luaChonCapNhat != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }

                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            if(luaChonCapNhat == 1 && soHoaDonFile == 0) {
                                printf("File chua co hoa don\n");
                                break;
                            } else if(luaChonCapNhat == 2 && soHoaDon == 0) {
                                printf("Mang chua co hoa don\n");
                                break;
                            }

                            HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                            if(!danhSachHoaDonFile) {
                                printf("Khong the khoi tao mang dong de cap nhat hoa don\n");
                                break;
                            }
                            docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);

                            if(luaChonCapNhat == 1) {
                                int coMat = 0;
                                for (int i = 0; i < soHoaDonFile; i++) {
                                    coMat = 0;
                                    if (soHoaDon >= MAX_HOA_DON) {
                                        break;
                                    }

                                    for(int j = 0; j < soHoaDon; j++) {
                                        if(coNhuNhauHoaDon(danhSachHoaDonFile[i], danhSachHoaDon[j]) == 1) {
                                            coMat = 1;
                                            break;
                                        }
                                    }

                                    if(coMat == 0) {
                                        saoChepHoaDon(&danhSachHoaDon[soHoaDon], &danhSachHoaDonFile[i]);
                                        soHoaDon++;
                                    }
                                }
                                printf("Mang hoa don da duoc cap nhat\n");
                            } else if(luaChonCapNhat == 2){
                                for(int i = 0; i < soHoaDon; i++) {
                                    int coMatTrongFile = 0; // 1 neu hoa don da co trong file; 0 neu khong co mat
                                    for(int j = 0; j < soHoaDonFile; j++) {
                                        coMatTrongFile = coNhuNhauHoaDon(danhSachHoaDon[i], danhSachHoaDonFile[j]);
                                        if(coMatTrongFile == 1) {
                                            break;
                                        }
                                    }
                                    if(coMatTrongFile == 0) {
                                        themHoaDonVaoFile(danhSachHoaDon[i], fileQuanLiChung);  //MARK: FILE_MANG
                                    }
                                }
                                printf("File hoa don da duoc cap nhat\n");
                            }
                            free(danhSachHoaDonFile);
                            break;
                        }
                        case 6: {
                            while(getchar() != '\n');
                            int canhCao;
                            printf("CANH BAO: VIEC NAY SE XOA TOAN BO DU LIEU CUA BAN VA KHONG THE BI DAO NGUOC. TIEP TUC? (1) ");
                            scanf(" %d", &canhCao);
                            if(canhCao != 1) {
                                break;
                            }

                            int luaChonXoa;
                            printf("Xoa du lieu mang hoa don hien tai (1) hay xoa du lieu file hoa don (2) ");
                            scanf(" %d", &luaChonXoa);
                            clearBuffer();
                            
                            if(luaChonXoa != 1 && luaChonXoa != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonXoa == 1) {
                                memset(danhSachHoaDon, 0, sizeof(danhSachHoaDon)); // Co can thiet khong??
                                soHoaDon = 0;
                                printf("Mang hoa don da duoc reset\n");
                            } else {
                                docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                                FILE* fptr = fopen(fileQuanLiChung, "w");
                                if(!fptr) {
                                    perror("Xoa du lieu that bai");
                                    break;
                                }

                                // Viet lai header vao file
                                fprintf(fptr, HOA_DON_HEADER);

                                fclose(fptr);
                                printf("Xoa du lieu file thanh cong!\n");
                            }

                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long chon lai.\n");
                            clearBuffer();              
                    }
                } while (luaChonCon != 7);
                break;
            case 4:
                do {
                    printf("\n--- KHACH HANG ---\n");
                    printf("1. Xem danh sach khach hang\n");
                    printf("2. Tim kiem khach hang\n");
                    printf("3. Them khach hang\n"); // Them thu cong mot khach hang
                    printf("4. Xoa khach hang\n");  // Xoa thu cong mot khach hang
                    printf("5. Cap nhat du lieu khach hang\n");
                    printf("6. Xoa du lieu khach hang\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");
                    scanf("%d", &luaChonCon);
            
                    switch (luaChonCon) {
                        case 1: {
                            while(getchar() != '\n');
                            int luaChonXem;
                            printf("Xem khach hang hien tai (1) hay xem khach hang tu file (2): ");
                            saferScanf(" %d", &luaChonXem);

                            if(luaChonXem != 1 && luaChonXem != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonXem == 1) {
                                xemDanhSachKhachHang(danhSachKhachHang, soKhachHang);
                            } else if(luaChonXem == 2) {
                                docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                                int soKhachHangFile = kiemTraSoKhachHang(fileQuanLiChung);

                                // Tap mot mang dong de hung gia tri doc duoc tu file.
                                // Su dung mang dong thay cho mang thuong de toi uu bo nho
                                KhachHang* danhSachKhachHangFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachHangFile);
                                if(!danhSachKhachHangFile) {
                                    printf("Khong the khoi tao mang dong de xem danh sach khach hang\n");
                                    break;
                                }
                                docFileKhachHang(fileQuanLiChung, soKhachHangFile, danhSachKhachHangFile);
                                xemDanhSachKhachHang(danhSachKhachHangFile, soKhachHangFile);
                                free(danhSachKhachHangFile);
                            }
                            break;
                        }
                        case 2: {
                            while(getchar() != '\n');
                            int luaChonTimKiem;
                            printf("Tim kiem khach hang hien tai (1) hay tim kiem khach hang trong file (2): ");
                            saferScanf(" %d", &luaChonTimKiem);

                            if(luaChonTimKiem != 1 && luaChonTimKiem != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonTimKiem == 1) {
                                timKiemKhachHang(danhSachKhachHang, soKhachHang);
                            } else if(luaChonTimKiem == 2) {
                                docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                                int soKhachHangFile = kiemTraSoKhachHang(fileQuanLiChung);
                                if(soKhachHangFile == 0) {
                                    printf("Chua co khach hang\n");
                                    break;
                                }
                                KhachHang* danhSachKhachHangFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachHangFile);
                                if(!danhSachKhachHangFile) {
                                    printf("Khong the khoi tao mang dong de tim kiem khach hang\n");
                                    break;
                                }
                                docFileKhachHang(fileQuanLiChung, soKhachHangFile, danhSachKhachHangFile);
                                timKiemKhachHang(danhSachKhachHangFile, soKhachHangFile);
                                free(danhSachKhachHangFile);
                            }
                            break;
                        }
                        case 3: {
                            while(getchar() != '\n');
                            int luaChonThem;
                            printf("Them khach hang vao mang hien tai (1) hay them khach hang vao file (2): ");
                            saferScanf(" %d", &luaChonThem);

                            if(luaChonThem != 1 && luaChonThem != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonThem == 1) {
                                if(soKhachHang >= MAX_KHACH_HANG) {
                                    printf("Da toi gioi han so khach hang\n");
                                    break;
                                } else {
                                    clearBuffer();
                                    KhachHang khachMoi;
                                    nhapThongTinKhach(&khachMoi);

                                    for(int i = 0; i < soKhachHang; i++) {
                                        if(coNhuNhauKhachHang(khachMoi, danhSachKhachHang[i]) == 1) {   // MARK: LAP_MANG
                                            printf("Khach hang da co trong mang\n");
                                            break;
                                        }
                                    }

                                    themKhachHang(danhSachKhachHang, &soKhachHang, khachMoi);   //MARK: LAP_FILE
                                    printf("Khach hang da duoc them vao mang\n");
                                }
                            } else if(luaChonThem == 2) {                        
                                docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);    //MARK: RETURN
                                int soKhachHangFile = kiemTraSoKhachHang(fileQuanLiChung);
                                KhachHang* danhSachKhachHangFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachHangFile);
                                if(!danhSachKhachHangFile) {
                                    printf("Khong the khoi tao mang dong de them khach hang\n");
                                    break;
                                }
                                docFileKhachHang(fileQuanLiChung, soKhachHangFile, danhSachKhachHangFile);

                                clearBuffer();
                                KhachHang khachMoi;
                                nhapThongTinKhach(&khachMoi);

                                // Kiem tra xem khach hang da co trong file chua
                                for(int i = 0; i < soKhachHangFile; i++) {
                                    if(coNhuNhauKhachHang(danhSachKhachHangFile[i], khachMoi) == 1) {
                                        printf("Khach hang da co trong file\n");
                                        free(danhSachKhachHangFile);        //MARK: LAP_FILE
                                        break;
                                    }
                                }

                                themKhachHangVaoFile(khachMoi, fileQuanLiChung);
                                free(danhSachKhachHangFile);
                                printf("Khach hang da duoc them vao file\n");
                            }

                            break;
                        }
                        case 4: {
                            while(getchar() != '\n');
                            int luaChonXoaBo;

                            printf("Xoa khach hang trong mang (1) hay xoa khach hang trong file (2) ");
                            saferScanf("%d", &luaChonXoaBo);

                            if(luaChonXoaBo != 1 && luaChonXoaBo != 2) {
                                printf("Lua chon khong hop le\n");
                                clearBuffer();
                                break;
                            }

                            clearBuffer();
                            KhachHang khachXoa;     //MARK: CHUAN_HOA
                            nhapThongTinKhach(&khachXoa);

                            if(luaChonXoaBo == 1) {
                                xoaKhachHang(danhSachKhachHang, &soKhachHang, khachXoa);
                            } else {
                                docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                                xoaKhachKhoiFile(khachXoa, fileQuanLiChung);
                            }

                            break;
                        }
                        case 5: {
                            while(getchar() != '\n');
                            int luaChonCapNhat;

                            printf("Cap nhat thong tin tu file vao mang (1) hay tu mang vao file (2) ");
                            saferScanf(" %d", &luaChonCapNhat);

                            if(luaChonCapNhat != 1 && luaChonCapNhat != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }

                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            int soKhachHangFile = kiemTraSoKhachHang(fileQuanLiChung);

                            if(luaChonCapNhat == 1 && soKhachHangFile == 0) {
                                printf("File chua co khach hang\n");
                                break;
                            } else if(luaChonCapNhat == 2 && soKhachHang == 0) {
                                printf("Mang khong co khach hang\n");
                                break;
                            }

                            KhachHang* danhSachKhachHangFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachHangFile);
                            if(!danhSachKhachHangFile) {
                                printf("Khong the khoi tao mang dong de cap nhat khach hang\n");
                                break;
                            }
                            docFileKhachHang(fileQuanLiChung, soKhachHangFile, danhSachKhachHangFile);

                            if(luaChonCapNhat == 1) {
                                int coMat = 0;
                                for (int i = 0; i < soKhachHangFile; i++) {
                                    coMat = 0;
                                    if (soKhachHang >= MAX_KHACH_HANG) {
                                        printf("Mang da day\n");
                                        break;
                                    }

                                    for(int j = 0; j < soKhachHang; j++) {
                                        if(coNhuNhauKhachHang(danhSachKhachHangFile[i], danhSachKhachHang[j]) == 1) {
                                            coMat = 1;
                                            break;
                                        }
                                    }

                                    if(coMat == 0) {
                                        saoChepKhachHang(&danhSachKhachHang[soKhachHang], &danhSachKhachHangFile[i]);
                                        soKhachHang++;
                                    }
                                }
                                printf("Mang khach hang da duoc cap nhat\n");
                            } else {
                                for(int i = 0; i < soKhachHang; i++) {
                                    int coMatTrongFile = 0; // 1 neu khach da co trong file; 0 neu khong co mat
                                    for(int j = 0; j < soKhachHangFile; j++) {
                                        coMatTrongFile = coNhuNhauKhachHang(danhSachKhachHang[i], danhSachKhachHangFile[j]);    //MARK: LAP_FILE
                                        if(coMatTrongFile == 1) {
                                            coMatTrongFile = 1;
                                            break;
                                        }
                                    }
                                    if(coMatTrongFile == 0) {
                                        themKhachHangVaoFile(danhSachKhachHang[i], fileQuanLiChung);    //MARK: FILE_MANG
                                    }
                                }
                                printf("File khach hang da duoc cap nhat\n");
                            }
                            free(danhSachKhachHangFile);

                            break;
                        }
                        case 6: {
                            while(getchar() != '\n');
                            int canhCao;
                            printf("CANH BAO: VIEC NAY SE XOA TOAN BO DU LIEU CUA BAN VA KHONG THE BI DAO NGUOC. TIEP TUC? (1) ");
                            saferScanf("%d", &canhCao);
                            if(canhCao != 1) {
                                clearBuffer();
                                break;
                            }

                            int luaChonXoa;
                            printf("Xoa du lieu mang khach hang hien tai (1) hay xoa du lieu file khach hang (2) ");
                            scanf(" %d", &luaChonXoa);
                            
                            if(luaChonXoa != 1 && luaChonXoa != 2) {
                                clearBuffer();
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonXoa == 1) {
                                soKhachHang = 0;
                                printf("Mang khach hang da duoc reset\n");
                            } else {
                                docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                                FILE* fptr = fopen(fileQuanLiChung, "w");
                                if(!fptr) {
                                    perror("Xoa du lieu that bai");
                                    break;
                                }

                                // Viet lai header vao file
                                fprintf(fptr, KHACH_HANG_HEADER);

                                fclose(fptr);
                                printf("Xoa du lieu file thanh cong!\n");
                            }

                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long chon lai.\n");
                            clearBuffer();
                    }
                } while (luaChonCon != 7);
                break;
            case 5:
                do {
                    printf("\n--- MENU QUAN LY KHO NGUYEN LIEU ---\n");
                    printf("1. Xem kho nguyen lieu\n");
                    printf("2. Tim kiem nguyen lieu\n");
                    printf("3. Them nguyen lieu\n");
                    printf("4. Xoa nguyen lieu\n");
                    printf("5. Cap nhat file nguyen lieu\n");
                    printf("6. Xoa du lieu kho\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");

                    scanf("%d", &luaChonCon); 
            
                    switch (luaChonCon) {
                        case 1: {
                            while(getchar() != '\n');
                            int luaChonXem;
                            printf("Xem kho hien tai (1) hay xem kho tu file (2): ");
                            scanf(" %d", &luaChonXem);
                            clearBuffer();

                            if(luaChonXem != 1 && luaChonXem != 2) {
                                printf("Lua chon khong hop le\n");
                            } else if(luaChonXem == 1) {
                                hienThiKho(khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);
                            } else if(luaChonXem == 2) {
                                docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                                int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);

                                // Tap mot mang dong de hung gia tri doc duoc tu file.
                                // Su dung mang dong thay cho mang thuong de toi uu bo nho
                                NguyenLieu* khoFile = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soNguyenLieuFile);
                                if(!khoFile) {
                                    printf("Khong the khoi tao mang dong de xem kho\n");
                                    break;
                                }
                                docFileKho(fileQuanLiChung, soNguyenLieuFile, khoFile);
                                hienThiKho(khoFile, soNguyenLieuFile);
                                free(khoFile);
                            }
                            break;
                        }
                        case 2: {
                            while(getchar() != '\n');
                            int luaChonTimKiem;
                            printf("Tim kiem nguyen lieu trong kho hien tai (1) hay tim kiem nguyen lieu trong file (2): ");
                            scanf(" %d", &luaChonTimKiem);
                            clearBuffer();

                            if(luaChonTimKiem != 1 && luaChonTimKiem != 2) {
                                printf("Lua chon khong hop le\n");
                            }
                            if(luaChonTimKiem == 1) {
                                timKiemNguyenLieu(khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);
                            } else if(luaChonTimKiem == 2) {
                                docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                                int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                                NguyenLieu* khoFile = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soNguyenLieuFile);
                                if(!khoFile) {
                                    printf("Khong the khoi tao mang dong de tim kiem nguyen lieu\n");
                                    break;
                                }
                                docFileKho(fileQuanLiChung, soNguyenLieuFile, khoFile);
                                timKiemNguyenLieu(khoFile, soNguyenLieuFile);
                                free(khoFile);
                            }
                            break;
                        }
                        case 3: {
                            while(getchar() != '\n');
                            int luaChonThem;
                            printf("Them nguyen lieu vao mang kho hien tai (1) hay them nguyen lieu vao file (2): ");
                            scanf(" %d", &luaChonThem);
                            clearBuffer();

                            if(luaChonThem != 1 && luaChonThem != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonThem == 1) {
                                if(soLuongNguyenLieuSuDung >= MAX_NGUYEN_LIEU) {
                                    printf("Da day, khong the them nguyen lieu\n");
                                    break;
                                }
                                NguyenLieu nguyenLieuMoi;
                                nhapThongTinNguyenLieu(&nguyenLieuMoi);
                                int thoat = 0;
                                for(int i = 0; i < soLuongNguyenLieuSuDung; i++) {
                                    if(strcmp(khoNguyenLieuSuDung[i].tenNguyenLieu, nguyenLieuMoi.tenNguyenLieu) == 0) {
                                        printf("Nguyen lieu da co trong kho\n");
                                        thoat = 1;
                                        break;
                                    }
                                }
                                if(thoat == 1) {
                                    break;
                                }
                                saoChepNguyenLieu(&khoNguyenLieuSuDung[soLuongNguyenLieuSuDung], &nguyenLieuMoi);
                                soLuongNguyenLieuSuDung++;
                            } else if(luaChonThem == 2) {
                                docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                                int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                                if(soNguyenLieuFile >= MAX_NGUYEN_LIEU) {   // De dam bao tinh dong nhat, file kho cung khong the chua qua MAX_NGUYEN_LIEU nguyen lieu
                                    printf("Da day, khong the cho nguyen lieu vao file\n");
                                    break;
                                }
                                NguyenLieu* khoFile = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soNguyenLieuFile);
                                if(!khoFile) {
                                    printf("Khong the khoi tao mang dong de them them nguyen lieu\n");
                                    break;
                                }
                                docFileKho(fileQuanLiChung, soNguyenLieuFile, khoFile);
                
                                NguyenLieu nguyenLieuMoi;
                                nhapThongTinNguyenLieu(&nguyenLieuMoi);

                                // Kiem tra xem nguyen lieu da co trong file chua
                                int thoat = 0;
                                for(int i = 0; i < soNguyenLieuFile; i++) {
                                    if(strcmp(khoFile[i].tenNguyenLieu, nguyenLieuMoi.tenNguyenLieu) == 0) {
                                        printf("Nguyen lieu da co trong file\n");
                                        free(khoFile);
                                        thoat = 1;
                                        break;
                                    }
                                }
                                if(thoat == 1) {
                                    break;
                                }

                                themNguyenLieuVaoFile(nguyenLieuMoi, fileQuanLiChung);
                                free(khoFile);
                            }
                            printf("Nguyen lieu da duoc them vao file\n");
                            break;
                        }    
                        case 4: {
                            while(getchar() != '\n');
                            int luaChonXoaBo;

                            printf("Xoa nguyen lieu trong mang hien tai (1) hay xoa nguyen lieu trong file kho (2) ");
                            scanf(" %d", &luaChonXoaBo);
                            clearBuffer();

                            if(luaChonXoaBo != 1 && luaChonXoaBo != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }

                            char tenNguyenLieuXoa[MAX_DO_DAI_TEN_NGUYEN_LIEU];
                            printf("Ten nguyen lieu xoa: ");
                            fgets(tenNguyenLieuXoa, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);     //MARK: STR_PRO
                            tenNguyenLieuXoa[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
                            tenNguyenLieuXoa[strcspn(tenNguyenLieuXoa, "\n")] = '\0';
                            
                            if(luaChonXoaBo == 1) {
                                xoaNguyenLieu(khoNguyenLieuSuDung, &soLuongNguyenLieuSuDung, tenNguyenLieuXoa);
                            } else {
                                docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                                xoaNguyenLieuKhoiFile(tenNguyenLieuXoa, fileQuanLiChung);
                            }

                            break;
                        }
                        case 5: {
                            while(getchar() != '\n');
                            int luaChonCapNhat;

                            printf("Cap nhat thong tin tu file vao mang (1) hay tu mang vao file (2) ");
                            scanf(" %d", &luaChonCapNhat);
                            clearBuffer();

                            if(luaChonCapNhat != 1 && luaChonCapNhat != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }
                            
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            NguyenLieu* khoFile = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soNguyenLieuFile);
                            if(!khoFile) {
                                printf("Khong the khoi tao mang dong de cap nhat nguyen lieu\n");
                                break;
                            }
                            docFileKho(fileQuanLiChung, soNguyenLieuFile, khoFile);

                            if(luaChonCapNhat == 1) {
                                // Them nguyen lieu tu file vao mang dam bao dieu kien khong bi lap va khong vuot qua so nguyen lieu cho phep
                                // Cac nguyen lieu cu khong bi xoa bo. Tuy nhien, nguyen lieu cung ten nhung khac gia tri vx co the duoc update                   
                                int coMat = 0;
                                for (int i = 0; i < soNguyenLieuFile; i++) {
                                    coMat = 0;
                                    if (soLuongNguyenLieuSuDung >= MAX_NGUYEN_LIEU) {
                                        printf("Mang da day\n");
                                        break;
                                    }

                                    for(int j = 0; j < soLuongNguyenLieuSuDung; j++) {
                                        if(strcmp(khoFile[i].tenNguyenLieu, khoNguyenLieuSuDung[j].tenNguyenLieu) == 0) {
                                            // Cap nhat du lieu cho nguyen lieu cung ten nhung khac thuoc tinh
                                            // Khong tang so nguyen lieu
                                            saoChepNguyenLieu(&khoNguyenLieuSuDung[j], &khoFile[i]); 
                                            coMat = 1;
                                            break;
                                        }
                                    }

                                    if(coMat == 0) {
                                        saoChepNguyenLieu(&khoNguyenLieuSuDung[soLuongNguyenLieuSuDung], &khoFile[i]);
                                        soLuongNguyenLieuSuDung++;
                                    }
                                }
                            } else if(luaChonCapNhat == 2) {
                                // Tranh lap. Nguyen lieu trong file trung ten voi trong mang nhung thuoc tinh khac thi thuoc tinh cua nguyen lieu file se duoc cap nhat
                                // File bi gioi han so luong nguyen lieu ve MAX_NGUYEN_LIEU de dam bao dong nhat. Dieu nay khac voi file hoa don va khach hang
                                int coMat = 0;
                                NguyenLieu khoMoi[MAX_NGUYEN_LIEU]; // Chu y khong the dung mang dong o tren de hung nguyen lieu moi duoc do size co the se it hon so nguyen lieu hien co trong mang
                                chuanHoaKho(khoMoi, MAX_NGUYEN_LIEU);
                                for (int i = 0; i < soLuongNguyenLieuSuDung; i++) {
                                    coMat = 0;
                                    if (soNguyenLieuFile >= MAX_NGUYEN_LIEU) {
                                        printf("File da day\n");
                                        break;
                                    }

                                    for(int j = 0; j < soNguyenLieuFile; j++) {
                                        if(strcmp(khoFile[j].tenNguyenLieu, khoNguyenLieuSuDung[i].tenNguyenLieu) == 0) {
                                            // Cap nhat du lieu cho nguyen lieu cung ten nhung khac thuoc tinh
                                            // Khong tang so nguyen lieu
                                            saoChepNguyenLieu(&khoMoi[j], &khoNguyenLieuSuDung[i]);
                                            coMat = 1;
                                            break;
                                        }
                                    }

                                    if(coMat == 0) {
                                        saoChepNguyenLieu(&khoMoi[soNguyenLieuFile], &khoNguyenLieuSuDung[i]);
                                        soNguyenLieuFile++;
                                    }
                                }
                                // Cap nhat du lieu vao lai file
                                // Don sach thong tin cu cua kho
                                FILE* fptr = fopen(fileQuanLiChung, "w");
                                if(!fptr) {
                                    perror("Khong the mo file de cap nhat thong tin");
                                    break;
                                }
                                fprintf(fptr, KHO_HEADER);
                                fclose(fptr); // Dong file de tranh xung dot khi them nguyen lieu ben duoi
                                themNhieuNguyenLieuVaoFile(khoMoi, soNguyenLieuFile, fileQuanLiChung);
                            }
                            free(khoFile);
                            printf("Cap nhat du lieu thanh cong\n");
                            break;
                        }   
                        case 6: {
                            while(getchar() != '\n');
                            int canhCao;
                            printf("CANH BAO: VIEC NAY SE XOA TOAN BO DU LIEU CUA BAN VA KHONG THE BI DAO NGUOC. TIEP TUC? (1) ");
                            scanf(" %d", &canhCao);
                            if(canhCao != 1) {
                                break;
                            }

                            int luaChonXoa;
                            printf("Xoa du lieu kho hien tai (1) hay xoa du lieu file kho (2) ");
                            scanf(" %d", &luaChonXoa);
                            clearBuffer();
                            
                            if(luaChonXoa != 1 && luaChonXoa != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            } else if(luaChonXoa == 1) {
                                // memset(khoNguyenLieuSuDung, 0, sizeof(khoNguyenLieuSuDung)); // LIABILITY ###########################################################
                                soLuongNguyenLieuSuDung = 0;
                                printf("Mang kho da duoc reset\n");
                            } else {
                                docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                                FILE* fptr = fopen(fileQuanLiChung, "w");
                                if(!fptr) {
                                    perror("Xoa du lieu that bai");
                                    break;
                                }

                                // Viet lai header vao file
                                fprintf(fptr, KHO_HEADER);

                                fclose(fptr);
                                printf("Xoa du lieu file thanh cong!\n");
                            }
                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le, vui long chon lai\n");
                            clearBuffer();
                    }
                } while (luaChonCon != 7);
                break; 
            case 6: // Thong ke du lieu trong file. Profit se duoc tinh su dung ca tien thua
                do {
                    printf("\n--- Thong ke ---\n");
                    printf("1. Thong ke trong nam\n");
                    printf("2. Thong ke trong thang\n");
                    printf("3. Quay lai\n");
                    printf("Nhap lua chon: ");
                    scanf("%d", &luaChonCon);

                    switch (luaChonCon){
                        case 1: {
                            while(getchar() != '\n');

                            int namThongKe;
                            printf("Nhap nam thong ke: ");
                            saferScanf("%d", &namThongKe);

                            if(namThongKe < 0) {
                                printf("Nam khong the am\n");
                                break;
                            }

                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                            
                            // Kiem tra xem bo nho co duoc cap phat chua
                            if(!danhSachHoaDonFile) {
                                printf("Khong the khoi tao mang dong de thong ke hoa don theo nam");
                                break;
                            }

                            docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);

                            float tongTienQ1 = 0, chiPhiQ1 = 0;
                            float tongTienQ2 = 0, chiPhiQ2 = 0;
                            float tongTienQ3 = 0, chiPhiQ3 = 0;
                            float tongTienQ4 = 0, chiPhiQ4 = 0;
                            int soDonQ1 = 0, soDonQ2 = 0, soDonQ3 = 0, soDonQ4 = 0;
                            int tonTaiNam = 0; // Flag danh dau xem input nam co nam trong file khong

                            for(int i = 0; i < soHoaDonFile; i++) {
                                if(danhSachHoaDonFile[i].ngayNhapDon.nam == namThongKe) {
                                    tonTaiNam = 1;
                                    if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 1 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 3) {
                                        tongTienQ1 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ1 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ1++;
                                    } else if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 4 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 6) {
                                        tongTienQ2 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ2 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ2++;
                                    } else if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 7 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 9) {
                                        tongTienQ3 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ3 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ3++;
                                    } else if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 10 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 12) {
                                        tongTienQ4 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ4 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ4++;
                                    }
                                }
                            }

                            if(tonTaiNam == 0) {
                                printf("Khong ton tai nam %d trong he thong\n", namThongKe);
                                break;
                            }

                            printf("\n--- Nam %d ---\n", namThongKe);
                            printf("Quy 1 co %d don hang, tong loi nhuan: %.2f\n", soDonQ1, tongTienQ1 - chiPhiQ1);
                            printf("Quy 2 co %d don hang, tong loi nhuan: %.2f\n", soDonQ2, tongTienQ2 - chiPhiQ2);
                            printf("Quy 3 co %d don hang, tong loi nhuan: %.2f\n", soDonQ3, tongTienQ3 - chiPhiQ3);
                            printf("Quy 4 co %d don hang, tong loi nhuan: %.2f\n", soDonQ4, tongTienQ4 - chiPhiQ4);
                            printf("Nam %d co %d don hang, tong thu nhap: %.2f\n", namThongKe, soDonQ1 + soDonQ2 + soDonQ3 + soDonQ4,
                                        tongTienQ1 - chiPhiQ1 + tongTienQ2 - chiPhiQ2 + tongTienQ3 - chiPhiQ3 + tongTienQ4 - chiPhiQ4);

                            free(danhSachHoaDonFile);

                            break;
                        }
                        case 2: {
                            while(getchar() != '\n');

                            int namThongKe, thangThongKe;
                            printf("Nhap nam thong ke: ");
                            saferScanf("%d", &namThongKe);
                            printf("Nhap thang thong ke: ");
                            saferScanf("%d", &thangThongKe);

                            if(namThongKe < 0 || thangThongKe < 0) {
                                printf("Nam va thang khong the am\n");
                                break;
                            }

                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                            
                            // Kiem tra xem bo nho co duoc cap phat chua
                            if(!danhSachHoaDonFile) {
                                printf("Khong the khoi tao mang dong de thong ke hoa don theo thang");
                                break;
                            }

                            docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);

                            float tongTienThongKe = 0, tienNguyenLieuThongKe = 0;
                            int soHoaDonThongKe = 0;
                            int tonTaiThoiDiem = 0; // Kiem tra xem file co luu hoa don cua thang, nam do khong

                            for(int i = 0; i < soHoaDonFile; i++) {
                                if(danhSachHoaDonFile[i].ngayNhapDon.nam == namThongKe && danhSachHoaDonFile[i].ngayNhapDon.thang == thangThongKe) {
                                    tonTaiThoiDiem = 1;
                                    tongTienThongKe += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                    tienNguyenLieuThongKe += danhSachHoaDonFile[i].tienNguyenLieu;
                                    soHoaDonThongKe++;
                                }
                            }

                            if(tonTaiThoiDiem == 0) {
                                printf("Khong ton tai hoa don thang %d nam %d trong file\n", thangThongKe, namThongKe);
                                break;
                            }
                            printf("\n--- Thong ke thang %d nam %d ---\n", thangThongKe, namThongKe);
                            printf("Tong thu nhap: %.2f\n", tongTienThongKe - tienNguyenLieuThongKe);
                            printf("So hoa don: %d\n", soHoaDonThongKe);

                            free(danhSachHoaDonFile);

                            break;
                        }
                        case 3:
                            break;
                        default:
                            printf("Lua chon khong hop le, vui long chon lai\n");
                            clearBuffer();
                    }
                } while(luaChonCon != 3);
                break;
            case 7:
                do {
                    printf("\n--- FILE ---\n");
                    printf("1. File khach hang\n");
                    printf("2. File hoa don\n");
                    printf("3. File kho\n");
                    printf("4. File menu\n");
                    printf("5. Reset file quan li\n");
                    printf("6. Quay lai\n");
                    printf("Nhap lua chon: ");
                    scanf("%d", &luaChonCon);

                    if(luaChonCon == 5) {
                        FILE* quanLiFptr = fopen(MANAGING_FILE, "w");
                        if(quanLiFptr) {
                            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                                fprintf(quanLiFptr, PLACEHOLDER_QUAN_LY);
                            }
                            fclose(quanLiFptr);
                            printf("Reset file thanh cong\n");
                        } else {
                            perror("Khong the reset file quan ly");
                        }
                    } else if(luaChonCon == 1 || luaChonCon == 2 || luaChonCon == 3 || luaChonCon == 4) {
                        do {
                            printf("\n--- Hanh dong ---\n");
                            printf("1. Xoa file\n");
                            printf("2. Tao file\n");
                            printf("3. Di chuyen file\n");
                            printf("4. Xem duong dan hien tai\n");
                            printf("5. Chon file\n");
                            printf("6. Quay lai\n");
                            printf("Nhap lua chon: ");
                            scanf(" %d", &luaChonCon2);
                    
                            switch (luaChonCon2) {
                                case 1: { // Use "{}" for better scoping
                                    // Xoa file
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    int ketQuaXoa = remove(fileQuanLiChung);
                                    if(ketQuaXoa != 0) {
                                        perror("Xoa file that bai");
                                        break;
                                    }
                                    printf("File da duoc xoa!\n");

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, "");
                                    break;
                                }
                                case 2: {
                                    while (getchar() != '\n');
                                    // Tao file moi
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    printf("Nhap duong dan moi: ");
                                    fgets(duongDanMoi, MAX_FILE_PATH_LENGTH - 1, stdin);
                                    duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';
                                    duongDanMoi[MAX_FILE_PATH_LENGTH - 1] = '\0';

                                    FILE* fptr = fopen(duongDanMoi, "w");
                                    if(!fptr) {
                                        printf("Loi khi tao file!\n");
                                        break;
                                    }
                                    // Khoi tao header
                                    switch (luaChonCon) {
                                        case LUA_CHON_KHACH_HANG:
                                            fprintf(fptr, KHACH_HANG_HEADER);
                                            break;
                                        case LUA_CHON_HOA_DON:
                                            fprintf(fptr, HOA_DON_HEADER);
                                            break;
                                        case LUA_CHON_KHO:
                                            fprintf(fptr, KHO_HEADER);
                                            break;
                                        case LUA_CHON_MENU:
                                            fprintf(fptr, MENU_HEADER);
                                        default:
                                            break;
                                            clearBuffer();
                                    }

                                    printf("File duoc tao thanh cong!\n");
                                    fclose(fptr);

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    break;
                                }
                                case 3: {
                                    while (getchar() != '\n');
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    printf("Nhap dia chi moi: ");
                                    fgets(duongDanMoi, MAX_FILE_PATH_LENGTH - 1, stdin);
                                    duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';
                                    duongDanMoi[MAX_FILE_PATH_LENGTH - 1] = '\0';

                                    docFileQuanLi(luaChonCon, fileQuanLiChung);

                                    if(strncmp(duongDanMoi, fileQuanLiChung, MAX_FILE_PATH_LENGTH) == 0) {
                                        printf("Duong dan moi khong the giong duong dan cu!\n");
                                        break;
                                    }
                                    
                                    // Tao file o dia chi moi
                                    FILE* fptrDich = fopen(duongDanMoi, "w");
                                    if(!fptrDich) {
                                        perror("Loi khi tao file o dia chi moi");
                                        break;
                                    }

                                    // Sao chep du lieu sang file moi
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    FILE* fptrNguon = fopen(fileQuanLiChung, "r");
                                    if(!fptrNguon) {
                                        perror("Khong the mo file cu de chuyen du lieu");
                                        break;
                                    }
                                    char dongDuLieu[MAX_DONG_DU_LIEU];
                                    while(fgets(dongDuLieu, MAX_DONG_DU_LIEU - 1, fptrNguon)) {
                                        dongDuLieu[MAX_DONG_DU_LIEU - 1] = '\0';
                                        fprintf(fptrDich, "%s", dongDuLieu);
                                    }
                                    fclose(fptrNguon);
                                    fclose(fptrDich);

                                    // Xoa file du lieu cu
                                    if(remove(fileQuanLiChung) != 0) {
                                        perror("File du lieu nguon chua duoc xoa");
                                    }

                                    // Cap nhat duong dan moi cuar file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    printf("File da duoc cap nhat thanh cong\n");
                                    break;
                                }
                                case 4: {
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    printf("Duong dan hien tai: %s\n", fileQuanLiChung);
                                    break;
                                }
                                case 5: {
                                    // Chuong trinh chi co the lam viec voi du lieu cua mot file cho moi loai doi tuong tai mot thoi diem
                                    // Lay duong dan cua mot file du lieu
                                    printf("CANH BAO: HAY DAM BAO FILE DUOC HUONG TOI LA FILE DU LIEU DUNG LOAI VA DUNG CU PHAP!!!!\n");
                                    while (getchar() != '\n');
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    printf("Nhap dia chi moi: ");
                                    fgets(duongDanMoi, MAX_FILE_PATH_LENGTH - 1, stdin);
                                    duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';
                                    duongDanMoi[MAX_FILE_PATH_LENGTH - 1] = '\0';

                                    // Kiem tra xem dia chi co ton tai khong
                                    FILE* fptr = fopen(duongDanMoi, "r");
                                    if(!fptr) {
                                        perror("Khong the su dung file");
                                        break;
                                    }

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    break;
                                }
                                case 6:
                                    break;
                                default:
                                    printf("Lua chon khong hop le. Vui long chon lai.\n");
                                    clearBuffer();
                            }             
                        } while (luaChonCon2 != 6);
                    } else if(luaChonCon != 6) {
                        printf("Lua chon khong hop le. Vui long chon lai!\n");
                    }

                    clearBuffer();
                } while(luaChonCon != 6);
                break;
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                // Khi dien mot ky tu, neu do khong la mo so nguyen (vd: 2.3, "auhd"), cac ky tu invalid do se tiep tu bi ket trong buffer,
                // khien cho vong lap bi loi lien tuc. Do vay, ta can don sach buffer truoc
                clearBuffer();
        }
    } while (luaChon != 8);

    if(canFreeKhoNguyenLieu == 1) {
        free(khoNguyenLieuSuDung);
    }

    if(canFreeMenu == 1) {
        free(menuSuDung);
    }
    
    return 0;
}

// Hàm thêm khách hàng vào danh sách
void themKhachHang(KhachHang danhSachKhachHang[], int *soKhachHang, KhachHang khachHangMoi) {
    danhSachKhachHang[*soKhachHang] = khachHangMoi;
    (*soKhachHang)++;
}

void timKiemKhachHang(KhachHang danhSachKhachHang[], int soKhachHang) {
    if(soKhachHang == 0) {
        printf("Chua co khach hang\n");
        return;
    }

    int luaChon;
    char keyword[50];

    printf("\nChon phuong thuc tim kiem:\n");
    printf("1. Tim theo ten\n");
    printf("2. Tim theo so dien thoai\n");
    printf("Nhap lua chon: ");
    scanf("%d", &luaChon);
    clearBuffer();

    if(luaChon != 1 && luaChon != 2) {
        printf("Lua chon khong hop le\n");
    } else if (luaChon == 1) {
        printf("Nhap ten khach hang: ");
        getchar();  // Đọc ký tự newline
        fgets(keyword, sizeof(keyword) - 1, stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline
        keyword[sizeof(keyword) - 1] = '\0';

        printf("\nDanh sach khach hang tim duoc theo ten '%s':\n", keyword);
        for (int i = 0; i < soKhachHang; i++) {
            if (strstr(danhSachKhachHang[i].tenKhachHang, keyword) != NULL) {
                printf("%d. %s - %s - %d\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
            }
        }
    } else if (luaChon == 2) {
        printf("Nhap so dien thoai khach hang: ");
        getchar();  // Đọc ký tự newline
        fgets(keyword, sizeof(keyword) - 1, stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline
        keyword[sizeof(keyword) - 1] = '\0';

        printf("\nDanh sach khach hang tim duoc theo so dien thoai '%s':\n", keyword);
        for (int i = 0; i < soKhachHang; i++) {
            if (strstr(danhSachKhachHang[i].soDienThoai, keyword) != NULL) {
                printf("%d. %s - %s - %d\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
            }
        }
    }
}

// Ham xem khach hang
void xemDanhSachKhachHang(KhachHang danhSachKhachHang[], int soKhachHang) {
    if(soKhachHang == 0) {
        printf("Chua co khach hang\n");
        return;
    }
    for (int i = 0; i < soKhachHang; i++) {
        printf("%d. %s - %s - %d\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
    }
}

void xoaKhachHang(KhachHang danhSachKhach[], int* soLuong, KhachHang khachXoa) {
    if(*soLuong == 0) {
        printf("Chua co khach hang\n");
        return;
    }
    
    for(int i = 0; i < *soLuong; i++) {
        if(coNhuNhauKhachHang(danhSachKhachHang[i], khachXoa) == 1) {
            // Xoa khach hang bang cach di chuyen cac khach hang con lai
            for(int j = i; j < *soLuong - 1; j++) {
                danhSachKhachHang[j] = danhSachKhachHang[j + 1];
            }
            printf("Khach hang da duoc xoa\n");
            (*soLuong)--;
            return;
        }
    }
    printf("Khong tim thay khach hang\n");
}

// Ham nhap thong tin khach
void nhapThongTinKhach(KhachHang* khachHang) {
    chuanHoaKhachHang(khachHang, 1);

    printf("Nhap ten khach hang: ");
    fgets(khachHang->tenKhachHang, DO_DAI_TEN_KHACH - 1, stdin);
    printf("Nhap so dien thoai khach hang: ");
    fgets(khachHang->soDienThoai, DO_DAI_SO_DIEN_THOAI - 1, stdin);
    printf("Nhap so diem tich luy khach hang: ");
    saferScanf("%f", khachHang->diemTichLuy);

    // Khu newline cho cac input
    khachHang->tenKhachHang[strcspn(khachHang->tenKhachHang, "\n")] = '\0';
    khachHang->soDienThoai[strcspn(khachHang->soDienThoai, "\n")] = '\0';

    // Khu null cho cac input
    khachHang->tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
    khachHang->soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
}

// Hàm hiển thị menu
void hienThiMenu(MonAn menu[], int soMon) {
    printf("\nDanh sach mon an:\n");
    for (int i = 0; i < soMon; i++) {
        printf("%d. %s - Gia: %.2f\n", i + 1, menu[i].tenMon, menu[i].gia);
    }
}

// Hàm xóa món
void xoaMonAn(MonAn menu[], int* soMonAn, char tenMonXoa[]) {
    if(*soMonAn == 0) {
        return;
    }

    for(int i = 0; i < *soMonAn; i++) {
        if(strcmp(menu[i].tenMon, tenMonXoa) == 0) {       //MARK: LAP_MANG
            for(int j = i; j < (*soMonAn) - 1; j++) {
                menu[j] = menu[j + 1];
            }
            printf("Mon an da duoc xoa\n");
            (*soMonAn)--;
            return;
        }
    }
    printf("Khong tim thay mon an\n");
}

void nhapThongTinMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho) {
    // Su dung de khai bao thong tin cho mot mon an moi
    // Su dung trong themMon va suaMon
    printf("\nNhap ten mon moi: ");
    fgets(monAn->tenMon, sizeof(monAn->tenMon) - 1, stdin);
    monAn->tenMon[strcspn(monAn->tenMon, "\n")] = '\0'; // Loại bỏ ký tự newline
    monAn->tenMon[sizeof(monAn->tenMon) - 1] = '\0';
    printf("Nhap gia mon moi: ");
    saferScanf("%f", &monAn->gia);

    do {
        printf("Luu y: so nguyen lieu mot mon phai duong va khong the qua %d\n", soNguyenLieuKho);
        printf("Nhap so nguyen lieu mon mon: ");
        saferScanf("%d", &monAn->soNguyenLieu);
    } while(monAn->soNguyenLieu <= 0 || monAn->soNguyenLieu > soNguyenLieuKho);

    int i = 0;
    while(i < monAn->soNguyenLieu) {        //MARK: THEM_MON
        hienThiKho(kho, soNguyenLieuKho);
        printf("Nhap ten nguyen lieu: ");
        fgets(monAn->nguyenLieu[i].tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
        monAn->nguyenLieu[i].tenNguyenLieu[strcspn(monAn->nguyenLieu[i].tenNguyenLieu, "\n")] = '\0';   //MARK: STR_PRO
        monAn->nguyenLieu[i].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';

        for(int j = 0; j < soNguyenLieuKho; j++) {
            if(strcmp(monAn->nguyenLieu[i].tenNguyenLieu, kho[j].tenNguyenLieu) == 0) {
                do {
                    printf("So luong phai duong va khong qua %.2f %s\n", kho[j].soLuong, kho[j].donVi);
                    printf("Nhap so luong cho nguyen lieu nay: ");
                    saferScanf("%f", &monAn->nguyenLieu[i].soLuong);
                } while(monAn->nguyenLieu[i].soLuong <= 0 && monAn->nguyenLieu[i].soLuong > kho[j].soLuong);

                monAn->nguyenLieu[i].gia = kho[j].gia;
                strncpy(monAn->nguyenLieu[i].donVi, kho[j].donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
                monAn->nguyenLieu[i].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';         //MARK: STR_PRO

                i++;
                break;
            }
        }
    }
}

// Hàm thanh toán
void thanhToan(MonAn menu[], int soMon, HoaDon danhSachHoaDon[], int *soHoaDon,
                KhachHang danhSachKhachHang[], int *soKhachHang, NguyenLieu kho[], int soNguyenLieuKho) {
    int soLuong, chonMon;
    HoaDon hoaDon; 
    chuanHoaHoaDon(&hoaDon, 1);
    printf("\nNhap thong tin khach hang:\n");
    printf("Nhap ten khach hang: ");
    // getchar();  // Đọc ký tự newline
    fgets(hoaDon.khachHang.tenKhachHang, sizeof(hoaDon.khachHang.tenKhachHang) - 1, stdin); //MARK: STR_PRO
    hoaDon.khachHang.tenKhachHang[strcspn(hoaDon.khachHang.tenKhachHang, "\n")] = '\0'; // Loại bỏ ký tự newline
    hoaDon.khachHang.tenKhachHang[sizeof(hoaDon.khachHang.tenKhachHang) - 1] = '\0';

    printf("Nhap so dien thoai khach hang: ");
    fgets(hoaDon.khachHang.soDienThoai, sizeof(hoaDon.khachHang.soDienThoai) - 1, stdin);   //MARK: STR_PRO
    hoaDon.khachHang.soDienThoai[strcspn(hoaDon.khachHang.soDienThoai, "\n")] = '\0'; // Loại bỏ ký tự newline
    hoaDon.khachHang.soDienThoai[sizeof(hoaDon.khachHang.soDienThoai) - 1] = '\0';

    printf("Nhap ngay: ");
    scanf(" %d", &hoaDon.ngayNhapDon.ngay);
    printf("Nhap thang: ");
    scanf(" %d", &hoaDon.ngayNhapDon.thang);
    printf("Nhap nam: ");
    scanf(" %d", &hoaDon.ngayNhapDon.nam);

    printf("\nChon mon va so luong mon:\n");
    hoaDon.soMonGoi = 0;
    hoaDon.tongTien = 0;
    while (1) {
        hienThiMenu(menu, soMon);
        printf("Nhap so mon (0 de ket thuc): ");
        scanf(" %d", &chonMon);

        if (chonMon == 0) break;
        
        if (chonMon < 1 || chonMon > soMon) {
            printf("Mon khong hop le. Vui long chon lai.\n");
            continue;
        }

        // Them ten mon an
        strncpy(hoaDon.tenMonGoi[hoaDon.soMonGoi], menu[chonMon - 1].tenMon, DO_DAI_TEN_MON - 1);
        hoaDon.tenMonGoi[hoaDon.soMonGoi][DO_DAI_TEN_MON - 1] = '\0';
        hoaDon.giaMonGoi[hoaDon.soMonGoi] = menu[chonMon - 1].gia;
        
        printf("Nhap so luong mon %s: ", hoaDon.tenMonGoi[hoaDon.soMonGoi]);
        scanf(" %d", &soLuong);
        hoaDon.soLuongMon[hoaDon.soMonGoi] = soLuong;
        hoaDon.tongTien += soLuong * hoaDon.giaMonGoi[hoaDon.soMonGoi];
        for(int i = 0; i < menu[chonMon - 1].soNguyenLieu; i++) {
            hoaDon.tienNguyenLieu += menu[chonMon - 1].nguyenLieu[i].gia * soLuong;
        }

        // Tru nguyen lieu trong file
        // Xac dinh so nguyen lieu cua mon
        for(int i = 0; i < soMon; i++) {
            if(strcmp(hoaDon.tenMonGoi[hoaDon.soMonGoi], menu[i].tenMon) == 0) {
                for(int j = 0; j < menu[i].soNguyenLieu; j++) {
                    layNguyenLieu(kho, soNguyenLieuKho, menu[i].nguyenLieu[j], soLuong);
                }
                break;
            }
        }

        hoaDon.soMonGoi++;
    }
    
    printf("\nTong tien thanh toan: %.2f\n", hoaDon.tongTien);
    float tienKhachDua, tienThua;
    printf("Nhap so tien khach dua: ");
    scanf(" %f", &tienKhachDua);
    tienThua = tienKhachDua - hoaDon.tongTien;
    hoaDon.tienThua = tienThua;
    printf("Tien thua: %.2f\n", tienThua);
    
    // Dam bao hoa don va khach hang duoc luu vao mang la khong bi lap
    if(coNhuNhauHoaDon(danhSachHoaDon[(*soHoaDon) - 1], hoaDon) == 1) {     //MARK: LAP_MANG
        printf("\nHoa don nay da ton tai!\n");
    } else {
        luuHoaDon(danhSachHoaDon, soHoaDon, hoaDon);
        printf("\nHoa don da duoc luu.\n");
    }

    if(coNhuNhauKhachHang(danhSachKhachHang[(*soKhachHang) - 1], hoaDon.khachHang) == 0) {  //MARK: LAP_MANG
        themKhachHang(danhSachKhachHang, soKhachHang, hoaDon.khachHang);
    }
}

// Hàm lưu hóa đơn
void luuHoaDon(HoaDon danhSachHoaDon[], int *soHoaDon, HoaDon hoaDon) {
    danhSachHoaDon[*soHoaDon] = hoaDon;
    (*soHoaDon)++;
}

// Hàm tìm kiếm hóa đơn
void timKiemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon) {
    int luaChon;
    float giaTien;
    char keyword[50];
    int monTimKiem;

    printf("\nChon phuong thuc tim kiem hoa don:\n");
    printf("1. Tim theo gia tien\n");
    printf("2. Tim theo ten/sdt khach hang\n");
    printf("3. Tim theo mon an\n");
    printf("Nhap lua chon: ");
    scanf("%d", &luaChon);
    clearBuffer();

    if (luaChon == 1) {
        printf("Nhap gia tien hoa don: ");
        scanf("%f", &giaTien);
        
        printf("\nDanh sach hoa don tim duoc theo gia tien %.2f:\n", giaTien);
        for (int i = 0; i < soHoaDon; i++) {
            if (danhSachHoaDon[i].tongTien == giaTien) {
                printf("Hoa don %d: Ten khach hang: %s - So dien thoai: %s - Ngay nhap: %d/%d/%d - Tong tien: %.2f\n", 
                        i + 1, danhSachHoaDon[i].khachHang.tenKhachHang, danhSachHoaDon[i].khachHang.soDienThoai, danhSachHoaDon[i].ngayNhapDon.ngay,
                        danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam, danhSachHoaDon[i].tongTien);
            }
        }
    } else if (luaChon == 2) {
        printf("Nhap ten hoac so dien thoai khach hang: ");
        fgets(keyword, sizeof(keyword) - 1, stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline    //MARK: STR_PRO
        keyword[sizeof(keyword) - 1] = '\0';
        
        printf("\nDanh sach hoa don tim duoc theo ten/sdt khach hang '%s':\n", keyword);
        for (int i = 0; i < soHoaDon; i++) {
            if (strstr(danhSachHoaDon[i].khachHang.tenKhachHang, keyword) != NULL || 
                strstr(danhSachHoaDon[i].khachHang.soDienThoai, keyword) != NULL) {
                printf("Hoa don %d: Ten khach hang: %s - So dien thoai: %s - Ngay nhap: %d/%d/%d - Tong tien: %.2f\n", 
                        i + 1, danhSachHoaDon[i].khachHang.tenKhachHang, danhSachHoaDon[i].khachHang.soDienThoai, danhSachHoaDon[i].ngayNhapDon.ngay,
                        danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam, danhSachHoaDon[i].tongTien);
            }
        }
    } else if (luaChon == 3) {
        printf("Nhap mon an can tim: ");
        getchar();  // Đọc ký tự newline
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline    //MARK: STR_PRO
        keyword[sizeof(keyword) - 1] = '\0';

        printf("\nDanh sach hoa don chua mon an '%s':\n", keyword);
        for (int i = 0; i < soHoaDon; i++) {
            for (int j = 0; j < danhSachHoaDon[i].soMonGoi; j++) {
                if (strstr(danhSachHoaDon[i].tenMonGoi[j], keyword) != NULL) {
                    printf("Hoa don %d: Ten khach hang: %s - So dien thoai: %s - Ngay nhap: %d/%d/%d - Tong tien: %.2f\n", 
                        i + 1, danhSachHoaDon[i].khachHang.tenKhachHang, danhSachHoaDon[i].khachHang.soDienThoai, danhSachHoaDon[i].ngayNhapDon.ngay,
                        danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam, danhSachHoaDon[i].tongTien);
                    break;  // Nếu tìm thấy món ăn trong hóa đơn, dừng kiểm tra cho hóa đơn đó
                }
            }
        }
    } else {
        printf("Lua chon khong hop le.\n");
    }
}

// Hàm xem hóa đơn
void xemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon) {
    // Viec hien thi cac mon goi tu hoa don doc tu trong file la mot van de do menu co the thay doi
    printf("\nDanh sach hoa don:\n");
    for (int i = 0; i < soHoaDon; i++) {
        printf("\n");
        printf("Hoa don %d:\n", i + 1);
        printf("Ten khach hang: %s\n", danhSachHoaDon[i].khachHang.tenKhachHang);
        printf("Diem tich luy khach hang: %d\n", danhSachHoaDon[i].khachHang.diemTichLuy);
        printf("So dien thoai: %s\n", danhSachHoaDon[i].khachHang.soDienThoai);
        printf("Ngay nhap: %d/%d/%d\n", danhSachHoaDon[i].ngayNhapDon.ngay, danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam);
        printf("Danh sach mon an:\n");
        for (int j = 0; j < danhSachHoaDon[i].soMonGoi; j++) {
            printf("%d. %s - %d x %.2f = %.2f\n", j + 1, danhSachHoaDon[i].tenMonGoi[j], danhSachHoaDon[i].soLuongMon[j], danhSachHoaDon[i].giaMonGoi[j], danhSachHoaDon[i].soLuongMon[j] * danhSachHoaDon[i].giaMonGoi[j]);
        }
        printf("Tong tien: %.2f\n", danhSachHoaDon[i].tongTien);
        printf("Tien thua: %.2f\n", danhSachHoaDon[i].tienThua);
    }
}

void xoaHoaDon(HoaDon danhSach[], int* soLuong, HoaDon hoaDonXoa) {
    if(*soLuong == 0) {
        printf("Danh sach khong co hoa don\n");
        return;
    }

    for(int i = 0; i < *soLuong; i++) {
        if(coNhuNhauHoaDon(danhSach[i], hoaDonXoa) == 1) {
            // Xoa khach hang bang cach di chuyen cac hoa don con lai
            for(int j = i; j < (*soLuong) - 1; j++) {
                danhSach[j] = danhSach[j + 1];
            }
            printf("Hoa don da duoc xoa\n");
            (*soLuong)--;
            return;
        }
    }
    printf("Khong tim thay hoa don\n");
}

void nhapThongTinHoaDon(HoaDon* hoaDon, MonAn menu[], int soMon) {
    // Version don gian hon cua thanh toan, khong co chuc nang tru nguyen lieu tu kho
    // Khong thay the thanh toan, chi mang y nghia bo tro, vd: bo sung hoa don bi thieu.
    chuanHoaHoaDon(hoaDon, 1);

    printf("Nhap ten khach hang: ");
    fgets(hoaDon->khachHang.tenKhachHang, DO_DAI_TEN_KHACH - 1, stdin);
    hoaDon->khachHang.tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
    hoaDon->khachHang.tenKhachHang[strcspn(hoaDon->khachHang.tenKhachHang, "\n")] = '\0';

    printf("Nhap so dien thoai khach hang: ");
    fgets(hoaDon->khachHang.soDienThoai, DO_DAI_SO_DIEN_THOAI - 1, stdin);
    hoaDon->khachHang.soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
    hoaDon->khachHang.soDienThoai[strcspn(hoaDon->khachHang.soDienThoai, "\n")] = '\0';

    printf("Nhap ngay: ");
    saferScanf("%d", &hoaDon->ngayNhapDon.ngay);
    printf("Nhap thang: ");
    saferScanf("%d", &hoaDon->ngayNhapDon.thang);
    printf("Nhap nam: ");
    saferScanf("%d", &hoaDon->ngayNhapDon.nam);

    do {
        printf("So mon phai duong va khong qua %d\n", MAX_MON);
        printf("Nhap so mon: ");
        saferScanf(" %d", &hoaDon->soMonGoi);
    } while(hoaDon->soMonGoi < 0 || hoaDon->soMonGoi > MAX_MON);

    int i = 0;
    while(i < hoaDon->soMonGoi) {
        hienThiMenu(menu, soMon);
        printf("Nhap ten mon an: ");
        fgets(hoaDon->tenMonGoi[i], DO_DAI_TEN_MON, stdin);
        hoaDon->tenMonGoi[i][DO_DAI_TEN_MON - 1] = '\0';
        hoaDon->tenMonGoi[i][strcspn(hoaDon->tenMonGoi[i], "\n")] = '\0';
                                
        int timThayMon = 0;
        for(int j = 0; j < soMon; j++) {
            if(strcmp(hoaDon->tenMonGoi[i], menu[j].tenMon) == 0) {
                do {
                    printf("So luong moi mon phai duong\n");
                    printf("Nhap so luong mon: ");
                    saferScanf(" %d", &hoaDon->soLuongMon[i]);
                } while(hoaDon->soLuongMon[i] < 0);

                hoaDon->giaMonGoi[i] = menu[j].gia;
                for(int k = 0; k < menu[j].soNguyenLieu; k++) {
                    hoaDon->tienNguyenLieu += menu[j].nguyenLieu[k].gia * hoaDon->soLuongMon[i];
                }

                hoaDon->tongTien += menu[j].gia * hoaDon->soLuongMon[i];

                // Tuy ham khong tru vao kho nguyen lieu, gia nguyen lieu van can duoc tinh de co the so sanh voi cac hoa don khac.
                // => Co the nhap dung het thong tin nhung hoa don nhap vao bang ham van khong dung voi hoa don hien co. Dieu do co the do gia nguyen lieu da thay doi

                timThayMon = 1;
                i++;
                break;
            }
        }
        if(timThayMon == 0) {
            printf("Khong tim thay mon an\n");
        }
    }

    float tienThanhToan = 0;
    printf("Nhap so tien khach tra: ");
    saferScanf(" %f", &tienThanhToan);
    hoaDon->tienThua = tienThanhToan - hoaDon->tongTien;
}

// Hàm hiển thị danh sách nguyên liệu trong kho
void hienThiKho(NguyenLieu kho[], int soLuong) {
    if(soLuong == 0) {
        printf("Chua co nguyen lieu\n");
        return;
    }
    printf("DANH SACH NGUYEN LIEU TRONG KHO:\n");
    printf("%-3s %-25s %-10s %-10s\n", "STT", "Ten Nguyen Lieu", "Don Vi", "So Luong");
    for (int i = 0; i < soLuong; i++) {
        printf("%-3d %-25s %-10s %-10.2f\n", i + 1, kho[i].tenNguyenLieu, kho[i].donVi, kho[i].soLuong);
    }
}

// Hàm thêm nguyên liệu vào kho
void themNguyenLieu(NguyenLieu kho[], int* soLuong) {
    if (*soLuong >= MAX_NGUYEN_LIEU) {
        printf("Kho da day, khong the them nguyen lieu moi!\n");
        return;
    }

    NguyenLieu nguyenLieuMoi;
    chuanHoaKho(&nguyenLieuMoi, 1);
    printf("Nhap ten nguyen lieu: ");
    fgets(nguyenLieuMoi.tenNguyenLieu, sizeof(nguyenLieuMoi.tenNguyenLieu) - 1, stdin);
    nguyenLieuMoi.tenNguyenLieu[strcspn(nguyenLieuMoi.tenNguyenLieu, "\n")] = 0;    //MARK: STR_PRO
    nguyenLieuMoi.tenNguyenLieu[sizeof(nguyenLieuMoi.tenNguyenLieu) - 1] = '\0';

    // Kiem tra xem loai nguyen lieu do da co trong mang hay chua. Chi can quan tam den ten
    for(int i = 0; i < *soLuong; i++) {
        if(strcmp(kho[i].tenNguyenLieu, nguyenLieuMoi.tenNguyenLieu) == 0) {
            printf("Nguyen lieu nay da co trong kho\n");                //MARK: LAP_MANG
            return;
        }
    }

    printf("Nhap don vi (vi du: kg, hop, qua): ");
    scanf("%s", nguyenLieuMoi.donVi);
    printf("Nhap so luong: ");
    scanf("%f", &nguyenLieuMoi.soLuong);
    kho[*soLuong] = nguyenLieuMoi;
    (*soLuong)++;
    printf("Da them nguyen lieu: %s\n", nguyenLieuMoi.tenNguyenLieu);
}

void xoaNguyenLieu(NguyenLieu kho[], int* soLuong, char tenNguyenLieuXoa[]) {
    if(*soLuong == 0) {
        return;
    }
    // Xoa phan tu tuong tu KhachXoa dau tien
    for(int i = 0; i < *soLuong; i++) {
        if(strcmp(kho[i].tenNguyenLieu, tenNguyenLieuXoa) == 0) {       //MARK: LAP_MANG
            for(int j = i; j < *soLuong - 1; j++) {
                kho[j] = kho[j + 1];
            }
            printf("Nguyen lieu da duoc xoa\n");
            (*soLuong)--;
            return;
        }
    }
    printf("Khong tim thay nguyen lieu\n");
}

void layNguyenLieu(NguyenLieu kho[], int soNguyenLieuKho, NguyenLieu nguyenLieuSuDung, int soMon) {
    for(int i = 0; i < soNguyenLieuKho; i++) {
        if(strcmp(nguyenLieuSuDung.tenNguyenLieu, kho[i].tenNguyenLieu) == 0) { //MARK: LAP_MANG
            if(nguyenLieuSuDung.soLuong <= kho[i].soLuong) {
                kho[i].soLuong -= nguyenLieuSuDung.soLuong * soMon;
                printf("Tru nguyen lieu thanh cong\n");
                return;
            }

            printf("Khong the tru di nhieu nguyen lieu nhu vay\n");
            return;
        }
    }
}

void nhapThongTinNguyenLieu(NguyenLieu* nguyenLieu) {
    chuanHoaKho(nguyenLieu, 1);
    printf("Nhap ten nguyen lieu moi: ");
    fgets(nguyenLieu->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    nguyenLieu->tenNguyenLieu[strcspn(nguyenLieu->tenNguyenLieu, "\n")] = '\0';
    nguyenLieu->tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';

    printf("Nhap don vi do cua nguyen lieu moi: ");
    fgets(nguyenLieu->donVi, MAX_DO_DAI_CHUOI_DON_VI - 1, stdin);
    nguyenLieu->donVi[strcspn(nguyenLieu->donVi, "\n")] = '\0';
    nguyenLieu->donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';

    printf("Nhap so luong nguyen lieu: ");
    scanf(" %f", &(nguyenLieu->soLuong));
}

// Ham ho tro
void docFileQuanLi(int luaChon, char duongDan[]) {
    // 1: file khach hang
    // 2: file hoa don
    // 3: file kho
    // 4: file menu
    if(luaChon < 1 || luaChon > 4) {
        printf("Lua chon mo file quan li khong hop le!\n");
        return;
    }

    FILE* fptr = fopen(MANAGING_FILE, "r");

    if (!fptr) {
        perror("Khong the mo file quan li file");
        return;
    }
    
    for(int i = 1; i <= luaChon; i++) {
        if(!fgets(duongDan, MAX_FILE_PATH_LENGTH, fptr)) { //DK !feof(fptr) ??
            perror("Xay ra loi khi doc file quan li");
            fclose(fptr);
            return;
        }
    }

    duongDan[strcspn(duongDan, "\n")] = '\0';

    fclose(fptr);
}

void capNhatFileQuanLi(int luaChon, char duongDanMoi[]) {
    // 1: file khach hang
    // 2: file hoa don
    // 3: file kho
    // 4: file menu

    if (luaChon < 1 || luaChon > SO_DOI_TUONG_LAM_VIEC) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    // Loai bo ky tu newline cua dau vao (neu co). Neu dau vao khong co newline, doan code nay khong gay anh huong gi
    if(strlen(duongDanMoi) != 0) {
        duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';     
    }

    // Mo file de doc
    char noiDungFile[SO_DOI_TUONG_LAM_VIEC][MAX_FILE_PATH_LENGTH] = {""}; // Store up to 3 lines
    FILE* fptr1 = fopen(MANAGING_FILE, "r");
    if (!fptr1) {
        perror("Khong the mo file quan li!");
        return;
    }

    // Luu noi dung file ra mang tam thoi
    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        if (!fgets(noiDungFile[i], MAX_FILE_PATH_LENGTH, fptr1)) {//DK !feof(fptr) ??
                perror("Co loi khi doc file quan li");
                fclose(fptr1);
                return;
        } else {
            // Xoa bo ky tu newline cua tat ca duong dan cu
            noiDungFile[i][strcspn(noiDungFile[i], "\n")] = '\0';   //MARK: STR_PRO
        }
    }
    fclose(fptr1);

    // Update noi dung cua duong dan moi vao mang tam thoi
    // Su dung MAX_FILE_PATH_LENGTH - 1 de dam bao cho cho ky tu '\0'
    strncpy(noiDungFile[luaChon - 1], duongDanMoi, MAX_FILE_PATH_LENGTH - 1); // Dieu nay chi thuong co anh huong khi duong dan moi dai hon MAX_FILE_PATH_LENGTH
    noiDungFile[luaChon - 1][MAX_FILE_PATH_LENGTH - 1] = '\0';      //MARK: STR_PRO

    // Mo file de viet lai noi dung moi
    FILE* fptr2 = fopen(MANAGING_FILE, "w");
    if (!fptr2) {
        perror("Khong the mo file quan li de ghi");
        return;
    }

    // Viet noi dung moi, them '\n' vao cuoi moi duong dan de dung dinh dang
    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        fprintf(fptr2, "%s\n", noiDungFile[i]);
    }
    fclose(fptr2);
}

void clearBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}; // Doc buffer den khi gap ky tu xuong dong (enter) hoac den het buffer (neu buffer khong co xuong dong)
}

void saferScanf(char formatString[], void* addr) {
    /*
    Ep nguoi dung nhap dung dinh dang input de dam bao tinh dung dan du lieu.
    Chi co the nhan du lieu cho mot bien mot luc, khong nhu scanf
    */
    // Chu y tranh su dung format string voi whitespace phia sau, vd: " %d  ". Dieu do se khien cho input khong bao gio duoc chap nhan
    int result;
    char extraChr;
    char chr;

    while (1) {
        result = scanf(formatString, addr);
        if(result == 0 || result == EOF) {
            printf("Dau vao khong hop le\n");
            printf("Dau vao: ");
            while((chr = getchar()) != '\n' && chr != EOF); // Don sach input khong hop le cu trong buffer
        } else {
            if(scanf("%c", &extraChr) == 1 && extraChr != '\n') { // Do mot ly do nao do, input nhu "3ad" voi format %d vx duoc nhan. Dieu kien nay o day de ngan dieu do
                printf("Dau vao khong hop le\n");
                printf("Dau vao: ");
                while((chr = getchar()) != '\n' && chr != EOF); // Don sach input khong hop le cu trong buffer
            } else {
                // while((chr = getchar()) != '\n' && chr != EOF); // Don sach buffer
                break;
            }
        }
    }
}

// Cac ham chua dung
// Hàm sửa món
void suaMon(MonAn menu[], int soMon, NguyenLieu kho[], int soNguyenLieuKho) { // MARK: THEM_MON
    int sua;
    hienThiMenu(menu, soMon);
    printf("Nhap so mon muon sua: ");
    scanf("%d", &sua);
    clearBuffer();
    
    if (sua < 1 || sua > soMon) {
        printf("Mon khong hop le.\n");
        return;
    }
    
    printf("Nhap ten mon moi: ");
    getchar();  // Đọc ký tự newline
    fgets(menu[sua - 1].tenMon, sizeof(menu[sua - 1].tenMon) - 1, stdin);
    menu[sua - 1].tenMon[strcspn(menu[sua - 1].tenMon, "\n")] = '\0'; //MARK: STR_PRO
    menu[sua - 1].tenMon[sizeof(menu[sua - 1].tenMon)] = '\0';
    printf("Nhap gia mon moi: ");
    scanf("%f", &menu[sua - 1].gia);

    do {
        printf("Nhap so nguyen lieu mon moi (lon hon 0): ");
        scanf(" %d", &menu[sua - 1].soNguyenLieu);
    } while(menu[sua - 1].soNguyenLieu <= 0);

    int i = 0;
    while(i < menu[sua - 1].soNguyenLieu) {
        printf("Nhap ten nguyen lieu: ");
        fgets(menu[sua - 1].nguyenLieu[i].tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
        menu[sua - 1].nguyenLieu[i].tenNguyenLieu[strcspn(menu[sua - 1].nguyenLieu[i].tenNguyenLieu, "\n")] = '\0';
        menu[sua - 1].nguyenLieu[i].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';   //MARK: STR_PRO

        for(int j = 0; j < soNguyenLieuKho; j++) {
            if(strcmp(menu[sua - 1].nguyenLieu[i].tenNguyenLieu, kho[j].tenNguyenLieu) == 0) {      //MARK: THEM_MON
                do {
                    printf("So luong phai duong va khong qua %.2f %s\n", kho[j].soLuong, kho[j].donVi);
                    printf("Nhap so luong cho nguyen lieu nay: ");
                    scanf(" %f", &menu[sua - 1].nguyenLieu[i].soLuong);
                } while(menu[sua - 1].nguyenLieu[i].soLuong > 0 && menu[sua - 1].nguyenLieu[i].soLuong <= kho[j].soLuong);

                menu[sua - 1].nguyenLieu[i].gia = kho[j].gia;
                strncpy(menu[sua - 1].nguyenLieu[i].donVi, kho[j].donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
                menu[sua - 1].nguyenLieu[i].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';  //MARK: STR_PRO

                i++;
                break;
            }
        }
    } 
    
    printf("Mon da duoc sua.\n");
}

// Hàm xóa nguyên liệu khỏi kho
void xoaNguyenLieuBangSTT(NguyenLieu kho[], int* soLuong) {
    int stt;
    printf("Nhập STT nguyên liệu muốn xóa: ");
    scanf("%d", &stt);

    if (stt < 1 || stt > *soLuong) {
        printf("STT không hợp lệ!\n");
        return;
    }

    // Xóa nguyên liệu bằng cách di chuyển các nguyên liệu còn lại
    for (int i = stt - 1; i < *soLuong - 1; i++) {
        kho[i] = kho[i + 1];
    }
    (*soLuong)--;
    printf("Đã xóa nguyên liệu có STT: %d\n", stt);
}

// Hàm thêm món ăn
void themMon(MonAn menu[], int *soMon, NguyenLieu kho[], int soNguyenLieuKho) { // Con danh sach nguyen lieu va so nguyen lieu
    if (*soMon < MAX_MON) {
        MonAn monMoi;
        printf("\nNhap ten mon moi: ");
        getchar();  // Đọc ký tự newline
        fgets(monMoi.tenMon, sizeof(monMoi.tenMon) - 1, stdin);
        monMoi.tenMon[strcspn(monMoi.tenMon, "\n")] = '\0'; // Loại bỏ ký tự newline
        monMoi.tenMon[sizeof(monMoi.tenMon) - 1] = '\0';
        printf("Nhap gia mon moi: ");
        scanf("%f", &monMoi.gia);

        do {
            printf("Nhap so nguyen lieu mon moi (lon hon 0): ");
            scanf(" %d", &monMoi.soNguyenLieu);
        } while(monMoi.soNguyenLieu <= 0);

        int i = 0;
        while(i < monMoi.soNguyenLieu) {        //MARK: THEM_MON
            printf("Nhap ten nguyen lieu: ");
            fgets(monMoi.nguyenLieu[i].tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
            monMoi.nguyenLieu[i].tenNguyenLieu[strcspn(monMoi.nguyenLieu[i].tenNguyenLieu, "\n")] = '\0';   //MARK: STR_PRO
            monMoi.nguyenLieu[i].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';

            for(int j = 0; j < soNguyenLieuKho; j++) {
                if(strcmp(monMoi.nguyenLieu[i].tenNguyenLieu, kho[j].tenNguyenLieu) == 0) {
                    do {
                        printf("So luong phai duong va khong qua %.2f %s\n", kho[j].soLuong, kho[j].donVi);
                        printf("Nhap so luong cho nguyen lieu nay: ");
                        scanf(" %f", &monMoi.nguyenLieu[i].soLuong);
                    } while(monMoi.nguyenLieu[i].soLuong > 0 && monMoi.nguyenLieu[i].soLuong <= kho[j].soLuong);

                    monMoi.nguyenLieu[i].gia = kho[j].gia;
                    strncpy(monMoi.nguyenLieu[i].donVi, kho[j].donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
                    monMoi.nguyenLieu[i].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';         //MARK: STR_PRO

                    i++;
                    break;
                }
            }
        }
        
        menu[*soMon] = monMoi;
        (*soMon)++;
        printf("Mon moi da duoc them vao danh sach.\n");
    } else {
        printf("Danh sach da day, khong the them mon.\n");
    }
}

// Ham tim kiem nguyen lieu trong kho
void timKiemNguyenLieu(NguyenLieu kho[], int soNguyenLieu) {
    if(soNguyenLieu == 0) {
        printf("Chua co nguyen lieu\n");
        return;
    }

    char tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU];
    printf("Nhap ten nguyen lieu: ");
    fgets(tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    tenNguyenLieu[strcspn(tenNguyenLieu, "\n")] = '\0';     //MARK: STR_PRO
    tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';

    printf("\nDanh sach nguyen lieu tim duoc theo ten '%s':\n", tenNguyenLieu);
    for (int i = 0; i < soNguyenLieu; i++) {
        if (strstr(kho[i].tenNguyenLieu, tenNguyenLieu)) {
            printf("%d. %s - %.2f %s\n", i + 1, kho[i].tenNguyenLieu, kho[i].soLuong, kho[i].donVi);
        }
    }
}

void xoaMon(MonAn menu[], int *soMon) {
    int xoa;
    hienThiMenu(menu, *soMon);
    printf("Nhap so mon muon xoa: ");
    saferScanf("%d", &xoa);
    
    if (xoa < 1 || xoa > *soMon) {
        printf("Mon khong hop le.\n");
        return;
    }
    
    for (int i = xoa - 1; i < *soMon - 1; i++) {
        menu[i] = menu[i + 1];
    }
    (*soMon)--;
    printf("Mon da duoc xoa.\n");
}
