#include <f2d/error.h>

#include <stdarg.h>
#include <stdio.h>

void _error(const char *function, unsigned long line, const char *file, char *str, ...) {
    printf("Error in function %s(line %lu): ", function, line);
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
}
