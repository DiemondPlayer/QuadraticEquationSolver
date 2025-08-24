const int EQUATION_INFINITE_ROOTS = -1; /* returned by quadraticEquation() and linearEquation()
                                     in case the given equation has infinite amount of roots */

// quadratics
int quadraticEquation(double a, double b, double c, double* x1, double* x2);

// linears
int linearEquation(double k, double b, double* x1);
