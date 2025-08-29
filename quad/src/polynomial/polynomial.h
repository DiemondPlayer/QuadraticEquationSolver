enum RootNumber {
    NOT_DEFINED = -2,
    INFINITE_ROOTS,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

struct EquationData {
    RootNumber rootNumber = NOT_DEFINED;
    const double a, b, c;
    double x1 = NAN, x2 = NAN;
};


//quadratics
void quadraticEquation(EquationData* eqData);

// linears
void linearEquation(EquationData* eqData);
