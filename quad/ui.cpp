#include <cstdio>
#include "ui.h"
#include "feedbackAssert.h"
#include "polynomial.h"

static const int UNKNOWN_ERROR = 1; /* returned by printRoots() in
                            case none of the switches work */
static const int NO_ERRORS = 0; /* returned by printRoots() in case
                            the program finishes without any errors */

static void interpretInput(double coeffs[]);
static void clearInput();

void determineCoefficients(double coeffs[]) {
    feedbackAssert(&coeffs[0], "ERROR: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(&coeffs[1], "ERROR: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(&coeffs[2], "ERROR: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(&coeffs[0] != &coeffs[1] && &coeffs[1] != &coeffs[2] && &coeffs[2] != &coeffs[0],
                "ERROR: Provided two or more identical pointers to determineCoefficients()!");

    printf("Quadratic equation solving program v1\n"
           "-------------------------------------\n");
    interpretInput(coeffs);
    printf("The coefficients have been determined as such:\n"
           "a = %lg\n"
           "b = %lg\n"
           "c = %lg\n", coeffs[0], coeffs[1], coeffs[2]);
}

int printRoots(int numberOfRoots, double roots[], bool isLinear) {
    switch (numberOfRoots) {
        case 0:
            printf("The given equation has no real roots :(");
            break;
        case 1:
            if (isLinear) {
                printf("The given equation is deemed linear!\n"
                        "The given equation has only one root:\n"
                        "x = %lg", roots[0]);
            } else {
                printf("The given equation has one distinct real root:\n"
                        "x1 = x2 = %lg", roots[0]);
            }
            break;
        case 2:
            printf("The given equation has two distinct real roots:\n"
                    "x1 = %lg\n"
                    "x2 = %lg", roots[0], roots[1]);
            break;
        case EQUATION_INFINITE_ROOTS:
            printf("The given equation has infinite amount of "
                    "real distinct roots (any x will do) :O");
            break;
        default:
            printf("ERROR: Unknown error happened");
            return UNKNOWN_ERROR;
    }
    printf("\nCOMMIT GITHUB");
    return NO_ERRORS;
}

//! @brief uses getchar() until it encounters a newline char or EOF
//! @author Leonid Yutlin
static void clearInput() {
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n');
}

static void interpretInput(double coeffs[]) {
    feedbackAssert(&coeffs[0], "ERROR: Provided a null pointer to interpretInput()!");
    feedbackAssert(&coeffs[1], "ERROR: Provided a null pointer to interpretInput()!");
    feedbackAssert(&coeffs[2], "ERROR: Provided a null pointer to interpretInput()!");
    feedbackAssert(&coeffs[0] != &coeffs[1]
                    && &coeffs[1] != &coeffs[2]
                    && &coeffs[2] != &coeffs[0],
                    "ERROR: Provided two or more identical pointers to interpretInput()!");

    printf("Enter coefficients of the equation (a, b, c): ");
    while (scanf("%lg %lg %lg", &coeffs[0], &coeffs[1], &coeffs[2]) != 3) {
        printf("ERROR! Some input was not a valid coefficient! Try again!\n");
        printf("Enter coefficients of the equation (a, b, c): ");
        clearInput();
    }
}
