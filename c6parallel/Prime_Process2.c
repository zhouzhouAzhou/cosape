#include<stdio.h>
#include <windows.h>

int num2=0;

int main(){
    char str[50];
    int a[2]={5001,10000};
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
            num2++;
        }
    }
    sprintf(str, "prime_Process2¼ÆËãËØÊı£º%d¸ö\n",num2);
    char echoStr[30] = "echo ";
    system(strcat(echoStr, str));
    system("pause");
}
