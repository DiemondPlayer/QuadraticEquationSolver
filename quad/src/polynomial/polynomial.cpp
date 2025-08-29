#include <math.h>

#include "polynomial/polynomial.h"
#include "util/double.h"
#include "util/assert.h"

// quadratics
static RootNumber discriminantToRootNumber(double discriminant);

void solveEquation(EquationData* eqData) {
    feedbackAssert(eqData, "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(eqData->coeffs.a)
                   && !isnan(eqData->coeffs.b)
                   && !isnan(eqData->coeffs.c),
                   "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

    if (isZero(eqData->coeffs.a)) {
        linearEquation(eqData);
    } else {
        quadraticEquation(eqData);
    }
}

void quadraticEquation(EquationData* eqData) {
    feedbackAssert(eqData, "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(eqData->coeffs.a)
                   && !isnan(eqData->coeffs.b)
                   && !isnan(eqData->coeffs.c),
                   "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

    double a = eqData->coeffs.a, b = eqData->coeffs.b, c = eqData->coeffs.c;

    if (isZero(a)) return linearEquation(eqData);

    double discriminant = b * b - 4 * a * c;

    eqData->roots.rootNumber = discriminantToRootNumber(discriminant);

    if (eqData->roots.rootNumber == TWO_ROOTS) {
        double sqRoot = sqrt(discriminant);
        eqData->roots.x1 = (-b - sqRoot) / (2 * a);
        eqData->roots.x2 = (-b + sqRoot) / (2 * a);
    } else if (eqData->roots.rootNumber == ONE_ROOT) {
        eqData->roots.x1 = eqData->roots.x2 = -b / (2 * a);
    }
}

void linearEquation(EquationData* eqData) {
    feedbackAssert(eqData, "\n[ERROR]: Provided a null EquationData pointer!");
    feedbackAssert(!isnan(eqData->coeffs.a)
                   && !isnan(eqData->coeffs.b)
                   && !isnan(eqData->coeffs.c),
                   "\n[ERROR]: Provided a nan double (coefficient inside EquationData)");

    double b = eqData->coeffs.b, c = eqData->coeffs.c;

    if (isZero(b)) {
        eqData->roots.rootNumber = isZero(c) ? INFINITE_ROOTS : NO_ROOTS;
        return;
    }

    eqData->roots.x1 = -c / b;
    // eqData->roots.x2 = NAN; // а он и так нан.. может убрать

    eqData->roots.rootNumber = ONE_ROOT;
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

const char* rootNumberToString(RootNumber rootNumber) {
    switch (rootNumber) {
        case NO_ROOTS:       return "NO_ROOTS";
        case ONE_ROOT:       return "ONE_ROOT";
        case TWO_ROOTS:      return "TWO_ROOTS";
        case INFINITE_ROOTS: return "INFINITE_ROOTS";
        case NOT_DEFINED:    return "NOT_DEFINED";
        default:
            //не оч красиво, переформатировать?
            feedbackAssert(false,
                "\n[ERROR]: No valid case found for switch(rootNumber) in rootNumberToString()"
                "\nIf it weren't for the assert, the program would return NOT_DEFINED instead");
            return "NOT_DEFINED";
    }
}

bool areEqualRoots(Roots r1, Roots r2) {
    return r1.rootNumber == r2.rootNumber &&
        ((smartEqual(r1.x1, r2.x1, THRESHOLD) && smartEqual(r1.x2, r2.x2, THRESHOLD))
        || (smartEqual(r1.x1, r2.x2, THRESHOLD) && smartEqual(r1.x2, r2.x1, THRESHOLD)));
}
