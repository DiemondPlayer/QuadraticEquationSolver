// advanced assert
void feedbackAssert(bool expr, const char* message, const char* file, int line, const char* func, const char* exprString);

#define feedbackAssert(A, B) feedbackAssert(A, B, __FILE__, __LINE__, __PRETTY_FUNCTION__, #A)

// file and line from pre-processor, pretty function from compiler
