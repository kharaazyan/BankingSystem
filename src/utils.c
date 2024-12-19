#include "../include/bank.h"
#include "../include/functions.h"

void veracum(char*account){
    for(int i = (int)strlen(account) - 1; i < SIZE_OWNER - 1; i++){
        account[i] = ' ';
    }
    account[SIZE_OWNER - 1] = '\0';
}

void generator(Account* account){
    char arr[BANK_ACC] = {"4318 2900 "};
    int tiv, count = 0, naxkin = -1;
    strcpy(account->number, arr);
    srand((unsigned)time(NULL));
    while(count != 9){
       if(count == 4){
            account->number[count + 10] = ' ';
            count++;
       } else {
            tiv = rand() % 10;
            if(naxkin != tiv){
                account->number[10 + count] = (char)(tiv + '0');
                count++;
            }
            naxkin = tiv;
       }
    }
    account->number[BANK_ACC - 1] = '\0';
    return;
}

void zroacum(char*arr){
    for(int i = 0; i < BANK_ACC; i++){
        arr[i] = '\0';
    }
}

size_t my_atoi(char**arr){
    size_t sum = 0;
    size_t count_local = 0;
    int okay = 0;
    for (int i = 0; (*arr)[i] != '\0'; i++) { 
        while ((*arr)[i] >= '0' && (*arr)[i] <= '9') {
            count_local++;
            sum = sum * 10 + (size_t)((*arr)[i] - '0');
            i++;
            okay = 1;
        }
        if(okay) break;
        if ((*arr)[i] == '\0') break; 
        count_local++;
    }
    (*arr) = &((*arr)[count_local]);
    return sum;
}

void clear(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void endo(int sig){
    synco();
    system("clear");
    printf("Thank you for using Kharazyan Bank!\n");
    exit(0);
}

void any_key(){
    printf("Press Enter to continue...");
    clear();
    getchar();
}
