enum RootNumber {
    NOT_DEFINED    = -2,
    INFINITE_ROOTS = -1,
    NO_ROOTS       =  0,
    ONE_ROOT       =  1,
    TWO_ROOTS      =  2
};

struct EquationData {
    RootNumber rootNumber = NOT_DEFINED;
    const double a, b, c;
    double x1 = NAN, x2 = NAN;
};

// enums
const char* rootNumberToString(RootNumber rootNumber);

// quadratics
void quadraticEquation(EquationData* eqData);

// linears
void linearEquation(EquationData* eqData);

/* вопрос ментору: а как это сделать если компилятор ругается и на точки и на стрелки
#define groupAssertEquationData(A); \
feedbackAssert(A, "\n[ERROR]: Provided a null EquationData pointer!"); \
feedbackAssert(!isnan(A->a) && !isnan(A->b) && !isnan(A->c), \
"\n[ERROR]: Provided a nan double (coefficient inside EquationData)");
*/
