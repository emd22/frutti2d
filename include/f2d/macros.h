#ifndef MACROS_H
#define MACROS_H

#if defined(__linux__)
#define IS_UNIX
#define STDCALL
#endif

#ifdef __WIN32
#define IS_WINDOWS

// why, windows?
#define STDCALL __stdcall
#endif

#define SUCCESS 0
#define FAILURE 1

#endif