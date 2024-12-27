#ifndef GENERAL_H_
#define GENRAL_H_

#define NGAN_PHAN_TU_CSV ","

typedef struct {
    int ngay;
    int thang;
    int nam;
} Ngay;

int coNhuNhauNgay(Ngay n1, Ngay n2) {
    if(n1.ngay == n2.ngay && n1.thang == n2.thang && n1.nam == n2.nam) {
        return 1;
    }
    return 0;
}

void saoChepNgay(Ngay* ngayNhan, Ngay* ngayNguon) {
    ngayNhan->ngay = ngayNguon->ngay;
    ngayNhan->thang = ngayNguon->thang;
    ngayNhan->nam = ngayNguon->nam;
}


#endif