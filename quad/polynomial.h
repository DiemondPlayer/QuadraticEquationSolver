const int EQUATION_INFINITE_ROOTS = -1; /* returned by quadraticEquation() and linearEquation()
                                     in case the given equation has infinite amount of roots */

// quadratics
int quadraticEquation(double coeffs[], double roots[]);

// linears
int linearEquation(double coeffs[], double* x1);
