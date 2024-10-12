#include <stdio.h>     
#include <stdlib.h>    
#include <string.h> 
#include <errno.h>
#include <arpa/inet.h>

#include "commands.h"
#include "helpers.h"

int main(void)
{   
    char login_cookie[BUFF_LEN];
    memset(login_cookie, 0, BUFF_LEN);
    char jwt_token[BUFF_LEN];
    memset(jwt_token, 0, BUFF_LEN);

    // valori booleani pentru a verifica daca userul este logat si daca are acces la biblioteca
    int logged_in = 0;
    int access_granted = 0;

    int sockfd = -1;

    while (1) {
        // citirea comenzii de la tastatura si eliminarea caracterului newline
        char command[BUFF_LEN];
        memset(command, 0, BUFF_LEN);
        fgets(command, BUFF_LEN, stdin);
        command[strlen(command) - 1] = '\0';

        // deschiderea conexiunii cu serverul
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
        DIE(sockfd < 0, "open_connection");

        if (!strcmp(command, "register")) {
            register_command(sockfd);

        }else if (!strcmp(command, "login")) {
            char *new_cookie = login(sockfd);

            if (new_cookie) {
                strcpy(login_cookie, new_cookie);
                free(new_cookie);
                logged_in = 1;
            }
        } else if (!strcmp(command, "register")) {
            register_command(sockfd);
        } else if (!strcmp(command, "enter_library")) {
            if (!logged_in) {
                printf(INVALID_LOGIN);
                continue;
            }

            char *jwt = enter_library(sockfd, login_cookie);
            if (jwt) {
                strcpy(jwt_token, jwt);
                free(jwt);
                access_granted = 1;
            }

        } else if (!strcmp(command, "get_books")) {
            if (!access_granted) {
                printf(INVALID_LOGIN);
                continue;
            }

            get_books(sockfd, jwt_token);

        } else if (!strcmp(command, "get_book")) {
            if (!access_granted) {
                printf(INVALID_ACCESS);
                continue;
            }

            get_book(sockfd, jwt_token);\

        } else if (!strcmp(command, "add_book")) {
            if (!access_granted) {
                printf(INVALID_ACCESS);
                continue;
            }
            add_book(sockfd, jwt_token);

        } else if (!strcmp(command, "delete_book")) {
            if (!access_granted) {
                printf(INVALID_ACCESS);
                continue;
            }
            delete_book(sockfd, jwt_token);

        } else if (!strcmp(command, "logout")) {
            if (!logged_in) {
                printf(INVALID_LOGIN);
                continue;
            }
            logout(sockfd, login_cookie);
            complete_logout(&logged_in, &access_granted, login_cookie, jwt_token);
        } else if (!strcmp(command, "exit")) {
            break;
        } else {
            printf("Invalid command\n");
        }

        close_connection(sockfd);
        sockfd = -1;
    }
    
    if (sockfd != -1) {
        close_connection(sockfd);
    }

    return 0;
}
