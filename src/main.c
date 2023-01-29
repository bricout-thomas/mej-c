#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// first element of the array is its size
// one in two elements is the number of times the prime comes back
// O(sqrt(n)) according to the site I got the function from
// there probably exists better algorithms out there
int* prime_factors(int n) {
  int* results = malloc(sizeof(int)*sqrt(n)*2+1); // probably more memory than necessary
  int j = 0; // number of time the current prime comes back
  int* current_result; // keep track of the current prime position
  current_result = results + 1;

  while (n%2==0){ // allow to get rid of every odd number in the next loop
    j++;
    n/=2;       }
  if (j>0) {
    *current_result = 2;
    current_result++;
    *current_result = j;
    current_result++;
    j=0;
  }
  // main loop of the function
  for (int i=3; i<=sqrt(n); i+=2) {
    while (n%i==0){ 
      j++;
      n/=i;       }
    if (j>0) {
      *current_result = i;
      current_result++;
      *current_result = j;
      current_result++;
      j=0;
    }
  }
  // case were n itself is now a prime number greater than two
  if (n>2) {
    *current_result = n;
    current_result++;
    *current_result = 1;
    current_result++;
  }

  *results = (current_result - results); // the first element is the size of the array, with this element
  return (results); // do not forget to free that once it's been used
}

void test_prime_factors() {
  while (true) {
    int to_test_number = 2;
    printf("Number to test: ");
    scanf("%d", &to_test_number);

    int* results = prime_factors(to_test_number);
    for (int i = 0; i < *results; i++) {
      printf("%d", results[i]);
    }
    printf("\n");
    free(results);
  }
}

// this function helps tell you how many ways you can combine n methods k times of giving you a number without counting twice due to commutativity
// for example ways to write 25 using 5 two times, with two methods for writing five (sum last) is 3 because a*b and b*a is considered the same thing
// see https://stackoverflow.com/questions/11032781/fastest-way-to-generate-binomial-coefficients, I have no idea how the filling the table works
int* gen_binomial_coeff (int target_number, int n_max) {
  int (*table)[target_number] = malloc(target_number * n_max * sizeof(int));
  // we know that k will always be smaller or equal to target_number
  // however, n is the number of methods, since it's what were looking for, the array will be reallocated for n
  // I decided we'll have table[n][k], for easy realloc(), for now it will just fill up to n, whatever you decide it to be
  // see https://stackoverflow.com/questions/23720005/allocate-a-matrix-in-c-using-malloc

  for (int k = 1; k <= target_number; k++)  table[0][k] = 0;
  for (int n = 0; n <= n_max; n++)              table[n][0] = 1;

  for (int n = 1; n <= n_max; n++)
     for (int k = 1; k <= target_number; k++)
        table[n][k] = table[n-1][k-1] + table[n-1][k];
}

int sum_last_poss(int *array, int target) {
  return (1); // todo
}

int mul_last_poss(int *array, int target) {
  return (1); // todo
}

int get_result(int target_number) {

  int *addition = malloc(target_number * sizeof(int));
  int *multiplication = malloc(target_number * sizeof(int));
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
    
    *current_addition = sum_last_poss(multiplication, i);
    *current_multiplication = mul_last_poss(addition, i);
    
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
