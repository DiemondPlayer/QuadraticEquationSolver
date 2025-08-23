#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define THRESHOLD 1e-9 /* threshold below which difference between doubles are ignored and they are deemed equal */
#define UNKNOWN_ERROR 1 /* returned by main() and printRoots() in case none of the switches work */
#define NO_ERRORS 0 /* returned by main() and printRoots() in case the program finishes without any errors */
#define QUADRATIC_EQUATION_INFINITE_ROOTS (-1) /* returned by quadraticEquation() in case the given equation has infinite amount of roots */

void determineCoefficients(double* a, double* b, double* c);
int printRoots(int numberOfRoots, double x1, double x2, bool isLinear);
bool isEqualDouble(double d1, double d2, double threshold);
int quadraticEquation(double a, double b, double c, double * x1, double * x2);

int main() {
    double a, b, c, x1, x2;
    a = b = c = x1 = x2 = NAN;
    // printf("%lf %lf %lf %lf %lf", a, b, c, x1, x2);
    determineCoefficients(&a,&b,&c);
    int numberOfRoots = quadraticEquation(a, b, c, &x1, &x2);
    return printRoots(numberOfRoots, x1, x2, isEqualDouble(a, 0.0, THRESHOLD));
}

int printRoots(int numberOfRoots, double x1, double x2, bool isLinear){
    switch (numberOfRoots) {
        case 0:
            printf("The given equation has no real roots :(");
            break;
        case 1:
            printf("The given equation has one distinct real root:\n%lg", x1);
            break;
        case 2:
            if (isLinear){
                printf("The given equation is deemed linear!\nThe given equation has only one root:\n%lg", x1);
            }else {
                printf("The given equation has two distinct real roots:\n%lg\n%lg", x1, x2);
            }
            break;
        case QUADRATIC_EQUATION_INFINITE_ROOTS:
            printf("The given equation has infinite amount of real distinct roots (any x will do) :O");
            break;
        default:
            printf("Unknown error happened");
            return UNKNOWN_ERROR;
    }
    return NO_ERRORS;
}

void determineCoefficients(double* a, double* b, double* c) {
    printf("Quadratic equation solving program v1\n"
           "-------------------------------------\n");
    printf("Enter coefficients of the equation (a, b, c): ");
    scanf("%lg %lg %lg", a, b, c);
    printf("The coefficients have been determined as such:\n"
           "a = %lg\n"
           "b = %lg\n"
           "c = %lg\n", *a, *b, *c);
}

//! @brief Checks if two doubles are similar enough in value (similarity is determined by a threshold)
//! @author Leonid Yutlin
//! @param [in] d1 First double to compare
//! @param [in] d2 Second double to compare
//! @param [in] threshold Double (uninclusive) threshold to check for
//! @returns true if doubles are similar enough in value; false if not
bool isEqualDouble(double d1, double d2, double threshold) {
    return fabs(d1 - d2) < fabs(threshold);
}

//! @brief Solves quadratic equation by takin in 3 coefficients of it and putting the roots inside the pointers
//! @author Leonid Yutlin
//! @param [in] a First non-zero coefficient
//! @param [in] b Second coefficient
//! @param [in] c Third coefficient
//! @param [out] x1 Non-null pointer to the first root
//! @param [out] x2 Non-null pointer to the second root
//! @returns Number of distinct real roots of the given quadratic equation; Returns QUADRATIC_EQUATION_INFINITE_ROOTS in case the coefficients are 0,0,0
//! @throws AssertionError:\n If any of the pointers are null \n If pointers are the same pointer
int quadraticEquation(double a, double b, double c,
    double * x1, double * x2) {
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if(isEqualDouble(a, 0.0, THRESHOLD)) {
        if (isEqualDouble(b, 0.0, THRESHOLD)
        && isEqualDouble(c, 0.0, THRESHOLD)) return QUADRATIC_EQUATION_INFINITE_ROOTS;
        *x1 = *x2 = -c/b;
        return 1;
    }
    double discriminant = b*b - 4*a*c;
    *x1 = (-b + sqrt(discriminant))/(2*a);
    *x2 = (-b - sqrt(discriminant))/(2*a);

    if (isEqualDouble(discriminant, 0.0, THRESHOLD)) return 1;
    if (discriminant > 0.0) return 2;
    /* if discriminant < 0.0 */ return 0;
}
