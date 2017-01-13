#include <stdio.h>
#include <stdlib.h>


#define DUP_NUM 3

int ffs(int a)
{
  int loc = 0;
  
  if(0 == a) return -1;

  if(!(a & 0xffff)) {
      //first one bit in high 16 bit 
      a >>= 16;
      loc += 16;
  }
  if(!(a & 0xff)) {
      //first one bit in high 8 bit 
      a >>= 8;
      loc += 8;
  }

  if(!(a & 0xf)) {
      //first one bit in high 4 bit 
      a >>= 4;
      loc += 4;
  }

  if(!(a & 0x3)) {
      //first one bit in high 2 bit 
      a >>= 2;
      loc += 2;
  }

  if(!(a & 0x1)) {
      //first one bit in high bit 
      a >>= 1;
      loc += 1;
  }

  return loc;

}

int fls(int a)
{
  int loc = 0;
  
  if(0 == a) return -1;

  if(a & (0xffff << 16)) {
      //high one bit in low 16 bit 
      loc += 16;
      a >>= 16;
  }

  if(a & (0xff << 8)) {
      //high one bit in low 8 bit 
      loc += 8;
      a >>= 8;
  }
  
  if(a & (0xf << 4)) {
      //high one bit in high 4 bit 
      loc += 4;
      a >>= 4;
  }
  
  printf("a is 0x%x \n", a );
  if(a & (0x3 << 2)) {
      //high one bit in high 2 bit
      printf("a is 0x%x \n", a & (0x3 << 2) );
      loc += 2;
      a >>= 2;
  }
  
  if(a & (0x1 << 1)) {
      //high one bit in high bit 
      loc += 1;
  }

  return loc;
}


int my_swap(int *a, int *b)
{
    if(b == a) return -1;

    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;

    return 0;
}

int my_abs(int a)
{
    int i = a >> 31;//right shift -1 or 0 since int
    
    return ((a ^ i) - i); 
}
  
int findLonelyOne(int * a, int len)
{
    int i, b = 0;
    
    for(i=0;i<len;i++) {
        b ^= a[i];
    }

    return b;
}

int findLonelyOneUpdate(int * a, int len, int dupNum)
{
    int i, j, sum, b;

    sum = b = 0;
    
    for(i=0;i<32;i++) {
        sum = 0;
        for(j=0;j<len;j++) {
            if((1 << i) & a[j]) {
                sum ++;
            }
        }
        if(sum % dupNum) b += (1 << i);
    }

    return b;
}


int findLonelyTwo(int * a, int len, int *c, int *d)
{
    int i, b;
    
    b = *c = *d =0;

    for(i=0;i<len;i++) {
        b ^= a[i];
    }

    for(i=0;i<len;i++) {
      if((1 << ffs(b)) & a[i]) {
          *c ^= a[i];
      } else {
          *d ^= a[i];
      }
    }
    
    return b;
}


int binaryReverse(int a)
{
    a = (((a & 0xAAAAAAAA) >> 1) | ((a & 0x55555555) << 1));//
    a = (((a & 0xCCCCCCCC) >> 2) | ((a & 0x33333333) << 2));//
    a = (((a & 0xF0F0F0F0) >> 4) | ((a & 0x0F0F0F0F) << 4));//
    a = (((a & 0xFF00FF00) >> 8) | ((a & 0x00FF00FF) << 8));//
    a = (((a & 0xFFFF0000) >> 16) | ((a & 0x0000FFFF) << 16));//
    
    return a;
}


int countTotalOnes(int a)
{
    a = (((a & 0xAAAAAAAA) >> 1) + (a & 0x55555555));//
    a = (((a & 0xCCCCCCCC) >> 2) + (a & 0x33333333));//
    a = (((a & 0xF0F0F0F0) >> 4) + (a & 0x0F0F0F0F));//
    a = (((a & 0xFF00FF00) >> 8) + (a & 0x00FF00FF));//
    a = (((a & 0xFFFF0000) >> 16) + (a & 0x0000FFFF));//

    return a;
}

int main(int argc, char * argv[])
{
    int c,d,a = 0x07000170;
    int g = 0x07000100;
    int b[] = {1, 3, 5, 4, 3, 5, 1};
    int x[] = {0, 1, 3, 5, 4, 3, 5, 1};
    int y[] = {0,1,2,3,3,2,1,3,1,2,7,0,0};
   
    if(2 == argc) {
        a = atoi(argv[1]);
    }

    //printf("the input is 0x%x, %d, %s \n", a, argc, argv[1]);

    printf("first bit is in the %d bit \n", ffs(g));
    printf("first bit is in the %d bit \n", fls(g));

    printf("the lonely one is %d \n", findLonelyOne(b, sizeof(b)/sizeof(int)));

    findLonelyTwo(x, sizeof(x)/sizeof(int), &c, &d);
    
    printf("the lonely two is %d, %d \n", c, d);

    printf("the lonely one update is %d  \n", findLonelyOneUpdate(y, sizeof(y)/sizeof(int), DUP_NUM));

    printf("the total 1 is %d \n", countTotalOnes(a));
    printf("the binary reverse is 0x%x \n", binaryReverse(a));
   
    a = -20;
    my_swap(&a, &b[2]);
    
    printf("a is %d, b[2] is %d, after abs b[2] is %d \n", a, b[2], my_abs(b[2]));

    return 0;
}
