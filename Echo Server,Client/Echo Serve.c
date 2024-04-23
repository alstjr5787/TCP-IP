#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, const char* argv[])
{
    if(argc != 2)
    {
        printf("%s\r\n", "./ECHO_SERVER 9999");
        return -1;
    }

    int server_sock_fd = 0;
    int client_sock_fd = 0;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    memset(&server_addr, 0, sizeof server_addr);
    memset(&client_addr, 0, sizeof client_addr);

    server_sock_fd = socket(PF_INET /*IPv4*/, SOCK_STREAM /*TCP*/, 0);
    printf("SERVER FD : %d\r\n", server_sock_fd); // OPEN
    if(server_sock_fd == -1)
    {
        printf("socket() error\r\n");
        return -1;
    }
    // 번호 받기 IP, PORT
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 127.0.0.1 or 192.168.0.7
    server_addr.sin_port = htons(atoi(argv[1])); // "9999" -> 99_99 뒤바뀌어 들어감
                                                 
    const int bind_state = (server_sock_fd, (const struct sockaddr*)&server_addr, sizeof server_addr);
    if(bind_state == -1)
    {
        printf("bind() error\r\n");
        return -1;
    }

    const int listen_state = listen(server_sock_fd, 5); // 대기자가 5개
    if(listen_state == -1)
    {
        printf("listen() error\r\n");
        return -1;
    }
    int client_addr_size = sizeof client_addr;
    char message[BUFSIZ] = {'\0',};
    for(int i = 0; i < 5; i++) // client를 5개 받겠다
    {
        // OPEN
        client_sock_fd = accept(server_sock_fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);
        printf("CLIENT SOCK FD : %d\r\n", client_sock_fd); // 4
        if(client_sock_fd == -1)
        {
            printf("accept() error\r\n");
            return -1;
        }

        printf("Client is connected ...");
        int str_length = 0;
        while((str_length = read(client_sock_fd, message, BUFSIZ)) != 0)
        {
            write(client_sock_fd, message, str_length);
        }  
       close(client_sock_fd); 
    }
    close(server_sock_fd);
    return 0;
}

