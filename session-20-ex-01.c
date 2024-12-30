#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int maSach;
    char tenSach[100];
    char tacGia[100];
    float giaTien;
    char theLoai[100];
} Sach;

Sach danhSachSach[100];
int soLuongSach = 0;

void nhapThongTinSach(Sach *sach) {
    printf("Nhap ma sach: ");
    scanf("%d", &sach->maSach);
    getchar();
    printf("Nhap ten sach: ");
    fgets(sach->tenSach, 100, stdin);
    sach->tenSach[strcspn(sach->tenSach, "\n")] = '\0';
    printf("Nhap tac gia: ");
    fgets(sach->tacGia, 100, stdin);
    sach->tacGia[strcspn(sach->tacGia, "\n")] = '\0';
    printf("Nhap gia tien: ");
    scanf("%f", &sach->giaTien);
    getchar();
    printf("Nhap the loai: ");
    fgets(sach->theLoai, 100, stdin);
    sach->theLoai[strcspn(sach->theLoai, "\n")] = '\0';
}

void nhapDanhSachSach() {
    printf("Nhap so luong sach: ");
    scanf("%d", &soLuongSach);
    getchar();
    for (int i = 0; i < soLuongSach; i++) {
        printf("\nNhap thong tin sach %d:\n", i + 1);
        nhapThongTinSach(&danhSachSach[i]);
    }
}

void hienThiDanhSachSach() {
    printf("\nDanh sach sach:\n");
    printf("Ma sach | Ten sach | Tac gia | Gia tien | The loai\n");
    for (int i = 0; i < soLuongSach; i++) {
        printf("%d | %s | %s | %.2f | %s\n", 
            danhSachSach[i].maSach, 
            danhSachSach[i].tenSach, 
            danhSachSach[i].tacGia, 
            danhSachSach[i].giaTien, 
            danhSachSach[i].theLoai);
    }
}

void themSachVaoViTri() {
    int viTri;
    if (soLuongSach >= 100) {
        printf("Danh sach sach da day!\n");
        return;
    }

    printf("Nhap vi tri muon them sach: ");
    scanf("%d", &viTri);
    if (viTri < 0 || viTri > soLuongSach) {
        printf("Vi tri khong hop le!\n");
        return;
    }

    for (int i = soLuongSach; i > viTri; i--) {
        danhSachSach[i] = danhSachSach[i - 1];
    }
    nhapThongTinSach(&danhSachSach[viTri]);
    soLuongSach++;
}

void xoaSachTheoMa() {
    int maSach;
    printf("Nhap ma sach muon xoa: ");
    scanf("%d", &maSach);

    int index = -1;
    for (int i = 0; i < soLuongSach; i++) {
        if (danhSachSach[i].maSach == maSach) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay sach co ma %d\n", maSach);
        return;
    }

    for (int i = index; i < soLuongSach - 1; i++) {
        danhSachSach[i] = danhSachSach[i + 1];
    }
    soLuongSach--;
    printf("Xoa sach voi ma %d thanh cong!\n", maSach);
}

void capNhatThongTinSach() {
    int maSach;
    printf("Nhap ma sach muon cap nhat: ");
    scanf("%d", &maSach);

    int index = -1;
    for (int i = 0; i < soLuongSach; i++) {
        if (danhSachSach[i].maSach == maSach) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay sach co ma %d\n", maSach);
        return;
    }

    printf("Nhap thong tin moi cho sach co ma %d:\n", maSach);
    nhapThongTinSach(&danhSachSach[index]);
    printf("Cap nhat thong tin sach thanh cong!\n");
}

void sapXepSachTheoGia(int tangDan) {
    for (int i = 0; i < soLuongSach - 1; i++) {
        for (int j = i + 1; j < soLuongSach; j++) {
            if ((tangDan && danhSachSach[i].giaTien > danhSachSach[j].giaTien) || 
                (!tangDan && danhSachSach[i].giaTien < danhSachSach[j].giaTien)) {
                Sach temp = danhSachSach[i];
                danhSachSach[i] = danhSachSach[j];
                danhSachSach[j] = temp;
            }
        }
    }
    printf("Danh sach sach sau khi sap xep:\n");
    hienThiDanhSachSach();
}

void timSachTheoTen() {
    char tenSach[100];
    printf("Nhap ten sach muon tim: ");
    getchar();
    fgets(tenSach, 100, stdin);
    tenSach[strcspn(tenSach, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < soLuongSach; i++) {
        if (strstr(danhSachSach[i].tenSach, tenSach) != NULL) {
            if (!found) {
                printf("\nKet qua tim kiem:\n");
                printf("Ma sach | Ten sach | Tac gia | Gia tien | The loai\n");
            }
            printf("%d | %s | %s | %.2f | %s\n", 
                danhSachSach[i].maSach, 
                danhSachSach[i].tenSach, 
                danhSachSach[i].tacGia, 
                danhSachSach[i].giaTien, 
                danhSachSach[i].theLoai);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach theo ten '%s'\n", tenSach);
    }
}

void hienThiMenu() {
    printf("\nMENU\n");
    printf("1. Nhap so luong va thong tin sach\n");
    printf("2. Hien thi thong tin sach\n");
    printf("3. Them sach vao vi tri\n");
    printf("4. Xoa sach theo ma sach\n");
    printf("5. Cap nhat thong tin sach theo ma sach\n");
    printf("6. Sap xep sach theo gia (tang/giam)\n");
    printf("7. Tim kiem sach theo ten sach\n");
    printf("8. Thoat\n");
}

int main() {
    int luaChon;
    do {
        hienThiMenu();
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                nhapDanhSachSach();
                break;
            case 2:
                hienThiDanhSachSach();
                break;
            case 3:
                themSachVaoViTri();
                break;
            case 4:
                xoaSachTheoMa();
                break;
            case 5:
                capNhatThongTinSach();
                break;
            case 6:
                {
                    int luaChonSapXep;
                    printf("Chon sap xep theo gia:\n");
                    printf("1. Tang dan\n");
                    printf("2. Giam dan\n");
                    printf("Lua chon: ");
                    scanf("%d", &luaChonSapXep);
                    sapXepSachTheoGia(luaChonSapXep == 1);
                }
                break;
            case 7:
                timSachTheoTen();
                break;
            case 8:
                printf("Thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (luaChon != 8);

    return 0;
}
