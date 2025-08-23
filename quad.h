#define THRESHOLD 1e-9 /* threshold below which difference between doubles are ignored and they are deemed equal */
#define UNKNOWN_ERROR 1 /* returned by main() and printRoots() in case none of the switches work */
#define NO_ERRORS 0 /* returned by main() and printRoots() in case the program finishes without any errors */
#define QUADRATIC_EQUATION_INFINITE_ROOTS (-1) /* returned by quadraticEquation() in case the given equation has infinite amount of roots */

void determineCoefficients(double* a, double* b, double* c);
int printRoots(int numberOfRoots, double x1, double x2, bool isLinear);
bool isEqualDouble(double d1, double d2, double threshold);
int quadraticEquation(double a, double b, double c, double * x1, double * x2);
void clearInput();