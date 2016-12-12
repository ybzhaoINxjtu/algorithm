#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

int bubbleSort(int cnt, int * a);
int swap(int *x, int *y); 
void printResult(int cnt, int * a);


int bubbleSort(int cnt, int * a)
{
  printf("enter bubbleSort \n");
#if 0
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
#endif
    int i, border, breakIndex = cnt - 1;

    while(breakIndex > 0) {
        
        border = breakIndex;
        breakIndex = 0; //No swap happens means no need to do anymore sort 

        for(i = 0;i < border;i++) {
            if(a[i] > a[i+1]) {
                swap(&a[i], &a[i+1]);
                breakIndex = i; //the last time swap means from the index to the end, it already sorted
            }
        }
    
    }

    return 0;
}

int insertSort(int cnt, int * a)
{
    int i, j;
    
    printf("enter insertSort \n");
    
    for(i = 1; i < cnt;i++) {
        for(j = i;j > 0 && a[j-1] > a[j]; j--) {
            swap(&a[j-1], &a[j]);
        }
    
    }

    return 0;
}

int mergeArray(int * a, int start, int end, int mid, int * temp)
{
    int i, j, len, k = 0;
    i = start;
    len = end - start + 1;
    j = mid + 1;

    while(i <= mid && j <= end) {

      if(a[i] <= a[j]) {
          temp[k++] = a[i++]; 
      } else {
          temp[k++] = a[j++]; 
      }
    }

    while(i <= mid) {
        temp[k++] = a[i++];
    }

    while(j <= end) {
        temp[k++] = a[j++];
    }

    for(k = 0;k < len;k++) {
         a[start + k] = temp[k];
    }

    return 0;
}

int mergeSort(int * a, int start, int end, int *temp)
{
    int mid, i = start;
    int j = end;

    if(i < j) {
        mid = (i + j) / 2;
        mergeSort(a, i, mid, temp);
        mergeSort(a, mid + 1, j, temp);
        mergeArray(a, i, j, mid, temp);
    }
    
    return 0;
}

int partition(int *a, int left, int right)
{
   int i, j, pivot;
   i = left;
   j = right;
   
   pivot = a[i];

   while(i < j) {
      while(i < j && pivot <= a[j]) {
          j--;
      }

      if(i < j) {
          swap(&a[i++], &a[j]);
          //i++;
      }
      
      while(i < j && a[i] < pivot){
          i++;
      }

      if(i < j) {
          swap(&a[i], &a[j--]);
         // j--;
      }

   }

   a[i] = pivot;

   return i;
}

int quickSort(int *a, int l, int r)
{
  int i = l;
  int j = r;
  int k = 0;

  k = partition(a,l,r);
  if(l < k - 1) quickSort(a,l,k - 1);
  if(k + 1 < r) quickSort(a,k + 1, r);

  return 0;
}

int min_heapUp(int * a, int cnt)
{
    int i;

    for(i = cnt;i > 0 && a[i] > a[(i-1)/2];i = (i-1)/2) {
        swap(&a[i], &a[(i-1)/2]);
    }

    return 0;
}

int min_heapAdd(int * a, int cnt, int b)
{
    a[cnt] = b;
    min_heapUp(a, cnt);

    return 0;
}

void MinHeapFixdown(int a[], int i, int n)  
{  
    int j, temp;  
  
    temp = a[i];  
    j = 2 * i + 1;  
    while (j < n)  
    {  
        if (j + 1 < n && a[j + 1] < a[j]) //在左右孩子中找最小的  
            j++;  
  
        if (a[j] >= temp)  
            break;  
  
        a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点  
        i = j;  
        j = 2 * i + 1;  
    }  
    a[i] = temp;  
} 

int min_heapDown(int *a, int cnt, int start)
{
    int parent, min, child;
    
    parent = start;

    child = 2 * parent + 1;
    
    while(child <= cnt) {

      min = a[child];
      
      if(((child + 1) <= cnt) && a[child] > a[child + 1]) min = a[++child];

      if(min > a[parent]) break;

      swap(&a[child], &a[parent]);

      parent = child;
    
      child = 2 * parent + 1;
    }

    return 0;
}

int min_heapDel(int *a, int cnt)
{
    swap(&a[0], &a[cnt]);
    min_heapDown(a, cnt - 1, 0);//cnt -1
    //MinHeapFixdown(a, 0, cnt - 1);
    return 0;
}

int min_heapSort(int *a, int cnt)
{
    int i;
    for(i = (cnt - 1) / 2;i >= 0;i--) { // start and end
       min_heapDown(a, cnt, i);
      //  MinHeapFixdown(a, i, cnt);
    }
   
    for(i = cnt;i > 0;i--){// start and end

        min_heapDel(a, i);
    }

    return 0;
}

int findDupNum(int *a, int num)
{
    int i, index;
    for(i = 0;i < num; i++) {
        index = (a[i] > num? a[i] - num : a[i]);//using radix sort concept

        if(a[index] > num) { // already found once
            return index;
        } else {
            a[index] += num; 
        }
    }

    return -1;
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

  printf("\n");

  return;
}

void main(int argc, char * argv[])
{
    int b[] = {2, 5, 2, 8, 3, 4, 3, 1, 0};
    int a[] = {9, 12, 17, 30, 50, 20, 60, 65, 4, 19, 18};
    //int a[] = {5,2,3,2342,34,56,674,8768,12,414,3452};
    int * p = (int *) malloc(sizeof(a));
    
   // min_heapSort(a, sizeof(a)/sizeof(int) - 1);
    //quickSort(a, 0, sizeof(a)/sizeof(int) - 1);
    //mergeSort(a, 0, sizeof(a)/sizeof(int) - 1, p);
    //bubbleSort(sizeof(a)/sizeof(int), a);
    //insertSort(sizeof(a)/sizeof(int), a);
    printf("the repeated num is %d \n",findDupNum(b, sizeof(b)/sizeof(int)));
    printResult(sizeof(a)/sizeof(int), a);
    
    free(p);
    
    return;
}
