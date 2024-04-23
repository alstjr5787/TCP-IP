#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork(); // 새로운 프로세스 생성

    if(pid == 0) // 자식 프로세스인 경우
    {
        puts("Hi I am a child process"); // 자식 프로세스에서 출력
    }
    else // 부모 프로세스인 경우
    {
        printf("Child Process ID : %d \n", pid); // 자식 프로세스의 ID 출력
        sleep(30); // 부모 프로세스가 30초 동안 대기
    }

    // 자식과 부모 프로세스가 모두 실행하는 부분
    if(pid == 0) // 자식 프로세스인 경우
        puts("End child process"); // 자식 프로세스에서 출력
    else // 부모 프로세스인 경우
        puts("End parent process"); // 부모 프로세스에서 출력

    return 0;
}
