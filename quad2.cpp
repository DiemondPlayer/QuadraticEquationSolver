#include <stdio.h>
#include <cstdlib>

#define advancedAssert(A, B) if((A)) { printf((B)); abort(); }

int main() {
    advancedAssert(1==1, "COCONUT OTTER!");
}
