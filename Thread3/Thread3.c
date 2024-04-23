#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD 100

// 증가 스레드의 역할을 하는 함수
void * thread_inc(void * arg);
// 감소 스레드의 역할을 하는 함수
void * thread_des(void * arg);
long long num = 0;

int main(int argc, char *argv[])
{
    pthread_t thread_id[NUM_THREAD]; // 스레드 식별자 배열
    int i;

    printf("sizeof long long: %d\r\n", sizeof(long long)); // long long의 크기 출력
    for(i = 0; i < NUM_THREAD; i++)
    {
        // 인덱스가 홀수인 경우 증가 스레드 생성, 짝수인 경우 감소 스레드 생성
        if(i % 2)
            pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
        else
            pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
    }

    // 모든 스레드가 종료될 때까지 대기
    for(i = 0; i < NUM_THREAD; i++)
        pthread_join(thread_id[i], NULL);

    // 결과 출력
    printf("result: %11d\r\n", num);
    return 0;
}

// 증가 스레드의 역할을 하는 함수
void * thread_inc(void * arg)
{
    int i;
    for(i = 0; i < 50000000; i++)
        num += 1; // num 증가
    return NULL;
}

// 감소 스레드의 역할을 하는 함수
void * thread_des(void * arg)
{
    int i;
    for(i = 0; i < 50000000; i++)
        num -= 1; // num 감소
    return NULL;
}
