#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int maSP;
    char tenSP[100];
    float giaNhap;
    float giaBan;
    int soLuong;
} Product;

Product products[100];  // Mảng chứa sản phẩm
int productCount = 0;  // Biến đếm số lượng sản phẩm
float doanhThu = 0;  // Biến lưu doanh thu hiện tại

void nhapThongTinSP(Product* sp) {
    printf("Nhap ma san pham: ");
    scanf("%d", &sp->maSP);
    getchar();  // Clear the newline character
    printf("Nhap ten san pham: ");
    fgets(sp->tenSP, sizeof(sp->tenSP), stdin);
    sp->tenSP[strcspn(sp->tenSP, "\n")] = '\0';  // Remove newline character at the end
    printf("Nhap gia nhap: ");
    scanf("%f", &sp->giaNhap);
    printf("Nhap gia ban: ");
    scanf("%f", &sp->giaBan);
    printf("Nhap so luong: ");
    scanf("%d", &sp->soLuong);
}

void nhapDanhSachSP() {
    printf("Nhap so luong san pham: ");
    scanf("%d", &productCount);

    for (int i = 0; i < productCount; i++) {
        printf("\nNhap thong tin san pham %d:\n", i + 1);
        nhapThongTinSP(&products[i]);
        doanhThu -= products[i].soLuong * products[i].giaNhap;  // Giảm doanh thu khi nhập hàng
    }
}

void hienThiDanhSachSP() {
    printf("\nDanh sach san pham:\n");
    printf("MaSP\tTenSanPham\tGiaNhap\tGiaBan\tSoLuong\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d\t%s\t%.2f\t%.2f\t%d\n", products[i].maSP, products[i].tenSP, products[i].giaNhap, products[i].giaBan, products[i].soLuong);
    }
}

void nhapSanPham() {
    int maSP;
    printf("Nhap ma san pham muon nhap: ");
    scanf("%d", &maSP);

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].maSP == maSP) {
            found = 1;
            int soLuong;
            printf("Nhap so luong muon nhap: ");
            scanf("%d", &soLuong);
            products[i].soLuong += soLuong;
            doanhThu -= soLuong * products[i].giaNhap;  // Giảm doanh thu khi nhập hàng
            printf("Nhap san pham thanh cong!\n");
            break;
        }
    }

    if (!found) {
        printf("San pham voi ma %d khong ton tai! Vui long them san pham moi.\n", maSP);
        Product newProduct;
        newProduct.maSP = maSP;
        nhapThongTinSP(&newProduct);
        products[productCount++] = newProduct;
        doanhThu -= newProduct.soLuong * newProduct.giaNhap;  // Giảm doanh thu khi nhập hàng
    }
}

void capNhatSP() {
    int maSP;
    printf("Nhap ma san pham muon cap nhat: ");
    scanf("%d", &maSP);

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].maSP == maSP) {
            found = 1;
            printf("Nhap gia nhap moi: ");
            scanf("%f", &products[i].giaNhap);
            printf("Nhap gia ban moi: ");
            scanf("%f", &products[i].giaBan);
            printf("Nhap so luong moi: ");
            scanf("%d", &products[i].soLuong);
            printf("Cap nhat thong tin san pham thanh cong!\n");
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay san pham voi ma %d\n", maSP);
    }
}

void sapXepSP() {
    int luaChon;
    printf("Chon sap xep san pham theo gia:\n");
    printf("1. Tang dan\n");
    printf("2. Giam dan\n");
    printf("Lua chon: ");
    scanf("%d", &luaChon);

    for (int i = 0; i < productCount - 1; i++) {
        for (int j = i + 1; j < productCount; j++) {
            if ((luaChon == 1 && products[i].giaBan > products[j].giaBan) || 
                (luaChon == 2 && products[i].giaBan < products[j].giaBan)) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }

    printf("Danh sach san pham sau khi sap xep:\n");
    hienThiDanhSachSP();
}

void timKiemSP() {
    char tenSP[100];
    printf("Nhap ten san pham muon tim: ");
    getchar();  // Clear the newline character
    fgets(tenSP, sizeof(tenSP), stdin);
    tenSP[strcspn(tenSP, "\n")] = '\0';  // Remove newline character

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].tenSP, tenSP) != NULL) {
            if (!found) {
                printf("\nKet qua tim kiem:\n");
                printf("MaSP\tTenSanPham\tGiaNhap\tGiaBan\tSoLuong\n");
            }
            printf("%d\t%s\t%.2f\t%.2f\t%d\n", products[i].maSP, products[i].tenSP, products[i].giaNhap, products[i].giaBan, products[i].soLuong);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham co ten '%s'\n", tenSP);
    }
}

void banSanPham() {
    int maSP, soLuong;
    printf("Nhap ma san pham muon ban: ");
    scanf("%d", &maSP);

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].maSP == maSP) {
            found = 1;
            printf("Nhap so luong muon ban: ");
            scanf("%d", &soLuong);

            if (soLuong > products[i].soLuong) {
                printf("Khong con du hang!\n");
            } else if (products[i].soLuong == 0) {
                printf("San pham da het hang!\n");
            } else {
                products[i].soLuong -= soLuong;
                doanhThu += soLuong * products[i].giaBan;
                printf("Ban hang thanh cong!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay san pham voi ma %d\n", maSP);
    }
}

void hienThiDoanhThu() {
    printf("\nDoanh thu hien tai: %.2f\n", doanhThu);
}

void displayMenu() {
    printf("\nMENU\n");
    printf("1. Nhap thong tin san pham\n");
    printf("2. Hien thi danh sach san pham\n");
    printf("3. Nhap san pham\n");
    printf("4. Cap nhat thong tin san pham\n");
    printf("5. Sap xep san pham theo gia\n");
    printf("6. Tim kiem san pham\n");
    printf("7. Ban san pham\n");
    printf("8. Xem doanh thu\n");
    printf("9. Thoat\n");
}

int main() {
    int choice;
    do {
        displayMenu();
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                nhapDanhSachSP();
                break;
            case 2:
                hienThiDanhSachSP();
                break;
            case 3:
                nhapSanPham();
                break;
            case 4:
                capNhatSP();
                break;
            case 5:
                sapXepSP();
                break;
            case 6:
                timKiemSP();
                break;
            case 7:
                banSanPham();
                break;
            case 8:
                hienThiDoanhThu();
                break;
            case 9:
                printf("Thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (choice != 9);

    return 0;
}
