/**
 * @file locale.h
 * @brief Localization utilities (Minimal "C" locale only)
 */

#ifndef _LOCALE_H
#define _LOCALE_H

/* NULL pointer definition (usually pulled from stddef.h) */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* Locale Category Macros */
#define LC_ALL 0
#define LC_COLLATE 1
#define LC_CTYPE 2
#define LC_MONETARY 3
#define LC_NUMERIC 4
#define LC_TIME 5

/* Structure holding formatting rules for numbers and currency.
 * In a minimal embedded system, this will always return the "C" locale rules. */
struct lconv
{
    /* Numeric formatting */
    char* decimal_point; /* e.g., "." */
    char* thousands_sep; /* e.g., "" */
    char* grouping; /* e.g., "" */

    /* Monetary formatting */
    char* int_curr_symbol; /* e.g., "" */
    char* currency_symbol; /* e.g., "" */
    char* mon_decimal_point; /* e.g., "" */
    char* mon_thousands_sep; /* e.g., "" */
    char* mon_grouping; /* e.g., "" */
    char* positive_sign; /* e.g., "" */
    char* negative_sign; /* e.g., "" */
    char int_frac_digits; /* e.g., CHAR_MAX */
    char frac_digits; /* e.g., CHAR_MAX */
    char p_cs_precedes; /* e.g., CHAR_MAX */
    char p_sep_by_space; /* e.g., CHAR_MAX */
    char n_cs_precedes; /* e.g., CHAR_MAX */
    char n_sep_by_space; /* e.g., CHAR_MAX */
    char p_sign_posn; /* e.g., CHAR_MAX */
    char n_sign_posn; /* e.g., CHAR_MAX */
};

/* Function Prototypes */

/**
 * @brief Sets or gets the current locale.
 * In this minimal implementation, it will only succeed if locale is "C" or "".
 */
char* setlocale(int category, const char* locale);

/**
 * @brief Returns the formatting rules for the current locale.
 */
struct lconv* localeconv(void);

#endif /* _LOCALE_H */