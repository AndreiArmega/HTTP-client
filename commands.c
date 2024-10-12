#include "commands.h"
#include "helpers.h"
#include "requests.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "utils.h"

void register_command(int sockfd) {
    char *json_info = get_json_info();
    if (json_info == NULL) {
        return;
    }

    // construim mesajul de post
    char *message = compute_post_request(SERVER,
                "/api/v1/tema/auth/register", "application/json", &json_info, 1, NULL, 0, NULL);
    send_to_server(sockfd, message);

    // primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Register failed\n%s\n", payload);  
    } else {
        printf("SUCCESS: Register completed\n");
    }

    // eliberarea memoriei
    free(json_info);
    free(message);
    free(response);
    free(payload);
}

char* login(int sockfd) {
    char *json_info = get_json_info();
    if (json_info == NULL) {
        return NULL;
    }

    // Construim mesajul de post
    char *message = compute_post_request(SERVER,
            "/api/v1/tema/auth/login", "application/json", &json_info, 1, NULL, 0, NULL);
    send_to_server(sockfd, message);

    // Primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Login failed\n%s\n", payload);
        // Eliberarea memoriei
        free(json_info);
        free(message);
        free(response);
        free(payload);
        return NULL;
    } else {
        printf("SUCCESS: Login completed\n");
    }

    char *cookie = extract_cookie(response);

    // Eliberarea memoriei
    free(json_info);
    free(message);
    free(response);
    free(payload);

    return cookie;
}

char *enter_library(int sockfd, char* cookie) {
    // construim mesajul de get
    char *message = compute_get_request(SERVER,
                "/api/v1/tema/library/access", NULL, &cookie, 1, NULL);
    send_to_server(sockfd, message);

    // primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Access library failed\n%s\n", payload);
        // eliberarea memoriei
        free(message);
        free(response);
        free(payload);
        return NULL;
    } else {
        printf("SUCCESS: Access library successful\n");
    }

    char *jwt_token = extract_jwt_token(payload);

    // eliberarea memoriei
    free(message);
    free(response);
    free(payload);

    return jwt_token;
}

void get_books(int sockfd, char *jwt_token) {
    // construim mesajul de get
    char *message = compute_get_request(SERVER,
            "/api/v1/tema/library/books", NULL, NULL, 0, jwt_token);
    send_to_server(sockfd, message);

    // primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Get books failed\n%s\n", payload);
    } else {
        printf("SUCCESS: Get books completed\n%s\n", payload);
    }

    // eliberarea memoriei
    free(message);
    free(response);
    free(payload);
}

void get_book(int sockfd, char *jwt_token) {
    char id[LINELEN];
    printf("id=");
    fgets(id, LINELEN, stdin);
    id[strlen(id) - 1] = '\0';

    // verificam daca id-ul este valid
    if (strlen(id) == 0 || !all_digits(id)) {
        printf("Invalid id\n");
        return;
    }

    // construim mesajul de get
    char *message = compute_get_request(SERVER,
                "/api/v1/tema/library/books", id, NULL, 0, jwt_token);
    send_to_server(sockfd, message);

    // primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Get book failed\n%s\n", payload);
    } else {
        printf("SUCCESS: Get book completed\n%s\n", payload);
    }

    // eliberarea memoriei
    free(message);
    free(response);
    free(payload);
}

void logout(int sockfd, char* cookie) {
    // construim mesajul de get
    char *message = compute_get_request(SERVER,
                "/api/v1/tema/auth/logout", NULL, &cookie, 1, NULL);
    send_to_server(sockfd, message);

    // primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Logout failed\n%s\n", payload);
    } else {
        printf("SUCCESS: Logout successful\n");
    }

    // eliberarea memoriei
    free(message);
    free(response);
    free(payload);
}

void add_book(int sockfd, char* jwt) {
    char *json_book = get_json_book();
    if (json_book == NULL) {
        return;
    }

    // construim mesajul de post
    char *message = compute_post_request(SERVER,
                "/api/v1/tema/library/books", "application/json", &json_book, 1, NULL, 0, jwt);
    send_to_server(sockfd, message);

    // primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Add book failed\n%s\n", payload);
    } else {
        printf("SUCCESS: Add book completed\n");
    }

    // eliberarea memoriei
    free(json_book);
    free(message);
    free(response);
    free(payload);
}

void delete_book(int sockfd, char* jwt) {
    char id[LINELEN];
    printf("id=");
    fgets(id, LINELEN, stdin);
    id[strlen(id) - 1] = '\0';

    // verificam daca id-ul este valid
    if (strlen(id) == 0 || !all_digits(id)) {
        printf("Invalid id\n");
        return;
    }

    // construim mesajul de delete
    char *message = compute_delete_request(SERVER, "/api/v1/tema/library/books", id, NULL, 0, jwt);
    send_to_server(sockfd, message);

    // primirea raspunsului de la server
    char *response = receive_from_server(sockfd);
    char *payload = extract_payload_json(response);

    if (strstr(response, "400 Bad Request") != NULL) {
        printf("ERROR : Delete book failed\n%s\n", payload);
    } else {
        printf("SUCCESS: Delete book completed\n");
    }

    // eliberarea memoriei
    free(message);
    free(response);
    free(payload);
}
