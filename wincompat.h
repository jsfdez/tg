#if !defined(WINCOMPAT) && defined(_WIN32)

#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ShlObj.h>
#include <direct.h>
#include <io.h>
#include <WinSock2.h>
#include <wincrypt.h>
#include <process.h>

#include "wingetopt.h"

/* Macros for access() */
#define R_OK  4  /* Read */
#define W_OK  2  /* Write */
#define X_OK  1  /* Execute */
#define F_OK  0  /* Existence */

#define __attribute__(X)
#define mkdir(X, Y) _mkdir(X)
#define access _access
#define open _open
#define read(FileHandle, DstBuf, MaxCharCount) _read(FileHandle, DstBuf, (int)(MaxCharCount))
#define write(FileHandle, Buf, MaxCharCount) _write(FileHandle, Buf, (unsigned int)(MaxCharCount))
#define close(fd) _close(fd)
#define strdup _strdup
#define lseek _lseek
#undef small
#define poll WSAPoll
#define getpid _getpid

struct __SYSTEMTIME
{
	DWORD tv_nsec;
	DWORD tv_sec;
};

#define timespec __SYSTEMTIME

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1

#define lrand48 rand

#define __builtin_bswap32 htonl

#ifndef TCP_QUICKACK
#define TCP_QUICKACK 0
#endif

#ifdef _WIN64
typedef __int64 ssize_t;
#else
typedef __int32 ssize_t;
#endif

#include <stdio.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream);
ssize_t getstr(char ** lineptr, size_t *n, FILE * stream, char terminator, int offset);

#include "tools.h"

int vasprintf (char **buf, const char *format, va_list ap);
char* strndup (const char *s, size_t n);

#endif
