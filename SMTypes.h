
#ifndef _SMTypes_H_
#define _SMTypes_H_

#if !defined(SMCALL)
#if defined(_WIN32)
    //! Take WIN32 platform as example
    #define SMCALL __stdcall
#else
    #define SMCALL
#endif /* _WIN32 */
#endif /* SMCALL */

#if defined _WIN32 || defined __CYGWIN__
//! Take WIN32 platform as example
#define SM_DLL_IMPORT __declspec(dllimport)
//! Take WIN32 platform as example
#define SM_DLL_EXPORT __declspec(dllexport)
//! Take WIN32 platform as example
#define SM_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define SM_DLL_IMPORT __attribute__ ((visibility ("default")))
#define SM_DLL_EXPORT __attribute__ ((visibility ("default")))
#define SM_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define SM_DLL_IMPORT
#define SM_DLL_EXPORT
#define SM_DLL_LOCAL
#endif
#endif

#ifdef SM_DLL_EXPORTS // macro VA_DLL_EXPORTS must be predefined if we are building the DLL (instead of using it).
/*!
    \brief Take WIN32 platform as example, <b style="color:#FF0000">macro VA_DLL_EXPORTS
    must be predefined if we are building the DLL (instead of using it)</b>.
*/
#define SMAPI_PORT SM_DLL_EXPORT
#else
#define SMAPI_PORT SM_DLL_IMPORT
#endif // VA_DLL_EXPORTS

#endif // _VATypes_H_
