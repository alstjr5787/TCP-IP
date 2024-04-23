#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // linux 라이브러리
#include <arpa/inet.h> // ip(host) 라이브러리
#include <sys/socket.h> // socket 라이브러리
#include <stdbool.h> // 1 -> true, 0 -> false

int main(int argc, const char* args[])
{
    int server_sock = 0; // socket -> VFS (Virtual File System) -> 정숫값
    int client_sock = 0;
    struct sockaddr_in server_addr; // server imformation
    struct sockaddr_in client_addr; // client imformation
    
    socklen_t client_addr_size = 0UL; // client 주소 사이즈 
    // 서버가 클라이언트에게 환영합니다.
    const char* message = "Welcome My Server";
    if (argc != 2)
    {
        printf("You have a wrong command \r\n");
        printf("./HELLO_SERVER 127.0.0.1 9999\r\n");
        return -1;
    }
    server_sock = socket(PF_INET, SOCK_STREAM, 0); // ( IPv4, TCP, 0)
    if(server_sock == -1) 
    {
        printf("SOCKET() error\r\n");
        return -1;    
    }
    memset(&server_addr, 0, sizeof server_addr); // server_addr 사이즈만큼 0으로 초기화
    memset(&client_addr, 0, sizeof client_addr); // client_addr 사이즈만큼 0으로 초기화
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    server_addr.sin_port = htons(atoi(args[1]));

    int bind_state = bind(server_sock, (const struct sockaddr*)&server_addr, sizeof server_addr);
    if(bind_state == -1)
    {
        printf("BIND() error\r\n");
        return -1;
    }
    int listen_state = listen(server_sock, 5);
    if(listen_state == -1)
    {
        printf("LISTEN() error\r\n");
        return -1;
    }
    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size); // blocking
    if(client_sock == -1)
    {
    printf("ACCEPT() error\r\n");
    return -1;
    }
    write(client_sock, message, sizeof message);             
    close(client_sock);
    close(server_sock);

    return 0;
}
