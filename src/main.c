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

// number of ways there is to write a number using a and a chosen operation
// with n methods for writing a itself and the number of times a is required
// It should become a linked list or a vector of vectors (matrix) or a reallocatable vector of arrays
int* gen_fibonacci_tree(int max_n, int max_i) {
  int* contents = malloc(sizeof(int)*max_n*max_i);
  // fill the n = 0 parts
  for (int i=0; i<max_i; i++) {
    contents[i*max_i] = 0;
  }
  // fill the i = 0 parts
  for (int n=0; n<max_i; n++) {
    contents[n] = 1;
  }
  // fill everything else according to the m(n, i) = m(n-1, i) + m(n, i-1) rule
  for (int i=1; i<max_i; i++) {
    for (int n=1; n<max_n; n++) {
      contents[i*max_i+n] = contents[i*max_i+(n-1)] + contents[(i-1)*max_i+n];
    }
  }
  // return a ptr to the filled fibonacci_tree
  return (contents);
}

int get_fibonacci_tree_value(int* fibonacci_tree, int n, int i, int max_i) {
  return fibonacci_tree[i*max_i+n];
  // todo: make it reallocate and fill the necessary parts
}

int test_fibonacci_tree(int* fibonacci_tree, int max_i) {
  while (true) {
    int n = 2;
    printf("Number of methods: ");
    scanf("%d", &n);

    int i = 2;
    printf("Number of repetitions: ");
    scanf("%d", &i);

    int result = get_fibonacci_tree_value(fibonacci_tree, n, i, max_i);
    printf("Result: %d\n", result);
  }
}

int sum_last_poss(int *array, int target) {
  return (1); // todo
}

int mul_last_poss(int *array, int target) {
  return (1); // todo
}

int get_result(int target_number) {

  int max_i = target_number;
  int precalculation_n = 500;

  int *fibonacci_tree = gen_fibonacci_tree(precalculation_n, max_i);
  test_fibonacci_tree(fibonacci_tree, max_i);

  int *addition = malloc(target_number * sizeof(int));
  int *multiplication = malloc(target_number * sizeof(int));
  // both pointers target the first element of the array, they shouldn't be modified
  // each array cells contains the number of possibilities to write the index+1
  // with the last operation being an addition or a multiplication
  
  int *current_addition;
  int *current_multiplication;
  // these exist for readability and optimisation purpose (replacing multiplication by addition)
  current_addition = addition;
  current_multiplication = multiplication;
  
  // we manually insert the possibilities for 1
  *current_addition = 0; // 1 multiplied by something gives one so in order to keep the pattern poss = add + mul this is set to zero
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
