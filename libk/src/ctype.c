#include <ctype.h>

int islower(int c)
{
    return (c >= 'a' && c <= 'z');
}

int isupper(int c)
{
    return (c >= 'A' && c <= 'Z');
}

int isalpha(int c)
{
    return islower(c) || isupper(c);
}

int isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int isalnum(int c)
{
    return isalpha(c) || isdigit(c);
}

int isxdigit(int c)
{
    return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

int isblank(int c)
{
    return (c == ' ' || c == '\t');
}

int isspace(int c)
{
    return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
}

int iscntrl(int c)
{
    return (c >= 0 && c <= 31) || (c == 127);
}

int isgraph(int c)
{
    return (c > 32 && c < 127);
}

int isprint(int c)
{
    return (c >= 32 && c < 127);
}

int ispunct(int c)
{
    return isgraph(c) && !isalnum(c);
}

int tolower(int c)
{
    if (isupper(c))
    {
        return c - 'A' + 'a';
    }
    return c;
}

int toupper(int c)
{
    if (islower(c))
    {
        return c - 'a' + 'A';
    }
    return c;
}