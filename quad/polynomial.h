enum RootNumber {
    INFINITE_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

// quadratics
RootNumber quadraticEquation(const double coeffs[], double roots[]);

// linears
RootNumber linearEquation(const double coeffs[], double* x1);
