#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "utils.h"
#include "helpers.h"

int all_digits(char *str) {
    for (int i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

char* user_info_json(char *username, char *password) {
    char *json = calloc(BUFF_LEN, sizeof(char));
    DIE(json == NULL, "calloc");
    sprintf(json, "{\"username\":\"%s\",\"password\":\"%s\"}", username, password);
    return json;
}

char *extract_payload_json(char *response) {
    char *payload = calloc(BUFF_LEN, sizeof(char));
    DIE(payload == NULL, "calloc");

    char *start = strstr(response, "\r\n\r\n");
    if (start == NULL) {
        return NULL;
    }

    start += strlen("\r\n\r\n");
    strcpy(payload, start);
    return payload;
}

char* extract_cookie(char *response) {
    char *cookie = calloc(BUFF_LEN, sizeof(char));
    DIE(cookie == NULL, "calloc");

    char *start = strstr(response, "Set-Cookie: ");
    if (start == NULL) {
        return NULL;
    }

    start += strlen("Set-Cookie: ");
    char *end = strstr(start, ";");
    if (end == NULL) {
        return NULL;
    }

    strncpy(cookie, start, end - start);
    return cookie;
}

char *extract_jwt_token(char *response) {
    char *jwt_token = calloc(BUFF_LEN, sizeof(char));
    DIE(jwt_token == NULL, "calloc");

    char *start = strstr(response, "token");
    if (start == NULL) {
        return NULL;
    }

    start += strlen("token") + 3;
    char *end = strstr(start, "\"");
    if (end == NULL) {
        return NULL;
    }

    strncpy(jwt_token, start, end - start);
    return jwt_token;
}


char *get_json_info() {
    char username[BUFF_LEN];
    printf("username=");
    fgets(username, BUFF_LEN, stdin);
    username[strlen(username) - 1] = '\0';

    printf("password=");
    char password[BUFF_LEN];
    fgets(password, BUFF_LEN, stdin);
    password[strlen(password) - 1] = '\0';

    if (strlen(username) == 0 || strlen(password) == 0) {
        printf("Invalid username or password\n");
        return NULL;
    }
    // obtinerea json-ului pentru register
    return user_info_json(username, password);
}

char* get_json_book() {
    char title[BUFF_LEN];
    printf("title=");
    fgets(title, BUFF_LEN, stdin);
    title[strlen(title) - 1] = '\0';

    printf("author=");
    char author[BUFF_LEN];
    fgets(author, BUFF_LEN, stdin);
    author[strlen(author) - 1] = '\0';

    printf("genre=");
    char genre[BUFF_LEN];
    fgets(genre, BUFF_LEN, stdin);
    genre[strlen(genre) - 1] = '\0';

    printf("page_count=");
    char page_count[BUFF_LEN];
    fgets(page_count, BUFF_LEN, stdin);
    page_count[strlen(page_count) - 1] = '\0';

    printf("publisher=");
    char publisher[BUFF_LEN];
    fgets(publisher, BUFF_LEN, stdin);
    publisher[strlen(publisher) - 1] = '\0';

    if (strlen(title) == 0 || strlen(author) == 0 || strlen(genre) == 0 ||
                strlen(publisher) == 0 || strlen(page_count) == 0 || !all_digits(page_count)) {
        printf("Invalid book info\n");
        return NULL;
    }

    char *json = calloc(BUFF_LEN, sizeof(char));
    DIE(json == NULL, "calloc");
    sprintf(json,"{\"title\":\"%s\",\"author\":\"%s\",\"genre\":\"%s\",\"page_count\":%s,\"publisher\":\"%s\"}",
        title, author, genre, page_count, publisher);
    return json;
}

void complete_logout(int* logged_in, int* access_granted, char* login_cookie, char* jwt_token) {
    *logged_in = 0;
    *access_granted = 0;
    memset(login_cookie, 0, BUFF_LEN);
    memset(jwt_token, 0, BUFF_LEN);
}
