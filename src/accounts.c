#include "../include/bank.h"
#include "../include/functions.h"

int login(char *arr) {
    if (endo_m->acc_count < 1) return -1;
    char account[SIZE] = {'\0'};
    lseek((int)fd_account, 0, SEEK_SET); 
    int count = -1;
    while (read((int)fd_account, account, SIZE) > 0) {
        count++;
        char temp_owner[SIZE_OWNER];
        for (int i = 6; i < SIZE_OWNER && account[i] != '\0'; ++i) {
            temp_owner[i - OWNER_POS] = account[i];
        }
        veracum(temp_owner);
        if (strcmp(arr, temp_owner) == 0) {
            return count; 
        }
    }
    return -1; 
}

int mutq(Account* account) {
    char arr_login[SIZE_OWNER] = {'\0'};
    char arr_parol[SIZE_OWNER] = {'\0'};
    int log;
    system("clear");
    printf("Enter the owner name: ");
    clear();
    fgets(arr_login, SIZE_OWNER, stdin);
    veracum(arr_login);
    log = login(arr_login);
    if (log == -1) {
        printf("User not found!\n");
        sleep(1);
        return -1;
    }

    off_t offset = log * SIZE;
    off = lseek((int)fd_account, offset, SEEK_SET);
    char tmp[SIZE] = {'\0'};
    if (read((int)fd_account, tmp, SIZE) == -1) {
        perror("read");
        exit(1);
    }

    char* copy = tmp;
    account->ID = my_atoi(&copy);
    copy = &tmp[MONEY_POS];
    account->balance = my_atoi(&copy);
    if (tmp[94] == 'L') {
        account->status = BLOCKED;
    } else if (tmp[94] == 'C') {
        account->status = ACTIVE;
    } else {
        account->status = ADMIN;
    }
    if(account->status == BLOCKED) {
        system("clear");
        printf("Your account has been blocked!\nContact your system administrator for unlocking!\n");
        sleep(4);
        return -2;
    }
    for (int i = 0; i < BANK_ACC; i++) {
        account->owner[i] = tmp[i + OWNER_POS];
        account->pass[i] = tmp[i + PASS_POS];
        if (i < BANK_ACC) account->number[i] = tmp[i + NUMBER_POS];
    }

    veracum(account->owner);
    veracum(account->pass);
    account->number[19] = '\0';
    printf("Enter your password: ");
    fgets(arr_parol, SIZE_OWNER, stdin);
    veracum(arr_parol);

    int count = 0;
    while (strcmp(arr_parol, account->pass)) {
        count++;
        system("clear");
        if (count == 3) {
            printf("Your account has been blocked!\n");
            sleep(2);
            account->status = BLOCKED;
            endo_m->acc_block_count++;

            lseek((int)fd_account, offset + STATUS_POS, SEEK_SET);
            if (off == -1) {
                perror("lseek");
                exit(1);
            }
            if (write((int)fd_account, "BLOCKED", 7) == -1) { 
                perror("write");
                exit(1);
            }
            synco();
            return -2;
        } else {
            printf("There are %d attempts left. Then the account will be blocked!\n", 3 - count);
        }
        printf("Enter your password: ");
        fgets(arr_parol, SIZE_OWNER, stdin);
        veracum(arr_parol);
    }

    printf("You have successfully logged in\n");
    sleep(1);
    if (account->status == ADMIN) return 0;
    else return 1;
}

void acc_menu(Account* account) {
    char yntrutyun_menu = 'y';
    system("clear");
    printf("Hello, my dear: %s\n", account->owner);
    sleep(2);
    do {
        system("clear");
        int gorcoxutyun;
        printf("Your options:\n");
        printf("1. Check your balance\n");
        printf("2. Deposit funds\n");
        printf("3. Withdraw funds\n");
        printf("4. Transfer money between accounts\n");
        printf("5. Block an account\n");
        printf("6. Accessing root privileges\n");
        printf("7. Return to main menu\n");
        printf("Please choose an action: ");
        scanf("%d", &gorcoxutyun);

        while(gorcoxutyun < 1 || gorcoxutyun > 7) {
            system("clear");
            printf("Oops! That's not a valid choice.\n");
            printf("Let's try again:\n");
            printf("1. Check your balance\n");
            printf("2. Deposit funds\n");
            printf("3. Withdraw funds\n");
            printf("4. Transfer money between accounts\n");
            printf("5. Block an account\n");
            printf("6. Accessing root privileges\n");
            printf("7. Return to main menu\n");
            printf("Please choose an action: ");
            scanf("%d", &gorcoxutyun);
        }

        system("clear");
        switch(gorcoxutyun) {
            case 1: printf("Your account balance: %zu.0 AMD\n\n", account->balance); any_key(); break;
            case 2: deposit(account); break;
            case 3: withdraw(account); break;
            case 4: transfer(account); break;
            // блокировка аккаунта в admin.c, но вызывается здесь
            case 5: {
                extern void block(Account*account, char*arr);
                block(account, &yntrutyun_menu);
                break;
            }
            case 6: {
                extern void root_access(Account* account);
                root_access(account); 
                return;
            }
            case 7: yntrutyun_menu = 'n';
        }
    } while(yntrutyun_menu == 'y');
    system("clear");
    printf("Goodbye, my dear %s\nThank you for using our service.\n", account->owner);
    sleep(3);
    return;
}

void deposit(Account* account) {
    double depositAmount;
    printf("Enter the amount to deposit (minimum 1000): ");
    scanf("%lf", &depositAmount);

    while(depositAmount < 1000) {
        printf("The minimum deposit amount is 1000. Please enter a valid amount: ");
        scanf("%lf", &depositAmount);
    }

    account->balance += depositAmount;
    endo_m->all_money += depositAmount;
    endo_m->transaction++;
    lseek((int)fd_account, off + MONEY_POS, SEEK_SET);
    dprintf((int)fd_account, "%zu.0 AMD", account->balance);
    synco();
    printf("Deposit successful! Your new balance is %zu AMD\n", account->balance);
    sleep(2);
}

void withdraw(Account* account) {
    double amount;
    double commission = 0.01;
    double total;

    printf("Enter the amount to withdraw: ");
    scanf("%lf", &amount);

    total = amount + (amount * commission);

    while(total > account->balance) {
        printf("Insufficient funds. Your balance is %.zu.0 AMD\nEnter a valid amount: ", account->balance);
        scanf("%lf", &amount);
        total = amount + (amount * commission);
    }

    account->balance -= total;
    endo_m->all_money -= total;
    endo_m->transaction++;
    lseek((int)fd_account, off + MONEY_POS, SEEK_SET);
    dprintf((int)fd_account, "%zu.0 AMD", account->balance);
    synco();
    printf("Withdrawal successful!\nYou withdrew %.lf.0 AMD with a 1%% commission.\nYour new balance is %.zu.0 AMD\n", amount, account->balance);
    any_key();
}

void transfer(Account* account) {
    size_t id_transfer;
    double amount;
    char account_data[15] = {'\0'};
    char owner[SIZE_OWNER] = {'\0'};
    char *copy = account_data;
    off_t umic = off;

    printf("Enter the recipient's account ID: ");
    scanf("%zu", &id_transfer);

    if (!log_id(id_transfer)) {
        printf("Recipient account not found!\n");
        any_key();
        return;
    }

    lseek((int)fd_account, off * SIZE + OWNER_POS, SEEK_SET);
    if (read((int)fd_account, owner, SIZE_OWNER - 1) == -1) {
        perror("read");
        exit(1);
    }

    lseek((int)fd_account, off * SIZE + MONEY_POS, SEEK_SET);
    if (read((int)fd_account, account_data, 15) == -1) {
        perror("read");
        exit(1);
    }

    size_t money = my_atoi(&copy);
    printf("Enter the amount to transfer: ");
    scanf("%lf", &amount);

    double commission = amount * 0.01;
    double total_deduction = amount + commission;

    if (total_deduction > account->balance) {
        printf("Insufficient funds. Your balance is %.zu.0 AMD\n", account->balance);
        any_key();
        return;
    }

    account->balance -= total_deduction;
    money += amount;
    endo_m->transaction++;
    endo_m->all_money -= total_deduction - amount;
    synco();

    lseek((int)fd_account, umic + MONEY_POS, SEEK_SET);
    dprintf((int)fd_account, "%zu.0 AMD", account->balance);

    lseek((int)fd_account, off * SIZE + MONEY_POS, SEEK_SET);
    dprintf((int)fd_account, "%zu.0 AMD", money);

    synco();

    printf("Transfer successful! You transferred %.lf.0 AMD + 1%% comission to %s.\nYour new balance is %.zu.0 AMD\n", amount, owner, account->balance);
    any_key();
}
