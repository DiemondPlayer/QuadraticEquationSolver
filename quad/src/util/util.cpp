#include <cstdio>
#include <cstdlib>
#include "util/util.h"
#undef feedbackAssert

void feedbackAssert(bool expr, const char* message, const char* file,
                    int line, const char* func, const char* exprString) {
    if (!expr) {
        printf("%s"
               "\nFILE: %s"
               "\nLINE: %d"
               "\nFUNCTION: %s"
               "\nEXPRESSION: %s",
               message, file, line, func, exprString);
        abort();
    }
}
