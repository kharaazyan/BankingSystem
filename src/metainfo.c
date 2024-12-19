#include "../include/bank.h"
#include "../include/functions.h"

void metaread(char* arr, Metainfo*metainfo){
    char*copy = arr;
    metainfo->ID = my_atoi(&copy);
    metainfo->acc_count = my_atoi(&copy);
    metainfo->acc_block_count = my_atoi(&copy);
    metainfo->transaction = my_atoi(&copy);
    metainfo->all_money = my_atoi(&copy);
    metainfo->ID++; 
    synco();
}

void grancum(Metainfo*metainfo){
    Account account;
    zroacum(account.owner);
    zroacum(account.pass);
    zroacum(account.number);
    system("clear");

    printf("Enter the owner name: ");
    clear();
    fgets(account.owner, SIZE_OWNER, stdin);
    while(account.owner[7] == '\0' || account.owner[7]== '\n'){
        printf("The minimum length for a name is 8 characters!\nTry again: ");
        zroacum(account.owner);
        fgets(account.owner, SIZE_OWNER, stdin);
    }
    veracum(account.owner);
    if(login(account.owner) != -1){
        system("clear");
        printf("This name is taken! You will be returned to the menu!\n");
        sleep(2);
        return;
    }

    printf("Enter the password: ");
    fgets(account.pass, SIZE_OWNER, stdin);
    while(account.pass[7] == '\0' || account.pass[7] == '\n'){
        printf("The minimum length for a password is 8 characters!\nTry again: ");
        zroacum(account.pass);
        fgets(account.pass, SIZE_OWNER, stdin);
    }
    veracum(account.pass);
    generator(&account);
    account.ID = metainfo->acc_count + 1;
    account.status = ACTIVE;
    account.balance = 0;
    metainfo->acc_count++;
    system("clear");
    printf("Please, wait :)\n");
    synco();
    char id[7] = {"      "};
    sprintf(id, "%zu", account.ID);
    for(int i = 0; i < 6; i++){
        if(id[i] == '\0') id[i] = ' ';
    }
    id[6] = '\0';
    off = lseek((int)fd_account, 0, SEEK_END);
    dprintf((int)fd_account, "%s%s%s|%s | 0.0 AMD         ACTIVE \n", id, account.owner, account.pass, account.number);
    fsync(fd_account);
    printf("The information has been updated!\n");
    sleep(1);
}

int log_id(size_t ID){
    char account[SIZE] = {'\0'};
    lseek((int)fd_account, 0, SEEK_SET); 
    int count = -1;

    while (read((int)fd_account, account, SIZE) > 0) {
        count++;
        char*copy = account;
        int tmp = (int)my_atoi(&copy);
        if((size_t)tmp == ID){
            off = count;
            return 1;
        }
    }
    return 0; 
}

void ogtaterer(){
    system("clear");
    if (endo_m->acc_count < 1){
        printf("No users found\n");
        sleep(2);
        any_key();
        return;
    }
    Account account = {0};
    char account_char[SIZE] = {'\0'};
    lseek((int)fd_account, SIZE, SEEK_SET); 
    while (read((int)fd_account, account_char, SIZE) > 0) {
        char id[7] = {"      "};
        char char_status[8] = {'\0'};
        account.ID = (size_t)atoi(account_char);
        for(int i = 0; i < SIZE_OWNER; i++){
            account.owner[i] = account_char[i + OWNER_POS];
        }
        veracum(account.owner);
        for(int i = 0; i < BANK_ACC; i++){
            account.number[i] = account_char[i + NUMBER_POS];
        }
        for(int i = 0; account_char[i + STATUS_POS] != '\n' && i < 7; i++){
            char_status[i] = account_char[i + STATUS_POS];
            if(char_status[i] == '\n') char_status[i] = ' ';
        }
        sprintf(id, "%zu", account.ID);
        for(int i = 0; i < 6; i++){
            if(id[i] == '\0') id[i] = ' ';
        }
        id[6] = '\0';
        char_status[7] = '\0';
        account.owner[SIZE_OWNER - 1] = '\0';
        account.number[BANK_ACC - 1] = '\0';
        
        printf("ID: %s| %s | %s | %s\n", id, account.owner, account.number, char_status);
    }
    any_key();
}

void ogtaterer_block(){
    system("clear");
    if (endo_m->acc_block_count < 1){
        printf("No users found\n");
        any_key();
        return;
    }
    Account account = {0};
    char account_char[SIZE] = {'\0'};
    lseek((int)fd_account, SIZE, SEEK_SET); 
    while (read((int)fd_account, account_char, SIZE) > 0) {
        char char_status[8] = {'\0'};
        account.ID = (size_t)atoi(account_char);
        for(int i = 0; i < SIZE_OWNER; i++){
            account.owner[i] = account_char[i + OWNER_POS];
        }
        veracum(account.owner);
        for(int i = 0; i < BANK_ACC; i++){
            account.number[i] = account_char[i + NUMBER_POS];
        }
        for(int i = 0; account_char[i + STATUS_POS] != '\n' && i < 7; i++){
            char_status[i] = account_char[i + STATUS_POS];
            if(char_status[i] == '\n') char_status[i] = ' ';
        }
        char_status[7] = '\0';
        account.owner[SIZE_OWNER - 1] = '\0';
        account.number[BANK_ACC - 1] = '\0';
        if(char_status[0] == 'B'){
            printf("ID: %zu | %s | %s | %s\n", account.ID, account.owner, account.number, char_status);
        }
    }
    any_key();
}

void apokalipsis(){
    char confirm;
    char stugum[24] = {'\0'};
    char arr[12] = "papayutyun\n";
    system("clear");
    printf("Are you sure you want to delete the database? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        printf("Please, enter the admin password: ");
        clear();
        fgets(stugum, 24, stdin);

        if (strcmp(stugum, arr) == 0) {
            close((int)fd_account);
            close((int)fd_metainfo);
            fd_account = (size_t)open(FILE_ACC, O_RDWR | O_TRUNC | O_CREAT, 0664);
            fd_metainfo = (size_t)open(FILE_INFO, O_RDWR | O_TRUNC | O_CREAT, 0664);
            if (fd_account == (size_t)-1 || fd_metainfo == (size_t)-1) {
                perror("Failed to reset database files");
                exit(1);
            }
            dprintf((int)fd_account, "ID:   Owner:                  Password:                Number:               Balance:        Status:\n");
            dprintf((int)fd_metainfo, "\t\t\t\t\t\t\tMetainformation:\n");
            printf("Database has been successfully deleted.\n");
            any_key();
            exit(0);
        } else {
            printf("Incorrect password. Database deletion cancelled.\n");
        }
    } else {
        printf("Database deletion cancelled.\n");
    }
    any_key();
}

void synco(){
    close((int)fd_metainfo);
    fd_metainfo = (size_t)open(FILE_INFO, O_RDWR | O_TRUNC);
    dprintf((int)fd_metainfo, "\t\t\t\t\t\t\tMetainformation:\n");
    dprintf((int)fd_metainfo, "Unique ID: %zu\nNumber of accounts: %zu\nNumber of blocked accounts: %zu\nNumber of transactions: %zu\nThe total amount of money: %zu\n",
            endo_m->ID, endo_m->acc_count, endo_m->acc_block_count, endo_m->transaction, endo_m->all_money);
    fsync((int)fd_metainfo);
}
