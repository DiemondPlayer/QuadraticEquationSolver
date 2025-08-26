#include <stdio.h>
#include <math.h>

#include "unitTest.h"
#include "polynomial.h"
#include "double.h"
#include "feedbackAssert.h"

struct EquationTestData {
    RootNumber refRootNumber;
    double coeffs[3], refRoots[2];
};

// quadratics tests
static void testQuadraticEquations(int* passed, int* total);
static void testQuadraticEquation(int* passed, int* total,
                        const EquationTestData* eqData);

// linear tests
static void testLinearEquations(int* passed, int* total);
static void testLinearEquation(int* passed, int* total,
                        const EquationTestData* eqData);

#define sizer(A) sizeof(A) / sizeof(A[0])

void runUnitTests() {
    printf("Meow ^w^");
    int total = 0, passed = 0;

    testQuadraticEquations(&passed, &total);
    testLinearEquations(&passed, &total);

    if (total == passed) {
        printf("\nAll unit tests have ran successfully");
    } else {
        printf("\n(%d/%d) unit tests have ran successfully", passed, total);
    }
}

static void testQuadraticEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testQuadraticEquations()!");

    const EquationTestData tests[5] = {
        {TWO_ROOTS, {1, -5, 6}, {2, 3}},
        {ONE_ROOT, {1, 2, 1}, {-1, -1}},
        {NO_ROOTS, {1, 2, 3}, {NAN, NAN}},
        {ONE_ROOT, {1e-10, 2, 1}, {-0.5, NAN}},
        {INFINITE_ROOTS, {0, 1e-10, 1e-10}, {NAN, NAN}}
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testQuadraticEquation(passed, total, &(tests[i]));
}

static void testQuadraticEquation(int* passed, int* total,
                                const EquationTestData* eqData) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testQuadraticEquation()!");

	double roots[2] = {NAN, NAN};

	RootNumber rootNumber = quadraticEquation(eqData->coeffs, roots);

    (*total)++;

	if(!(rootNumber == eqData->refRootNumber
        && smartEqual(roots[0], eqData->refRoots[0], THRESHOLD)
        && smartEqual(roots[1], eqData->refRoots[1], THRESHOLD))) {
		printf("\n#%d FAILED: quadraticEquation(%lf, %lf, %lf, ...)"
                " returned %d, x1 = %lf, x2 = %lf"
                "\n(should be rootNumber = %d, x1 = %lf, x2=%lf)",
                *total, eqData->coeffs[0], eqData->coeffs[1], eqData->coeffs[2],
                rootNumber, roots[0], roots[1], eqData->refRootNumber,
                eqData->refRoots[0], eqData->refRoots[1]);
		return;
	}

    (*passed)++;
}

static void testLinearEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testLinearEquations()!");

    const EquationTestData tests[3] = {
        {ONE_ROOT, {4, 2}, {-0.5}},
        {INFINITE_ROOTS, {0, 0}, {NAN}},
        {NO_ROOTS, {0, 3}, {NAN}}
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testLinearEquation(passed, total, &(tests[i]));
}

static void testLinearEquation(int* passed, int* total,
                                const EquationTestData* eqData) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testLinearEquation()!");

    double x1 = NAN;
	RootNumber rootNumber = linearEquation(eqData->coeffs, &x1);

    (*total)++;

	if(!(rootNumber == eqData->refRootNumber
        && smartEqual(x1, eqData->refRoots[0], THRESHOLD))) {
		printf("\n#%d FAILED: linearEquation(%lf, %lf, ...)"
                " returned %d, x1 = %lf"
                "\n(should be rootNumber = %d, x1 = %lf)",
                *total, eqData->coeffs[0],
                eqData->coeffs[1], rootNumber, x1, eqData  ->
                refRootNumber, eqData->refRoots[0]);
		return;
	}

    (*passed)++;
}

