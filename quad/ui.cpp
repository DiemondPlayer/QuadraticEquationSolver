#include <cstdio>
#include "ui.h"
#include "feedbackAssert.h"

static const int UNKNOWN_ERROR = 1; /* returned by printRoots() in
                            case none of the switches work */
static const int NO_ERRORS = 0; /* returned by printRoots() in case
                            the program finishes without any errors */

static void interpretInput(double coeffs[]);
static void clearInput();

void determineCoefficients(double coeffs[]) {
    feedbackAssert(&coeffs[0], "\n[ERROR]: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(&coeffs[1], "\n[ERROR]: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(&coeffs[2], "\n[ERROR]: Provided a null pointer to determineCoefficients()!");
    feedbackAssert(&coeffs[0] != &coeffs[1] && &coeffs[1] != &coeffs[2] && &coeffs[2] != &coeffs[0],
                "\n[ERROR]: Provided two or more identical pointers to determineCoefficients()!");

    printf("\nQuadratic equation solving program v1"
           "\n-------------------------------------");
    interpretInput(coeffs);
    printf("\nThe coefficients have been determined as such:"
           "\na = %lg"
           "\nb = %lg"
           "\nc = %lg", coeffs[0], coeffs[1], coeffs[2]);
}

int printRoots(RootNumber rootNumber, double roots[], bool isLinear) {
    switch (rootNumber) {
        case NO_ROOTS:
            printf("\nThe given equation has no real roots :(");
            break;
        case ONE_ROOT:
            if (isLinear) {
                printf("\nThe given equation is deemed linear!"
                        "\nThe given equation has only one root:"
                        "\nx = %lg", roots[0]);
            } else {
                printf("\nThe given equation has one distinct real root:"
                        "\nx1 = x2 = %lg", roots[0]);
            }
            break;
        case TWO_ROOTS:
            printf("\nThe given equation has two distinct real roots:"
                    "\nx1 = %lg"
                    "\nx2 = %lg", roots[0], roots[1]);
            break;
        case INFINITE_ROOTS:
            printf("\nThe given equation has infinite amount of "
                    "real distinct roots (any x will do) :O");
            break;
        default:
            feedbackAssert(false, "\n[ERROR]: No valid case found for switch(rootNumber) in printRoots()");
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
    feedbackAssert(&coeffs[0], "\n[ERROR]: Provided a null pointer to interpretInput()!");
    feedbackAssert(&coeffs[1], "\n[ERROR]: Provided a null pointer to interpretInput()!");
    feedbackAssert(&coeffs[2], "\n[ERROR]: Provided a null pointer to interpretInput()!");
    feedbackAssert(&coeffs[0] != &coeffs[1]
                    && &coeffs[1] != &coeffs[2]
                    && &coeffs[2] != &coeffs[0],
                    "\n[ERROR]: Provided two or more identical pointers to interpretInput()!");

    printf("\nEnter coefficients of the equation (a, b, c): ");
    while (scanf("%lg %lg %lg", &coeffs[0], &coeffs[1], &coeffs[2]) != 3) {
        printf("\nERROR! Some input was not a valid coefficient! Try again!");
        printf("\nEnter coefficients of the equation (a, b, c): ");
        clearInput();
    }
}
