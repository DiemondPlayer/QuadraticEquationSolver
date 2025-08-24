#include <math.h>

#include "unitTest.h"
#include "polynomial.h"
#include "double.h"
#include "ui.h"

int main() {
    runUnitTests();
    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;
    determineCoefficients(&a, &b, &c);
    int numberOfRoots = quadraticEquation(a, b, c, &x1, &x2);
    return printRoots(numberOfRoots, x1, x2, isZero(a));
}

// -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
