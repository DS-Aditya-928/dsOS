#include <limits.h>
#include <locale.h>

static struct lconv c_locale_rules = {
    .decimal_point = ".",
    .thousands_sep = "",
    .grouping = "",
    .int_curr_symbol = "",
    .currency_symbol = "",
    .mon_decimal_point = "",
    .mon_thousands_sep = "",
    .mon_grouping = "",
    .positive_sign = "",
    .negative_sign = "",
    .int_frac_digits = CHAR_MAX,
    .frac_digits = CHAR_MAX,
    .p_cs_precedes = CHAR_MAX,
    .p_sep_by_space = CHAR_MAX,
    .n_cs_precedes = CHAR_MAX,
    .n_sep_by_space = CHAR_MAX,
    .p_sign_posn = CHAR_MAX,
    .n_sign_posn = CHAR_MAX
};

char* setlocale(int category, const char* locale)
{
    if (locale == NULL || locale[0] == '\0' || (locale[0] == 'C' && locale[1] == '\0'))
    {
        return "C";
    }

    return NULL;
}

struct lconv* localeconv(void)
{
    return &c_locale_rules;
}