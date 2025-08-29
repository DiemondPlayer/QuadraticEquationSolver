#include <cstdio>
#include <math.h>
#include "io.h"
#include "util.h"

// input
static EquationData inputToEquationData();
static void interpretInput(double* a, double* b, double* c);
static void clearInput();
static bool askToContinue();

// output
static void printRoots(EquationData* eqData);

void handleIO() {
    printf("\nQuadratic equation solving program v1");
    do {
        printf("\n-------------------------------------");
        EquationData eqData = inputToEquationData();
        quadraticEquation(&eqData);
        printRoots(&eqData);
    } while (askToContinue() == true);
    printf("\nCOMMIT GITHUB");
}

static EquationData inputToEquationData() {
    double a = NAN, b = NAN, c = NAN;
    interpretInput(&a, &b, &c);
    printf("\nThe coefficients have been determined as such:"
           "\na = %lg"
           "\nb = %lg"
           "\nc = %lg", a, b, c);
    return {.a = a, .b = b, .c = c}; //остальные станут дефолт значениями
}

static void printRoots(EquationData* eqData) {
    feedbackAssert(eqData, "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(eqData->a) && !isnan(eqData->b) && !isnan(eqData->c),
                    "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

    switch (eqData->rootNumber) {
        case NO_ROOTS:
            printf("\nThe given equation has no real roots :(");
            break;
        case ONE_ROOT:
            if (isnan(eqData->x2)) {
                printf("\nThe given equation is deemed linear!"
                       "\nThe given equation has only one root:"
                       "\nx = %lg", eqData->x1);
            } else {
                printf("\nThe given equation has one distinct real root:"
                       "\nx1 = x2 = %lg", eqData->x1);
            }
            break;
        case TWO_ROOTS:
            printf("\nThe given equation has two distinct real roots:"
                   "\nx1 = %lg"
                   "\nx2 = %lg", eqData->x1, eqData->x2);
            break;
        case INFINITE_ROOTS:
            printf("\nThe given equation has infinite amount of "
                   "real distinct roots (any x will do) :O");
            break;
        case NOT_DEFINED:
            feedbackAssert(false, "\n[ERROR]: Caught a NOT_DEFINED case "
                                  "in switch(rootNumber) in printRoots()");
            break;
            //TODO better msg
        default:
            feedbackAssert(false, "\n[ERROR]: No valid case found "
                                  "for switch(rootNumber) in printRoots()");
    }
}

//! @brief uses getchar() until it encounters a newline char or EOF
//! @author Leonid Yutlin
static void clearInput() {
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n');
}

static void interpretInput(double* a, double* b, double* c) {
    feedbackAssert(a, "\n[ERROR]: Provided a null pointer to interpretInput()!");
    feedbackAssert(b, "\n[ERROR]: Provided a null pointer to interpretInput()!");
    feedbackAssert(c, "\n[ERROR]: Provided a null pointer to interpretInput()!");
    feedbackAssert(a != b && b != c && c != a,
                   "\n[ERROR]: Provided two or more identical pointers to interpretInput()!");

    printf("\nEnter coefficients of the equation (a, b, c): ");
    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        printf("\nERROR! Some input was not a valid coefficient! Try again!");
        printf("\nEnter coefficients of the equation (a, b, c): ");
        clearInput();
    }
}

static bool askToContinue() {
    //баг, ждёт инпут два раза хотя сканирует только первый ответ
    char c = '\0';
    printf("\nDo you want to solve another equation? (y/n or 1/0)");
    scanf(" %c ", &c);
    clearInput();
    return c == '1' || c == 'y';
}
