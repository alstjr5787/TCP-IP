#include <stdio.h>
#include <stdlib.h> // # 표준 라이브러리 
#include <string.h>
#include <unistd.h> // linux 시스템 라이브러리 
#include <arpa/inet.h> // "IP" -> IP, "PORT" -> PORT 바이너리타입으로 변환
#include <sys/socket.h> // socket(), bind(), listen(), accept()
#include <stdbool.h> // 1 => true, 0 => false

// publc static void main(String[] args) : Java
int main(int argc, const char* argv[]) // C++: argv, args : Java
{
    if(argc != 3) 
    {
        printf("./HELLO)CLIENT 127.0.0.1 9999\r\n");
        return -1;
    }
    int sock = 0;
    struct sockaddr_in server_sock;
    char message[BUFSIZ] = {'\0',}; // 512 바이트 배열 초기화
    unsigned int  str_length = 0u; // 문자열의 길이
    memset(&server_sock, 0, sizeof server_sock);
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("SOCKET() error \r\n");
        return -1;
    }
    server_sock.sin_family = AF_INET;
    server_sock.sin_addr.s_addr = inet_addr(argv[1]); // "127.0.0.1" -> 바이너리 값
   server_sock.sin_port = htons(atoi(argv[2])); // "9999" -> 바이너리 값
                                                 
    if((connect(sock, (const struct sockaddr*)&server_sock, sizeof server_sock)) == -1)
    {
        printf("CONNET() error\r\n");
    }
    str_length = read(sock, message, sizeof message -1); // read() 함수가 오류가 발생하면 -1 리턴
    if(str_length == -1)
    {
        printf("read() error\r\n");
    
    }
    printf("A message from server : %s \r\n,message");
    close(sock);

    return 0;
}

