#include "../include/Test_SpecialPoins.h"
#include "../include/Minunit.h"
#include "../include/SpecialPoints.h"

#include <stdio.h>

static char * test_solve_linear_eqation(const double A, const double B, SpecialPoint *sPoint, const int answer) {
    mu_assert("error, foo != 7", answer == solve_linear_eqation(A, B, sPoint));
    return 0;
}

static char * all_tests() {
    Vector * vector = create_vector(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    SpecialPoint * sPoint = create_SpecialPoint(vector);
    mu_run_test(test_solve_linear_eqation(2.0, 4.0, sPoint, 3));
    return 0;
}

void Test_SpecialPoints( void ){

}

/*
  int tests_run = 0;

 int foo = 7;
 int bar = 4;

 static char * test_foo() {
     mu_assert("error, foo != 7", foo == 7);
     return 0;
 }

 static char * test_bar() {
     mu_assert("error, bar != 5", bar == 5);
     return 0;
 }

 static char * all_tests() {
     mu_run_test(test_foo);
     mu_run_test(test_bar);
     return 0;
 }

 int main(int argc, char **argv) {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);

     return result != 0;
 }
 */