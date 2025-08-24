#include <stdio.h>
#include <math.h>

#include "unitTest.h"
#include "polynomial.h"
#include "double.h"
#include "feedbackAssert.h"

// quadratics tests
static void testQuadraticEquations(int* passed, int* total);
static void testQuadraticEquation(int* passed, int* total,
                        double a, double b, double c,
                        int refNumberOfRoots, double refX1, double refX2);

// linear tests
static void testLinearEquations(int* passed, int* total);
static void testLinearEquation(int* passed, int* total,
                        double k, double b,
                        int refNumberOfRoots, double refX1);

void runUnitTests() {
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

    testQuadraticEquation(passed, total, 1, -5, 6, 2, 2, 3);
	testQuadraticEquation(passed, total, 1, 2, 1, 1, -1, -1);
	testQuadraticEquation(passed, total, 1, 2, 3, 0, NAN, NAN);
    //testQuadraticEquation(passed, total, 1, 1111, 3, 0, NAN, NAN); // will fail on purpose
    testQuadraticEquation(passed, total, 1e-10, 2, 1, 1, -0.5, NAN);
    testQuadraticEquation(passed, total, 0, 1e-10, 1e-10, EQUATION_INFINITE_ROOTS, NAN, NAN);
    //testQuadraticEquation(passed, total, 0, 2, -3, 2, NAN, NAN); // fail on purpose
}

static void testQuadraticEquation(int* passed, int* total,
            double a, double b, double c,
            int refNumberOfRoots, double refX1, double refX2) {
    feedbackAssert(passed && total,
                    "ERROR: Provided a null pointer to testQuadraticEquation()!");

	double x1 = NAN, x2 = NAN;
	int numberOfRoots = quadraticEquation(a, b, c, &x1, &x2);

    *total = *total + 1;

	if(!(numberOfRoots == refNumberOfRoots
        && smartEqual(x1, refX1, THRESHOLD)
        && smartEqual(x2, refX2, THRESHOLD))) {
		printf("#%d FAILED: quadraticEquation(%lf, %lf, %lf, ...)"
                " returned %d, x1 = %lf, x2 = %lf\n"
                "(should be numberOfRoots = %d, x1 = %lf, x2=%lf)\n",
                *total, a, b, c, numberOfRoots, x1, x2, refNumberOfRoots, refX1, refX2);
		return;
	}

    *passed = *passed + 1;
}

static void testLinearEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                    "ERROR: Provided a null pointer to testLinearEquations()!");

    testLinearEquation(passed, total, 4, 2, 1, -0.5);
    testLinearEquation(passed, total, 0, 0, EQUATION_INFINITE_ROOTS, NAN);
    //testLinearEquation(passed, total, 0, 3, 0, 8); //will fail on purpose
    testLinearEquation(passed, total, 0, 3, 0, NAN);
}

static void testLinearEquation(int* passed, int* total,
            double k, double b,
            int refNumberOfRoots, double refX1) {
    feedbackAssert(passed && total,
                    "ERROR: Provided a null pointer to testLinearEquation()!");

    double x1 = NAN;
	int numberOfRoots = linearEquation(k, b, &x1);

    *total = *total + 1;

	if(!(numberOfRoots == refNumberOfRoots
        && smartEqual(x1, refX1, THRESHOLD))) {
		printf("#%d FAILED: linearEquation(%lf, %lf, ...)"
                " returned %d, x1 = %lf\n"
                "(should be numberOfRoots = %d, x1 = %lf)\n",
                *total, k, b, numberOfRoots, x1, refNumberOfRoots, refX1);
		return;
	}

    *passed = *passed + 1;
}

