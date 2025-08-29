enum RootNumber {
    NOT_DEFINED,
    INFINITE_ROOTS,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

const int ROOT_NUMBER_STR_LIMIT = 15;

struct Coeffs {
    const double a, b, c;
};

struct Roots {
    RootNumber rootNumber = NOT_DEFINED;
    double x1 = NAN, x2 = NAN;
};

struct EquationData {
    Coeffs coeffs;
    Roots roots = {};
};

// enums
const char* rootNumberToString(RootNumber rootNumber);
RootNumber stringToRootNumber(const char* rootNumberStr);

// structs
bool areEqualRoots(Roots r1, Roots r2);

// general
void solveEquation(EquationData* eqData);

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
