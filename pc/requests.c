#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *query_params,
                            char **cookies, int cookies_count, char **tokens, int tokens_count)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    if (cookies != NULL) {
        int i = 0;
        while(cookies_count > i ) {
            sprintf(line, "Cookie: %s", cookies[i]);
            compute_message(message, line);
            i++;
        }
    }
    if (tokens != NULL) {
        int i = 0;
        while(tokens_count > i ) {
            sprintf(line, "Authorization: Bearer %s", tokens[i]);
            compute_message(message, line);
            i++;
        }
    }
    compute_message(message, "");
    return message;
}
char *compute_delete_request(char *host, char *url, char *query_params,
                            char **cookies, int cookies_count, char **tokens, int tokens_count)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }

    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    if (cookies != NULL) {
        int i = 0;
        while(cookies_count > i ) {
            sprintf(line, "Cookie: %s", cookies[i]);
            compute_message(message, line);
            i++;
        }
    }
    if (tokens != NULL) {
        int i = 0;
        while(tokens_count > i ) {
            sprintf(line, "Authorization: Bearer %s", tokens[i]);
            compute_message(message, line);
            i++;
        }
    }
    compute_message(message, "");
    return message;
}

char *compute_post_request(char *host, char *url, char* content_type, char **body_data,
                            int body_data_fields_count, char **cookies, int cookies_count, char **tokens, int tokens_count)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
    
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    
    strcpy(body_data_buffer, "");
    for (int i = 0; i < body_data_fields_count; ++i)
    {
        strcat(body_data_buffer, body_data[i]);
        if (i != body_data_fields_count - 1)
            strcat(body_data_buffer, "&");
    }
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);
    sprintf(line, "Content-Length: %ld", strlen(body_data_buffer));
    compute_message(message, line);


    if (cookies != NULL) {
        int i = 0;
        while(cookies_count > i ) {
            sprintf(line, "Cookie: %s", cookies[i]);
            compute_message(message, line);
            i++;
        }

    }
    if (tokens != NULL) {
        int i = 0;
        while(tokens_count > i ) {
            sprintf(line, "Authorization: Bearer %s", tokens[i]);
            compute_message(message, line);
            i++;
        }

    }
    compute_message(message, "");
    memset(line, 0, LINELEN);
    compute_message(message, body_data_buffer);

    free(line);
    return message;
}
