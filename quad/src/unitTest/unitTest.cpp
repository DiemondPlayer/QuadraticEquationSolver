#include <stdio.h>
#include <math.h>

#include "unitTest/unitTest.h"
#include "polynomial/polynomial.h"
#include "util/double.h"
#include "util/assert.h"

//better array length macros
#define sizer(A) sizeof(A) / sizeof(A[0])

struct EquationTestData {
    EquationData eqData;
    const Roots refRoots;
};

// quadratics tests
static void testQuadraticEquations(int* passed, int* total);
static void testQuadraticEquation (int* passed, int* total,
                        EquationTestData* test);

// linear tests
static void testLinearEquations(int* passed, int* total);
static void testLinearEquation (int* passed, int* total,
                        EquationTestData* test);

TestFeedback runUnitTests() {
    printf("Meow ^w^");
    int total = 0, passed = 0;

    testQuadraticEquations(&passed, &total);
    testLinearEquations   (&passed, &total);

    if (total == passed) {
        printf("\nAll unit tests have ran successfully");
    } else {
        printf("\n(%d/%d) unit tests have ran successfully", passed, total);
        return FAILED_UNIT_TEST_ERROR;
    }
    return OK;
}

static void testQuadraticEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testQuadraticEquations()!");

    EquationTestData tests[] = {
/*
        {
        .eqData = {.coeffs = {.a = , .b = , .c = }},
        .refRoots = {.refRootNumber = , .refX1 = , .refX2 = }
        },
*/
        {{{.a = 1,     .b = -5,    .c = 6    }}, {TWO_ROOTS,      2,    3  }},
        {{{.a = 1,     .b =  2,    .c = 1    }}, {ONE_ROOT,       -1,   -1 }},
        {{{.a = 1,     .b =  2,    .c = 3    }}, {NO_ROOTS,       NAN,  NAN}},
        {{{.a = 1e-10, .b =  2,    .c = 1    }}, {ONE_ROOT,       -0.5, NAN}},
        {{{.a = 0,     .b = 1e-10, .c = 1e-10}}, {INFINITE_ROOTS, NAN,  NAN}},
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testQuadraticEquation(passed, total, &(tests[i]));

    FILE* filePtr = fopen("src/unitTest/quadraticEquationTests.txt", "r");

    double a = NAN, b = NAN, c = NAN;
    char rootNumberStr[ROOT_NUMBER_STR_LIMIT] = {};
    double refX1 = NAN, refX2 = NAN;

    while (fscanf(filePtr, "%lf %lf %lf %s %lf %lf", &a, &b, &c, rootNumberStr, &refX1, &refX2) == 6) {
        EquationTestData fileDrivenTest = {
            .eqData = {.coeffs = {.a = a, .b = b, .c = c}},
            .refRoots = {.rootNumber = stringToRootNumber(rootNumberStr), .x1 = refX1, .x2 = refX2}
        };
        testQuadraticEquation(passed, total, &fileDrivenTest);
    }

    fclose(filePtr);
}

static void testQuadraticEquation(int* passed, int* total,
                                    EquationTestData* test) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testQuadraticEquation()!");
    feedbackAssert(&(test->eqData),
                   "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(test->eqData.coeffs.a)
                   && !isnan(test->eqData.coeffs.b) && !isnan(test->eqData.coeffs.c),
                   "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

	quadraticEquation(&(test->eqData));

    (*total)++;

	if (!areEqualRoots(test->eqData.roots, test->refRoots)) {
		printf("\n#%d FAILED: quadraticEquation(%lf, %lf, %lf, ...)"
               "\nreturned %s, x1 = %lf, x2 = %lf"
               "\n(should be rootNumber = %s, x1 = %lf, x2=%lf)",
               *total, (test->eqData).coeffs.a, (test->eqData).coeffs.b, (test->eqData).coeffs.c,
               rootNumberToString((test->eqData).roots.rootNumber), (test->eqData).roots.x1, (test->eqData).roots.x2,
               rootNumberToString(test->refRoots.rootNumber),        test->refRoots.x1,       test->refRoots.x2);
		return;
	}

    (*passed)++;
}

static void testLinearEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testLinearEquations()!");

    EquationTestData tests[] = {
/*
        {
        .eqData = {.coeffs = {.a = , .b = , .c = }},
        .refRoots = {.refRootNumber = , .refX1 = , .refX2 = }
        },
*/
        {{{.a = 0, .b = 2, .c = 8}}, {ONE_ROOT,       -4,  NAN}},
        {{{.a = 0, .b = 0, .c = 0}}, {INFINITE_ROOTS, NAN, NAN}},
        {{{.a = 0, .b = 0, .c = 5}}, {NO_ROOTS,       NAN, NAN}},
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testLinearEquation(passed, total, &(tests[i]));

    FILE* filePtr = fopen("src/unitTest/linearEquationTests.txt", "r");

    double b = NAN, c = NAN;
    char rootNumberStr[ROOT_NUMBER_STR_LIMIT] = {};
    double refX1 = NAN;

    while (fscanf(filePtr, "%lf %lf %s %lf", &b, &c, rootNumberStr, &refX1) == 4) {
        EquationTestData fileDrivenTest = {
            .eqData = {.coeffs = {.a = 0, .b = b, .c = c}},
            .refRoots = {.rootNumber = stringToRootNumber(rootNumberStr), .x1 = refX1, .x2 = NAN}
        };
        testQuadraticEquation(passed, total, &fileDrivenTest);
    }

    fclose(filePtr);
}

static void testLinearEquation(int* passed, int* total,
                               EquationTestData* test) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testLinearEquation()!");
    feedbackAssert(&(test->eqData),
                   "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(test->eqData.coeffs.a)
                   && !isnan(test->eqData.coeffs.b) && !isnan(test->eqData.coeffs.c),
                   "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

    linearEquation(&(test->eqData));

    (*total)++;

	if (!areEqualRoots(test->eqData.roots, test->refRoots)) {
		printf("\n#%d FAILED: linearEquation(%lf, %lf, %lf, ...)"
               "\nreturned %s, x1 = %lf, x2 = %lf"
               "\n(should be rootNumber = %s, x1 = %lf, x2=%lf)",
               *total, (test->eqData).coeffs.a, (test->eqData).coeffs.b, (test->eqData).coeffs.c,
               rootNumberToString((test->eqData).roots.rootNumber), (test->eqData).roots.x1, (test->eqData).roots.x2,
               rootNumberToString(test->refRoots.rootNumber),        test->refRoots.x1,       test->refRoots.x2);
		return;
	}

    (*passed)++;
}

