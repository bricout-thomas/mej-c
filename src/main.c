#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  // ask the user for the size of the triangle
  int triangle_size = 0;
  printf("Insert triangle size:");
  scanf("%d", &triangle_size);
  
  // draw the triangle
  for (int i=1; i <= triangle_size; i++) {
    for (int j=0; j < i; j++) {
      printf("*");
    }
    printf("\n");
  }

  return (EXIT_SUCCESS);
}
