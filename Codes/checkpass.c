#include <stdio.h>
#include <string.h>

int checkpass(void){
  int x;
  char a[9];
  x = 0;

  fprintf(stderr,"a at %p and\nx at %p\n", (void *)a, (void *)&x);
  printf("Enter a short word: ");
  scanf("%s", a);
  if (strcmp(a, "mypass") == 0)
    x = 1;

  return x;
}

int main(int argc, char const *argv[]) {

  printf("result: %d\n", checkpass());

  return 0;
}
