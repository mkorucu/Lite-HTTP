#include "Lite_Http.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {int main();}
#endif
    // http://webhook.site/241a6792-c015-4b07-9c5e-d965c39cabd0
int main()
{
    char *ip_str = "46.4.105.116";
    int socketFd;

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sockAddr = {
        .sin_addr.s_addr = inet_addr(ip_str),
        .sin_family = AF_INET,
        .sin_port = htons(80),
    };
    printf("Connect return %d\n",connect(socketFd, (const struct sockaddr *)&sockAddr, sizeof(sockAddr)));

    Lite_Http lite_http = Lite_Http(1024);

    char *buff, resv_buff[1024];

    //buff = (char *)lite_http.fast_post("/241a6792-c015-4b07-9c5e-d965c39cabd0", "webhook.site", 5, (uint8_t *)"Selam");
    //buff = (char *)lite_http.fast_get("/241a6792-c015-4b07-9c5e-d965c39cabd0", "webhook.site");
    lite_http.create_request(GET, "/241a6792-c015-4b07-9c5e-d965c39cabd0");
    lite_http.add_header("Host", "webhook.site");
    lite_http.add_header("Content-Length", 5);
    lite_http.add_header("Content-Type", "text/html");
    lite_http.add_header("Connection", "close");
    lite_http.add_body((uint8_t *)"komşular", sizeof("komşular"));
    buff = (char *)lite_http.serialize();
    printf("/==START==\\\n%s\n/==END==\\\n", buff);
    send(socketFd, buff, strlen(buff), 0);
    recv(socketFd, resv_buff, 1024, 0);
    printf("/==RECEIVED==\\\n%s\n/==END==\\\n", resv_buff);
}