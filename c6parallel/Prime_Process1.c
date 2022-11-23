#include<stdio.h>
#include <windows.h>

int num1=0;

int main(){
    char str[50];
    int a[2]={2,5000};
    int i,j;
    for(i=a[0];i<=a[1];i++) {
        int flag=0;
        for(j=2;j*j<=i;j++) {
            if(i%j==0) {
                flag=1;
                break;
            }
        }
        if(!flag) {
            num1++;
        }
    }
    sprintf(str, "prime_Process1¼ÆËãËØÊı£º%d¸ö\n", num1);
    char echoStr[30] = "echo ";
    system(strcat(echoStr, str));
    system("pause");
}
