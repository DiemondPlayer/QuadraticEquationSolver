#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <cstdlib>

//#define feedbackAssert(A, B) if(!A) { printf("%s\nFILE: %s LINE: %d\n", B, __FILE__, __LINE__); assert(A); }
//#define feedbackAbort(A, B) if(!A) { printf("%s\n", B); abort(); }

const double THRESHOLD = 1e-9; /* threshold below which difference between doubles
                                is ignored and they are deemed equal */
const int UNKNOWN_ERROR = 1; /* returned by main() and printRoots() in
                            case none of the switches work */
const int NO_ERRORS = 0; /* returned by main() and printRoots() in case
                            the program finishes without any errors */
const int EQUATION_INFINITE_ROOTS = -1; /* returned by quadraticEquation() and linearEquation()
                                     in case the given equation has infinite amount of roots */

void feedbackAssert(bool expr, const char* s, const char* file, int line) {
    if(!expr) {
        printf("%s\nFILE: %s LINE: %d\n", s, file, line);
        abort();
    }
}

#define feedbackAssert(A, B) feedbackAssert(A, B, __FILE__, __LINE__);

// input and output
void determineCoefficients(double* a, double* b, double* c);
void interpretInput(double* a, double* b, double* c);
int printRoots(int numberOfRoots, double x1, double x2, bool isLinear);
void clearInput();

// quadratics
int quadraticEquation(double a, double b, double c, double* x1, double* x2);
int discriminantToNumberOfRoots(double discriminant, double threshold);
    void testQuadraticEquation();

// linears
int linearEquation(double k, double b, double* x1);
    void testLinearEquation();

// double logic
bool isEqualDouble(double d1, double d2, double threshold);

int main() {
    testQuadraticEquation();
    testLinearEquation();
    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;
    determineCoefficients(NULL, &b, &c);
    determineCoefficients(&a, &b, &c);
    int numberOfRoots = quadraticEquation(a, b, c, &x1, &x2);
    return printRoots(numberOfRoots, x1, x2, isEqualDouble(a, 0.0, THRESHOLD));
}

void determineCoefficients(double* a, double* b, double* c) {
    feedbackAssert(a, "ERROR: Provided a null pointer to determineCoefficients()!")
    feedbackAssert(b, "ERROR: Provided a null pointer to determineCoefficients()!")
    feedbackAssert(c, "ERROR: Provided a null pointer to determineCoefficients()!")
    feedbackAssert((a != b && b != c && c != a),
                    "ERROR: Provided two or more identical pointers to determineCoefficients()!")

    printf("Quadratic equation solving program v1\n"
           "-------------------------------------\n");
    interpretInput(a, b, c);
    printf("The coefficients have been determined as such:\n"
           "a = %lg\n"
           "b = %lg\n"
           "c = %lg\n", *a, *b, *c);
}

void interpretInput(double* a, double* b, double* c) {
    feedbackAssert(a, "ERROR: Provided a null pointer to interpretInput()!")
    feedbackAssert(b, "ERROR: Provided a null pointer to interpretInput()!")
    feedbackAssert(c, "ERROR: Provided a null pointer to interpretInput()!")
    feedbackAssert((a != b && b != c && c != a),
                    "ERROR: Provided two or more identical pointers to interpretInput()!")

    printf("Enter coefficients of the equation (a, b, c): ");
    while (scanf("%lg %lg %lg", a, b, c) != 3) {
        printf("ERROR! Some input was not a valid coefficient! Try again!\n");
        printf("Enter coefficients of the equation (a, b, c): ");
        clearInput();
    }
}

//! @brief Solves quadratic equation by takin in 3 coefficients
//!  of it and putting the roots inside the pointers (if the
//!  equation is linear the root is recorded inside x1 and x2 is assigned nan)
//! @author Leonid Yutlin
//! @param [in] a First coefficient
//! @param [in] b Second coefficient
//! @param [in] c Third coefficient
//! @param [out] x1 Non-null pointer to the first root
//! @param [out] x2 Non-null pointer to the second root
//! @returns Number of distinct real roots of the given quadratic equation;
//!  Returns EQUATION_INFINITE_ROOTS in case the coefficients are 0,0,0
//! @throws AssertionError:
//!  If any of the pointers are null
//!  If pointers are the same pointer
int quadraticEquation(double a, double b, double c,
    double* x1, double* x2) {
    feedbackAssert((!isnan(a) && !isnan(b) && !isnan(c)),
        "ERROR: Provided a nan double to quadraticEquation()!")
    feedbackAssert((x1 && x2), "ERROR: Provided a null pointer to quadraticEquation()!")
    feedbackAssert((x1 != x2),
        "ERROR: Provided two identical pointers as root pointers to quadraticEquation()!");

    if (isEqualDouble(a, 0.0, THRESHOLD)) { //checks for linearity
        *x2 = NAN;
        return linearEquation(b, c, x1);;
    }

    double discriminant = b * b - 4 * a * c;

    int numberOfRoots = discriminantToNumberOfRoots(discriminant, THRESHOLD);

    if (numberOfRoots != 0) {
        *x1 = (-b - sqrt(discriminant)) / (2 * a);
        *x2 = (-b + sqrt(discriminant)) / (2 * a);
    }

    return numberOfRoots;
}

//! @brief Solves linear equation by takin in 2 coefficients
//!  of it and putting the root inside the pointer (if there are no roots
//!  or infinite amount of them, does not put anything in the pointer)
//! @author Leonid Yutlin
//! @param [in] k First coefficient
//! @param [in] b Second coefficient
//! @param [out] x1 Non-null pointer to the root
//! @returns Number of distinct real roots of the given linear equation;
//!  Returns EQUATION_INFINITE_ROOTS in case the coefficients are 0,0
//! @throws AssertionError:
//!  If the pointer is null
//!  If any of the doubles are nan
int linearEquation(double k, double b, double* x1) {
    feedbackAssert(x1, "ERROR: Provided a null pointer to linearEquation()!")
    feedbackAssert((!isnan(k) && !isnan(b)), "ERROR: Provided a nan double to linearEquation()!")

    if (isEqualDouble(k, 0.0, THRESHOLD))
        return isEqualDouble(b, 0.0, THRESHOLD) ? EQUATION_INFINITE_ROOTS : 0;

    *x1 = -b / k;

    return 1;
}

//! @author Leonid Yutlin
//! @param [in] discriminant Discriminant of a quadratic equation
//! @param [in] threshold Threshold to check for proximity to zero
//! @returns Number of distinct real roots of the given quadratic equation
//!  (presuming the equation is not linear nor infinitely solvable)
//! @throws AssertionError:
//!  If any of the doubles are nan
int discriminantToNumberOfRoots(double discriminant, double threshold) {
    feedbackAssert((!isnan(discriminant) && !isnan(threshold)), "ERROR: Provided a nan double to discriminantToNumberOfRoots()!")

    if (isEqualDouble(discriminant, 0.0, threshold)) return 1;
    if (discriminant > 0.0) return 2;
    /* if discriminant < 0.0 */ return 0;
}

int printRoots(int numberOfRoots, double x1, double x2, bool isLinear) {
    switch (numberOfRoots) {
        case 0:
            printf("The given equation has no real roots :(");
            break;
        case 1:
            if (isLinear) {
                printf("The given equation is deemed linear!\nThe given equation has only one root:\n%lg", x1);
            } else {
                printf("The given equation has one distinct real root:\n%lg", x1);
            }
            break;
        case 2:
            printf("The given equation has two distinct real roots:\n%lg\n%lg", x1, x2);
            break;
        case EQUATION_INFINITE_ROOTS:
            printf("The given equation has infinite amount of real distinct roots (any x will do) :O");
            break;
        default:
            printf("ERROR: Unknown error happened");
            return UNKNOWN_ERROR;
    }
    return NO_ERRORS;
}

//! @brief uses getchar() until it encounters a newline char or EOF
//! @author Leonid Yutlin
void clearInput() {
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n');
}

//! @brief Checks if two doubles are similar enough in value (similarity is determined by a threshold)
//! @author Leonid Yutlin
//! @param [in] d1 First double to compare
//! @param [in] d2 Second double to compare
//! @param [in] threshold Double (uninclusive) threshold to check for
//! @returns true if doubles are similar enough in value; false if not
//! @throws AssertionError:
//!  If any of the doubles are nan
bool isEqualDouble(double d1, double d2, double threshold) {
    feedbackAssert((!isnan(d1) && !isnan(threshold) && !isnan(d2)),
        "ERROR: Provided a nan double to isEqualDouble()!")

    return fabs(d1 - d2) < fabs(threshold);
}

void testQuadraticEquation() {
    double x1 = NAN, x2 = NAN;
	int numberOfRoots = quadraticEquation(1, -5, 6, &x1, &x2);
	if (!(numberOfRoots == 2 && isEqualDouble(x1, 2.0, THRESHOLD) && isEqualDouble(x2, 3.0, THRESHOLD))) {
		printf("#1 FAILED: quadraticEquation(-1, 5, 6, ...) returned %d, x1 = %lf, x2 = %lf \n(should be numberOfRoots = 2, x1 = 2, x2 = 3)\n", numberOfRoots, x1, x2);
	}
    numberOfRoots = quadraticEquation(1, 2, 1, &x1, &x2);
	if (!(numberOfRoots == 1 && isEqualDouble(x1, -1.0, THRESHOLD) && isEqualDouble(x2, -1.0, THRESHOLD))) {
		printf("#2 FAILED: quadraticEquation(1, 2, 1,...) returned %d, x1 = %lf, x2 = %lf \n(should be numberOfRoots = 1, x1 = -1, x2 = -1)\n", numberOfRoots, x1, x2);
	}
    numberOfRoots = quadraticEquation(3, 2, 1, &x1, &x2);
	if (!(numberOfRoots == 0 && isnan(x1) && isnan(x2))) {
		printf("#3 FAILED: quadraticEquation(3, 2, 1,...) returned %d, x1 = %lf, x2 = %lf \n(should be numberOfRoots = 0, x1=nan, x2=nan)\n", numberOfRoots, x1, x2);
	}
    numberOfRoots = quadraticEquation(0.0000000000000000001, 2, 1, &x1, &x2);
	if (!(numberOfRoots == 1 && isEqualDouble(x1, -0.5, THRESHOLD) && isnan(x2))) {
		printf("#4 FAILED: quadraticEquation(0.0000000000000000001, 2, 1,...) returned %d, x1 = %lf, x2 = %lf \n(should be numberOfRoots = 1, x1=-0.5, x2=nan)\n", numberOfRoots, x1, x2);
	}
    numberOfRoots = quadraticEquation(0, 0.0000000000000000001, 0.0000000000000000001, &x1, &x2);
	if (!(numberOfRoots == EQUATION_INFINITE_ROOTS)) {
		printf("#5 FAILED: quadraticEquation(0, 0.0000000000000000001, 0.0000000000000000001,...) returned %d \n(should be numberOfRoots = -1)\n", numberOfRoots, x1, x2);
	}
}

void testLinearEquation() {
    double x1 = NAN;
	int numberOfRoots = linearEquation(4, 2, &x1);
	if (!(numberOfRoots == 1 && isEqualDouble(x1, -0.5, THRESHOLD))) {
		printf("#1 FAILED: linearEquation(4, 2, ...) returned %d, x1 = %lf\n(should be numberOfRoots = 1, x1 = -0.5)\n", numberOfRoots, x1);
	}
    numberOfRoots = linearEquation(0, 0, &x1);
	if (!(numberOfRoots == EQUATION_INFINITE_ROOTS)) {
		printf("#2 FAILED: linearEquation(0, 0, ...) returned %d\n(should be numberOfRoots = -1)\n", numberOfRoots);
	}
    numberOfRoots = linearEquation(0, 3, &x1);
	if (!(numberOfRoots == 0)) {
		printf("#3 FAILED: linearEquation(0, 3, ...) returned %d\n(should be numberOfRoots = 0)\n", numberOfRoots);
	}
}

// -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
