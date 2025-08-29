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
static void testQuadraticEquation (int* passed, int* total,
                        EquationTestData* test);

// linear tests
static void testLinearEquations(int* passed, int* total);
static void testLinearEquation (int* passed, int* total,
                        EquationTestData* test);

int runUnitTests() {
    printf("Meow ^w^");
    int total = 0, passed = 0;

    testQuadraticEquations(&passed, &total);
    testLinearEquations(&passed,    &total);

    if (total == passed) {
        printf("\nAll unit tests have ran successfully");
    } else {
        printf("\n(%d/%d) unit tests have ran successfully"
               "\nShutting down program", passed, total);
        return 1;
    }
    return 0;
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

    //А я сейчас файл-ридер забабахаю!

//     FILE* fp = fopen("test.txt", "r");

    //int ch = '\0';
    //double assembledDoubles[5] = {NAN, NAN, NAN, NAN, NAN};

    // while (fscanf(fp, "%lf %lf %lf %lf %lf") == 5) {
        // char str[100];
        // str[0] = ch;
        // printf("%c", ch);
        // int i = 1;
        // while ((ch = getc(fp)) != EOF && ch != '\n') {
        //     str[i] = ch;
        //     printf("%c", ch);
        //     i++;
        // }
        // str[i+1] = '\0';
        // double a = NAN, b = NAN, c = NAN;
        // double refX1 = NAN, refX2 = NAN;
        // fscanf(fp, "%lf %lf %lf %lf %lf", &a, &b, &c, &refX1, &refX2);
        // int ch = 0;
        // while ((ch = getchar()) != EOF && ch != '\n');
        // if (refX1 > refX2) {
        //     double temp = refX1;
        //     refX2 = refX1;
        //     refX1 = temp;
        // }
        // int counter = 2;
        // if (isZero(refX1)) {
        //     refX1 = NAN;
        //     counter--;
        // }
        // if (isZero(refX2)) {
        //     refX2 = NAN;
        //     counter--;
        // }
        // RootNumber rootNumber = NOT_DEFINED;
        // switch (counter) {
        //     case 0: rootNumber = NO_ROOTS; break;
        //     case 1: rootNumber = ONE_ROOT; break;
        //     case 2: rootNumber = TWO_ROOTS; break;
        // }

//         EquationTestData test = {{NOT_DEFINED, a, b, c, NAN, NAN}, rootNumber, refX1, refX2};
//         testQuadraticEquation(passed, total, &test);
//     }
//
//     fclose(fp);
}

static void testQuadraticEquation(int* passed, int* total,
                                    EquationTestData* test) {
    feedbackAssert(passed && total,
                    "\n[ERROR]: Provided a null pointer to testQuadraticEquation()!");
    feedbackAssert(&(test->eqData), "\n[ERROR]: Provided a null EquationData pointer!");
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
    feedbackAssert(&(test->eqData), "\n[ERROR]: Provided a null EquationData pointer!");
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

