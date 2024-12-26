#include <stdio.h>
#include <string.h>
struct students {
    int id;
    char name[50];
    int age;
};
struct students SV[100];
void printstudents();
void addstudent();
void editstudent();
void deletestudent();
void searchstudent();
void sortstudents();
void readstudentsfromfile(const char *filename);
void writestudentsfile(const char *filename);
int main() {
    int choose;
    readstudentsfromfile("students.dat");
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                printstudents();
                break;
            case 2:
                addstudent();
                break;
            case 3:
                editstudent();
                break;
            case 4:
                deletestudent();
                break;
            case 5:
                searchstudent();
                break;
            case 6:
                sortstudents();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }

    } while (choose != 7);

    return 0;
}
void printstudents() {
    printf("\nDanh sach sinh vien\n");
    printf("ID\tTen\tTuoi\n");
    for (int i = 0; i < 100; i++) {
        if (SV[i].id != 0) {
            printf("%d\t%s\t%d\n", SV[i].id, SV[i].name, SV[i].age);
        }
    }
}
void addstudent() {
    int id, age;
    char name[50];

    printf("Nhap ID sinh vien: ");
    scanf("%d", &id);
    printf("Nhap ten sinh vien: ");
    getchar();
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Nhap tuoi sinh vien: ");
    scanf("%d", &age);

    for (int i = 0; i < 100; i++) {
        if (SV[i].id == 0) {
            SV[i].id = id;
            strcpy(SV[i].name, name);
            SV[i].age = age;
            writestudentsfile("students.dat");
            printf("Sinh vien da duoc them!\n");
            return;
        }
    }
    printf("Danh sach sinh vien da day!\n");
}
void editstudent() {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);

    for (int i = 0; i < 100; i++) {
        if (SV[i].id == id) {
            printf("Nhap ten moi: ");
            getchar();
            fgets(SV[i].name, 50, stdin);
            SV[i].name[strcspn(SV[i].name, "\n")] = '\0';
            printf("Nhap tuoi moi: ");
            scanf("%d", &SV[i].age);
            writestudentsfile("students.dat");
            printf("Thong tin sinh vien da duoc cap nhat!\n");
            return;
        }
    }
    printf("Sinh vien khong ton tai!\n");
}

void deletestudent() {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < 100; i++) {
        if (SV[i].id == id) {
            SV[i].id = 0;
            memset(SV[i].name, 0, sizeof(SV[i].name));
            SV[i].age = 0;
            writestudentsfile("students.dat");
            printf("Sinh vien da duoc xoa!\n");
            return;
        }
    }
    printf("Sinh vien khong ton tai!\n");
}
void searchstudent() {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < 100; i++) {
        if (SV[i].id == id) {
            printf("Sinh vien: ID = %d, Ten = %s, Tuoi = %d\n", SV[i].id, SV[i].name, SV[i].age);
            return;
        }
    }
    printf("Sinh vien khong ton tai!\n");
}
void sortstudents() {
    for (int i = 0; i < 100 - 1; i++) {
        for (int j = i + 1; j < 100; j++) {
            if (SV[i].id > SV[j].id && SV[i].id != 0 && SV[j].id != 0) {
                struct students temp = SV[i];
                SV[i] = SV[j];
                SV[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien da duoc sap xep!\n");
}
void readstudentsfromfile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fread(SV, sizeof(struct students), 100, file);
        fclose(file);
    } else {
        printf("File khong ton tai, khoi tao du lieu moi\n");
    }
}
void writestudentsfile(const char *filename) {
    FILE *file = fopen(filename, "wb");
    fwrite(SV, sizeof(struct students), 100, file);
    fclose(file);
}


