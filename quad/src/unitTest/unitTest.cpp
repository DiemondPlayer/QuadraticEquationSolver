#include <stdio.h>
#include <math.h>

#include "unitTest.h"
#include "polynomial.h"
#include "double.h"
#include "util.h"

struct EquationTestData {
    EquationData eqData;
    const RootNumber refRootNumber;
    const double refX1, refX2;
};

// quadratics tests
static void testQuadraticEquations(int* passed, int* total);
static void testQuadraticEquation (int* passed, int* total,
                        EquationTestData* test);

// linear tests
static void testLinearEquations(int* passed, int* total);
static void testLinearEquation (int* passed, int* total,
                        EquationTestData* test);

RuntimeCondition runUnitTests() {
    printf("Meow ^w^");
    int total = 0, passed = 0;

    testQuadraticEquations(&passed, &total);
    testLinearEquations(&passed,    &total);

    if (total == passed) {
        printf("\nAll unit tests have ran successfully");
    } else {
        printf("\n(%d/%d) unit tests have ran successfully"
               "\nShutting down the program", passed, total);
        return SHUTDOWN;
    }
    return OK;
}

static void testQuadraticEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testQuadraticEquations()!");

    EquationTestData tests[] = {
//      {{.a =  ,     .b =   ,    .c =      }, .refRootNumber = , .refX1 = , .refX2 = }
        {{.a = 1,     .b = -5,    .c = 6    }, TWO_ROOTS,      2,    3  },
        {{.a = 1,     .b =  2,    .c = 1    }, ONE_ROOT,       -1,   -1 },
        {{.a = 1,     .b =  2,    .c = 3    }, NO_ROOTS,       NAN,  NAN},
        {{.a = 1e-10, .b =  2,    .c = 1    }, ONE_ROOT,       -0.5, NAN},
        {{.a = 0,     .b = 1e-10, .c = 1e-10}, INFINITE_ROOTS, NAN,  NAN},
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testQuadraticEquation(passed, total, &(tests[i]));

    //TODO tests via file reading
}

static void testQuadraticEquation(int* passed, int* total,
                                    EquationTestData* test) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testQuadraticEquation()!");
    feedbackAssert(&(test->eqData),
                   "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(test->eqData.a) && !isnan(test->eqData.b) && !isnan(test->eqData.c),
                   "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

	quadraticEquation(&(test->eqData)); //вопрос ментору: записать получше?

    (*total)++;

	if(!((test->eqData).rootNumber == test->refRootNumber
        && smartEqual((test->eqData).x1, test->refX1, THRESHOLD)
        && smartEqual((test->eqData).x2, test->refX2, THRESHOLD)))
    {
		printf("\n#%d FAILED: quadraticEquation(%lf, %lf, %lf, ...)"
               "\nreturned %s, x1 = %lf, x2 = %lf"
               "\n(should be rootNumber = %s, x1 = %lf, x2=%lf)",
               *total, (test->eqData).a, (test->eqData).b, (test->eqData).c,
               rootNumberToString((test->eqData).rootNumber), (test->eqData).x1, (test->eqData).x2,
               rootNumberToString(test->refRootNumber),        test->refX1,       test->refX2);
		return;
	}

    (*passed)++;
}

static void testLinearEquations(int* passed, int* total) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testLinearEquations()!");

    EquationTestData tests[3] = {
//      {{.a =  , .b =   , .c =  }, .refRootNumber = , .refX1 = , .refX2 = }
        {{.a = 0, .b =  4, .c = 2}, ONE_ROOT,       -0.5, NAN},
        {{.a = 0, .b =  0, .c = 0}, INFINITE_ROOTS, NAN,  NAN},
        {{.a = 0, .b =  0, .c = 3}, NO_ROOTS,       NAN,  NAN},
    };

    for (size_t i = 0; i < sizer(tests); i++)
        testLinearEquation(passed, total, &(tests[i]));
}

static void testLinearEquation(int* passed, int* total,
                               EquationTestData* test) {
    feedbackAssert(passed && total,
                   "\n[ERROR]: Provided a null pointer to testLinearEquation()!");
    feedbackAssert(&(test->eqData),
                   "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(test->eqData.a) && !isnan(test->eqData.b) && !isnan(test->eqData.c),
                   "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

    linearEquation(&(test->eqData)); //вопрос ментору: записать получше?

    (*total)++;

	if(!((test->eqData).rootNumber == test->refRootNumber
        && smartEqual((test->eqData).x1, test->refX1, THRESHOLD)
        && smartEqual((test->eqData).x2, test->refX2, THRESHOLD)))
    {
		printf("\n#%d FAILED: linearEquation(%lf, %lf, %lf, ...)"
               "\nreturned %s, x1 = %lf, x2 = %lf"
               "\n(should be rootNumber = %s, x1 = %lf, x2=%lf)",
               *total, (test->eqData).a, (test->eqData).b, (test->eqData).c,
               rootNumberToString((test->eqData).rootNumber), (test->eqData).x1, (test->eqData).x2,
               rootNumberToString(test->refRootNumber),        test->refX1,       test->refX2);
		return;
	}

    (*passed)++;
}

