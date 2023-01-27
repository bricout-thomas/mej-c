#include <stdio.h>
#include <stdlib.h>

int sum_last_poss(int *array) {
  return (1);
}

int mul_last_poss(int *array) {
  return (1);
}

int get_result(int target_number) {

  int *addition = (int*) malloc(target_number * sizeof(int));
  int *multiplication = (int*) malloc(target_number * sizeof(int));
  // both pointers target the first element of the array, they shouldn't be modified
  // each array contains the number of possibilities to write the index+1 number
  // with the last operation being an addition or a multiplication
  
  int *current_addition;
  int *current_multiplication;
  // these exist for readability and optimisation purpose (replacing multiplication by addition)
  current_addition = addition;
  current_multiplication = multiplication;
  
  // we manually insert the possibilities for 1
  *current_addition = 1;
  *current_multiplication = 1;

  // each iterations, we compute the number of possibilities for i
  for (int i=2; i<=target_number; i++) {
    current_addition ++; // the way c works takes care of multiplying 1 by sizeof(int)
    current_multiplication ++;
    
    *current_addition = sum_last_poss(multiplication);
    *current_multiplication = mul_last_poss(addition);
    
    int sum = *current_multiplication + *current_addition;

    printf("possibilities for %d:\n\
mul: %d add: %d total: %d\n", i, *current_multiplication, *current_addition, sum);
  }

  free(addition); free(multiplication);
  return (*current_addition + *current_multiplication);
}

int main(int argc, char *argv[])
{ 
  int target_number = 0;
  printf("Nombre pour lequel l'on cherche le nombre de possibilité dans l'écriture: ");
  scanf("%d", &target_number);
  
  int result = get_result(target_number);
  printf("Le resultat pour %d est: %d", target_number, result);

  return (EXIT_SUCCESS);
}
