const double THRESHOLD = 1e-9; /* threshold below which difference between doubles
                                is ignored and they are deemed equal */

// double logic
bool isEqualDouble(double d1, double d2, double threshold);
bool isZero(double d1);
bool smartEqual(double d1, double d2, double threshold);
