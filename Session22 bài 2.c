#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    char username[30];
    char password[30];
} Account;
int checkAccountExists(Account accounts[], int numAccounts, char username[]) {
    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;  
        }
    }
    return 0;  
}
void registerAccount(Account accounts[], int *numAccounts) {
    Account newAccount;
    char confirmPassword[30];
    printf("Nhap tai khoan: ");
    fgets(newAccount.username, sizeof(newAccount.username), stdin);
    newAccount.username[strcspn(newAccount.username, "\n")] = 0;  
    if (checkAccountExists(accounts, *numAccounts, newAccount.username)) {
        printf("Tai khoan da ton tai\n");
        return;
    }
    printf("Nhap mat khau: ");
    fgets(newAccount.password, sizeof(newAccount.password), stdin);
    newAccount.password[strcspn(newAccount.password, "\n")] = 0;
    printf("Xac nhan mat khau: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;
    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("Mat khau sai\n");
        return;
    }
    accounts[*numAccounts] = newAccount;
    (*numAccounts)++;
    FILE *file = fopen("accounts.dat", "wb");
    if (!file) {
        printf("Loi luu file\n");
        return;
    }
    fwrite(accounts, sizeof(Account), *numAccounts, file);
    fclose(file);
    printf("Dang ki thanh cong\n");
}
void login(Account accounts[], int numAccounts) {
    char username[30], password[30];
    printf("Nhap tai khoan: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("Nhap mat khau: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong\n");
            return;
        }
    }
    printf("Dang nhap that bai\n");
}
int loadAccounts(Account accounts[]) {
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        return 0;  
    }
    int numAccounts = 0;
    while (fread(&accounts[numAccounts], sizeof(Account), 1, file)) {
        numAccounts++;
        if (numAccounts >= 100) break; 
    }
    fclose(file);
    return numAccounts;
}
int main() {
    Account accounts[100];
    int numAccounts = loadAccounts(accounts);
    int choice;
    while (1) {
        printf("\nMENU\n");
    	printf("1. Dang nhap\n");
    	printf("2. Dang ky\n");
    	printf("3. Thoat\n");
    	printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();  
        switch (choice) {
            case 1:
                login(accounts, numAccounts);
                break;
            case 2:
                registerAccount(accounts, &numAccounts);
                break;
            case 3:
                printf("Thoat\n");
                return 0;
            default:
                printf("Lua chon khong dung\n");
        }
    }
    return 0;
}



