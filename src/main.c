#include "../include/bank.h"
#include "../include/functions.h"

char yntrutyun = 'y';
size_t fd_metainfo;
size_t fd_account;
off_t off;
Metainfo *endo_m = NULL;

int main() {
    signal(SIGTERM, endo);
    signal(SIGINT, endo);
    Metainfo metainfo;
    endo_m = &metainfo;
    char metainfo_c[SIZE*2] = {'\0'};
    fd_metainfo = open(FILE_INFO, O_RDWR | O_CREAT, 0664);
    fd_account = open(FILE_ACC, O_RDWR | O_CREAT, 0664);

    if(fd_metainfo == (size_t)-1 || fd_account == (size_t)-1){
        perror("open");
        exit(1);
    }

    if(read(fd_metainfo, metainfo_c, SIZE * 2) == 0){
        dprintf((int)fd_metainfo, "\t\t\t\t\t\t\tMetainformation:\n");
        metainfo.ID = 1;
        metainfo.acc_count = 0;
        metainfo.acc_block_count = 0;
        metainfo.all_money = 0; 
        metainfo.transaction = 0;
        dprintf((int)fd_account, "ID:   Owner:                  Password:                Number:               Balance:        Status:\n");
    } else {
        metaread(metainfo_c, &metainfo);
    }

    system("clear");
    printf("Welcome to Kharazyan Bank!\n");
    printf("Your gateway to stellar financial services.\n");
    sleep(2);

    do {
        system("clear");
        Account account = {0};
        int gorcoxutyun;
        printf("Main Menu:\n");
        printf("1. Register a new user\n");
        printf("2. View registered users\n");
        printf("3. Login as a user\n");
        printf("4. Exit\n");
        printf("Please enter your choice: ");
        scanf(" %d", &gorcoxutyun);

        while(gorcoxutyun < 1 || gorcoxutyun > 4) {
            system("clear");
            printf("Invalid choice! Let's try again.\n");
            printf("Main Menu:\n");
            printf("1. Register a new user\n");
            printf("2. View registered users\n");
            printf("3. Login as a user\n");
            printf("4. Exit\n");
            printf("Please enter your choice: ");
            scanf("%d", &gorcoxutyun);
        }

        int log = 0;
        switch(gorcoxutyun) {
            case 1: grancum(&metainfo); break;
            case 2: ogtaterer(); break;
            case 3:
                log = mutq(&account);
                switch(log) {
                    case 0: admin_menu(&account); break;
                    case 1: acc_menu(&account); break;
                }
                break;
            case 4: yntrutyun = 'n'; break;
        }
    } while(yntrutyun == 'y');

    raise(SIGTERM);
    return 0;
}
