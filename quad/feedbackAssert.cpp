#include <cstdio>
#include <cstdlib>
#include "feedbackAssert.h"
#undef feedbackAssert

void feedbackAssert(bool expr, const char* s, const char* file, int line) {
    if (!expr) {
        printf("%s\n"
        "FILE: %s LINE: %d\n", s, file, line);
        abort();
    }
}
