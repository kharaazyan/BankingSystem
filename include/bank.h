#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE_OWNER 25
#define BANK_ACC 20
#define SIZE 101
#define OWNER_POS 6
#define PASS_POS 30
#define STATUS_POS 93
#define NUMBER_POS 55
#define MONEY_POS 77

#define FILE_ACC "passwd.txt"
#define FILE_INFO "metainfo.txt"

typedef enum status {
    INACTIVE, BLOCKED, ACTIVE, ADMIN
} Status;

typedef struct account {
    char owner[SIZE_OWNER];
    char pass[SIZE_OWNER];
    char number[BANK_ACC];
    size_t balance;
    size_t ID;
    Status status;
} Account;

typedef struct metainfo {
    size_t ID;
    size_t acc_count;
    size_t acc_block_count;
    size_t all_money;
    size_t transaction;
} Metainfo;

extern char yntrutyun;
extern size_t fd_metainfo;
extern size_t fd_account;
extern off_t off;
extern Metainfo *endo_m;

#endif // BANK_H
