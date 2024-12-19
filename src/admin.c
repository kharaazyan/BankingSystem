#include "../include/bank.h"
#include "../include/functions.h"

void admin_menu(Account*account){
    char yntrutyun_menu = 'y';
    system("clear");
    printf("Welcome, esteemed system administrator\nYou have been granted root privileges.\n");
    sleep(3);
    do {
        int gorcoxutyun;
        system("clear");
        printf("Admin Menu:\n");
        printf("1. View all registered users\n");
        printf("2. View blocked accounts\n");
        printf("3. Change an account status\n");
        printf("4. Change account password\n");
        printf("5. Delete database\n");
        printf("6. Return to main menu\n");
        printf("Please choose an action: ");
        scanf("%d", &gorcoxutyun);

        while(gorcoxutyun < 1 || gorcoxutyun > 6) {
            system("clear");
            printf("Oops! That's not a valid choice.\n");
            printf("Admin Menu:\n");
            printf("1. View all registered users\n");
            printf("2. View blocked accounts\n");
            printf("3. Change an account status\n");
            printf("4. Change account password\n");
            printf("5. Delete database\n");
            printf("6. Return to main menu\n");
            printf("Please choose an action: ");
            scanf("%d", &gorcoxutyun);
        }

        system("clear");
        switch(gorcoxutyun){
            case 1: ogtaterer(); break;
            case 2: ogtaterer_block(); break;
            case 3: admin_status(); break;
            case 4: change_pass(); break;
            case 5: apokalipsis(); break;
            case 6: yntrutyun_menu = 'n'; break;
        }
    } while(yntrutyun_menu == 'y');
    sleep(1);
}

void change_pass() {
    size_t user_id;
    char new_pass[SIZE_OWNER] = {'\0'};
    char current_pass[SIZE_OWNER] = {'\0'};

    printf("Enter the user account ID: ");
    scanf("%zu", &user_id);

    if (!log_id(user_id)) {
        printf("User account not found!\n");
        any_key();
        return;
    }

    lseek((int)fd_account, off * SIZE + PASS_POS, SEEK_SET);
    read((int)fd_account, current_pass, SIZE_OWNER);

    printf("Enter the new password: ");
    clear();
    fgets(new_pass, SIZE_OWNER, stdin);

    for (int i = 0; i < SIZE_OWNER; i++) {
        if (new_pass[i] == '\n') {
            new_pass[i] = '\0';
            break;
        }
    }

    lseek((int)fd_account, off * SIZE + PASS_POS, SEEK_SET);
    dprintf((int)fd_account, "                        "); 
    lseek((int)fd_account, off * SIZE + PASS_POS, SEEK_SET);
    dprintf((int)fd_account, "%s", new_pass);

    synco();
    printf("Password of user ID: %zu has been successfully changed.\n", user_id);
    any_key();
}


void root_access(Account* account){
    char admin_password[SIZE_OWNER] = "papayutyun\n"; 
    char entered_password[SIZE_OWNER] = {'\0'};
    system("clear");
    printf("Please enter the system administrator password: ");
    clear();
    fgets(entered_password, SIZE_OWNER, stdin);

    if(strcmp(entered_password, admin_password) == 0){
        account->status = ADMIN;
        lseek((int)fd_account, off + STATUS_POS, SEEK_SET);
        dprintf((int)fd_account, "ADMIN  ");
        printf("Admin privileges granted.\n");
    } else {
        printf("Incorrect admin password.\n");
    }
    sleep(1);
}

void admin_status() {
    size_t user_id;
    char new_status[9] = {'\0'};
    char account_data[9] = {'\0'};
    int count = 0;
    printf("Enter the user account ID: ");
    scanf("%zu", &user_id);

    if (!log_id(user_id)) {
        printf("User account not found!\n");
        any_key();
        return;
    }

    lseek((int)fd_account, off * SIZE + STATUS_POS, SEEK_SET);
    read((int)fd_account, account_data, 7);
    if(strcmp("BLOCKED", account_data) == 0){
        count++;
    }
    printf("Enter the new status (ACTIVE, BLOCKED, ADMIN): ");
    clear();
    fgets(new_status, 8, stdin);

    if (strcmp(new_status, "ACTIVE\n") != 0 && strcmp(new_status, "BLOCKED") != 0 && strcmp(new_status, "ADMIN\n") != 0) {
        printf("Invalid status!\n");
        any_key();
        return;
    }
    for(int i = 0; i < 9; i++){
        if(new_status[i] == '\n') new_status[i] = ' ';
        if(account_data[i] == '\n') account_data[i] = '\0'; 
    }
    lseek((int)fd_account, off * SIZE + STATUS_POS, SEEK_SET);
    dprintf((int)fd_account, "       \n");
    lseek((int)fd_account, off * SIZE + STATUS_POS, SEEK_SET);
    dprintf((int)fd_account, "%s", new_status);
    if(count){
        if(strcmp("BLOCKED", new_status)){
             endo_m->acc_block_count--;
        }
    }
    else{
        if(strcmp("BLOCKED", new_status) == 0){
            endo_m->acc_block_count++;
        }
    }
    synco();
    printf("Status of user ID %zu | %s has been successfully changed to %s.\n", user_id, account_data, new_status);
    any_key();
}


void block(Account*account, char*arr){
    char confirm;
    printf("Are you sure you want to block your account? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        account->status = BLOCKED;
        lseek((int)fd_account, off + STATUS_POS, SEEK_SET);
        dprintf((int)fd_account, "BLOCKED");
        endo_m->acc_block_count++;
        *arr = 'n';
        printf("Your account has been successfully blocked.\n");
    } else {
        printf("Account blocking cancelled.\n");
    }
    synco();
    any_key();
}
