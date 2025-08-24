#include <cstdio>
#include "ui.h"
#include "feedbackAssert.h"
#include "polynomial.h"

static void interpretInput(double* a, double* b, double* c);
static void clearInput();

void determineCoefficients(double* a, double* b, double* c) {
    feedbackAssert(a, "ERROR: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(b, "ERROR: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(c, "ERROR: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(a != b && b != c && c != a,
                "ERROR: Provided two or more identical pointers to determineCoefficients()!");

    printf("Quadratic equation solving program v1\n"
           "-------------------------------------\n");
    interpretInput(a, b, c);
    printf("The coefficients have been determined as such:\n"
           "a = %lg\n"
           "b = %lg\n"
           "c = %lg\n", *a, *b, *c);
}

int printRoots(int numberOfRoots, double x1, double x2, bool isLinear) {
    switch (numberOfRoots) {
        case 0:
            printf("The given equation has no real roots :(");
            break;
        case 1:
            if (isLinear) {
                printf("The given equation is deemed linear!\n"
                        "The given equation has only one root:\n"
                        "x = %lg", x1);
            } else {
                printf("The given equation has one distinct real root:\n"
                        "x1 = x2 = %lg", x1);
            }
            break;
        case 2:
            printf("The given equation has two distinct real roots:\n"
                    "x1 = %lg\n"
                    "x2 = %lg", x1, x2);
            break;
        case EQUATION_INFINITE_ROOTS:
            printf("The given equation has infinite amount of "
                    "real distinct roots (any x will do) :O");
            break;
        default:
            printf("ERROR: Unknown error happened");
            return UNKNOWN_ERROR;
    }
    return NO_ERRORS;
}

//! @brief uses getchar() until it encounters a newline char or EOF
//! @author Leonid Yutlin
static void clearInput() {
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n');
}

static void interpretInput(double* a, double* b, double* c) {
    feedbackAssert(a, "ERROR: Provided a null pointer to interpretInput()!");
    feedbackAssert(b, "ERROR: Provided a null pointer to interpretInput()!");
    feedbackAssert(c, "ERROR: Provided a null pointer to interpretInput()!");
    feedbackAssert(a != b && b != c && c != a,
                    "ERROR: Provided two or more identical pointers to interpretInput()!");

    printf("Enter coefficients of the equation (a, b, c): ");
    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        printf("ERROR! Some input was not a valid coefficient! Try again!\n");
        printf("Enter coefficients of the equation (a, b, c): ");
        clearInput();
    }
}
