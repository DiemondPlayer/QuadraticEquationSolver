// advanced assert
void feedbackAssert(bool expr, const char* s, const char* file, int line);

#define feedbackAssert(A, B) feedbackAssert(A, B, __FILE__, __LINE__)
