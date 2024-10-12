#ifndef _UTILS_ 
#define _UTILS_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SERVER "34.246.184.49:8080"
#define HOST "34.246.184.49"
#define PORT 8080
#define BUFF_LEN 1000
#define INVALID_ACCESS "ERROR: You must be logged in and have access to the library!\n"
#define INVALID_LOGIN "ERROR: You must be logged in!\n"
#define DIE(assertion, call_description) \
    do {                                \
        if (assertion) {                \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__); \
            perror(call_description);    \
            exit(errno);                \
        }                               \
    } while (0)


// functie care verifica daca un string contine doar cifre
int all_digits(char *str);

// functie care extrage payload-ul json dintr-un mesaj http
char *extract_payload_json(char *response);

// functie care extrage cookie-ul dintr-un mesaj http
char* extract_cookie(char *response);

// functie care extrage token-ul jwt dintr-un mesaj http
char *extract_jwt_token(char *response);

// functie care construieste un json cu informatiile userului pe care
// le citim de la tastatura
char *get_json_info();

// functie care construieste un json cu informatiile cartii pe care
// le citim de la tastatura
char *get_json_book();

// reseteaza accesul si logarea userului
void complete_logout(int* logged_in, int* access_granted, char* login_cookie, char* jwt_token);



#endif