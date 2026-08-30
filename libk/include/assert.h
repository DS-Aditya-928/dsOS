#ifndef __ASSERT_H__
#define __ASSERT_H__

#ifdef NDEBUG
#define assert(condition) ((void)0)
#else
extern void __assert_fail(const char* expr, const char* file, int line, const char* func);
#define assert(condition) ((condition) ? (void)0 : __assert_fail(#condition, __FILE__, __LINE__, __func__));
#endif

#endif