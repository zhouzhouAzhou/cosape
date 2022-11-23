#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/***多线程 ref:https://www.jianshu.com/p/07a4739334e8

***/
/*
void* myfunc(void *args)
{
    printf("Hello world!\n");
    return NULL;
}


int main()
{
    pthread_t th;
    pthread_create(&th,NULL,myfunc,NULL);
    pthread_join(th,NULL);
    printf("Hello world!\n");
    return 0;
}
*/
/*

void* myfunc(void *args)
{
    int i;
    char *name = (char*)args;
    for(i=1;i<50;i++)
    printf("%s:%d\n",name,i);
    return NULL;
}

int main()
{
    pthread_t th1;
    pthread_t th2;

    pthread_create(&th1,NULL,myfunc,"th1");
    pthread_create(&th2,NULL,myfunc,"th2");
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    printf("End!\n");
    return 0;
}


*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[5000];
int s1 = 0; // th1计算的加法和
int s2 = 0; // th2计算的加法和


void *myfunc1(void *args) {
    int i;
    char *name = (char *) args;
    for (i = 1; i < 2500; i++) s1 += arr[i];

    return NULL;
}

void *myfunc2(void *args) {
    int i;
    char *name = (char *) args;
    for (i = 2500; i < 5000; i++) s2 += arr[i];

    return NULL;
}

int main() {
    int i;
    for (i = 0; i < 5000; i++) arr[i] = rand() % 50;

    pthread_t th1;
    pthread_t th2;

    pthread_create(&th1, NULL, myfunc1, NULL);
    pthread_create(&th2, NULL, myfunc2, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("s1 = %d, s2 = %d, s1 + s2 = %d\n", s1, s2, s1 + s2);

    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int s;

pthread_mutex_t lock;

void *myfunc(void *args) {
    int i;
    for (i = 0; i < 5000; i++) {
        pthread_mutex_lock(&lock);
        s++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main() {
    pthread_t th1;
    pthread_t th2;

    // 初始化锁
    pthread_mutex_init(&lock, NULL);

    pthread_create(&th1, NULL, myfunc, NULL);
    pthread_create(&th2, NULL, myfunc, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("s = %d\n", s);

    return 0;
}
*/
/***多进程 https://blog.csdn.net/jaj2003/article/details/123910646
#include <unistd.h>
#include <stdio.h>

#include <stdio.h>
#include<stdlib.h>

void tellEnd()
{
	puts("The end!");
}

int main(void)
{
	atexit(tellEnd);
	puts("exit");
}
***/

/*
#include <stdio.h>
#include<Windows.h>

int main()
{
	system("notepad");
	return(0);
}
*/

/*
#include <stdio.h>
#include<windows.h>
#include<wchar.h>
int main(int argc, char* argv[])
{
 char szCommandLine[] = "son_process.exe";
 STARTUPINFO si = {sizeof(si)};
 PROCESS_INFORMATION pi;
 HMODULE handle;
 int pid;
 int success=CreateProcess(NULL, szCommandLine, NULL, NULL, 0,
CREATE_NEW_CONSOLE | HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi);
//WIN32API函数CreateProcess用来创建一个新的进程和它的主线程，这个新进程运行指定的可执行文件。
 if (success)
 {
 pid = pi.dwProcessId;
 handle = pi.hProcess;
 printf("pid=%ld,hwnd=%d", pid, handle);
 Sleep(1000);
 char str[100] = "";
 sprintf(str, "taskkill /pid %d", pid);
 system(str);
 //TerminateProcess(handle, 0);
 CloseHandle(pi.hThread); //结束新创建主线程句柄
 CloseHandle(pi.hProcess); //结束新创建主进程句柄
 }
 else
 {
 printf("error!!\n");
 }
}*/

