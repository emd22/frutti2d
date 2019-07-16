#ifndef ERROR_H
#define ERROR_H

#define f2d_error(str, ...) _error(__func__, __LINE__, __FILE__, str, __VA_ARGS__)

void _error(const char *function, unsigned long line, const char *file, char *str, ...);

#endif
