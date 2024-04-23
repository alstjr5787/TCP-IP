#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// 스레드가 실행할 함수
void* thread_main(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id; // 스레드 식별자
    int thread_param = 5; // 스레드에 전달할 매개변수

    // 새로운 스레드 생성
    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)
    {
        puts("pthread_create() error"); // 오류 처리
        return -1;
    };

    sleep(10); // 메인 스레드가 10초 동안 대기
    puts("end of main"); // 메인 스레드 종료
    return 0;
}

// 스레드가 실행할 함수 정의
void* thread_main(void *arg)
{
    int i;
    int cnt = *((int*)arg); // 매개변수로부터 반복 횟수를 받음
    for(i = 0; i < cnt; i++)
    {
        sleep(1); // 1초 대기
        puts("running thread"); // 실행 중인 스레드 출력
    }
    return NULL; // 스레드 종료
}
