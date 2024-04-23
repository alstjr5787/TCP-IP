#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUFSIZ];
    int str_len;
    struct sockaddr_in server_addr;

    if(argc != 3)
    {
        printf("Using : %s 192.168.0.7 9999\r\n", argv[0]);
        exit(1);
    }

    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        error_handling("socket() error");
        return -1;
    }


// 미작성 코드
