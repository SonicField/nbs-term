extern void abort(void);
# 0 "src/extension.phc"
# 1 "/data/users/alexturner/nbs-term//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "src/extension.phc"
# 17 "src/extension.phc"
# 1 "/home/alexturner/include/python3.15/Python.h" 1
# 13 "/home/alexturner/include/python3.15/Python.h"
# 1 "/home/alexturner/include/python3.15/patchlevel.h" 1
# 14 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pyconfig.h" 1
# 15 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pymacconfig.h" 1
# 16 "/home/alexturner/include/python3.15/Python.h" 2




# 1 "/usr/include/assert.h" 1 3 4
# 35 "/usr/include/assert.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 392 "/usr/include/features.h" 3 4
# 1 "/usr/include/features-time64.h" 1 3 4
# 20 "/usr/include/features-time64.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 21 "/usr/include/features-time64.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 22 "/usr/include/features-time64.h" 2 3 4
# 393 "/usr/include/features.h" 2 3 4
# 490 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 551 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 552 "/usr/include/sys/cdefs.h" 2 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 553 "/usr/include/sys/cdefs.h" 2 3 4
# 491 "/usr/include/features.h" 2 3 4
# 514 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 515 "/usr/include/features.h" 2 3 4
# 36 "/usr/include/assert.h" 2 3 4
# 21 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/include/inttypes.h" 1 3 4
# 27 "/usr/include/inttypes.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4



# 31 "/usr/include/bits/types.h" 3 4
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 142 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/time64.h" 1 3 4
# 143 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 28 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4




# 1 "/usr/include/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 35 "/usr/include/stdint.h" 2 3 4


# 1 "/usr/include/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4





typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 71 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 87 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 101 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stdint.h" 2 3 4
# 28 "/usr/include/inttypes.h" 2 3 4






typedef int __gwchar_t;
# 266 "/usr/include/inttypes.h" 3 4





typedef struct
  {
    long int quot;
    long int rem;
  } imaxdiv_t;
# 290 "/usr/include/inttypes.h" 3 4
extern intmax_t imaxabs (intmax_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern intmax_t strtoimax (const char *__restrict __nptr,
      char **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));


extern uintmax_t strtoumax (const char *__restrict __nptr,
       char ** __restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));


extern intmax_t wcstoimax (const __gwchar_t *__restrict __nptr,
      __gwchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));


extern uintmax_t wcstoumax (const __gwchar_t *__restrict __nptr,
       __gwchar_t ** __restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));


# 22 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/limits.h" 1 3 4
# 34 "/usr/lib/gcc/x86_64-redhat-linux/11/include/limits.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/syslimits.h" 1 3 4






# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/limits.h" 1 3 4
# 203 "/usr/lib/gcc/x86_64-redhat-linux/11/include/limits.h" 3 4
# 1 "/usr/include/limits.h" 1 3 4
# 26 "/usr/include/limits.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/limits.h" 2 3 4
# 195 "/usr/include/limits.h" 3 4
# 1 "/usr/include/bits/posix1_lim.h" 1 3 4
# 27 "/usr/include/bits/posix1_lim.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/posix1_lim.h" 2 3 4
# 161 "/usr/include/bits/posix1_lim.h" 3 4
# 1 "/usr/include/bits/local_lim.h" 1 3 4
# 38 "/usr/include/bits/local_lim.h" 3 4
# 1 "/usr/include/linux/limits.h" 1 3 4
# 39 "/usr/include/bits/local_lim.h" 2 3 4
# 81 "/usr/include/bits/local_lim.h" 3 4
# 1 "/usr/include/bits/pthread_stack_min-dynamic.h" 1 3 4
# 23 "/usr/include/bits/pthread_stack_min-dynamic.h" 3 4

extern long int __sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));

# 82 "/usr/include/bits/local_lim.h" 2 3 4
# 162 "/usr/include/bits/posix1_lim.h" 2 3 4
# 196 "/usr/include/limits.h" 2 3 4



# 1 "/usr/include/bits/posix2_lim.h" 1 3 4
# 200 "/usr/include/limits.h" 2 3 4



# 1 "/usr/include/bits/xopen_lim.h" 1 3 4
# 64 "/usr/include/bits/xopen_lim.h" 3 4
# 1 "/usr/include/bits/uio_lim.h" 1 3 4
# 65 "/usr/include/bits/xopen_lim.h" 2 3 4
# 204 "/usr/include/limits.h" 2 3 4
# 204 "/usr/lib/gcc/x86_64-redhat-linux/11/include/limits.h" 2 3 4
# 8 "/usr/lib/gcc/x86_64-redhat-linux/11/include/syslimits.h" 2 3 4
# 35 "/usr/lib/gcc/x86_64-redhat-linux/11/include/limits.h" 2 3 4
# 23 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/include/math.h" 1 3 4
# 27 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/math.h" 2 3 4












# 1 "/usr/include/bits/math-vector.h" 1 3 4
# 25 "/usr/include/bits/math-vector.h" 3 4
# 1 "/usr/include/bits/libm-simd-decl-stubs.h" 1 3 4
# 26 "/usr/include/bits/math-vector.h" 2 3 4
# 41 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/floatn.h" 1 3 4
# 119 "/usr/include/bits/floatn.h" 3 4
# 1 "/usr/include/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/bits/floatn-common.h" 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 25 "/usr/include/bits/floatn-common.h" 2 3 4
# 120 "/usr/include/bits/floatn.h" 2 3 4
# 44 "/usr/include/math.h" 2 3 4
# 152 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/flt-eval-method.h" 1 3 4
# 153 "/usr/include/math.h" 2 3 4
# 163 "/usr/include/math.h" 3 4
typedef float float_t;
typedef double double_t;
# 204 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/fp-logb.h" 1 3 4
# 205 "/usr/include/math.h" 2 3 4
# 247 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/fp-fast.h" 1 3 4
# 248 "/usr/include/math.h" 2 3 4



enum
  {
    FP_INT_UPWARD =

      0,
    FP_INT_DOWNWARD =

      1,
    FP_INT_TOWARDZERO =

      2,
    FP_INT_TONEARESTFROMZERO =

      3,
    FP_INT_TONEAREST =

      4,
  };
# 312 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassify (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbit (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinf (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finite (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnan (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsig (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignaling (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 313 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern double acos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acos (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double cos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cos (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double sin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tan (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double cosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double sinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tanh (double __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincos (double __x, double *__sinx, double *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincos (double __x, double *__sinx, double *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern double acosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atanh (double __x) __attribute__ ((__nothrow__ , __leaf__));





 extern double exp (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern double log (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log10 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern double exp10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp10 (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log1p (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log1p (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double logb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __logb (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log2 (double __x) __attribute__ ((__nothrow__ , __leaf__));






 extern double pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));




extern double cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/bits/mathcalls.h" 3 4
extern int isinf (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));




extern int finite (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern double drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double significand (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __significand (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern double __nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 213 "/usr/include/bits/mathcalls.h" 3 4
extern int isnan (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));





extern double j0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double j1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double jn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __jn (int, double) __attribute__ ((__nothrow__ , __leaf__));
extern double y0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double y1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double yn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __yn (int, double) __attribute__ ((__nothrow__ , __leaf__));





extern double erf (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erf (double) __attribute__ ((__nothrow__ , __leaf__));
extern double erfc (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erfc (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma (double) __attribute__ ((__nothrow__ , __leaf__));




extern double tgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __tgamma (double) __attribute__ ((__nothrow__ , __leaf__));





extern double gamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __gamma (double) __attribute__ ((__nothrow__ , __leaf__));







extern double lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern double rint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __rint (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));

extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




extern double nextdown (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextdown (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double nextup (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextup (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogb (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern double nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lround (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__));




extern double roundeven (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __roundeven (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfp (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfp (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfp (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfp (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpx (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpx (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpx (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpx (double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalize (double *__cx, const double *__x) __attribute__ ((__nothrow__ , __leaf__));






extern double fmaxmag (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmaxmag (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fminmag (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fminmag (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorder (const double *__x, const double *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermag (const double *__x, const double *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern double getpayload (const double *__x) __attribute__ ((__nothrow__ , __leaf__)); extern double __getpayload (const double *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayload (double *__x, double __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsig (double *__x, double __payload) __attribute__ ((__nothrow__ , __leaf__));







extern double scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__));
# 314 "/usr/include/math.h" 2 3 4
# 329 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinff (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finitef (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsigf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 330 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern float acosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float cosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float sinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float coshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __coshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincosf (float __x, float *__sinx, float *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosf (float __x, float *__sinx, float *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern float acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));





 extern float expf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern float logf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log10f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern float exp10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp10f (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float logbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logbf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log2f (float __x) __attribute__ ((__nothrow__ , __leaf__));






 extern float powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));




extern float cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/bits/mathcalls.h" 3 4
extern int isinff (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));




extern int finitef (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern float dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float significandf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __significandf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern float __nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 213 "/usr/include/bits/mathcalls.h" 3 4
extern int isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));





extern float j0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float j1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float jnf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __jnf (int, float) __attribute__ ((__nothrow__ , __leaf__));
extern float y0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float y1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float ynf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __ynf (int, float) __attribute__ ((__nothrow__ , __leaf__));





extern float erff (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erff (float) __attribute__ ((__nothrow__ , __leaf__));
extern float erfcf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erfcf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf (float) __attribute__ ((__nothrow__ , __leaf__));




extern float tgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __tgammaf (float) __attribute__ ((__nothrow__ , __leaf__));





extern float gammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __gammaf (float) __attribute__ ((__nothrow__ , __leaf__));







extern float lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern float rintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __rintf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));

extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




extern float nextdownf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextdownf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float nextupf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextupf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern float nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__));




extern float roundevenf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundevenf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfpf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfpf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpxf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpxf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpxf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpxf (float __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalizef (float *__cx, const float *__x) __attribute__ ((__nothrow__ , __leaf__));






extern float fmaxmagf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxmagf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fminmagf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminmagf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorderf (const float *__x, const float *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermagf (const float *__x, const float *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern float getpayloadf (const float *__x) __attribute__ ((__nothrow__ , __leaf__)); extern float __getpayloadf (const float *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadf (float *__x, float __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsigf (float *__x, float __payload) __attribute__ ((__nothrow__ , __leaf__));







extern float scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__));
# 331 "/usr/include/math.h" 2 3 4
# 398 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsigl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 399 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern long double acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincosl (long double __x, long double *__sinx, long double *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosl (long double __x, long double *__sinx, long double *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern long double acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));





 extern long double expl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern long double logl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern long double exp10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));






 extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




extern long double cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/bits/mathcalls.h" 3 4
extern int isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));




extern int finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern long double dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 213 "/usr/include/bits/mathcalls.h" 3 4
extern int isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));





extern long double j0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double j1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__));





extern long double erfl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double erfcl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__ , __leaf__));




extern long double tgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__ , __leaf__));





extern long double gammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __gammal (long double) __attribute__ ((__nothrow__ , __leaf__));







extern long double lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern long double rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));

extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




extern long double nextdownl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextdownl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double nextupl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextupl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__));




extern long double roundevenl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundevenl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfpl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfpl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpxl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpxl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpxl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpxl (long double __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalizel (long double *__cx, const long double *__x) __attribute__ ((__nothrow__ , __leaf__));






extern long double fmaxmagl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxmagl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fminmagl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminmagl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorderl (const long double *__x, const long double *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermagl (const long double *__x, const long double *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern long double getpayloadl (const long double *__x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __getpayloadl (const long double *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadl (long double *__x, long double __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsigl (long double *__x, long double __payload) __attribute__ ((__nothrow__ , __leaf__));







extern long double scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__));
# 400 "/usr/include/math.h" 2 3 4
# 450 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32 acosf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __acosf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 asinf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __asinf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 atanf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __atanf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 atan2f32 (_Float32 __y, _Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __atan2f32 (_Float32 __y, _Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float32 cosf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __cosf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

 extern _Float32 sinf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __sinf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 tanf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __tanf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32 coshf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __coshf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 sinhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __sinhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 tanhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __tanhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincosf32 (_Float32 __x, _Float32 *__sinx, _Float32 *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosf32 (_Float32 __x, _Float32 *__sinx, _Float32 *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern _Float32 acoshf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __acoshf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 asinhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __asinhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 atanhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __atanhf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));





 extern _Float32 expf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __expf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 frexpf32 (_Float32 __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __frexpf32 (_Float32 __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 ldexpf32 (_Float32 __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __ldexpf32 (_Float32 __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float32 logf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __logf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 log10f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __log10f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 modff32 (_Float32 __x, _Float32 *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __modff32 (_Float32 __x, _Float32 *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern _Float32 exp10f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __exp10f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32 expm1f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __expm1f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 log1pf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __log1pf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 logbf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __logbf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32 exp2f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __exp2f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 log2f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __log2f32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));






 extern _Float32 powf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __powf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 sqrtf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __sqrtf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32 hypotf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __hypotf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32 cbrtf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __cbrtf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32 ceilf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __ceilf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32 fabsf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __fabsf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32 floorf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __floorf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32 fmodf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __fmodf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__));
# 198 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32 copysignf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __copysignf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float32 nanf32 (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __nanf32 (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 220 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32 j0f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __j0f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32 j1f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __j1f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32 jnf32 (int, _Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __jnf32 (int, _Float32) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32 y0f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __y0f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32 y1f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __y1f32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32 ynf32 (int, _Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __ynf32 (int, _Float32) __attribute__ ((__nothrow__ , __leaf__));





extern _Float32 erff32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __erff32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32 erfcf32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __erfcf32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32 lgammaf32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __lgammaf32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32 tgammaf32 (_Float32) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __tgammaf32 (_Float32) __attribute__ ((__nothrow__ , __leaf__));
# 252 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32 lgammaf32_r (_Float32, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __lgammaf32_r (_Float32, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32 rintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __rintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 nextafterf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __nextafterf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32 nextdownf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __nextdownf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32 nextupf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __nextupf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32 remainderf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __remainderf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32 scalbnf32 (_Float32 __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __scalbnf32 (_Float32 __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogbf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogbf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32 scalblnf32 (_Float32 __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __scalblnf32 (_Float32 __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32 nearbyintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __nearbyintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32 roundf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __roundf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern _Float32 truncf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __truncf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float32 remquof32 (_Float32 __x, _Float32 __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __remquof32 (_Float32 __x, _Float32 __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32 fdimf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __fdimf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 fmaxf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __fmaxf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32 fminf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __fminf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32 fmaf32 (_Float32 __x, _Float32 __y, _Float32 __z) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __fmaf32 (_Float32 __x, _Float32 __y, _Float32 __z) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32 roundevenf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __roundevenf32 (_Float32 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfpf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfpf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpxf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpxf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpxf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpxf32 (_Float32 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalizef32 (_Float32 *__cx, const _Float32 *__x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32 fmaxmagf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __fmaxmagf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32 fminmagf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32 __fminmagf32 (_Float32 __x, _Float32 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorderf32 (const _Float32 *__x, const _Float32 *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermagf32 (const _Float32 *__x, const _Float32 *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern _Float32 getpayloadf32 (const _Float32 *__x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32 __getpayloadf32 (const _Float32 *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadf32 (_Float32 *__x, _Float32 __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsigf32 (_Float32 *__x, _Float32 __payload) __attribute__ ((__nothrow__ , __leaf__));
# 451 "/usr/include/math.h" 2 3 4
# 467 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64 acosf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __acosf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 asinf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __asinf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 atanf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __atanf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 atan2f64 (_Float64 __y, _Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __atan2f64 (_Float64 __y, _Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float64 cosf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __cosf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

 extern _Float64 sinf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __sinf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 tanf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __tanf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64 coshf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __coshf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 sinhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __sinhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 tanhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __tanhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincosf64 (_Float64 __x, _Float64 *__sinx, _Float64 *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosf64 (_Float64 __x, _Float64 *__sinx, _Float64 *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern _Float64 acoshf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __acoshf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 asinhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __asinhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 atanhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __atanhf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));





 extern _Float64 expf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __expf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 frexpf64 (_Float64 __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __frexpf64 (_Float64 __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 ldexpf64 (_Float64 __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __ldexpf64 (_Float64 __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float64 logf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __logf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 log10f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __log10f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 modff64 (_Float64 __x, _Float64 *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __modff64 (_Float64 __x, _Float64 *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern _Float64 exp10f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __exp10f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64 expm1f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __expm1f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 log1pf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __log1pf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 logbf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __logbf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64 exp2f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __exp2f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 log2f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __log2f64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));






 extern _Float64 powf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __powf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 sqrtf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __sqrtf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 hypotf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __hypotf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64 cbrtf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __cbrtf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64 ceilf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __ceilf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64 fabsf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __fabsf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64 floorf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __floorf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64 fmodf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __fmodf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));
# 198 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64 copysignf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __copysignf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float64 nanf64 (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __nanf64 (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 220 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64 j0f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __j0f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64 j1f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __j1f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64 jnf64 (int, _Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __jnf64 (int, _Float64) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64 y0f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __y0f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64 y1f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __y1f64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64 ynf64 (int, _Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __ynf64 (int, _Float64) __attribute__ ((__nothrow__ , __leaf__));





extern _Float64 erff64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __erff64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64 erfcf64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __erfcf64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64 lgammaf64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __lgammaf64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64 tgammaf64 (_Float64) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __tgammaf64 (_Float64) __attribute__ ((__nothrow__ , __leaf__));
# 252 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64 lgammaf64_r (_Float64, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __lgammaf64_r (_Float64, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64 rintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __rintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 nextafterf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __nextafterf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64 nextdownf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __nextdownf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64 nextupf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __nextupf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 remainderf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __remainderf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 scalbnf64 (_Float64 __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __scalbnf64 (_Float64 __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogbf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogbf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64 scalblnf64 (_Float64 __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __scalblnf64 (_Float64 __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 nearbyintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __nearbyintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 roundf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __roundf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern _Float64 truncf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __truncf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float64 remquof64 (_Float64 __x, _Float64 __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __remquof64 (_Float64 __x, _Float64 __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 fdimf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __fdimf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 fmaxf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __fmaxf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64 fminf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __fminf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64 fmaf64 (_Float64 __x, _Float64 __y, _Float64 __z) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __fmaf64 (_Float64 __x, _Float64 __y, _Float64 __z) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64 roundevenf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __roundevenf64 (_Float64 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfpf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfpf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpxf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpxf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpxf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpxf64 (_Float64 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalizef64 (_Float64 *__cx, const _Float64 *__x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64 fmaxmagf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __fmaxmagf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64 fminmagf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64 __fminmagf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorderf64 (const _Float64 *__x, const _Float64 *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermagf64 (const _Float64 *__x, const _Float64 *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern _Float64 getpayloadf64 (const _Float64 *__x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64 __getpayloadf64 (const _Float64 *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadf64 (_Float64 *__x, _Float64 __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsigf64 (_Float64 *__x, _Float64 __payload) __attribute__ ((__nothrow__ , __leaf__));
# 468 "/usr/include/math.h" 2 3 4
# 481 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinff128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finitef128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnanf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsigf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 482 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern _Float128 acosf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __acosf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 asinf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __asinf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 atanf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __atanf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 atan2f128 (_Float128 __y, _Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __atan2f128 (_Float128 __y, _Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float128 cosf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __cosf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

 extern _Float128 sinf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __sinf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 tanf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __tanf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float128 coshf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __coshf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 sinhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __sinhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 tanhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __tanhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincosf128 (_Float128 __x, _Float128 *__sinx, _Float128 *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosf128 (_Float128 __x, _Float128 *__sinx, _Float128 *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern _Float128 acoshf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __acoshf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 asinhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __asinhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 atanhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __atanhf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));





 extern _Float128 expf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __expf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 frexpf128 (_Float128 __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __frexpf128 (_Float128 __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 ldexpf128 (_Float128 __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __ldexpf128 (_Float128 __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float128 logf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __logf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 log10f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __log10f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 modff128 (_Float128 __x, _Float128 *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __modff128 (_Float128 __x, _Float128 *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern _Float128 exp10f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __exp10f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float128 expm1f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __expm1f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 log1pf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __log1pf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 logbf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __logbf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float128 exp2f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __exp2f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 log2f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __log2f128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));






 extern _Float128 powf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __powf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 sqrtf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __sqrtf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 hypotf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __hypotf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));




extern _Float128 cbrtf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __cbrtf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float128 ceilf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __ceilf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float128 fabsf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __fabsf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float128 floorf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __floorf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float128 fmodf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __fmodf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));
# 198 "/usr/include/bits/mathcalls.h" 3 4
extern _Float128 copysignf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __copysignf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float128 nanf128 (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __nanf128 (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 220 "/usr/include/bits/mathcalls.h" 3 4
extern _Float128 j0f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __j0f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));
extern _Float128 j1f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __j1f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));
extern _Float128 jnf128 (int, _Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __jnf128 (int, _Float128) __attribute__ ((__nothrow__ , __leaf__));
extern _Float128 y0f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __y0f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));
extern _Float128 y1f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __y1f128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));
extern _Float128 ynf128 (int, _Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __ynf128 (int, _Float128) __attribute__ ((__nothrow__ , __leaf__));





extern _Float128 erff128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __erff128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));
extern _Float128 erfcf128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __erfcf128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));
extern _Float128 lgammaf128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __lgammaf128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));




extern _Float128 tgammaf128 (_Float128) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __tgammaf128 (_Float128) __attribute__ ((__nothrow__ , __leaf__));
# 252 "/usr/include/bits/mathcalls.h" 3 4
extern _Float128 lgammaf128_r (_Float128, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __lgammaf128_r (_Float128, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern _Float128 rintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __rintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 nextafterf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __nextafterf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));






extern _Float128 nextdownf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __nextdownf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float128 nextupf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __nextupf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 remainderf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __remainderf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 scalbnf128 (_Float128 __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __scalbnf128 (_Float128 __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogbf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogbf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float128 scalblnf128 (_Float128 __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __scalblnf128 (_Float128 __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 nearbyintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __nearbyintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 roundf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __roundf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern _Float128 truncf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __truncf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float128 remquof128 (_Float128 __x, _Float128 __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __remquof128 (_Float128 __x, _Float128 __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 fdimf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __fdimf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float128 fmaxf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __fmaxf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float128 fminf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __fminf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float128 fmaf128 (_Float128 __x, _Float128 __y, _Float128 __z) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __fmaf128 (_Float128 __x, _Float128 __y, _Float128 __z) __attribute__ ((__nothrow__ , __leaf__));




extern _Float128 roundevenf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __roundevenf128 (_Float128 __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfpf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfpf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpxf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpxf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpxf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpxf128 (_Float128 __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalizef128 (_Float128 *__cx, const _Float128 *__x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float128 fmaxmagf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __fmaxmagf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float128 fminmagf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float128 __fminmagf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorderf128 (const _Float128 *__x, const _Float128 *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermagf128 (const _Float128 *__x, const _Float128 *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern _Float128 getpayloadf128 (const _Float128 *__x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float128 __getpayloadf128 (const _Float128 *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadf128 (_Float128 *__x, _Float128 __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsigf128 (_Float128 *__x, _Float128 __payload) __attribute__ ((__nothrow__ , __leaf__));
# 485 "/usr/include/math.h" 2 3 4
# 501 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32x acosf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __acosf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x asinf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __asinf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x atanf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __atanf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x atan2f32x (_Float32x __y, _Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __atan2f32x (_Float32x __y, _Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float32x cosf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __cosf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

 extern _Float32x sinf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __sinf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x tanf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __tanf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32x coshf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __coshf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x sinhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __sinhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x tanhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __tanhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincosf32x (_Float32x __x, _Float32x *__sinx, _Float32x *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosf32x (_Float32x __x, _Float32x *__sinx, _Float32x *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern _Float32x acoshf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __acoshf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x asinhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __asinhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x atanhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __atanhf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));





 extern _Float32x expf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __expf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x frexpf32x (_Float32x __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __frexpf32x (_Float32x __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x ldexpf32x (_Float32x __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __ldexpf32x (_Float32x __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float32x logf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __logf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x log10f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __log10f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x modff32x (_Float32x __x, _Float32x *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __modff32x (_Float32x __x, _Float32x *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern _Float32x exp10f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __exp10f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32x expm1f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __expm1f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x log1pf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __log1pf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x logbf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __logbf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32x exp2f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __exp2f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x log2f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __log2f32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));






 extern _Float32x powf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __powf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x sqrtf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __sqrtf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x hypotf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __hypotf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32x cbrtf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __cbrtf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32x ceilf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __ceilf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32x fabsf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __fabsf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32x floorf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __floorf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32x fmodf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __fmodf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));
# 198 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32x copysignf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __copysignf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float32x nanf32x (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __nanf32x (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 220 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32x j0f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __j0f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32x j1f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __j1f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32x jnf32x (int, _Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __jnf32x (int, _Float32x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32x y0f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __y0f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32x y1f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __y1f32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32x ynf32x (int, _Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __ynf32x (int, _Float32x) __attribute__ ((__nothrow__ , __leaf__));





extern _Float32x erff32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __erff32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32x erfcf32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __erfcf32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float32x lgammaf32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __lgammaf32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32x tgammaf32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __tgammaf32x (_Float32x) __attribute__ ((__nothrow__ , __leaf__));
# 252 "/usr/include/bits/mathcalls.h" 3 4
extern _Float32x lgammaf32x_r (_Float32x, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __lgammaf32x_r (_Float32x, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32x rintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __rintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x nextafterf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __nextafterf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32x nextdownf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __nextdownf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float32x nextupf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __nextupf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x remainderf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __remainderf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x scalbnf32x (_Float32x __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __scalbnf32x (_Float32x __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogbf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogbf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32x scalblnf32x (_Float32x __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __scalblnf32x (_Float32x __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x nearbyintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __nearbyintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x roundf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __roundf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern _Float32x truncf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __truncf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float32x remquof32x (_Float32x __x, _Float32x __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __remquof32x (_Float32x __x, _Float32x __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x fdimf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __fdimf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x fmaxf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __fmaxf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32x fminf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __fminf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32x fmaf32x (_Float32x __x, _Float32x __y, _Float32x __z) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __fmaf32x (_Float32x __x, _Float32x __y, _Float32x __z) __attribute__ ((__nothrow__ , __leaf__));




extern _Float32x roundevenf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __roundevenf32x (_Float32x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfpf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfpf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpxf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpxf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpxf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpxf32x (_Float32x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalizef32x (_Float32x *__cx, const _Float32x *__x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float32x fmaxmagf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __fmaxmagf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float32x fminmagf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float32x __fminmagf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorderf32x (const _Float32x *__x, const _Float32x *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermagf32x (const _Float32x *__x, const _Float32x *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern _Float32x getpayloadf32x (const _Float32x *__x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float32x __getpayloadf32x (const _Float32x *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadf32x (_Float32x *__x, _Float32x __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsigf32x (_Float32x *__x, _Float32x __payload) __attribute__ ((__nothrow__ , __leaf__));
# 502 "/usr/include/math.h" 2 3 4
# 518 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64x acosf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __acosf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x asinf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __asinf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x atanf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __atanf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x atan2f64x (_Float64x __y, _Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __atan2f64x (_Float64x __y, _Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float64x cosf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __cosf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

 extern _Float64x sinf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __sinf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x tanf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __tanf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64x coshf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __coshf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x sinhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __sinhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x tanhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __tanhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));



 extern void sincosf64x (_Float64x __x, _Float64x *__sinx, _Float64x *__cosx) __attribute__ ((__nothrow__ , __leaf__)); extern void __sincosf64x (_Float64x __x, _Float64x *__sinx, _Float64x *__cosx) __attribute__ ((__nothrow__ , __leaf__))
                                                        ;




extern _Float64x acoshf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __acoshf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x asinhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __asinhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x atanhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __atanhf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));





 extern _Float64x expf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __expf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x frexpf64x (_Float64x __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __frexpf64x (_Float64x __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x ldexpf64x (_Float64x __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __ldexpf64x (_Float64x __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern _Float64x logf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __logf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x log10f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __log10f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x modff64x (_Float64x __x, _Float64x *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __modff64x (_Float64x __x, _Float64x *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern _Float64x exp10f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __exp10f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64x expm1f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __expm1f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x log1pf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __log1pf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x logbf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __logbf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64x exp2f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __exp2f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x log2f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __log2f64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));






 extern _Float64x powf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __powf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x sqrtf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __sqrtf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x hypotf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __hypotf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64x cbrtf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __cbrtf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64x ceilf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __ceilf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64x fabsf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __fabsf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64x floorf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __floorf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64x fmodf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __fmodf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));
# 198 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64x copysignf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __copysignf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float64x nanf64x (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __nanf64x (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 220 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64x j0f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __j0f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64x j1f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __j1f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64x jnf64x (int, _Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __jnf64x (int, _Float64x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64x y0f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __y0f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64x y1f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __y1f64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64x ynf64x (int, _Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __ynf64x (int, _Float64x) __attribute__ ((__nothrow__ , __leaf__));





extern _Float64x erff64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __erff64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64x erfcf64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __erfcf64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));
extern _Float64x lgammaf64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __lgammaf64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64x tgammaf64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __tgammaf64x (_Float64x) __attribute__ ((__nothrow__ , __leaf__));
# 252 "/usr/include/bits/mathcalls.h" 3 4
extern _Float64x lgammaf64x_r (_Float64x, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __lgammaf64x_r (_Float64x, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64x rintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __rintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x nextafterf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __nextafterf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64x nextdownf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __nextdownf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));

extern _Float64x nextupf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __nextupf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x remainderf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __remainderf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x scalbnf64x (_Float64x __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __scalbnf64x (_Float64x __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));




extern long int llogbf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __llogbf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64x scalblnf64x (_Float64x __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __scalblnf64x (_Float64x __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x nearbyintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __nearbyintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x roundf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __roundf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern _Float64x truncf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __truncf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern _Float64x remquof64x (_Float64x __x, _Float64x __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __remquof64x (_Float64x __x, _Float64x __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x fdimf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __fdimf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x fmaxf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __fmaxf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64x fminf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __fminf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64x fmaf64x (_Float64x __x, _Float64x __y, _Float64x __z) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __fmaf64x (_Float64x __x, _Float64x __y, _Float64x __z) __attribute__ ((__nothrow__ , __leaf__));




extern _Float64x roundevenf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __roundevenf64x (_Float64x __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern __intmax_t fromfpf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                            ;



extern __uintmax_t ufromfpf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                              ;




extern __intmax_t fromfpxf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __intmax_t __fromfpxf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                             ;




extern __uintmax_t ufromfpxf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__)); extern __uintmax_t __ufromfpxf64x (_Float64x __x, int __round, unsigned int __width) __attribute__ ((__nothrow__ , __leaf__))
                               ;


extern int canonicalizef64x (_Float64x *__cx, const _Float64x *__x) __attribute__ ((__nothrow__ , __leaf__));






extern _Float64x fmaxmagf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __fmaxmagf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern _Float64x fminmagf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern _Float64x __fminmagf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int totalorderf64x (const _Float64x *__x, const _Float64x *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern int totalordermagf64x (const _Float64x *__x, const _Float64x *__y) __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__pure__));


extern _Float64x getpayloadf64x (const _Float64x *__x) __attribute__ ((__nothrow__ , __leaf__)); extern _Float64x __getpayloadf64x (const _Float64x *__x) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadf64x (_Float64x *__x, _Float64x __payload) __attribute__ ((__nothrow__ , __leaf__));


extern int setpayloadsigf64x (_Float64x *__x, _Float64x __payload) __attribute__ ((__nothrow__ , __leaf__));
# 519 "/usr/include/math.h" 2 3 4
# 566 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern float fadd (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fdiv (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fmul (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fsub (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
# 567 "/usr/include/math.h" 2 3 4
# 585 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern float faddl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fdivl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fmull (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fsubl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 586 "/usr/include/math.h" 2 3 4
# 611 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern double daddl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double ddivl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double dmull (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double dsubl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 612 "/usr/include/math.h" 2 3 4
# 691 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float32 f32addf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32divf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32mulf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32subf32x (_Float32x __x, _Float32x __y) __attribute__ ((__nothrow__ , __leaf__));
# 692 "/usr/include/math.h" 2 3 4
# 701 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float32 f32addf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32divf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32mulf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32subf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));
# 702 "/usr/include/math.h" 2 3 4
# 711 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float32 f32addf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32divf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32mulf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32subf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));
# 712 "/usr/include/math.h" 2 3 4
# 721 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float32 f32addf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32divf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32mulf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32 f32subf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));
# 722 "/usr/include/math.h" 2 3 4
# 741 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float32x f32xaddf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xdivf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xmulf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xsubf64 (_Float64 __x, _Float64 __y) __attribute__ ((__nothrow__ , __leaf__));
# 742 "/usr/include/math.h" 2 3 4
# 751 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float32x f32xaddf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xdivf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xmulf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xsubf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));
# 752 "/usr/include/math.h" 2 3 4
# 761 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float32x f32xaddf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xdivf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xmulf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float32x f32xsubf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));
# 762 "/usr/include/math.h" 2 3 4
# 781 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float64 f64addf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 f64divf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 f64mulf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 f64subf64x (_Float64x __x, _Float64x __y) __attribute__ ((__nothrow__ , __leaf__));
# 782 "/usr/include/math.h" 2 3 4
# 791 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float64 f64addf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 f64divf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 f64mulf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64 f64subf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));
# 792 "/usr/include/math.h" 2 3 4
# 811 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls-narrow.h" 1 3 4
# 24 "/usr/include/bits/mathcalls-narrow.h" 3 4
extern _Float64x f64xaddf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x f64xdivf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x f64xmulf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern _Float64x f64xsubf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));
# 812 "/usr/include/math.h" 2 3 4
# 848 "/usr/include/math.h" 3 4
extern int signgam;
# 928 "/usr/include/math.h" 3 4
enum
  {
    FP_NAN =

      0,
    FP_INFINITE =

      1,
    FP_ZERO =

      2,
    FP_SUBNORMAL =

      3,
    FP_NORMAL =

      4
  };
# 1048 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/iscanonical.h" 1 3 4
# 23 "/usr/include/bits/iscanonical.h" 3 4
extern int __iscanonicall (long double __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 1049 "/usr/include/math.h" 2 3 4
# 1400 "/usr/include/math.h" 3 4

# 24 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 99 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 25 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/include/wchar.h" 1 3 4
# 27 "/usr/include/wchar.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/wchar.h" 2 3 4







# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 209 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 321 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 3 4
typedef int wchar_t;
# 36 "/usr/include/wchar.h" 2 3 4





# 1 "/usr/include/bits/types/wint_t.h" 1 3 4
# 20 "/usr/include/bits/types/wint_t.h" 3 4
typedef unsigned int wint_t;
# 42 "/usr/include/wchar.h" 2 3 4
# 1 "/usr/include/bits/types/mbstate_t.h" 1 3 4



# 1 "/usr/include/bits/types/__mbstate_t.h" 1 3 4
# 13 "/usr/include/bits/types/__mbstate_t.h" 3 4
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 5 "/usr/include/bits/types/mbstate_t.h" 2 3 4

typedef __mbstate_t mbstate_t;
# 43 "/usr/include/wchar.h" 2 3 4
# 1 "/usr/include/bits/types/__FILE.h" 1 3 4



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 44 "/usr/include/wchar.h" 2 3 4


# 1 "/usr/include/bits/types/FILE.h" 1 3 4



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 47 "/usr/include/wchar.h" 2 3 4


# 1 "/usr/include/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/bits/types/locale_t.h" 3 4
# 1 "/usr/include/bits/types/__locale_t.h" 1 3 4
# 28 "/usr/include/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 50 "/usr/include/wchar.h" 2 3 4
# 79 "/usr/include/wchar.h" 3 4




struct tm;



extern wchar_t *wcscpy (wchar_t *__restrict __dest,
   const wchar_t *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern wchar_t *wcsncpy (wchar_t *__restrict __dest,
    const wchar_t *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern wchar_t *wcscat (wchar_t *__restrict __dest,
   const wchar_t *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern wchar_t *wcsncat (wchar_t *__restrict __dest,
    const wchar_t *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int wcscmp (const wchar_t *__s1, const wchar_t *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int wcsncmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));



extern int wcscasecmp (const wchar_t *__s1, const wchar_t *__s2) __attribute__ ((__nothrow__ , __leaf__));


extern int wcsncasecmp (const wchar_t *__s1, const wchar_t *__s2,
   size_t __n) __attribute__ ((__nothrow__ , __leaf__));



extern int wcscasecmp_l (const wchar_t *__s1, const wchar_t *__s2,
    locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));

extern int wcsncasecmp_l (const wchar_t *__s1, const wchar_t *__s2,
     size_t __n, locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));




extern int wcscoll (const wchar_t *__s1, const wchar_t *__s2) __attribute__ ((__nothrow__ , __leaf__));



extern size_t wcsxfrm (wchar_t *__restrict __s1,
         const wchar_t *__restrict __s2, size_t __n) __attribute__ ((__nothrow__ , __leaf__));







extern int wcscoll_l (const wchar_t *__s1, const wchar_t *__s2,
        locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));




extern size_t wcsxfrm_l (wchar_t *__s1, const wchar_t *__s2,
    size_t __n, locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));


extern wchar_t *wcsdup (const wchar_t *__s) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (__builtin_free, 1)));
# 165 "/usr/include/wchar.h" 3 4
extern wchar_t *wcschr (const wchar_t *__wcs, wchar_t __wc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
# 175 "/usr/include/wchar.h" 3 4
extern wchar_t *wcsrchr (const wchar_t *__wcs, wchar_t __wc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));





extern wchar_t *wcschrnul (const wchar_t *__s, wchar_t __wc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));




extern size_t wcscspn (const wchar_t *__wcs, const wchar_t *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));


extern size_t wcsspn (const wchar_t *__wcs, const wchar_t *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
# 202 "/usr/include/wchar.h" 3 4
extern wchar_t *wcspbrk (const wchar_t *__wcs, const wchar_t *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
# 213 "/usr/include/wchar.h" 3 4
extern wchar_t *wcsstr (const wchar_t *__haystack, const wchar_t *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));



extern wchar_t *wcstok (wchar_t *__restrict __s,
   const wchar_t *__restrict __delim,
   wchar_t **__restrict __ptr) __attribute__ ((__nothrow__ , __leaf__));


extern size_t wcslen (const wchar_t *__s) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
# 234 "/usr/include/wchar.h" 3 4
extern wchar_t *wcswcs (const wchar_t *__haystack, const wchar_t *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));





extern size_t wcsnlen (const wchar_t *__s, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
# 254 "/usr/include/wchar.h" 3 4
extern wchar_t *wmemchr (const wchar_t *__s, wchar_t __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));



extern int wmemcmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));


extern wchar_t *wmemcpy (wchar_t *__restrict __s1,
    const wchar_t *__restrict __s2, size_t __n) __attribute__ ((__nothrow__ , __leaf__));



extern wchar_t *wmemmove (wchar_t *__s1, const wchar_t *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));


extern wchar_t *wmemset (wchar_t *__s, wchar_t __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern wchar_t *wmempcpy (wchar_t *__restrict __s1,
     const wchar_t *__restrict __s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));





extern wint_t btowc (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int wctob (wint_t __c) __attribute__ ((__nothrow__ , __leaf__));



extern int mbsinit (const mbstate_t *__ps) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));



extern size_t mbrtowc (wchar_t *__restrict __pwc,
         const char *__restrict __s, size_t __n,
         mbstate_t *__restrict __p) __attribute__ ((__nothrow__ , __leaf__));


extern size_t wcrtomb (char *__restrict __s, wchar_t __wc,
         mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));


extern size_t __mbrlen (const char *__restrict __s, size_t __n,
   mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));
extern size_t mbrlen (const char *__restrict __s, size_t __n,
        mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));







extern wint_t __btowc_alias (int __c) __asm ("btowc");
extern __inline __attribute__ ((__gnu_inline__)) wint_t
__attribute__ ((__nothrow__ , __leaf__)) btowc (int __c)
{ return (__builtin_constant_p (__c) && __c >= '\0' && __c <= '\x7f'
   ? (wint_t) __c : __btowc_alias (__c)); }

extern int __wctob_alias (wint_t __c) __asm ("wctob");
extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) wctob (wint_t __wc)
{ return (__builtin_constant_p (__wc) && __wc >= L'\0' && __wc <= L'\x7f'
   ? (int) __wc : __wctob_alias (__wc)); }

extern __inline __attribute__ ((__gnu_inline__)) size_t
__attribute__ ((__nothrow__ , __leaf__)) mbrlen (const char *__restrict __s, size_t __n, mbstate_t *__restrict __ps)

{ return (__ps != ((void *)0)
   ? mbrtowc (((void *)0), __s, __n, __ps) : __mbrlen (__s, __n, ((void *)0))); }




extern size_t mbsrtowcs (wchar_t *__restrict __dst,
    const char **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));



extern size_t wcsrtombs (char *__restrict __dst,
    const wchar_t **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));





extern size_t mbsnrtowcs (wchar_t *__restrict __dst,
     const char **__restrict __src, size_t __nmc,
     size_t __len, mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));



extern size_t wcsnrtombs (char *__restrict __dst,
     const wchar_t **__restrict __src,
     size_t __nwc, size_t __len,
     mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));






extern int wcwidth (wchar_t __c) __attribute__ ((__nothrow__ , __leaf__));



extern int wcswidth (const wchar_t *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));





extern double wcstod (const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));



extern float wcstof (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));
extern long double wcstold (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));
# 397 "/usr/include/wchar.h" 3 4
extern _Float32 wcstof32 (const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 wcstof64 (const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 wcstof128 (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x wcstof32x (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x wcstof64x (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));
# 429 "/usr/include/wchar.h" 3 4
extern long int wcstol (const wchar_t *__restrict __nptr,
   wchar_t **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));



extern unsigned long int wcstoul (const wchar_t *__restrict __nptr,
      wchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));




__extension__
extern long long int wcstoll (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));



__extension__
extern unsigned long long int wcstoull (const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr,
     int __base) __attribute__ ((__nothrow__ , __leaf__));





__extension__
extern long long int wcstoq (const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));



__extension__
extern unsigned long long int wcstouq (const wchar_t *__restrict __nptr,
           wchar_t **__restrict __endptr,
           int __base) __attribute__ ((__nothrow__ , __leaf__));






extern long int wcstol_l (const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr, int __base,
     locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));

extern unsigned long int wcstoul_l (const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr,
        int __base, locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));

__extension__
extern long long int wcstoll_l (const wchar_t *__restrict __nptr,
    wchar_t **__restrict __endptr,
    int __base, locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));

__extension__
extern unsigned long long int wcstoull_l (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr,
       int __base, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__));

extern double wcstod_l (const wchar_t *__restrict __nptr,
   wchar_t **__restrict __endptr, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__));

extern float wcstof_l (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__));

extern long double wcstold_l (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr,
         locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
# 512 "/usr/include/wchar.h" 3 4
extern _Float32 wcstof32_l (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr,
       locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64 wcstof64_l (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr,
       locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));



extern _Float128 wcstof128_l (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr,
         locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));



extern _Float32x wcstof32x_l (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr,
         locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));



extern _Float64x wcstof64x_l (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr,
         locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
# 552 "/usr/include/wchar.h" 3 4
extern wchar_t *wcpcpy (wchar_t *__restrict __dest,
   const wchar_t *__restrict __src) __attribute__ ((__nothrow__ , __leaf__));



extern wchar_t *wcpncpy (wchar_t *__restrict __dest,
    const wchar_t *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));
# 581 "/usr/include/wchar.h" 3 4
extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) ;





extern int fwide (__FILE *__fp, int __mode) __attribute__ ((__nothrow__ , __leaf__));






extern int fwprintf (__FILE *__restrict __stream,
       const wchar_t *__restrict __format, ...)
                                                           ;




extern int wprintf (const wchar_t *__restrict __format, ...)
                                                           ;

extern int swprintf (wchar_t *__restrict __s, size_t __n,
       const wchar_t *__restrict __format, ...)
     __attribute__ ((__nothrow__ , __leaf__)) ;





extern int vfwprintf (__FILE *__restrict __s,
        const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
                                                           ;




extern int vwprintf (const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                           ;


extern int vswprintf (wchar_t *__restrict __s, size_t __n,
        const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) ;






extern int fwscanf (__FILE *__restrict __stream,
      const wchar_t *__restrict __format, ...)
                                                          ;




extern int wscanf (const wchar_t *__restrict __format, ...)
                                                          ;

extern int swscanf (const wchar_t *__restrict __s,
      const wchar_t *__restrict __format, ...)
     __attribute__ ((__nothrow__ , __leaf__)) ;
# 657 "/usr/include/wchar.h" 3 4
extern int fwscanf (__FILE *__restrict __stream, const wchar_t *__restrict __format, ...) __asm__ ("" "__isoc99_fwscanf")


                                                          ;
extern int wscanf (const wchar_t *__restrict __format, ...) __asm__ ("" "__isoc99_wscanf")

                                                          ;
extern int swscanf (const wchar_t *__restrict __s, const wchar_t *__restrict __format, ...) __asm__ ("" "__isoc99_swscanf") __attribute__ ((__nothrow__ , __leaf__))


                                                          ;
# 688 "/usr/include/wchar.h" 3 4
extern int vfwscanf (__FILE *__restrict __s,
       const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                          ;




extern int vwscanf (const wchar_t *__restrict __format,
      __gnuc_va_list __arg)
                                                          ;

extern int vswscanf (const wchar_t *__restrict __s,
       const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) ;







extern int vfwscanf (__FILE *__restrict __s, const wchar_t *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfwscanf")


                                                          ;
extern int vwscanf (const wchar_t *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vwscanf")

                                                          ;
extern int vswscanf (const wchar_t *__restrict __s, const wchar_t *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vswscanf") __attribute__ ((__nothrow__ , __leaf__))


                                                          ;
# 744 "/usr/include/wchar.h" 3 4
extern wint_t fgetwc (__FILE *__stream);
extern wint_t getwc (__FILE *__stream);





extern wint_t getwchar (void);






extern wint_t fputwc (wchar_t __wc, __FILE *__stream);
extern wint_t putwc (wchar_t __wc, __FILE *__stream);





extern wint_t putwchar (wchar_t __wc);







extern wchar_t *fgetws (wchar_t *__restrict __ws, int __n,
   __FILE *__restrict __stream);





extern int fputws (const wchar_t *__restrict __ws,
     __FILE *__restrict __stream);






extern wint_t ungetwc (wint_t __wc, __FILE *__stream);
# 799 "/usr/include/wchar.h" 3 4
extern wint_t getwc_unlocked (__FILE *__stream);
extern wint_t getwchar_unlocked (void);







extern wint_t fgetwc_unlocked (__FILE *__stream);







extern wint_t fputwc_unlocked (wchar_t __wc, __FILE *__stream);
# 825 "/usr/include/wchar.h" 3 4
extern wint_t putwc_unlocked (wchar_t __wc, __FILE *__stream);
extern wint_t putwchar_unlocked (wchar_t __wc);
# 835 "/usr/include/wchar.h" 3 4
extern wchar_t *fgetws_unlocked (wchar_t *__restrict __ws, int __n,
     __FILE *__restrict __stream);







extern int fputws_unlocked (const wchar_t *__restrict __ws,
       __FILE *__restrict __stream);






extern size_t wcsftime (wchar_t *__restrict __s, size_t __maxsize,
   const wchar_t *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));




extern size_t wcsftime_l (wchar_t *__restrict __s, size_t __maxsize,
     const wchar_t *__restrict __format,
     const struct tm *__restrict __tp,
     locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
# 882 "/usr/include/wchar.h" 3 4

# 26 "/home/alexturner/include/python3.15/Python.h" 2

# 1 "/usr/include/sys/types.h" 1 3 4
# 27 "/usr/include/sys/types.h" 3 4






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;






typedef __ino64_t ino_t;




typedef __ino64_t ino64_t;




typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;







typedef __off64_t off_t;




typedef __off64_t off64_t;




typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;




# 1 "/usr/include/bits/types/clock_t.h" 1 3 4






typedef __clock_t clock_t;
# 127 "/usr/include/sys/types.h" 2 3 4

# 1 "/usr/include/bits/types/clockid_t.h" 1 3 4






typedef __clockid_t clockid_t;
# 129 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/time_t.h" 1 3 4
# 10 "/usr/include/bits/types/time_t.h" 3 4
typedef __time_t time_t;
# 130 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/timer_t.h" 1 3 4






typedef __timer_t timer_t;
# 131 "/usr/include/sys/types.h" 2 3 4



typedef __useconds_t useconds_t;



typedef __suseconds_t suseconds_t;





# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 145 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;







typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;


typedef int register_t __attribute__ ((__mode__ (__word__)));
# 176 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 24 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 35 "/usr/include/bits/endian.h" 3 4
# 1 "/usr/include/bits/endianness.h" 1 3 4
# 36 "/usr/include/bits/endian.h" 2 3 4
# 25 "/usr/include/endian.h" 2 3 4
# 35 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 33 "/usr/include/bits/byteswap.h" 3 4
static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{

  return __builtin_bswap16 (__bsx);



}






static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{

  return __builtin_bswap32 (__bsx);



}
# 69 "/usr/include/bits/byteswap.h" 3 4
__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{

  return __builtin_bswap64 (__bsx);



}
# 36 "/usr/include/endian.h" 2 3 4
# 1 "/usr/include/bits/uintn-identity.h" 1 3 4
# 32 "/usr/include/bits/uintn-identity.h" 3 4
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 37 "/usr/include/endian.h" 2 3 4
# 177 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/select.h" 1 3 4
# 30 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 31 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/types/sigset_t.h" 1 3 4



# 1 "/usr/include/bits/types/__sigset_t.h" 1 3 4




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/bits/types/sigset_t.h" 2 3 4


typedef __sigset_t sigset_t;
# 34 "/usr/include/sys/select.h" 2 3 4



# 1 "/usr/include/bits/types/struct_timeval.h" 1 3 4







struct timeval
{




  __time_t tv_sec;
  __suseconds_t tv_usec;

};
# 38 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/types/struct_timespec.h" 1 3 4
# 11 "/usr/include/bits/types/struct_timespec.h" 3 4
struct timespec
{



  __time_t tv_sec;




  __syscall_slong_t tv_nsec;
# 31 "/usr/include/bits/types/struct_timespec.h" 3 4
};
# 40 "/usr/include/sys/select.h" 2 3 4
# 49 "/usr/include/sys/select.h" 3 4
typedef long int __fd_mask;
# 59 "/usr/include/sys/select.h" 3 4
typedef struct
  {



    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];





  } fd_set;






typedef __fd_mask fd_mask;
# 91 "/usr/include/sys/select.h" 3 4

# 102 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 127 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 153 "/usr/include/sys/select.h" 3 4

# 180 "/usr/include/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;
# 205 "/usr/include/sys/types.h" 3 4
typedef __blkcnt64_t blkcnt_t;



typedef __fsblkcnt64_t fsblkcnt_t;



typedef __fsfilcnt64_t fsfilcnt_t;





typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;





# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/thread-shared-types.h" 1 3 4
# 44 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes-arch.h" 1 3 4
# 21 "/usr/include/bits/pthreadtypes-arch.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 22 "/usr/include/bits/pthreadtypes-arch.h" 2 3 4
# 45 "/usr/include/bits/thread-shared-types.h" 2 3 4

# 1 "/usr/include/bits/atomic_wide_counter.h" 1 3 4
# 25 "/usr/include/bits/atomic_wide_counter.h" 3 4
typedef union
{
  __extension__ unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
# 47 "/usr/include/bits/thread-shared-types.h" 2 3 4




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
# 76 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/struct_mutex.h" 1 3 4
# 22 "/usr/include/bits/struct_mutex.h" 3 4
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;



  int __kind;

  short __spins;
  short __elision;
  __pthread_list_t __list;
# 53 "/usr/include/bits/struct_mutex.h" 3 4
};
# 77 "/usr/include/bits/thread-shared-types.h" 2 3 4
# 89 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/struct_rwlock.h" 1 3 4
# 23 "/usr/include/bits/struct_rwlock.h" 3 4
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;




  unsigned char __pad1[7];


  unsigned long int __pad2;


  unsigned int __flags;
# 55 "/usr/include/bits/struct_rwlock.h" 3 4
};
# 90 "/usr/include/bits/thread-shared-types.h" 2 3 4




struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __glibc_unused___g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};

typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;

typedef struct
{
  int __data ;
} __once_flag;
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 228 "/usr/include/sys/types.h" 2 3 4



# 28 "/home/alexturner/include/python3.15/Python.h" 2
# 37 "/home/alexturner/include/python3.15/Python.h"
# 1 "/usr/include/errno.h" 1 3 4
# 28 "/usr/include/errno.h" 3 4
# 1 "/usr/include/bits/errno.h" 1 3 4
# 26 "/usr/include/bits/errno.h" 3 4
# 1 "/usr/include/linux/errno.h" 1 3 4
# 1 "/usr/include/asm/errno.h" 1 3 4
# 1 "/usr/include/asm-generic/errno.h" 1 3 4




# 1 "/usr/include/asm-generic/errno-base.h" 1 3 4
# 6 "/usr/include/asm-generic/errno.h" 2 3 4
# 2 "/usr/include/asm/errno.h" 2 3 4
# 2 "/usr/include/linux/errno.h" 2 3 4
# 27 "/usr/include/bits/errno.h" 2 3 4
# 29 "/usr/include/errno.h" 2 3 4








extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));







extern char *program_invocation_name;
extern char *program_invocation_short_name;

# 1 "/usr/include/bits/types/error_t.h" 1 3 4
# 22 "/usr/include/bits/types/error_t.h" 3 4
typedef int error_t;
# 49 "/usr/include/errno.h" 2 3 4




# 38 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 34 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/include/bits/types/__fpos_t.h" 1 3 4
# 10 "/usr/include/bits/types/__fpos_t.h" 3 4
typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 40 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/__fpos64_t.h" 1 3 4
# 10 "/usr/include/bits/types/__fpos64_t.h" 3 4
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 41 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/bits/types/struct_FILE.h" 1 3 4
# 35 "/usr/include/bits/types/struct_FILE.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 36 "/usr/include/bits/types/struct_FILE.h" 2 3 4

struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;






  int _flags2;

  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;
# 117 "/usr/include/bits/types/struct_FILE.h" 3 4
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};
# 44 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/bits/types/cookie_io_functions_t.h" 1 3 4
# 27 "/usr/include/bits/types/cookie_io_functions_t.h" 3 4
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);







typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);







typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);


typedef int cookie_close_function_t (void *__cookie);






typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
# 47 "/usr/include/stdio.h" 2 3 4
# 86 "/usr/include/stdio.h" 3 4
typedef __fpos64_t fpos_t;


typedef __fpos64_t fpos64_t;
# 133 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 134 "/usr/include/stdio.h" 2 3 4



extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
# 164 "/usr/include/stdio.h" 3 4
extern int renameat2 (int __oldfd, const char *__old, int __newfd,
        const char *__new, unsigned int __flags) __attribute__ ((__nothrow__ , __leaf__));






extern int fclose (FILE *__stream);
# 186 "/usr/include/stdio.h" 3 4
extern FILE *tmpfile (void) __asm__ ("" "tmpfile64")
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;






extern FILE *tmpfile64 (void)
   __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;



extern char *tmpnam (char[20]) __attribute__ ((__nothrow__ , __leaf__)) ;




extern char *tmpnam_r (char __s[20]) __attribute__ ((__nothrow__ , __leaf__)) ;
# 216 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
   __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (__builtin_free, 1)));






extern int fflush (FILE *__stream);
# 233 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 243 "/usr/include/stdio.h" 3 4
extern int fcloseall (void);
# 264 "/usr/include/stdio.h" 3 4
extern FILE *fopen (const char *__restrict __filename, const char *__restrict __modes) __asm__ ("" "fopen64")

  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern FILE *freopen (const char *__restrict __filename, const char *__restrict __modes, FILE *__restrict __stream) __asm__ ("" "freopen64")


  ;






extern FILE *fopen64 (const char *__restrict __filename,
        const char *__restrict __modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern FILE *freopen64 (const char *__restrict __filename,
   const char *__restrict __modes,
   FILE *__restrict __stream) ;




extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;





extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;





extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1)));





extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));





extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;




extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
# 428 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 453 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));





extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 507 "/usr/include/stdio.h" 3 4
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);






extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 532 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);
# 543 "/usr/include/stdio.h" 3 4
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);
# 559 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__access__ (__write_only__, 1, 2)));
# 609 "/usr/include/stdio.h" 3 4
extern char *fgets_unlocked (char *__restrict __s, int __n,
        FILE *__restrict __stream)
    __attribute__ ((__access__ (__write_only__, 1, 2)));
# 626 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) ;







extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);
# 685 "/usr/include/stdio.h" 3 4
extern int fputs_unlocked (const char *__restrict __s,
      FILE *__restrict __stream);
# 696 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);







extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);
# 738 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off64_t __off, int __whence) __asm__ ("" "fseeko64")

                  ;
extern __off64_t ftello (FILE *__stream) __asm__ ("" "ftello64");
# 762 "/usr/include/stdio.h" 3 4
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos) __asm__ ("" "fgetpos64")
                                          ;
extern int fsetpos (FILE *__stream, const fpos_t *__pos) __asm__ ("" "fsetpos64")
                                                          ;







extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) ;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);



extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;







extern void perror (const char *__s);




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 817 "/usr/include/stdio.h" 3 4
extern int pclose (FILE *__stream);





extern FILE *popen (const char *__command, const char *__modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (pclose, 1))) ;






extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1)));





extern char *cuserid (char *__s)
  __attribute__ ((__access__ (__write_only__, 1)));




struct obstack;


extern int obstack_printf (struct obstack *__restrict __obstack,
      const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
       const char *__restrict __format,
       __gnuc_va_list __args)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0)));







extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 879 "/usr/include/stdio.h" 3 4
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 896 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio.h" 1 3 4
# 38 "/usr/include/bits/stdio.h" 3 4
extern __inline __attribute__ ((__gnu_inline__)) int
vprintf (const char *__restrict __fmt, __gnuc_va_list __arg)
{
  return vfprintf (stdout, __fmt, __arg);
}



extern __inline __attribute__ ((__gnu_inline__)) int
getchar (void)
{
  return getc (stdin);
}




extern __inline __attribute__ ((__gnu_inline__)) int
fgetc_unlocked (FILE *__fp)
{
  return (__builtin_expect (((__fp)->_IO_read_ptr >= (__fp)->_IO_read_end), 0) ? __uflow (__fp) : *(unsigned char *) (__fp)->_IO_read_ptr++);
}





extern __inline __attribute__ ((__gnu_inline__)) int
getc_unlocked (FILE *__fp)
{
  return (__builtin_expect (((__fp)->_IO_read_ptr >= (__fp)->_IO_read_end), 0) ? __uflow (__fp) : *(unsigned char *) (__fp)->_IO_read_ptr++);
}


extern __inline __attribute__ ((__gnu_inline__)) int
getchar_unlocked (void)
{
  return (__builtin_expect (((stdin)->_IO_read_ptr >= (stdin)->_IO_read_end), 0) ? __uflow (stdin) : *(unsigned char *) (stdin)->_IO_read_ptr++);
}




extern __inline __attribute__ ((__gnu_inline__)) int
putchar (int __c)
{
  return putc (__c, stdout);
}




extern __inline __attribute__ ((__gnu_inline__)) int
fputc_unlocked (int __c, FILE *__stream)
{
  return (__builtin_expect (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end), 0) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}





extern __inline __attribute__ ((__gnu_inline__)) int
putc_unlocked (int __c, FILE *__stream)
{
  return (__builtin_expect (((__stream)->_IO_write_ptr >= (__stream)->_IO_write_end), 0) ? __overflow (__stream, (unsigned char) (__c)) : (unsigned char) (*(__stream)->_IO_write_ptr++ = (__c)));
}


extern __inline __attribute__ ((__gnu_inline__)) int
putchar_unlocked (int __c)
{
  return (__builtin_expect (((stdout)->_IO_write_ptr >= (stdout)->_IO_write_end), 0) ? __overflow (stdout, (unsigned char) (__c)) : (unsigned char) (*(stdout)->_IO_write_ptr++ = (__c)));
}





extern __inline __attribute__ ((__gnu_inline__)) __ssize_t
getline (char **__lineptr, size_t *__n, FILE *__stream)
{
  return __getdelim (__lineptr, __n, '\n', __stream);
}





extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) feof_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x0010) != 0);
}


extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) ferror_unlocked (FILE *__stream)
{
  return (((__stream)->_flags & 0x0020) != 0);
}
# 897 "/usr/include/stdio.h" 2 3 4







# 39 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/include/stdlib.h" 1 3 4
# 25 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 26 "/usr/include/stdlib.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 32 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/include/bits/waitflags.h" 1 3 4
# 40 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/bits/waitstatus.h" 1 3 4
# 41 "/usr/include/stdlib.h" 2 3 4
# 58 "/usr/include/stdlib.h" 3 4
typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 97 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;



extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 140 "/usr/include/stdlib.h" 3 4
extern _Float32 strtof32 (const char *__restrict __nptr,
     char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern _Float64 strtof64 (const char *__restrict __nptr,
     char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern _Float128 strtof128 (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern _Float32x strtof32x (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern _Float64x strtof64x (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 176 "/usr/include/stdlib.h" 3 4
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int strfromd (char *__dest, size_t __size, const char *__format,
       double __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));

extern int strfromf (char *__dest, size_t __size, const char *__format,
       float __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));

extern int strfroml (char *__dest, size_t __size, const char *__format,
       long double __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));
# 232 "/usr/include/stdlib.h" 3 4
extern int strfromf32 (char *__dest, size_t __size, const char * __format,
         _Float32 __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));



extern int strfromf64 (char *__dest, size_t __size, const char * __format,
         _Float64 __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));



extern int strfromf128 (char *__dest, size_t __size, const char * __format,
   _Float128 __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));



extern int strfromf32x (char *__dest, size_t __size, const char * __format,
   _Float32x __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));



extern int strfromf64x (char *__dest, size_t __size, const char * __format,
   _Float64x __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));
# 274 "/usr/include/stdlib.h" 3 4
extern long int strtol_l (const char *__restrict __nptr,
     char **__restrict __endptr, int __base,
     locale_t __loc) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

extern unsigned long int strtoul_l (const char *__restrict __nptr,
        char **__restrict __endptr,
        int __base, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
    char **__restrict __endptr, int __base,
    locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
       char **__restrict __endptr,
       int __base, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 4)));

extern double strtod_l (const char *__restrict __nptr,
   char **__restrict __endptr, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));

extern float strtof_l (const char *__restrict __nptr,
         char **__restrict __endptr, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));

extern long double strtold_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
# 316 "/usr/include/stdlib.h" 3 4
extern _Float32 strtof32_l (const char *__restrict __nptr,
       char **__restrict __endptr,
       locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));



extern _Float64 strtof64_l (const char *__restrict __nptr,
       char **__restrict __endptr,
       locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));



extern _Float128 strtof128_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));



extern _Float32x strtof32x_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));



extern _Float64x strtof64x_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));
# 360 "/usr/include/stdlib.h" 3 4
extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) atoi (const char *__nptr)
{
  return (int) strtol (__nptr, (char **) ((void *)0), 10);
}
extern __inline __attribute__ ((__gnu_inline__)) long int
__attribute__ ((__nothrow__ , __leaf__)) atol (const char *__nptr)
{
  return strtol (__nptr, (char **) ((void *)0), 10);
}


__extension__ extern __inline __attribute__ ((__gnu_inline__)) long long int
__attribute__ ((__nothrow__ , __leaf__)) atoll (const char *__nptr)
{
  return strtoll (__nptr, (char **) ((void *)0), 10);
}
# 385 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
# 401 "/usr/include/stdlib.h" 3 4
extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));



extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;






extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));


extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));







extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__))
     __attribute__ ((__alloc_size__ (2, 3)))
    __attribute__ ((__malloc__ (__builtin_free, 1)));


extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__ (reallocarray, 1)));



# 1 "/usr/include/alloca.h" 1 3 4
# 24 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 25 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 574 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) ;



extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern char *secure_getenv (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;






extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 680 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 696 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __asm__ ("" "mkstemp64")
     __attribute__ ((__nonnull__ (1))) ;





extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 718 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __asm__ ("" "mkstemps64")
                     __attribute__ ((__nonnull__ (1))) ;





extern int mkstemps64 (char *__template, int __suffixlen)
     __attribute__ ((__nonnull__ (1))) ;
# 736 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 750 "/usr/include/stdlib.h" 3 4
extern int mkostemp (char *__template, int __flags) __asm__ ("" "mkostemp64")
     __attribute__ ((__nonnull__ (1))) ;





extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
# 771 "/usr/include/stdlib.h" 3 4
extern int mkostemps (char *__template, int __suffixlen, int __flags) __asm__ ("" "mkostemps64")

     __attribute__ ((__nonnull__ (1))) ;





extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;
# 789 "/usr/include/stdlib.h" 3 4
extern int system (const char *__command) ;





extern char *canonicalize_file_name (const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__malloc__))
     __attribute__ ((__malloc__ (__builtin_free, 1))) ;
# 806 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (const void *, const void *);


typedef __compar_fn_t comparison_fn_t;



typedef int (*__compar_d_fn_t) (const void *, const void *, void *);




extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;


# 1 "/usr/include/bits/stdlib-bsearch.h" 1 3 4
# 19 "/usr/include/bits/stdlib-bsearch.h" 3 4
extern __inline __attribute__ ((__gnu_inline__)) void *
bsearch (const void *__key, const void *__base, size_t __nmemb, size_t __size,
  __compar_fn_t __compar)
{
  size_t __l, __u, __idx;
  const void *__p;
  int __comparison;

  __l = 0;
  __u = __nmemb;
  while (__l < __u)
    {
      __idx = (__l + __u) / 2;
      __p = (const void *) (((const char *) __base) + (__idx * __size));
      __comparison = (*__compar) (__key, __p);
      if (__comparison < 0)
 __u = __idx;
      else if (__comparison > 0)
 __l = __idx + 1;
      else
 {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"

   return (void *) __p;

#pragma GCC diagnostic pop

 }
    }

  return ((void *)0);
}
# 832 "/usr/include/stdlib.h" 2 3 4




extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));

extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
       __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));




extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;






extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
# 878 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));





extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__read_only__, 2)));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1, 3)))
  __attribute__ ((__access__ (__read_only__, 2)));






extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 965 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;







extern int posix_openpt (int __oflag) ;







extern int grantpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));



extern int unlockpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));




extern char *ptsname (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;






extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 2, 3)));


extern int getpt (void);






extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1021 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/stdlib-float.h" 1 3 4
# 24 "/usr/include/bits/stdlib-float.h" 3 4
extern __inline __attribute__ ((__gnu_inline__)) double
__attribute__ ((__nothrow__ , __leaf__)) atof (const char *__nptr)
{
  return strtod (__nptr, (char **) ((void *)0));
}
# 1022 "/usr/include/stdlib.h" 2 3 4
# 1033 "/usr/include/stdlib.h" 3 4

# 40 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/usr/include/string.h" 1 3 4
# 26 "/usr/include/string.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/string.h" 2 3 4






# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 34 "/usr/include/string.h" 2 3 4
# 43 "/usr/include/string.h" 3 4
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 4)));




extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 80 "/usr/include/string.h" 3 4
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 107 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 120 "/usr/include/string.h" 3 4
extern void *rawmemchr (const void *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 133 "/usr/include/string.h" 3 4
extern void *memrchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)))
      __attribute__ ((__access__ (__read_only__, 1, 3)));





extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 1, 3)));






extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)))
     __attribute__ ((__access__ (__write_only__, 1, 3)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 246 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 273 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 286 "/usr/include/string.h" 3 4
extern char *strchrnul (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 323 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 350 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 380 "/usr/include/string.h" 3 4
extern char *strcasestr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));







extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)))
    __attribute__ ((__access__ (__read_only__, 1, 2)))
    __attribute__ ((__access__ (__read_only__, 3, 4)));



extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
# 444 "/usr/include/string.h" 3 4
extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 2, 3)));




extern const char *strerrordesc_np (int __err) __attribute__ ((__nothrow__ , __leaf__));

extern const char *strerrorname_np (int __err) __attribute__ ((__nothrow__ , __leaf__));





extern char *strerror_l (int __errnum, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/strings.h" 1 3 4
# 23 "/usr/include/strings.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 24 "/usr/include/strings.h" 2 3 4










extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bcopy (const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 68 "/usr/include/strings.h" 3 4
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 96 "/usr/include/strings.h" 3 4
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));



# 463 "/usr/include/string.h" 2 3 4



extern void explicit_bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));



extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));



extern const char *sigabbrev_np (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern const char *sigdescr_np (int __sig) __attribute__ ((__nothrow__ , __leaf__));



extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int strverscmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strfry (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void *memfrob (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));
# 527 "/usr/include/string.h" 3 4
extern char *basename (const char *__filename) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 539 "/usr/include/string.h" 3 4

# 41 "/home/alexturner/include/python3.15/Python.h" 2


# 1 "/usr/include/ctype.h" 1 3 4
# 28 "/usr/include/ctype.h" 3 4

# 46 "/usr/include/ctype.h" 3 4
enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
# 79 "/usr/include/ctype.h" 3 4
extern const unsigned short int **__ctype_b_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_tolower_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_toupper_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 108 "/usr/include/ctype.h" 3 4
extern int isalnum (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha (int) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit (int) __attribute__ ((__nothrow__ , __leaf__));
extern int islower (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint (int) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit (int) __attribute__ ((__nothrow__ , __leaf__));



extern int tolower (int __c) __attribute__ ((__nothrow__ , __leaf__));


extern int toupper (int __c) __attribute__ ((__nothrow__ , __leaf__));




extern int isblank (int) __attribute__ ((__nothrow__ , __leaf__));




extern int isctype (int __c, int __mask) __attribute__ ((__nothrow__ , __leaf__));






extern int isascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int toascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int _toupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int _tolower (int) __attribute__ ((__nothrow__ , __leaf__));
# 206 "/usr/include/ctype.h" 3 4
extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) tolower (int __c)
{
  return __c >= -128 && __c < 256 ? (*__ctype_tolower_loc ())[__c] : __c;
}

extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) toupper (int __c)
{
  return __c >= -128 && __c < 256 ? (*__ctype_toupper_loc ())[__c] : __c;
}
# 251 "/usr/include/ctype.h" 3 4
extern int isalnum_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int islower_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));

extern int isblank_l (int, locale_t) __attribute__ ((__nothrow__ , __leaf__));



extern int __tolower_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int tolower_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));


extern int __toupper_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int toupper_l (int __c, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
# 327 "/usr/include/ctype.h" 3 4

# 44 "/home/alexturner/include/python3.15/Python.h" 2

# 1 "/usr/include/unistd.h" 1 3 4
# 27 "/usr/include/unistd.h" 3 4

# 202 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/posix_opt.h" 1 3 4
# 203 "/usr/include/unistd.h" 2 3 4



# 1 "/usr/include/bits/environments.h" 1 3 4
# 22 "/usr/include/bits/environments.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 23 "/usr/include/bits/environments.h" 2 3 4
# 207 "/usr/include/unistd.h" 2 3 4
# 226 "/usr/include/unistd.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 227 "/usr/include/unistd.h" 2 3 4
# 274 "/usr/include/unistd.h" 3 4
typedef __socklen_t socklen_t;
# 287 "/usr/include/unistd.h" 3 4
extern int access (const char *__name, int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int euidaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int eaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int execveat (int __fd, const char *__path, char *const __argv[],
                     char *const __envp[], int __flags)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));






extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
# 342 "/usr/include/unistd.h" 3 4
extern __off64_t lseek (int __fd, __off64_t __offset, int __whence) __asm__ ("" "lseek64") __attribute__ ((__nothrow__ , __leaf__))

             ;





extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     __attribute__ ((__nothrow__ , __leaf__));






extern int close (int __fd);




extern void closefrom (int __lowfd) __attribute__ ((__nothrow__ , __leaf__));







extern ssize_t read (int __fd, void *__buf, size_t __nbytes)
    __attribute__ ((__access__ (__write_only__, 2, 3)));





extern ssize_t write (int __fd, const void *__buf, size_t __n)
    __attribute__ ((__access__ (__read_only__, 2, 3)));
# 404 "/usr/include/unistd.h" 3 4
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes, __off64_t __offset) __asm__ ("" "pread64")


    __attribute__ ((__access__ (__write_only__, 2, 3)));
extern ssize_t pwrite (int __fd, const void *__buf, size_t __nbytes, __off64_t __offset) __asm__ ("" "pwrite64")


    __attribute__ ((__access__ (__read_only__, 2, 3)));
# 422 "/usr/include/unistd.h" 3 4
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
   __off64_t __offset)
    __attribute__ ((__access__ (__write_only__, 2, 3)));


extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
    __off64_t __offset)
    __attribute__ ((__access__ (__read_only__, 2, 3)));







extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int pipe2 (int __pipedes[2], int __flags) __attribute__ ((__nothrow__ , __leaf__)) ;
# 452 "/usr/include/unistd.h" 3 4
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__ , __leaf__));
# 464 "/usr/include/unistd.h" 3 4
extern unsigned int sleep (unsigned int __seconds);







extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__ , __leaf__));






extern int usleep (__useconds_t __useconds);
# 489 "/usr/include/unistd.h" 3 4
extern int pause (void);



extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;






extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;



extern int chdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchdir (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
# 531 "/usr/include/unistd.h" 3 4
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__ , __leaf__)) ;





extern char *get_current_dir_name (void) __attribute__ ((__nothrow__ , __leaf__));







extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__))
    __attribute__ ((__access__ (__write_only__, 1)));




extern int dup (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;


extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__ , __leaf__));




extern int dup3 (int __fd, int __fd2, int __flags) __attribute__ ((__nothrow__ , __leaf__));



extern char **__environ;

extern char **environ;





extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




extern int execv (const char *__path, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execle (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execl (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execvp (const char *__file, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int execlp (const char *__file, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int execvpe (const char *__file, char *const __argv[],
      char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int nice (int __inc) __attribute__ ((__nothrow__ , __leaf__)) ;




extern void _exit (int __status) __attribute__ ((__noreturn__));





# 1 "/usr/include/bits/confname.h" 1 3 4
# 24 "/usr/include/bits/confname.h" 3 4
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG,


    _SC_LEVEL1_ICACHE_SIZE,

    _SC_LEVEL1_ICACHE_ASSOC,

    _SC_LEVEL1_ICACHE_LINESIZE,

    _SC_LEVEL1_DCACHE_SIZE,

    _SC_LEVEL1_DCACHE_ASSOC,

    _SC_LEVEL1_DCACHE_LINESIZE,

    _SC_LEVEL2_CACHE_SIZE,

    _SC_LEVEL2_CACHE_ASSOC,

    _SC_LEVEL2_CACHE_LINESIZE,

    _SC_LEVEL3_CACHE_SIZE,

    _SC_LEVEL3_CACHE_ASSOC,

    _SC_LEVEL3_CACHE_LINESIZE,

    _SC_LEVEL4_CACHE_SIZE,

    _SC_LEVEL4_CACHE_ASSOC,

    _SC_LEVEL4_CACHE_LINESIZE,



    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,

    _SC_RAW_SOCKETS,


    _SC_V7_ILP32_OFF32,

    _SC_V7_ILP32_OFFBIG,

    _SC_V7_LP64_OFF64,

    _SC_V7_LPBIG_OFFBIG,


    _SC_SS_REPL_MAX,


    _SC_TRACE_EVENT_NAME_MAX,

    _SC_TRACE_NAME_MAX,

    _SC_TRACE_SYS_MAX,

    _SC_TRACE_USER_EVENT_MAX,


    _SC_XOPEN_STREAMS,


    _SC_THREAD_ROBUST_PRIO_INHERIT,

    _SC_THREAD_ROBUST_PRIO_PROTECT,


    _SC_MINSIGSTKSZ,


    _SC_SIGSTKSZ

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,



    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_V5_WIDTH_RESTRICTED_ENVS,



    _CS_V7_WIDTH_RESTRICTED_ENVS,



    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LIBS,

    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_LP64_OFF64_CFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LIBS,

    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


    _CS_V6_ENV,

    _CS_V7_ENV

  };
# 631 "/usr/include/unistd.h" 2 3 4


extern long int pathconf (const char *__path, int __name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__ , __leaf__));


extern long int sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));



extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__write_only__, 2, 3)));




extern __pid_t getpid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t getppid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t getpgrp (void) __attribute__ ((__nothrow__ , __leaf__));


extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));

extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));






extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__ , __leaf__));
# 682 "/usr/include/unistd.h" 3 4
extern int setpgrp (void) __attribute__ ((__nothrow__ , __leaf__));






extern __pid_t setsid (void) __attribute__ ((__nothrow__ , __leaf__));



extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));



extern __uid_t getuid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __uid_t geteuid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __gid_t getgid (void) __attribute__ ((__nothrow__ , __leaf__));


extern __gid_t getegid (void) __attribute__ ((__nothrow__ , __leaf__));




extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__write_only__, 2, 1)));


extern int group_member (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__));






extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;






extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;





extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     __attribute__ ((__nothrow__ , __leaf__));



extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     __attribute__ ((__nothrow__ , __leaf__));



extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     __attribute__ ((__nothrow__ , __leaf__)) ;



extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     __attribute__ ((__nothrow__ , __leaf__)) ;






extern __pid_t fork (void) __attribute__ ((__nothrow__));







extern __pid_t vfork (void) __attribute__ ((__nothrow__ , __leaf__));






extern __pid_t _Fork (void) __attribute__ ((__nothrow__ , __leaf__));





extern char *ttyname (int __fd) __attribute__ ((__nothrow__ , __leaf__));



extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));



extern int isatty (int __fd) __attribute__ ((__nothrow__ , __leaf__));




extern int ttyslot (void) __attribute__ ((__nothrow__ , __leaf__));




extern int link (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4))) ;




extern int symlink (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));





extern int symlinkat (const char *__from, int __tofd,
        const char *__to) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3))) ;


extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)))
     __attribute__ ((__access__ (__write_only__, 3, 4)));



extern int unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int unlinkat (int __fd, const char *__name, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern int rmdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__ , __leaf__));


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__ , __leaf__));






extern char *getlogin (void);







extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));




extern int setlogin (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







# 1 "/usr/include/bits/getopt_posix.h" 1 3 4
# 27 "/usr/include/bits/getopt_posix.h" 3 4
# 1 "/usr/include/bits/getopt_core.h" 1 3 4
# 28 "/usr/include/bits/getopt_core.h" 3 4








extern char *optarg;
# 50 "/usr/include/bits/getopt_core.h" 3 4
extern int optind;




extern int opterr;



extern int optopt;
# 91 "/usr/include/bits/getopt_core.h" 3 4
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));


# 28 "/usr/include/bits/getopt_posix.h" 2 3 4


# 49 "/usr/include/bits/getopt_posix.h" 3 4

# 904 "/usr/include/unistd.h" 2 3 4







extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));






extern int sethostname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));



extern int sethostid (long int __id) __attribute__ ((__nothrow__ , __leaf__)) ;





extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
     __attribute__ ((__access__ (__write_only__, 1, 2)));
extern int setdomainname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));




extern int vhangup (void) __attribute__ ((__nothrow__ , __leaf__));


extern int revoke (const char *__file) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int acct (const char *__name) __attribute__ ((__nothrow__ , __leaf__));



extern char *getusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void endusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void setusershell (void) __attribute__ ((__nothrow__ , __leaf__));





extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__ , __leaf__)) ;






extern int chroot (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;



extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));







extern int fsync (int __fd);





extern int syncfs (int __fd) __attribute__ ((__nothrow__ , __leaf__));






extern long int gethostid (void);


extern void sync (void) __attribute__ ((__nothrow__ , __leaf__));





extern int getpagesize (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern int getdtablesize (void) __attribute__ ((__nothrow__ , __leaf__));
# 1030 "/usr/include/unistd.h" 3 4
extern int truncate (const char *__file, __off64_t __length) __asm__ ("" "truncate64") __attribute__ ((__nothrow__ , __leaf__))

                  __attribute__ ((__nonnull__ (1))) ;





extern int truncate64 (const char *__file, __off64_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 1052 "/usr/include/unistd.h" 3 4
extern int ftruncate (int __fd, __off64_t __length) __asm__ ("" "ftruncate64") __attribute__ ((__nothrow__ , __leaf__))
                        ;





extern int ftruncate64 (int __fd, __off64_t __length) __attribute__ ((__nothrow__ , __leaf__)) ;
# 1070 "/usr/include/unistd.h" 3 4
extern int brk (void *__addr) __attribute__ ((__nothrow__ , __leaf__)) ;





extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__ , __leaf__));
# 1091 "/usr/include/unistd.h" 3 4
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__ , __leaf__));
# 1117 "/usr/include/unistd.h" 3 4
extern int lockf (int __fd, int __cmd, __off64_t __len) __asm__ ("" "lockf64")
                       ;





extern int lockf64 (int __fd, int __cmd, __off64_t __len) ;
# 1142 "/usr/include/unistd.h" 3 4
ssize_t copy_file_range (int __infd, __off64_t *__pinoff,
    int __outfd, __off64_t *__poutoff,
    size_t __length, unsigned int __flags);





extern int fdatasync (int __fildes);
# 1159 "/usr/include/unistd.h" 3 4
extern char *crypt (const char *__key, const char *__salt)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));







extern void swab (const void *__restrict __from, void *__restrict __to,
    ssize_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)))
    __attribute__ ((__access__ (__read_only__, 1, 3)))
    __attribute__ ((__access__ (__write_only__, 2, 3)));
# 1198 "/usr/include/unistd.h" 3 4
int getentropy (void *__buffer, size_t __length)
    __attribute__ ((__access__ (__write_only__, 1, 2)));
# 1208 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/unistd_ext.h" 1 3 4
# 34 "/usr/include/bits/unistd_ext.h" 3 4
extern __pid_t gettid (void) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/linux/close_range.h" 1 3 4
# 39 "/usr/include/bits/unistd_ext.h" 2 3 4
# 56 "/usr/include/bits/unistd_ext.h" 3 4
extern int close_range (unsigned int __fd, unsigned int __max_fd,
   int __flags) __attribute__ ((__nothrow__ , __leaf__));
# 1209 "/usr/include/unistd.h" 2 3 4


# 46 "/home/alexturner/include/python3.15/Python.h" 2
# 73 "/home/alexturner/include/python3.15/Python.h"
# 1 "/home/alexturner/include/python3.15/pyport.h" 1
# 145 "/home/alexturner/include/python3.15/pyport.h"

# 145 "/home/alexturner/include/python3.15/pyport.h"
typedef uintptr_t Py_uintptr_t;
typedef intptr_t Py_intptr_t;
# 156 "/home/alexturner/include/python3.15/pyport.h"
typedef ssize_t Py_ssize_t;
# 170 "/home/alexturner/include/python3.15/pyport.h"
typedef Py_ssize_t Py_hash_t;


typedef size_t Py_uhash_t;


typedef Py_ssize_t Py_ssize_clean_t;
# 388 "/home/alexturner/include/python3.15/pyport.h"
# 1 "/home/alexturner/include/python3.15/exports.h" 1
# 389 "/home/alexturner/include/python3.15/pyport.h" 2
# 74 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pymacro.h" 1
# 281 "/home/alexturner/include/python3.15/pymacro.h"
__attribute__ ((visibility ("default"))) uint32_t Py_PACK_FULL_VERSION(int x, int y, int z, int level, int serial);
__attribute__ ((visibility ("default"))) uint32_t Py_PACK_VERSION(int x, int y);
# 75 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pymath.h" 1
# 76 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pymem.h" 1
# 48 "/home/alexturner/include/python3.15/pymem.h"
__attribute__ ((visibility ("default"))) void * PyMem_Malloc(size_t size);
__attribute__ ((visibility ("default"))) void * PyMem_Calloc(size_t nelem, size_t elsize);
__attribute__ ((visibility ("default"))) void * PyMem_Realloc(void *ptr, size_t new_size);
__attribute__ ((visibility ("default"))) void PyMem_Free(void *ptr);
# 95 "/home/alexturner/include/python3.15/pymem.h"
__attribute__ ((visibility ("default"))) void * PyMem_RawMalloc(size_t size);
__attribute__ ((visibility ("default"))) void * PyMem_RawCalloc(size_t nelem, size_t elsize);
__attribute__ ((visibility ("default"))) void * PyMem_RawRealloc(void *ptr, size_t new_size);
__attribute__ ((visibility ("default"))) void PyMem_RawFree(void *ptr);




# 1 "/home/alexturner/include/python3.15/cpython/pymem.h" 1




typedef enum {

    PYMEM_DOMAIN_RAW,


    PYMEM_DOMAIN_MEM,


    PYMEM_DOMAIN_OBJ
} PyMemAllocatorDomain;

typedef enum {
    PYMEM_ALLOCATOR_NOT_SET = 0,
    PYMEM_ALLOCATOR_DEFAULT = 1,
    PYMEM_ALLOCATOR_DEBUG = 2,
    PYMEM_ALLOCATOR_MALLOC = 3,
    PYMEM_ALLOCATOR_MALLOC_DEBUG = 4,

    PYMEM_ALLOCATOR_PYMALLOC = 5,
    PYMEM_ALLOCATOR_PYMALLOC_DEBUG = 6,


    PYMEM_ALLOCATOR_MIMALLOC = 7,
    PYMEM_ALLOCATOR_MIMALLOC_DEBUG = 8,

} PyMemAllocatorName;


typedef struct {

    void *ctx;


    void* (*malloc) (void *ctx, size_t size);


    void* (*calloc) (void *ctx, size_t nelem, size_t elsize);


    void* (*realloc) (void *ctx, void *ptr, size_t new_size);


    void (*free) (void *ctx, void *ptr);
} PyMemAllocatorEx;


__attribute__ ((visibility ("default"))) void PyMem_GetAllocator(PyMemAllocatorDomain domain,
                                    PyMemAllocatorEx *allocator);
# 65 "/home/alexturner/include/python3.15/cpython/pymem.h"
__attribute__ ((visibility ("default"))) void PyMem_SetAllocator(PyMemAllocatorDomain domain,
                                    PyMemAllocatorEx *allocator);
# 84 "/home/alexturner/include/python3.15/cpython/pymem.h"
__attribute__ ((visibility ("default"))) void PyMem_SetupDebugHooks(void);
# 104 "/home/alexturner/include/python3.15/pymem.h" 2
# 77 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pytypedefs.h" 1
# 12 "/home/alexturner/include/python3.15/pytypedefs.h"
typedef struct PyModuleDef PyModuleDef;
typedef struct PyModuleDef_Slot PyModuleDef_Slot;
typedef struct PyMethodDef PyMethodDef;
typedef struct PyGetSetDef PyGetSetDef;
typedef struct PyMemberDef PyMemberDef;

typedef struct _object PyObject;
typedef struct _longobject PyLongObject;
typedef struct _typeobject PyTypeObject;
typedef struct PyCodeObject PyCodeObject;
typedef struct _frame PyFrameObject;

typedef struct _ts PyThreadState;
typedef struct _is PyInterpreterState;
# 78 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pybuffer.h" 1
# 20 "/home/alexturner/include/python3.15/pybuffer.h"
typedef struct {
    void *buf;
    PyObject *obj;
    Py_ssize_t len;
    Py_ssize_t itemsize;

    int readonly;
    int ndim;
    char *format;
    Py_ssize_t *shape;
    Py_ssize_t *strides;
    Py_ssize_t *suboffsets;
    void *internal;
} Py_buffer;

typedef int (*getbufferproc)(PyObject *, Py_buffer *, int);
typedef void (*releasebufferproc)(PyObject *, Py_buffer *);


__attribute__ ((visibility ("default"))) int PyObject_CheckBuffer(PyObject *obj);






__attribute__ ((visibility ("default"))) int PyObject_GetBuffer(PyObject *obj, Py_buffer *view,
                                   int flags);



__attribute__ ((visibility ("default"))) void * PyBuffer_GetPointer(const Py_buffer *view, const Py_ssize_t *indices);



__attribute__ ((visibility ("default"))) Py_ssize_t PyBuffer_SizeFromFormat(const char *format);


__attribute__ ((visibility ("default"))) int PyBuffer_ToContiguous(void *buf, const Py_buffer *view,
                                      Py_ssize_t len, char order);

__attribute__ ((visibility ("default"))) int PyBuffer_FromContiguous(const Py_buffer *view, const void *buf,
                                        Py_ssize_t len, char order);
# 77 "/home/alexturner/include/python3.15/pybuffer.h"
__attribute__ ((visibility ("default"))) int PyObject_CopyData(PyObject *dest, PyObject *src);


__attribute__ ((visibility ("default"))) int PyBuffer_IsContiguous(const Py_buffer *view, char fort);





__attribute__ ((visibility ("default"))) void PyBuffer_FillContiguousStrides(int ndims,
                                               Py_ssize_t *shape,
                                               Py_ssize_t *strides,
                                               int itemsize,
                                               char fort);






__attribute__ ((visibility ("default"))) int PyBuffer_FillInfo(Py_buffer *view, PyObject *o, void *buf,
                                  Py_ssize_t len, int readonly,
                                  int flags);


__attribute__ ((visibility ("default"))) void PyBuffer_Release(Py_buffer *view);
# 79 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pystats.h" 1
# 80 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pyatomic.h" 1
# 9 "/home/alexturner/include/python3.15/pyatomic.h"
# 1 "/home/alexturner/include/python3.15/cpython/pyatomic.h" 1
# 93 "/home/alexturner/include/python3.15/cpython/pyatomic.h"
static inline int
_Py_atomic_add_int(int *obj, int value);

static inline int8_t
_Py_atomic_add_int8(int8_t *obj, int8_t value);

static inline int16_t
_Py_atomic_add_int16(int16_t *obj, int16_t value);

static inline int32_t
_Py_atomic_add_int32(int32_t *obj, int32_t value);

static inline int64_t
_Py_atomic_add_int64(int64_t *obj, int64_t value);

static inline intptr_t
_Py_atomic_add_intptr(intptr_t *obj, intptr_t value);

static inline unsigned int
_Py_atomic_add_uint(unsigned int *obj, unsigned int value);

static inline uint8_t
_Py_atomic_add_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_add_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_add_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_add_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_add_uintptr(uintptr_t *obj, uintptr_t value);

static inline Py_ssize_t
_Py_atomic_add_ssize(Py_ssize_t *obj, Py_ssize_t value);
# 143 "/home/alexturner/include/python3.15/cpython/pyatomic.h"
static inline int
_Py_atomic_compare_exchange_int(int *obj, int *expected, int desired);

static inline int
_Py_atomic_compare_exchange_int8(int8_t *obj, int8_t *expected, int8_t desired);

static inline int
_Py_atomic_compare_exchange_int16(int16_t *obj, int16_t *expected, int16_t desired);

static inline int
_Py_atomic_compare_exchange_int32(int32_t *obj, int32_t *expected, int32_t desired);

static inline int
_Py_atomic_compare_exchange_int64(int64_t *obj, int64_t *expected, int64_t desired);

static inline int
_Py_atomic_compare_exchange_intptr(intptr_t *obj, intptr_t *expected, intptr_t desired);

static inline int
_Py_atomic_compare_exchange_uint(unsigned int *obj, unsigned int *expected, unsigned int desired);

static inline int
_Py_atomic_compare_exchange_uint8(uint8_t *obj, uint8_t *expected, uint8_t desired);

static inline int
_Py_atomic_compare_exchange_uint16(uint16_t *obj, uint16_t *expected, uint16_t desired);

static inline int
_Py_atomic_compare_exchange_uint32(uint32_t *obj, uint32_t *expected, uint32_t desired);

static inline int
_Py_atomic_compare_exchange_uint64(uint64_t *obj, uint64_t *expected, uint64_t desired);

static inline int
_Py_atomic_compare_exchange_uintptr(uintptr_t *obj, uintptr_t *expected, uintptr_t desired);

static inline int
_Py_atomic_compare_exchange_ssize(Py_ssize_t *obj, Py_ssize_t *expected, Py_ssize_t desired);



static inline int
_Py_atomic_compare_exchange_ptr(void *obj, void *expected, void *value);





static inline int
_Py_atomic_exchange_int(int *obj, int value);

static inline int8_t
_Py_atomic_exchange_int8(int8_t *obj, int8_t value);

static inline int16_t
_Py_atomic_exchange_int16(int16_t *obj, int16_t value);

static inline int32_t
_Py_atomic_exchange_int32(int32_t *obj, int32_t value);

static inline int64_t
_Py_atomic_exchange_int64(int64_t *obj, int64_t value);

static inline intptr_t
_Py_atomic_exchange_intptr(intptr_t *obj, intptr_t value);

static inline unsigned int
_Py_atomic_exchange_uint(unsigned int *obj, unsigned int value);

static inline uint8_t
_Py_atomic_exchange_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_exchange_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_exchange_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_exchange_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_exchange_uintptr(uintptr_t *obj, uintptr_t value);

static inline Py_ssize_t
_Py_atomic_exchange_ssize(Py_ssize_t *obj, Py_ssize_t value);

static inline void *
_Py_atomic_exchange_ptr(void *obj, void *value);





static inline uint8_t
_Py_atomic_and_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_and_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_and_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_and_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_and_uintptr(uintptr_t *obj, uintptr_t value);





static inline uint8_t
_Py_atomic_or_uint8(uint8_t *obj, uint8_t value);

static inline uint16_t
_Py_atomic_or_uint16(uint16_t *obj, uint16_t value);

static inline uint32_t
_Py_atomic_or_uint32(uint32_t *obj, uint32_t value);

static inline uint64_t
_Py_atomic_or_uint64(uint64_t *obj, uint64_t value);

static inline uintptr_t
_Py_atomic_or_uintptr(uintptr_t *obj, uintptr_t value);





static inline int
_Py_atomic_load_int(const int *obj);

static inline int8_t
_Py_atomic_load_int8(const int8_t *obj);

static inline int16_t
_Py_atomic_load_int16(const int16_t *obj);

static inline int32_t
_Py_atomic_load_int32(const int32_t *obj);

static inline int64_t
_Py_atomic_load_int64(const int64_t *obj);

static inline intptr_t
_Py_atomic_load_intptr(const intptr_t *obj);

static inline uint8_t
_Py_atomic_load_uint8(const uint8_t *obj);

static inline uint16_t
_Py_atomic_load_uint16(const uint16_t *obj);

static inline uint32_t
_Py_atomic_load_uint32(const uint32_t *obj);

static inline uint64_t
_Py_atomic_load_uint64(const uint64_t *obj);

static inline uintptr_t
_Py_atomic_load_uintptr(const uintptr_t *obj);

static inline unsigned int
_Py_atomic_load_uint(const unsigned int *obj);

static inline Py_ssize_t
_Py_atomic_load_ssize(const Py_ssize_t *obj);

static inline void *
_Py_atomic_load_ptr(const void *obj);





static inline int
_Py_atomic_load_int_relaxed(const int *obj);

static inline char
_Py_atomic_load_char_relaxed(const char *obj);

static inline unsigned char
_Py_atomic_load_uchar_relaxed(const unsigned char *obj);

static inline short
_Py_atomic_load_short_relaxed(const short *obj);

static inline unsigned short
_Py_atomic_load_ushort_relaxed(const unsigned short *obj);

static inline long
_Py_atomic_load_long_relaxed(const long *obj);

static inline double
_Py_atomic_load_double_relaxed(const double *obj);

static inline long long
_Py_atomic_load_llong_relaxed(const long long *obj);

static inline int8_t
_Py_atomic_load_int8_relaxed(const int8_t *obj);

static inline int16_t
_Py_atomic_load_int16_relaxed(const int16_t *obj);

static inline int32_t
_Py_atomic_load_int32_relaxed(const int32_t *obj);

static inline int64_t
_Py_atomic_load_int64_relaxed(const int64_t *obj);

static inline intptr_t
_Py_atomic_load_intptr_relaxed(const intptr_t *obj);

static inline uint8_t
_Py_atomic_load_uint8_relaxed(const uint8_t *obj);

static inline uint16_t
_Py_atomic_load_uint16_relaxed(const uint16_t *obj);

static inline uint32_t
_Py_atomic_load_uint32_relaxed(const uint32_t *obj);

static inline uint64_t
_Py_atomic_load_uint64_relaxed(const uint64_t *obj);

static inline uintptr_t
_Py_atomic_load_uintptr_relaxed(const uintptr_t *obj);

static inline unsigned int
_Py_atomic_load_uint_relaxed(const unsigned int *obj);

static inline Py_ssize_t
_Py_atomic_load_ssize_relaxed(const Py_ssize_t *obj);

static inline void *
_Py_atomic_load_ptr_relaxed(const void *obj);

static inline unsigned long long
_Py_atomic_load_ullong_relaxed(const unsigned long long *obj);




static inline void
_Py_atomic_store_int(int *obj, int value);

static inline void
_Py_atomic_store_int8(int8_t *obj, int8_t value);

static inline void
_Py_atomic_store_int16(int16_t *obj, int16_t value);

static inline void
_Py_atomic_store_int32(int32_t *obj, int32_t value);

static inline void
_Py_atomic_store_int64(int64_t *obj, int64_t value);

static inline void
_Py_atomic_store_intptr(intptr_t *obj, intptr_t value);

static inline void
_Py_atomic_store_uint8(uint8_t *obj, uint8_t value);

static inline void
_Py_atomic_store_uint16(uint16_t *obj, uint16_t value);

static inline void
_Py_atomic_store_uint32(uint32_t *obj, uint32_t value);

static inline void
_Py_atomic_store_uint64(uint64_t *obj, uint64_t value);

static inline void
_Py_atomic_store_uintptr(uintptr_t *obj, uintptr_t value);

static inline void
_Py_atomic_store_uint(unsigned int *obj, unsigned int value);

static inline void
_Py_atomic_store_ptr(void *obj, void *value);

static inline void
_Py_atomic_store_ssize(Py_ssize_t* obj, Py_ssize_t value);





static inline void
_Py_atomic_store_int_relaxed(int *obj, int value);

static inline void
_Py_atomic_store_int8_relaxed(int8_t *obj, int8_t value);

static inline void
_Py_atomic_store_int16_relaxed(int16_t *obj, int16_t value);

static inline void
_Py_atomic_store_int32_relaxed(int32_t *obj, int32_t value);

static inline void
_Py_atomic_store_int64_relaxed(int64_t *obj, int64_t value);

static inline void
_Py_atomic_store_intptr_relaxed(intptr_t *obj, intptr_t value);

static inline void
_Py_atomic_store_uint8_relaxed(uint8_t* obj, uint8_t value);

static inline void
_Py_atomic_store_uint16_relaxed(uint16_t *obj, uint16_t value);

static inline void
_Py_atomic_store_uint32_relaxed(uint32_t *obj, uint32_t value);

static inline void
_Py_atomic_store_uint64_relaxed(uint64_t *obj, uint64_t value);

static inline void
_Py_atomic_store_uintptr_relaxed(uintptr_t *obj, uintptr_t value);

static inline void
_Py_atomic_store_uint_relaxed(unsigned int *obj, unsigned int value);

static inline void
_Py_atomic_store_ptr_relaxed(void *obj, void *value);

static inline void
_Py_atomic_store_ssize_relaxed(Py_ssize_t *obj, Py_ssize_t value);

static inline void
_Py_atomic_store_ullong_relaxed(unsigned long long *obj,
                                unsigned long long value);

static inline void
_Py_atomic_store_char_relaxed(char *obj, char value);

static inline void
_Py_atomic_store_uchar_relaxed(unsigned char *obj, unsigned char value);

static inline void
_Py_atomic_store_short_relaxed(short *obj, short value);

static inline void
_Py_atomic_store_ushort_relaxed(unsigned short *obj, unsigned short value);

static inline void
_Py_atomic_store_long_relaxed(long *obj, long value);

static inline void
_Py_atomic_store_float_relaxed(float *obj, float value);

static inline void
_Py_atomic_store_double_relaxed(double *obj, double value);

static inline void
_Py_atomic_store_llong_relaxed(long long *obj, long long value);





static inline void *
_Py_atomic_load_ptr_acquire(const void *obj);

static inline uintptr_t
_Py_atomic_load_uintptr_acquire(const uintptr_t *obj);


static inline void
_Py_atomic_store_ptr_release(void *obj, void *value);

static inline void
_Py_atomic_store_uintptr_release(uintptr_t *obj, uintptr_t value);

static inline void
_Py_atomic_store_ssize_release(Py_ssize_t *obj, Py_ssize_t value);

static inline void
_Py_atomic_store_int_release(int *obj, int value);

static inline int
_Py_atomic_load_int_acquire(const int *obj);

static inline void
_Py_atomic_store_uint32_release(uint32_t *obj, uint32_t value);

static inline void
_Py_atomic_store_uint64_release(uint64_t *obj, uint64_t value);

static inline uint64_t
_Py_atomic_load_uint64_acquire(const uint64_t *obj);

static inline uint32_t
_Py_atomic_load_uint32_acquire(const uint32_t *obj);

static inline Py_ssize_t
_Py_atomic_load_ssize_acquire(const Py_ssize_t *obj);
# 556 "/home/alexturner/include/python3.15/cpython/pyatomic.h"
static inline void _Py_atomic_fence_seq_cst(void);


static inline void _Py_atomic_fence_acquire(void);


static inline void _Py_atomic_fence_release(void);
# 577 "/home/alexturner/include/python3.15/cpython/pyatomic.h"
# 1 "/home/alexturner/include/python3.15/cpython/pyatomic_gcc.h" 1
# 13 "/home/alexturner/include/python3.15/cpython/pyatomic_gcc.h"
static inline int
_Py_atomic_add_int(int *obj, int value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int8_t
_Py_atomic_add_int8(int8_t *obj, int8_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int16_t
_Py_atomic_add_int16(int16_t *obj, int16_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int32_t
_Py_atomic_add_int32(int32_t *obj, int32_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline int64_t
_Py_atomic_add_int64(int64_t *obj, int64_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline intptr_t
_Py_atomic_add_intptr(intptr_t *obj, intptr_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline unsigned int
_Py_atomic_add_uint(unsigned int *obj, unsigned int value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint8_t
_Py_atomic_add_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint16_t
_Py_atomic_add_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint32_t
_Py_atomic_add_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uint64_t
_Py_atomic_add_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline uintptr_t
_Py_atomic_add_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_fetch_add(obj, value, 5); }

static inline Py_ssize_t
_Py_atomic_add_ssize(Py_ssize_t *obj, Py_ssize_t value)
{ return __atomic_fetch_add(obj, value, 5); }




static inline int
_Py_atomic_compare_exchange_int(int *obj, int *expected, int desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int8(int8_t *obj, int8_t *expected, int8_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int16(int16_t *obj, int16_t *expected, int16_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int32(int32_t *obj, int32_t *expected, int32_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_int64(int64_t *obj, int64_t *expected, int64_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_intptr(intptr_t *obj, intptr_t *expected, intptr_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint(unsigned int *obj, unsigned int *expected, unsigned int desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint8(uint8_t *obj, uint8_t *expected, uint8_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint16(uint16_t *obj, uint16_t *expected, uint16_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint32(uint32_t *obj, uint32_t *expected, uint32_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uint64(uint64_t *obj, uint64_t *expected, uint64_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_uintptr(uintptr_t *obj, uintptr_t *expected, uintptr_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_ssize(Py_ssize_t *obj, Py_ssize_t *expected, Py_ssize_t desired)
{ return __atomic_compare_exchange_n(obj, expected, desired, 0,
                                     5, 5); }

static inline int
_Py_atomic_compare_exchange_ptr(void *obj, void *expected, void *desired)
{ return __atomic_compare_exchange_n((void **)obj, (void **)expected, desired, 0,
                                     5, 5); }




static inline int
_Py_atomic_exchange_int(int *obj, int value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int8_t
_Py_atomic_exchange_int8(int8_t *obj, int8_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int16_t
_Py_atomic_exchange_int16(int16_t *obj, int16_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int32_t
_Py_atomic_exchange_int32(int32_t *obj, int32_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline int64_t
_Py_atomic_exchange_int64(int64_t *obj, int64_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline intptr_t
_Py_atomic_exchange_intptr(intptr_t *obj, intptr_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline unsigned int
_Py_atomic_exchange_uint(unsigned int *obj, unsigned int value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint8_t
_Py_atomic_exchange_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint16_t
_Py_atomic_exchange_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint32_t
_Py_atomic_exchange_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uint64_t
_Py_atomic_exchange_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline uintptr_t
_Py_atomic_exchange_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline Py_ssize_t
_Py_atomic_exchange_ssize(Py_ssize_t *obj, Py_ssize_t value)
{ return __atomic_exchange_n(obj, value, 5); }

static inline void *
_Py_atomic_exchange_ptr(void *obj, void *value)
{ return __atomic_exchange_n((void **)obj, value, 5); }




static inline uint8_t
_Py_atomic_and_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uint16_t
_Py_atomic_and_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uint32_t
_Py_atomic_and_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uint64_t
_Py_atomic_and_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_fetch_and(obj, value, 5); }

static inline uintptr_t
_Py_atomic_and_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_fetch_and(obj, value, 5); }




static inline uint8_t
_Py_atomic_or_uint8(uint8_t *obj, uint8_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uint16_t
_Py_atomic_or_uint16(uint16_t *obj, uint16_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uint32_t
_Py_atomic_or_uint32(uint32_t *obj, uint32_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uint64_t
_Py_atomic_or_uint64(uint64_t *obj, uint64_t value)
{ return __atomic_fetch_or(obj, value, 5); }

static inline uintptr_t
_Py_atomic_or_uintptr(uintptr_t *obj, uintptr_t value)
{ return __atomic_fetch_or(obj, value, 5); }




static inline int
_Py_atomic_load_int(const int *obj)
{ return __atomic_load_n(obj, 5); }

static inline int8_t
_Py_atomic_load_int8(const int8_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline int16_t
_Py_atomic_load_int16(const int16_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline int32_t
_Py_atomic_load_int32(const int32_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline int64_t
_Py_atomic_load_int64(const int64_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline intptr_t
_Py_atomic_load_intptr(const intptr_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint8_t
_Py_atomic_load_uint8(const uint8_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint16_t
_Py_atomic_load_uint16(const uint16_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint32_t
_Py_atomic_load_uint32(const uint32_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uint64_t
_Py_atomic_load_uint64(const uint64_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline uintptr_t
_Py_atomic_load_uintptr(const uintptr_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline unsigned int
_Py_atomic_load_uint(const unsigned int *obj)
{ return __atomic_load_n(obj, 5); }

static inline Py_ssize_t
_Py_atomic_load_ssize(const Py_ssize_t *obj)
{ return __atomic_load_n(obj, 5); }

static inline void *
_Py_atomic_load_ptr(const void *obj)
{ return (void *)__atomic_load_n((void * const *)obj, 5); }




static inline int
_Py_atomic_load_int_relaxed(const int *obj)
{ return __atomic_load_n(obj, 0); }

static inline char
_Py_atomic_load_char_relaxed(const char *obj)
{ return __atomic_load_n(obj, 0); }

static inline unsigned char
_Py_atomic_load_uchar_relaxed(const unsigned char *obj)
{ return __atomic_load_n(obj, 0); }

static inline short
_Py_atomic_load_short_relaxed(const short *obj)
{ return __atomic_load_n(obj, 0); }

static inline unsigned short
_Py_atomic_load_ushort_relaxed(const unsigned short *obj)
{ return __atomic_load_n(obj, 0); }

static inline long
_Py_atomic_load_long_relaxed(const long *obj)
{ return __atomic_load_n(obj, 0); }

static inline float
_Py_atomic_load_float_relaxed(const float *obj)
{ float ret; __atomic_load(obj, &ret, 0); return ret; }

static inline double
_Py_atomic_load_double_relaxed(const double *obj)
{ double ret; __atomic_load(obj, &ret, 0); return ret; }

static inline int8_t
_Py_atomic_load_int8_relaxed(const int8_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline int16_t
_Py_atomic_load_int16_relaxed(const int16_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline int32_t
_Py_atomic_load_int32_relaxed(const int32_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline int64_t
_Py_atomic_load_int64_relaxed(const int64_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline intptr_t
_Py_atomic_load_intptr_relaxed(const intptr_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint8_t
_Py_atomic_load_uint8_relaxed(const uint8_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint16_t
_Py_atomic_load_uint16_relaxed(const uint16_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint32_t
_Py_atomic_load_uint32_relaxed(const uint32_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uint64_t
_Py_atomic_load_uint64_relaxed(const uint64_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline uintptr_t
_Py_atomic_load_uintptr_relaxed(const uintptr_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline unsigned int
_Py_atomic_load_uint_relaxed(const unsigned int *obj)
{ return __atomic_load_n(obj, 0); }

static inline Py_ssize_t
_Py_atomic_load_ssize_relaxed(const Py_ssize_t *obj)
{ return __atomic_load_n(obj, 0); }

static inline void *
_Py_atomic_load_ptr_relaxed(const void *obj)
{ return (void *)__atomic_load_n((void * const *)obj, 0); }

static inline unsigned long long
_Py_atomic_load_ullong_relaxed(const unsigned long long *obj)
{ return __atomic_load_n(obj, 0); }

static inline long long
_Py_atomic_load_llong_relaxed(const long long *obj)
{ return __atomic_load_n(obj, 0); }




static inline void
_Py_atomic_store_int(int *obj, int value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int8(int8_t *obj, int8_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int16(int16_t *obj, int16_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int32(int32_t *obj, int32_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_int64(int64_t *obj, int64_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_intptr(intptr_t *obj, intptr_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint8(uint8_t *obj, uint8_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint16(uint16_t *obj, uint16_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint32(uint32_t *obj, uint32_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint64(uint64_t *obj, uint64_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uintptr(uintptr_t *obj, uintptr_t value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_uint(unsigned int *obj, unsigned int value)
{ __atomic_store_n(obj, value, 5); }

static inline void
_Py_atomic_store_ptr(void *obj, void *value)
{ __atomic_store_n((void **)obj, value, 5); }

static inline void
_Py_atomic_store_ssize(Py_ssize_t *obj, Py_ssize_t value)
{ __atomic_store_n(obj, value, 5); }




static inline void
_Py_atomic_store_int_relaxed(int *obj, int value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int8_relaxed(int8_t *obj, int8_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int16_relaxed(int16_t *obj, int16_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int32_relaxed(int32_t *obj, int32_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_int64_relaxed(int64_t *obj, int64_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_intptr_relaxed(intptr_t *obj, intptr_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint8_relaxed(uint8_t *obj, uint8_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint16_relaxed(uint16_t *obj, uint16_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint32_relaxed(uint32_t *obj, uint32_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint64_relaxed(uint64_t *obj, uint64_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uintptr_relaxed(uintptr_t *obj, uintptr_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uint_relaxed(unsigned int *obj, unsigned int value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_ptr_relaxed(void *obj, void *value)
{ __atomic_store_n((void **)obj, value, 0); }

static inline void
_Py_atomic_store_ssize_relaxed(Py_ssize_t *obj, Py_ssize_t value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_ullong_relaxed(unsigned long long *obj,
                                unsigned long long value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_char_relaxed(char *obj, char value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_uchar_relaxed(unsigned char *obj, unsigned char value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_short_relaxed(short *obj, short value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_ushort_relaxed(unsigned short *obj, unsigned short value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_long_relaxed(long *obj, long value)
{ __atomic_store_n(obj, value, 0); }

static inline void
_Py_atomic_store_float_relaxed(float *obj, float value)
{ __atomic_store(obj, &value, 0); }

static inline void
_Py_atomic_store_double_relaxed(double *obj, double value)
{ __atomic_store(obj, &value, 0); }

static inline void
_Py_atomic_store_llong_relaxed(long long *obj, long long value)
{ __atomic_store_n(obj, value, 0); }




static inline void *
_Py_atomic_load_ptr_acquire(const void *obj)
{ return (void *)__atomic_load_n((void * const *)obj, 2); }

static inline uintptr_t
_Py_atomic_load_uintptr_acquire(const uintptr_t *obj)
{ return (uintptr_t)__atomic_load_n(obj, 2); }

static inline void
_Py_atomic_store_ptr_release(void *obj, void *value)
{ __atomic_store_n((void **)obj, value, 3); }

static inline void
_Py_atomic_store_uintptr_release(uintptr_t *obj, uintptr_t value)
{ __atomic_store_n(obj, value, 3); }

static inline void
_Py_atomic_store_int_release(int *obj, int value)
{ __atomic_store_n(obj, value, 3); }

static inline void
_Py_atomic_store_ssize_release(Py_ssize_t *obj, Py_ssize_t value)
{ __atomic_store_n(obj, value, 3); }

static inline int
_Py_atomic_load_int_acquire(const int *obj)
{ return __atomic_load_n(obj, 2); }

static inline void
_Py_atomic_store_uint32_release(uint32_t *obj, uint32_t value)
{ __atomic_store_n(obj, value, 3); }

static inline void
_Py_atomic_store_uint64_release(uint64_t *obj, uint64_t value)
{ __atomic_store_n(obj, value, 3); }

static inline uint64_t
_Py_atomic_load_uint64_acquire(const uint64_t *obj)
{ return __atomic_load_n(obj, 2); }

static inline uint32_t
_Py_atomic_load_uint32_acquire(const uint32_t *obj)
{ return __atomic_load_n(obj, 2); }

static inline Py_ssize_t
_Py_atomic_load_ssize_acquire(const Py_ssize_t *obj)
{ return __atomic_load_n(obj, 2); }



static inline void
_Py_atomic_fence_seq_cst(void)
{ __atomic_thread_fence(5); }

 static inline void
_Py_atomic_fence_acquire(void)
{ __atomic_thread_fence(2); }

 static inline void
_Py_atomic_fence_release(void)
{ __atomic_thread_fence(3); }
# 578 "/home/alexturner/include/python3.15/cpython/pyatomic.h" 2
# 10 "/home/alexturner/include/python3.15/pyatomic.h" 2
# 81 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/pylock.h" 1
# 33 "/home/alexturner/include/python3.15/cpython/pylock.h"
typedef struct PyMutex {
    uint8_t _bits;
} PyMutex;


__attribute__ ((visibility ("default"))) void PyMutex_Lock(PyMutex *m);


__attribute__ ((visibility ("default"))) void PyMutex_Unlock(PyMutex *m);


__attribute__ ((visibility ("default"))) int PyMutex_IsLocked(PyMutex *m);






static inline void
_PyMutex_Lock(PyMutex *m)
{
    uint8_t expected = 0;
    if (!_Py_atomic_compare_exchange_uint8(&m->_bits, &expected, 1)) {
        PyMutex_Lock(m);
    }
}



static inline void
_PyMutex_Unlock(PyMutex *m)
{
    uint8_t expected = 1;
    if (!_Py_atomic_compare_exchange_uint8(&m->_bits, &expected, 0)) {
        PyMutex_Unlock(m);
    }
}



static inline int
_PyMutex_IsLocked(PyMutex *m)
{
    return (_Py_atomic_load_uint8(&m->_bits) & 1) != 0;
}
# 82 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/critical_section.h" 1
# 9 "/home/alexturner/include/python3.15/critical_section.h"
# 1 "/home/alexturner/include/python3.15/cpython/critical_section.h" 1
# 70 "/home/alexturner/include/python3.15/cpython/critical_section.h"
typedef struct PyCriticalSection PyCriticalSection;
typedef struct PyCriticalSection2 PyCriticalSection2;

__attribute__ ((visibility ("default"))) void
PyCriticalSection_Begin(PyCriticalSection *c, PyObject *op);

__attribute__ ((visibility ("default"))) void
PyCriticalSection_BeginMutex(PyCriticalSection *c, PyMutex *m);

__attribute__ ((visibility ("default"))) void
PyCriticalSection_End(PyCriticalSection *c);

__attribute__ ((visibility ("default"))) void
PyCriticalSection2_Begin(PyCriticalSection2 *c, PyObject *a, PyObject *b);

__attribute__ ((visibility ("default"))) void
PyCriticalSection2_BeginMutex(PyCriticalSection2 *c, PyMutex *m1, PyMutex *m2);

__attribute__ ((visibility ("default"))) void
PyCriticalSection2_End(PyCriticalSection2 *c);
# 10 "/home/alexturner/include/python3.15/critical_section.h" 2
# 83 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/object.h" 1
# 127 "/home/alexturner/include/python3.15/object.h"
struct _object {
    union {

        int64_t ob_refcnt_full;
        struct {





            uint32_t ob_refcnt;
            uint16_t ob_overflow;
            uint16_t ob_flags;

        };



        _Alignas(4) _Alignas(char) char _aligner;
    };

    PyTypeObject *ob_type;
};
# 174 "/home/alexturner/include/python3.15/object.h"
struct PyVarObject {
    PyObject ob_base;
    Py_ssize_t ob_size;
};

typedef struct PyVarObject PyVarObject;






__attribute__ ((visibility ("default"))) int Py_Is(PyObject *x, PyObject *y);
# 268 "/home/alexturner/include/python3.15/object.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyLong_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyBool_Type;



__attribute__ ((visibility ("default"))) PyTypeObject* Py_TYPE(PyObject *ob);


__attribute__ ((visibility ("default"))) Py_ssize_t Py_SIZE(PyObject *ob);
__attribute__ ((visibility ("default"))) int Py_IS_TYPE(PyObject *ob, PyTypeObject *type);
__attribute__ ((visibility ("default"))) void Py_SET_SIZE(PyVarObject *ob, Py_ssize_t size);




static inline void
Py_SET_TYPE(PyObject *ob, PyTypeObject *type)
{
    ob->ob_type = type;
}
# 310 "/home/alexturner/include/python3.15/object.h"
static inline
PyTypeObject* _Py_TYPE_impl(PyObject *ob)
{
    return ob->ob_type;
}


static inline Py_ssize_t
_Py_SIZE_impl(PyObject *ob)
{
    
# 320 "/home/alexturner/include/python3.15/object.h" 3 4
   ((void) (0))
# 320 "/home/alexturner/include/python3.15/object.h"
                                      ;
    
# 321 "/home/alexturner/include/python3.15/object.h" 3 4
   ((void) (0))
# 321 "/home/alexturner/include/python3.15/object.h"
                                      ;
    return ((PyVarObject*)((ob)))->ob_size;
}

static inline int
_Py_IS_TYPE_impl(PyObject *ob, PyTypeObject *type)
{
    return _Py_TYPE_impl(((PyObject*)((ob)))) == type;
}

static inline void
_Py_SET_SIZE_impl(PyVarObject *ob, Py_ssize_t size)
{
    
# 334 "/home/alexturner/include/python3.15/object.h" 3 4
   ((void) (0))
# 334 "/home/alexturner/include/python3.15/object.h"
                                                      ;
    
# 335 "/home/alexturner/include/python3.15/object.h" 3 4
   ((void) (0))
# 335 "/home/alexturner/include/python3.15/object.h"
                                                      ;



    ob->ob_size = size;

}
# 361 "/home/alexturner/include/python3.15/object.h"
typedef PyObject * (*unaryfunc)(PyObject *);
typedef PyObject * (*binaryfunc)(PyObject *, PyObject *);
typedef PyObject * (*ternaryfunc)(PyObject *, PyObject *, PyObject *);
typedef int (*inquiry)(PyObject *);
typedef Py_ssize_t (*lenfunc)(PyObject *);
typedef PyObject *(*ssizeargfunc)(PyObject *, Py_ssize_t);
typedef PyObject *(*ssizessizeargfunc)(PyObject *, Py_ssize_t, Py_ssize_t);
typedef int(*ssizeobjargproc)(PyObject *, Py_ssize_t, PyObject *);
typedef int(*ssizessizeobjargproc)(PyObject *, Py_ssize_t, Py_ssize_t, PyObject *);
typedef int(*objobjargproc)(PyObject *, PyObject *, PyObject *);

typedef int (*objobjproc)(PyObject *, PyObject *);
typedef int (*visitproc)(PyObject *, void *);
typedef int (*traverseproc)(PyObject *, visitproc, void *);


typedef void (*freefunc)(void *);
typedef void (*destructor)(PyObject *);
typedef PyObject *(*getattrfunc)(PyObject *, char *);
typedef PyObject *(*getattrofunc)(PyObject *, PyObject *);
typedef int (*setattrfunc)(PyObject *, char *, PyObject *);
typedef int (*setattrofunc)(PyObject *, PyObject *, PyObject *);
typedef PyObject *(*reprfunc)(PyObject *);
typedef Py_hash_t (*hashfunc)(PyObject *);
typedef PyObject *(*richcmpfunc) (PyObject *, PyObject *, int);
typedef PyObject *(*getiterfunc) (PyObject *);
typedef PyObject *(*iternextfunc) (PyObject *);
typedef PyObject *(*descrgetfunc) (PyObject *, PyObject *, PyObject *);
typedef int (*descrsetfunc) (PyObject *, PyObject *, PyObject *);
typedef int (*initproc)(PyObject *, PyObject *, PyObject *);
typedef PyObject *(*newfunc)(PyTypeObject *, PyObject *, PyObject *);
typedef PyObject *(*allocfunc)(PyTypeObject *, Py_ssize_t);


typedef PyObject *(*vectorcallfunc)(PyObject *callable, PyObject *const *args,
                                    size_t nargsf, PyObject *kwnames);


typedef struct{
    int slot;
    void *pfunc;
} PyType_Slot;

typedef struct{
    const char* name;
    int basicsize;
    int itemsize;
    unsigned int flags;
    PyType_Slot *slots;
} PyType_Spec;

__attribute__ ((visibility ("default"))) PyObject* PyType_FromSpec(PyType_Spec*);

__attribute__ ((visibility ("default"))) PyObject* PyType_FromSpecWithBases(PyType_Spec*, PyObject*);


__attribute__ ((visibility ("default"))) void* PyType_GetSlot(PyTypeObject*, int);


__attribute__ ((visibility ("default"))) PyObject* PyType_FromModuleAndSpec(PyObject *, PyType_Spec *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyType_GetModule(PyTypeObject *);
__attribute__ ((visibility ("default"))) void * PyType_GetModuleState(PyTypeObject *);


__attribute__ ((visibility ("default"))) PyObject * PyType_GetName(PyTypeObject *);
__attribute__ ((visibility ("default"))) PyObject * PyType_GetQualName(PyTypeObject *);


__attribute__ ((visibility ("default"))) PyObject * PyType_GetFullyQualifiedName(PyTypeObject *type);
__attribute__ ((visibility ("default"))) PyObject * PyType_GetModuleName(PyTypeObject *type);


__attribute__ ((visibility ("default"))) PyObject * PyType_FromMetaclass(PyTypeObject*, PyObject*, PyType_Spec*, PyObject*);
__attribute__ ((visibility ("default"))) void * PyObject_GetTypeData(PyObject *obj, PyTypeObject *cls);
__attribute__ ((visibility ("default"))) Py_ssize_t PyType_GetTypeDataSize(PyTypeObject *cls);


__attribute__ ((visibility ("default"))) int PyType_GetBaseByToken(PyTypeObject *, void *, PyTypeObject **);




__attribute__ ((visibility ("default"))) int PyType_IsSubtype(PyTypeObject *, PyTypeObject *);

static inline int PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) {
    return _Py_IS_TYPE_impl(((PyObject*)((ob))), (type)) || PyType_IsSubtype(_Py_TYPE_impl(((PyObject*)((ob)))), type);
}




extern __attribute__ ((visibility ("default"))) PyTypeObject PyType_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyBaseObject_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PySuper_Type;

__attribute__ ((visibility ("default"))) unsigned long PyType_GetFlags(PyTypeObject*);

__attribute__ ((visibility ("default"))) int PyType_Ready(PyTypeObject *);
__attribute__ ((visibility ("default"))) PyObject * PyType_GenericAlloc(PyTypeObject *, Py_ssize_t);
__attribute__ ((visibility ("default"))) PyObject * PyType_GenericNew(PyTypeObject *,
                                               PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) unsigned int PyType_ClearCache(void);
__attribute__ ((visibility ("default"))) void PyType_Modified(PyTypeObject *);


__attribute__ ((visibility ("default"))) PyObject * PyObject_Repr(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyObject_Str(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyObject_ASCII(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyObject_Bytes(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyObject_RichCompare(PyObject *, PyObject *, int);
__attribute__ ((visibility ("default"))) int PyObject_RichCompareBool(PyObject *, PyObject *, int);
__attribute__ ((visibility ("default"))) PyObject * PyObject_GetAttrString(PyObject *, const char *);
__attribute__ ((visibility ("default"))) int PyObject_SetAttrString(PyObject *, const char *, PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_DelAttrString(PyObject *v, const char *name);
__attribute__ ((visibility ("default"))) int PyObject_HasAttrString(PyObject *, const char *);
__attribute__ ((visibility ("default"))) PyObject * PyObject_GetAttr(PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) int PyObject_GetOptionalAttr(PyObject *, PyObject *, PyObject **);
__attribute__ ((visibility ("default"))) int PyObject_GetOptionalAttrString(PyObject *, const char *, PyObject **);

__attribute__ ((visibility ("default"))) int PyObject_SetAttr(PyObject *, PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_DelAttr(PyObject *v, PyObject *name);
__attribute__ ((visibility ("default"))) int PyObject_HasAttr(PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) int PyObject_HasAttrWithError(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_HasAttrStringWithError(PyObject *, const char *);

__attribute__ ((visibility ("default"))) PyObject * PyObject_SelfIter(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyObject_GenericGetAttr(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_GenericSetAttr(PyObject *, PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) int PyObject_GenericSetDict(PyObject *, PyObject *, void *);

__attribute__ ((visibility ("default"))) Py_hash_t PyObject_Hash(PyObject *);
__attribute__ ((visibility ("default"))) Py_hash_t PyObject_HashNotImplemented(PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_IsTrue(PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_Not(PyObject *);
__attribute__ ((visibility ("default"))) int PyCallable_Check(PyObject *);
__attribute__ ((visibility ("default"))) void PyObject_ClearWeakRefs(PyObject *);






__attribute__ ((visibility ("default"))) PyObject * PyObject_Dir(PyObject *);


__attribute__ ((visibility ("default"))) int Py_ReprEnter(PyObject *);
__attribute__ ((visibility ("default"))) void Py_ReprLeave(PyObject *);
# 671 "/home/alexturner/include/python3.15/object.h"
__attribute__ ((visibility ("default"))) PyObject* Py_GetConstant(unsigned int constant_id);
__attribute__ ((visibility ("default"))) PyObject* Py_GetConstantBorrowed(unsigned int constant_id);







extern __attribute__ ((visibility ("default"))) PyObject _Py_NoneStruct;
# 689 "/home/alexturner/include/python3.15/object.h"
__attribute__ ((visibility ("default"))) int Py_IsNone(PyObject *x);
# 704 "/home/alexturner/include/python3.15/object.h"
extern __attribute__ ((visibility ("default"))) PyObject _Py_NotImplementedStruct;
# 730 "/home/alexturner/include/python3.15/object.h"
typedef enum {
    PYGEN_RETURN = 0,
    PYGEN_ERROR = -1,
    PYGEN_NEXT = 1
} PySendResult;
# 811 "/home/alexturner/include/python3.15/object.h"
# 1 "/home/alexturner/include/python3.15/cpython/object.h" 1




__attribute__ ((visibility ("default"))) void _Py_NewReference(PyObject *op);
__attribute__ ((visibility ("default"))) void _Py_NewReferenceNoTotal(PyObject *op);
__attribute__ ((visibility ("default"))) void _Py_ResurrectReference(PyObject *op);
__attribute__ ((visibility ("default"))) void _Py_ForgetReference(PyObject *op);
# 39 "/home/alexturner/include/python3.15/cpython/object.h"
typedef struct _Py_Identifier {
    const char* string;


    Py_ssize_t index;

    struct {
        uint8_t v;
    } mutex;
} _Py_Identifier;
# 61 "/home/alexturner/include/python3.15/cpython/object.h"
typedef struct {




    binaryfunc nb_add;
    binaryfunc nb_subtract;
    binaryfunc nb_multiply;
    binaryfunc nb_remainder;
    binaryfunc nb_divmod;
    ternaryfunc nb_power;
    unaryfunc nb_negative;
    unaryfunc nb_positive;
    unaryfunc nb_absolute;
    inquiry nb_bool;
    unaryfunc nb_invert;
    binaryfunc nb_lshift;
    binaryfunc nb_rshift;
    binaryfunc nb_and;
    binaryfunc nb_xor;
    binaryfunc nb_or;
    unaryfunc nb_int;
    void *nb_reserved;
    unaryfunc nb_float;

    binaryfunc nb_inplace_add;
    binaryfunc nb_inplace_subtract;
    binaryfunc nb_inplace_multiply;
    binaryfunc nb_inplace_remainder;
    ternaryfunc nb_inplace_power;
    binaryfunc nb_inplace_lshift;
    binaryfunc nb_inplace_rshift;
    binaryfunc nb_inplace_and;
    binaryfunc nb_inplace_xor;
    binaryfunc nb_inplace_or;

    binaryfunc nb_floor_divide;
    binaryfunc nb_true_divide;
    binaryfunc nb_inplace_floor_divide;
    binaryfunc nb_inplace_true_divide;

    unaryfunc nb_index;

    binaryfunc nb_matrix_multiply;
    binaryfunc nb_inplace_matrix_multiply;
} PyNumberMethods;

typedef struct {
    lenfunc sq_length;
    binaryfunc sq_concat;
    ssizeargfunc sq_repeat;
    ssizeargfunc sq_item;
    void *was_sq_slice;
    ssizeobjargproc sq_ass_item;
    void *was_sq_ass_slice;
    objobjproc sq_contains;

    binaryfunc sq_inplace_concat;
    ssizeargfunc sq_inplace_repeat;
} PySequenceMethods;

typedef struct {
    lenfunc mp_length;
    binaryfunc mp_subscript;
    objobjargproc mp_ass_subscript;
} PyMappingMethods;

typedef PySendResult (*sendfunc)(PyObject *iter, PyObject *value, PyObject **result);

typedef struct {
    unaryfunc am_await;
    unaryfunc am_aiter;
    unaryfunc am_anext;
    sendfunc am_send;
} PyAsyncMethods;

typedef struct {
     getbufferproc bf_getbuffer;
     releasebufferproc bf_releasebuffer;
} PyBufferProcs;



typedef Py_ssize_t printfunc;



struct _typeobject {
    PyVarObject ob_base;
    const char *tp_name;
    Py_ssize_t tp_basicsize, tp_itemsize;



    destructor tp_dealloc;
    Py_ssize_t tp_vectorcall_offset;
    getattrfunc tp_getattr;
    setattrfunc tp_setattr;
    PyAsyncMethods *tp_as_async;

    reprfunc tp_repr;



    PyNumberMethods *tp_as_number;
    PySequenceMethods *tp_as_sequence;
    PyMappingMethods *tp_as_mapping;



    hashfunc tp_hash;
    ternaryfunc tp_call;
    reprfunc tp_str;
    getattrofunc tp_getattro;
    setattrofunc tp_setattro;


    PyBufferProcs *tp_as_buffer;


    unsigned long tp_flags;

    const char *tp_doc;



    traverseproc tp_traverse;


    inquiry tp_clear;



    richcmpfunc tp_richcompare;


    Py_ssize_t tp_weaklistoffset;


    getiterfunc tp_iter;
    iternextfunc tp_iternext;


    PyMethodDef *tp_methods;
    PyMemberDef *tp_members;
    PyGetSetDef *tp_getset;

    PyTypeObject *tp_base;
    PyObject *tp_dict;
    descrgetfunc tp_descr_get;
    descrsetfunc tp_descr_set;
    Py_ssize_t tp_dictoffset;
    initproc tp_init;
    allocfunc tp_alloc;
    newfunc tp_new;
    freefunc tp_free;
    inquiry tp_is_gc;
    PyObject *tp_bases;
    PyObject *tp_mro;
    PyObject *tp_cache;
    void *tp_subclasses;
    PyObject *tp_weaklist;
    destructor tp_del;




    unsigned int tp_version_tag;

    destructor tp_finalize;
    vectorcallfunc tp_vectorcall;


    unsigned char tp_watched;






    uint16_t tp_versions_used;
};






struct _specialization_cache {
# 260 "/home/alexturner/include/python3.15/cpython/object.h"
    PyObject *getitem;
    uint32_t getitem_version;
    PyObject *init;
};


typedef struct _heaptypeobject {


    PyTypeObject ht_type;
    PyAsyncMethods as_async;
    PyNumberMethods as_number;
    PyMappingMethods as_mapping;
    PySequenceMethods as_sequence;




    PyBufferProcs as_buffer;
    PyObject *ht_name, *ht_slots, *ht_qualname;
    struct _dictkeysobject *ht_cached_keys;
    PyObject *ht_module;
    char *_ht_tpname;
    void *ht_token;
    struct _specialization_cache _spec_cache;




} PyHeapTypeObject;

__attribute__ ((visibility ("default"))) const char * _PyType_Name(PyTypeObject *);
__attribute__ ((visibility ("default"))) PyObject * _PyType_Lookup(PyTypeObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * _PyType_LookupRef(PyTypeObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyType_GetDict(PyTypeObject *);

__attribute__ ((visibility ("default"))) int PyObject_Print(PyObject *, FILE *, int);
__attribute__ ((visibility ("default"))) void _Py_BreakPoint(void);
__attribute__ ((visibility ("default"))) void PyUnstable_Object_Dump(PyObject *);




__attribute__ ((visibility ("default"))) PyObject* _PyObject_GetAttrId(PyObject *, _Py_Identifier *);

__attribute__ ((visibility ("default"))) PyObject ** _PyObject_GetDictPtr(PyObject *);
__attribute__ ((visibility ("default"))) void PyObject_CallFinalizer(PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_CallFinalizerFromDealloc(PyObject *);

__attribute__ ((visibility ("default"))) void PyUnstable_Object_ClearWeakRefsNoCallbacks(PyObject *);



__attribute__ ((visibility ("default"))) PyObject *
_PyObject_GenericGetAttrWithDict(PyObject *, PyObject *, PyObject *, int);
__attribute__ ((visibility ("default"))) int
_PyObject_GenericSetAttrWithDict(PyObject *, PyObject *,
                                 PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) PyObject * _PyObject_FunctionStr(PyObject *);
# 427 "/home/alexturner/include/python3.15/cpython/object.h"
__attribute__ ((visibility ("default"))) void __attribute__((__noreturn__)) _PyObject_AssertFailed(
    PyObject *obj,
    const char *expr,
    const char *msg,
    const char *file,
    int line,
    const char *function);


__attribute__ ((visibility ("default"))) void _PyTrash_thread_deposit_object(PyThreadState *tstate, PyObject *op);
__attribute__ ((visibility ("default"))) void _PyTrash_thread_destroy_chain(PyThreadState *tstate);






__attribute__ ((visibility ("default"))) void * PyObject_GetItemData(PyObject *obj);

__attribute__ ((visibility ("default"))) int PyObject_VisitManagedDict(PyObject *obj, visitproc visit, void *arg);
__attribute__ ((visibility ("default"))) void PyObject_ClearManagedDict(PyObject *obj);


typedef int(*PyType_WatchCallback)(PyTypeObject *);
__attribute__ ((visibility ("default"))) int PyType_AddWatcher(PyType_WatchCallback callback);
__attribute__ ((visibility ("default"))) int PyType_ClearWatcher(int watcher_id);
__attribute__ ((visibility ("default"))) int PyType_Watch(int watcher_id, PyObject *type);
__attribute__ ((visibility ("default"))) int PyType_Unwatch(int watcher_id, PyObject *type);






__attribute__ ((visibility ("default"))) int PyUnstable_Type_AssignVersionTag(PyTypeObject *type);


typedef enum {
    PyRefTracer_CREATE = 0,
    PyRefTracer_DESTROY = 1,
    PyRefTracer_TRACKER_REMOVED = 2,
} PyRefTracerEvent;

typedef int (*PyRefTracer)(PyObject *, PyRefTracerEvent event, void *);
__attribute__ ((visibility ("default"))) int PyRefTracer_SetTracer(PyRefTracer tracer, void *data);
__attribute__ ((visibility ("default"))) PyRefTracer PyRefTracer_GetTracer(void**);






__attribute__ ((visibility ("default"))) int PyUnstable_Object_EnableDeferredRefcount(PyObject *);




__attribute__ ((visibility ("default"))) int PyUnstable_Object_IsUniqueReferencedTemporary(PyObject *);


__attribute__ ((visibility ("default"))) int PyUnstable_IsImmortal(PyObject *);




__attribute__ ((visibility ("default"))) int PyUnstable_TryIncRef(PyObject *);
__attribute__ ((visibility ("default"))) void PyUnstable_EnableTryIncRef(PyObject *);

__attribute__ ((visibility ("default"))) int PyUnstable_Object_IsUniquelyReferenced(PyObject *);
# 812 "/home/alexturner/include/python3.15/object.h" 2




static inline int
PyType_HasFeature(PyTypeObject *type, unsigned long feature)
{
    unsigned long flags;




    flags = type->tp_flags;

    return ((flags & feature) != 0);
}



static inline int PyType_Check(PyObject *op) {
    return PyType_HasFeature((_Py_TYPE_impl(((PyObject*)((op))))), ((1UL << 31)));
}







static inline int PyType_CheckExact(PyObject *op) {
    return _Py_IS_TYPE_impl(((PyObject*)((op))), (&PyType_Type));
}





__attribute__ ((visibility ("default"))) PyObject * PyType_GetModuleByDef(PyTypeObject *, PyModuleDef *);



__attribute__ ((visibility ("default"))) int PyType_Freeze(PyTypeObject *type);



__attribute__ ((visibility ("default"))) PyObject * PyType_GetModuleByToken(PyTypeObject *type,
                                               const void *token);
# 84 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/refcount.h" 1
# 96 "/home/alexturner/include/python3.15/refcount.h"
__attribute__ ((visibility ("default"))) Py_ssize_t Py_REFCNT(PyObject *ob);





    static inline Py_ssize_t _Py_REFCNT(PyObject *ob) {

        return ob->ob_refcnt;
# 114 "/home/alexturner/include/python3.15/refcount.h"
    }
# 123 "/home/alexturner/include/python3.15/refcount.h"
static inline __attribute__((always_inline)) int _Py_IsImmortal(PyObject *op)
{




    return ((int32_t)(op->ob_refcnt)) < 0;



}



static inline __attribute__((always_inline)) int _Py_IsStaticImmortal(PyObject *op)
{

    return (op->ob_flags & (1 << 2)) != 0;



}




__attribute__ ((visibility ("default"))) void _Py_SetRefcnt(PyObject *ob, Py_ssize_t refcnt);

static inline void Py_SET_REFCNT(PyObject *ob, Py_ssize_t refcnt) {
    
# 152 "/home/alexturner/include/python3.15/refcount.h" 3 4
   ((void) (0))
# 152 "/home/alexturner/include/python3.15/refcount.h"
                      ;
# 162 "/home/alexturner/include/python3.15/refcount.h"
    if (_Py_IsImmortal(((PyObject*)((ob))))) {
        return;
    }


    ob->ob_refcnt = (uint32_t)refcnt;
# 195 "/home/alexturner/include/python3.15/refcount.h"
}
# 236 "/home/alexturner/include/python3.15/refcount.h"
__attribute__ ((visibility ("default"))) void _Py_Dealloc(PyObject *);






__attribute__ ((visibility ("default"))) void Py_IncRef(PyObject *);
__attribute__ ((visibility ("default"))) void Py_DecRef(PyObject *);



__attribute__ ((visibility ("default"))) void _Py_IncRef(PyObject *);
__attribute__ ((visibility ("default"))) void _Py_DecRef(PyObject *);

static inline __attribute__((always_inline)) void Py_INCREF(PyObject *op)
{
# 281 "/home/alexturner/include/python3.15/refcount.h"
    uint32_t cur_refcnt = op->ob_refcnt;
    if (cur_refcnt >= (3ULL << 30)) {

        ((void)0);
        return;
    }
    op->ob_refcnt = cur_refcnt + 1;







    ((void)0);







}
# 410 "/home/alexturner/include/python3.15/refcount.h"
static inline __attribute__((always_inline)) void Py_DECREF(PyObject *op)
{


    if (_Py_IsImmortal(((PyObject*)((op))))) {
        ((void)0);
        return;
    }
    ((void)0);
    if (--op->ob_refcnt == 0) {
        _Py_Dealloc(op);
    }
}
# 500 "/home/alexturner/include/python3.15/refcount.h"
static inline void Py_XINCREF(PyObject *op)
{
    if (op != 
# 502 "/home/alexturner/include/python3.15/refcount.h" 3 4
             ((void *)0)
# 502 "/home/alexturner/include/python3.15/refcount.h"
                     ) {
        Py_INCREF(((PyObject*)((op))));
    }
}




static inline void Py_XDECREF(PyObject *op)
{
    if (op != 
# 512 "/home/alexturner/include/python3.15/refcount.h" 3 4
             ((void *)0)
# 512 "/home/alexturner/include/python3.15/refcount.h"
                     ) {
        Py_DECREF(((PyObject*)((op))));
    }
}






__attribute__ ((visibility ("default"))) PyObject* Py_NewRef(PyObject *obj);


__attribute__ ((visibility ("default"))) PyObject* Py_XNewRef(PyObject *obj);

static inline PyObject* _Py_NewRef(PyObject *obj)
{
    Py_INCREF(((PyObject*)((obj))));
    return obj;
}

static inline PyObject* _Py_XNewRef(PyObject *obj)
{
    Py_XINCREF(((PyObject*)((obj))));
    return obj;
}
# 85 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/objimpl.h" 1
# 93 "/home/alexturner/include/python3.15/objimpl.h"
__attribute__ ((visibility ("default"))) void * PyObject_Malloc(size_t size);

__attribute__ ((visibility ("default"))) void * PyObject_Calloc(size_t nelem, size_t elsize);

__attribute__ ((visibility ("default"))) void * PyObject_Realloc(void *ptr, size_t new_size);
__attribute__ ((visibility ("default"))) void PyObject_Free(void *ptr);
# 117 "/home/alexturner/include/python3.15/objimpl.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_Init(PyObject *, PyTypeObject *);
__attribute__ ((visibility ("default"))) PyVarObject * PyObject_InitVar(PyVarObject *,
                                           PyTypeObject *, Py_ssize_t);







__attribute__ ((visibility ("default"))) PyObject * _PyObject_New(PyTypeObject *);
__attribute__ ((visibility ("default"))) PyVarObject * _PyObject_NewVar(PyTypeObject *, Py_ssize_t);
# 150 "/home/alexturner/include/python3.15/objimpl.h"
__attribute__ ((visibility ("default"))) Py_ssize_t PyGC_Collect(void);

__attribute__ ((visibility ("default"))) int PyGC_Enable(void);
__attribute__ ((visibility ("default"))) int PyGC_Disable(void);
__attribute__ ((visibility ("default"))) int PyGC_IsEnabled(void);




__attribute__ ((visibility ("default"))) PyVarObject * _PyObject_GC_Resize(PyVarObject *, Py_ssize_t);





__attribute__ ((visibility ("default"))) PyObject * _PyObject_GC_New(PyTypeObject *);
__attribute__ ((visibility ("default"))) PyVarObject * _PyObject_GC_NewVar(PyTypeObject *, Py_ssize_t);




__attribute__ ((visibility ("default"))) void PyObject_GC_Track(void *);




__attribute__ ((visibility ("default"))) void PyObject_GC_UnTrack(void *);

__attribute__ ((visibility ("default"))) void PyObject_GC_Del(void *);






__attribute__ ((visibility ("default"))) int PyObject_GC_IsTracked(PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_GC_IsFinalized(PyObject *);
# 204 "/home/alexturner/include/python3.15/objimpl.h"
# 1 "/home/alexturner/include/python3.15/cpython/objimpl.h" 1




static inline size_t _PyObject_SIZE(PyTypeObject *type) {
    return ((size_t)(type->tp_basicsize));
}
# 23 "/home/alexturner/include/python3.15/cpython/objimpl.h"
static inline size_t _PyObject_VAR_SIZE(PyTypeObject *type, Py_ssize_t nitems) {
    size_t size = ((size_t)(type->tp_basicsize));
    size += ((size_t)(nitems)) * ((size_t)(type->tp_itemsize));
    return (((size_t)(size) + (size_t)((8) - 1)) & ~(size_t)((8) - 1));
}
# 59 "/home/alexturner/include/python3.15/cpython/objimpl.h"
typedef struct {

    void *ctx;


    void* (*alloc) (void *ctx, size_t size);


    void (*free) (void *ctx, void *ptr, size_t size);
} PyObjectArenaAllocator;


__attribute__ ((visibility ("default"))) void PyObject_GetArenaAllocator(PyObjectArenaAllocator *allocator);


__attribute__ ((visibility ("default"))) void PyObject_SetArenaAllocator(PyObjectArenaAllocator *allocator);



__attribute__ ((visibility ("default"))) int PyObject_IS_GC(PyObject *obj);



__attribute__ ((visibility ("default"))) int PyType_SUPPORTS_WEAKREFS(PyTypeObject *type);

__attribute__ ((visibility ("default"))) PyObject ** PyObject_GET_WEAKREFS_LISTPTR(PyObject *op);

__attribute__ ((visibility ("default"))) PyObject * PyUnstable_Object_GC_NewWithExtraData(PyTypeObject *,
                                                             size_t);
# 103 "/home/alexturner/include/python3.15/cpython/objimpl.h"
typedef int (*gcvisitobjects_t)(PyObject*, void*);
__attribute__ ((visibility ("default"))) void PyUnstable_GC_VisitObjects(gcvisitobjects_t callback, void* arg);
# 205 "/home/alexturner/include/python3.15/objimpl.h" 2
# 86 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/typeslots.h" 1
# 87 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pyhash.h" 1
# 52 "/home/alexturner/include/python3.15/pyhash.h"
# 1 "/home/alexturner/include/python3.15/cpython/pyhash.h" 1
# 30 "/home/alexturner/include/python3.15/cpython/pyhash.h"
__attribute__ ((visibility ("default"))) Py_hash_t _Py_HashDouble(PyObject *, double);



typedef struct {
    Py_hash_t (*const hash)(const void *, Py_ssize_t);
    const char *name;
    const int hash_bits;
    const int seed_bits;
} PyHash_FuncDef;

__attribute__ ((visibility ("default"))) PyHash_FuncDef* PyHash_GetFuncDef(void);

__attribute__ ((visibility ("default"))) Py_hash_t Py_HashPointer(const void *ptr);


__attribute__((__deprecated__)) static inline Py_hash_t
_Py_HashPointer(const void *ptr)
{
    return Py_HashPointer(ptr);
}

__attribute__ ((visibility ("default"))) Py_hash_t PyObject_GenericHash(PyObject *);

__attribute__ ((visibility ("default"))) Py_hash_t Py_HashBuffer(const void *ptr, Py_ssize_t len);
# 53 "/home/alexturner/include/python3.15/pyhash.h" 2
# 88 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/pydebug.h" 1







__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_DebugFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_VerboseFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_QuietFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_InteractiveFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_InspectFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_OptimizeFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_NoSiteFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_BytesWarningFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_FrozenFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_IgnoreEnvironmentFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_DontWriteBytecodeFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_NoUserSiteDirectory;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_UnbufferedStdioFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_HashRandomizationFlag;
__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_IsolatedFlag;
# 32 "/home/alexturner/include/python3.15/cpython/pydebug.h"
__attribute__ ((visibility ("default"))) char* Py_GETENV(const char *name);
# 89 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/bytearrayobject.h" 1
# 20 "/home/alexturner/include/python3.15/bytearrayobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyByteArray_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyByteArrayIter_Type;






__attribute__ ((visibility ("default"))) PyObject * PyByteArray_FromObject(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyByteArray_Concat(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyByteArray_FromStringAndSize(const char *, Py_ssize_t);
__attribute__ ((visibility ("default"))) Py_ssize_t PyByteArray_Size(PyObject *);
__attribute__ ((visibility ("default"))) char * PyByteArray_AsString(PyObject *);
__attribute__ ((visibility ("default"))) int PyByteArray_Resize(PyObject *, Py_ssize_t);



# 1 "/home/alexturner/include/python3.15/cpython/bytearrayobject.h" 1





typedef struct {
    PyVarObject ob_base;





    Py_ssize_t ob_alloc;
    char *ob_bytes;
    char *ob_start;
    Py_ssize_t ob_exports;
    PyObject *ob_bytes_object;
} PyByteArrayObject;





static inline char* PyByteArray_AS_STRING(PyObject *op)
{
    return (
# 26 "/home/alexturner/include/python3.15/cpython/bytearrayobject.h" 3 4
          ((void) (0))
# 26 "/home/alexturner/include/python3.15/cpython/bytearrayobject.h"
          , ((PyByteArrayObject*)(op)))->ob_start;
}


static inline Py_ssize_t PyByteArray_GET_SIZE(PyObject *op) {
    PyByteArrayObject *self = (
# 31 "/home/alexturner/include/python3.15/cpython/bytearrayobject.h" 3 4
                             ((void) (0))
# 31 "/home/alexturner/include/python3.15/cpython/bytearrayobject.h"
                             , ((PyByteArrayObject*)(op)));



    return _Py_SIZE_impl(((PyObject*)((self))));

}
# 38 "/home/alexturner/include/python3.15/bytearrayobject.h" 2
# 90 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/bytesobject.h" 1
# 24 "/home/alexturner/include/python3.15/bytesobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyBytes_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyBytesIter_Type;





__attribute__ ((visibility ("default"))) PyObject * PyBytes_FromStringAndSize(const char *, Py_ssize_t);
__attribute__ ((visibility ("default"))) PyObject * PyBytes_FromString(const char *);
__attribute__ ((visibility ("default"))) PyObject * PyBytes_FromObject(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyBytes_FromFormatV(const char*, va_list)
                                __attribute__((format(printf, 1, 0)));
__attribute__ ((visibility ("default"))) PyObject * PyBytes_FromFormat(const char*, ...)
                                __attribute__((format(printf, 1, 2)));
__attribute__ ((visibility ("default"))) Py_ssize_t PyBytes_Size(PyObject *);
__attribute__ ((visibility ("default"))) char * PyBytes_AsString(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyBytes_Repr(PyObject *, int);
__attribute__ ((visibility ("default"))) void PyBytes_Concat(PyObject **, PyObject *);
__attribute__ ((visibility ("default"))) void PyBytes_ConcatAndDel(PyObject **, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyBytes_DecodeEscape(const char *, Py_ssize_t,
                                            const char *, Py_ssize_t,
                                            const char *);





__attribute__ ((visibility ("default"))) int PyBytes_AsStringAndSize(
    PyObject *obj,
    char **s,
    Py_ssize_t *len
    );



# 1 "/home/alexturner/include/python3.15/cpython/bytesobject.h" 1




typedef struct {
    PyVarObject ob_base;
    __attribute__((__deprecated__)) Py_hash_t ob_shash;
    char ob_sval[1];






} PyBytesObject;

__attribute__ ((visibility ("default"))) int _PyBytes_Resize(PyObject **, Py_ssize_t);





static inline char* PyBytes_AS_STRING(PyObject *op)
{
    return (
# 25 "/home/alexturner/include/python3.15/cpython/bytesobject.h" 3 4
          ((void) (0))
# 25 "/home/alexturner/include/python3.15/cpython/bytesobject.h"
          , ((PyBytesObject*)(op)))->ob_sval;
}


static inline Py_ssize_t PyBytes_GET_SIZE(PyObject *op) {
    PyBytesObject *self = (
# 30 "/home/alexturner/include/python3.15/cpython/bytesobject.h" 3 4
                         ((void) (0))
# 30 "/home/alexturner/include/python3.15/cpython/bytesobject.h"
                         , ((PyBytesObject*)(op)));
    return _Py_SIZE_impl(((PyObject*)((self))));
}


__attribute__ ((visibility ("default"))) PyObject* PyBytes_Join(PyObject *sep, PyObject *iterable);


__attribute__((__deprecated__)) static inline PyObject*
_PyBytes_Join(PyObject *sep, PyObject *iterable)
{
    return PyBytes_Join(sep, iterable);
}




typedef struct PyBytesWriter PyBytesWriter;

__attribute__ ((visibility ("default"))) PyBytesWriter * PyBytesWriter_Create(
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) void PyBytesWriter_Discard(
    PyBytesWriter *writer);
__attribute__ ((visibility ("default"))) PyObject* PyBytesWriter_Finish(
    PyBytesWriter *writer);
__attribute__ ((visibility ("default"))) PyObject* PyBytesWriter_FinishWithSize(
    PyBytesWriter *writer,
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) PyObject* PyBytesWriter_FinishWithPointer(
    PyBytesWriter *writer,
    void *buf);

__attribute__ ((visibility ("default"))) void* PyBytesWriter_GetData(
    PyBytesWriter *writer);
__attribute__ ((visibility ("default"))) Py_ssize_t PyBytesWriter_GetSize(
    PyBytesWriter *writer);

__attribute__ ((visibility ("default"))) int PyBytesWriter_WriteBytes(
    PyBytesWriter *writer,
    const void *bytes,
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) int PyBytesWriter_Format(
    PyBytesWriter *writer,
    const char *format,
    ...);

__attribute__ ((visibility ("default"))) int PyBytesWriter_Resize(
    PyBytesWriter *writer,
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) int PyBytesWriter_Grow(
    PyBytesWriter *writer,
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) void* PyBytesWriter_GrowAndUpdatePointer(
    PyBytesWriter *writer,
    Py_ssize_t size,
    void *buf);
# 60 "/home/alexturner/include/python3.15/bytesobject.h" 2
# 91 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/unicodeobject.h" 1
# 94 "/home/alexturner/include/python3.15/unicodeobject.h"
typedef uint32_t Py_UCS4;
typedef uint16_t Py_UCS2;
typedef uint8_t Py_UCS1;






extern __attribute__ ((visibility ("default"))) PyTypeObject PyUnicode_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyUnicodeIter_Type;
# 122 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_FromStringAndSize(
    const char *u,
    Py_ssize_t size
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_FromString(
    const char *u
    );


__attribute__ ((visibility ("default"))) PyObject* PyUnicode_Substring(
    PyObject *str,
    Py_ssize_t start,
    Py_ssize_t end);
# 146 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) Py_UCS4* PyUnicode_AsUCS4(
    PyObject *unicode,
    Py_UCS4* buffer,
    Py_ssize_t buflen,
    int copy_null);




__attribute__ ((visibility ("default"))) Py_UCS4* PyUnicode_AsUCS4Copy(PyObject *unicode);





__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_GetLength(
    PyObject *unicode
);





__attribute__ ((visibility ("default"))) Py_UCS4 PyUnicode_ReadChar(
    PyObject *unicode,
    Py_ssize_t index
    );






__attribute__ ((visibility ("default"))) int PyUnicode_WriteChar(
    PyObject *unicode,
    Py_ssize_t index,
    Py_UCS4 character
    );
# 200 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) int PyUnicode_Resize(
    PyObject **unicode,
    Py_ssize_t length
    );
# 218 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_FromEncodedObject(
    PyObject *obj,
    const char *encoding,
    const char *errors
    );
# 233 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_FromObject(
    PyObject *obj
    );

__attribute__ ((visibility ("default"))) PyObject * PyUnicode_FromFormatV(
    const char *format,
    va_list vargs
    );
__attribute__ ((visibility ("default"))) PyObject * PyUnicode_FromFormat(
    const char *format,
    ...
    );

__attribute__ ((visibility ("default"))) void PyUnicode_InternInPlace(PyObject **);
__attribute__ ((visibility ("default"))) PyObject * PyUnicode_InternFromString(
    const char *u
    );
# 260 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_FromWideChar(
    const wchar_t *w,
    Py_ssize_t size
    );
# 277 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_AsWideChar(
    PyObject *unicode,
    wchar_t *w,
    Py_ssize_t size
    );
# 291 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) wchar_t* PyUnicode_AsWideCharString(
    PyObject *unicode,
    Py_ssize_t *size
    );
# 307 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_FromOrdinal(int ordinal);
# 330 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) const char* PyUnicode_GetDefaultEncoding(void);






__attribute__ ((visibility ("default"))) PyObject* PyUnicode_Decode(
    const char *s,
    Py_ssize_t size,
    const char *encoding,
    const char *errors
    );




__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsEncodedString(
    PyObject *unicode,
    const char *encoding,
    const char *errors
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_BuildEncodingMap(
    PyObject* string
   );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF7(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF7Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF8(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF8Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsUTF8String(
    PyObject *unicode
    );
# 405 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) const char * PyUnicode_AsUTF8AndSize(
    PyObject *unicode,
    Py_ssize_t *size);
# 435 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF32(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder


    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF32Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder,


    Py_ssize_t *consumed
    );




__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsUTF32String(
    PyObject *unicode
    );
# 502 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF16(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder


    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUTF16Stateful(
    const char *string,
    Py_ssize_t length,
    const char *errors,
    int *byteorder,


    Py_ssize_t *consumed
    );




__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsUTF16String(
    PyObject *unicode
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeUnicodeEscape(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsUnicodeEscapeString(
    PyObject *unicode
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeRawUnicodeEscape(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsRawUnicodeEscapeString(
    PyObject *unicode
    );





__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeLatin1(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsLatin1String(
    PyObject *unicode
    );







__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeASCII(
    const char *string,
    Py_ssize_t length,
    const char *errors
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsASCIIString(
    PyObject *unicode
    );
# 599 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeCharmap(
    const char *string,
    Py_ssize_t length,
    PyObject *mapping,
    const char *errors
    );

__attribute__ ((visibility ("default"))) PyObject* PyUnicode_AsCharmapString(
    PyObject *unicode,
    PyObject *mapping
    );
# 662 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeLocaleAndSize(
    const char *str,
    Py_ssize_t len,
    const char *errors);




__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeLocale(
    const char *str,
    const char *errors);






__attribute__ ((visibility ("default"))) PyObject* PyUnicode_EncodeLocale(
    PyObject *unicode,
    const char *errors
    );







__attribute__ ((visibility ("default"))) int PyUnicode_FSConverter(PyObject*, void*);




__attribute__ ((visibility ("default"))) int PyUnicode_FSDecoder(PyObject*, void*);





__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeFSDefault(
    const char *s
    );


__attribute__ ((visibility ("default"))) PyObject* PyUnicode_DecodeFSDefaultAndSize(
    const char *s,
    Py_ssize_t size
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_EncodeFSDefault(
    PyObject *unicode
    );
# 725 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_Concat(
    PyObject *left,
    PyObject *right
    );




__attribute__ ((visibility ("default"))) void PyUnicode_Append(
    PyObject **pleft,
    PyObject *right
    );




__attribute__ ((visibility ("default"))) void PyUnicode_AppendAndDel(
    PyObject **pleft,
    PyObject *right
    );
# 757 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_Split(
    PyObject *s,
    PyObject *sep,
    Py_ssize_t maxsplit
    );






__attribute__ ((visibility ("default"))) PyObject* PyUnicode_Splitlines(
    PyObject *s,
    int keepends
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_Partition(
    PyObject *s,
    PyObject *sep
    );




__attribute__ ((visibility ("default"))) PyObject* PyUnicode_RPartition(
    PyObject *s,
    PyObject *sep
    );
# 801 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_RSplit(
    PyObject *s,
    PyObject *sep,
    Py_ssize_t maxsplit
    );
# 819 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyUnicode_Translate(
    PyObject *str,
    PyObject *table,
    const char *errors
    );




__attribute__ ((visibility ("default"))) PyObject* PyUnicode_Join(
    PyObject *separator,
    PyObject *seq
    );




__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_Tailmatch(
    PyObject *str,
    PyObject *substr,
    Py_ssize_t start,
    Py_ssize_t end,
    int direction
    );





__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_Find(
    PyObject *str,
    PyObject *substr,
    Py_ssize_t start,
    Py_ssize_t end,
    int direction
    );



__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_FindChar(
    PyObject *str,
    Py_UCS4 ch,
    Py_ssize_t start,
    Py_ssize_t end,
    int direction
    );




__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_Count(
    PyObject *str,
    PyObject *substr,
    Py_ssize_t start,
    Py_ssize_t end
    );




__attribute__ ((visibility ("default"))) PyObject * PyUnicode_Replace(
    PyObject *str,
    PyObject *substr,
    PyObject *replstr,
    Py_ssize_t maxcount

    );





__attribute__ ((visibility ("default"))) int PyUnicode_Compare(
    PyObject *left,
    PyObject *right
    );







__attribute__ ((visibility ("default"))) int PyUnicode_CompareWithASCIIString(
    PyObject *left,
    const char *right
    );






__attribute__ ((visibility ("default"))) int PyUnicode_EqualToUTF8(PyObject *, const char *);
__attribute__ ((visibility ("default"))) int PyUnicode_EqualToUTF8AndSize(PyObject *, const char *, Py_ssize_t);



__attribute__ ((visibility ("default"))) int PyUnicode_Equal(PyObject *str1, PyObject *str2);
# 932 "/home/alexturner/include/python3.15/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyUnicode_RichCompare(
    PyObject *left,
    PyObject *right,
    int op
    );




__attribute__ ((visibility ("default"))) PyObject * PyUnicode_Format(
    PyObject *format,
    PyObject *args
    );







__attribute__ ((visibility ("default"))) int PyUnicode_Contains(
    PyObject *container,
    PyObject *element
    );



__attribute__ ((visibility ("default"))) int PyUnicode_IsIdentifier(PyObject *s);





# 1 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 1
# 9 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__((__deprecated__)) typedef wchar_t PY_UNICODE_TYPE;
__attribute__((__deprecated__)) typedef wchar_t Py_UNICODE;





static inline int Py_UNICODE_IS_SURROGATE(Py_UCS4 ch) {
    return (0xD800 <= ch && ch <= 0xDFFF);
}
static inline int Py_UNICODE_IS_HIGH_SURROGATE(Py_UCS4 ch) {
    return (0xD800 <= ch && ch <= 0xDBFF);
}
static inline int Py_UNICODE_IS_LOW_SURROGATE(Py_UCS4 ch) {
    return (0xDC00 <= ch && ch <= 0xDFFF);
}


static inline Py_UCS4 Py_UNICODE_JOIN_SURROGATES(Py_UCS4 high, Py_UCS4 low) {
    
# 28 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 28 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                             ;
    
# 29 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 29 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                           ;
    return 0x10000 + (((high & 0x03FF) << 10) | (low & 0x03FF));
}



static inline Py_UCS4 Py_UNICODE_HIGH_SURROGATE(Py_UCS4 ch) {
    
# 36 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 36 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                          ;
    return (0xD800 - (0x10000 >> 10) + (ch >> 10));
}



static inline Py_UCS4 Py_UNICODE_LOW_SURROGATE(Py_UCS4 ch) {
    
# 43 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 43 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                          ;
    return (0xDC00 + (ch & 0x3FF));
}




struct _PyUnicodeObject_state {
# 64 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
    unsigned int interned:2;
# 88 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
    unsigned int kind:3;




    unsigned int compact:1;



    unsigned int ascii:1;

    unsigned int statically_allocated:1;



    unsigned int :24;

};





typedef struct {
# 156 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
    PyObject ob_base;
    Py_ssize_t length;
    Py_hash_t hash;

   _Alignas(4) _Alignas(struct _PyUnicodeObject_state) struct _PyUnicodeObject_state state;
} PyASCIIObject;




typedef struct {
    PyASCIIObject _base;
    Py_ssize_t utf8_length;

    char *utf8;
} PyCompactUnicodeObject;


typedef struct {
    PyCompactUnicodeObject _base;
    union {
        void *any;
        Py_UCS1 *latin1;
        Py_UCS2 *ucs2;
        Py_UCS4 *ucs4;
    } data;
} PyUnicodeObject;
# 207 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
static inline unsigned int PyUnicode_CHECK_INTERNED(PyObject *op) {



    return (
# 211 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 211 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyASCIIObject*)((op))))->state.interned;

}



static inline unsigned int PyUnicode_IS_READY(PyObject* _unused_op __attribute__((unused))) {
    return 1;
}




static inline unsigned int PyUnicode_IS_ASCII(PyObject *op) {
    return (
# 225 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 225 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyASCIIObject*)((op))))->state.ascii;
}




static inline unsigned int PyUnicode_IS_COMPACT(PyObject *op) {
    return (
# 232 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 232 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyASCIIObject*)((op))))->state.compact;
}




static inline int PyUnicode_IS_COMPACT_ASCII(PyObject *op) {
    return ((
# 239 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
           ((void) (0))
# 239 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
           , ((PyASCIIObject*)((op))))->state.ascii && PyUnicode_IS_COMPACT(((PyObject*)((op)))));
}


enum PyUnicode_Kind {

    PyUnicode_1BYTE_KIND = 1,
    PyUnicode_2BYTE_KIND = 2,
    PyUnicode_4BYTE_KIND = 4
};

__attribute__ ((visibility ("default"))) int PyUnicode_KIND(PyObject *op);
# 261 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
static inline void* _PyUnicode_COMPACT_DATA(PyObject *op) {
    if (PyUnicode_IS_ASCII(((PyObject*)((op))))) {
        return ((void*)(((
# 263 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
              ((void) (0))
# 263 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
              , ((PyASCIIObject*)((op)))) + 1)));
    }
    return ((void*)(((
# 265 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 265 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyCompactUnicodeObject*)((op)))) + 1)));
}

static inline void* _PyUnicode_NONCOMPACT_DATA(PyObject *op) {
    void *data;
    
# 270 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 270 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                    ;
    data = (
# 271 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 271 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyUnicodeObject*)((op))))->data.any;
    
# 272 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 272 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                       ;
    return data;
}

__attribute__ ((visibility ("default"))) void* PyUnicode_DATA(PyObject *op);

static inline void* _PyUnicode_DATA(PyObject *op) {
    if (PyUnicode_IS_COMPACT(((PyObject*)((op))))) {
        return _PyUnicode_COMPACT_DATA(op);
    }
    return _PyUnicode_NONCOMPACT_DATA(op);
}
# 296 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
static inline Py_ssize_t PyUnicode_GET_LENGTH(PyObject *op) {
    return (
# 297 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 297 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyASCIIObject*)((op))))->length;
}



static inline Py_hash_t
PyUnstable_Unicode_GET_CACHED_HASH(PyObject *op) {



    return (
# 307 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 307 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyASCIIObject*)((op))))->hash;

}






static inline void PyUnicode_WRITE(int kind, void *data,
                                   Py_ssize_t index, Py_UCS4 value)
{
    
# 319 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 319 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                     ;
    if (kind == PyUnicode_1BYTE_KIND) {
        
# 321 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
       ((void) (0))
# 321 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                             ;
        ((Py_UCS1*)(data))[index] = ((Py_UCS1)(value));
    }
    else if (kind == PyUnicode_2BYTE_KIND) {
        
# 325 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
       ((void) (0))
# 325 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                               ;
        ((Py_UCS2*)(data))[index] = ((Py_UCS2)(value));
    }
    else {
        
# 329 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
       ((void) (0))
# 329 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                           ;
        
# 330 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
       ((void) (0))
# 330 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                 ;
        ((Py_UCS4*)(data))[index] = value;
    }
}






static inline Py_UCS4 PyUnicode_READ(int kind,
                                     const void *data, Py_ssize_t index)
{
    
# 343 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 343 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                     ;
    if (kind == PyUnicode_1BYTE_KIND) {
        return ((const Py_UCS1*)(data))[index];
    }
    if (kind == PyUnicode_2BYTE_KIND) {
        return ((const Py_UCS2*)(data))[index];
    }
    
# 350 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 350 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                       ;
    return ((const Py_UCS4*)(data))[index];
}
# 362 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
static inline Py_UCS4 PyUnicode_READ_CHAR(PyObject *unicode, Py_ssize_t index)
{
    int kind;

    
# 366 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 366 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                     ;

    
# 368 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 368 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                                 ;

    kind = ((void)0, ((
# 370 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 370 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyASCIIObject*)((unicode))))->state.kind));
    if (kind == PyUnicode_1BYTE_KIND) {
        return ((Py_UCS1*)(_PyUnicode_DATA(((PyObject*)((unicode))))))[index];
    }
    if (kind == PyUnicode_2BYTE_KIND) {
        return ((Py_UCS2*)(_PyUnicode_DATA(((PyObject*)((unicode))))))[index];
    }
    
# 377 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 377 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                       ;
    return ((Py_UCS4*)(_PyUnicode_DATA(((PyObject*)((unicode))))))[index];
}






static inline Py_UCS4 PyUnicode_MAX_CHAR_VALUE(PyObject *op)
{
    int kind;

    if (PyUnicode_IS_ASCII(((PyObject*)((op))))) {
        return 0x7fU;
    }

    kind = ((void)0, ((
# 394 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
          ((void) (0))
# 394 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
          , ((PyASCIIObject*)((op))))->state.kind));
    if (kind == PyUnicode_1BYTE_KIND) {
       return 0xffU;
    }
    if (kind == PyUnicode_2BYTE_KIND) {
        return 0xffffU;
    }
    
# 401 "/home/alexturner/include/python3.15/cpython/unicodeobject.h" 3 4
   ((void) (0))
# 401 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
                                       ;
    return 0x10ffffU;
}
# 413 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyUnicode_New(
    Py_ssize_t size,
    Py_UCS4 maxchar
    );


static inline int PyUnicode_READY(PyObject* _unused_op __attribute__((unused)))
{
    return 0;
}
# 443 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_CopyCharacters(
    PyObject *to,
    Py_ssize_t to_start,
    PyObject *from,
    Py_ssize_t from_start,
    Py_ssize_t how_many
    );
# 459 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__ ((visibility ("default"))) Py_ssize_t PyUnicode_Fill(
    PyObject *unicode,
    Py_ssize_t start,
    Py_ssize_t length,
    Py_UCS4 fill_char
    );



__attribute__ ((visibility ("default"))) PyObject* PyUnicode_FromKindAndData(
    int kind,
    const void *buffer,
    Py_ssize_t size);




typedef struct PyUnicodeWriter PyUnicodeWriter;

__attribute__ ((visibility ("default"))) PyUnicodeWriter* PyUnicodeWriter_Create(Py_ssize_t length);
__attribute__ ((visibility ("default"))) void PyUnicodeWriter_Discard(PyUnicodeWriter *writer);
__attribute__ ((visibility ("default"))) PyObject* PyUnicodeWriter_Finish(PyUnicodeWriter *writer);

__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteChar(
    PyUnicodeWriter *writer,
    Py_UCS4 ch);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteUTF8(
    PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteASCII(
    PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteWideChar(
    PyUnicodeWriter *writer,
    const wchar_t *str,
    Py_ssize_t size);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteUCS4(
    PyUnicodeWriter *writer,
    Py_UCS4 *str,
    Py_ssize_t size);

__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteStr(
    PyUnicodeWriter *writer,
    PyObject *obj);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteRepr(
    PyUnicodeWriter *writer,
    PyObject *obj);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_WriteSubstring(
    PyUnicodeWriter *writer,
    PyObject *str,
    Py_ssize_t start,
    Py_ssize_t end);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_Format(
    PyUnicodeWriter *writer,
    const char *format,
    ...);
__attribute__ ((visibility ("default"))) int PyUnicodeWriter_DecodeUTF8Stateful(
    PyUnicodeWriter *writer,
    const char *string,
    Py_ssize_t length,
    const char *errors,
    Py_ssize_t *consumed);




typedef struct {
    PyObject *buffer;
    void *data;
    int kind;
    Py_UCS4 maxchar;
    Py_ssize_t size;
    Py_ssize_t pos;


    Py_ssize_t min_length;


    Py_UCS4 min_char;


    unsigned char overallocate;



    unsigned char readonly;
} _PyUnicodeWriter;






__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void _PyUnicodeWriter_Init(
    _PyUnicodeWriter *writer);
# 571 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyUnicodeWriter_PrepareInternal(
    _PyUnicodeWriter *writer,
    Py_ssize_t length,
    Py_UCS4 maxchar);
# 588 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyUnicodeWriter_PrepareKindInternal(
    _PyUnicodeWriter *writer,
    int kind);



__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyUnicodeWriter_WriteChar(
    _PyUnicodeWriter *writer,
    Py_UCS4 ch);



__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyUnicodeWriter_WriteStr(
    _PyUnicodeWriter *writer,
    PyObject *str);



__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyUnicodeWriter_WriteSubstring(
    _PyUnicodeWriter *writer,
    PyObject *str,
    Py_ssize_t start,
    Py_ssize_t end);



__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyUnicodeWriter_WriteASCIIString(
    _PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t len);



__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyUnicodeWriter_WriteLatin1String(
    _PyUnicodeWriter *writer,
    const char *str,
    Py_ssize_t len);




__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) PyObject * _PyUnicodeWriter_Finish(
    _PyUnicodeWriter *writer);


__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void _PyUnicodeWriter_Dealloc(
    _PyUnicodeWriter *writer);
# 652 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__ ((visibility ("default"))) const char * PyUnicode_AsUTF8(PyObject *unicode);


__attribute__((__deprecated__)) static inline const char*
_PyUnicode_AsString(PyObject *unicode)
{
    return PyUnicode_AsUTF8(unicode);
}
# 671 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
__attribute__ ((visibility ("default"))) int _PyUnicode_IsLowercase(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsUppercase(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsTitlecase(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsWhitespace(
    const Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsLinebreak(
    const Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) Py_UCS4 _PyUnicode_ToLowercase(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) Py_UCS4 _PyUnicode_ToUppercase(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) Py_UCS4 _PyUnicode_ToTitlecase(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_ToDecimalDigit(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_ToDigit(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) double _PyUnicode_ToNumeric(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsDecimalDigit(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsDigit(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsNumeric(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsPrintable(
    Py_UCS4 ch
    );

__attribute__ ((visibility ("default"))) int _PyUnicode_IsAlpha(
    Py_UCS4 ch
    );


extern __attribute__ ((visibility ("default"))) const unsigned char _Py_ascii_whitespace[];





static inline int Py_UNICODE_ISSPACE(Py_UCS4 ch) {
    if (ch < 128) {
        return _Py_ascii_whitespace[ch];
    }
    return _PyUnicode_IsWhitespace(ch);
}
# 769 "/home/alexturner/include/python3.15/cpython/unicodeobject.h"
static inline int Py_UNICODE_ISALNUM(Py_UCS4 ch) {
   return (_PyUnicode_IsAlpha(ch)
           || _PyUnicode_IsDecimalDigit(ch)
           || _PyUnicode_IsDigit(ch)
           || _PyUnicode_IsNumeric(ch));
}






__attribute__ ((visibility ("default"))) PyObject* _PyUnicode_FromId(_Py_Identifier*);
# 966 "/home/alexturner/include/python3.15/unicodeobject.h" 2
# 92 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pyerrors.h" 1
# 9 "/home/alexturner/include/python3.15/pyerrors.h"
__attribute__ ((visibility ("default"))) void PyErr_SetNone(PyObject *);
__attribute__ ((visibility ("default"))) void PyErr_SetObject(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) void PyErr_SetString(
    PyObject *exception,
    const char *string
    );
__attribute__ ((visibility ("default"))) PyObject * PyErr_Occurred(void);
__attribute__ ((visibility ("default"))) void PyErr_Clear(void);
__attribute__ ((visibility ("default"))) void PyErr_Fetch(PyObject **, PyObject **, PyObject **);
__attribute__ ((visibility ("default"))) void PyErr_Restore(PyObject *, PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyErr_GetRaisedException(void);
__attribute__ ((visibility ("default"))) void PyErr_SetRaisedException(PyObject *);

__attribute__ ((visibility ("default"))) PyObject* PyErr_GetHandledException(void);
__attribute__ ((visibility ("default"))) void PyErr_SetHandledException(PyObject *);


__attribute__ ((visibility ("default"))) void PyErr_GetExcInfo(PyObject **, PyObject **, PyObject **);
__attribute__ ((visibility ("default"))) void PyErr_SetExcInfo(PyObject *, PyObject *, PyObject *);







__attribute__ ((visibility ("default"))) void __attribute__((__noreturn__)) Py_FatalError(const char *message);


__attribute__ ((visibility ("default"))) int PyErr_GivenExceptionMatches(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) int PyErr_ExceptionMatches(PyObject *);
__attribute__ ((visibility ("default"))) void PyErr_NormalizeException(PyObject**, PyObject**, PyObject**);


__attribute__ ((visibility ("default"))) int PyException_SetTraceback(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyException_GetTraceback(PyObject *);


__attribute__ ((visibility ("default"))) PyObject * PyException_GetCause(PyObject *);
__attribute__ ((visibility ("default"))) void PyException_SetCause(PyObject *, PyObject *);


__attribute__ ((visibility ("default"))) PyObject * PyException_GetContext(PyObject *);
__attribute__ ((visibility ("default"))) void PyException_SetContext(PyObject *, PyObject *);


__attribute__ ((visibility ("default"))) PyObject * PyException_GetArgs(PyObject *);
__attribute__ ((visibility ("default"))) void PyException_SetArgs(PyObject *, PyObject *);
# 67 "/home/alexturner/include/python3.15/pyerrors.h"
__attribute__ ((visibility ("default"))) const char * PyExceptionClass_Name(PyObject *);
# 76 "/home/alexturner/include/python3.15/pyerrors.h"
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_BaseException;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_Exception;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_BaseExceptionGroup;

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_StopAsyncIteration;

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_StopIteration;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_GeneratorExit;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ArithmeticError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_LookupError;

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_AssertionError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_AttributeError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_BufferError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_EOFError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_FloatingPointError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_OSError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ImportError;

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ModuleNotFoundError;

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_IndexError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_KeyError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_KeyboardInterrupt;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_MemoryError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_NameError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_OverflowError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_RuntimeError;

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_RecursionError;

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_NotImplementedError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_SyntaxError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_IndentationError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_TabError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ReferenceError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_SystemError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_SystemExit;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_TypeError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_UnboundLocalError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_UnicodeError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_UnicodeEncodeError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_UnicodeDecodeError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_UnicodeTranslateError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ValueError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ZeroDivisionError;


extern __attribute__ ((visibility ("default"))) PyObject * PyExc_BlockingIOError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_BrokenPipeError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ChildProcessError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ConnectionError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ConnectionAbortedError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ConnectionRefusedError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ConnectionResetError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_FileExistsError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_FileNotFoundError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_InterruptedError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_IsADirectoryError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_NotADirectoryError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_PermissionError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ProcessLookupError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_TimeoutError;




extern __attribute__ ((visibility ("default"))) PyObject * PyExc_EnvironmentError;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_IOError;





extern __attribute__ ((visibility ("default"))) PyObject * PyExc_Warning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_UserWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_DeprecationWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_PendingDeprecationWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_SyntaxWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_RuntimeWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_FutureWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ImportWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_UnicodeWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_BytesWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_EncodingWarning;
extern __attribute__ ((visibility ("default"))) PyObject * PyExc_ResourceWarning;




__attribute__ ((visibility ("default"))) int PyErr_BadArgument(void);
__attribute__ ((visibility ("default"))) PyObject * PyErr_NoMemory(void);
__attribute__ ((visibility ("default"))) PyObject * PyErr_SetFromErrno(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyErr_SetFromErrnoWithFilenameObject(
    PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyErr_SetFromErrnoWithFilenameObjects(
    PyObject *, PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyErr_SetFromErrnoWithFilename(
    PyObject *exc,
    const char *filename
    );

__attribute__ ((visibility ("default"))) PyObject * PyErr_Format(
    PyObject *exception,
    const char *format,
    ...
    );

__attribute__ ((visibility ("default"))) PyObject * PyErr_FormatV(
    PyObject *exception,
    const char *format,
    va_list vargs);
# 213 "/home/alexturner/include/python3.15/pyerrors.h"
__attribute__ ((visibility ("default"))) PyObject * PyErr_SetImportErrorSubclass(PyObject *, PyObject *,
    PyObject *, PyObject *);


__attribute__ ((visibility ("default"))) PyObject * PyErr_SetImportError(PyObject *, PyObject *,
    PyObject *);



__attribute__ ((visibility ("default"))) void PyErr_BadInternalCall(void);
__attribute__ ((visibility ("default"))) void _PyErr_BadInternalCall(const char *filename, int lineno);





__attribute__ ((visibility ("default"))) PyObject * PyErr_NewException(
    const char *name, PyObject *base, PyObject *dict);
__attribute__ ((visibility ("default"))) PyObject * PyErr_NewExceptionWithDoc(
    const char *name, const char *doc, PyObject *base, PyObject *dict);
__attribute__ ((visibility ("default"))) void PyErr_WriteUnraisable(PyObject *);



__attribute__ ((visibility ("default"))) int PyErr_CheckSignals(void);
__attribute__ ((visibility ("default"))) void PyErr_SetInterrupt(void);

__attribute__ ((visibility ("default"))) int PyErr_SetInterruptEx(int signum);



__attribute__ ((visibility ("default"))) void PyErr_SyntaxLocation(
    const char *filename,
    int lineno);
__attribute__ ((visibility ("default"))) void PyErr_SyntaxLocationEx(
    const char *filename,
    int lineno,
    int col_offset);
__attribute__ ((visibility ("default"))) PyObject * PyErr_ProgramText(
    const char *filename,
    int lineno);





__attribute__ ((visibility ("default"))) PyObject * PyUnicodeDecodeError_Create(
    const char *encoding,
    const char *object,
    Py_ssize_t length,
    Py_ssize_t start,
    Py_ssize_t end,
    const char *reason
    );


__attribute__ ((visibility ("default"))) PyObject * PyUnicodeEncodeError_GetEncoding(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyUnicodeDecodeError_GetEncoding(PyObject *);


__attribute__ ((visibility ("default"))) PyObject * PyUnicodeEncodeError_GetObject(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyUnicodeDecodeError_GetObject(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyUnicodeTranslateError_GetObject(PyObject *);



__attribute__ ((visibility ("default"))) int PyUnicodeEncodeError_GetStart(PyObject *, Py_ssize_t *);
__attribute__ ((visibility ("default"))) int PyUnicodeDecodeError_GetStart(PyObject *, Py_ssize_t *);
__attribute__ ((visibility ("default"))) int PyUnicodeTranslateError_GetStart(PyObject *, Py_ssize_t *);



__attribute__ ((visibility ("default"))) int PyUnicodeEncodeError_SetStart(PyObject *, Py_ssize_t);
__attribute__ ((visibility ("default"))) int PyUnicodeDecodeError_SetStart(PyObject *, Py_ssize_t);
__attribute__ ((visibility ("default"))) int PyUnicodeTranslateError_SetStart(PyObject *, Py_ssize_t);



__attribute__ ((visibility ("default"))) int PyUnicodeEncodeError_GetEnd(PyObject *, Py_ssize_t *);
__attribute__ ((visibility ("default"))) int PyUnicodeDecodeError_GetEnd(PyObject *, Py_ssize_t *);
__attribute__ ((visibility ("default"))) int PyUnicodeTranslateError_GetEnd(PyObject *, Py_ssize_t *);



__attribute__ ((visibility ("default"))) int PyUnicodeEncodeError_SetEnd(PyObject *, Py_ssize_t);
__attribute__ ((visibility ("default"))) int PyUnicodeDecodeError_SetEnd(PyObject *, Py_ssize_t);
__attribute__ ((visibility ("default"))) int PyUnicodeTranslateError_SetEnd(PyObject *, Py_ssize_t);


__attribute__ ((visibility ("default"))) PyObject * PyUnicodeEncodeError_GetReason(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyUnicodeDecodeError_GetReason(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyUnicodeTranslateError_GetReason(PyObject *);



__attribute__ ((visibility ("default"))) int PyUnicodeEncodeError_SetReason(
    PyObject *exc,
    const char *reason
    );
__attribute__ ((visibility ("default"))) int PyUnicodeDecodeError_SetReason(
    PyObject *exc,
    const char *reason
    );
__attribute__ ((visibility ("default"))) int PyUnicodeTranslateError_SetReason(
    PyObject *exc,
    const char *reason
    );

__attribute__ ((visibility ("default"))) int PyOS_snprintf(char *str, size_t size, const char *format, ...)
                        __attribute__((format(printf, 3, 4)));
__attribute__ ((visibility ("default"))) int PyOS_vsnprintf(char *str, size_t size, const char *format, va_list va)
                        __attribute__((format(printf, 3, 0)));



# 1 "/home/alexturner/include/python3.15/cpython/pyerrors.h" 1
# 13 "/home/alexturner/include/python3.15/cpython/pyerrors.h"
typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
} PyBaseExceptionObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *msg;
    PyObject *excs;
} PyBaseExceptionGroupObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *msg;
    PyObject *filename;
    PyObject *lineno;
    PyObject *offset;
    PyObject *end_lineno;
    PyObject *end_offset;
    PyObject *text;
    PyObject *print_file_and_line;
    PyObject *metadata;
} PySyntaxErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *msg;
    PyObject *name;
    PyObject *path;
    PyObject *name_from;
} PyImportErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *encoding;
    PyObject *object;
    Py_ssize_t start;
    Py_ssize_t end;
    PyObject *reason;
} PyUnicodeErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *code;
} PySystemExitObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *myerrno;
    PyObject *strerror;
    PyObject *filename;
    PyObject *filename2;



    Py_ssize_t written;
} PyOSErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *value;
} PyStopIterationObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *name;
} PyNameErrorObject;

typedef struct {
    PyObject ob_base; PyObject *dict; PyObject *args; PyObject *notes; PyObject *traceback; PyObject *context; PyObject *cause; char suppress_context;
    PyObject *obj;
    PyObject *name;
} PyAttributeErrorObject;


typedef PyOSErrorObject PyEnvironmentErrorObject;






__attribute__ ((visibility ("default"))) void _PyErr_ChainExceptions1(PyObject *);



__attribute__ ((visibility ("default"))) PyObject* PyUnstable_Exc_PrepReraiseStar(
     PyObject *orig,
     PyObject *excs);



__attribute__ ((visibility ("default"))) int PySignal_SetWakeupFd(int fd);



__attribute__ ((visibility ("default"))) void PyErr_SyntaxLocationObject(
    PyObject *filename,
    int lineno,
    int col_offset);

__attribute__ ((visibility ("default"))) void PyErr_RangedSyntaxLocationObject(
    PyObject *filename,
    int lineno,
    int col_offset,
    int end_lineno,
    int end_col_offset);

__attribute__ ((visibility ("default"))) PyObject * PyErr_ProgramTextObject(
    PyObject *filename,
    int lineno);

__attribute__ ((visibility ("default"))) void __attribute__((__noreturn__)) _Py_FatalErrorFunc(
    const char *func,
    const char *message);

__attribute__ ((visibility ("default"))) void PyErr_FormatUnraisable(const char *, ...);

extern __attribute__ ((visibility ("default"))) PyObject * PyExc_PythonFinalizationError;
# 329 "/home/alexturner/include/python3.15/pyerrors.h" 2
# 93 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/longobject.h" 1
# 16 "/home/alexturner/include/python3.15/longobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyLong_FromLong(long);
__attribute__ ((visibility ("default"))) PyObject * PyLong_FromUnsignedLong(unsigned long);
__attribute__ ((visibility ("default"))) PyObject * PyLong_FromSize_t(size_t);
__attribute__ ((visibility ("default"))) PyObject * PyLong_FromSsize_t(Py_ssize_t);
__attribute__ ((visibility ("default"))) PyObject * PyLong_FromDouble(double);

__attribute__ ((visibility ("default"))) long PyLong_AsLong(PyObject *);
__attribute__ ((visibility ("default"))) long PyLong_AsLongAndOverflow(PyObject *, int *);
__attribute__ ((visibility ("default"))) Py_ssize_t PyLong_AsSsize_t(PyObject *);
__attribute__ ((visibility ("default"))) size_t PyLong_AsSize_t(PyObject *);
__attribute__ ((visibility ("default"))) unsigned long PyLong_AsUnsignedLong(PyObject *);
__attribute__ ((visibility ("default"))) unsigned long PyLong_AsUnsignedLongMask(PyObject *);


__attribute__ ((visibility ("default"))) int PyLong_AsInt(PyObject *);



__attribute__ ((visibility ("default"))) PyObject* PyLong_FromInt32(int32_t value);
__attribute__ ((visibility ("default"))) PyObject* PyLong_FromUInt32(uint32_t value);
__attribute__ ((visibility ("default"))) PyObject* PyLong_FromInt64(int64_t value);
__attribute__ ((visibility ("default"))) PyObject* PyLong_FromUInt64(uint64_t value);

__attribute__ ((visibility ("default"))) int PyLong_AsInt32(PyObject *obj, int32_t *value);
__attribute__ ((visibility ("default"))) int PyLong_AsUInt32(PyObject *obj, uint32_t *value);
__attribute__ ((visibility ("default"))) int PyLong_AsInt64(PyObject *obj, int64_t *value);
__attribute__ ((visibility ("default"))) int PyLong_AsUInt64(PyObject *obj, uint64_t *value);
# 79 "/home/alexturner/include/python3.15/longobject.h"
__attribute__ ((visibility ("default"))) Py_ssize_t PyLong_AsNativeBytes(PyObject* v, void* buffer,
    Py_ssize_t n_bytes, int flags);
# 90 "/home/alexturner/include/python3.15/longobject.h"
__attribute__ ((visibility ("default"))) PyObject* PyLong_FromNativeBytes(const void* buffer, size_t n_bytes,
    int flags);
__attribute__ ((visibility ("default"))) PyObject* PyLong_FromUnsignedNativeBytes(const void* buffer,
    size_t n_bytes, int flags);



__attribute__ ((visibility ("default"))) PyObject * PyLong_GetInfo(void);
# 150 "/home/alexturner/include/python3.15/longobject.h"
__attribute__ ((visibility ("default"))) double PyLong_AsDouble(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyLong_FromVoidPtr(void *);
__attribute__ ((visibility ("default"))) void * PyLong_AsVoidPtr(PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyLong_FromLongLong(long long);
__attribute__ ((visibility ("default"))) PyObject * PyLong_FromUnsignedLongLong(unsigned long long);
__attribute__ ((visibility ("default"))) long long PyLong_AsLongLong(PyObject *);
__attribute__ ((visibility ("default"))) unsigned long long PyLong_AsUnsignedLongLong(PyObject *);
__attribute__ ((visibility ("default"))) unsigned long long PyLong_AsUnsignedLongLongMask(PyObject *);
__attribute__ ((visibility ("default"))) long long PyLong_AsLongLongAndOverflow(PyObject *, int *);

__attribute__ ((visibility ("default"))) PyObject * PyLong_FromString(const char *, char **, int);




__attribute__ ((visibility ("default"))) unsigned long PyOS_strtoul(const char *, char **, int);
__attribute__ ((visibility ("default"))) long PyOS_strtol(const char *, char **, int);



# 1 "/home/alexturner/include/python3.15/cpython/longobject.h" 1







__attribute__ ((visibility ("default"))) PyObject* PyLong_FromUnicodeObject(PyObject *u, int base);

__attribute__ ((visibility ("default"))) int PyUnstable_Long_IsCompact(const PyLongObject* op);
__attribute__ ((visibility ("default"))) Py_ssize_t PyUnstable_Long_CompactValue(const PyLongObject* op);





__attribute__ ((visibility ("default"))) int PyLong_IsPositive(PyObject *obj);





__attribute__ ((visibility ("default"))) int PyLong_IsNegative(PyObject *obj);





__attribute__ ((visibility ("default"))) int PyLong_IsZero(PyObject *obj);






__attribute__ ((visibility ("default"))) int PyLong_GetSign(PyObject *v, int *sign);

__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int _PyLong_Sign(PyObject *v);







__attribute__ ((visibility ("default"))) int64_t _PyLong_NumBits(PyObject *v);
# 61 "/home/alexturner/include/python3.15/cpython/longobject.h"
__attribute__ ((visibility ("default"))) PyObject * _PyLong_FromByteArray(
    const unsigned char* bytes, size_t n,
    int little_endian, int is_signed);
# 84 "/home/alexturner/include/python3.15/cpython/longobject.h"
__attribute__ ((visibility ("default"))) int _PyLong_AsByteArray(PyLongObject* v,
    unsigned char* bytes, size_t n,
    int little_endian, int is_signed, int with_exceptions);


__attribute__ ((visibility ("default"))) PyObject * _PyLong_GCD(PyObject *, PyObject *);
# 172 "/home/alexturner/include/python3.15/longobject.h" 2
# 94 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/longintrepr.h" 1
# 43 "/home/alexturner/include/python3.15/cpython/longintrepr.h"
typedef uint32_t digit;
typedef int32_t sdigit;
typedef uint64_t twodigits;
typedef int64_t stwodigits;
# 93 "/home/alexturner/include/python3.15/cpython/longintrepr.h"
typedef struct _PyLongValue {
    uintptr_t lv_tag;
    digit ob_digit[1];
} _PyLongValue;

struct _longobject {
    PyObject ob_base;
    _PyLongValue long_value;
};

__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) PyLongObject* _PyLong_New(Py_ssize_t);


__attribute__ ((visibility ("default"))) PyObject* _PyLong_Copy(PyLongObject *src);

__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) PyLongObject* _PyLong_FromDigits(
    int negative,
    Py_ssize_t digit_count,
    digit *digits);
# 121 "/home/alexturner/include/python3.15/cpython/longintrepr.h"
static inline int
_PyLong_IsCompact(const PyLongObject* op) {
    
# 123 "/home/alexturner/include/python3.15/cpython/longintrepr.h" 3 4
   ((void) (0))
# 123 "/home/alexturner/include/python3.15/cpython/longintrepr.h"
                                                                           ;
    return op->long_value.lv_tag < (2 << 3);
}



static inline Py_ssize_t
_PyLong_CompactValue(const PyLongObject *op)
{
    Py_ssize_t sign;
    
# 133 "/home/alexturner/include/python3.15/cpython/longintrepr.h" 3 4
   ((void) (0))
# 133 "/home/alexturner/include/python3.15/cpython/longintrepr.h"
                                                                           ;
    
# 134 "/home/alexturner/include/python3.15/cpython/longintrepr.h" 3 4
   ((void) (0))
# 134 "/home/alexturner/include/python3.15/cpython/longintrepr.h"
                                        ;
    sign = 1 - (op->long_value.lv_tag & 3);
    return sign * (Py_ssize_t)op->long_value.ob_digit[0];
}






typedef struct PyLongLayout {
    uint8_t bits_per_digit;
    uint8_t digit_size;
    int8_t digits_order;
    int8_t digit_endianness;
} PyLongLayout;

__attribute__ ((visibility ("default"))) const PyLongLayout* PyLong_GetNativeLayout(void);

typedef struct PyLongExport {
    int64_t value;
    uint8_t negative;
    Py_ssize_t ndigits;
    const void *digits;

    Py_uintptr_t _reserved;
} PyLongExport;

__attribute__ ((visibility ("default"))) int PyLong_Export(
    PyObject *obj,
    PyLongExport *export_long);
__attribute__ ((visibility ("default"))) void PyLong_FreeExport(
    PyLongExport *export_long);




typedef struct PyLongWriter PyLongWriter;

__attribute__ ((visibility ("default"))) PyLongWriter* PyLongWriter_Create(
    int negative,
    Py_ssize_t ndigits,
    void **digits);
__attribute__ ((visibility ("default"))) PyObject* PyLongWriter_Finish(PyLongWriter *writer);
__attribute__ ((visibility ("default"))) void PyLongWriter_Discard(PyLongWriter *writer);
# 95 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/boolobject.h" 1
# 17 "/home/alexturner/include/python3.15/boolobject.h"
extern __attribute__ ((visibility ("default"))) PyLongObject _Py_FalseStruct;
extern __attribute__ ((visibility ("default"))) PyLongObject _Py_TrueStruct;
# 30 "/home/alexturner/include/python3.15/boolobject.h"
__attribute__ ((visibility ("default"))) int Py_IsTrue(PyObject *x);



__attribute__ ((visibility ("default"))) int Py_IsFalse(PyObject *x);
# 49 "/home/alexturner/include/python3.15/boolobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyBool_FromLong(long);
# 96 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/floatobject.h" 1
# 14 "/home/alexturner/include/python3.15/floatobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyFloat_Type;
# 31 "/home/alexturner/include/python3.15/floatobject.h"
__attribute__ ((visibility ("default"))) double PyFloat_GetMax(void);
__attribute__ ((visibility ("default"))) double PyFloat_GetMin(void);
__attribute__ ((visibility ("default"))) PyObject* PyFloat_GetInfo(void);


__attribute__ ((visibility ("default"))) PyObject* PyFloat_FromString(PyObject*);


__attribute__ ((visibility ("default"))) PyObject* PyFloat_FromDouble(double);



__attribute__ ((visibility ("default"))) double PyFloat_AsDouble(PyObject*);



# 1 "/home/alexturner/include/python3.15/cpython/floatobject.h" 1




typedef struct {
    PyObject ob_base;
    double ob_fval;
} PyFloatObject;






static inline double PyFloat_AS_DOUBLE(PyObject *op) {
    return (
# 16 "/home/alexturner/include/python3.15/cpython/floatobject.h" 3 4
          ((void) (0))
# 16 "/home/alexturner/include/python3.15/cpython/floatobject.h"
          , ((PyFloatObject*)(op)))->ob_fval;
}



__attribute__ ((visibility ("default"))) int PyFloat_Pack2(double x, char *p, int le);
__attribute__ ((visibility ("default"))) int PyFloat_Pack4(double x, char *p, int le);
__attribute__ ((visibility ("default"))) int PyFloat_Pack8(double x, char *p, int le);

__attribute__ ((visibility ("default"))) double PyFloat_Unpack2(const char *p, int le);
__attribute__ ((visibility ("default"))) double PyFloat_Unpack4(const char *p, int le);
__attribute__ ((visibility ("default"))) double PyFloat_Unpack8(const char *p, int le);
# 48 "/home/alexturner/include/python3.15/floatobject.h" 2
# 97 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/complexobject.h" 1
# 11 "/home/alexturner/include/python3.15/complexobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyComplex_Type;




__attribute__ ((visibility ("default"))) PyObject * PyComplex_FromDoubles(double real, double imag);

__attribute__ ((visibility ("default"))) double PyComplex_RealAsDouble(PyObject *op);
__attribute__ ((visibility ("default"))) double PyComplex_ImagAsDouble(PyObject *op);



# 1 "/home/alexturner/include/python3.15/cpython/complexobject.h" 1




typedef struct {
    double real;
    double imag;
} Py_complex;



__attribute__ ((visibility ("default"))) Py_complex _Py_c_sum(Py_complex, Py_complex);
__attribute__ ((visibility ("default"))) Py_complex _Py_c_diff(Py_complex, Py_complex);
__attribute__ ((visibility ("default"))) Py_complex _Py_c_neg(Py_complex);
__attribute__ ((visibility ("default"))) Py_complex _Py_c_prod(Py_complex, Py_complex);
__attribute__ ((visibility ("default"))) Py_complex _Py_c_quot(Py_complex, Py_complex);
__attribute__ ((visibility ("default"))) Py_complex _Py_c_pow(Py_complex, Py_complex);
__attribute__ ((visibility ("default"))) double _Py_c_abs(Py_complex);
# 27 "/home/alexturner/include/python3.15/cpython/complexobject.h"
typedef struct {
    PyObject ob_base;
    Py_complex cval;
} PyComplexObject;

__attribute__ ((visibility ("default"))) PyObject * PyComplex_FromCComplex(Py_complex);

__attribute__ ((visibility ("default"))) Py_complex PyComplex_AsCComplex(PyObject *op);
# 24 "/home/alexturner/include/python3.15/complexobject.h" 2
# 98 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/rangeobject.h" 1
# 18 "/home/alexturner/include/python3.15/rangeobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyRange_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyRangeIter_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyLongRangeIter_Type;
# 99 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/memoryobject.h" 1
# 9 "/home/alexturner/include/python3.15/memoryobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyMemoryView_Type;



__attribute__ ((visibility ("default"))) PyObject * PyMemoryView_FromObject(PyObject *base);

__attribute__ ((visibility ("default"))) PyObject * PyMemoryView_FromMemory(char *mem, Py_ssize_t size,
                                               int flags);


__attribute__ ((visibility ("default"))) PyObject * PyMemoryView_FromBuffer(const Py_buffer *info);

__attribute__ ((visibility ("default"))) PyObject * PyMemoryView_GetContiguous(PyObject *base,
                                                  int buffertype,
                                                  char order);



# 1 "/home/alexturner/include/python3.15/cpython/memoryobject.h" 1
# 11 "/home/alexturner/include/python3.15/cpython/memoryobject.h"
typedef struct {
    PyObject ob_base;
    int flags;
    Py_ssize_t exports;
    Py_buffer master;
} _PyManagedBufferObject;
# 27 "/home/alexturner/include/python3.15/cpython/memoryobject.h"
typedef struct {
    PyVarObject ob_base;
    _PyManagedBufferObject *mbuf;
    Py_hash_t hash;
    int flags;
    Py_ssize_t exports;
    Py_buffer view;
    PyObject *weakreflist;
    Py_ssize_t ob_array[1];
} PyMemoryViewObject;




static inline Py_buffer* PyMemoryView_GET_BUFFER(PyObject *op) {
    return (&((PyMemoryViewObject*)(op))->view);
}



static inline PyObject* PyMemoryView_GET_BASE(PyObject *op) {
    return ((PyMemoryViewObject*)(op))->view.obj;
}
# 28 "/home/alexturner/include/python3.15/memoryobject.h" 2
# 100 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/tupleobject.h" 1
# 23 "/home/alexturner/include/python3.15/tupleobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyTuple_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyTupleIter_Type;





__attribute__ ((visibility ("default"))) PyObject * PyTuple_New(Py_ssize_t size);
__attribute__ ((visibility ("default"))) Py_ssize_t PyTuple_Size(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyTuple_GetItem(PyObject *, Py_ssize_t);
__attribute__ ((visibility ("default"))) int PyTuple_SetItem(PyObject *, Py_ssize_t, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyTuple_GetSlice(PyObject *, Py_ssize_t, Py_ssize_t);
__attribute__ ((visibility ("default"))) PyObject * PyTuple_Pack(Py_ssize_t, ...);



# 1 "/home/alexturner/include/python3.15/cpython/tupleobject.h" 1




typedef struct {
    PyVarObject ob_base;

    Py_hash_t ob_hash;



    PyObject *ob_item[1];
} PyTupleObject;

__attribute__ ((visibility ("default"))) int _PyTuple_Resize(PyObject **, Py_ssize_t);







static inline Py_ssize_t PyTuple_GET_SIZE(PyObject *op) {
    PyTupleObject *tuple = (
# 24 "/home/alexturner/include/python3.15/cpython/tupleobject.h" 3 4
                          ((void) (0))
# 24 "/home/alexturner/include/python3.15/cpython/tupleobject.h"
                          , ((PyTupleObject*)((op))));
    return _Py_SIZE_impl(((PyObject*)((tuple))));
}





static inline void
PyTuple_SET_ITEM(PyObject *op, Py_ssize_t index, PyObject *value) {
    PyTupleObject *tuple = (
# 34 "/home/alexturner/include/python3.15/cpython/tupleobject.h" 3 4
                          ((void) (0))
# 34 "/home/alexturner/include/python3.15/cpython/tupleobject.h"
                          , ((PyTupleObject*)((op))));
    
# 35 "/home/alexturner/include/python3.15/cpython/tupleobject.h" 3 4
   ((void) (0))
# 35 "/home/alexturner/include/python3.15/cpython/tupleobject.h"
                     ;
    
# 36 "/home/alexturner/include/python3.15/cpython/tupleobject.h" 3 4
   ((void) (0))
# 36 "/home/alexturner/include/python3.15/cpython/tupleobject.h"
                                 ;
    tuple->ob_item[index] = value;
}



__attribute__ ((visibility ("default"))) PyObject* PyTuple_FromArray(
    PyObject *const *array,
    Py_ssize_t size);
# 40 "/home/alexturner/include/python3.15/tupleobject.h" 2
# 101 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/listobject.h" 1
# 20 "/home/alexturner/include/python3.15/listobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyList_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyListIter_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyListRevIter_Type;





__attribute__ ((visibility ("default"))) PyObject * PyList_New(Py_ssize_t size);
__attribute__ ((visibility ("default"))) Py_ssize_t PyList_Size(PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyList_GetItem(PyObject *, Py_ssize_t);

__attribute__ ((visibility ("default"))) PyObject * PyList_GetItemRef(PyObject *, Py_ssize_t);

__attribute__ ((visibility ("default"))) int PyList_SetItem(PyObject *, Py_ssize_t, PyObject *);
__attribute__ ((visibility ("default"))) int PyList_Insert(PyObject *, Py_ssize_t, PyObject *);
__attribute__ ((visibility ("default"))) int PyList_Append(PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyList_GetSlice(PyObject *, Py_ssize_t, Py_ssize_t);
__attribute__ ((visibility ("default"))) int PyList_SetSlice(PyObject *, Py_ssize_t, Py_ssize_t, PyObject *);

__attribute__ ((visibility ("default"))) int PyList_Sort(PyObject *);
__attribute__ ((visibility ("default"))) int PyList_Reverse(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyList_AsTuple(PyObject *);



# 1 "/home/alexturner/include/python3.15/cpython/listobject.h" 1




typedef struct {
    PyVarObject ob_base;

    PyObject **ob_item;
# 21 "/home/alexturner/include/python3.15/cpython/listobject.h"
    Py_ssize_t allocated;
} PyListObject;







static inline Py_ssize_t PyList_GET_SIZE(PyObject *op) {
    PyListObject *list = (
# 31 "/home/alexturner/include/python3.15/cpython/listobject.h" 3 4
                        ((void) (0))
# 31 "/home/alexturner/include/python3.15/cpython/listobject.h"
                        , ((PyListObject*)((op))));



    return _Py_SIZE_impl(((PyObject*)((list))));

}




static inline void
PyList_SET_ITEM(PyObject *op, Py_ssize_t index, PyObject *value) {
    PyListObject *list = (
# 44 "/home/alexturner/include/python3.15/cpython/listobject.h" 3 4
                        ((void) (0))
# 44 "/home/alexturner/include/python3.15/cpython/listobject.h"
                        , ((PyListObject*)((op))));
    
# 45 "/home/alexturner/include/python3.15/cpython/listobject.h" 3 4
   ((void) (0))
# 45 "/home/alexturner/include/python3.15/cpython/listobject.h"
                     ;
    
# 46 "/home/alexturner/include/python3.15/cpython/listobject.h" 3 4
   ((void) (0))
# 46 "/home/alexturner/include/python3.15/cpython/listobject.h"
                                  ;
    list->ob_item[index] = value;
}



__attribute__ ((visibility ("default"))) int PyList_Extend(PyObject *self, PyObject *iterable);
__attribute__ ((visibility ("default"))) int PyList_Clear(PyObject *self);
# 49 "/home/alexturner/include/python3.15/listobject.h" 2
# 102 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/dictobject.h" 1
# 15 "/home/alexturner/include/python3.15/dictobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDict_Type;





__attribute__ ((visibility ("default"))) PyObject * PyDict_New(void);
__attribute__ ((visibility ("default"))) PyObject * PyDict_GetItem(PyObject *mp, PyObject *key);
__attribute__ ((visibility ("default"))) PyObject * PyDict_GetItemWithError(PyObject *mp, PyObject *key);
__attribute__ ((visibility ("default"))) int PyDict_SetItem(PyObject *mp, PyObject *key, PyObject *item);
__attribute__ ((visibility ("default"))) int PyDict_DelItem(PyObject *mp, PyObject *key);
__attribute__ ((visibility ("default"))) void PyDict_Clear(PyObject *mp);
__attribute__ ((visibility ("default"))) int PyDict_Next(
    PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value);
__attribute__ ((visibility ("default"))) PyObject * PyDict_Keys(PyObject *mp);
__attribute__ ((visibility ("default"))) PyObject * PyDict_Values(PyObject *mp);
__attribute__ ((visibility ("default"))) PyObject * PyDict_Items(PyObject *mp);
__attribute__ ((visibility ("default"))) Py_ssize_t PyDict_Size(PyObject *mp);
__attribute__ ((visibility ("default"))) PyObject * PyDict_Copy(PyObject *mp);
__attribute__ ((visibility ("default"))) int PyDict_Contains(PyObject *mp, PyObject *key);


__attribute__ ((visibility ("default"))) int PyDict_Update(PyObject *mp, PyObject *other);






__attribute__ ((visibility ("default"))) int PyDict_Merge(PyObject *mp,
                             PyObject *other,
                             int override);






__attribute__ ((visibility ("default"))) int PyDict_MergeFromSeq2(PyObject *d,
                                     PyObject *seq2,
                                     int override);

__attribute__ ((visibility ("default"))) PyObject * PyDict_GetItemString(PyObject *dp, const char *key);
__attribute__ ((visibility ("default"))) int PyDict_SetItemString(PyObject *dp, const char *key, PyObject *item);
__attribute__ ((visibility ("default"))) int PyDict_DelItemString(PyObject *dp, const char *key);







__attribute__ ((visibility ("default"))) int PyDict_GetItemRef(PyObject *mp, PyObject *key, PyObject **result);
__attribute__ ((visibility ("default"))) int PyDict_GetItemStringRef(PyObject *mp, const char *key, PyObject **result);
# 80 "/home/alexturner/include/python3.15/dictobject.h"
__attribute__ ((visibility ("default"))) int PyDict_SetDefaultRef(PyObject *mp, PyObject *key, PyObject *default_value, PyObject **result);



__attribute__ ((visibility ("default"))) PyObject * PyObject_GenericGetDict(PyObject *, void *);




extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictKeys_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictValues_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictItems_Type;
# 102 "/home/alexturner/include/python3.15/dictobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictIterKey_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictIterValue_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictIterItem_Type;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictRevIterKey_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictRevIterItem_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictRevIterValue_Type;




# 1 "/home/alexturner/include/python3.15/cpython/dictobject.h" 1




typedef struct _dictkeysobject PyDictKeysObject;
typedef struct _dictvalues PyDictValues;




typedef struct {
    PyObject ob_base;


    Py_ssize_t ma_used;







    uint64_t _ma_watcher_tag;

    PyDictKeysObject *ma_keys;






    PyDictValues *ma_values;
} PyDictObject;

__attribute__ ((visibility ("default"))) PyObject * _PyDict_GetItem_KnownHash(PyObject *mp, PyObject *key,
                                                 Py_hash_t hash);

__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) PyObject * _PyDict_GetItemStringWithError(PyObject *, const char *);
__attribute__ ((visibility ("default"))) PyObject * PyDict_SetDefault(
    PyObject *mp, PyObject *key, PyObject *defaultobj);


static inline Py_ssize_t PyDict_GET_SIZE(PyObject *op) {
    PyDictObject *mp;
    
# 45 "/home/alexturner/include/python3.15/cpython/dictobject.h" 3 4
   ((void) (0))
# 45 "/home/alexturner/include/python3.15/cpython/dictobject.h"
                           ;
    mp = ((PyDictObject*)(op));



    return mp->ma_used;

}


__attribute__ ((visibility ("default"))) int PyDict_ContainsString(PyObject *mp, const char *key);

__attribute__ ((visibility ("default"))) PyObject * _PyDict_NewPresized(Py_ssize_t minused);

__attribute__ ((visibility ("default"))) int PyDict_Pop(PyObject *dict, PyObject *key, PyObject **result);
__attribute__ ((visibility ("default"))) int PyDict_PopString(PyObject *dict, const char *key, PyObject **result);


__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) PyObject * _PyDict_Pop(
    PyObject *dict,
    PyObject *key,
    PyObject *default_value);
# 78 "/home/alexturner/include/python3.15/cpython/dictobject.h"
typedef enum {

    PyDict_EVENT_ADDED, PyDict_EVENT_MODIFIED, PyDict_EVENT_DELETED, PyDict_EVENT_CLONED, PyDict_EVENT_CLEARED, PyDict_EVENT_DEALLOCATED,

} PyDict_WatchEvent;




typedef int(*PyDict_WatchCallback)(PyDict_WatchEvent event, PyObject* dict, PyObject* key, PyObject* new_value);


__attribute__ ((visibility ("default"))) int PyDict_AddWatcher(PyDict_WatchCallback callback);
__attribute__ ((visibility ("default"))) int PyDict_ClearWatcher(int watcher_id);


__attribute__ ((visibility ("default"))) int PyDict_Watch(int watcher_id, PyObject* dict);
__attribute__ ((visibility ("default"))) int PyDict_Unwatch(int watcher_id, PyObject* dict);
# 114 "/home/alexturner/include/python3.15/dictobject.h" 2
# 103 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/odictobject.h" 1
# 13 "/home/alexturner/include/python3.15/cpython/odictobject.h"
typedef struct _odictobject PyODictObject;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyODict_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyODictIter_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyODictKeys_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyODictItems_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyODictValues_Type;





__attribute__ ((visibility ("default"))) PyObject * PyODict_New(void);
__attribute__ ((visibility ("default"))) int PyODict_SetItem(PyObject *od, PyObject *key, PyObject *item);
__attribute__ ((visibility ("default"))) int PyODict_DelItem(PyObject *od, PyObject *key);
# 104 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/enumobject.h" 1
# 10 "/home/alexturner/include/python3.15/enumobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyEnum_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyReversed_Type;
# 105 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/setobject.h" 1
# 9 "/home/alexturner/include/python3.15/setobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PySet_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyFrozenSet_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PySetIter_Type;

__attribute__ ((visibility ("default"))) PyObject * PySet_New(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFrozenSet_New(PyObject *);

__attribute__ ((visibility ("default"))) int PySet_Add(PyObject *set, PyObject *key);
__attribute__ ((visibility ("default"))) int PySet_Clear(PyObject *set);
__attribute__ ((visibility ("default"))) int PySet_Contains(PyObject *anyset, PyObject *key);
__attribute__ ((visibility ("default"))) int PySet_Discard(PyObject *set, PyObject *key);
__attribute__ ((visibility ("default"))) PyObject * PySet_Pop(PyObject *set);
__attribute__ ((visibility ("default"))) Py_ssize_t PySet_Size(PyObject *anyset);
# 42 "/home/alexturner/include/python3.15/setobject.h"
# 1 "/home/alexturner/include/python3.15/cpython/setobject.h" 1
# 20 "/home/alexturner/include/python3.15/cpython/setobject.h"
typedef struct {
    PyObject *key;
    Py_hash_t hash;
} setentry;
# 36 "/home/alexturner/include/python3.15/cpython/setobject.h"
typedef struct {
    PyObject ob_base;

    Py_ssize_t fill;
    Py_ssize_t used;





    Py_ssize_t mask;






    setentry *table;
    Py_hash_t hash;
    Py_ssize_t finger;

    setentry smalltable[8];
    PyObject *weakreflist;
} PySetObject;




static inline Py_ssize_t PySet_GET_SIZE(PyObject *so) {



    return (
# 68 "/home/alexturner/include/python3.15/cpython/setobject.h" 3 4
          ((void) (0))
# 68 "/home/alexturner/include/python3.15/cpython/setobject.h"
          , ((PySetObject*)(so)))->used;

}
# 43 "/home/alexturner/include/python3.15/setobject.h" 2
# 106 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/methodobject.h" 1
# 14 "/home/alexturner/include/python3.15/methodobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyCFunction_Type;




typedef PyObject *(*PyCFunction)(PyObject *, PyObject *);
typedef PyObject *(*PyCFunctionFast) (PyObject *, PyObject *const *, Py_ssize_t);
typedef PyObject *(*PyCFunctionWithKeywords)(PyObject *, PyObject *,
                                             PyObject *);
typedef PyObject *(*PyCFunctionFastWithKeywords) (PyObject *,
                                                  PyObject *const *, Py_ssize_t,
                                                  PyObject *);
typedef PyObject *(*PyCMethod)(PyObject *, PyTypeObject *, PyObject *const *,
                               Py_ssize_t, PyObject *);





typedef PyCFunctionFast _PyCFunctionFast;
typedef PyCFunctionFastWithKeywords _PyCFunctionFastWithKeywords;
# 64 "/home/alexturner/include/python3.15/methodobject.h"
__attribute__ ((visibility ("default"))) PyCFunction PyCFunction_GetFunction(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyCFunction_GetSelf(PyObject *);
__attribute__ ((visibility ("default"))) int PyCFunction_GetFlags(PyObject *);

struct PyMethodDef {
    const char *ml_name;
    PyCFunction ml_meth;
    int ml_flags;

    const char *ml_doc;
};




__attribute__ ((visibility ("default"))) PyObject * PyCFunction_New(PyMethodDef *, PyObject *);



__attribute__ ((visibility ("default"))) PyObject * PyCFunction_NewEx(PyMethodDef *, PyObject *,
                                         PyObject *);



__attribute__ ((visibility ("default"))) PyObject * PyCMethod_New(PyMethodDef *, PyObject *,
                                     PyObject *, PyTypeObject *);
# 139 "/home/alexturner/include/python3.15/methodobject.h"
# 1 "/home/alexturner/include/python3.15/cpython/methodobject.h" 1






typedef struct {
    PyObject ob_base;
    PyMethodDef *m_ml;
    PyObject *m_self;
    PyObject *m_module;
    PyObject *m_weakreflist;
    vectorcallfunc vectorcall;
} PyCFunctionObject;
# 23 "/home/alexturner/include/python3.15/cpython/methodobject.h"
typedef struct {
    PyCFunctionObject func;
    PyTypeObject *mm_class;
} PyCMethodObject;





extern __attribute__ ((visibility ("default"))) PyTypeObject PyCMethod_Type;







static inline PyCFunction PyCFunction_GET_FUNCTION(PyObject *func) {
    return (
# 41 "/home/alexturner/include/python3.15/cpython/methodobject.h" 3 4
          ((void) (0))
# 41 "/home/alexturner/include/python3.15/cpython/methodobject.h"
          , ((PyCFunctionObject*)((func))))->m_ml->ml_meth;
}


static inline PyObject* PyCFunction_GET_SELF(PyObject *func_obj) {
    PyCFunctionObject *func = (
# 46 "/home/alexturner/include/python3.15/cpython/methodobject.h" 3 4
                             ((void) (0))
# 46 "/home/alexturner/include/python3.15/cpython/methodobject.h"
                             , ((PyCFunctionObject*)((func_obj))));
    if (func->m_ml->ml_flags & 0x0020) {
        return 
# 48 "/home/alexturner/include/python3.15/cpython/methodobject.h" 3 4
              ((void *)0)
# 48 "/home/alexturner/include/python3.15/cpython/methodobject.h"
                      ;
    }
    return func->m_self;
}


static inline int PyCFunction_GET_FLAGS(PyObject *func) {
    return (
# 55 "/home/alexturner/include/python3.15/cpython/methodobject.h" 3 4
          ((void) (0))
# 55 "/home/alexturner/include/python3.15/cpython/methodobject.h"
          , ((PyCFunctionObject*)((func))))->m_ml->ml_flags;
}


static inline PyTypeObject* PyCFunction_GET_CLASS(PyObject *func_obj) {
    PyCFunctionObject *func = (
# 60 "/home/alexturner/include/python3.15/cpython/methodobject.h" 3 4
                             ((void) (0))
# 60 "/home/alexturner/include/python3.15/cpython/methodobject.h"
                             , ((PyCFunctionObject*)((func_obj))));
    if (func->m_ml->ml_flags & 0x0200) {
        return (
# 62 "/home/alexturner/include/python3.15/cpython/methodobject.h" 3 4
              ((void) (0))
# 62 "/home/alexturner/include/python3.15/cpython/methodobject.h"
              , ((PyCMethodObject*)((func))))->mm_class;
    }
    return 
# 64 "/home/alexturner/include/python3.15/cpython/methodobject.h" 3 4
          ((void *)0)
# 64 "/home/alexturner/include/python3.15/cpython/methodobject.h"
                  ;
}
# 140 "/home/alexturner/include/python3.15/methodobject.h" 2
# 107 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/moduleobject.h" 1
# 10 "/home/alexturner/include/python3.15/moduleobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyModule_Type;





__attribute__ ((visibility ("default"))) PyObject * PyModule_NewObject(
    PyObject *name
    );

__attribute__ ((visibility ("default"))) PyObject * PyModule_New(
    const char *name
    );
__attribute__ ((visibility ("default"))) PyObject * PyModule_GetDict(PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyModule_GetNameObject(PyObject *);

__attribute__ ((visibility ("default"))) const char * PyModule_GetName(PyObject *);
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) const char * PyModule_GetFilename(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyModule_GetFilenameObject(PyObject *);
__attribute__ ((visibility ("default"))) PyModuleDef* PyModule_GetDef(PyObject*);
__attribute__ ((visibility ("default"))) void* PyModule_GetState(PyObject*);



__attribute__ ((visibility ("default"))) PyObject * PyModuleDef_Init(PyModuleDef*);
extern __attribute__ ((visibility ("default"))) PyTypeObject PyModuleDef_Type;



typedef struct PyModuleDef_Base {
  PyObject ob_base;






  PyObject* (*m_init)(void);




  Py_ssize_t m_index;




  PyObject* m_copy;
} PyModuleDef_Base;
# 71 "/home/alexturner/include/python3.15/moduleobject.h"
struct PyModuleDef_Slot {
    int slot;
    void *value;
};
# 121 "/home/alexturner/include/python3.15/moduleobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyModule_FromSlotsAndSpec(const PyModuleDef_Slot *,
                                                 PyObject *spec);
__attribute__ ((visibility ("default"))) int PyModule_Exec(PyObject *mod);
__attribute__ ((visibility ("default"))) int PyModule_GetStateSize(PyObject *mod, Py_ssize_t *result);
__attribute__ ((visibility ("default"))) int PyModule_GetToken(PyObject *, void **result);



struct PyModuleDef {
  PyModuleDef_Base m_base;
  const char* m_name;
  const char* m_doc;
  Py_ssize_t m_size;
  PyMethodDef *m_methods;
  PyModuleDef_Slot *m_slots;
  traverseproc m_traverse;
  inquiry m_clear;
  freefunc m_free;
};
# 108 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/monitoring.h" 1
# 45 "/home/alexturner/include/python3.15/cpython/monitoring.h"
typedef struct _PyMonitoringState {
    uint8_t active;
    uint8_t opaque;
} PyMonitoringState;


__attribute__ ((visibility ("default"))) int
PyMonitoring_EnterScope(PyMonitoringState *state_array, uint64_t *version,
                         const uint8_t *event_types, Py_ssize_t length);

__attribute__ ((visibility ("default"))) int
PyMonitoring_ExitScope(void);


__attribute__ ((visibility ("default"))) int
_PyMonitoring_FirePyStartEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FirePyResumeEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FirePyReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                                PyObject *retval);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FirePyYieldEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                               PyObject *retval);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireCallEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                            PyObject* callable, PyObject *arg0);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireLineEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                            int lineno);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireJumpEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                            PyObject *target_offset);

__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int
_PyMonitoring_FireBranchEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *target_offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireBranchRightEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *target_offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireBranchLeftEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *target_offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireCReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                               PyObject *retval);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FirePyThrowEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireReraiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireExceptionHandledEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireCRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FirePyUnwindEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset);

__attribute__ ((visibility ("default"))) int
_PyMonitoring_FireStopIterationEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset, PyObject *value);
# 131 "/home/alexturner/include/python3.15/cpython/monitoring.h"
static inline int
PyMonitoring_FirePyStartEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyStartEvent(state, codelike, offset)); } else { return 0; }

                                                                ;
}

static inline int
PyMonitoring_FirePyResumeEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyResumeEvent(state, codelike, offset)); } else { return 0; }

                                                                 ;
}

static inline int
PyMonitoring_FirePyReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                               PyObject *retval)
{
    if ((state)->active) { return (_PyMonitoring_FirePyReturnEvent(state, codelike, offset, retval)); } else { return 0; }

                                                                         ;
}

static inline int
PyMonitoring_FirePyYieldEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *retval)
{
    if ((state)->active) { return (_PyMonitoring_FirePyYieldEvent(state, codelike, offset, retval)); } else { return 0; }

                                                                        ;
}

static inline int
PyMonitoring_FireCallEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                           PyObject* callable, PyObject *arg0)
{
    if ((state)->active) { return (_PyMonitoring_FireCallEvent(state, codelike, offset, callable, arg0)); } else { return 0; }

                                                                             ;
}

static inline int
PyMonitoring_FireLineEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                           int lineno)
{
    if ((state)->active) { return (_PyMonitoring_FireLineEvent(state, codelike, offset, lineno)); } else { return 0; }

                                                                     ;
}

static inline int
PyMonitoring_FireJumpEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                           PyObject *target_offset)
{
    if ((state)->active) { return (_PyMonitoring_FireJumpEvent(state, codelike, offset, target_offset)); } else { return 0; }

                                                                            ;
}

static inline int
PyMonitoring_FireBranchRightEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                             PyObject *target_offset)
{
    if ((state)->active) { return (_PyMonitoring_FireBranchRightEvent(state, codelike, offset, target_offset)); } else { return 0; }

                                                                                   ;
}

static inline int
PyMonitoring_FireBranchLeftEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                             PyObject *target_offset)
{
    if ((state)->active) { return (_PyMonitoring_FireBranchLeftEvent(state, codelike, offset, target_offset)); } else { return 0; }

                                                                                  ;
}

static inline int
PyMonitoring_FireCReturnEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset,
                              PyObject *retval)
{
    if ((state)->active) { return (_PyMonitoring_FireCReturnEvent(state, codelike, offset, retval)); } else { return 0; }

                                                                        ;
}

static inline int
PyMonitoring_FirePyThrowEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyThrowEvent(state, codelike, offset)); } else { return 0; }

                                                                ;
}

static inline int
PyMonitoring_FireRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireRaiseEvent(state, codelike, offset)); } else { return 0; }

                                                              ;
}

static inline int
PyMonitoring_FireReraiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireReraiseEvent(state, codelike, offset)); } else { return 0; }

                                                                ;
}

static inline int
PyMonitoring_FireExceptionHandledEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireExceptionHandledEvent(state, codelike, offset)); } else { return 0; }

                                                                         ;
}

static inline int
PyMonitoring_FireCRaiseEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FireCRaiseEvent(state, codelike, offset)); } else { return 0; }

                                                               ;
}

static inline int
PyMonitoring_FirePyUnwindEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset)
{
    if ((state)->active) { return (_PyMonitoring_FirePyUnwindEvent(state, codelike, offset)); } else { return 0; }

                                                                 ;
}

static inline int
PyMonitoring_FireStopIterationEvent(PyMonitoringState *state, PyObject *codelike, int32_t offset, PyObject *value)
{
    if ((state)->active) { return (_PyMonitoring_FireStopIterationEvent(state, codelike, offset, value)); } else { return 0; }

                                                                             ;
}
# 109 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/funcobject.h" 1
# 21 "/home/alexturner/include/python3.15/cpython/funcobject.h"
typedef struct {
    PyObject *fc_globals; PyObject *fc_builtins; PyObject *fc_name; PyObject *fc_qualname; PyObject *fc_code; PyObject *fc_defaults; PyObject *fc_kwdefaults; PyObject *fc_closure;
} PyFrameConstructor;
# 36 "/home/alexturner/include/python3.15/cpython/funcobject.h"
typedef struct {
    PyObject ob_base;
    PyObject *func_globals; PyObject *func_builtins; PyObject *func_name; PyObject *func_qualname; PyObject *func_code; PyObject *func_defaults; PyObject *func_kwdefaults; PyObject *func_closure;
    PyObject *func_doc;
    PyObject *func_dict;
    PyObject *func_weakreflist;
    PyObject *func_module;
    PyObject *func_annotations;
    PyObject *func_annotate;
    PyObject *func_typeparams;
    vectorcallfunc vectorcall;
# 55 "/home/alexturner/include/python3.15/cpython/funcobject.h"
    uint32_t func_version;






} PyFunctionObject;



extern __attribute__ ((visibility ("default"))) PyTypeObject PyFunction_Type;



__attribute__ ((visibility ("default"))) PyObject * PyFunction_New(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_NewWithQualName(PyObject *, PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_GetCode(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_GetGlobals(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_GetModule(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_GetDefaults(PyObject *);
__attribute__ ((visibility ("default"))) int PyFunction_SetDefaults(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) void PyFunction_SetVectorcall(PyFunctionObject *, vectorcallfunc);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_GetKwDefaults(PyObject *);
__attribute__ ((visibility ("default"))) int PyFunction_SetKwDefaults(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_GetClosure(PyObject *);
__attribute__ ((visibility ("default"))) int PyFunction_SetClosure(PyObject *, PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyFunction_GetAnnotations(PyObject *);
__attribute__ ((visibility ("default"))) int PyFunction_SetAnnotations(PyObject *, PyObject *);






static inline PyObject* PyFunction_GET_CODE(PyObject *func) {
    return (
# 91 "/home/alexturner/include/python3.15/cpython/funcobject.h" 3 4
          ((void) (0))
# 91 "/home/alexturner/include/python3.15/cpython/funcobject.h"
          , ((PyFunctionObject*)(func)))->func_code;
}


static inline PyObject* PyFunction_GET_GLOBALS(PyObject *func) {
    return (
# 96 "/home/alexturner/include/python3.15/cpython/funcobject.h" 3 4
          ((void) (0))
# 96 "/home/alexturner/include/python3.15/cpython/funcobject.h"
          , ((PyFunctionObject*)(func)))->func_globals;
}


static inline PyObject* PyFunction_GET_MODULE(PyObject *func) {
    return (
# 101 "/home/alexturner/include/python3.15/cpython/funcobject.h" 3 4
          ((void) (0))
# 101 "/home/alexturner/include/python3.15/cpython/funcobject.h"
          , ((PyFunctionObject*)(func)))->func_module;
}


static inline PyObject* PyFunction_GET_DEFAULTS(PyObject *func) {
    return (
# 106 "/home/alexturner/include/python3.15/cpython/funcobject.h" 3 4
          ((void) (0))
# 106 "/home/alexturner/include/python3.15/cpython/funcobject.h"
          , ((PyFunctionObject*)(func)))->func_defaults;
}


static inline PyObject* PyFunction_GET_KW_DEFAULTS(PyObject *func) {
    return (
# 111 "/home/alexturner/include/python3.15/cpython/funcobject.h" 3 4
          ((void) (0))
# 111 "/home/alexturner/include/python3.15/cpython/funcobject.h"
          , ((PyFunctionObject*)(func)))->func_kwdefaults;
}


static inline PyObject* PyFunction_GET_CLOSURE(PyObject *func) {
    return (
# 116 "/home/alexturner/include/python3.15/cpython/funcobject.h" 3 4
          ((void) (0))
# 116 "/home/alexturner/include/python3.15/cpython/funcobject.h"
          , ((PyFunctionObject*)(func)))->func_closure;
}


static inline PyObject* PyFunction_GET_ANNOTATIONS(PyObject *func) {
    return (
# 121 "/home/alexturner/include/python3.15/cpython/funcobject.h" 3 4
          ((void) (0))
# 121 "/home/alexturner/include/python3.15/cpython/funcobject.h"
          , ((PyFunctionObject*)(func)))->func_annotations;
}



extern __attribute__ ((visibility ("default"))) PyTypeObject PyClassMethod_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyStaticMethod_Type;

__attribute__ ((visibility ("default"))) PyObject * PyClassMethod_New(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyStaticMethod_New(PyObject *);
# 140 "/home/alexturner/include/python3.15/cpython/funcobject.h"
typedef enum {

    PyFunction_EVENT_CREATE, PyFunction_EVENT_DESTROY, PyFunction_EVENT_MODIFY_CODE, PyFunction_EVENT_MODIFY_DEFAULTS, PyFunction_EVENT_MODIFY_KWDEFAULTS, PyFunction_EVENT_MODIFY_QUALNAME,

} PyFunction_WatchEvent;
# 161 "/home/alexturner/include/python3.15/cpython/funcobject.h"
typedef int (*PyFunction_WatchCallback)(
  PyFunction_WatchEvent event,
  PyFunctionObject *func,
  PyObject *new_value);
# 173 "/home/alexturner/include/python3.15/cpython/funcobject.h"
__attribute__ ((visibility ("default"))) int PyFunction_AddWatcher(PyFunction_WatchCallback callback);






__attribute__ ((visibility ("default"))) int PyFunction_ClearWatcher(int watcher_id);
# 110 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/classobject.h" 1
# 12 "/home/alexturner/include/python3.15/cpython/classobject.h"
typedef struct {
    PyObject ob_base;
    PyObject *im_func;
    PyObject *im_self;
    PyObject *im_weakreflist;
    vectorcallfunc vectorcall;
} PyMethodObject;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyMethod_Type;



__attribute__ ((visibility ("default"))) PyObject * PyMethod_New(PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyMethod_Function(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyMethod_Self(PyObject *);






static inline PyObject* PyMethod_GET_FUNCTION(PyObject *meth) {
    return (
# 35 "/home/alexturner/include/python3.15/cpython/classobject.h" 3 4
          ((void) (0))
# 35 "/home/alexturner/include/python3.15/cpython/classobject.h"
          , ((PyMethodObject*)(meth)))->im_func;
}


static inline PyObject* PyMethod_GET_SELF(PyObject *meth) {
    return (
# 40 "/home/alexturner/include/python3.15/cpython/classobject.h" 3 4
          ((void) (0))
# 40 "/home/alexturner/include/python3.15/cpython/classobject.h"
          , ((PyMethodObject*)(meth)))->im_self;
}


typedef struct {
    PyObject ob_base;
    PyObject *func;
} PyInstanceMethodObject;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyInstanceMethod_Type;



__attribute__ ((visibility ("default"))) PyObject * PyInstanceMethod_New(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyInstanceMethod_Function(PyObject *);







static inline PyObject* PyInstanceMethod_GET_FUNCTION(PyObject *meth) {
    return (
# 63 "/home/alexturner/include/python3.15/cpython/classobject.h" 3 4
          ((void) (0))
# 63 "/home/alexturner/include/python3.15/cpython/classobject.h"
          , ((PyInstanceMethodObject*)(meth)))->func;
}
# 111 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/fileobject.h" 1
# 11 "/home/alexturner/include/python3.15/fileobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyFile_FromFd(int, const char *, const char *, int,
                                     const char *, const char *,
                                     const char *, int);
__attribute__ ((visibility ("default"))) PyObject * PyFile_GetLine(PyObject *, int);
__attribute__ ((visibility ("default"))) int PyFile_WriteObject(PyObject *, PyObject *, int);
__attribute__ ((visibility ("default"))) int PyFile_WriteString(const char *, PyObject *);
__attribute__ ((visibility ("default"))) int PyObject_AsFileDescriptor(PyObject *);




__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) const char * Py_FileSystemDefaultEncoding;

__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) const char * Py_FileSystemDefaultEncodeErrors;

__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_HasFileSystemDefaultEncoding;


__attribute__((__deprecated__)) extern __attribute__ ((visibility ("default"))) int Py_UTF8Mode;




# 1 "/home/alexturner/include/python3.15/cpython/fileobject.h" 1




__attribute__ ((visibility ("default"))) char * Py_UniversalNewlineFgets(char *, int, FILE*, PyObject *);



__attribute__ ((visibility ("default"))) PyObject * PyFile_NewStdPrinter(int);
extern __attribute__ ((visibility ("default"))) PyTypeObject PyStdPrinter_Type;

typedef PyObject * (*Py_OpenCodeHookFunction)(PyObject *, void *);

__attribute__ ((visibility ("default"))) PyObject * PyFile_OpenCode(const char *utf8path);
__attribute__ ((visibility ("default"))) PyObject * PyFile_OpenCodeObject(PyObject *path);
__attribute__ ((visibility ("default"))) int PyFile_SetOpenCodeHook(Py_OpenCodeHookFunction hook, void *userData);
# 35 "/home/alexturner/include/python3.15/fileobject.h" 2
# 112 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pycapsule.h" 1
# 21 "/home/alexturner/include/python3.15/pycapsule.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyCapsule_Type;

typedef void (*PyCapsule_Destructor)(PyObject *);




__attribute__ ((visibility ("default"))) PyObject * PyCapsule_New(
    void *pointer,
    const char *name,
    PyCapsule_Destructor destructor);

__attribute__ ((visibility ("default"))) void * PyCapsule_GetPointer(PyObject *capsule, const char *name);

__attribute__ ((visibility ("default"))) PyCapsule_Destructor PyCapsule_GetDestructor(PyObject *capsule);

__attribute__ ((visibility ("default"))) const char * PyCapsule_GetName(PyObject *capsule);

__attribute__ ((visibility ("default"))) void * PyCapsule_GetContext(PyObject *capsule);

__attribute__ ((visibility ("default"))) int PyCapsule_IsValid(PyObject *capsule, const char *name);

__attribute__ ((visibility ("default"))) int PyCapsule_SetPointer(PyObject *capsule, void *pointer);

__attribute__ ((visibility ("default"))) int PyCapsule_SetDestructor(PyObject *capsule, PyCapsule_Destructor destructor);

__attribute__ ((visibility ("default"))) int PyCapsule_SetName(PyObject *capsule, const char *name);

__attribute__ ((visibility ("default"))) int PyCapsule_SetContext(PyObject *capsule, void *context);

__attribute__ ((visibility ("default"))) void * PyCapsule_Import(
    const char *name,
    int no_block);
# 113 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/code.h" 1
# 11 "/home/alexturner/include/python3.15/cpython/code.h"
typedef struct {
    PyObject *_co_code;
    PyObject *_co_varnames;
    PyObject *_co_cellvars;
    PyObject *_co_freevars;
} _PyCoCached;

typedef struct {
    int size;
    int capacity;
    struct _PyExecutorObject *executors[1];
} _PyExecutorArray;
# 115 "/home/alexturner/include/python3.15/cpython/code.h"
struct PyCodeObject { PyVarObject ob_base; PyObject *co_consts; PyObject *co_names; PyObject *co_exceptiontable; int co_flags; int co_argcount; int co_posonlyargcount; int co_kwonlyargcount; int co_stacksize; int co_firstlineno; int co_nlocalsplus; int co_framesize; int co_nlocals; int co_ncellvars; int co_nfreevars; uint32_t co_version; PyObject *co_localsplusnames; PyObject *co_localspluskinds; PyObject *co_filename; PyObject *co_name; PyObject *co_qualname; PyObject *co_linetable; PyObject *co_weakreflist; _PyExecutorArray *co_executors; _PyCoCached *_co_cached; uintptr_t _co_instrumentation_version; struct _PyCoMonitoringData *_co_monitoring; Py_ssize_t _co_unique_id; int _co_firsttraceable; void *co_extra; char co_code_adaptive[(1)]; };
# 162 "/home/alexturner/include/python3.15/cpython/code.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyCode_Type;



static inline Py_ssize_t PyCode_GetNumFree(PyCodeObject *op) {
    
# 167 "/home/alexturner/include/python3.15/cpython/code.h" 3 4
   ((void) (0))
# 167 "/home/alexturner/include/python3.15/cpython/code.h"
                           ;
    return op->co_nfreevars;
}

static inline int PyUnstable_Code_GetFirstFree(PyCodeObject *op) {
    
# 172 "/home/alexturner/include/python3.15/cpython/code.h" 3 4
   ((void) (0))
# 172 "/home/alexturner/include/python3.15/cpython/code.h"
                           ;
    return op->co_nlocalsplus - op->co_nfreevars;
}

__attribute__((__deprecated__)) static inline int PyCode_GetFirstFree(PyCodeObject *op) {
    return PyUnstable_Code_GetFirstFree(op);
}


__attribute__ ((visibility ("default"))) PyCodeObject * PyUnstable_Code_New(
        int, int, int, int, int, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, int, PyObject *,
        PyObject *);

__attribute__ ((visibility ("default"))) PyCodeObject * PyUnstable_Code_NewWithPosOnlyArgs(
        int, int, int, int, int, int, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, PyObject *,
        PyObject *, PyObject *, PyObject *, int, PyObject *,
        PyObject *);


__attribute__((__deprecated__)) static inline PyCodeObject *
PyCode_New(
        int a, int b, int c, int d, int e, PyObject *f, PyObject *g,
        PyObject *h, PyObject *i, PyObject *j, PyObject *k,
        PyObject *l, PyObject *m, PyObject *n, int o, PyObject *p,
        PyObject *q)
{
    return PyUnstable_Code_New(
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q);
}
__attribute__((__deprecated__)) static inline PyCodeObject *
PyCode_NewWithPosOnlyArgs(
        int a, int poac, int b, int c, int d, int e, PyObject *f, PyObject *g,
        PyObject *h, PyObject *i, PyObject *j, PyObject *k,
        PyObject *l, PyObject *m, PyObject *n, int o, PyObject *p,
        PyObject *q)
{
    return PyUnstable_Code_NewWithPosOnlyArgs(
        a, poac, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q);
}


__attribute__ ((visibility ("default"))) PyCodeObject *
PyCode_NewEmpty(const char *filename, const char *funcname, int firstlineno);




__attribute__ ((visibility ("default"))) int PyCode_Addr2Line(PyCodeObject *, int);

__attribute__ ((visibility ("default"))) int PyCode_Addr2Location(PyCodeObject *, int, int *, int *, int *, int *);





typedef enum {

    PY_CODE_EVENT_CREATE, PY_CODE_EVENT_DESTROY,

} PyCodeEvent;
# 246 "/home/alexturner/include/python3.15/cpython/code.h"
typedef int (*PyCode_WatchCallback)(
  PyCodeEvent event,
  PyCodeObject* co);
# 257 "/home/alexturner/include/python3.15/cpython/code.h"
__attribute__ ((visibility ("default"))) int PyCode_AddWatcher(PyCode_WatchCallback callback);






__attribute__ ((visibility ("default"))) int PyCode_ClearWatcher(int watcher_id);


struct _opaque {
    int computed_line;
    const uint8_t *lo_next;
    const uint8_t *limit;
};

typedef struct _line_offsets {
    int ar_start;
    int ar_end;
    int ar_line;
    struct _opaque opaque;
} PyCodeAddressRange;




__attribute__ ((visibility ("default"))) int _PyCode_CheckLineNumber(int lasti, PyCodeAddressRange *bounds);

__attribute__ ((visibility ("default"))) PyObject* PyCode_Optimize(PyObject *code, PyObject* consts,
                                      PyObject *names, PyObject *lnotab);

__attribute__ ((visibility ("default"))) int PyUnstable_Code_GetExtra(
    PyObject *code, Py_ssize_t index, void **extra);
__attribute__ ((visibility ("default"))) int PyUnstable_Code_SetExtra(
    PyObject *code, Py_ssize_t index, void *extra);

__attribute__((__deprecated__)) static inline int
_PyCode_GetExtra(PyObject *code, Py_ssize_t index, void **extra)
{
    return PyUnstable_Code_GetExtra(code, index, extra);
}
__attribute__((__deprecated__)) static inline int
_PyCode_SetExtra(PyObject *code, Py_ssize_t index, void *extra)
{
    return PyUnstable_Code_SetExtra(code, index, extra);
}



__attribute__ ((visibility ("default"))) PyObject * PyCode_GetCode(PyCodeObject *code);

__attribute__ ((visibility ("default"))) PyObject * PyCode_GetVarnames(PyCodeObject *code);

__attribute__ ((visibility ("default"))) PyObject * PyCode_GetCellvars(PyCodeObject *code);

__attribute__ ((visibility ("default"))) PyObject * PyCode_GetFreevars(PyCodeObject *code);

typedef enum _PyCodeLocationInfoKind {

    PY_CODE_LOCATION_INFO_SHORT0 = 0,

    PY_CODE_LOCATION_INFO_ONE_LINE0 = 10,
    PY_CODE_LOCATION_INFO_ONE_LINE1 = 11,
    PY_CODE_LOCATION_INFO_ONE_LINE2 = 12,

    PY_CODE_LOCATION_INFO_NO_COLUMNS = 13,
    PY_CODE_LOCATION_INFO_LONG = 14,
    PY_CODE_LOCATION_INFO_NONE = 15
} _PyCodeLocationInfoKind;
# 114 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pyframe.h" 1
# 13 "/home/alexturner/include/python3.15/pyframe.h"
__attribute__ ((visibility ("default"))) int PyFrame_GetLineNumber(PyFrameObject *);

__attribute__ ((visibility ("default"))) PyCodeObject * PyFrame_GetCode(PyFrameObject *frame);



# 1 "/home/alexturner/include/python3.15/cpython/pyframe.h" 1




extern __attribute__ ((visibility ("default"))) PyTypeObject PyFrame_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyFrameLocalsProxy_Type;




__attribute__ ((visibility ("default"))) PyFrameObject * PyFrame_GetBack(PyFrameObject *frame);
__attribute__ ((visibility ("default"))) PyObject * PyFrame_GetLocals(PyFrameObject *frame);

__attribute__ ((visibility ("default"))) PyObject * PyFrame_GetGlobals(PyFrameObject *frame);
__attribute__ ((visibility ("default"))) PyObject * PyFrame_GetBuiltins(PyFrameObject *frame);

__attribute__ ((visibility ("default"))) PyObject * PyFrame_GetGenerator(PyFrameObject *frame);
__attribute__ ((visibility ("default"))) int PyFrame_GetLasti(PyFrameObject *frame);
__attribute__ ((visibility ("default"))) PyObject* PyFrame_GetVar(PyFrameObject *frame, PyObject *name);
__attribute__ ((visibility ("default"))) PyObject* PyFrame_GetVarString(PyFrameObject *frame, const char *name);




struct _PyInterpreterFrame;



__attribute__ ((visibility ("default"))) PyObject * PyUnstable_InterpreterFrame_GetCode(struct _PyInterpreterFrame *frame);



__attribute__ ((visibility ("default"))) int PyUnstable_InterpreterFrame_GetLasti(struct _PyInterpreterFrame *frame);



__attribute__ ((visibility ("default"))) int PyUnstable_InterpreterFrame_GetLine(struct _PyInterpreterFrame *frame);







extern __attribute__ ((visibility ("default"))) const PyTypeObject * const PyUnstable_ExecutableKinds[5 +1];
# 20 "/home/alexturner/include/python3.15/pyframe.h" 2
# 115 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/traceback.h" 1
# 9 "/home/alexturner/include/python3.15/traceback.h"
__attribute__ ((visibility ("default"))) int PyTraceBack_Here(PyFrameObject *);
__attribute__ ((visibility ("default"))) int PyTraceBack_Print(PyObject *, PyObject *);


extern __attribute__ ((visibility ("default"))) PyTypeObject PyTraceBack_Type;





# 1 "/home/alexturner/include/python3.15/cpython/traceback.h" 1




typedef struct _traceback PyTracebackObject;

struct _traceback {
    PyObject ob_base;
    PyTracebackObject *tb_next;
    PyFrameObject *tb_frame;
    int tb_lasti;
    int tb_lineno;
};
# 20 "/home/alexturner/include/python3.15/traceback.h" 2
# 116 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/sliceobject.h" 1
# 9 "/home/alexturner/include/python3.15/sliceobject.h"
extern __attribute__ ((visibility ("default"))) PyObject _Py_EllipsisObject;
# 19 "/home/alexturner/include/python3.15/sliceobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PySlice_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyEllipsis_Type;



__attribute__ ((visibility ("default"))) PyObject * PySlice_New(PyObject* start, PyObject* stop,
                                  PyObject* step);
__attribute__ ((visibility ("default"))) int PySlice_GetIndices(PyObject *r, Py_ssize_t length,
                                  Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step);
__attribute__((__deprecated__))
__attribute__ ((visibility ("default"))) int PySlice_GetIndicesEx(PyObject *r, Py_ssize_t length,
                                     Py_ssize_t *start, Py_ssize_t *stop,
                                     Py_ssize_t *step,
                                     Py_ssize_t *slicelength);







__attribute__ ((visibility ("default"))) int PySlice_Unpack(PyObject *slice,
                               Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step);
__attribute__ ((visibility ("default"))) Py_ssize_t PySlice_AdjustIndices(Py_ssize_t length,
                                             Py_ssize_t *start, Py_ssize_t *stop,
                                             Py_ssize_t step);




# 1 "/home/alexturner/include/python3.15/cpython/sliceobject.h" 1
# 12 "/home/alexturner/include/python3.15/cpython/sliceobject.h"
typedef struct {
    PyObject ob_base;
    PyObject *start, *stop, *step;
} PySliceObject;

__attribute__ ((visibility ("default"))) PyObject * _PySlice_FromIndices(Py_ssize_t start, Py_ssize_t stop);
__attribute__ ((visibility ("default"))) int _PySlice_GetLongIndices(PySliceObject *self, PyObject *length,
                                 PyObject **start_ptr, PyObject **stop_ptr,
                                 PyObject **step_ptr);
# 50 "/home/alexturner/include/python3.15/sliceobject.h" 2
# 117 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/cellobject.h" 1
# 10 "/home/alexturner/include/python3.15/cpython/cellobject.h"
typedef struct {
    PyObject ob_base;

    PyObject *ob_ref;
} PyCellObject;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyCell_Type;



__attribute__ ((visibility ("default"))) PyObject * PyCell_New(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyCell_Get(PyObject *);
__attribute__ ((visibility ("default"))) int PyCell_Set(PyObject *, PyObject *);

static inline PyObject* PyCell_GET(PyObject *op) {
    PyObject *res;
    PyCellObject *cell;
    
# 27 "/home/alexturner/include/python3.15/cpython/cellobject.h" 3 4
   ((void) (0))
# 27 "/home/alexturner/include/python3.15/cpython/cellobject.h"
                           ;
    cell = ((PyCellObject*)(op));
    {;
    res = cell->ob_ref;
    };
    return res;
}


static inline void PyCell_SET(PyObject *op, PyObject *value) {
    PyCellObject *cell;
    
# 38 "/home/alexturner/include/python3.15/cpython/cellobject.h" 3 4
   ((void) (0))
# 38 "/home/alexturner/include/python3.15/cpython/cellobject.h"
                           ;
    cell = ((PyCellObject*)(op));
    {;
    cell->ob_ref = value;
    };
}
# 118 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/iterobject.h" 1







extern __attribute__ ((visibility ("default"))) PyTypeObject PySeqIter_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyCallIter_Type;



__attribute__ ((visibility ("default"))) PyObject * PySeqIter_New(PyObject *);




__attribute__ ((visibility ("default"))) PyObject * PyCallIter_New(PyObject *, PyObject *);
# 119 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/initconfig.h" 1
# 10 "/home/alexturner/include/python3.15/cpython/initconfig.h"
typedef struct {
    enum {
        _PyStatus_TYPE_OK=0,
        _PyStatus_TYPE_ERROR=1,
        _PyStatus_TYPE_EXIT=2
    } _type;
    const char *func;
    const char *err_msg;
    int exitcode;
} PyStatus;

__attribute__ ((visibility ("default"))) PyStatus PyStatus_Ok(void);
__attribute__ ((visibility ("default"))) PyStatus PyStatus_Error(const char *err_msg);
__attribute__ ((visibility ("default"))) PyStatus PyStatus_NoMemory(void);
__attribute__ ((visibility ("default"))) PyStatus PyStatus_Exit(int exitcode);
__attribute__ ((visibility ("default"))) int PyStatus_IsError(PyStatus err);
__attribute__ ((visibility ("default"))) int PyStatus_IsExit(PyStatus err);
__attribute__ ((visibility ("default"))) int PyStatus_Exception(PyStatus err);



typedef struct {


    Py_ssize_t length;
    wchar_t **items;
} PyWideStringList;

__attribute__ ((visibility ("default"))) PyStatus PyWideStringList_Append(PyWideStringList *list,
    const wchar_t *item);
__attribute__ ((visibility ("default"))) PyStatus PyWideStringList_Insert(PyWideStringList *list,
    Py_ssize_t index,
    const wchar_t *item);




typedef struct PyPreConfig {
    int _config_init;



    int parse_argv;






    int isolated;




    int use_environment;



    int configure_locale;
# 81 "/home/alexturner/include/python3.15/cpython/initconfig.h"
    int coerce_c_locale;







    int coerce_c_locale_warn;
# 113 "/home/alexturner/include/python3.15/cpython/initconfig.h"
    int utf8_mode;





    int dev_mode;



    int allocator;
} PyPreConfig;

__attribute__ ((visibility ("default"))) void PyPreConfig_InitPythonConfig(PyPreConfig *config);
__attribute__ ((visibility ("default"))) void PyPreConfig_InitIsolatedConfig(PyPreConfig *config);





typedef struct PyConfig {
    int _config_init;

    int isolated;
    int use_environment;
    int dev_mode;
    int install_signal_handlers;
    int use_hash_seed;
    unsigned long hash_seed;
    int faulthandler;
    int tracemalloc;
    int perf_profiling;
    int remote_debug;
    int import_time;
    int code_debug_ranges;
    int show_ref_count;
    int dump_refs;
    wchar_t *dump_refs_file;
    int malloc_stats;
    wchar_t *filesystem_encoding;
    wchar_t *filesystem_errors;
    wchar_t *pycache_prefix;
    int parse_argv;
    PyWideStringList orig_argv;
    PyWideStringList argv;
    PyWideStringList xoptions;
    PyWideStringList warnoptions;
    int site_import;
    int bytes_warning;
    int warn_default_encoding;
    int inspect;
    int interactive;
    int optimization_level;
    int parser_debug;
    int write_bytecode;
    int verbose;
    int quiet;
    int user_site_directory;
    int configure_c_stdio;
    int buffered_stdio;
    wchar_t *stdio_encoding;
    wchar_t *stdio_errors;



    wchar_t *check_hash_pycs_mode;
    int use_frozen_modules;
    int safe_path;
    int int_max_str_digits;



    int thread_inherit_context;
    int context_aware_warnings;




    int cpu_count;






    int pathconfig_warnings;
    wchar_t *program_name;
    wchar_t *pythonpath_env;
    wchar_t *home;
    wchar_t *platlibdir;


    int module_search_paths_set;
    PyWideStringList module_search_paths;
    wchar_t *stdlib_dir;
    wchar_t *executable;
    wchar_t *base_executable;
    wchar_t *prefix;
    wchar_t *base_prefix;
    wchar_t *exec_prefix;
    wchar_t *base_exec_prefix;


    int skip_source_first_line;
    wchar_t *run_command;
    wchar_t *run_module;
    wchar_t *run_filename;


    wchar_t *sys_path_0;





    int _install_importlib;


    int _init_main;


    int _is_python_build;
# 246 "/home/alexturner/include/python3.15/cpython/initconfig.h"
} PyConfig;

__attribute__ ((visibility ("default"))) void PyConfig_InitPythonConfig(PyConfig *config);
__attribute__ ((visibility ("default"))) void PyConfig_InitIsolatedConfig(PyConfig *config);
__attribute__ ((visibility ("default"))) void PyConfig_Clear(PyConfig *);
__attribute__ ((visibility ("default"))) PyStatus PyConfig_SetString(
    PyConfig *config,
    wchar_t **config_str,
    const wchar_t *str);
__attribute__ ((visibility ("default"))) PyStatus PyConfig_SetBytesString(
    PyConfig *config,
    wchar_t **config_str,
    const char *str);
__attribute__ ((visibility ("default"))) PyStatus PyConfig_Read(PyConfig *config);
__attribute__ ((visibility ("default"))) PyStatus PyConfig_SetBytesArgv(
    PyConfig *config,
    Py_ssize_t argc,
    char * const *argv);
__attribute__ ((visibility ("default"))) PyStatus PyConfig_SetArgv(PyConfig *config,
    Py_ssize_t argc,
    wchar_t * const *argv);
__attribute__ ((visibility ("default"))) PyStatus PyConfig_SetWideStringList(PyConfig *config,
    PyWideStringList *list,
    Py_ssize_t length, wchar_t **items);




__attribute__ ((visibility ("default"))) PyObject* PyConfig_Get(const char *name);
__attribute__ ((visibility ("default"))) int PyConfig_GetInt(const char *name, int *value);
__attribute__ ((visibility ("default"))) PyObject* PyConfig_Names(void);
__attribute__ ((visibility ("default"))) int PyConfig_Set(const char *name, PyObject *value);







__attribute__ ((visibility ("default"))) void Py_GetArgcArgv(int *argc, wchar_t ***argv);




typedef struct PyInitConfig PyInitConfig;

__attribute__ ((visibility ("default"))) PyInitConfig* PyInitConfig_Create(void);
__attribute__ ((visibility ("default"))) void PyInitConfig_Free(PyInitConfig *config);

__attribute__ ((visibility ("default"))) int PyInitConfig_GetError(PyInitConfig* config,
    const char **err_msg);
__attribute__ ((visibility ("default"))) int PyInitConfig_GetExitCode(PyInitConfig* config,
    int *exitcode);

__attribute__ ((visibility ("default"))) int PyInitConfig_HasOption(PyInitConfig *config,
    const char *name);
__attribute__ ((visibility ("default"))) int PyInitConfig_GetInt(PyInitConfig *config,
    const char *name,
    int64_t *value);
__attribute__ ((visibility ("default"))) int PyInitConfig_GetStr(PyInitConfig *config,
    const char *name,
    char **value);
__attribute__ ((visibility ("default"))) int PyInitConfig_GetStrList(PyInitConfig *config,
    const char *name,
    size_t *length,
    char ***items);
__attribute__ ((visibility ("default"))) void PyInitConfig_FreeStrList(size_t length, char **items);

__attribute__ ((visibility ("default"))) int PyInitConfig_SetInt(PyInitConfig *config,
    const char *name,
    int64_t value);
__attribute__ ((visibility ("default"))) int PyInitConfig_SetStr(PyInitConfig *config,
    const char *name,
    const char *value);
__attribute__ ((visibility ("default"))) int PyInitConfig_SetStrList(PyInitConfig *config,
    const char *name,
    size_t length,
    char * const *items);

__attribute__ ((visibility ("default"))) int PyInitConfig_AddModule(PyInitConfig *config,
    const char *name,
    PyObject* (*initfunc)(void));

__attribute__ ((visibility ("default"))) int Py_InitializeFromInitConfig(PyInitConfig *config);
# 120 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pystate.h" 1
# 14 "/home/alexturner/include/python3.15/pystate.h"
__attribute__ ((visibility ("default"))) PyInterpreterState * PyInterpreterState_New(void);
__attribute__ ((visibility ("default"))) void PyInterpreterState_Clear(PyInterpreterState *);
__attribute__ ((visibility ("default"))) void PyInterpreterState_Delete(PyInterpreterState *);
# 26 "/home/alexturner/include/python3.15/pystate.h"
__attribute__ ((visibility ("default"))) PyInterpreterState * PyInterpreterState_Get(void);




__attribute__ ((visibility ("default"))) PyObject * PyInterpreterState_GetDict(PyInterpreterState *);




__attribute__ ((visibility ("default"))) int64_t PyInterpreterState_GetID(PyInterpreterState *);






__attribute__ ((visibility ("default"))) int PyState_AddModule(PyObject*, PyModuleDef*);
__attribute__ ((visibility ("default"))) int PyState_RemoveModule(PyModuleDef*);

__attribute__ ((visibility ("default"))) PyObject* PyState_FindModule(PyModuleDef*);

__attribute__ ((visibility ("default"))) PyThreadState * PyThreadState_New(PyInterpreterState *);
__attribute__ ((visibility ("default"))) void PyThreadState_Clear(PyThreadState *);
__attribute__ ((visibility ("default"))) void PyThreadState_Delete(PyThreadState *);
# 60 "/home/alexturner/include/python3.15/pystate.h"
__attribute__ ((visibility ("default"))) PyThreadState * PyThreadState_Get(void);




__attribute__ ((visibility ("default"))) PyThreadState * PyThreadState_Swap(PyThreadState *);
__attribute__ ((visibility ("default"))) PyObject * PyThreadState_GetDict(void);
__attribute__ ((visibility ("default"))) int PyThreadState_SetAsyncExc(unsigned long, PyObject *);



__attribute__ ((visibility ("default"))) PyInterpreterState* PyThreadState_GetInterpreter(PyThreadState *tstate);
__attribute__ ((visibility ("default"))) PyFrameObject* PyThreadState_GetFrame(PyThreadState *tstate);
__attribute__ ((visibility ("default"))) uint64_t PyThreadState_GetID(PyThreadState *tstate);


typedef
    enum {PyGILState_LOCKED, PyGILState_UNLOCKED}
        PyGILState_STATE;
# 102 "/home/alexturner/include/python3.15/pystate.h"
__attribute__ ((visibility ("default"))) PyGILState_STATE PyGILState_Ensure(void);
# 112 "/home/alexturner/include/python3.15/pystate.h"
__attribute__ ((visibility ("default"))) void PyGILState_Release(PyGILState_STATE);







__attribute__ ((visibility ("default"))) PyThreadState * PyGILState_GetThisThreadState(void);




# 1 "/home/alexturner/include/python3.15/cpython/pystate.h" 1







__attribute__ ((visibility ("default"))) int _PyInterpreterState_RequiresIDRef(PyInterpreterState *);
__attribute__ ((visibility ("default"))) void _PyInterpreterState_RequireIDRef(PyInterpreterState *, int);




typedef int (*Py_tracefunc)(PyObject *, PyFrameObject *, int, PyObject *);
# 32 "/home/alexturner/include/python3.15/cpython/pystate.h"
typedef struct {
    int32_t debugger_pending_call;
    char debugger_script_path[512];
} _PyRemoteDebuggerSupport;

typedef struct _err_stackitem {
# 51 "/home/alexturner/include/python3.15/cpython/pystate.h"
    PyObject *exc_value;

    struct _err_stackitem *previous_item;

} _PyErr_StackItem;

typedef struct _stack_chunk {
    struct _stack_chunk *previous;
    size_t size;
    size_t top;
    PyObject * data[1];
} _PyStackChunk;



struct _ts {


    PyThreadState *prev;
    PyThreadState *next;
    PyInterpreterState *interp;




    uintptr_t eval_breaker;

    struct {




        unsigned int initialized:1;


        unsigned int bound:1;

        unsigned int unbound:1;

        unsigned int bound_gilstate:1;

        unsigned int active:1;


        unsigned int finalizing:1;
        unsigned int cleared:1;
        unsigned int finalized:1;


        unsigned int :24;
    } _status;
# 114 "/home/alexturner/include/python3.15/cpython/pystate.h"
    int holds_gil;


    int gil_requested;

    int _whence;



    int state;

    int py_recursion_remaining;
    int py_recursion_limit;
    int recursion_headroom;




    int tracing;
    int what_event;


    struct _PyInterpreterFrame *current_frame;

    Py_tracefunc c_profilefunc;
    Py_tracefunc c_tracefunc;
    PyObject *c_profileobj;
    PyObject *c_traceobj;


    PyObject *current_exception;




    _PyErr_StackItem *exc_info;

    PyObject *dict;

    int gilstate_counter;

    PyObject *async_exc;
    unsigned long thread_id;





    unsigned long native_thread_id;






    PyObject *delete_later;






    uintptr_t critical_section;

    int coroutine_origin_tracking_depth;

    PyObject *async_gen_firstiter;
    PyObject *async_gen_finalizer;

    PyObject *context;
    uint64_t context_ver;


    uint64_t id;

    _PyStackChunk *datastack_chunk;
    PyObject **datastack_top;
    PyObject **datastack_limit;
# 206 "/home/alexturner/include/python3.15/cpython/pystate.h"
    _PyErr_StackItem exc_state;

    PyObject *current_executor;


    struct _PyExitData *jit_exit;

    uint64_t dict_global_version;


    PyObject *threading_local_key;




    PyObject *threading_local_sentinel;
    _PyRemoteDebuggerSupport remote_debugger_support;
# 232 "/home/alexturner/include/python3.15/cpython/pystate.h"
};





__attribute__ ((visibility ("default"))) PyThreadState * PyThreadState_GetUnchecked(void);


__attribute__((__deprecated__)) static inline PyThreadState*
_PyThreadState_UncheckedGet(void)
{
    return PyThreadState_GetUnchecked();
}


__attribute__ ((visibility ("default"))) void PyThreadState_EnterTracing(PyThreadState *tstate);



__attribute__ ((visibility ("default"))) void PyThreadState_LeaveTracing(PyThreadState *tstate);
# 275 "/home/alexturner/include/python3.15/cpython/pystate.h"
__attribute__ ((visibility ("default"))) int PyGILState_Check(void);




__attribute__ ((visibility ("default"))) PyObject* _PyThread_CurrentFrames(void);



__attribute__ ((visibility ("default"))) int PyUnstable_ThreadState_SetStackProtection(
    PyThreadState *tstate,
    void *stack_start_addr,
    size_t stack_size);



__attribute__ ((visibility ("default"))) void PyUnstable_ThreadState_ResetStackProtection(
    PyThreadState *tstate);



__attribute__ ((visibility ("default"))) PyInterpreterState * PyInterpreterState_Main(void);
__attribute__ ((visibility ("default"))) PyInterpreterState * PyInterpreterState_Head(void);
__attribute__ ((visibility ("default"))) PyInterpreterState * PyInterpreterState_Next(PyInterpreterState *);
__attribute__ ((visibility ("default"))) PyThreadState * PyInterpreterState_ThreadHead(PyInterpreterState *);
__attribute__ ((visibility ("default"))) PyThreadState * PyThreadState_Next(PyThreadState *);
__attribute__ ((visibility ("default"))) void PyThreadState_DeleteCurrent(void);



typedef PyObject* (*_PyFrameEvalFunction)(PyThreadState *tstate, struct _PyInterpreterFrame *, int);

__attribute__ ((visibility ("default"))) _PyFrameEvalFunction _PyInterpreterState_GetEvalFrameFunc(
    PyInterpreterState *interp);
__attribute__ ((visibility ("default"))) void _PyInterpreterState_SetEvalFrameFunc(
    PyInterpreterState *interp,
    _PyFrameEvalFunction eval_frame);
# 126 "/home/alexturner/include/python3.15/pystate.h" 2
# 121 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/genobject.h" 1
# 12 "/home/alexturner/include/python3.15/cpython/genobject.h"
typedef struct _PyGenObject PyGenObject;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyGen_Type;




__attribute__ ((visibility ("default"))) PyObject * PyGen_New(PyFrameObject *);
__attribute__ ((visibility ("default"))) PyObject * PyGen_NewWithQualName(PyFrameObject *,
    PyObject *name, PyObject *qualname);
__attribute__ ((visibility ("default"))) PyCodeObject * PyGen_GetCode(PyGenObject *gen);




typedef struct _PyCoroObject PyCoroObject;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyCoro_Type;


__attribute__ ((visibility ("default"))) PyObject * PyCoro_New(PyFrameObject *,
    PyObject *name, PyObject *qualname);




typedef struct _PyAsyncGenObject PyAsyncGenObject;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyAsyncGen_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject _PyAsyncGenASend_Type;

__attribute__ ((visibility ("default"))) PyObject * PyAsyncGen_New(PyFrameObject *,
    PyObject *name, PyObject *qualname);
# 122 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/descrobject.h" 1







typedef PyObject *(*getter)(PyObject *, void *);
typedef int (*setter)(PyObject *, PyObject *, void *);

struct PyGetSetDef {
    const char *name;
    getter get;
    setter set;
    const char *doc;
    void *closure;
};

extern __attribute__ ((visibility ("default"))) PyTypeObject PyClassMethodDescr_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyGetSetDescr_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyMemberDescr_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyMethodDescr_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyWrapperDescr_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyDictProxy_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyProperty_Type;

__attribute__ ((visibility ("default"))) PyObject * PyDescr_NewMethod(PyTypeObject *, PyMethodDef *);
__attribute__ ((visibility ("default"))) PyObject * PyDescr_NewClassMethod(PyTypeObject *, PyMethodDef *);
__attribute__ ((visibility ("default"))) PyObject * PyDescr_NewMember(PyTypeObject *, PyMemberDef *);
__attribute__ ((visibility ("default"))) PyObject * PyDescr_NewGetSet(PyTypeObject *, PyGetSetDef *);

__attribute__ ((visibility ("default"))) PyObject * PyDictProxy_New(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyWrapper_New(PyObject *, PyObject *);







struct PyMemberDef {
    const char *name;
    int type;
    Py_ssize_t offset;
    int flags;
    const char *doc;
};
# 88 "/home/alexturner/include/python3.15/descrobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyMember_GetOne(const char *, PyMemberDef *);
__attribute__ ((visibility ("default"))) int PyMember_SetOne(char *, PyMemberDef *, PyObject *);



# 1 "/home/alexturner/include/python3.15/cpython/descrobject.h" 1




typedef PyObject *(*wrapperfunc)(PyObject *self, PyObject *args,
                                 void *wrapped);

typedef PyObject *(*wrapperfunc_kwds)(PyObject *self, PyObject *args,
                                      void *wrapped, PyObject *kwds);

struct wrapperbase {
    const char *name;
    int offset;
    void *function;
    wrapperfunc wrapper;
    const char *doc;
    int flags;
    PyObject *name_strobj;
};






typedef struct {
    PyObject ob_base;
    PyTypeObject *d_type;
    PyObject *d_name;
    PyObject *d_qualname;
} PyDescrObject;






typedef struct {
    PyDescrObject d_common;
    PyMethodDef *d_method;
    vectorcallfunc vectorcall;
} PyMethodDescrObject;

typedef struct {
    PyDescrObject d_common;
    PyMemberDef *d_member;
} PyMemberDescrObject;

typedef struct {
    PyDescrObject d_common;
    PyGetSetDef *d_getset;
} PyGetSetDescrObject;

typedef struct {
    PyDescrObject d_common;
    struct wrapperbase *d_base;
    void *d_wrapped;
} PyWrapperDescrObject;

__attribute__ ((visibility ("default"))) PyObject * PyDescr_NewWrapper(PyTypeObject *,
                                                struct wrapperbase *, void *);
__attribute__ ((visibility ("default"))) int PyDescr_IsData(PyObject *);
# 94 "/home/alexturner/include/python3.15/descrobject.h" 2
# 123 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/genericaliasobject.h" 1







__attribute__ ((visibility ("default"))) PyObject * Py_GenericAlias(PyObject *, PyObject *);
extern __attribute__ ((visibility ("default"))) PyTypeObject Py_GenericAliasType;
# 124 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/warnings.h" 1






__attribute__ ((visibility ("default"))) int PyErr_WarnEx(
    PyObject *category,
    const char *message,
    Py_ssize_t stack_level);

__attribute__ ((visibility ("default"))) int PyErr_WarnFormat(
    PyObject *category,
    Py_ssize_t stack_level,
    const char *format,
    ...);



__attribute__ ((visibility ("default"))) int PyErr_ResourceWarning(
    PyObject *source,
    Py_ssize_t stack_level,
    const char *format,
    ...);


__attribute__ ((visibility ("default"))) int PyErr_WarnExplicit(
    PyObject *category,
    const char *message,
    const char *filename,
    int lineno,
    const char *module,
    PyObject *registry);



# 1 "/home/alexturner/include/python3.15/cpython/warnings.h" 1




__attribute__ ((visibility ("default"))) int PyErr_WarnExplicitObject(
    PyObject *category,
    PyObject *message,
    PyObject *filename,
    int lineno,
    PyObject *module,
    PyObject *registry);

__attribute__ ((visibility ("default"))) int PyErr_WarnExplicitFormat(
    PyObject *category,
    const char *filename, int lineno,
    const char *module, PyObject *registry,
    const char *format, ...);
# 38 "/home/alexturner/include/python3.15/warnings.h" 2
# 125 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/weakrefobject.h" 1
# 9 "/home/alexturner/include/python3.15/weakrefobject.h"
typedef struct _PyWeakReference PyWeakReference;

extern __attribute__ ((visibility ("default"))) PyTypeObject _PyWeakref_RefType;
extern __attribute__ ((visibility ("default"))) PyTypeObject _PyWeakref_ProxyType;
extern __attribute__ ((visibility ("default"))) PyTypeObject _PyWeakref_CallableProxyType;
# 26 "/home/alexturner/include/python3.15/weakrefobject.h"
__attribute__ ((visibility ("default"))) PyObject * PyWeakref_NewRef(PyObject *ob,
                                        PyObject *callback);
__attribute__ ((visibility ("default"))) PyObject * PyWeakref_NewProxy(PyObject *ob,
                                          PyObject *callback);


__attribute__ ((visibility ("default"))) int PyWeakref_GetRef(PyObject *ref, PyObject **pobj);





# 1 "/home/alexturner/include/python3.15/cpython/weakrefobject.h" 1







struct _PyWeakReference {
    PyObject ob_base;





    PyObject *wr_object;


    PyObject *wr_callback;




    Py_hash_t hash;






    PyWeakReference *wr_prev;
    PyWeakReference *wr_next;
    vectorcallfunc vectorcall;
# 41 "/home/alexturner/include/python3.15/cpython/weakrefobject.h"
};

__attribute__ ((visibility ("default"))) void _PyWeakref_ClearRef(PyWeakReference *self);





__attribute__ ((visibility ("default"))) int PyWeakref_IsDead(PyObject *ref);
# 39 "/home/alexturner/include/python3.15/weakrefobject.h" 2
# 126 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/structseq.h" 1
# 10 "/home/alexturner/include/python3.15/structseq.h"
typedef struct PyStructSequence_Field {
    const char *name;
    const char *doc;
} PyStructSequence_Field;

typedef struct PyStructSequence_Desc {
    const char *name;
    const char *doc;
    PyStructSequence_Field *fields;
    int n_in_sequence;
} PyStructSequence_Desc;

extern __attribute__ ((visibility ("default"))) const char * const PyStructSequence_UnnamedField;

__attribute__ ((visibility ("default"))) PyTypeObject* PyStructSequence_NewType(PyStructSequence_Desc *desc);

__attribute__ ((visibility ("default"))) PyObject * PyStructSequence_New(PyTypeObject* type);

__attribute__ ((visibility ("default"))) void PyStructSequence_SetItem(PyObject*, Py_ssize_t, PyObject*);
__attribute__ ((visibility ("default"))) PyObject* PyStructSequence_GetItem(PyObject*, Py_ssize_t);



# 1 "/home/alexturner/include/python3.15/cpython/structseq.h" 1




__attribute__ ((visibility ("default"))) void PyStructSequence_InitType(PyTypeObject *type,
                                           PyStructSequence_Desc *desc);
__attribute__ ((visibility ("default"))) int PyStructSequence_InitType2(PyTypeObject *type,
                                           PyStructSequence_Desc *desc);

typedef PyTupleObject PyStructSequence;
# 34 "/home/alexturner/include/python3.15/structseq.h" 2
# 127 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/picklebufobject.h" 1
# 13 "/home/alexturner/include/python3.15/cpython/picklebufobject.h"
extern __attribute__ ((visibility ("default"))) PyTypeObject PyPickleBuffer_Type;




__attribute__ ((visibility ("default"))) PyObject * PyPickleBuffer_FromObject(PyObject *);



__attribute__ ((visibility ("default"))) const Py_buffer * PyPickleBuffer_GetBuffer(PyObject *);

__attribute__ ((visibility ("default"))) int PyPickleBuffer_Release(PyObject *);
# 128 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/pytime.h" 1
# 10 "/home/alexturner/include/python3.15/cpython/pytime.h"
typedef int64_t PyTime_t;



__attribute__ ((visibility ("default"))) double PyTime_AsSecondsDouble(PyTime_t t);
__attribute__ ((visibility ("default"))) int PyTime_Monotonic(PyTime_t *result);
__attribute__ ((visibility ("default"))) int PyTime_PerfCounter(PyTime_t *result);
__attribute__ ((visibility ("default"))) int PyTime_Time(PyTime_t *result);

__attribute__ ((visibility ("default"))) int PyTime_MonotonicRaw(PyTime_t *result);
__attribute__ ((visibility ("default"))) int PyTime_PerfCounterRaw(PyTime_t *result);
__attribute__ ((visibility ("default"))) int PyTime_TimeRaw(PyTime_t *result);
# 129 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/codecs.h" 1
# 26 "/home/alexturner/include/python3.15/codecs.h"
__attribute__ ((visibility ("default"))) int PyCodec_Register(
       PyObject *search_function
       );





__attribute__ ((visibility ("default"))) int PyCodec_Unregister(
       PyObject *search_function
       );
# 45 "/home/alexturner/include/python3.15/codecs.h"
__attribute__ ((visibility ("default"))) int PyCodec_KnownEncoding(
       const char *encoding
       );
# 59 "/home/alexturner/include/python3.15/codecs.h"
__attribute__ ((visibility ("default"))) PyObject * PyCodec_Encode(
       PyObject *object,
       const char *encoding,
       const char *errors
       );
# 75 "/home/alexturner/include/python3.15/codecs.h"
__attribute__ ((visibility ("default"))) PyObject * PyCodec_Decode(
       PyObject *object,
       const char *encoding,
       const char *errors
       );
# 102 "/home/alexturner/include/python3.15/codecs.h"
__attribute__ ((visibility ("default"))) PyObject * PyCodec_Encoder(const char *encoding);



__attribute__ ((visibility ("default"))) PyObject * PyCodec_Decoder(const char *encoding);



__attribute__ ((visibility ("default"))) PyObject * PyCodec_IncrementalEncoder(
   const char *encoding,
   const char *errors);



__attribute__ ((visibility ("default"))) PyObject * PyCodec_IncrementalDecoder(
   const char *encoding,
   const char *errors);



__attribute__ ((visibility ("default"))) PyObject * PyCodec_StreamReader(
   const char *encoding,
   PyObject *stream,
   const char *errors);



__attribute__ ((visibility ("default"))) PyObject * PyCodec_StreamWriter(
   const char *encoding,
   PyObject *stream,
   const char *errors);
# 142 "/home/alexturner/include/python3.15/codecs.h"
__attribute__ ((visibility ("default"))) int PyCodec_RegisterError(const char *name, PyObject *error);




__attribute__ ((visibility ("default"))) PyObject * PyCodec_LookupError(const char *name);


__attribute__ ((visibility ("default"))) PyObject * PyCodec_StrictErrors(PyObject *exc);


__attribute__ ((visibility ("default"))) PyObject * PyCodec_IgnoreErrors(PyObject *exc);


__attribute__ ((visibility ("default"))) PyObject * PyCodec_ReplaceErrors(PyObject *exc);


__attribute__ ((visibility ("default"))) PyObject * PyCodec_XMLCharRefReplaceErrors(PyObject *exc);


__attribute__ ((visibility ("default"))) PyObject * PyCodec_BackslashReplaceErrors(PyObject *exc);



__attribute__ ((visibility ("default"))) PyObject * PyCodec_NameReplaceErrors(PyObject *exc);



extern __attribute__ ((visibility ("default"))) const char * Py_hexdigits;
# 130 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pythread.h" 1



typedef void *PyThread_type_lock;







typedef enum PyLockStatus {
    PY_LOCK_FAILURE = 0,
    PY_LOCK_ACQUIRED = 1,
    PY_LOCK_INTR
} PyLockStatus;

__attribute__ ((visibility ("default"))) void PyThread_init_thread(void);
__attribute__ ((visibility ("default"))) unsigned long PyThread_start_new_thread(void (*)(void *), void *);
# 38 "/home/alexturner/include/python3.15/pythread.h"
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void __attribute__((__noreturn__)) PyThread_exit_thread(void);

__attribute__ ((visibility ("default"))) unsigned long PyThread_get_thread_ident(void);







__attribute__ ((visibility ("default"))) unsigned long PyThread_get_thread_native_id(void);


__attribute__ ((visibility ("default"))) PyThread_type_lock PyThread_allocate_lock(void);
__attribute__ ((visibility ("default"))) void PyThread_free_lock(PyThread_type_lock);
__attribute__ ((visibility ("default"))) int PyThread_acquire_lock(PyThread_type_lock, int);
# 74 "/home/alexturner/include/python3.15/pythread.h"
__attribute__ ((visibility ("default"))) PyLockStatus PyThread_acquire_lock_timed(PyThread_type_lock,
                                                     long long microseconds,
                                                     int intr_flag);

__attribute__ ((visibility ("default"))) void PyThread_release_lock(PyThread_type_lock);

__attribute__ ((visibility ("default"))) size_t PyThread_get_stacksize(void);
__attribute__ ((visibility ("default"))) int PyThread_set_stacksize(size_t);


__attribute__ ((visibility ("default"))) PyObject* PyThread_GetInfo(void);
# 95 "/home/alexturner/include/python3.15/pythread.h"
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int PyThread_create_key(void);
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void PyThread_delete_key(int key);
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) int PyThread_set_key_value(int key,
                                                          void *value);
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void * PyThread_get_key_value(int key);
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void PyThread_delete_key_value(int key);


__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void PyThread_ReInitTLS(void);






typedef struct _Py_tss_t Py_tss_t;

__attribute__ ((visibility ("default"))) Py_tss_t * PyThread_tss_alloc(void);
__attribute__ ((visibility ("default"))) void PyThread_tss_free(Py_tss_t *key);


__attribute__ ((visibility ("default"))) int PyThread_tss_is_created(Py_tss_t *key);
__attribute__ ((visibility ("default"))) int PyThread_tss_create(Py_tss_t *key);
__attribute__ ((visibility ("default"))) void PyThread_tss_delete(Py_tss_t *key);
__attribute__ ((visibility ("default"))) int PyThread_tss_set(Py_tss_t *key, void *value);
__attribute__ ((visibility ("default"))) void * PyThread_tss_get(Py_tss_t *key);




# 1 "/home/alexturner/include/python3.15/cpython/pythread.h" 1
# 11 "/home/alexturner/include/python3.15/cpython/pythread.h"
extern __attribute__ ((visibility ("default"))) const long long PY_TIMEOUT_MAX;





# 1 "/usr/include/pthread.h" 1 3 4
# 22 "/usr/include/pthread.h" 3 4
# 1 "/usr/include/sched.h" 1 3 4
# 29 "/usr/include/sched.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 30 "/usr/include/sched.h" 2 3 4
# 43 "/usr/include/sched.h" 3 4
# 1 "/usr/include/bits/sched.h" 1 3 4
# 60 "/usr/include/bits/sched.h" 3 4
# 1 "/usr/include/linux/sched/types.h" 1 3 4




# 1 "/usr/include/linux/types.h" 1 3 4




# 1 "/usr/include/asm/types.h" 1 3 4
# 1 "/usr/include/asm-generic/types.h" 1 3 4






# 1 "/usr/include/asm-generic/int-ll64.h" 1 3 4
# 12 "/usr/include/asm-generic/int-ll64.h" 3 4
# 1 "/usr/include/asm/bitsperlong.h" 1 3 4
# 11 "/usr/include/asm/bitsperlong.h" 3 4
# 1 "/usr/include/asm-generic/bitsperlong.h" 1 3 4
# 12 "/usr/include/asm/bitsperlong.h" 2 3 4
# 13 "/usr/include/asm-generic/int-ll64.h" 2 3 4








# 20 "/usr/include/asm-generic/int-ll64.h" 3 4
typedef __signed__ char __s8;
typedef unsigned char __u8;

typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;


__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;
# 8 "/usr/include/asm-generic/types.h" 2 3 4
# 2 "/usr/include/asm/types.h" 2 3 4
# 6 "/usr/include/linux/types.h" 2 3 4



# 1 "/usr/include/linux/posix_types.h" 1 3 4




# 1 "/usr/include/linux/stddef.h" 1 3 4
# 6 "/usr/include/linux/posix_types.h" 2 3 4
# 25 "/usr/include/linux/posix_types.h" 3 4
typedef struct {
 unsigned long fds_bits[1024 / (8 * sizeof(long))];
} __kernel_fd_set;


typedef void (*__kernel_sighandler_t)(int);


typedef int __kernel_key_t;
typedef int __kernel_mqd_t;

# 1 "/usr/include/asm/posix_types.h" 1 3 4






# 1 "/usr/include/asm/posix_types_64.h" 1 3 4
# 11 "/usr/include/asm/posix_types_64.h" 3 4
typedef unsigned short __kernel_old_uid_t;
typedef unsigned short __kernel_old_gid_t;


typedef unsigned long __kernel_old_dev_t;


# 1 "/usr/include/asm-generic/posix_types.h" 1 3 4
# 15 "/usr/include/asm-generic/posix_types.h" 3 4
typedef long __kernel_long_t;
typedef unsigned long __kernel_ulong_t;



typedef __kernel_ulong_t __kernel_ino_t;



typedef unsigned int __kernel_mode_t;



typedef int __kernel_pid_t;



typedef int __kernel_ipc_pid_t;



typedef unsigned int __kernel_uid_t;
typedef unsigned int __kernel_gid_t;



typedef __kernel_long_t __kernel_suseconds_t;



typedef int __kernel_daddr_t;



typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;
# 72 "/usr/include/asm-generic/posix_types.h" 3 4
typedef __kernel_ulong_t __kernel_size_t;
typedef __kernel_long_t __kernel_ssize_t;
typedef __kernel_long_t __kernel_ptrdiff_t;




typedef struct {
 int val[2];
} __kernel_fsid_t;





typedef __kernel_long_t __kernel_off_t;
typedef long long __kernel_loff_t;
typedef __kernel_long_t __kernel_old_time_t;
typedef __kernel_long_t __kernel_time_t;
typedef long long __kernel_time64_t;
typedef __kernel_long_t __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef char * __kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;
# 19 "/usr/include/asm/posix_types_64.h" 2 3 4
# 8 "/usr/include/asm/posix_types.h" 2 3 4
# 37 "/usr/include/linux/posix_types.h" 2 3 4
# 10 "/usr/include/linux/types.h" 2 3 4


typedef __signed__ __int128 __s128 __attribute__((aligned(16)));
typedef unsigned __int128 __u128 __attribute__((aligned(16)));
# 31 "/usr/include/linux/types.h" 3 4
typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;
typedef __u64 __le64;
typedef __u64 __be64;

typedef __u16 __sum16;
typedef __u32 __wsum;
# 55 "/usr/include/linux/types.h" 3 4
typedef unsigned __poll_t;
# 6 "/usr/include/linux/sched/types.h" 2 3 4
# 98 "/usr/include/linux/sched/types.h" 3 4
struct sched_attr {
 __u32 size;

 __u32 sched_policy;
 __u64 sched_flags;


 __s32 sched_nice;


 __u32 sched_priority;


 __u64 sched_runtime;
 __u64 sched_deadline;
 __u64 sched_period;


 __u32 sched_util_min;
 __u32 sched_util_max;

};
# 61 "/usr/include/bits/sched.h" 2 3 4
# 119 "/usr/include/bits/sched.h" 3 4
# 1 "/usr/include/bits/types/struct_sched_param.h" 1 3 4
# 23 "/usr/include/bits/types/struct_sched_param.h" 3 4
struct sched_param
{
  int sched_priority;
};
# 120 "/usr/include/bits/sched.h" 2 3 4





extern int clone (int (*__fn) (void *__arg), void *__child_stack,
    int __flags, void *__arg, ...) __attribute__ ((__nothrow__ , __leaf__));


extern int unshare (int __flags) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getcpu (void) __attribute__ ((__nothrow__ , __leaf__));


extern int getcpu (unsigned int *, unsigned int *) __attribute__ ((__nothrow__ , __leaf__));


extern int setns (int __fd, int __nstype) __attribute__ ((__nothrow__ , __leaf__));


int sched_setattr (pid_t tid, struct sched_attr *attr, unsigned int flags)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



int sched_getattr (pid_t tid, struct sched_attr *attr, unsigned int size,
     unsigned int flags)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




# 44 "/usr/include/sched.h" 2 3 4
# 1 "/usr/include/bits/cpu-set.h" 1 3 4
# 32 "/usr/include/bits/cpu-set.h" 3 4
typedef unsigned long int __cpu_mask;






typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;
# 115 "/usr/include/bits/cpu-set.h" 3 4


extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
     __attribute__ ((__nothrow__ , __leaf__));
extern cpu_set_t *__sched_cpualloc (size_t __count) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void __sched_cpufree (cpu_set_t *__set) __attribute__ ((__nothrow__ , __leaf__));


# 45 "/usr/include/sched.h" 2 3 4









extern int sched_setparam (__pid_t __pid, const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getparam (__pid_t __pid, struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_setscheduler (__pid_t __pid, int __policy,
          const struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getscheduler (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_yield (void) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_max (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_min (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));



extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) __attribute__ ((__nothrow__ , __leaf__));
# 130 "/usr/include/sched.h" 3 4
extern int sched_setaffinity (__pid_t __pid, size_t __cpusetsize,
         const cpu_set_t *__cpuset) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getaffinity (__pid_t __pid, size_t __cpusetsize,
         cpu_set_t *__cpuset) __attribute__ ((__nothrow__ , __leaf__));



# 23 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/time.h" 1 3 4
# 29 "/usr/include/time.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/11/include/stddef.h" 1 3 4
# 30 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/time.h" 1 3 4
# 73 "/usr/include/bits/time.h" 3 4
# 1 "/usr/include/bits/timex.h" 1 3 4
# 26 "/usr/include/bits/timex.h" 3 4
struct timex
{
# 58 "/usr/include/bits/timex.h" 3 4
  unsigned int modes;
  __syscall_slong_t offset;
  __syscall_slong_t freq;
  __syscall_slong_t maxerror;
  __syscall_slong_t esterror;
  int status;
  __syscall_slong_t constant;
  __syscall_slong_t precision;
  __syscall_slong_t tolerance;
  struct timeval time;
  __syscall_slong_t tick;
  __syscall_slong_t ppsfreq;
  __syscall_slong_t jitter;
  int shift;
  __syscall_slong_t stabil;
  __syscall_slong_t jitcnt;
  __syscall_slong_t calcnt;
  __syscall_slong_t errcnt;
  __syscall_slong_t stbcnt;

  int tai;


  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32;

};
# 74 "/usr/include/bits/time.h" 2 3 4




extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) __attribute__ ((__nothrow__ , __leaf__));
# 90 "/usr/include/bits/time.h" 3 4

# 34 "/usr/include/time.h" 2 3 4





# 1 "/usr/include/bits/types/struct_tm.h" 1 3 4






struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  const char *tm_zone;




};
# 40 "/usr/include/time.h" 2 3 4
# 48 "/usr/include/time.h" 3 4
# 1 "/usr/include/bits/types/struct_itimerspec.h" 1 3 4







struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
# 49 "/usr/include/time.h" 2 3 4
struct sigevent;
# 68 "/usr/include/time.h" 3 4




extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));



extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
# 100 "/usr/include/time.h" 3 4
extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));




extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     __attribute__ ((__nothrow__ , __leaf__));






extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));



extern char *strptime_l (const char *__restrict __s,
    const char *__restrict __fmt, struct tm *__tp,
    locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));






extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
# 154 "/usr/include/time.h" 3 4
extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
# 179 "/usr/include/time.h" 3 4
extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));



extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
# 197 "/usr/include/time.h" 3 4
extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
# 217 "/usr/include/time.h" 3 4
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));



extern int daylight;
extern long int timezone;
# 249 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));

extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
# 262 "/usr/include/time.h" 3 4
extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 272 "/usr/include/time.h" 3 4
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);


extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__));
# 311 "/usr/include/time.h" 3 4
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);
# 326 "/usr/include/time.h" 3 4
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));



extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));
# 364 "/usr/include/time.h" 3 4
extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));






extern int timespec_get (struct timespec *__ts, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 387 "/usr/include/time.h" 3 4
extern int timespec_getres (struct timespec *__ts, int __base)
     __attribute__ ((__nothrow__ , __leaf__));
# 413 "/usr/include/time.h" 3 4
extern int getdate_err;
# 422 "/usr/include/time.h" 3 4
extern struct tm *getdate (const char *__string);
# 436 "/usr/include/time.h" 3 4
extern int getdate_r (const char *__restrict __string,
        struct tm *__restrict __resbufp);



# 24 "/usr/include/pthread.h" 2 3 4



# 1 "/usr/include/bits/setjmp.h" 1 3 4
# 26 "/usr/include/bits/setjmp.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 27 "/usr/include/bits/setjmp.h" 2 3 4




typedef long int __jmp_buf[8];
# 28 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/pthread.h" 2 3 4


# 1 "/usr/include/bits/types/struct___jmp_buf_tag.h" 1 3 4
# 26 "/usr/include/bits/types/struct___jmp_buf_tag.h" 3 4
struct __jmp_buf_tag
  {




    __jmp_buf __jmpbuf;
    int __mask_was_saved;
    __sigset_t __saved_mask;
  };
# 32 "/usr/include/pthread.h" 2 3 4





enum
{
  PTHREAD_CREATE_JOINABLE,

  PTHREAD_CREATE_DETACHED

};



enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP

  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL



  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP

};




enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};





enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};
# 104 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
# 124 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_INHERIT_SCHED,

  PTHREAD_EXPLICIT_SCHED

};



enum
{
  PTHREAD_SCOPE_SYSTEM,

  PTHREAD_SCOPE_PROCESS

};



enum
{
  PTHREAD_PROCESS_PRIVATE,

  PTHREAD_PROCESS_SHARED

};
# 159 "/usr/include/pthread.h" 3 4
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};


enum
{
  PTHREAD_CANCEL_ENABLE,

  PTHREAD_CANCEL_DISABLE

};
enum
{
  PTHREAD_CANCEL_DEFERRED,

  PTHREAD_CANCEL_ASYNCHRONOUS

};
# 197 "/usr/include/pthread.h" 3 4





extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));





extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));







extern int pthread_join (pthread_t __th, void **__thread_return);




extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) __attribute__ ((__nothrow__ , __leaf__));
# 233 "/usr/include/pthread.h" 3 4
extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
     const struct timespec *__abstime);
# 243 "/usr/include/pthread.h" 3 4
extern int pthread_clockjoin_np (pthread_t __th, void **__thread_return,
                                 clockid_t __clockid,
     const struct timespec *__abstime);
# 269 "/usr/include/pthread.h" 3 4
extern int pthread_detach (pthread_t __th) __attribute__ ((__nothrow__ , __leaf__));



extern pthread_t pthread_self (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));







extern int pthread_attr_init (pthread_attr_t *__attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_destroy (pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getdetachstate (const pthread_attr_t *__attr,
     int *__detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getguardsize (const pthread_attr_t *__attr,
          size_t *__guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getschedparam (const pthread_attr_t *__restrict __attr,
           struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
           const struct sched_param *__restrict
           __param) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_getschedpolicy (const pthread_attr_t *__restrict
     __attr, int *__restrict __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getinheritsched (const pthread_attr_t *__restrict
      __attr, int *__restrict __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getscope (const pthread_attr_t *__restrict __attr,
      int *__restrict __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getstackaddr (const pthread_attr_t *__restrict
          __attr, void **__restrict __stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));





extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));


extern int pthread_attr_getstacksize (const pthread_attr_t *__restrict
          __attr, size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getstack (const pthread_attr_t *__restrict __attr,
      void **__restrict __stackaddr,
      size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int pthread_attr_setaffinity_np (pthread_attr_t *__attr,
     size_t __cpusetsize,
     const cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));



extern int pthread_attr_getaffinity_np (const pthread_attr_t *__attr,
     size_t __cpusetsize,
     cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));


extern int pthread_getattr_default_np (pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_setsigmask_np (pthread_attr_t *__attr,
           const __sigset_t *sigmask);




extern int pthread_attr_getsigmask_np (const pthread_attr_t *__attr,
           __sigset_t *sigmask);







extern int pthread_setattr_default_np (const pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));







extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));


extern int pthread_getschedparam (pthread_t __target_thread,
      int *__restrict __policy,
      struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));


extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     __attribute__ ((__nothrow__ , __leaf__));




extern int pthread_getname_np (pthread_t __target_thread, char *__buf,
          size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int pthread_setname_np (pthread_t __target_thread, const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));





extern int pthread_getconcurrency (void) __attribute__ ((__nothrow__ , __leaf__));


extern int pthread_setconcurrency (int __level) __attribute__ ((__nothrow__ , __leaf__));



extern int pthread_yield (void) __attribute__ ((__nothrow__ , __leaf__));

extern int pthread_yield (void) __asm__ ("" "sched_yield") __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("pthread_yield is deprecated, use sched_yield instead")))
                                                      ;







extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
       const cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));


extern int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize,
       cpu_set_t *__cpuset)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));
# 509 "/usr/include/pthread.h" 3 4
extern int pthread_once (pthread_once_t *__once_control,
    void (*__init_routine) (void)) __attribute__ ((__nonnull__ (1, 2)));
# 521 "/usr/include/pthread.h" 3 4
extern int pthread_setcancelstate (int __state, int *__oldstate);



extern int pthread_setcanceltype (int __type, int *__oldtype);


extern int pthread_cancel (pthread_t __th);




extern void pthread_testcancel (void);




struct __cancel_jmp_buf_tag
{
  __jmp_buf __cancel_jmp_buf;
  int __mask_was_saved;
};

typedef struct
{
  struct __cancel_jmp_buf_tag __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__ ((__aligned__));
# 557 "/usr/include/pthread.h" 3 4
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};
# 697 "/usr/include/pthread.h" 3 4
extern void __pthread_register_cancel (__pthread_unwind_buf_t *__buf)
     ;
# 709 "/usr/include/pthread.h" 3 4
extern void __pthread_unregister_cancel (__pthread_unwind_buf_t *__buf)
  ;
# 732 "/usr/include/pthread.h" 3 4
extern void __pthread_register_cancel_defer (__pthread_unwind_buf_t *__buf)
     ;
# 745 "/usr/include/pthread.h" 3 4
extern void __pthread_unregister_cancel_restore (__pthread_unwind_buf_t *__buf)
  ;



extern void __pthread_unwind_next (__pthread_unwind_buf_t *__buf)
     __attribute__ ((__noreturn__))

     __attribute__ ((__weak__))

     ;
# 766 "/usr/include/pthread.h" 3 4
extern int __sigsetjmp_cancel (struct __cancel_jmp_buf_tag __env[1], int __savemask) __asm__ ("" "__sigsetjmp") __attribute__ ((__nothrow__))


                     __attribute__ ((__returns_twice__));
# 781 "/usr/include/pthread.h" 3 4
extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          const pthread_mutexattr_t *__mutexattr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
        const struct timespec *__restrict
        __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 817 "/usr/include/pthread.h" 3 4
extern int pthread_mutex_clocklock (pthread_mutex_t *__restrict __mutex,
        clockid_t __clockid,
        const struct timespec *__restrict
        __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
# 835 "/usr/include/pthread.h" 3 4
extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
      __restrict __mutex,
      int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
      int __prioceiling,
      int *__restrict __old_ceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));




extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_consistent_np (pthread_mutex_t *) __asm__ ("" "pthread_mutex_consistent") __attribute__ ((__nothrow__ , __leaf__))
                                __attribute__ ((__nonnull__ (1)))
  __attribute__ ((__deprecated__ ("pthread_mutex_consistent_np is deprecated, use pthread_mutex_consistent")))
                                                                         ;
# 874 "/usr/include/pthread.h" 3 4
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
      __restrict __attr,
      int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict
          __attr, int *__restrict __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
       __restrict __attr,
       int *__restrict __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
          __restrict __attr,
          int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
     int *__robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_getrobust_np (pthread_mutexattr_t *, int *) __asm__ ("" "pthread_mutexattr_getrobust") __attribute__ ((__nothrow__ , __leaf__))

                                   __attribute__ ((__nonnull__ (1)))
  __attribute__ ((__deprecated__ ("pthread_mutexattr_getrobust_np is deprecated, use pthread_mutexattr_getrobust")))
                                                                               ;






extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *, int) __asm__ ("" "pthread_mutexattr_setrobust") __attribute__ ((__nothrow__ , __leaf__))

                                   __attribute__ ((__nonnull__ (1)))
  __attribute__ ((__deprecated__ ("pthread_mutexattr_setrobust_np is deprecated, use pthread_mutexattr_setrobust")))
                                                                               ;
# 967 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
    const pthread_rwlockattr_t *__restrict
    __attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 1004 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_clockrdlock (pthread_rwlock_t *__restrict __rwlock,
           clockid_t __clockid,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
# 1023 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 1051 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_clockwrlock (pthread_rwlock_t *__restrict __rwlock,
           clockid_t __clockid,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));
# 1071 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getkind_np (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pref)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
         const pthread_condattr_t *__restrict __cond_attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_destroy (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_signal (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
         pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));
# 1145 "/usr/include/pthread.h" 3 4
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       const struct timespec *__restrict __abstime)
     __attribute__ ((__nonnull__ (1, 2, 3)));
# 1171 "/usr/include/pthread.h" 3 4
extern int pthread_cond_clockwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       __clockid_t __clock_id,
       const struct timespec *__restrict __abstime)
     __attribute__ ((__nonnull__ (1, 2, 4)));
# 1194 "/usr/include/pthread.h" 3 4
extern int pthread_condattr_init (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_getpshared (const pthread_condattr_t *
     __restrict __attr,
     int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_condattr_getclock (const pthread_condattr_t *
          __restrict __attr,
          __clockid_t *__restrict __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1230 "/usr/include/pthread.h" 3 4
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
     const pthread_barrierattr_t *__restrict
     __attr, unsigned int __count)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_getpshared (const pthread_barrierattr_t *
        __restrict __attr,
        int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1297 "/usr/include/pthread.h" 3 4
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_key_delete (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern void *pthread_getspecific (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern int pthread_setspecific (pthread_key_t __key,
    const void *__pointer)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__access__ (__none__, 2)));




extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




extern pid_t pthread_gettid_np (pthread_t __thread_id);
# 1337 "/usr/include/pthread.h" 3 4
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) __attribute__ ((__nothrow__ , __leaf__));




extern __inline __attribute__ ((__gnu_inline__)) int
__attribute__ ((__nothrow__ , __leaf__)) pthread_equal (pthread_t __thread1, pthread_t __thread2)
{
  return __thread1 == __thread2;
}



# 18 "/home/alexturner/include/python3.15/cpython/pythread.h" 2
# 35 "/home/alexturner/include/python3.15/cpython/pythread.h"

# 35 "/home/alexturner/include/python3.15/cpython/pythread.h"
struct _Py_tss_t {
    int _is_initialized;
    pthread_key_t _key;
};
# 126 "/home/alexturner/include/python3.15/pythread.h" 2
# 131 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/context.h" 1







extern __attribute__ ((visibility ("default"))) PyTypeObject PyContext_Type;
typedef struct _pycontextobject PyContext;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyContextVar_Type;
typedef struct _pycontextvarobject PyContextVar;

extern __attribute__ ((visibility ("default"))) PyTypeObject PyContextToken_Type;
typedef struct _pycontexttokenobject PyContextToken;







__attribute__ ((visibility ("default"))) PyObject * PyContext_New(void);
__attribute__ ((visibility ("default"))) PyObject * PyContext_Copy(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PyContext_CopyCurrent(void);

__attribute__ ((visibility ("default"))) int PyContext_Enter(PyObject *);
__attribute__ ((visibility ("default"))) int PyContext_Exit(PyObject *);

typedef enum {





    Py_CONTEXT_SWITCHED = 1,
} PyContextEvent;
# 46 "/home/alexturner/include/python3.15/cpython/context.h"
typedef int (*PyContext_WatchCallback)(PyContextEvent, PyObject *);
# 55 "/home/alexturner/include/python3.15/cpython/context.h"
__attribute__ ((visibility ("default"))) int PyContext_AddWatcher(PyContext_WatchCallback callback);






__attribute__ ((visibility ("default"))) int PyContext_ClearWatcher(int watcher_id);





__attribute__ ((visibility ("default"))) PyObject * PyContextVar_New(
    const char *name, PyObject *default_value);
# 87 "/home/alexturner/include/python3.15/cpython/context.h"
__attribute__ ((visibility ("default"))) int PyContextVar_Get(
    PyObject *var, PyObject *default_value, PyObject **value);





__attribute__ ((visibility ("default"))) PyObject * PyContextVar_Set(PyObject *var, PyObject *value);





__attribute__ ((visibility ("default"))) int PyContextVar_Reset(PyObject *var, PyObject *token);
# 132 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/modsupport.h" 1
# 9 "/home/alexturner/include/python3.15/modsupport.h"
__attribute__ ((visibility ("default"))) int PyArg_Parse(PyObject *, const char *, ...);
__attribute__ ((visibility ("default"))) int PyArg_ParseTuple(PyObject *, const char *, ...);
__attribute__ ((visibility ("default"))) int PyArg_ParseTupleAndKeywords(PyObject *, PyObject *,
                                            const char *, char * const *, ...);
__attribute__ ((visibility ("default"))) int PyArg_VaParse(PyObject *, const char *, va_list);
__attribute__ ((visibility ("default"))) int PyArg_VaParseTupleAndKeywords(PyObject *, PyObject *,
                                              const char *, char * const *, va_list);

__attribute__ ((visibility ("default"))) int PyArg_ValidateKeywordArguments(PyObject *);
__attribute__ ((visibility ("default"))) int PyArg_UnpackTuple(PyObject *, const char *, Py_ssize_t, Py_ssize_t, ...);
__attribute__ ((visibility ("default"))) PyObject * Py_BuildValue(const char *, ...);
__attribute__ ((visibility ("default"))) PyObject * Py_VaBuildValue(const char *, va_list);





__attribute__ ((visibility ("default"))) int PyModule_AddObjectRef(PyObject *mod, const char *name, PyObject *value);




__attribute__ ((visibility ("default"))) int PyModule_Add(PyObject *mod, const char *name, PyObject *value);





__attribute__ ((visibility ("default"))) int PyModule_AddObject(PyObject *mod, const char *, PyObject *value);

__attribute__ ((visibility ("default"))) int PyModule_AddIntConstant(PyObject *, const char *, long);
__attribute__ ((visibility ("default"))) int PyModule_AddStringConstant(PyObject *, const char *, const char *);



__attribute__ ((visibility ("default"))) int PyModule_AddType(PyObject *module, PyTypeObject *type);







__attribute__ ((visibility ("default"))) int PyModule_SetDocString(PyObject *, const char *);
__attribute__ ((visibility ("default"))) int PyModule_AddFunctions(PyObject *, PyMethodDef *);
__attribute__ ((visibility ("default"))) int PyModule_ExecDef(PyObject *module, PyModuleDef *def);




__attribute__ ((visibility ("default"))) PyObject * PyModule_Create2(PyModuleDef*, int apiver);
# 71 "/home/alexturner/include/python3.15/modsupport.h"
__attribute__ ((visibility ("default"))) PyObject * PyModule_FromDefAndSpec2(PyModuleDef *def,
                                                PyObject *spec,
                                                int module_api_version);
# 87 "/home/alexturner/include/python3.15/modsupport.h"
typedef struct PyABIInfo {
    uint8_t abiinfo_major_version;
    uint8_t abiinfo_minor_version;
    uint16_t flags;
    uint32_t build_version;
    uint32_t abi_version;
} PyABIInfo;







__attribute__ ((visibility ("default"))) int PyABIInfo_Check(PyABIInfo *info, const char *module_name);
# 153 "/home/alexturner/include/python3.15/modsupport.h"
# 1 "/home/alexturner/include/python3.15/cpython/modsupport.h" 1






typedef struct {
    uint8_t v;
} _PyOnceFlag;

typedef struct _PyArg_Parser {
    const char *format;
    const char * const *keywords;
    const char *fname;
    const char *custom_msg;
    _PyOnceFlag once;
    int is_kwtuple_owned;
    int pos;
    int min;
    int max;
    PyObject *kwtuple;
    struct _PyArg_Parser *next;
} _PyArg_Parser;

__attribute__ ((visibility ("default"))) int _PyArg_ParseTupleAndKeywordsFast(PyObject *, PyObject *,
                                                 struct _PyArg_Parser *, ...);
# 154 "/home/alexturner/include/python3.15/modsupport.h" 2
# 133 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/compile.h" 1
# 15 "/home/alexturner/include/python3.15/compile.h"
# 1 "/home/alexturner/include/python3.15/cpython/compile.h" 1
# 27 "/home/alexturner/include/python3.15/cpython/compile.h"
typedef struct {
    int cf_flags;
    int cf_feature_version;
} PyCompilerFlags;
# 49 "/home/alexturner/include/python3.15/cpython/compile.h"
__attribute__ ((visibility ("default"))) int PyCompile_OpcodeStackEffect(int opcode, int oparg);
__attribute__ ((visibility ("default"))) int PyCompile_OpcodeStackEffectWithJump(int opcode, int oparg, int jump);
# 16 "/home/alexturner/include/python3.15/compile.h" 2
# 134 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pythonrun.h" 1
# 10 "/home/alexturner/include/python3.15/pythonrun.h"
__attribute__ ((visibility ("default"))) PyObject * Py_CompileString(const char *, const char *, int);

__attribute__ ((visibility ("default"))) void PyErr_Print(void);
__attribute__ ((visibility ("default"))) void PyErr_PrintEx(int);
__attribute__ ((visibility ("default"))) void PyErr_Display(PyObject *, PyObject *, PyObject *);


__attribute__ ((visibility ("default"))) void PyErr_DisplayException(PyObject *);




extern __attribute__ ((visibility ("default"))) int (*PyOS_InputHook)(void);
# 35 "/home/alexturner/include/python3.15/pythonrun.h"
# 1 "/home/alexturner/include/python3.15/cpython/pythonrun.h" 1




__attribute__ ((visibility ("default"))) int PyRun_SimpleStringFlags(const char *, PyCompilerFlags *);
__attribute__ ((visibility ("default"))) int PyRun_AnyFileExFlags(
    FILE *fp,
    const char *filename,
    int closeit,
    PyCompilerFlags *flags);
__attribute__ ((visibility ("default"))) int PyRun_SimpleFileExFlags(
    FILE *fp,
    const char *filename,
    int closeit,
    PyCompilerFlags *flags);
__attribute__ ((visibility ("default"))) int PyRun_InteractiveOneFlags(
    FILE *fp,
    const char *filename,
    PyCompilerFlags *flags);
__attribute__ ((visibility ("default"))) int PyRun_InteractiveOneObject(
    FILE *fp,
    PyObject *filename,
    PyCompilerFlags *flags);
__attribute__ ((visibility ("default"))) int PyRun_InteractiveLoopFlags(
    FILE *fp,
    const char *filename,
    PyCompilerFlags *flags);


__attribute__ ((visibility ("default"))) PyObject * PyRun_StringFlags(const char *, int, PyObject *,
                                         PyObject *, PyCompilerFlags *);

__attribute__ ((visibility ("default"))) PyObject * PyRun_FileExFlags(
    FILE *fp,
    const char *filename,
    int start,
    PyObject *globals,
    PyObject *locals,
    int closeit,
    PyCompilerFlags *flags);


__attribute__ ((visibility ("default"))) PyObject * Py_CompileStringExFlags(
    const char *str,
    const char *filename,
    int start,
    PyCompilerFlags *flags,
    int optimize);
__attribute__ ((visibility ("default"))) PyObject * Py_CompileStringObject(
    const char *str,
    PyObject *filename, int start,
    PyCompilerFlags *flags,
    int optimize);
# 62 "/home/alexturner/include/python3.15/cpython/pythonrun.h"
__attribute__ ((visibility ("default"))) PyObject * PyRun_String(const char *str, int s, PyObject *g, PyObject *l);
__attribute__ ((visibility ("default"))) int PyRun_AnyFile(FILE *fp, const char *name);
__attribute__ ((visibility ("default"))) int PyRun_AnyFileEx(FILE *fp, const char *name, int closeit);
__attribute__ ((visibility ("default"))) int PyRun_AnyFileFlags(FILE *, const char *, PyCompilerFlags *);
__attribute__ ((visibility ("default"))) int PyRun_SimpleString(const char *s);
__attribute__ ((visibility ("default"))) int PyRun_SimpleFile(FILE *f, const char *p);
__attribute__ ((visibility ("default"))) int PyRun_SimpleFileEx(FILE *f, const char *p, int c);
__attribute__ ((visibility ("default"))) int PyRun_InteractiveOne(FILE *f, const char *p);
__attribute__ ((visibility ("default"))) int PyRun_InteractiveLoop(FILE *f, const char *p);
__attribute__ ((visibility ("default"))) PyObject * PyRun_File(FILE *fp, const char *p, int s, PyObject *g, PyObject *l);
__attribute__ ((visibility ("default"))) PyObject * PyRun_FileEx(FILE *fp, const char *p, int s, PyObject *g, PyObject *l, int c);
__attribute__ ((visibility ("default"))) PyObject * PyRun_FileFlags(FILE *fp, const char *p, int s, PyObject *g, PyObject *l, PyCompilerFlags *flags);
# 95 "/home/alexturner/include/python3.15/cpython/pythonrun.h"
__attribute__ ((visibility ("default"))) char * PyOS_Readline(FILE *, FILE *, const char *);
extern __attribute__ ((visibility ("default"))) char *(*PyOS_ReadlineFunctionPointer)(FILE *, FILE *, const char *);
# 36 "/home/alexturner/include/python3.15/pythonrun.h" 2
# 135 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pylifecycle.h" 1
# 12 "/home/alexturner/include/python3.15/pylifecycle.h"
__attribute__ ((visibility ("default"))) void Py_Initialize(void);
__attribute__ ((visibility ("default"))) void Py_InitializeEx(int);
__attribute__ ((visibility ("default"))) void Py_Finalize(void);

__attribute__ ((visibility ("default"))) int Py_FinalizeEx(void);

__attribute__ ((visibility ("default"))) int Py_IsInitialized(void);


__attribute__ ((visibility ("default"))) PyThreadState * Py_NewInterpreter(void);
__attribute__ ((visibility ("default"))) void Py_EndInterpreter(PyThreadState *);





__attribute__ ((visibility ("default"))) int Py_AtExit(void (*func)(void));

__attribute__ ((visibility ("default"))) void __attribute__((__noreturn__)) Py_Exit(int);


__attribute__ ((visibility ("default"))) int Py_Main(int argc, wchar_t **argv);
__attribute__ ((visibility ("default"))) int Py_BytesMain(int argc, char **argv);


__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void Py_SetProgramName(const wchar_t *);
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void Py_SetPythonHome(const wchar_t *);






__attribute__ ((visibility ("default"))) const char * Py_GetVersion(void);
__attribute__ ((visibility ("default"))) const char * Py_GetPlatform(void);
__attribute__ ((visibility ("default"))) const char * Py_GetCopyright(void);
__attribute__ ((visibility ("default"))) const char * Py_GetCompiler(void);
__attribute__ ((visibility ("default"))) const char * Py_GetBuildInfo(void);


typedef void (*PyOS_sighandler_t)(int);
__attribute__ ((visibility ("default"))) PyOS_sighandler_t PyOS_getsig(int);
__attribute__ ((visibility ("default"))) PyOS_sighandler_t PyOS_setsig(int, PyOS_sighandler_t);


extern __attribute__ ((visibility ("default"))) const unsigned long Py_Version;



__attribute__ ((visibility ("default"))) int Py_IsFinalizing(void);




# 1 "/home/alexturner/include/python3.15/cpython/pylifecycle.h" 1






__attribute__ ((visibility ("default"))) int Py_FrozenMain(int argc, char **argv);



__attribute__ ((visibility ("default"))) PyStatus Py_PreInitialize(
    const PyPreConfig *src_config);
__attribute__ ((visibility ("default"))) PyStatus Py_PreInitializeFromBytesArgs(
    const PyPreConfig *src_config,
    Py_ssize_t argc,
    char **argv);
__attribute__ ((visibility ("default"))) PyStatus Py_PreInitializeFromArgs(
    const PyPreConfig *src_config,
    Py_ssize_t argc,
    wchar_t **argv);




__attribute__ ((visibility ("default"))) PyStatus Py_InitializeFromConfig(
    const PyConfig *config);

__attribute__ ((visibility ("default"))) int Py_RunMain(void);


__attribute__ ((visibility ("default"))) void __attribute__((__noreturn__)) Py_ExitStatusException(PyStatus err);

__attribute__ ((visibility ("default"))) int Py_FdIsInteractive(FILE *, const char *);







typedef struct {

    int use_main_obmalloc;
    int allow_fork;
    int allow_exec;
    int allow_threads;
    int allow_daemon_threads;
    int check_multi_interp_extensions;
    int gil;
} PyInterpreterConfig;
# 83 "/home/alexturner/include/python3.15/cpython/pylifecycle.h"
__attribute__ ((visibility ("default"))) PyStatus Py_NewInterpreterFromConfig(
    PyThreadState **tstate_p,
    const PyInterpreterConfig *config);

typedef void (*atexit_datacallbackfunc)(void *);
__attribute__ ((visibility ("default"))) int PyUnstable_AtExit(
        PyInterpreterState *, atexit_datacallbackfunc, void *);
# 67 "/home/alexturner/include/python3.15/pylifecycle.h" 2
# 136 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/ceval.h" 1
# 10 "/home/alexturner/include/python3.15/ceval.h"
__attribute__ ((visibility ("default"))) PyObject * PyEval_EvalCode(PyObject *, PyObject *, PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyEval_EvalCodeEx(PyObject *co,
                                         PyObject *globals,
                                         PyObject *locals,
                                         PyObject *const *args, int argc,
                                         PyObject *const *kwds, int kwdc,
                                         PyObject *const *defs, int defc,
                                         PyObject *kwdefs, PyObject *closure);

__attribute__ ((visibility ("default"))) PyObject * PyEval_GetBuiltins(void);
__attribute__ ((visibility ("default"))) PyObject * PyEval_GetGlobals(void);
__attribute__ ((visibility ("default"))) PyObject * PyEval_GetLocals(void);
__attribute__ ((visibility ("default"))) PyFrameObject * PyEval_GetFrame(void);

__attribute__ ((visibility ("default"))) PyObject * PyEval_GetFrameBuiltins(void);
__attribute__ ((visibility ("default"))) PyObject * PyEval_GetFrameGlobals(void);
__attribute__ ((visibility ("default"))) PyObject * PyEval_GetFrameLocals(void);

__attribute__ ((visibility ("default"))) int Py_AddPendingCall(int (*func)(void *), void *arg);
__attribute__ ((visibility ("default"))) int Py_MakePendingCalls(void);
# 57 "/home/alexturner/include/python3.15/ceval.h"
__attribute__ ((visibility ("default"))) void Py_SetRecursionLimit(int);
__attribute__ ((visibility ("default"))) int Py_GetRecursionLimit(void);

__attribute__ ((visibility ("default"))) int Py_EnterRecursiveCall(const char *where);
__attribute__ ((visibility ("default"))) void Py_LeaveRecursiveCall(void);

__attribute__ ((visibility ("default"))) const char * PyEval_GetFuncName(PyObject *);
__attribute__ ((visibility ("default"))) const char * PyEval_GetFuncDesc(PyObject *);

__attribute__ ((visibility ("default"))) PyObject * PyEval_EvalFrame(PyFrameObject *);
__attribute__ ((visibility ("default"))) PyObject * PyEval_EvalFrameEx(PyFrameObject *f, int exc);
# 111 "/home/alexturner/include/python3.15/ceval.h"
__attribute__ ((visibility ("default"))) PyThreadState * PyEval_SaveThread(void);
__attribute__ ((visibility ("default"))) void PyEval_RestoreThread(PyThreadState *);

__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void PyEval_InitThreads(void);

__attribute__ ((visibility ("default"))) void PyEval_AcquireThread(PyThreadState *tstate);
__attribute__ ((visibility ("default"))) void PyEval_ReleaseThread(PyThreadState *tstate);
# 138 "/home/alexturner/include/python3.15/ceval.h"
# 1 "/home/alexturner/include/python3.15/cpython/ceval.h" 1




__attribute__ ((visibility ("default"))) void PyEval_SetProfile(Py_tracefunc, PyObject *);
__attribute__ ((visibility ("default"))) void PyEval_SetProfileAllThreads(Py_tracefunc, PyObject *);
__attribute__ ((visibility ("default"))) void PyEval_SetTrace(Py_tracefunc, PyObject *);
__attribute__ ((visibility ("default"))) void PyEval_SetTraceAllThreads(Py_tracefunc, PyObject *);




__attribute__ ((visibility ("default"))) int PyEval_MergeCompilerFlags(PyCompilerFlags *cf);

__attribute__ ((visibility ("default"))) PyObject * _PyEval_EvalFrameDefault(PyThreadState *tstate, struct _PyInterpreterFrame *f, int exc);

__attribute__ ((visibility ("default"))) Py_ssize_t PyUnstable_Eval_RequestCodeExtraIndex(freefunc);

__attribute__((__deprecated__)) static inline Py_ssize_t
_PyEval_RequestCodeExtraIndex(freefunc f) {
    return PyUnstable_Eval_RequestCodeExtraIndex(f);
}

__attribute__ ((visibility ("default"))) int _PyEval_SliceIndex(PyObject *, Py_ssize_t *);
__attribute__ ((visibility ("default"))) int _PyEval_SliceIndexNotNone(PyObject *, Py_ssize_t *);




typedef struct {
    FILE* perf_map;
    PyThread_type_lock map_lock;
} PerfMapState;

__attribute__ ((visibility ("default"))) int PyUnstable_PerfMapState_Init(void);
__attribute__ ((visibility ("default"))) int PyUnstable_WritePerfMapEntry(
    const void *code_addr,
    unsigned int code_size,
    const char *entry_name);
__attribute__ ((visibility ("default"))) void PyUnstable_PerfMapState_Fini(void);
__attribute__ ((visibility ("default"))) int PyUnstable_CopyPerfMapFile(const char* parent_filename);
__attribute__ ((visibility ("default"))) int PyUnstable_PerfTrampoline_CompileCode(PyCodeObject *);
__attribute__ ((visibility ("default"))) int PyUnstable_PerfTrampoline_SetPersistAfterFork(int enable);
# 139 "/home/alexturner/include/python3.15/ceval.h" 2
# 137 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/sysmodule.h" 1







__attribute__ ((visibility ("default"))) PyObject * PySys_GetAttr(PyObject *);
__attribute__ ((visibility ("default"))) PyObject * PySys_GetAttrString(const char *);
__attribute__ ((visibility ("default"))) int PySys_GetOptionalAttr(PyObject *, PyObject **);
__attribute__ ((visibility ("default"))) int PySys_GetOptionalAttrString(const char *, PyObject **);

__attribute__ ((visibility ("default"))) PyObject * PySys_GetObject(const char *);
__attribute__ ((visibility ("default"))) int PySys_SetObject(const char *, PyObject *);

__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void PySys_SetArgv(int, wchar_t **);
__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void PySys_SetArgvEx(int, wchar_t **, int);

__attribute__ ((visibility ("default"))) void PySys_WriteStdout(const char *format, ...)
                 __attribute__((format(printf, 1, 2)));
__attribute__ ((visibility ("default"))) void PySys_WriteStderr(const char *format, ...)
                 __attribute__((format(printf, 1, 2)));
__attribute__ ((visibility ("default"))) void PySys_FormatStdout(const char *format, ...);
__attribute__ ((visibility ("default"))) void PySys_FormatStderr(const char *format, ...);

__attribute__ ((visibility ("default"))) PyObject * PySys_GetXOptions(void);
# 138 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/audit.h" 1
# 9 "/home/alexturner/include/python3.15/audit.h"
__attribute__ ((visibility ("default"))) int PySys_Audit(
    const char *event,
    const char *argFormat,
    ...);

__attribute__ ((visibility ("default"))) int PySys_AuditTuple(
    const char *event,
    PyObject *args);





# 1 "/home/alexturner/include/python3.15/cpython/audit.h" 1





typedef int(*Py_AuditHookFunction)(const char *, PyObject *, void *);

__attribute__ ((visibility ("default"))) int PySys_AddAuditHook(Py_AuditHookFunction, void*);
# 23 "/home/alexturner/include/python3.15/audit.h" 2
# 139 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/osmodule.h" 1
# 11 "/home/alexturner/include/python3.15/osmodule.h"
__attribute__ ((visibility ("default"))) PyObject * PyOS_FSPath(PyObject *path);
# 140 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/intrcheck.h" 1






__attribute__ ((visibility ("default"))) int PyOS_InterruptOccurred(void);



__attribute__ ((visibility ("default"))) void PyOS_BeforeFork(void);
__attribute__ ((visibility ("default"))) void PyOS_AfterFork_Parent(void);
__attribute__ ((visibility ("default"))) void PyOS_AfterFork_Child(void);




__attribute__((__deprecated__)) __attribute__ ((visibility ("default"))) void PyOS_AfterFork(void);
# 141 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/import.h" 1
# 9 "/home/alexturner/include/python3.15/import.h"
__attribute__ ((visibility ("default"))) long PyImport_GetMagicNumber(void);
__attribute__ ((visibility ("default"))) const char * PyImport_GetMagicTag(void);
__attribute__ ((visibility ("default"))) PyObject * PyImport_ExecCodeModule(
    const char *name,
    PyObject *co
    );
__attribute__ ((visibility ("default"))) PyObject * PyImport_ExecCodeModuleEx(
    const char *name,
    PyObject *co,
    const char *pathname
    );
__attribute__ ((visibility ("default"))) PyObject * PyImport_ExecCodeModuleWithPathnames(
    const char *name,
    PyObject *co,
    const char *pathname,
    const char *cpathname
    );

__attribute__ ((visibility ("default"))) PyObject * PyImport_ExecCodeModuleObject(
    PyObject *name,
    PyObject *co,
    PyObject *pathname,
    PyObject *cpathname
    );

__attribute__ ((visibility ("default"))) PyObject * PyImport_GetModuleDict(void);

__attribute__ ((visibility ("default"))) PyObject * PyImport_GetModule(PyObject *name);


__attribute__ ((visibility ("default"))) PyObject * PyImport_AddModuleObject(
    PyObject *name
    );

__attribute__ ((visibility ("default"))) PyObject * PyImport_AddModule(
    const char *name
    );

__attribute__ ((visibility ("default"))) PyObject * PyImport_AddModuleRef(
    const char *name
    );

__attribute__ ((visibility ("default"))) PyObject * PyImport_ImportModule(
    const char *name
    );
__attribute__ ((visibility ("default"))) PyObject * PyImport_ImportModuleLevel(
    const char *name,
    PyObject *globals,
    PyObject *locals,
    PyObject *fromlist,
    int level
    );

__attribute__ ((visibility ("default"))) PyObject * PyImport_ImportModuleLevelObject(
    PyObject *name,
    PyObject *globals,
    PyObject *locals,
    PyObject *fromlist,
    int level
    );





__attribute__ ((visibility ("default"))) PyObject * PyImport_GetImporter(PyObject *path);
__attribute__ ((visibility ("default"))) PyObject * PyImport_Import(PyObject *name);
__attribute__ ((visibility ("default"))) PyObject * PyImport_ReloadModule(PyObject *m);

__attribute__ ((visibility ("default"))) int PyImport_ImportFrozenModuleObject(
    PyObject *name
    );

__attribute__ ((visibility ("default"))) int PyImport_ImportFrozenModule(
    const char *name
    );

__attribute__ ((visibility ("default"))) int PyImport_AppendInittab(
    const char *name,
    PyObject* (*initfunc)(void)
    );



# 1 "/home/alexturner/include/python3.15/cpython/import.h" 1




struct _inittab {
    const char *name;
    PyObject* (*initfunc)(void);
};

extern __attribute__ ((visibility ("default"))) struct _inittab * PyImport_Inittab;
__attribute__ ((visibility ("default"))) int PyImport_ExtendInittab(struct _inittab *newtab);




__attribute__ ((visibility ("default"))) PyObject * PyImport_CreateModuleFromInitfunc(
    PyObject *spec,
    PyObject *(*initfunc)(void));

struct _frozen {
    const char *name;
    const unsigned char *code;
    int size;
    int is_package;
};




extern __attribute__ ((visibility ("default"))) const struct _frozen * PyImport_FrozenModules;

__attribute__ ((visibility ("default"))) PyObject* PyImport_ImportModuleAttr(
    PyObject *mod_name,
    PyObject *attr_name);
__attribute__ ((visibility ("default"))) PyObject* PyImport_ImportModuleAttrString(
    const char *mod_name,
    const char *attr_name);
# 94 "/home/alexturner/include/python3.15/import.h" 2
# 142 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/abstract.h" 1
# 199 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_CallNoArgs(PyObject *func);
# 211 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_Call(PyObject *callable,
                                     PyObject *args, PyObject *kwargs);
# 222 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_CallObject(PyObject *callable,
                                           PyObject *args);
# 235 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_CallFunction(PyObject *callable,
                                             const char *format, ...);
# 247 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_CallMethod(PyObject *obj,
                                           const char *name,
                                           const char *format, ...);
# 259 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_CallFunctionObjArgs(PyObject *callable,
                                                    ...);
# 270 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_CallMethodObjArgs(
    PyObject *obj,
    PyObject *name,
    ...);





__attribute__ ((visibility ("default"))) Py_ssize_t PyVectorcall_NARGS(size_t nargsf);



__attribute__ ((visibility ("default"))) PyObject * PyVectorcall_Call(PyObject *callable, PyObject *tuple, PyObject *dict);






__attribute__ ((visibility ("default"))) PyObject * PyObject_Vectorcall(
    PyObject *callable,
    PyObject *const *args,
    size_t nargsf,
    PyObject *kwnames);


__attribute__ ((visibility ("default"))) PyObject * PyObject_VectorcallMethod(
    PyObject *name, PyObject *const *args,
    size_t nargsf, PyObject *kwnames);
# 338 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_Type(PyObject *o);
# 347 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) Py_ssize_t PyObject_Size(PyObject *o);




__attribute__ ((visibility ("default"))) Py_ssize_t PyObject_Length(PyObject *o);






__attribute__ ((visibility ("default"))) PyObject * PyObject_GetItem(PyObject *o, PyObject *key);







__attribute__ ((visibility ("default"))) int PyObject_SetItem(PyObject *o, PyObject *key, PyObject *v);





__attribute__ ((visibility ("default"))) int PyObject_DelItemString(PyObject *o, const char *key);





__attribute__ ((visibility ("default"))) int PyObject_DelItem(PyObject *o, PyObject *key);




__attribute__ ((visibility ("default"))) PyObject * PyObject_Format(PyObject *obj,
                                       PyObject *format_spec);







__attribute__ ((visibility ("default"))) PyObject * PyObject_GetIter(PyObject *);




__attribute__ ((visibility ("default"))) PyObject * PyObject_GetAIter(PyObject *);




__attribute__ ((visibility ("default"))) int PyIter_Check(PyObject *);




__attribute__ ((visibility ("default"))) int PyAIter_Check(PyObject *);






__attribute__ ((visibility ("default"))) int PyIter_NextItem(PyObject *iter, PyObject **item);
# 427 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyIter_Next(PyObject *);
# 439 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PySendResult PyIter_Send(PyObject *, PyObject *, PyObject **);
# 448 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) int PyNumber_Check(PyObject *o);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Add(PyObject *o1, PyObject *o2);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Subtract(PyObject *o1, PyObject *o2);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Multiply(PyObject *o1, PyObject *o2);



__attribute__ ((visibility ("default"))) PyObject * PyNumber_MatrixMultiply(PyObject *o1, PyObject *o2);






__attribute__ ((visibility ("default"))) PyObject * PyNumber_FloorDivide(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_TrueDivide(PyObject *o1, PyObject *o2);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Remainder(PyObject *o1, PyObject *o2);






__attribute__ ((visibility ("default"))) PyObject * PyNumber_Divmod(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_Power(PyObject *o1, PyObject *o2,
                                      PyObject *o3);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Negative(PyObject *o);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Positive(PyObject *o);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Absolute(PyObject *o);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Invert(PyObject *o);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Lshift(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_Rshift(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_And(PyObject *o1, PyObject *o2);




__attribute__ ((visibility ("default"))) PyObject * PyNumber_Xor(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_Or(PyObject *o1, PyObject *o2);



__attribute__ ((visibility ("default"))) int PyIndex_Check(PyObject *);



__attribute__ ((visibility ("default"))) PyObject * PyNumber_Index(PyObject *o);







__attribute__ ((visibility ("default"))) Py_ssize_t PyNumber_AsSsize_t(PyObject *o, PyObject *exc);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_Long(PyObject *o);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_Float(PyObject *o);
# 584 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceAdd(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceSubtract(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceMultiply(PyObject *o1, PyObject *o2);



__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceMatrixMultiply(PyObject *o1, PyObject *o2);






__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceFloorDivide(PyObject *o1,
                                                   PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceTrueDivide(PyObject *o1,
                                                  PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceRemainder(PyObject *o1, PyObject *o2);






__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlacePower(PyObject *o1, PyObject *o2,
                                             PyObject *o3);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceLshift(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceRshift(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceAnd(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceXor(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_InPlaceOr(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PyNumber_ToBase(PyObject *n, int base);
# 674 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) int PySequence_Check(PyObject *o);


__attribute__ ((visibility ("default"))) Py_ssize_t PySequence_Size(PyObject *o);



__attribute__ ((visibility ("default"))) Py_ssize_t PySequence_Length(PyObject *o);






__attribute__ ((visibility ("default"))) PyObject * PySequence_Concat(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PySequence_Repeat(PyObject *o, Py_ssize_t count);




__attribute__ ((visibility ("default"))) PyObject * PySequence_GetItem(PyObject *o, Py_ssize_t i);




__attribute__ ((visibility ("default"))) PyObject * PySequence_GetSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2);





__attribute__ ((visibility ("default"))) int PySequence_SetItem(PyObject *o, Py_ssize_t i, PyObject *v);




__attribute__ ((visibility ("default"))) int PySequence_DelItem(PyObject *o, Py_ssize_t i);





__attribute__ ((visibility ("default"))) int PySequence_SetSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2,
                                    PyObject *v);





__attribute__ ((visibility ("default"))) int PySequence_DelSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2);




__attribute__ ((visibility ("default"))) PyObject * PySequence_Tuple(PyObject *o);



__attribute__ ((visibility ("default"))) PyObject * PySequence_List(PyObject *o);
# 746 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PySequence_Fast(PyObject *o, const char* m);






__attribute__ ((visibility ("default"))) Py_ssize_t PySequence_Count(PyObject *o, PyObject *value);





__attribute__ ((visibility ("default"))) int PySequence_Contains(PyObject *seq, PyObject *ob);







__attribute__ ((visibility ("default"))) int PySequence_In(PyObject *o, PyObject *value);
# 777 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) Py_ssize_t PySequence_Index(PyObject *o, PyObject *value);
# 786 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PySequence_InPlaceConcat(PyObject *o1, PyObject *o2);





__attribute__ ((visibility ("default"))) PyObject * PySequence_InPlaceRepeat(PyObject *o, Py_ssize_t count);







__attribute__ ((visibility ("default"))) int PyMapping_Check(PyObject *o);



__attribute__ ((visibility ("default"))) Py_ssize_t PyMapping_Size(PyObject *o);



__attribute__ ((visibility ("default"))) Py_ssize_t PyMapping_Length(PyObject *o);
# 838 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) int PyMapping_HasKeyString(PyObject *o, const char *key);






__attribute__ ((visibility ("default"))) int PyMapping_HasKey(PyObject *o, PyObject *key);





__attribute__ ((visibility ("default"))) int PyMapping_HasKeyWithError(PyObject *o, PyObject *key);





__attribute__ ((visibility ("default"))) int PyMapping_HasKeyStringWithError(PyObject *o, const char *key);



__attribute__ ((visibility ("default"))) PyObject * PyMapping_Keys(PyObject *o);



__attribute__ ((visibility ("default"))) PyObject * PyMapping_Values(PyObject *o);




__attribute__ ((visibility ("default"))) PyObject * PyMapping_Items(PyObject *o);




__attribute__ ((visibility ("default"))) PyObject * PyMapping_GetItemString(PyObject *o,
                                               const char *key);
# 889 "/home/alexturner/include/python3.15/abstract.h"
__attribute__ ((visibility ("default"))) int PyMapping_GetOptionalItem(PyObject *, PyObject *, PyObject **);
__attribute__ ((visibility ("default"))) int PyMapping_GetOptionalItemString(PyObject *, const char *, PyObject **);






__attribute__ ((visibility ("default"))) int PyMapping_SetItemString(PyObject *o, const char *key,
                                        PyObject *value);


__attribute__ ((visibility ("default"))) int PyObject_IsInstance(PyObject *object, PyObject *typeorclass);


__attribute__ ((visibility ("default"))) int PyObject_IsSubclass(PyObject *object, PyObject *typeorclass);



# 1 "/home/alexturner/include/python3.15/cpython/abstract.h" 1
# 9 "/home/alexturner/include/python3.15/cpython/abstract.h"
__attribute__ ((visibility ("default"))) PyObject* _PyObject_CallMethodId(
    PyObject *obj,
    _Py_Identifier *name,
    const char *format, ...);
# 24 "/home/alexturner/include/python3.15/cpython/abstract.h"
__attribute__ ((visibility ("default"))) PyObject* _PyStack_AsDict(PyObject *const *values, PyObject *kwnames);







static inline Py_ssize_t
_PyVectorcall_NARGS(size_t n)
{
    return n & ~(((size_t)(1)) << (8 * sizeof(size_t) - 1));
}


__attribute__ ((visibility ("default"))) vectorcallfunc PyVectorcall_Function(PyObject *callable);
# 53 "/home/alexturner/include/python3.15/cpython/abstract.h"
__attribute__ ((visibility ("default"))) PyObject * PyObject_VectorcallDict(
    PyObject *callable,
    PyObject *const *args,
    size_t nargsf,
    PyObject *kwargs);

__attribute__ ((visibility ("default"))) PyObject * PyObject_CallOneArg(PyObject *func, PyObject *arg);

static inline PyObject *
PyObject_CallMethodNoArgs(PyObject *self, PyObject *name)
{
    size_t nargsf = 1 | (((size_t)(1)) << (8 * sizeof(size_t) - 1));
    return PyObject_VectorcallMethod(name, &self, nargsf, 
# 65 "/home/alexturner/include/python3.15/cpython/abstract.h" 3 4
                                                         ((void *)0)
# 65 "/home/alexturner/include/python3.15/cpython/abstract.h"
                                                                 );
}

static inline PyObject *
PyObject_CallMethodOneArg(PyObject *self, PyObject *name, PyObject *arg)
{
    PyObject *args[2] = {self, arg};
    size_t nargsf = 2 | (((size_t)(1)) << (8 * sizeof(size_t) - 1));
    
# 73 "/home/alexturner/include/python3.15/cpython/abstract.h" 3 4
   ((void) (0))
# 73 "/home/alexturner/include/python3.15/cpython/abstract.h"
                      ;
    return PyObject_VectorcallMethod(name, args, nargsf, 
# 74 "/home/alexturner/include/python3.15/cpython/abstract.h" 3 4
                                                        ((void *)0)
# 74 "/home/alexturner/include/python3.15/cpython/abstract.h"
                                                                );
}




__attribute__ ((visibility ("default"))) Py_ssize_t PyObject_LengthHint(PyObject *o, Py_ssize_t);
# 909 "/home/alexturner/include/python3.15/abstract.h" 2
# 143 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/bltinmodule.h" 1






extern __attribute__ ((visibility ("default"))) PyTypeObject PyFilter_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyMap_Type;
extern __attribute__ ((visibility ("default"))) PyTypeObject PyZip_Type;
# 144 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/pyctype.h" 1
# 16 "/home/alexturner/include/python3.15/cpython/pyctype.h"
extern __attribute__ ((visibility ("default"))) const unsigned int _Py_ctype_table[256];
# 29 "/home/alexturner/include/python3.15/cpython/pyctype.h"
extern __attribute__ ((visibility ("default"))) const unsigned char _Py_ctype_tolower[256];
extern __attribute__ ((visibility ("default"))) const unsigned char _Py_ctype_toupper[256];
# 145 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pystrtod.h" 1
# 9 "/home/alexturner/include/python3.15/pystrtod.h"
__attribute__ ((visibility ("default"))) double PyOS_string_to_double(const char *str,
                                         char **endptr,
                                         PyObject *overflow_exception);



__attribute__ ((visibility ("default"))) char * PyOS_double_to_string(double val,
                                         char format_code,
                                         int precision,
                                         int flags,
                                         int *type);
# 146 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/pystrcmp.h" 1







__attribute__ ((visibility ("default"))) int PyOS_mystrnicmp(const char *, const char *, Py_ssize_t);
__attribute__ ((visibility ("default"))) int PyOS_mystricmp(const char *, const char *);
# 147 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/fileutils.h" 1
# 9 "/home/alexturner/include/python3.15/fileutils.h"
# 1 "/usr/include/sys/stat.h" 1 3 4
# 99 "/usr/include/sys/stat.h" 3 4


# 1 "/usr/include/bits/stat.h" 1 3 4
# 25 "/usr/include/bits/stat.h" 3 4
# 1 "/usr/include/bits/struct_stat.h" 1 3 4
# 26 "/usr/include/bits/struct_stat.h" 3 4

# 26 "/usr/include/bits/struct_stat.h" 3 4
struct stat
  {



    __dev_t st_dev;




    __ino_t st_ino;







    __nlink_t st_nlink;
    __mode_t st_mode;

    __uid_t st_uid;
    __gid_t st_gid;

    int __pad0;

    __dev_t st_rdev;




    __off_t st_size;



    __blksize_t st_blksize;

    __blkcnt_t st_blocks;
# 74 "/usr/include/bits/struct_stat.h" 3 4
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
# 89 "/usr/include/bits/struct_stat.h" 3 4
    __syscall_slong_t __glibc_reserved[3];
# 99 "/usr/include/bits/struct_stat.h" 3 4
  };



struct stat64
  {



    __dev_t st_dev;

    __ino64_t st_ino;
    __nlink_t st_nlink;
    __mode_t st_mode;






    __uid_t st_uid;
    __gid_t st_gid;

    int __pad0;
    __dev_t st_rdev;
    __off_t st_size;





    __blksize_t st_blksize;
    __blkcnt64_t st_blocks;







    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
# 151 "/usr/include/bits/struct_stat.h" 3 4
    __syscall_slong_t __glibc_reserved[3];




  };
# 26 "/usr/include/bits/stat.h" 2 3 4
# 102 "/usr/include/sys/stat.h" 2 3 4
# 227 "/usr/include/sys/stat.h" 3 4
extern int stat (const char *__restrict __file, struct stat *__restrict __buf) __asm__ ("" "stat64") __attribute__ ((__nothrow__ , __leaf__))

     __attribute__ ((__nonnull__ (1, 2)));
extern int fstat (int __fd, struct stat *__buf) __asm__ ("" "fstat64") __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__nonnull__ (2)));
# 240 "/usr/include/sys/stat.h" 3 4
extern int stat64 (const char *__restrict __file,
     struct stat64 *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int fstat64 (int __fd, struct stat64 *__buf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 279 "/usr/include/sys/stat.h" 3 4
extern int fstatat (int __fd, const char *__restrict __file, struct stat *__restrict __buf, int __flag) __asm__ ("" "fstatat64") __attribute__ ((__nothrow__ , __leaf__))


                 __attribute__ ((__nonnull__ (2, 3)));
# 291 "/usr/include/sys/stat.h" 3 4
extern int fstatat64 (int __fd, const char *__restrict __file,
        struct stat64 *__restrict __buf, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 327 "/usr/include/sys/stat.h" 3 4
extern int lstat (const char *__restrict __file, struct stat *__restrict __buf) __asm__ ("" "lstat64") __attribute__ ((__nothrow__ , __leaf__))


     __attribute__ ((__nonnull__ (1, 2)));







extern int lstat64 (const char *__restrict __file,
      struct stat64 *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 352 "/usr/include/sys/stat.h" 3 4
extern int chmod (const char *__file, __mode_t __mode)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int lchmod (const char *__file, __mode_t __mode)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int fchmod (int __fd, __mode_t __mode) __attribute__ ((__nothrow__ , __leaf__));





extern int fchmodat (int __fd, const char *__file, __mode_t __mode,
       int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;






extern __mode_t umask (__mode_t __mask) __attribute__ ((__nothrow__ , __leaf__));




extern __mode_t getumask (void) __attribute__ ((__nothrow__ , __leaf__));



extern int mkdir (const char *__path, __mode_t __mode)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int mkdirat (int __fd, const char *__path, __mode_t __mode)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));






extern int mknod (const char *__path, __mode_t __mode, __dev_t __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int mknodat (int __fd, const char *__path, __mode_t __mode,
      __dev_t __dev) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));





extern int mkfifo (const char *__path, __mode_t __mode)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int mkfifoat (int __fd, const char *__path, __mode_t __mode)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));






extern int utimensat (int __fd, const char *__path,
        const struct timespec __times[2],
        int __flags)
     __attribute__ ((__nothrow__ , __leaf__));
# 452 "/usr/include/sys/stat.h" 3 4
extern int futimens (int __fd, const struct timespec __times[2]) __attribute__ ((__nothrow__ , __leaf__));
# 465 "/usr/include/sys/stat.h" 3 4
# 1 "/usr/include/bits/statx.h" 1 3 4
# 31 "/usr/include/bits/statx.h" 3 4
# 1 "/usr/include/linux/stat.h" 1 3 4
# 56 "/usr/include/linux/stat.h" 3 4
struct statx_timestamp {
 __s64 tv_sec;
 __u32 tv_nsec;
 __s32 __reserved;
};
# 99 "/usr/include/linux/stat.h" 3 4
struct statx {


 __u32 stx_mask;


 __u32 stx_blksize;


 __u64 stx_attributes;



 __u32 stx_nlink;


 __u32 stx_uid;


 __u32 stx_gid;


 __u16 stx_mode;
 __u16 __spare0[1];



 __u64 stx_ino;


 __u64 stx_size;


 __u64 stx_blocks;


 __u64 stx_attributes_mask;



 struct statx_timestamp stx_atime;


 struct statx_timestamp stx_btime;


 struct statx_timestamp stx_ctime;


 struct statx_timestamp stx_mtime;



 __u32 stx_rdev_major;
 __u32 stx_rdev_minor;


 __u32 stx_dev_major;
 __u32 stx_dev_minor;


 __u64 stx_mnt_id;


 __u32 stx_dio_mem_align;


 __u32 stx_dio_offset_align;



 __u64 stx_subvol;


 __u32 stx_atomic_write_unit_min;


 __u32 stx_atomic_write_unit_max;



 __u32 stx_atomic_write_segments_max;


 __u32 stx_dio_read_offset_align;


 __u32 stx_atomic_write_unit_max_opt;
 __u32 __spare2[1];


 __u64 __spare3[8];


};
# 32 "/usr/include/bits/statx.h" 2 3 4







# 1 "/usr/include/bits/statx-generic.h" 1 3 4
# 25 "/usr/include/bits/statx-generic.h" 3 4
# 1 "/usr/include/bits/types/struct_statx_timestamp.h" 1 3 4
# 26 "/usr/include/bits/statx-generic.h" 2 3 4
# 1 "/usr/include/bits/types/struct_statx.h" 1 3 4
# 27 "/usr/include/bits/statx-generic.h" 2 3 4
# 57 "/usr/include/bits/statx-generic.h" 3 4



int statx (int __dirfd, const char *__restrict __path, int __flags,
           unsigned int __mask, struct statx *__restrict __buf)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 5)));


# 40 "/usr/include/bits/statx.h" 2 3 4
# 466 "/usr/include/sys/stat.h" 2 3 4



# 10 "/home/alexturner/include/python3.15/fileutils.h" 2
# 44 "/home/alexturner/include/python3.15/fileutils.h"

# 44 "/home/alexturner/include/python3.15/fileutils.h"
__attribute__ ((visibility ("default"))) wchar_t * Py_DecodeLocale(
    const char *arg,
    size_t *size);

__attribute__ ((visibility ("default"))) char* Py_EncodeLocale(
    const wchar_t *text,
    size_t *error_pos);




# 1 "/home/alexturner/include/python3.15/cpython/fileutils.h" 1




__attribute__ ((visibility ("default"))) FILE* Py_fopen(
    PyObject *path,
    const char *mode);


__attribute__((__deprecated__)) static inline FILE*
_Py_fopen_obj(PyObject *path, const char *mode)
{
    return Py_fopen(path, mode);
}

__attribute__ ((visibility ("default"))) int Py_fclose(FILE *file);
# 56 "/home/alexturner/include/python3.15/fileutils.h" 2
# 148 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/pyfpe.h" 1
# 149 "/home/alexturner/include/python3.15/Python.h" 2
# 1 "/home/alexturner/include/python3.15/cpython/tracemalloc.h" 1
# 15 "/home/alexturner/include/python3.15/cpython/tracemalloc.h"
__attribute__ ((visibility ("default"))) int PyTraceMalloc_Track(
    unsigned int domain,
    uintptr_t ptr,
    size_t size);





__attribute__ ((visibility ("default"))) int PyTraceMalloc_Untrack(
    unsigned int domain,
    uintptr_t ptr);
# 150 "/home/alexturner/include/python3.15/Python.h" 2
# 18 "src/extension.phc" 2
# 27 "src/extension.phc"
# 1 "src/sgr.phc" 1
# 14 "src/sgr.phc"
typedef enum {
    Color_Default,
    Color_Indexed,
    Color_RGB,
    Color__COUNT
} Color_Tag;

typedef struct {
    char _empty;
} Color_Default_t;

typedef struct {
    uint8_t index;
} Color_Indexed_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color_RGB_t;

typedef struct Color {
    Color_Tag tag;
    union {
        Color_Default_t Default;
        Color_Indexed_t Indexed;
        Color_RGB_t RGB;
    };
} Color;

static inline Color Color_mk_Default(void) {
    Color _v;
    _v.tag = Color_Default;
    return _v;
}

static inline Color Color_mk_Indexed(uint8_t index) {
    Color _v;
    _v.tag = Color_Indexed;
    _v.Indexed.index = index;
    return _v;
}

static inline Color Color_mk_RGB(uint8_t r, uint8_t g, uint8_t b) {
    Color _v;
    _v.tag = Color_RGB;
    _v.RGB.r = r;
    _v.RGB.g = g;
    _v.RGB.b = b;
    return _v;
}

static inline Color_Default_t Color_as_Default(Color v) {
    if (v.tag != Color_Default) abort();
    return v.Default;
}

static inline Color_Indexed_t Color_as_Indexed(Color v) {
    if (v.tag != Color_Indexed) abort();
    return v.Indexed;
}

static inline Color_RGB_t Color_as_RGB(Color v) {
    if (v.tag != Color_RGB) abort();
    return v.RGB;
}
#line 19 "src/sgr.phc"
# 34 "src/sgr.phc"
typedef struct {
    Color fg;
    Color bg;
    uint16_t attrs;
} Pen;

static inline Pen pen_default(void) {
    Pen p;
    p.fg = Color_mk_Default();
    p.bg = Color_mk_Default();
    p.attrs = 0;
    return p;
}


static inline void pen_apply_sgr(Pen *pen, int param) {
    if (param == 0) {
        *pen = pen_default();
    } else if (param == 1) {
        pen->attrs |= (1 << 0);
    } else if (param == 2) {
        pen->attrs |= (1 << 1);
    } else if (param == 3) {
        pen->attrs |= (1 << 2);
    } else if (param == 4) {
        pen->attrs |= (1 << 3);
    } else if (param == 5) {
        pen->attrs |= (1 << 4);
    } else if (param == 7) {
        pen->attrs |= (1 << 5);
    } else if (param == 8) {
        pen->attrs |= (1 << 6);
    } else if (param == 9) {
        pen->attrs |= (1 << 7);
    } else if (param == 22) {
        pen->attrs &= (uint16_t)~((1 << 0) | (1 << 1));
    } else if (param == 23) {
        pen->attrs &= (uint16_t)~(1 << 2);
    } else if (param == 24) {
        pen->attrs &= (uint16_t)~(1 << 3);
    } else if (param == 25) {
        pen->attrs &= (uint16_t)~(1 << 4);
    } else if (param == 27) {
        pen->attrs &= (uint16_t)~(1 << 5);
    } else if (param == 28) {
        pen->attrs &= (uint16_t)~(1 << 6);
    } else if (param == 29) {
        pen->attrs &= (uint16_t)~(1 << 7);
    } else if (param >= 30 && param <= 37) {
        pen->fg = Color_mk_Indexed((uint8_t)(param - 30));
    } else if (param == 39) {
        pen->fg = Color_mk_Default();
    } else if (param >= 40 && param <= 47) {
        pen->bg = Color_mk_Indexed((uint8_t)(param - 40));
    } else if (param == 49) {
        pen->bg = Color_mk_Default();
    } else if (param >= 90 && param <= 97) {
        pen->fg = Color_mk_Indexed((uint8_t)(param - 90 + 8));
    } else if (param >= 100 && param <= 107) {
        pen->bg = Color_mk_Indexed((uint8_t)(param - 100 + 8));
    }

}





static inline int pen_apply_sgr_extended(Pen *pen, int *params, int count, int is_bg) {
    if (count < 2) return 1;
    Color *target = is_bg ? &pen->bg : &pen->fg;
    if (params[1] == 5 && count >= 3) {

        *target = Color_mk_Indexed((uint8_t)(params[2] & 0xFF));
        return 3;
    } else if (params[1] == 2 && count >= 5) {

        *target = Color_mk_RGB(
            (uint8_t)(params[2] & 0xFF),
            (uint8_t)(params[3] & 0xFF),
            (uint8_t)(params[4] & 0xFF)
        );
        return 5;
    }
    return 1;
}


static inline int color_equal(Color a, Color other) {
    switch (a.tag) {
    case Color_Default: { return other.tag == Color_Default; } break;
    case Color_Indexed: { uint8_t index = a.Indexed.index; {
            return other.tag == Color_Indexed && index == other.Indexed.index;
        } break; }
    case Color_RGB: { uint8_t r = a.RGB.r; uint8_t g = a.RGB.g; uint8_t b = a.RGB.b; {
            return other.tag == Color_RGB &&
                   r == other.RGB.r && g == other.RGB.g && b == other.RGB.b;
        } break; }
    default: break;
}
#line 133 "src/vt_parser.phc"
    return 0;
}
# 28 "src/extension.phc" 2
# 1 "src/screen.phc" 1
# 18 "src/screen.phc"
typedef struct {
    uint32_t codepoint;
    Color fg;
    Color bg;
    uint16_t attrs;
    uint8_t wide;
    uint8_t wide_cont;
} Cell;

static inline Cell cell_empty(void) {
    Cell c;
    memset(&c, 0, sizeof(c));
    c.fg = Color_mk_Default();
    c.bg = Color_mk_Default();
    return c;
}

static inline Cell cell_from_pen(uint32_t codepoint, const Pen *pen) {
    Cell c;
    c.codepoint = codepoint;
    c.fg = pen->fg;
    c.bg = pen->bg;
    c.attrs = pen->attrs;
    c.wide = 0;
    c.wide_cont = 0;
    return c;
}



typedef struct {
    int row;
    int col;
    Pen pen;
    int origin_mode;
    int autowrap;
    int wrap_pending;
} Cursor;



typedef struct {
    Cell *lines;
    int cols;
    int max_lines;
    int count;
    int head;
} Scrollback;

static Scrollback *scrollback_alloc(int max_lines, int cols) {
    Scrollback *sb = calloc(1, sizeof(Scrollback));
    if (!sb) return 
# 69 "src/screen.phc" 3 4
                   ((void *)0)
# 69 "src/screen.phc"
                       ;
    sb->cols = cols;
    sb->max_lines = max_lines;
    sb->lines = calloc((size_t)(max_lines * cols), sizeof(Cell));
    if (!sb->lines) { free(sb); return 
# 73 "src/screen.phc" 3 4
                                      ((void *)0)
# 73 "src/screen.phc"
                                          ; }
    sb->count = 0;
    sb->head = 0;
    return sb;
}

static void scrollback_free(Scrollback *sb) {
    if (!sb) return;
    free(sb->lines);
    free(sb);
}

static void scrollback_push_n(Scrollback *sb, const Cell *line, int src_cols) {
    int write_idx;
    if (sb->count < sb->max_lines) {
        write_idx = sb->count;
        sb->count++;
    } else {
        write_idx = sb->head;
        sb->head = (sb->head + 1) % sb->max_lines;
    }
    Cell *dest = &sb->lines[write_idx * sb->cols];
    int copy_cols = src_cols < sb->cols ? src_cols : sb->cols;
    memcpy(dest, line, (size_t)copy_cols * sizeof(Cell));

    for (int i = copy_cols; i < sb->cols; i++) {
        dest[i] = cell_empty();
    }
}

static const Cell *scrollback_get(const Scrollback *sb, int index) {
    if (index < 0 || index >= sb->count) return 
# 104 "src/screen.phc" 3 4
                                               ((void *)0)
# 104 "src/screen.phc"
                                                   ;
    int actual = (sb->head + index) % sb->max_lines;
    return &sb->lines[actual * sb->cols];
}



typedef struct {
    Cell *cells;
    int rows;
    int cols;
    Cursor cursor;
    Cursor saved_cursor;
    int scroll_top;
    int scroll_bottom;


    int mode_bracketed_paste;
    int mode_app_cursor;
    int mode_app_keypad;
} ScreenBuffer;

static ScreenBuffer *screen_alloc(int rows, int cols) {
    ScreenBuffer *scr = calloc(1, sizeof(ScreenBuffer));
    if (!scr) return 
# 128 "src/screen.phc" 3 4
                    ((void *)0)
# 128 "src/screen.phc"
                        ;
    scr->rows = rows;
    scr->cols = cols;
    scr->cells = calloc((size_t)(rows * cols), sizeof(Cell));
    if (!scr->cells) { free(scr); return 
# 132 "src/screen.phc" 3 4
                                        ((void *)0)
# 132 "src/screen.phc"
                                            ; }
    for (int i = 0; i < rows * cols; i++) {
        scr->cells[i] = cell_empty();
    }
    scr->cursor.row = 0;
    scr->cursor.col = 0;
    scr->cursor.pen = pen_default();
    scr->cursor.autowrap = 1;
    scr->scroll_top = 0;
    scr->scroll_bottom = rows - 1;
    return scr;
}

static void screen_free(ScreenBuffer *scr) {
    if (!scr) return;
    free(scr->cells);
    free(scr);
}

static inline Cell *screen_cell(ScreenBuffer *scr, int row, int col) {
    return &scr->cells[row * scr->cols + col];
}

static inline const Cell *screen_cell_const(const ScreenBuffer *scr, int row, int col) {
    return &scr->cells[row * scr->cols + col];
}



static void screen_clear_line(ScreenBuffer *scr, int row, int from_col, int to_col) {
    for (int c = from_col; c <= to_col && c < scr->cols; c++) {
        scr->cells[row * scr->cols + c] = cell_empty();
    }
}

static void screen_clear_region(ScreenBuffer *scr, int top, int left, int bottom, int right) {
    for (int r = top; r <= bottom && r < scr->rows; r++) {
        screen_clear_line(scr, r, left, right);
    }
}


static void screen_scroll_up(ScreenBuffer *scr, Scrollback *sb, int count) {
    int top = scr->scroll_top;
    int bottom = scr->scroll_bottom;
    if (count <= 0) return;
    if (count > bottom - top + 1) count = bottom - top + 1;


    if (sb && top == 0) {
        for (int i = 0; i < count; i++) {
            scrollback_push_n(sb, &scr->cells[i * scr->cols], scr->cols);
        }
    }


    int lines_to_move = bottom - top + 1 - count;
    if (lines_to_move > 0) {
        memmove(&scr->cells[top * scr->cols],
                &scr->cells[(top + count) * scr->cols],
                (size_t)(lines_to_move * scr->cols) * sizeof(Cell));
    }


    for (int r = bottom - count + 1; r <= bottom; r++) {
        screen_clear_line(scr, r, 0, scr->cols - 1);
    }
}


static void screen_scroll_down(ScreenBuffer *scr, int count) {
    int top = scr->scroll_top;
    int bottom = scr->scroll_bottom;
    if (count <= 0) return;
    if (count > bottom - top + 1) count = bottom - top + 1;

    int lines_to_move = bottom - top + 1 - count;
    if (lines_to_move > 0) {
        memmove(&scr->cells[(top + count) * scr->cols],
                &scr->cells[top * scr->cols],
                (size_t)(lines_to_move * scr->cols) * sizeof(Cell));
    }

    for (int r = top; r < top + count; r++) {
        screen_clear_line(scr, r, 0, scr->cols - 1);
    }
}



static void screen_put_char(ScreenBuffer *scr, Scrollback *sb, uint32_t codepoint) {
    Cursor *cur = &scr->cursor;


    if (cur->wrap_pending) {
        cur->col = 0;
        cur->row++;
        if (cur->row > scr->scroll_bottom) {
            cur->row = scr->scroll_bottom;
            screen_scroll_up(scr, sb, 1);
        }
        cur->wrap_pending = 0;
    }


    Cell *c = screen_cell(scr, cur->row, cur->col);
    *c = cell_from_pen(codepoint, &cur->pen);


    if (cur->col < scr->cols - 1) {
        cur->col++;
    } else if (cur->autowrap) {
        cur->wrap_pending = 1;
    }
}



static void screen_cursor_clamp(ScreenBuffer *scr) {
    Cursor *cur = &scr->cursor;
    if (cur->row < 0) cur->row = 0;
    if (cur->row >= scr->rows) cur->row = scr->rows - 1;
    if (cur->col < 0) cur->col = 0;
    if (cur->col >= scr->cols) cur->col = scr->cols - 1;
    cur->wrap_pending = 0;
}

static void screen_cursor_up(ScreenBuffer *scr, int n) {
    scr->cursor.row -= n;
    if (scr->cursor.row < scr->scroll_top)
        scr->cursor.row = scr->scroll_top;
    scr->cursor.wrap_pending = 0;
}

static void screen_cursor_down(ScreenBuffer *scr, int n) {
    scr->cursor.row += n;
    if (scr->cursor.row > scr->scroll_bottom)
        scr->cursor.row = scr->scroll_bottom;
    scr->cursor.wrap_pending = 0;
}

static void screen_cursor_forward(ScreenBuffer *scr, int n) {
    scr->cursor.col += n;
    if (scr->cursor.col >= scr->cols)
        scr->cursor.col = scr->cols - 1;
    scr->cursor.wrap_pending = 0;
}

static void screen_cursor_back(ScreenBuffer *scr, int n) {
    scr->cursor.col -= n;
    if (scr->cursor.col < 0)
        scr->cursor.col = 0;
    scr->cursor.wrap_pending = 0;
}

static void screen_cursor_set(ScreenBuffer *scr, int row, int col) {
    scr->cursor.row = row;
    scr->cursor.col = col;
    screen_cursor_clamp(scr);
}




static void screen_erase_display(ScreenBuffer *scr, int mode) {
    switch (mode) {
    case 0:
        screen_clear_line(scr, scr->cursor.row, scr->cursor.col, scr->cols - 1);
        for (int r = scr->cursor.row + 1; r < scr->rows; r++)
            screen_clear_line(scr, r, 0, scr->cols - 1);
        break;
    case 1:
        for (int r = 0; r < scr->cursor.row; r++)
            screen_clear_line(scr, r, 0, scr->cols - 1);
        screen_clear_line(scr, scr->cursor.row, 0, scr->cursor.col);
        break;
    case 2:
    case 3:
        screen_clear_region(scr, 0, 0, scr->rows - 1, scr->cols - 1);
        break;
    }
}


static void screen_erase_line(ScreenBuffer *scr, int mode) {
    int row = scr->cursor.row;
    switch (mode) {
    case 0:
        screen_clear_line(scr, row, scr->cursor.col, scr->cols - 1);
        break;
    case 1:
        screen_clear_line(scr, row, 0, scr->cursor.col);
        break;
    case 2:
        screen_clear_line(scr, row, 0, scr->cols - 1);
        break;
    }
}


static void screen_insert_chars(ScreenBuffer *scr, int n) {
    int row = scr->cursor.row;
    int col = scr->cursor.col;
    if (n > scr->cols - col) n = scr->cols - col;
    int to_move = scr->cols - col - n;
    if (to_move > 0) {
        memmove(&scr->cells[row * scr->cols + col + n],
                &scr->cells[row * scr->cols + col],
                (size_t)to_move * sizeof(Cell));
    }
    for (int i = 0; i < n; i++) {
        scr->cells[row * scr->cols + col + i] = cell_empty();
    }
}


static void screen_delete_chars(ScreenBuffer *scr, int n) {
    int row = scr->cursor.row;
    int col = scr->cursor.col;
    if (n > scr->cols - col) n = scr->cols - col;
    int to_move = scr->cols - col - n;
    if (to_move > 0) {
        memmove(&scr->cells[row * scr->cols + col],
                &scr->cells[row * scr->cols + col + n],
                (size_t)to_move * sizeof(Cell));
    }
    for (int i = scr->cols - n; i < scr->cols; i++) {
        scr->cells[row * scr->cols + i] = cell_empty();
    }
}


static void screen_insert_lines(ScreenBuffer *scr, int n) {
    int row = scr->cursor.row;
    if (row < scr->scroll_top || row > scr->scroll_bottom) return;
    int saved_top = scr->scroll_top;
    scr->scroll_top = row;
    screen_scroll_down(scr, n);
    scr->scroll_top = saved_top;
}


static void screen_delete_lines(ScreenBuffer *scr, Scrollback *sb, int n) {
    int row = scr->cursor.row;
    if (row < scr->scroll_top || row > scr->scroll_bottom) return;
    int saved_top = scr->scroll_top;
    scr->scroll_top = row;
    screen_scroll_up(scr, sb, n);
    scr->scroll_top = saved_top;
}



static void screen_tab(ScreenBuffer *scr) {
    int col = scr->cursor.col;
    col = ((col / 8) + 1) * 8;
    if (col >= scr->cols) col = scr->cols - 1;
    scr->cursor.col = col;
    scr->cursor.wrap_pending = 0;
}



static void screen_reverse_index(ScreenBuffer *scr) {
    if (scr->cursor.row == scr->scroll_top) {
        screen_scroll_down(scr, 1);
    } else if (scr->cursor.row > 0) {
        scr->cursor.row--;
    }
}



static void screen_resize(ScreenBuffer *scr, int new_rows, int new_cols) {
    Cell *new_cells = calloc((size_t)(new_rows * new_cols), sizeof(Cell));
    if (!new_cells) return;
    for (int i = 0; i < new_rows * new_cols; i++) {
        new_cells[i] = cell_empty();
    }

    int copy_rows = scr->rows < new_rows ? scr->rows : new_rows;
    int copy_cols = scr->cols < new_cols ? scr->cols : new_cols;
    for (int r = 0; r < copy_rows; r++) {
        memcpy(&new_cells[r * new_cols],
               &scr->cells[r * scr->cols],
               (size_t)copy_cols * sizeof(Cell));
    }

    free(scr->cells);
    scr->cells = new_cells;
    scr->rows = new_rows;
    scr->cols = new_cols;
    scr->scroll_top = 0;
    scr->scroll_bottom = new_rows - 1;
    if (scr->cursor.row >= new_rows) scr->cursor.row = new_rows - 1;
    if (scr->cursor.col >= new_cols) scr->cursor.col = new_cols - 1;
}



typedef struct {
    ScreenBuffer *main_screen;
    ScreenBuffer *alt_screen;
    ScreenBuffer *active;
    Scrollback *scrollback;
    int using_alt;
    int charset_g0;
    int charset_g1;
    int charset_active;
} Terminal;

static Terminal *terminal_new(int rows, int cols) {
    Terminal *term = calloc(1, sizeof(Terminal));
    if (!term) return 
# 445 "src/screen.phc" 3 4
                     ((void *)0)
# 445 "src/screen.phc"
                         ;

    term->main_screen = screen_alloc(rows, cols);
    if (!term->main_screen) { free(term); return 
# 448 "src/screen.phc" 3 4
                                                ((void *)0)
# 448 "src/screen.phc"
                                                    ; }

    term->alt_screen = screen_alloc(rows, cols);
    if (!term->alt_screen) { screen_free(term->main_screen); free(term); return 
# 451 "src/screen.phc" 3 4
                                                                               ((void *)0)
# 451 "src/screen.phc"
                                                                                   ; }

    term->scrollback = scrollback_alloc(10000, cols);
    if (!term->scrollback) {
        screen_free(term->main_screen);
        screen_free(term->alt_screen);
        free(term);
        return 
# 458 "src/screen.phc" 3 4
              ((void *)0)
# 458 "src/screen.phc"
                  ;
    }

    term->active = term->main_screen;
    term->using_alt = 0;
    return term;
}

static void terminal_free(Terminal *term) {
    if (!term) return;
    screen_free(term->main_screen);
    screen_free(term->alt_screen);
    scrollback_free(term->scrollback);
    free(term);
}

static void terminal_switch_alt(Terminal *term, int to_alt) {
    if (to_alt && !term->using_alt) {

        term->main_screen->saved_cursor = term->main_screen->cursor;
        term->active = term->alt_screen;
        term->using_alt = 1;
        screen_erase_display(term->alt_screen, 2);
    } else if (!to_alt && term->using_alt) {

        term->active = term->main_screen;
        term->main_screen->cursor = term->main_screen->saved_cursor;
        term->using_alt = 0;
    }
}

static void terminal_resize(Terminal *term, int rows, int cols) {
    screen_resize(term->main_screen, rows, cols);
    screen_resize(term->alt_screen, rows, cols);

}
# 29 "src/extension.phc" 2
# 1 "src/vt_parser.phc" 1
# 18 "src/vt_parser.phc"
typedef enum {
    VTState_Ground,
    VTState_Escape,
    VTState_EscapeIntermediate,
    VTState_CSI,
    VTState_OSC,
    VTState_DCS,
    VTState__COUNT
} VTState_Tag;

typedef struct {
    char _empty;
} VTState_Ground_t;

typedef struct {
    char _empty;
} VTState_Escape_t;

typedef struct {
    char intermediate;
} VTState_EscapeIntermediate_t;

typedef struct {
    int params[16];
    int param_count;
    int priv;
} VTState_CSI_t;

typedef struct {
    char buf[512];
    int len;
    int esc_seen;
} VTState_OSC_t;

typedef struct {
    char buf[512];
    int len;
} VTState_DCS_t;

typedef struct VTState {
    VTState_Tag tag;
    union {
        VTState_Ground_t Ground;
        VTState_Escape_t Escape;
        VTState_EscapeIntermediate_t EscapeIntermediate;
        VTState_CSI_t CSI;
        VTState_OSC_t OSC;
        VTState_DCS_t DCS;
    };
} VTState;

static inline VTState VTState_mk_Ground(void) {
    VTState _v;
    _v.tag = VTState_Ground;
    return _v;
}

static inline VTState VTState_mk_Escape(void) {
    VTState _v;
    _v.tag = VTState_Escape;
    return _v;
}

static inline VTState VTState_mk_EscapeIntermediate(char intermediate) {
    VTState _v;
    _v.tag = VTState_EscapeIntermediate;
    _v.EscapeIntermediate.intermediate = intermediate;
    return _v;
}

static inline VTState VTState_mk_CSI(int param_count, int priv) {
    VTState _v;
    _v.tag = VTState_CSI;
    _v.CSI.param_count = param_count;
    _v.CSI.priv = priv;
    return _v;
}

static inline VTState VTState_mk_OSC(int len, int esc_seen) {
    VTState _v;
    _v.tag = VTState_OSC;
    _v.OSC.len = len;
    _v.OSC.esc_seen = esc_seen;
    return _v;
}

static inline VTState VTState_mk_DCS(int len) {
    VTState _v;
    _v.tag = VTState_DCS;
    _v.DCS.len = len;
    return _v;
}

static inline VTState_Ground_t VTState_as_Ground(VTState v) {
    if (v.tag != VTState_Ground) abort();
    return v.Ground;
}

static inline VTState_Escape_t VTState_as_Escape(VTState v) {
    if (v.tag != VTState_Escape) abort();
    return v.Escape;
}

static inline VTState_EscapeIntermediate_t VTState_as_EscapeIntermediate(VTState v) {
    if (v.tag != VTState_EscapeIntermediate) abort();
    return v.EscapeIntermediate;
}

static inline VTState_CSI_t VTState_as_CSI(VTState v) {
    if (v.tag != VTState_CSI) abort();
    return v.CSI;
}

static inline VTState_OSC_t VTState_as_OSC(VTState v) {
    if (v.tag != VTState_OSC) abort();
    return v.OSC;
}

static inline VTState_DCS_t VTState_as_DCS(VTState v) {
    if (v.tag != VTState_DCS) abort();
    return v.DCS;
}
#line 26 "src/vt_parser.phc"



typedef struct {
    uint32_t codepoint;
    int remaining;
    int expected;
} Utf8Decoder;



typedef struct {
    VTState state;
    Utf8Decoder utf8;
    Terminal *term;
} VTParser;

static VTParser *vt_parser_new(Terminal *term) {
    VTParser *p = calloc(1, sizeof(VTParser));
    if (!p) return 
# 45 "src/vt_parser.phc" 3 4
                  ((void *)0)
# 45 "src/vt_parser.phc"
                      ;
    p->state = VTState_mk_Ground();
    p->term = term;
    return p;
}

static void vt_parser_free(VTParser *p) {
    free(p);
}



static void handle_csi_dispatch(Terminal *term, int *params, int param_count, int priv, char final);
static void handle_osc_dispatch(Terminal *term, const char *buf, int len);
static void handle_esc_dispatch(Terminal *term, char ch, char intermediate);
# 69 "src/vt_parser.phc"
static int utf8_decode_byte(Utf8Decoder *dec, uint8_t byte, uint32_t *out) {
    if (dec->remaining > 0) {
        if ((byte & 0xC0) != 0x80) {


            dec->remaining = 0;
            *out = 0xFFFD;
            return -1;
        }
        dec->codepoint = (dec->codepoint << 6) | (byte & 0x3F);
        dec->remaining--;
        if (dec->remaining == 0) {
            uint32_t cp = dec->codepoint;

            if ((dec->expected == 2 && cp < 0x80) ||
                (dec->expected == 3 && cp < 0x800) ||
                (dec->expected == 4 && cp < 0x10000) ||
                (cp >= 0xD800 && cp <= 0xDFFF) ||
                cp > 0x10FFFF) {
                *out = 0xFFFD;
            } else {
                *out = cp;
            }
            return 1;
        }
        return 0;
    }

    if (byte < 0x80) {
        *out = byte;
        return 1;
    } else if ((byte & 0xE0) == 0xC0) {
        dec->codepoint = byte & 0x1F;
        dec->remaining = 1;
        dec->expected = 2;
    } else if ((byte & 0xF0) == 0xE0) {
        dec->codepoint = byte & 0x0F;
        dec->remaining = 2;
        dec->expected = 3;
    } else if ((byte & 0xF8) == 0xF0) {
        dec->codepoint = byte & 0x07;
        dec->remaining = 3;
        dec->expected = 4;
    } else {

        *out = 0xFFFD;
        return 1;
    }
    return 0;
}



static const uint32_t dec_special_graphics[] = {
               0x25C6,
               0x2592,
               0x2409,
               0x240C,
               0x240D,
               0x240A,
               0x00B0,
               0x00B1,
               0x2424,
               0x240B,
               0x2518,
               0x2510,
               0x250C,
               0x2514,
               0x253C,
               0x23BA,
               0x23BB,
               0x2500,
               0x23BC,
               0x23BD,
               0x251C,
               0x2524,
               0x2534,
               0x252C,
               0x2502,
               0x2264,
               0x2265,
               0x03C0,
               0x2260,
               0x00A3,
               0x00B7,
};

static uint32_t translate_charset(Terminal *term, uint32_t cp) {
    int charset = term->charset_active == 0 ? term->charset_g0 : term->charset_g1;
    if (charset == 1 && cp >= 0x60 && cp <= 0x7E) {
        return dec_special_graphics[cp - 0x60];
    }
    return cp;
}



static void handle_c0(Terminal *term, uint8_t byte) {
    ScreenBuffer *scr = term->active;
    switch (byte) {
    case 0x07:

        break;
    case 0x08:
        screen_cursor_back(scr, 1);
        break;
    case 0x09:
        screen_tab(scr);
        break;
    case 0x0A:
    case 0x0B:
    case 0x0C:
        if (scr->cursor.row == scr->scroll_bottom) {
            Scrollback *sb = term->using_alt ? 
# 182 "src/vt_parser.phc" 3 4
                                              ((void *)0) 
# 182 "src/vt_parser.phc"
                                                   : term->scrollback;
            screen_scroll_up(scr, sb, 1);
        } else {
            screen_cursor_down(scr, 1);
        }
        break;
    case 0x0D:
        scr->cursor.col = 0;
        scr->cursor.wrap_pending = 0;
        break;
    case 0x0E:
        term->charset_active = 1;
        break;
    case 0x0F:
        term->charset_active = 0;
        break;
    }
}



static void apply_sgr(Terminal *term, int *params, int param_count) {
    Pen *pen = &term->active->cursor.pen;
    if (param_count == 0) {
        *pen = pen_default();
        return;
    }
    for (int i = 0; i < param_count; i++) {
        int p = params[i] == -1 ? 0 : params[i];
        if (p == 38 || p == 48) {
            int is_bg = (p == 48);
            int consumed = pen_apply_sgr_extended(pen, &params[i], param_count - i, is_bg);
            i += consumed - 1;
        } else {
            pen_apply_sgr(pen, p);
        }
    }
}

static int csi_param(int *params, int param_count, int index, int default_val) {
    if (index >= param_count || params[index] == -1)
        return default_val;
    return params[index];
}

static void handle_csi_dispatch(Terminal *term, int *params, int param_count, int priv, char final) {
    ScreenBuffer *scr = term->active;
    Scrollback *sb = term->using_alt ? 
# 229 "src/vt_parser.phc" 3 4
                                      ((void *)0) 
# 229 "src/vt_parser.phc"
                                           : term->scrollback;
    int n;

    if (priv) {

        switch (final) {
        case 'h':
            for (int i = 0; i < param_count; i++) {
                switch (params[i]) {
                case 1: scr->mode_app_cursor = 1; break;
                case 7: scr->cursor.autowrap = 1; break;
                case 25: break;
                case 47:
                case 1047: terminal_switch_alt(term, 1); break;
                case 1049:
                    scr->saved_cursor = scr->cursor;
                    terminal_switch_alt(term, 1);
                    break;
                case 2004: scr->mode_bracketed_paste = 1; break;
                }
            }
            break;
        case 'l':
            for (int i = 0; i < param_count; i++) {
                switch (params[i]) {
                case 1: scr->mode_app_cursor = 0; break;
                case 7: scr->cursor.autowrap = 0; break;
                case 25: break;
                case 47:
                case 1047: terminal_switch_alt(term, 0); break;
                case 1049:
                    terminal_switch_alt(term, 0);
                    scr->cursor = scr->saved_cursor;
                    break;
                case 2004: scr->mode_bracketed_paste = 0; break;
                }
            }
            break;
        }
        return;
    }

    switch (final) {
    case 'A':
        n = csi_param(params, param_count, 0, 1);
        screen_cursor_up(scr, n);
        break;
    case 'B':
        n = csi_param(params, param_count, 0, 1);
        screen_cursor_down(scr, n);
        break;
    case 'C':
        n = csi_param(params, param_count, 0, 1);
        screen_cursor_forward(scr, n);
        break;
    case 'D':
        n = csi_param(params, param_count, 0, 1);
        screen_cursor_back(scr, n);
        break;
    case 'E':
        n = csi_param(params, param_count, 0, 1);
        screen_cursor_down(scr, n);
        scr->cursor.col = 0;
        break;
    case 'F':
        n = csi_param(params, param_count, 0, 1);
        screen_cursor_up(scr, n);
        scr->cursor.col = 0;
        break;
    case 'G':
        n = csi_param(params, param_count, 0, 1);
        scr->cursor.col = n - 1;
        screen_cursor_clamp(scr);
        break;
    case 'H':
    case 'f':
        screen_cursor_set(scr,
            csi_param(params, param_count, 0, 1) - 1,
            csi_param(params, param_count, 1, 1) - 1);
        break;
    case 'J':
        screen_erase_display(scr, csi_param(params, param_count, 0, 0));
        break;
    case 'K':
        screen_erase_line(scr, csi_param(params, param_count, 0, 0));
        break;
    case 'L':
        n = csi_param(params, param_count, 0, 1);
        screen_insert_lines(scr, n);
        break;
    case 'M':
        n = csi_param(params, param_count, 0, 1);
        screen_delete_lines(scr, sb, n);
        break;
    case 'P':
        n = csi_param(params, param_count, 0, 1);
        screen_delete_chars(scr, n);
        break;
    case 'S':
        n = csi_param(params, param_count, 0, 1);
        screen_scroll_up(scr, sb, n);
        break;
    case 'T':
        n = csi_param(params, param_count, 0, 1);
        screen_scroll_down(scr, n);
        break;
    case 'X':
        n = csi_param(params, param_count, 0, 1);
        for (int i = 0; i < n && scr->cursor.col + i < scr->cols; i++) {
            *screen_cell(scr, scr->cursor.row, scr->cursor.col + i) = cell_empty();
        }
        break;
    case '@':
        n = csi_param(params, param_count, 0, 1);
        screen_insert_chars(scr, n);
        break;
    case 'd':
        n = csi_param(params, param_count, 0, 1);
        scr->cursor.row = n - 1;
        screen_cursor_clamp(scr);
        break;
    case 'm':
        apply_sgr(term, params, param_count);
        break;
    case 'r':
        {
            int top = csi_param(params, param_count, 0, 1) - 1;
            int bottom = csi_param(params, param_count, 1, scr->rows) - 1;
            if (top < 0) top = 0;
            if (bottom >= scr->rows) bottom = scr->rows - 1;
            if (top < bottom) {
                scr->scroll_top = top;
                scr->scroll_bottom = bottom;
                screen_cursor_set(scr, 0, 0);
            }
        }
        break;
    case 's':
        scr->saved_cursor = scr->cursor;
        break;
    case 'u':
        scr->cursor = scr->saved_cursor;
        screen_cursor_clamp(scr);
        break;
    }
}



static void handle_esc_dispatch(Terminal *term, char ch, char intermediate) {
    ScreenBuffer *scr = term->active;
    if (intermediate == 0) {
        switch (ch) {
        case '7':
            scr->saved_cursor = scr->cursor;
            break;
        case '8':
            scr->cursor = scr->saved_cursor;
            screen_cursor_clamp(scr);
            break;
        case 'D':
            if (scr->cursor.row == scr->scroll_bottom) {
                Scrollback *sb = term->using_alt ? 
# 391 "src/vt_parser.phc" 3 4
                                                  ((void *)0) 
# 391 "src/vt_parser.phc"
                                                       : term->scrollback;
                screen_scroll_up(scr, sb, 1);
            } else {
                screen_cursor_down(scr, 1);
            }
            break;
        case 'E':
            scr->cursor.col = 0;
            if (scr->cursor.row == scr->scroll_bottom) {
                Scrollback *sb = term->using_alt ? 
# 400 "src/vt_parser.phc" 3 4
                                                  ((void *)0) 
# 400 "src/vt_parser.phc"
                                                       : term->scrollback;
                screen_scroll_up(scr, sb, 1);
            } else {
                screen_cursor_down(scr, 1);
            }
            break;
        case 'M':
            screen_reverse_index(scr);
            break;
        case 'c':
            screen_erase_display(scr, 2);
            scr->cursor.row = 0;
            scr->cursor.col = 0;
            scr->cursor.pen = pen_default();
            scr->scroll_top = 0;
            scr->scroll_bottom = scr->rows - 1;
            scr->mode_app_cursor = 0;
            scr->mode_bracketed_paste = 0;
            break;
        }
    } else if (intermediate == '#') {
        switch (ch) {
        case '8':
            for (int r = 0; r < scr->rows; r++)
                for (int c = 0; c < scr->cols; c++)
                    screen_cell(scr, r, c)->codepoint = 'E';
            break;
        }
    } else if (intermediate == '(') {

        if (ch == '0') term->charset_g0 = 1;
        else if (ch == 'B') term->charset_g0 = 0;
    } else if (intermediate == ')') {

        if (ch == '0') term->charset_g1 = 1;
        else if (ch == 'B') term->charset_g1 = 0;
    }
}



static void handle_osc_dispatch(Terminal *term, const char *buf, int len) {
    (void)term;
    (void)buf;
    (void)len;


}



static VTState vt_feed_byte(VTParser *parser, uint8_t byte) {
    Terminal *term = parser->term;
    VTState state = parser->state;



    if (byte == 0x1B && state.tag != VTState_OSC) {
        if (parser->utf8.remaining > 0) {

            Scrollback *sb = term->using_alt ? 
# 460 "src/vt_parser.phc" 3 4
                                              ((void *)0) 
# 460 "src/vt_parser.phc"
                                                   : term->scrollback;
            screen_put_char(term->active, sb, 0xFFFD);
        }
        parser->utf8.remaining = 0;
        return VTState_mk_Escape();
    }




    if (byte < 0x20 && byte != 0x1B &&
        state.tag != VTState_OSC && state.tag != VTState_DCS) {
        handle_c0(term, byte);
        return state;
    }

    switch (state.tag) {
    case VTState_Ground: {

            uint32_t cp;
            int rc = utf8_decode_byte(&parser->utf8, byte, &cp);
            Scrollback *sb = term->using_alt ? 
# 481 "src/vt_parser.phc" 3 4
                                              ((void *)0) 
# 481 "src/vt_parser.phc"
                                                   : term->scrollback;
            if (rc == -1) {

                screen_put_char(term->active, sb, cp);

                if (utf8_decode_byte(&parser->utf8, byte, &cp) == 1) {
                    cp = translate_charset(term, cp);
                    screen_put_char(term->active, sb, cp);
                }
            } else if (rc == 1) {
                cp = translate_charset(term, cp);
                screen_put_char(term->active, sb, cp);
            }
            return VTState_mk_Ground();
        } break;
    case VTState_Escape: {
            if (byte == '[') {
                VTState s = VTState_mk_CSI(0, 0);
                memset(s.CSI.params, -1, sizeof(s.CSI.params));
                s.CSI.param_count = 0;
                s.CSI.priv = 0;
                return s;
            }
            if (byte == ']') {
                VTState s = VTState_mk_OSC(0, 0);
                memset(s.OSC.buf, 0, sizeof(s.OSC.buf));
                s.OSC.len = 0;
                s.OSC.esc_seen = 0;
                return s;
            }
            if (byte == 'P') {
                VTState s = VTState_mk_DCS(0);
                memset(s.DCS.buf, 0, sizeof(s.DCS.buf));
                s.DCS.len = 0;
                return s;
            }
            if (byte == '#' || byte == '(' || byte == ')') {
                return VTState_mk_EscapeIntermediate((char)byte);
            }

            handle_esc_dispatch(term, (char)byte, 0);
            return VTState_mk_Ground();
        } break;
    case VTState_EscapeIntermediate: { char intermediate = state.EscapeIntermediate.intermediate; {
            handle_esc_dispatch(term, (char)byte, intermediate);
            return VTState_mk_Ground();
        } break; }
    case VTState_CSI: { int *params = state.CSI.params; int param_count = state.CSI.param_count; int priv = state.CSI.priv; {
            if (byte == '?' && param_count == 0) {

                VTState s = state;
                s.CSI.priv = 1;
                return s;
            }
            if (byte >= '0' && byte <= '9') {

                VTState s = state;
                int idx = s.CSI.param_count > 0 ? s.CSI.param_count - 1 : 0;
                if (s.CSI.param_count == 0) s.CSI.param_count = 1;

                if (s.CSI.params[idx] == -1) s.CSI.params[idx] = 0;
                s.CSI.params[idx] = s.CSI.params[idx] * 10 + (byte - '0');
                return s;
            }
            if (byte == ';') {
                VTState s = state;
                if (s.CSI.param_count == 0) {

                    s.CSI.param_count = 2;
                    s.CSI.params[0] = -1;
                    s.CSI.params[1] = -1;
                } else if (s.CSI.param_count < 16) {
                    s.CSI.param_count++;
                    s.CSI.params[s.CSI.param_count - 1] = -1;
                }
                return s;
            }
            if (byte >= 0x40 && byte <= 0x7E) {

                handle_csi_dispatch(term, params, param_count, priv, (char)byte);
                return VTState_mk_Ground();
            }

            return state;
        } break; }
    case VTState_OSC: { char *buf = state.OSC.buf; int len = state.OSC.len; int esc_seen = state.OSC.esc_seen; {

            if (byte == 0x07) {
                handle_osc_dispatch(term, buf, len);
                return VTState_mk_Ground();
            }
            if (byte == 0x1B) {

                VTState s = parser->state;
                s.OSC.esc_seen = 1;
                return s;
            }
            if (esc_seen == 1 && byte == '\\') {
                handle_osc_dispatch(term, buf, len);
                return VTState_mk_Ground();
            }
            if (esc_seen == 1) {


                parser->state = VTState_mk_Escape();
                return vt_feed_byte(parser, byte);
            }

            VTState s = parser->state;
            if (s.OSC.len < 511) {
                s.OSC.buf[s.OSC.len++] = (char)byte;
            }
            return s;
        } break; }
    case VTState_DCS: { char *buf = state.DCS.buf; int len = state.DCS.len; {
            (void)buf;
            (void)len;

            if (byte == 0x1B) {
                return VTState_mk_Escape();
            }
            if (byte == 0x9C) {
                return VTState_mk_Ground();
            }

            VTState s = state;
            if (s.DCS.len < 511) {
                s.DCS.buf[s.DCS.len++] = (char)byte;
            }
            return s;
        } break; }
    default: break;
}
#line 623 "src/input.phc"

    return VTState_mk_Ground();
}


static void vt_parser_feed(VTParser *parser, const uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        parser->state = vt_feed_byte(parser, data[i]);
    }
}
# 30 "src/extension.phc" 2
# 1 "src/input.phc" 1
# 26 "src/input.phc"
typedef enum {
    InputEvent_Key,
    InputEvent_Special,
    InputEvent_Paste,
    InputEvent_Resize,
    InputEvent__COUNT
} InputEvent_Tag;

typedef struct {
    int codepoint;
    int modifiers;
} InputEvent_Key_t;

typedef struct {
    int key;
    int modifiers;
} InputEvent_Special_t;

typedef struct {
    const char *data;
    int len;
} InputEvent_Paste_t;

typedef struct {
    int cols;
    int rows;
} InputEvent_Resize_t;

typedef struct InputEvent {
    InputEvent_Tag tag;
    union {
        InputEvent_Key_t Key;
        InputEvent_Special_t Special;
        InputEvent_Paste_t Paste;
        InputEvent_Resize_t Resize;
    };
} InputEvent;

static inline InputEvent InputEvent_mk_Key(int codepoint, int modifiers) {
    InputEvent _v;
    _v.tag = InputEvent_Key;
    _v.Key.codepoint = codepoint;
    _v.Key.modifiers = modifiers;
    return _v;
}

static inline InputEvent InputEvent_mk_Special(int key, int modifiers) {
    InputEvent _v;
    _v.tag = InputEvent_Special;
    _v.Special.key = key;
    _v.Special.modifiers = modifiers;
    return _v;
}

static inline InputEvent InputEvent_mk_Paste(const char *data, int len) {
    InputEvent _v;
    _v.tag = InputEvent_Paste;
    _v.Paste.data = data;
    _v.Paste.len = len;
    return _v;
}

static inline InputEvent InputEvent_mk_Resize(int cols, int rows) {
    InputEvent _v;
    _v.tag = InputEvent_Resize;
    _v.Resize.cols = cols;
    _v.Resize.rows = rows;
    return _v;
}

static inline InputEvent_Key_t InputEvent_as_Key(InputEvent v) {
    if (v.tag != InputEvent_Key) abort();
    return v.Key;
}

static inline InputEvent_Special_t InputEvent_as_Special(InputEvent v) {
    if (v.tag != InputEvent_Special) abort();
    return v.Special;
}

static inline InputEvent_Paste_t InputEvent_as_Paste(InputEvent v) {
    if (v.tag != InputEvent_Paste) abort();
    return v.Paste;
}

static inline InputEvent_Resize_t InputEvent_as_Resize(InputEvent v) {
    if (v.tag != InputEvent_Resize) abort();
    return v.Resize;
}
#line 32 "src/render.phc"



static int utf8_encode(uint32_t cp, char *buf, int bufsize) {
    if (cp < 0x80 && bufsize >= 1) {
        buf[0] = (char)cp;
        return 1;
    } else if (cp < 0x800 && bufsize >= 2) {
        buf[0] = (char)(0xC0 | (cp >> 6));
        buf[1] = (char)(0x80 | (cp & 0x3F));
        return 2;
    } else if (cp < 0x10000 && bufsize >= 3) {
        buf[0] = (char)(0xE0 | (cp >> 12));
        buf[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
        buf[2] = (char)(0x80 | (cp & 0x3F));
        return 3;
    } else if (cp < 0x110000 && bufsize >= 4) {
        buf[0] = (char)(0xF0 | (cp >> 18));
        buf[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
        buf[2] = (char)(0x80 | ((cp >> 6) & 0x3F));
        buf[3] = (char)(0x80 | (cp & 0x3F));
        return 4;
    }
    return 0;
}






static int encode_key_event(int codepoint, int modifiers, int app_cursor,
                            char *buf, int bufsize) {
    (void)app_cursor;

    if ((modifiers & (1 << 2)) && codepoint >= 'a' && codepoint <= 'z') {
        if (bufsize < 1) return 0;
        buf[0] = (char)(codepoint - 'a' + 1);
        return 1;
    }
    if ((modifiers & (1 << 2)) && codepoint >= 'A' && codepoint <= 'Z') {
        if (bufsize < 1) return 0;
        buf[0] = (char)(codepoint - 'A' + 1);
        return 1;
    }


    int offset = 0;
    if (modifiers & (1 << 1)) {
        if (bufsize < 2) return 0;
        buf[0] = 0x1B;
        offset = 1;
    }


    if (codepoint >= 0x20) {
        int n = utf8_encode((uint32_t)codepoint, buf + offset, bufsize - offset);
        return offset + n;
    }


    if (codepoint == 0x0D || codepoint == 0x09 || codepoint == 0x08 || codepoint == 0x1B) {
        if (bufsize < offset + 1) return 0;
        buf[offset] = (char)codepoint;
        return offset + 1;
    }

    return 0;
}
# 128 "src/input.phc"
static int encode_special_key(int key, int modifiers, int app_cursor,
                              char *buf, int bufsize) {


    int mod_param = 0;
    if (modifiers & (1 << 0)) mod_param |= 1;
    if (modifiers & (1 << 1)) mod_param |= 2;
    if (modifiers & (1 << 2)) mod_param |= 4;
    if (mod_param) mod_param++;


    if (key >= 0x100 && key <= 0x103) {
        const char codes[] = "ABCD";
        char code = codes[key - 0x100];
        if (mod_param) {

            return snprintf(buf, (size_t)bufsize, "\x1b[1;%d%c", mod_param, code);
        } else if (app_cursor) {
            return snprintf(buf, (size_t)bufsize, "\x1bO%c", code);
        } else {
            return snprintf(buf, (size_t)bufsize, "\x1b[%c", code);
        }
    }


    if (key == 0x104) {
        if (mod_param) return snprintf(buf, (size_t)bufsize, "\x1b[1;%dH", mod_param);
        return snprintf(buf, (size_t)bufsize, "\x1b[H");
    }
    if (key == 0x105) {
        if (mod_param) return snprintf(buf, (size_t)bufsize, "\x1b[1;%dF", mod_param);
        return snprintf(buf, (size_t)bufsize, "\x1b[F");
    }


    if (key == 0x106) {
        if (mod_param) return snprintf(buf, (size_t)bufsize, "\x1b[2;%d~", mod_param);
        return snprintf(buf, (size_t)bufsize, "\x1b[2~");
    }
    if (key == 0x107) {
        if (mod_param) return snprintf(buf, (size_t)bufsize, "\x1b[3;%d~", mod_param);
        return snprintf(buf, (size_t)bufsize, "\x1b[3~");
    }
    if (key == 0x108) {
        if (mod_param) return snprintf(buf, (size_t)bufsize, "\x1b[5;%d~", mod_param);
        return snprintf(buf, (size_t)bufsize, "\x1b[5~");
    }
    if (key == 0x109) {
        if (mod_param) return snprintf(buf, (size_t)bufsize, "\x1b[6;%d~", mod_param);
        return snprintf(buf, (size_t)bufsize, "\x1b[6~");
    }


    if (key >= 0x110 && key <= 0x113) {
        const char codes[] = "PQRS";
        char code = codes[key - 0x110];
        if (mod_param) {

            return snprintf(buf, (size_t)bufsize, "\x1b[1;%d%c", mod_param, code);
        }
        return snprintf(buf, (size_t)bufsize, "\x1bO%c", code);
    }

    if (key >= 0x114 && key <= 0x11B) {
        static const int nums[] = {15, 17, 18, 19, 20, 21, 23, 24};
        int num = nums[key - 0x114];
        if (mod_param) return snprintf(buf, (size_t)bufsize, "\x1b[%d;%d~", num, mod_param);
        return snprintf(buf, (size_t)bufsize, "\x1b[%d~", num);
    }

    return 0;
}


static int encode_paste_start(char *buf, int bufsize) {
    return snprintf(buf, (size_t)bufsize, "\x1b[200~");
}

static int encode_paste_end(char *buf, int bufsize) {
    return snprintf(buf, (size_t)bufsize, "\x1b[201~");
}
# 31 "src/extension.phc" 2
# 1 "src/render.phc" 1
# 21 "src/render.phc"
static void color_to_tk(Color c, const char *default_color, char *out, int outsize) {
    switch (c.tag) {
    case Color_Default: {
            snprintf(out, (size_t)outsize, "%s", default_color);
        } break;
    case Color_Indexed: { uint8_t index = c.Indexed.index; {

            static const char *ansi_colors[] = {
                "#000000", "#cd0000", "#00cd00", "#cdcd00",
                "#0000ee", "#cd00cd", "#00cdcd", "#e5e5e5",
                "#7f7f7f", "#ff0000", "#00ff00", "#ffff00",
                "#5c5cff", "#ff00ff", "#00ffff", "#ffffff"
            };
            if (index < 16) {
                snprintf(out, (size_t)outsize, "%s", ansi_colors[index]);
            } else if (index < 232) {

                int ci = index - 16;
                int r = ci / 36;
                int g = (ci / 6) % 6;
                int b = ci % 6;
                snprintf(out, (size_t)outsize, "#%02x%02x%02x",
                         r ? r * 40 + 55 : 0,
                         g ? g * 40 + 55 : 0,
                         b ? b * 40 + 55 : 0);
            } else {

                int v = (index - 232) * 10 + 8;
                snprintf(out, (size_t)outsize, "#%02x%02x%02x", v, v, v);
            }
        } break; }
    case Color_RGB: { uint8_t r = c.RGB.r; uint8_t g = c.RGB.g; uint8_t b = c.RGB.b; {
            snprintf(out, (size_t)outsize, "#%02x%02x%02x", r, g, b);
        } break; }
    default: break;
}
#line 56 "src/extension.phc"
}


static int render_utf8_encode(uint32_t cp, char *buf, int bufsize) {
    if (cp < 0x80 && bufsize >= 1) {
        buf[0] = (char)cp;
        return 1;
    } else if (cp < 0x800 && bufsize >= 2) {
        buf[0] = (char)(0xC0 | (cp >> 6));
        buf[1] = (char)(0x80 | (cp & 0x3F));
        return 2;
    } else if (cp < 0x10000 && bufsize >= 3) {
        buf[0] = (char)(0xE0 | (cp >> 12));
        buf[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
        buf[2] = (char)(0x80 | (cp & 0x3F));
        return 3;
    } else if (bufsize >= 4) {
        buf[0] = (char)(0xF0 | (cp >> 18));
        buf[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
        buf[2] = (char)(0x80 | ((cp >> 6) & 0x3F));
        buf[3] = (char)(0x80 | (cp & 0x3F));
        return 4;
    }
    return 0;
}




static PyObject *render_screen(const ScreenBuffer *scr,
                               const char *default_fg, const char *default_bg) {
    PyObject *rows = PyList_New(scr->rows);
    if (!rows) return 
# 88 "src/render.phc" 3 4
                     ((void *)0)
# 88 "src/render.phc"
                         ;

    for (int r = 0; r < scr->rows; r++) {
        PyObject *spans = PyList_New(0);
        if (!spans) { Py_DECREF(((PyObject*)((rows)))); return 
# 92 "src/render.phc" 3 4
                                             ((void *)0)
# 92 "src/render.phc"
                                                 ; }


        char text[4096];
        int text_len = 0;
        Color span_fg = Color_mk_Default();
        Color span_bg = Color_mk_Default();
        uint16_t span_attrs = 0;
        int span_started = 0;

        for (int c = 0; c < scr->cols; c++) {
            const Cell *cell = screen_cell_const(scr, r, c);
            if (cell->wide_cont) continue;


            int new_span = 0;
            if (!span_started) {
                span_fg = cell->fg;
                span_bg = cell->bg;
                span_attrs = cell->attrs;
                span_started = 1;
            } else if (cell->attrs != span_attrs ||
                       !color_equal(cell->fg, span_fg) ||
                       !color_equal(cell->bg, span_bg)) {
                new_span = 1;
            }

            if (new_span && text_len > 0) {

                char fg_buf[16], bg_buf[16];
                color_to_tk(span_fg, default_fg, fg_buf, sizeof(fg_buf));
                color_to_tk(span_bg, default_bg, bg_buf, sizeof(bg_buf));
                PyObject *span = Py_BuildValue("(s#ssi)",
                    text, (Py_ssize_t)text_len, fg_buf, bg_buf, (int)span_attrs);
                if (!span) { Py_DECREF(((PyObject*)((spans)))); Py_DECREF(((PyObject*)((rows)))); return 
# 126 "src/render.phc" 3 4
                                                                      ((void *)0)
# 126 "src/render.phc"
                                                                          ; }
                if (PyList_Append(spans, span) < 0) {
                    Py_DECREF(((PyObject*)((span)))); Py_DECREF(((PyObject*)((spans)))); Py_DECREF(((PyObject*)((rows)))); return 
# 128 "src/render.phc" 3 4
                                                                              ((void *)0)
# 128 "src/render.phc"
                                                                                  ;
                }
                Py_DECREF(((PyObject*)((span))));
                text_len = 0;
                span_fg = cell->fg;
                span_bg = cell->bg;
                span_attrs = cell->attrs;
            }


            uint32_t cp = cell->codepoint;
            if (cp == 0) cp = ' ';
            int n = render_utf8_encode(cp, text + text_len, 4096 - text_len);
            text_len += n;
        }


        if (text_len > 0) {
            char fg_buf[16], bg_buf[16];
            color_to_tk(span_fg, default_fg, fg_buf, sizeof(fg_buf));
            color_to_tk(span_bg, default_bg, bg_buf, sizeof(bg_buf));
            PyObject *span = Py_BuildValue("(s#ssi)",
                text, (Py_ssize_t)text_len, fg_buf, bg_buf, (int)span_attrs);
            if (!span) { Py_DECREF(((PyObject*)((spans)))); Py_DECREF(((PyObject*)((rows)))); return 
# 151 "src/render.phc" 3 4
                                                                  ((void *)0)
# 151 "src/render.phc"
                                                                      ; }
            if (PyList_Append(spans, span) < 0) {
                Py_DECREF(((PyObject*)((span)))); Py_DECREF(((PyObject*)((spans)))); Py_DECREF(((PyObject*)((rows)))); return 
# 153 "src/render.phc" 3 4
                                                                          ((void *)0)
# 153 "src/render.phc"
                                                                              ;
            }
            Py_DECREF(((PyObject*)((span))));
        }

        PyList_SET_ITEM(((PyObject*)((rows))), (r), ((PyObject*)((spans))));
    }

    return rows;
}
# 32 "src/extension.phc" 2



typedef struct {
    PyObject ob_base;
    Terminal *term;
    VTParser *parser;
} TerminalObject;

static void Terminal_dealloc(TerminalObject *self) {
    if (self->parser) vt_parser_free(self->parser);
    if (self->term) terminal_free(self->term);
    _Py_TYPE_impl(((PyObject*)((self))))->tp_free((PyObject *)self);
}

static PyObject *Terminal_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    (void)kwds;
    int rows = 24, cols = 80;
    if (!PyArg_ParseTuple(args, "|ii", &rows, &cols))
        return 
# 51 "src/extension.phc" 3 4
              ((void *)0)
# 51 "src/extension.phc"
                  ;

    TerminalObject *self = (TerminalObject *)type->tp_alloc(type, 0);
    if (!self) return 
# 54 "src/extension.phc" 3 4
                     ((void *)0)
# 54 "src/extension.phc"
                         ;

    self->term = terminal_new(rows, cols);
    if (!self->term) {
        Py_DECREF(((PyObject*)((self))));
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate terminal");
        return 
# 60 "src/extension.phc" 3 4
              ((void *)0)
# 60 "src/extension.phc"
                  ;
    }







    self->parser = vt_parser_new(self->term);
    if (!self->parser) {
        terminal_free(self->term);
        Py_DECREF(((PyObject*)((self))));
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate parser");
        return 
# 74 "src/extension.phc" 3 4
              ((void *)0)
# 74 "src/extension.phc"
                  ;
    }

    return (PyObject *)self;
}



static PyObject *Terminal_feed(TerminalObject *self, PyObject *args) {
    
# 83 "src/extension.phc" 3 4
   ((void) (0))
# 83 "src/extension.phc"
                             ;
    const char *data;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "y#", &data, &len))
        return 
# 87 "src/extension.phc" 3 4
              ((void *)0)
# 87 "src/extension.phc"
                  ;

    { PyThreadState *_save; _save = PyEval_SaveThread();

    const uint8_t *ptr = (const uint8_t *)data;
    Py_ssize_t remaining = len;
    while (remaining > 0) {
        int chunk = remaining > 0x7FFFFFFF ? 0x7FFFFFFF : (int)remaining;
        vt_parser_feed(self->parser, ptr, chunk);
        ptr += chunk;
        remaining -= chunk;
    }
    PyEval_RestoreThread(_save); }

    return (&_Py_NoneStruct);
}



static PyObject *Terminal_get_screen(TerminalObject *self, PyObject *args) {
    const char *fg = "#ffffff";
    const char *bg = "#000000";
    if (!PyArg_ParseTuple(args, "|ss", &fg, &bg))
        return 
# 110 "src/extension.phc" 3 4
              ((void *)0)
# 110 "src/extension.phc"
                  ;

    return render_screen(self->term->active, fg, bg);
}



static PyObject *Terminal_get_cursor(TerminalObject *self, PyObject *args) {
    (void)args;
    ScreenBuffer *scr = self->term->active;
    return Py_BuildValue("(ii)", scr->cursor.row, scr->cursor.col);
}



static PyObject *Terminal_encode_key(TerminalObject *self, PyObject *args) {
    int codepoint, modifiers = 0;
    if (!PyArg_ParseTuple(args, "i|i", &codepoint, &modifiers))
        return 
# 128 "src/extension.phc" 3 4
              ((void *)0)
# 128 "src/extension.phc"
                  ;

    char buf[32];
    int app_cursor = self->term->active->mode_app_cursor;
    int n = encode_key_event(codepoint, modifiers, app_cursor, buf, sizeof(buf));
    return PyBytes_FromStringAndSize(buf, n);
}



static PyObject *Terminal_encode_special(TerminalObject *self, PyObject *args) {
    int key, modifiers = 0;
    if (!PyArg_ParseTuple(args, "i|i", &key, &modifiers))
        return 
# 141 "src/extension.phc" 3 4
              ((void *)0)
# 141 "src/extension.phc"
                  ;

    char buf[32];
    int app_cursor = self->term->active->mode_app_cursor;
    int n = encode_special_key(key, modifiers, app_cursor, buf, sizeof(buf));
    return PyBytes_FromStringAndSize(buf, n);
}



static PyObject *Terminal_encode_paste(TerminalObject *self, PyObject *args) {
    const char *data;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "s#", &data, &len))
        return 
# 155 "src/extension.phc" 3 4
              ((void *)0)
# 155 "src/extension.phc"
                  ;

    int bracketed = self->term->active->mode_bracketed_paste;
    if (!bracketed) {
        return PyBytes_FromStringAndSize(data, len);
    }


    char start[8], end[8];
    int slen = encode_paste_start(start, sizeof(start));
    int elen = encode_paste_end(end, sizeof(end));
    Py_ssize_t total = slen + len + elen;

    PyObject *result = PyBytes_FromStringAndSize(
# 168 "src/extension.phc" 3 4
                                                ((void *)0)
# 168 "src/extension.phc"
                                                    , total);
    if (!result) return 
# 169 "src/extension.phc" 3 4
                       ((void *)0)
# 169 "src/extension.phc"
                           ;
    char *buf = PyBytes_AS_STRING(((PyObject*)((result))));
    memcpy(buf, start, (size_t)slen);
    memcpy(buf + slen, data, (size_t)len);
    memcpy(buf + slen + len, end, (size_t)elen);
    return result;
}



static PyObject *Terminal_resize(TerminalObject *self, PyObject *args) {
    int rows, cols;
    if (!PyArg_ParseTuple(args, "ii", &rows, &cols))
        return 
# 182 "src/extension.phc" 3 4
              ((void *)0)
# 182 "src/extension.phc"
                  ;

    terminal_resize(self->term, rows, cols);
    return (&_Py_NoneStruct);
}



static PyObject *Terminal_get_cell(TerminalObject *self, PyObject *args) {
    int row, col;
    if (!PyArg_ParseTuple(args, "ii", &row, &col))
        return 
# 193 "src/extension.phc" 3 4
              ((void *)0)
# 193 "src/extension.phc"
                  ;

    ScreenBuffer *scr = self->term->active;
    if (row < 0 || row >= scr->rows || col < 0 || col >= scr->cols)
        return (&_Py_NoneStruct);

    const Cell *cell = screen_cell_const(scr, row, col);
    char fg_buf[16], bg_buf[16];
    color_to_tk(cell->fg, "#ffffff", fg_buf, sizeof(fg_buf));
    color_to_tk(cell->bg, "#000000", bg_buf, sizeof(bg_buf));

    return Py_BuildValue("(Issi)", cell->codepoint, fg_buf, bg_buf, (int)cell->attrs);
}



static PyObject *Terminal_get_size(TerminalObject *self, PyObject *args) {
    (void)args;
    ScreenBuffer *scr = self->term->active;
    return Py_BuildValue("(ii)", scr->rows, scr->cols);
}



static PyObject *Terminal_get_scrollback_count(TerminalObject *self, PyObject *args) {
    (void)args;
    Scrollback *sb = self->term->scrollback;
    return PyLong_FromLong(sb ? sb->count : 0);
}



static PyObject *Terminal_get_scrollback_line(TerminalObject *self, PyObject *args) {
    int index;
    if (!PyArg_ParseTuple(args, "i", &index))
        return 
# 228 "src/extension.phc" 3 4
              ((void *)0)
# 228 "src/extension.phc"
                  ;

    Scrollback *sb = self->term->scrollback;
    if (!sb) return (&_Py_NoneStruct);

    const Cell *line = scrollback_get(sb, index);
    if (!line) return (&_Py_NoneStruct);


    PyObject *spans = PyList_New(0);
    if (!spans) return 
# 238 "src/extension.phc" 3 4
                      ((void *)0)
# 238 "src/extension.phc"
                          ;

    char text[4096];
    int text_len = 0;
    Color span_fg = Color_mk_Default();
    Color span_bg = Color_mk_Default();
    uint16_t span_attrs = 0;
    int span_started = 0;

    for (int c = 0; c < sb->cols; c++) {
        const Cell *cell = &line[c];
        if (cell->wide_cont) continue;

        int new_span = 0;
        if (!span_started) {
            span_fg = cell->fg;
            span_bg = cell->bg;
            span_attrs = cell->attrs;
            span_started = 1;
        } else if (cell->attrs != span_attrs ||
                   !color_equal(cell->fg, span_fg) ||
                   !color_equal(cell->bg, span_bg)) {
            new_span = 1;
        }

        if (new_span && text_len > 0) {
            char fg_buf[16], bg_buf[16];
            color_to_tk(span_fg, "#ffffff", fg_buf, sizeof(fg_buf));
            color_to_tk(span_bg, "#000000", bg_buf, sizeof(bg_buf));
            PyObject *span = Py_BuildValue("(s#ssi)",
                text, (Py_ssize_t)text_len, fg_buf, bg_buf, (int)span_attrs);
            if (!span) { Py_DECREF(((PyObject*)((spans)))); return 
# 269 "src/extension.phc" 3 4
                                                 ((void *)0)
# 269 "src/extension.phc"
                                                     ; }
            if (PyList_Append(spans, span) < 0) {
                Py_DECREF(((PyObject*)((span)))); Py_DECREF(((PyObject*)((spans)))); return 
# 271 "src/extension.phc" 3 4
                                                         ((void *)0)
# 271 "src/extension.phc"
                                                             ;
            }
            Py_DECREF(((PyObject*)((span))));
            text_len = 0;
            span_fg = cell->fg;
            span_bg = cell->bg;
            span_attrs = cell->attrs;
        }

        uint32_t cp = cell->codepoint;
        if (cp == 0) cp = ' ';
        int n = render_utf8_encode(cp, text + text_len, 4096 - text_len);
        text_len += n;
    }

    if (text_len > 0) {
        char fg_buf[16], bg_buf[16];
        color_to_tk(span_fg, "#ffffff", fg_buf, sizeof(fg_buf));
        color_to_tk(span_bg, "#000000", bg_buf, sizeof(bg_buf));
        PyObject *span = Py_BuildValue("(s#ssi)",
            text, (Py_ssize_t)text_len, fg_buf, bg_buf, (int)span_attrs);
        if (!span) { Py_DECREF(((PyObject*)((spans)))); return 
# 292 "src/extension.phc" 3 4
                                             ((void *)0)
# 292 "src/extension.phc"
                                                 ; }
        if (PyList_Append(spans, span) < 0) {
            Py_DECREF(((PyObject*)((span)))); Py_DECREF(((PyObject*)((spans)))); return 
# 294 "src/extension.phc" 3 4
                                                     ((void *)0)
# 294 "src/extension.phc"
                                                         ;
        }
        Py_DECREF(((PyObject*)((span))));
    }

    return spans;
}



static PyMethodDef Terminal_methods[] = {
    {"feed", (PyCFunction)Terminal_feed, 0x0001,
     "Feed output bytes from the remote terminal."},
    {"get_screen", (PyCFunction)Terminal_get_screen, 0x0001,
     "Get render commands as list of rows, each row a list of (text, fg, bg, attrs) spans."},
    {"get_cursor", (PyCFunction)Terminal_get_cursor, 0x0004,
     "Get cursor position as (row, col)."},
    {"encode_key", (PyCFunction)Terminal_encode_key, 0x0001,
     "Encode a key event to bytes for the remote terminal."},
    {"encode_special", (PyCFunction)Terminal_encode_special, 0x0001,
     "Encode a special key (arrow, F-key, etc.) to bytes."},
    {"encode_paste", (PyCFunction)Terminal_encode_paste, 0x0001,
     "Encode paste data, wrapping in bracketed paste if enabled."},
    {"resize", (PyCFunction)Terminal_resize, 0x0001,
     "Resize the terminal to new dimensions."},
    {"get_cell", (PyCFunction)Terminal_get_cell, 0x0001,
     "Get cell at (row, col) as (codepoint, fg, bg, attrs)."},
    {"get_size", (PyCFunction)Terminal_get_size, 0x0004,
     "Get terminal size as (rows, cols)."},
    {"get_scrollback_count", (PyCFunction)Terminal_get_scrollback_count, 0x0004,
     "Get number of lines in scrollback buffer."},
    {"get_scrollback_line", (PyCFunction)Terminal_get_scrollback_line, 0x0001,
     "Get scrollback line by index (0=oldest). Returns list of (text, fg, bg, attrs) spans."},
    {
# 327 "src/extension.phc" 3 4
    ((void *)0)
# 327 "src/extension.phc"
        , 
# 327 "src/extension.phc" 3 4
          ((void *)0)
# 327 "src/extension.phc"
              , 0, 
# 327 "src/extension.phc" 3 4
                   ((void *)0)
# 327 "src/extension.phc"
                       }
};



static PyTypeObject TerminalType = {
    { { { (((Py_ssize_t)(3ULL << 30)) | (((Py_ssize_t)((1 << 2) | (1 << 0))) << 48)) }, (
# 333 "src/extension.phc" 3 4
   ((void *)0)
# 333 "src/extension.phc"
   ) }, (0) },
    .tp_name = "_nbsterm.Terminal",
    .tp_doc = "Terminal emulator",
    .tp_basicsize = sizeof(TerminalObject),
    .tp_flags = ( 0 | 0),
    .tp_new = Terminal_new,
    .tp_dealloc = (destructor)Terminal_dealloc,
    .tp_methods = Terminal_methods,
};



static int add_key_constants(PyObject *m) {
    if (PyModule_AddIntConstant(m, "KEY_UP", 0x100) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_DOWN", 0x101) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_RIGHT", 0x102) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_LEFT", 0x103) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_HOME", 0x104) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_END", 0x105) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_INSERT", 0x106) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_DELETE", 0x107) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_PAGEUP", 0x108) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_PAGEDOWN", 0x109) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F1", 0x110) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F2", 0x111) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F3", 0x112) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F4", 0x113) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F5", 0x114) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F6", 0x115) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F7", 0x116) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F8", 0x117) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F9", 0x118) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F10", 0x119) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F11", 0x11A) < 0) return -1;
    if (PyModule_AddIntConstant(m, "KEY_F12", 0x11B) < 0) return -1;
    if (PyModule_AddIntConstant(m, "MOD_SHIFT", (1 << 0)) < 0) return -1;
    if (PyModule_AddIntConstant(m, "MOD_ALT", (1 << 1)) < 0) return -1;
    if (PyModule_AddIntConstant(m, "MOD_CTRL", (1 << 2)) < 0) return -1;
    return 0;
}



static PyModuleDef nbsterm_module = {
    { { { (((Py_ssize_t)(3ULL << 30)) | (((Py_ssize_t)((1 << 2) | (1 << 0))) << 48)) }, (
# 377 "src/extension.phc" 3 4
   ((void *)0)
# 377 "src/extension.phc"
   ) }, 
# 377 "src/extension.phc" 3 4
   ((void *)0)
# 377 "src/extension.phc"
   , 0, 
# 377 "src/extension.phc" 3 4
   ((void *)0)
# 377 "src/extension.phc"
   , },
    "_nbsterm",
    "NBS Terminal Emulator C Extension",
    -1,
    
# 381 "src/extension.phc" 3 4
   ((void *)0)
# 381 "src/extension.phc"
       , 
# 381 "src/extension.phc" 3 4
         ((void *)0)
# 381 "src/extension.phc"
             , 
# 381 "src/extension.phc" 3 4
               ((void *)0)
# 381 "src/extension.phc"
                   , 
# 381 "src/extension.phc" 3 4
                     ((void *)0)
# 381 "src/extension.phc"
                         , 
# 381 "src/extension.phc" 3 4
                           ((void *)0)

# 382 "src/extension.phc"
};

__attribute__ ((visibility ("default"))) PyObject* PyInit__nbsterm(void) {
    PyObject *m = PyModule_Create2((&nbsterm_module), 1013);
    if (!m) return 
# 386 "src/extension.phc" 3 4
                  ((void *)0)
# 386 "src/extension.phc"
                      ;

    if (PyType_Ready(&TerminalType) < 0) return 
# 388 "src/extension.phc" 3 4
                                               ((void *)0)
# 388 "src/extension.phc"
                                                   ;
    Py_INCREF(((PyObject*)((&TerminalType))));
    if (PyModule_AddObject(m, "Terminal", (PyObject *)&TerminalType) < 0) {
        Py_DECREF(((PyObject*)((&TerminalType))));
        Py_DECREF(((PyObject*)((m))));
        return 
# 393 "src/extension.phc" 3 4
              ((void *)0)
# 393 "src/extension.phc"
                  ;
    }

    if (add_key_constants(m) < 0) {
        Py_DECREF(((PyObject*)((m))));
        return 
# 398 "src/extension.phc" 3 4
              ((void *)0)
# 398 "src/extension.phc"
                  ;
    }

    return m;
}
