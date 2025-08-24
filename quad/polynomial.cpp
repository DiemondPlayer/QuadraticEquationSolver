#include <math.h>

#include "polynomial.h"
#include "double.h"
#include "feedbackAssert.h"

static int discriminantToNumberOfRoots(double discriminant);

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
    feedbackAssert(!isnan(a) && !isnan(b) && !isnan(c),
        "ERROR: Provided a nan double to quadraticEquation()!");
    feedbackAssert(x1 && x2, "ERROR: Provided a null pointer to quadraticEquation()!");
    feedbackAssert(x1 != x2,
        "ERROR: Provided two identical pointers as root pointers to quadraticEquation()!");

    if (isZero(a)) { //checks for linearity
        *x2 = NAN;
        return linearEquation(b, c, x1);;
    }

    double discriminant = b * b - 4 * a * c;

    int numberOfRoots = discriminantToNumberOfRoots(discriminant);

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
    feedbackAssert(x1, "ERROR: Provided a null pointer to linearEquation()!");
    feedbackAssert(!isnan(k) && !isnan(b),
                    "ERROR: Provided a nan double to linearEquation()!");

    if (isZero(k))
        return isZero(b) ? EQUATION_INFINITE_ROOTS : 0;

    *x1 = -b / k;

    return 1;
}

//! @author Leonid Yutlin
//! @param [in] discriminant Discriminant of a quadratic equation
//! @returns Number of distinct real roots of the given quadratic equation
//!  (presuming the equation is not linear nor infinitely solvable)
//! @throws AssertionError:
//!  If any of the doubles are nan
static int discriminantToNumberOfRoots(double discriminant) {
    feedbackAssert(!isnan(discriminant),
                "ERROR: Provided a nan double to discriminantToNumberOfRoots()!");

    if (isZero(discriminant)) return 1;
    if (discriminant > 0.0) return 2;
    /* if discriminant < 0.0 */ return 0;
}
