/**
 * @file limits.h
 * @brief Sizes of integer types for ESP32 (Xtensa 32-bit ILP32)
 */

#ifndef _LIMITS_H
#define _LIMITS_H

/* =====================================================================
 * CHAR AND MULTIBYTE TYPES
 * ===================================================================== */

/* Number of bits in a 'char' */
#define CHAR_BIT 8

/* Maximum number of bytes in a multibyte character.
 * (Typically 4 to fully support UTF-8 encoding). */
#define MB_LEN_MAX 4

/* Minimum and maximum values a 'signed char' can hold */
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127

/* Maximum value an 'unsigned char' can hold */
#define UCHAR_MAX 255

/* Minimum and maximum values a 'char' can hold.
 * GCC defines __CHAR_UNSIGNED__ if you compile with -funsigned-char.
 * This ensures the limits match the compiler's actual behavior. */
#ifdef __CHAR_UNSIGNED__
#define CHAR_MIN 0
#define CHAR_MAX UCHAR_MAX
#else
#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX
#endif

/* =====================================================================
 * SHORT, INT, LONG, AND LONG LONG TYPES
 * ===================================================================== */

/* Minimum and maximum values a 'short int' can hold (16-bit) */
#define SHRT_MIN (-32767 - 1)
#define SHRT_MAX 32767

/* Maximum value an 'unsigned short int' can hold */
#define USHRT_MAX 65535

/* Minimum and maximum values an 'int' can hold (32-bit) */
#define INT_MIN (-2147483647 - 1)
#define INT_MAX 2147483647

/* Maximum value an 'unsigned int' can hold */
#define UINT_MAX 4294967295U

/* Minimum and maximum values a 'long int' can hold (32-bit on ESP32) */
#define LONG_MIN (-2147483647L - 1L)
#define LONG_MAX 2147483647L

/* Maximum value an 'unsigned long int' can hold */
#define ULONG_MAX 4294967295UL

/* Minimum and maximum values a 'long long int' can hold (64-bit) */
#define LLONG_MIN (-9223372036854775807LL - 1LL)
#define LLONG_MAX 9223372036854775807LL

/* Maximum value an 'unsigned long long int' can hold */
#define ULLONG_MAX 18446744073709551615ULL

/* =====================================================================
 * POSIX / XOPEN EXTENSIONS
 * These are technically not part of strict ANSI C limits.h, but are
 * expected by almost all POSIX-compliant software and RTOS environments.
 * ===================================================================== */
#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE)
/* Number of bits in a word or type 'int' */
#define WORD_BIT 32

/* Number of bits in a type 'long int' */
#define LONG_BIT 32

/* Maximum value of 'ssize_t' (Signed size type) */
#define SSIZE_MAX INT_MAX
#endif

#endif /* _LIMITS_H */