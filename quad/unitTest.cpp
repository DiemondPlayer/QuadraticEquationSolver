#include <stdio.h>
#include <math.h>

#include "unitTest.h"
#include "polynomial.h"
#include "double.h"
#include "feedbackAssert.h"

struct EquationTestData {
    int refNumberOfRoots;
    double coeffs[3], refRoots[2];
};

// quadratics tests
static void testQuadraticEquations(int* passed, int* total);
static void testQuadraticEquation(int* passed, int* total,
                        EquationTestData* eqData);

// linear tests
static void testLinearEquations(int* passed, int* total);
static void testLinearEquation(int* passed, int* total,
                        EquationTestData* eqData);

#define sizer(A) sizeof(A) / sizeof(A[0])

void runUnitTests() {
    printf("Meow ^w^\n");
    int total = 0, passed = 0;

    testQuadraticEquations(&passed, &total);
    testLinearEquations(&passed, &total);

    if (total == passed) {
        printf("All unit tests have ran successfully\n");
    } else {
        printf("(%d/%d) unit tests have ran successfully\n", passed, total);
    }
}

static void testQuadraticEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                    "ERROR: Provided a null pointer to testQuadraticEquations()!");

    static EquationTestData tests[5] = {
        {2, {1, -5, 6}, {2, 3}},
        {1, {1, 2, 1}, {-1, -1}},
        {0, {1, 2, 3}, {NAN, NAN}},
        {1, {1e-10, 2, 1}, {-0.5, NAN}},
        {EQUATION_INFINITE_ROOTS, {0, 1e-10, 1e-10}, {NAN, NAN}}
    };

    for (int i = 0; i < sizer(tests); i++)
        testQuadraticEquation(passed, total, &(tests[i]));
}

static void testQuadraticEquation(int* passed, int* total,
                                EquationTestData* eqData) {
    feedbackAssert(passed && total,
                    "ERROR: Provided a null pointer to testQuadraticEquation()!");

	double roots[2] = {NAN, NAN};

	int numberOfRoots = quadraticEquation(eqData -> coeffs, roots);

    *total = *total + 1;

	if(!(numberOfRoots == eqData -> refNumberOfRoots
        && smartEqual(roots[0], eqData -> refRoots[0], THRESHOLD)
        && smartEqual(roots[1], eqData -> refRoots[1], THRESHOLD))) {
		printf("#%d FAILED: quadraticEquation(%lf, %lf, %lf, ...)"
                " returned %d, x1 = %lf, x2 = %lf\n"
                "(should be numberOfRoots = %d, x1 = %lf, x2=%lf)\n",
                *total, eqData -> coeffs[0], eqData -> coeffs[1], eqData -> coeffs[2],
                numberOfRoots, roots[0], roots[1], eqData -> refNumberOfRoots,
                eqData -> refRoots[0], eqData -> refRoots[1]);
		return;
	}

    *passed = *passed + 1;
}

static void testLinearEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                    "ERROR: Provided a null pointer to testLinearEquations()!");

    static EquationTestData tests[3] = {
        {1, {4, 2}, {-0.5}},
        {EQUATION_INFINITE_ROOTS, {0, 0}, {NAN}},
        {0, {0, 3}, {NAN}}
    };

    for (int i = 0; i < sizer(tests); i++)
        testLinearEquation(passed, total, &(tests[i]));
}

static void testLinearEquation(int* passed, int* total,
                                EquationTestData* eqData) {
    feedbackAssert(passed && total,
                    "ERROR: Provided a null pointer to testLinearEquation()!");

    double x1 = NAN;
	int numberOfRoots = linearEquation(eqData -> coeffs, &x1);

    *total = *total + 1;

	if(!(numberOfRoots == eqData -> refNumberOfRoots
        && smartEqual(x1, eqData -> refRoots[0], THRESHOLD))) {
		printf("#%d FAILED: linearEquation(%lf, %lf, ...)"
                " returned %d, x1 = %lf\n"
                "(should be numberOfRoots = %d, x1 = %lf)\n",
                *total, eqData -> coeffs[0],
                eqData -> coeffs[1], numberOfRoots, x1, eqData ->
                refNumberOfRoots, eqData -> refRoots[0]);
		return;
	}

    *passed = *passed + 1;
}

