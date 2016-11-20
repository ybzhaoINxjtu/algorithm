#include<stdio.h>

int bubbleSort(int cnt, int * a);
int swap(int *x, int *y); 
void printResult(int cnt, int * a);

void main(int argc, char * argv[])
{
    int a[6] = {1,3,11,15,113,118};

    bubbleSort(sizeof(a)/sizeof(int), a);
    printResult(sizeof(a)/sizeof(int), a);
}

int bubbleSort(int cnt, int * a)
{
    int i, quickbreak, border = cnt - 1;

    if(NULL == a) return -1;

    while(border > 0) {
        quickbreak = 1;
        for(i = 0; i < border; i++) {
            if(a[i] > a[i + 1]) {
              swap(&a[i], &a[i + 1]);
              quickbreak = 0 ; //tricky!!! means already sorted, could break 
            }
        }
        if(quickbreak) break;

        border--;
    }
    printf("Bubble sort over, swap times is %d \n", cnt - 1 - border);
  
    return 0;
}

int swap(int * x, int * y)
{
    if(NULL == x || NULL == y) {
        return -1;
    }

    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

  
void printResult(int cnt, int * a)
{
  int i;
  for(i = 0;i < cnt;i++) printf("%d ", a[i]);
}
