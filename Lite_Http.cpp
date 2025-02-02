#include "Lite_Http.h"

Lite_Http::Lite_Http(uint32_t send_buff_size)
{
    send_buff = (uint8_t *)malloc(sizeof(1) * send_buff_size);
}

uint8_t *Lite_Http::fast_post(char *path, char *host_name, uint32_t content_length, uint8_t *body)
{
    cursor = 0;

    cursor += sprintf((char *)send_buff, "POST %s HTTP/1.1\r\nHost: %s\r\nContent-Length: %lu\r\n\r\n", path, host_name, content_length);
    memmove((send_buff + cursor), body, content_length);

    cursor = 0;
    return send_buff;
}

uint8_t *Lite_Http::fast_get(char *path, char *host_name)
{    
    sprintf((char *)send_buff, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host_name);

    return send_buff;
}

void Lite_Http::create_request(http_type type, char *path)
{
    cursor += sprintf((char *)send_buff, "%s %s HTTP/1.1\r\n", type == POST ? "POST" : "GET", path);
}

void Lite_Http::add_header(char *key, int val)
{
    cursor += sprintf((char *)(send_buff + cursor), "%s: %d\r\n", key, val);
}

void Lite_Http::add_header(char *key, char *val)
{
    cursor += sprintf((char *)(send_buff + cursor), "%s: %s\r\n", key, val);
}

void Lite_Http::add_header(char *key, double val)
{
    cursor += sprintf((char *)(send_buff + cursor), "%s: %f\r\n", key, val);
}

void Lite_Http::add_body(uint8_t *body, size_t content_length)
{
    cursor += sprintf((char *)(send_buff + cursor), "\r\n");
    memmove(send_buff + cursor, body, content_length);
}

uint8_t *Lite_Http::serialize()
{
    cursor = 0;
    return send_buff;
}
