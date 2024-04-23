#include <stdio.h>
#include <unistd.h>

int g_value = 10; // 전역 변수 선언 및 초기화
int main() 
{
    pid_t pid = 0u; // 프로세스 ID 저장 변수 선언 및 초기화
    int l_value = 20; // 지역 변수 선언 및 초기화
    g_value++; // 전역 변수 증가
    l_value += 5; // 지역 변수 증가
    pid = fork(); // 새로운 프로세스 생성
    if(pid == 0) // 자식 프로세스인 경우
    {
        g_value += 2; // 전역 변수 증가
        l_value += 2; // 지역 변수 증가
    }
    else // 부모 프로세스인 경우
    {
        g_value -= 2; // 전역 변수 감소
        l_value -= 2; // 지역 변수 감소
    }
    if(pid == 0) // 자식 프로세스인 경우
    {
        printf("Child Process : %d %d\r\n", g_value, l_value); // 자식 프로세스에서 전역 및 지역 변수 출력
    }
    else // 부모 프로세스인 경우
    {
        printf("Parent Process : %d %d\r\n", g_value, l_value); // 부모 프로세스에서 전역 및 지역 변수 출력
    }
    return 0;
}
