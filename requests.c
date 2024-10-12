#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *query_params,
                          char **cookies, int cookies_count, char *jwt_token)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "GET %s/%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (cookies != NULL && cookies_count > 0) {
        strcat(message, "Cookie: ");
        for (int i = 0; i < cookies_count; ++i) {
            strcat(message, cookies[i]);
            if (i < cookies_count - 1) {
                strcat(message, "; ");
            }
        }
        strcat(message, "\r\n");
    }

    if (jwt_token != NULL) {
        sprintf(line, "Authorization: Bearer %s", jwt_token);
        compute_message(message, line);
    }

    compute_message(message, "");
    free(line);
    return message;
}


char *compute_post_request(char *host, char *url, char* content_type, char **body_data,
                           int body_data_fields_count, char **cookies, int cookies_count, char *jwt_token)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    for (int i = 0; i < body_data_fields_count; ++i) {
        strcat(body_data_buffer, body_data[i]);
        if (i < body_data_fields_count - 1) {
            strcat(body_data_buffer, "&");
        }
    }
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);
    sprintf(line, "Content-Length: %ld", strlen(body_data_buffer));
    compute_message(message, line);

    if (cookies != NULL && cookies_count > 0) {
        strcat(message, "Cookie: ");
        for (int i = 0; i < cookies_count; ++i) {
            strcat(message, cookies[i]);
            if (i < cookies_count - 1) {
                strcat(message, "; ");
            }
        }
        strcat(message, "\r\n");
    }

    if (jwt_token != NULL) {
        sprintf(line, "Authorization: Bearer %s", jwt_token);
        compute_message(message, line);
    }

    strcat(message, "\r\n");
    strcat(message, body_data_buffer);

    free(line);
    free(body_data_buffer);
    return message;
}

char* compute_delete_request(char *host, char *url, char *query_params,
                          char **cookies, int cookies_count, char *jwt_token)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "DELETE %s/%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }
    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (cookies != NULL && cookies_count > 0) {
        strcat(message, "Cookie: ");
        for (int i = 0; i < cookies_count; ++i) {
            strcat(message, cookies[i]);
            if (i < cookies_count - 1) {
                strcat(message, "; ");
            }
        }
        strcat(message, "\r\n");
    }

    if (jwt_token != NULL) {
        sprintf(line, "Authorization: Bearer %s", jwt_token);
        compute_message(message, line);
    }

    compute_message(message, "");
    free(line);
    return message;
}

