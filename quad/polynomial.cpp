#include <math.h>

#include "polynomial.h"
#include "double.h"
#include "feedbackAssert.h"

static RootNumber discriminantToRootNumber(double discriminant);

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
RootNumber quadraticEquation(const double coeffs[], double roots[]) {
        // feedbackAssert(!isnan(coeffs[i]),
        //     "\n[ERROR]: Provided a nan double to quadraticEquation()!");
    feedbackAssert(!isnan(coeffs[0]) && !isnan(coeffs[1]) && !isnan(coeffs[2]),
        "\n[ERROR]: Provided a nan double to quadraticEquation()!");
    feedbackAssert(&roots[0] && &roots[1],
        "\n[ERROR]: Provided a null pointer to quadraticEquation()!");
    feedbackAssert(&roots[0] != &roots[1],
        "\n[ERROR]: Provided two identical pointers as root pointers to quadraticEquation()!");

    double a = coeffs[0], b = coeffs[1], c = coeffs[2];

    if (isZero(a)) { //checks for linearity
        roots[1] = NAN;
        double linearCoeffs[2] = {b, c};
        return linearEquation(linearCoeffs, &roots[0]);
    }

    double discriminant = b * b - 4 * a * c;

    RootNumber rootNumber = discriminantToRootNumber(discriminant);

    if (rootNumber == TWO_ROOTS) {
        double sqRoot = sqrt(discriminant);
        roots[0] = (-b - sqRoot) / (2 * a);
        roots[1] = (-b + sqRoot) / (2 * a);
    } else if (rootNumber == ONE_ROOT) {
        roots[0] = roots[1] = (-b) / (2 * a);
    }

    return rootNumber;
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
RootNumber linearEquation(const double coeffs[], double* x1) {
    feedbackAssert(x1, "\n[ERROR]: Provided a null pointer to linearEquation()!");
    feedbackAssert(!isnan(coeffs[0]) && !isnan(coeffs[1]),
                    "\n[ERROR]: Provided a nan double to linearEquation()!");

    double k = coeffs[0], b = coeffs[1];

    if (isZero(k))
        return isZero(b) ? INFINITE_ROOTS : NO_ROOTS;

    *x1 = -b / k;

    return ONE_ROOT;
}

//! @author Leonid Yutlin
//! @param [in] discriminant Discriminant of a quadratic equation
//! @returns Number of distinct real roots of the given quadratic equation
//!  (presuming the equation is not linear nor infinitely solvable)
//! @throws AssertionError:
//!  If any of the doubles are nan
static RootNumber discriminantToRootNumber(double discriminant) {
    feedbackAssert(!isnan(discriminant),
                "\n[ERROR]: Provided a nan double to discriminantToRootNumber()!");

    if (isZero(discriminant)) return ONE_ROOT;
    if (discriminant > 0.0) return TWO_ROOTS;
    /* if discriminant < 0.0 */ return NO_ROOTS;
}
