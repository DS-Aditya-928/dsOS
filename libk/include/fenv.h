#ifndef _FENV_H
#define _FENV_H

#define FE_ALL_EXCEPT /* see description */
#define FE_DIVBYZERO /* see description */
#define FE_INEXACT /* see description */
#define FE_INVALID /* see description */
#define FE_OVERFLOW /* see description */
#define FE_UNDERFLOW /* see description */
#define FE_DOWNWARD /* see description */
#define FE_TONEARESTFROMZERO /* see description */
#define FE_TONEAREST /* see description */
#define FE_TOWARDZERO /* see description */
#define FE_UPWARD /* see description */
#define FE_DFL_ENV /* see description */
#define FE_DFL_MODE /* see description */

#define fenv_t /* see description */
#define fexcept_t /* see description */
#define femode_t /* see description */

#pragma STDC FENV_ACCESS /*on-off-switch*/
#pragma STDC FENV_ROUND direction
#pragma STDC FENV_ROUND FE_DYNAMIC

#ifdef __cplusplus
extern "C"
{
#endif

    // functions
    int feclearexcept(int excepts) { return 0; };
    int fegetexceptflag(fexcept_t* flagp, int excepts) { return 0; };
    int feraiseexcept(int excepts) { return 0; };
    int fesetexcept(int excepts) { return 0; };
    int fesetexceptflag(const fexcept_t* flagp, int excepts) { return 0; };
    int fetestexceptflag(const fexcept_t* flagp, int excepts) { return 0; };
    int fetestexcept(int excepts) { return 0; };
    int fegetmode(femode_t* modep) { return 0; };
    int fegetround(void) { return 0; };
    int fesetmode(const femode_t* modep) { return 0; };
    int fesetround(int rnd) { return 0; };
    int fegetenv(fenv_t* envp) { return 0; };
    int feholdexcept(fenv_t* envp) { return 0; };
    int fesetenv(const fenv_t* envp) { return 0; };
    int feupdateenv(const fenv_t* envp) { return 0; };

#ifdef __cplusplus
}
#endif

#endif // _FENV_H