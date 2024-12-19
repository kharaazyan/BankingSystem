#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "bank.h"

void veracum(char* account);
void generator(Account* account);
void zroacum(char* arr);
void endo(int sig);
size_t my_atoi(char** arr);
void clear();
void any_key();

void metaread(char* arr, Metainfo* metainfo);
void grancum(Metainfo* metainfo);
int log_id(size_t ID);
void ogtaterer();
void ogtaterer_block();
void apokalipsis();
void synco();

void admin_menu(Account* account);
void admin_status();
void change_pass();
void root_access(Account* account);
void block(Account* account, char* arr);

int login(char* arr);
int mutq(Account* account);
void acc_menu(Account* account);
void deposit(Account* account);
void withdraw(Account* account);
void transfer(Account* account);

#endif // FUNCTIONS_H
