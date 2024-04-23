#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

// 스레드가 실행할 함수
void* thread_main(void * arg)
{
    int count = *((int*)arg); // 전달된 매개변수로부터 반복 횟수를 받음
    for(int i = 0; i < count; i++)
    {
        sleep(1); // 1초 대기
        puts("Running thread\r\n"); // 실행 중인 스레드 출력
    }

    // 반환할 메시지 동적 할당
    char* msg = (char*) malloc(sizeof(char)*50);
    strcpy(msg, "Hello, I am thread~\r\n");

    return (void*)msg; // 메시지 반환
}

int main()
{
    pthread_t pthread_id = 0ul; // 스레드 식별자
    int thread_parameter = 5; // 스레드에 전달할 매개변수

    // 새로운 스레드 생성
    const int pthread_state = pthread_create(&pthread_id, NULL, thread_main, (void*)&thread_parameter);
    if(!pthread_state)
    {
        puts("thread error\r\n"); // 오류 처리
        return -1;
    }

    void* return_value = NULL; // 스레드 반환 값
    // 생성한 스레드가 종료될 때까지 기다림
    const int join_state = pthread_join(pthread_id, &return_value);
    if(!join_state)
    {
        puts("join error\r\n"); // 오류 처리
        return -1;
    }

    printf("return value from the thread : %s\r\n", (const char*)return_value); // 스레드에서 반환된 값 출력
    free(return_value); // 반환값 메모리 해제

    return 0;
}
