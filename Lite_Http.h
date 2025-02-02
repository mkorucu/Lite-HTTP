#ifndef __LITE_HTTP_H
#define __LITE_HTTP_H

//#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

typedef enum http_type_t{
    POST,
    GET,
} http_type;

class Lite_Http
{
    public:
        Lite_Http(uint32_t send_buff_size);
        uint8_t *fast_post(char *path, char *host_name, uint32_t content_length, uint8_t *body);
        uint8_t *fast_get(char *path, char *host_name);
        void create_request(http_type type, char *path);
        void add_header(char *key, int val);
        void add_header(char *key, char *val);
        void add_header(char *key, double val);
        void add_body(uint8_t *body, size_t content_length);
        uint8_t *serialize();
    private:
        uint32_t cursor;
        uint8_t *send_buff;
};
#endif
/*
    yöntem 1:
    buff = (char *)lite_http.fast_post("/241a6792-c015-4b07-9c5e-d965c39cabd0", "webhook.site", 5, (uint8_t *)"Selam");
    buff = (char *)lite_http.fast_get("/241a6792-c015-4b07-9c5e-d965c39cabd0", "webhook.site");

    yöntem 2:
    lite_http.create_request(POST, "/241a6792-c015-4b07-9c5e-d965c39cabd0");
    lite_http.add_header("Host", "webhook.site");
    lite_http.add_header("Content-Length", 5);
    lite_http.add_header("Content-Type", "text/html");
    lite_http.add_header("Connection", "close");
    lite_http.add_body((uint8_t *)"komşular", sizeof("komşular"));
    buff = (char *)lite_http.serialize();

*/