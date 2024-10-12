#ifndef COMMANDS_H
#define COMMANDS_H

#include "utils.h"

void register_command(int sockfd);

char* login(int sockfd);

char *enter_library(int sockfd, char* cookie);

void get_books(int sockfd, char *jwt_token);

void get_book(int sockfd, char *jwt_token);

void logout(int sockfd, char* cookie);

void add_book(int sockfd, char* jwt);

void delete_book(int sockfd, char* jwt);


#endif // COMMANDS_H