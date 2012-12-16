/*
 * MATLAB Compiler: 4.17 (R2012a)
 * Date: Sat Dec 15 00:18:54 2012
 * Arguments: "-B" "macro_default" "-t" "-L" "C" "-W" "lib:libapteres" "-T"
 * "link:lib" "-h" "calcul_C.mlibmmfile.mlib" 
 */

#ifndef __libapteres_h
#define __libapteres_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_libapteres
#define PUBLIC_libapteres_C_API __global
#else
#define PUBLIC_libapteres_C_API /* No import statement needed. */
#endif

#define LIB_libapteres_C_API PUBLIC_libapteres_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libapteres
#define PUBLIC_libapteres_C_API __declspec(dllexport)
#else
#define PUBLIC_libapteres_C_API __declspec(dllimport)
#endif

#define LIB_libapteres_C_API PUBLIC_libapteres_C_API


#else

#define LIB_libapteres_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libapteres_C_API 
#define LIB_libapteres_C_API /* No special import/export declaration */
#endif

extern LIB_libapteres_C_API 
bool MW_CALL_CONV libapteresInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libapteres_C_API 
bool MW_CALL_CONV libapteresInitialize(void);

extern LIB_libapteres_C_API 
void MW_CALL_CONV libapteresTerminate(void);



extern LIB_libapteres_C_API 
void MW_CALL_CONV libapteresPrintStackTrace(void);



#ifdef __cplusplus
}
#endif
#endif
