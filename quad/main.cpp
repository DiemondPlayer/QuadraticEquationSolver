#include <math.h>

#include "unitTest.h"
#include "double.h"
#include "ui.h"

int main() {
    runUnitTests();
    double coeffs[3] = {NAN, NAN, NAN};
    double roots[2] = {NAN, NAN};
    determineCoefficients(coeffs);
    RootNumber rootNumber = quadraticEquation(coeffs, roots);
    return printRoots(rootNumber, roots, isZero(coeffs[0]));
}

// -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
