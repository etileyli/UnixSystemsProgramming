#include <stdio.h>
// #include "bubblesort.c"

#define ARRAYSIZE 10

extern int count2;

void bubblesort(int a[], int n);
int getcount();

int main(void) {

    // printf("count2: %d\n", count2);
    //
    // count2 = 12;
    // printf("count2: %d\n", count2);

    printf("count: %d\n", count);

    count = 12;
    printf("count: %d\n", count);

   // int i;
   //
   // int a[ARRAYSIZE];
   // printf("Enter %d integers to sort\n", ARRAYSIZE);
   // for (i = 0; i < ARRAYSIZE; i++)
   //    scanf("%d", a+i);
   // printf("Array follows:\n");
   // for (i = 0;i < ARRAYSIZE; i++)
   //    printf("%2d: %4d\n", i, a[i]);
   // bubblesort(a, ARRAYSIZE);
   // printf("Sorted array follows:\n");
   // for (i = 0; i < ARRAYSIZE; i++)
   //    printf("%2d: %4d\n", i, a[i]);
   // printf("Number of ineterchanges: %d\n", getcount());
   return 0;
}
