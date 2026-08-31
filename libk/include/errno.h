#define EDOM /* implementation-defined */
#define EILSEQ /* implementation-defined */
#define ERANGE /* implementation-defined */

#define errno /* implementation-defined */

// Only if the implementation defines __STDC_LIB_EXT1__ and additionally the user code
// defines __STDC_WANT_LIB_EXT1__ before any inclusion of <errno.h>:
#ifdef __STDC_WANT_LIB_EXT1__
#define __STDC_LIB_EXT1__ /* implementation-defined */
#define errno_t /* implementation-defined */
#endif
