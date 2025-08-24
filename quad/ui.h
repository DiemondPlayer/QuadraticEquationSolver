const int UNKNOWN_ERROR = 1; /* returned by printRoots() in
                            case none of the switches work */
const int NO_ERRORS = 0; /* returned by printRoots() in case
                            the program finishes without any errors */

// input and output
void determineCoefficients(double* a, double* b, double* c);
int printRoots(int numberOfRoots, double x1, double x2, bool isLinear);
