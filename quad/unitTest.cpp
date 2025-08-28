#include <stdio.h>
#include <math.h>

#include "unitTest.h"
#include "polynomial.h"
#include "double.h"
#include "util.h"

struct EquationTestData {
    EquationData eqData;
    const RootNumber refRootNumber;
    const double refX1, refX2; //вопрос ментору: стоит ли тут ставить дефолт значения
};

// quadratics tests
static void testQuadraticEquations(int* passed, int* total);
static void testQuadraticEquation(int* passed, int* total,
                        EquationTestData* test);

// linear tests
static void testLinearEquations(int* passed, int* total);
static void testLinearEquation(int* passed, int* total,
                        EquationTestData* test);

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

    EquationTestData tests[] = {
        //{{.a = , .b = , .c = , .x1 = , .x2 = }, .refRootNumber = , .refX1 = , .refX2 = }
        {{NOT_DEFINED, 1, -5, 6, NAN, NAN}, TWO_ROOTS, 2, 3},
        {{NOT_DEFINED, 1, 2, 1, NAN, NAN}, ONE_ROOT, -1, -1},
        {{NOT_DEFINED, 1, 2, 3, NAN, NAN}, NO_ROOTS, NAN, NAN},
        {{NOT_DEFINED, 1e-10, 2, 1, NAN, NAN}, ONE_ROOT, -0.5, NAN},
        {{NOT_DEFINED, 0, 1e-10, 1e-10, NAN, NAN}, INFINITE_ROOTS, NAN, NAN}
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testQuadraticEquation(passed, total, &(tests[i]));
}

static void testQuadraticEquation(int* passed, int* total,
                                EquationTestData* test) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testQuadraticEquation()!");
    //TODO more asserts

	quadraticEquation(&(test->eqData)); //вопрос ментору: записать получше?

    (*total)++;

	if(!((test->eqData).rootNumber == test->refRootNumber
        && smartEqual((test->eqData).x1, test->refX1, THRESHOLD)
        && smartEqual((test->eqData).x2, test->refX2, THRESHOLD))) {
		printf("\n#%d FAILED: quadraticEquation(%lf, %lf, %lf, ...)"
                " returned %d, x1 = %lf, x2 = %lf"
                "\n(should be rootNumber = %d, x1 = %lf, x2=%lf)",
                *total, (test->eqData).a,
                (test->eqData).b, (test->eqData).c,
                (test->eqData).rootNumber, (test->eqData).x1,
                (test->eqData).x2, test->refRootNumber,
                test->refX1, test->refX2);
		return;
	}

    (*passed)++;
}

static void testLinearEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testLinearEquations()!");

    EquationTestData tests[3] = {
        {{NOT_DEFINED, 0, 4, 2, NAN, NAN}, ONE_ROOT, -0.5, NAN},
        {{NOT_DEFINED, 0, 0, 0, NAN, NAN}, INFINITE_ROOTS, NAN, NAN},
        {{NOT_DEFINED, 0, 0, 3, NAN, NAN}, NO_ROOTS, NAN, NAN}
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testLinearEquation(passed, total, &(tests[i]));
}

static void testLinearEquation(int* passed, int* total,
                                EquationTestData* test) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testLinearEquation()!");
    //TODO more asserts

    linearEquation(&(test->eqData)); //вопрос ментору: записать получше?

    (*total)++;

	if(!((test->eqData).rootNumber == test->refRootNumber
        && smartEqual((test->eqData).x1, test->refX1, THRESHOLD)
        && smartEqual((test->eqData).x2, test->refX2, THRESHOLD))) {
		printf("\n#%d FAILED: linearEquation(%lf, %lf, %lf, ...)"
                " returned %d, x1 = %lf, x2 = %lf"
                "\n(should be rootNumber = %d, x1 = %lf, x2=%lf)",
                *total, (test->eqData).a,
                (test->eqData).b, (test->eqData).c,
                (test->eqData).rootNumber, (test->eqData).x1,
                (test->eqData).x2, test->refRootNumber,
                test->refX1, test->refX2);
		return;
	}

    (*passed)++;
}

