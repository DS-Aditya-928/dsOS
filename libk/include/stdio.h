#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define BUFSIZ 512
#define EOF (-1)
#define FOPEN_MAX 8
#define FILENAME_MAX 256
#define L_tmpnam 20
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
#define TMP_MAX 25

struct _FILE
{
    void (*write)(const char* str, size_t len);
    void (*pushChar)(char c);
};

typedef struct _FILE FILE;
typedef long fpos_t;

#ifdef __cplusplus
#define restrict __restrict__
extern "C"
{
#endif

    extern FILE* stdin;
    extern FILE* stdout;
    extern FILE* stderr;

#define stdin stdin
#define stdout stdout
#define stderr stderr

    /* Operations on files */
    int remove(const char* filename);
    int rename(const char* old_p, const char* new_p);
    FILE* tmpfile(void);
    char* tmpnam(char* s);

    /* File access functions */
    int fclose(FILE* stream);
    int fflush(FILE* stream);
    FILE* fopen(const char* restrict filename, const char* restrict mode);
    FILE* freopen(const char* restrict filename, const char* restrict mode, FILE* restrict stream);
    void setbuf(FILE* restrict stream, char* restrict buf);
    int setvbuf(FILE* restrict stream, char* restrict buf, int mode, size_t size);

    /* Formatted input/output functions */
    int fprintf(FILE* restrict stream, const char* restrict format, ...);
    int fscanf(FILE* restrict stream, const char* restrict format, ...);
    int printf(const char* restrict format, ...);
    int scanf(const char* restrict format, ...);
    int snprintf(char* restrict s, size_t n, const char* restrict format, ...);
    int sprintf(char* restrict s, const char* restrict format, ...);
    int sscanf(const char* restrict s, const char* restrict format, ...);

    int vfprintf(FILE* restrict stream, const char* restrict format, va_list arg);
    int vfscanf(FILE* restrict stream, const char* restrict format, va_list arg);

    int vprintf(const char* restrict format, va_list arg);
    int vscanf(const char* restrict format, va_list arg);

    int vsnprintf(char* restrict s, size_t n, const char* restrict format, va_list arg);
    int vsprintf(char* restrict s, const char* restrict format, va_list arg);
    int vsscanf(const char* restrict s, const char* restrict format, va_list arg);

    int fgetc(FILE* stream);
    char* fgets(char* restrict s, int n, FILE* restrict stream);
    int fputc(int c, FILE* stream);
    int fputs(const char* restrict s, FILE* restrict stream);
    int getc(FILE* stream);
    int getchar(void);
    char* gets(char* s);
    int putc(int c, FILE* stream);
    int putchar(int c);
    int puts(const char* s);
    int ungetc(int c, FILE* stream);

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H */