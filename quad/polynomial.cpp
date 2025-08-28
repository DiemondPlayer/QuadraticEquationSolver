#include <math.h>

#include "polynomial.h"
#include "double.h"
#include "util.h"

// quadratics
static RootNumber discriminantToRootNumber(double discriminant);

void quadraticEquation(EquationData* eqData) {
    feedbackAssert(eqData, "\n[ERROR]: Provided a null pointer to quadraticEquation()!");
    feedbackAssert(!isnan(eqData->a) && !isnan(eqData->b) && !isnan(eqData->c),
                    "\n[ERROR]: Provided a nan double (coefficient inside eqData) "
                    "to quadraticEquation()!");

    double a = eqData->a, b = eqData->b, c = eqData->c;

    if (isZero(a)) return linearEquation(eqData);

    double discriminant = b * b - 4 * a * c;

    eqData->rootNumber = discriminantToRootNumber(discriminant);

    if (eqData->rootNumber == TWO_ROOTS) {
        double sqRoot = sqrt(discriminant);
        eqData->x1 = (-b - sqRoot) / (2 * a);
        eqData->x2 = (-b + sqRoot) / (2 * a);
    } else if (eqData->rootNumber == ONE_ROOT) {
        eqData->x1 = eqData->x2 = -b / (2 * a);
    }
}

void linearEquation(EquationData* eqData) {
    // feedbackAssert(eqData, "\n[ERROR]: Provided a null pointer to linearEquation()!");
    // feedbackAssert(!isnan(eqData->a) && !isnan(eqData->b) && !isnan(eqData->c),
    //                 "\n[ERROR]: Provided a nan double (coefficient inside eqData) "
    //                 "to linearEquation()!");

    double b = eqData->b, c = eqData->c;

    if (isZero(b)) {
        eqData->rootNumber = isZero(c) ? INFINITE_ROOTS : NO_ROOTS;
        return;
    }

    eqData->x1 = -c / b;
    // eqData->x2 = NAN; а он и так нан.. может убрать

    eqData->rootNumber = ONE_ROOT;
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
