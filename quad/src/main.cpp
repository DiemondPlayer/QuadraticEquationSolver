#include <math.h>
#include <cstdio>

#include "unitTest/unitTest.h"
#include "util/double.h"
#include "io/io.h"

// TODO fix compile
// TODO fix code
// TODO scanf
// TODO tests from file
// ...
// TODO update docs
// ...
// TODO 3x^2+5x+7=0

int main() {
    TestFeedback testFeedback = runUnitTests();
    if (testFeedback != OK) return testFeedback;

    printf("\nQuadratic equation solving program v1");

    do {
        printf("\n-------------------------------------");
        EquationData eqData = { .coeffs = inputCoeffs() };
        printCoeffs(eqData.coeffs);
        quadraticEquation(&eqData);
        printRoots(eqData.roots);
    } while (askToContinue() == true);

    printf("\nCOMMIT GITHUB");
    return 0;
}

// -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
