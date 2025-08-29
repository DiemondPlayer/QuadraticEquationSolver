#include <cstdio>
#include <math.h>
#include "io/io.h"
#include "util/assert.h"

static void clearInput();

Coeffs inputCoeffs() {
    double a = NAN, b = NAN, c = NAN;
    printf("\nEnter coefficients of the equation (a, b, c): ");
    while (scanf("%lg %lg %lg", &a, &b, &c) != 3) {
        printf("\nERROR! Some input was not a valid coefficient! Try again!");
        printf("\nEnter coefficients of the equation (a, b, c): ");
        clearInput();
    }
    return {.a = a, .b = b, .c = c};
}

void printCoeffs(Coeffs coeffs) {
    feedbackAssert(!isnan(coeffs.a) && !isnan(coeffs.b) && !isnan(coeffs.c),
                    "\n[ERROR]: Provided a nan double inside Coeffs to printCoeffs()");

    printf("\nThe coefficients have been determined as such:"
           "\na = %lg"
           "\nb = %lg"
           "\nc = %lg", coeffs.a, coeffs.b, coeffs.c);
}

void printRoots(Roots roots) {
    switch (roots.rootNumber) {
        case NO_ROOTS:
            printf("\nThe given equation has no real roots :(");
            break;
        case ONE_ROOT:
            if (isnan(roots.x2)) {
                printf("\nThe given equation is deemed linear!"
                       "\nThe given equation has only one root:"
                       "\nx = %lg", roots.x1);
            } else {
                printf("\nThe given equation has one distinct real root:"
                       "\nx1 = x2 = %lg", roots.x1);
            }
            break;
        case TWO_ROOTS:
            printf("\nThe given equation has two distinct real roots:"
                   "\nx1 = %lg"
                   "\nx2 = %lg", roots.x1, roots.x2);
            break;
        case INFINITE_ROOTS:
            printf("\nThe given equation has infinite amount of "
                   "real distinct roots (any x will do) :O");
            break;
        case NOT_DEFINED:
            feedbackAssert(false, "\n[ERROR]: Caught a NOT_DEFINED case "
                                  "in switch(rootNumber) in printRoots()");
            break;
        default:
            feedbackAssert(false, "\n[ERROR]: No valid case found "
                                  "for switch(rootNumber) in printRoots()");
    }
}

bool askToContinue() {
    char c = '\0';
    printf("\nDo you want to solve another equation?"
           "\nEnter y or 1 to continue, anything else to terminate: ");
    scanf(" %c", &c);
    clearInput();
    return c == '1' || c == 'y';
}

//! @brief uses getchar() until it encounters a newline char or EOF
//! @author Leonid Yutlin
static void clearInput() {
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n');
}
