#include <math.h>
#include <cstdlib>

#include "double.h"
#include "feedbackAssert.h"

//! @brief Checks if two doubles are similar enough in value (similarity is determined by a threshold)
//! @author Leonid Yutlin
//! @param [in] d1 First double to compare
//! @param [in] d2 Second double to compare
//! @param [in] threshold Double (uninclusive) threshold to check for
//! @returns true if doubles are similar enough in value; false if not
//! @throws AssertionError:
//!  If any of the doubles are nan
bool isEqualDouble(double d1, double d2, double threshold) {
    feedbackAssert(!isnan(d1) && !isnan(threshold) && !isnan(d2),
        "\n[ERROR]: Provided a nan double to isEqualDouble()!");

    return fabs(d1 - d2) < fabs(threshold);
} // @bug risk stackOverFlow

bool smartEqual(double d1, double d2, double threshold) {
    return (isnan(d1) || isnan(d2)) ?
            (isnan(d1) && isnan(d2)) : isEqualDouble(d1, d2, threshold);
} // @bug risk stackOverFlow

bool isZero(double d1) {
    feedbackAssert((!isnan(d1)),
        "\n[ERROR]: Provided a nan double to isZero()!");

    return isEqualDouble(d1, 0.0, THRESHOLD);
}
