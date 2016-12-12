#include <stdio.h>
#include <math.h>
void printResult(int cnt, int * a);

int constructArray(int *a, int *b, int cnt)
{
    int i;

    b[0] = 1;

    for(i = 1;i < cnt;i++) {
        b[i] = b[i - 1] * a[i - 1];
    }

    for(i = cnt - 1;i > 0;i--) {
        b[i] *= b[0];
        b[0] *= a[i];
    }

    return 1;
}

int my_abs(int a)
{
    int i = a >> 31;//right shift -1 or 0 since int
    
    return ((a ^ i) - i); 
}

int findTargetNum(int * a, int cnt, int tar)
{
    int index = 0;

    while(index < cnt) {
       index += my_abs(tar - a[index]);// tricky index +=
       if(a[index] == tar) return index;   
    }

    return -1;
}

void printResult(int cnt, int * a)
{
  int i;
  for(i = 0;i < cnt;i++) printf("%d ", a[i]);

  printf("\n");

  return;
}


void main(int argc, int argv)
{
    int b[5] = {1,1,1,1,1};
    int a [] = {7, 8, 9, 8, 7, 6, 5, 4, 3};

    //constructArray(a, b, sizeof(a)/sizeof(int));
    printf("the location is %d \n",findTargetNum(a, sizeof(a)/sizeof(int), 7));
    //printResult(sizeof(a)/sizeof(int), b);

    return;
}
