#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Helper macro to append a character and track the total count.It ensures we never write past (size - 1) to leave room for the null terminator.
#define APPEND_CHAR(c)                               \
    do                                               \
    {                                                \
        if (str != NULL && (size_t)count < size - 1) \
        {                                            \
            str[count] = (c);                        \
        }                                            \
        count++;                                     \
    } while (0)

int vsnprintf(char* str, size_t size, const char* format, va_list arg)
{
    int count = 0;

    if (size > 0 && str == NULL)
    {
        return -1;
    }

    while (*format)
    {
        if (*format != '%')
        {
            APPEND_CHAR(*format);
            format++;
            continue;
        }

        format++;
        switch (*format)
        {
        case 'c':
        {
            char c = (char)va_arg(arg, int);
            APPEND_CHAR(c);
            break;
        }
        case 's':
        {
            const char* s = va_arg(arg, const char*);
            if (!s)
            {
                s = "(null)";
            }
            while (*s)
            {
                APPEND_CHAR(*s);
                s++;
            }
            break;
        }
        case 'd':
        {
            int val = va_arg(arg, int);
            char num_buf[32];
            itoa(val, num_buf, 10);
            char* n = num_buf;
            while (*n)
            {
                APPEND_CHAR(*n++);
            }
            break;
        }
        case 'x':
        {
            int val = va_arg(arg, int);
            char num_buf[32];
            itoa(val, num_buf, 16);
            char* n = num_buf;
            while (*n)
            {
                APPEND_CHAR(*n++);
            }
            break;
        }
        case '%':
        {
            APPEND_CHAR('%');
            break;
        }
        default:
        {
            // Unrecognized specifier, treat it as a literal character
            APPEND_CHAR('%');
            APPEND_CHAR(*format);
            break;
        }
        }

        if (*format)
        {
            format++;
        }
    }

    if (size > 0)
    {
        if ((size_t)count < size)
        {
            str[count] = '\0';
        }
        else
        {
            str[size - 1] = '\0'; /* Truncated */
        }
    }

    return count;
}

// Helper macro to push a character and track the total count.
#define PUSH_CHAR(c)           \
    do                         \
    {                          \
        stream->pushChar((c)); \
        count++;               \
    } while (0)

int vfprintf(FILE* restrict stream, const char* restrict format, va_list arg)
{
    int count = 0;

    if (stream == NULL || stream->pushChar == NULL)
    {
        return -1;
    }

    while (*format)
    {
        if (*format != '%')
        {
            PUSH_CHAR(*format);
            format++;
            continue;
        }

        format++;
        switch (*format)
        {
        case 'c':
        {
            char c = (char)va_arg(arg, int);
            PUSH_CHAR(c);
            break;
        }
        case 's':
        {
            const char* s = va_arg(arg, const char*);
            if (!s)
            {
                s = "(null)";
            }
            while (*s)
            {
                PUSH_CHAR(*s);
                s++;
            }
            break;
        }
        case 'd':
        {
            int val = va_arg(arg, int);
            char num_buf[32];
            itoa(val, num_buf, 10);
            char* n = num_buf;
            while (*n)
            {
                PUSH_CHAR(*n++);
            }
            break;
        }
        case 'x':
        {
            int val = va_arg(arg, int);
            char num_buf[32];
            itoa(val, num_buf, 16);
            char* n = num_buf;
            while (*n)
            {
                PUSH_CHAR(*n++);
            }
            break;
        }
        case '%':
        {
            PUSH_CHAR('%');
            break;
        }
        default:
        {
            // Unrecognized specifier, treat it as a literal character
            PUSH_CHAR('%');
            PUSH_CHAR(*format);
            break;
        }
        }

        if (*format)
        {
            format++;
        }
    }

    return count;
}

int fprintf(FILE* restrict stream, const char* restrict format, ...) // rewrite to use vfprintf
{
    if (stream == NULL || stream->write == NULL || format == NULL)
    {
        return -1;
    }

    va_list args;
    va_start(args, format);

    char buffer[256];
    int chars_to_write = vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    if (chars_to_write > 0)
    {
        size_t len = (chars_to_write < sizeof(buffer)) ? chars_to_write : (sizeof(buffer) - 1);

        stream->write(buffer, len);
    }

    return chars_to_write;
}

int printf(const char* restrict format, ...)
{
    if (stdout == NULL || stdout->write == NULL || format == NULL)
    {
        return -1;
    }

    va_list args;
    va_start(args, format);

    char buffer[256];
    int chars_to_write = vfprintf(stdout, format, args);

    va_end(args);

    return chars_to_write;
}