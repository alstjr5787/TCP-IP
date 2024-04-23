#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h> // true -> 1, false -> 0
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> // system : kernel 라이브러리 : socket.h

int main(int argc, const char* argv[])
{
    //client
    //socket()
    //connect()
    //socket(PF_INET, SOCK_STREAM, 0);
    //connect(sock_fd, (*)&serv_addr, size_t);
    char message[BUFSIZ] = {'\0',};
    if(argc != 3)
    {
        printf("%s\r\n", "./TCP_CLIENT 192.168.0.7 9999");
        exit(1); // 비정상 종료  return -1 과 같음
    }
    const int sock_fd = socket(PF_INET, SOCK_STREAM,0);
    printf("SOCK FD : %d\r\n", sock_fd); // 0~2 이외의 값이 출력될것
    if(sock_fd == -1)
    {
        printf("%s\r\n", "socket() error");
    
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof serv_addr); // 구조체 serv_addr을 모두 0으로 초기화
    // 서버주소 넣어주기
    serv_addr.sin_family = PF_INET; // 원래는 AF_INET : IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // "192.168.0.7" -> bit값으로 바꿈
    serv_addr.sin_port = htons(atoi(argv[2])); // "9999" -> bit값으로 바꿈
    if((connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof serv_addr)) == -1)
    {
        printf("%s\r\n", "connect() error");
        exit(1);
    }
    int read_length = 0;
    int index = 0;
    int str_len = 0;
    while(read_length = read(sock_fd, &message[index++], sizeof(char))) // 값이 있을 때 까지 계속 읽어라
    {
        if(read_length == -1) printf("read() error");
        str_len += read_length;
    }
    printf("%s\r\n", message);
    printf("%d\r\n", str_len);
    close(sock_fd);


    return 0;
}
