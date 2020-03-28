// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Low-level types and utilities for porting Google Test to various
// platforms.  All macros ending with _ and symbols defined in an
// internal namespace are subject to change without notice.  Code
// outside Google Test MUST NOT USE THEM DIRECTLY.  Macros that don't
// end with _ are part of Google Test's public API and can be used by
// code outside Google Test.
//
// This file is fundamental to Google Test.  All other Google Test source
// files are expected to #include this.  Therefore, it cannot #include
// any other Google Test header.

// GOOGLETEST_CM0001 DO NOT DELETE

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_

// Environment-describing macros
// -----------------------------
//
// Google Test can be used in many different environments.  Macros in
// this section tell Google Test what kind of environment it is being
// used in, such that Google Test can provide environment-specific
// features and implementations.
//
// Google Test tries to automatically detect the properties of its
// environment, so users usually don't need to worry about these
// macros.  However, the automatic detection is not perfect.
// Sometimes it's necessary for a user to define some of the following
// macros in the build script to override Google Test's decisions.
//
// If the user doesn't define a macro in the list, Google Test will
// provide a default definition.  After this header is #included, all
// macros in this list will be defined to either 1 or 0.
//
// Notes to maintainers:
//   - Each macro here is a user-tweakable knob; do not grow the list
//     lightly.
//   - Use #if to key off these macros.  Don't use #ifdef or "#if
//     defined(...)", which will not work as these macros are ALWAYS
//     defined.
//
//   GTEST_HAS_CLONE          - Define it to 1/0 to indicate that clone(2)
//                              is/isn't available.
//   GTEST_HAS_EXCEPTIONS     - Define it to 1/0 to indicate that exceptions
//                              are enabled.
//   GTEST_HAS_POSIX_RE       - Define it to 1/0 to indicate that POSIX regular
//                              expressions are/aren't available.
//   GTEST_HAS_RTTI           - Define it to 1/0 to indicate that RTTI is/isn't
//                              enabled.
//   GTEST_HAS_STD_WSTRING    - Define it to 1/0 to indicate that
//                              std::wstring does/doesn't work (Google Test can
//                              be used where std::wstring is unavailable).
//   GTEST_HAS_SEH            - Define it to 1/0 to indicate whether the
//                              compiler supports Microsoft's "Structured
//                              Exception Handling".
//   GTEST_HAS_STREAM_REDIRECTION
//                            - Define it to 1/0 to indicate whether the
//                              platform supports I/O stream redirection using
//                              dup() and dup2().
//   GTEST_LINKED_AS_SHARED_LIBRARY
//                            - Define to 1 when compiling tests that use
//                              Google Test as a shared library (known as
//                              DLL on Windows).
//   GTEST_CREATE_SHARED_LIBRARY
//                            - Define to 1 when compiling Google Test itself
//                              as a shared library.
//   GTEST_DEFAULT_DEATH_TEST_STYLE
//                            - The default value of --gtest_death_test_style.
//                              The legacy default has been "fast" in the open
//                              source version since 2008. The recommended value
//                              is "threadsafe", and can be set in
//                              custom/gtest-port.h.

// Platform-indicating macros
// --------------------------
//
// Macros indicating the platform on which Google Test is being used
// (a macro is defined to 1 if compiled on the given platform;
// otherwise UNDEFINED -- it's never defined to 0.).  Google Test
// defines these macros automatically.  Code outside Google Test MUST
// NOT define them.
//
//   GTEST_OS_AIX      - IBM AIX
//   GTEST_OS_CYGWIN   - Cygwin
//   GTEST_OS_DRAGONFLY - DragonFlyBSD
//   GTEST_OS_FREEBSD  - FreeBSD
//   GTEST_OS_FUCHSIA  - Fuchsia
//   GTEST_OS_GNU_KFREEBSD - GNU/kFreeBSD
//   GTEST_OS_HAIKU    - Haiku
//   GTEST_OS_HPUX     - HP-UX
//   GTEST_OS_LINUX    - Linux
//     GTEST_OS_LINUX_ANDROID - Google Android
//   GTEST_OS_MAC      - Mac OS X
//     GTEST_OS_IOS    - iOS
//   GTEST_OS_NACL     - Google Native Client (NaCl)
//   GTEST_OS_NETBSD   - NetBSD
//   GTEST_OS_OPENBSD  - OpenBSD
//   GTEST_OS_OS2      - OS/2
//   GTEST_OS_QNX      - QNX
//   GTEST_OS_SOLARIS  - Sun Solaris
//   GTEST_OS_WINDOWS  - Windows (Desktop, MinGW, or Mobile)
//     GTEST_OS_WINDOWS_DESKTOP  - Windows Desktop
//     GTEST_OS_WINDOWS_MINGW    - MinGW
//     GTEST_OS_WINDOWS_MOBILE   - Windows Mobile
//     GTEST_OS_WINDOWS_PHONE    - Windows Phone
//     GTEST_OS_WINDOWS_RT       - Windows Store App/WinRT
//   GTEST_OS_ZOS      - z/OS
//
// Among the platforms, Cygwin, Linux, Mac OS X, and Windows have the
// most stable support.  Since core members of the Google Test project
// don't have access to other platforms, support for them may be less
// stable.  If you notice any problems on your platform, please notify
// googletestframework@googlegroups.com (patches for fixing them are
// even more welcome!).
//
// It is possible that none of the GTEST_OS_* macros are defined.

// Feature-indicating macros
// -------------------------
//
// Macros indicating which Google Test features are available (a macro
// is defined to 1 if the corresponding feature is supported;
// otherwise UNDEFINED -- it's never defined to 0.).  Google Test
// defines these macros automatically.  Code outside Google Test MUST
// NOT define them.
//
// These macros are public so that portable tests can be written.
// Such tests typically surround code using a feature with an #if
// which controls that code.  For example:
//
// #if GTEST_HAS_DEATH_TEST
//   EXPECT_DEATH(DoSomethingDeadly());
// #endif
//
//   GTEST_HAS_DEATH_TEST   - death tests
//   GTEST_HAS_TYPED_TEST   - typed tests
//   GTEST_HAS_TYPED_TEST_P - type-parameterized tests
//   GOOGLETEST_CM0007 DO NOT DELETE
//   GTEST_USES_POSIX_RE    - enhanced POSIX regex is used. Do not confuse with
//                            GTEST_HAS_POSIX_RE (see above) which users can
//                            define themselves.
//   GTEST_USES_SIMPLE_RE   - our own simple regex is used;
//                            the above RE\b(s) are mutually exclusive.

// Misc public macros
// ------------------
//
//   GTEST_FLAG(flag_name)  - references the variable corresponding to
//                            the given Google Test flag.

// Internal utilities
// ------------------
//
// The following macros and utilities are for Google Test's INTERNAL
// use only.  Code outside Google Test MUST NOT USE THEM DIRECTLY.
//
// Macros for basic C++ coding:
//   GTEST_AMBIGUOUS_ELSE_BLOCKER_ - for disabling a gcc warning.
//   GTEST_ATTRIBUTE_UNUSED_  - declares that a class' instances or a
//                              variable don't have to be used.
//   GTEST_DISALLOW_ASSIGN_   - disables copy operator=.
//   GTEST_DISALLOW_COPY_AND_ASSIGN_ - disables copy ctor and operator=.
//   GTEST_DISALLOW_MOVE_ASSIGN_   - disables move operator=.
//   GTEST_DISALLOW_MOVE_AND_ASSIGN_ - disables move ctor and operator=.
//   GTEST_MUST_USE_RESULT_   - declares that a function's result must be used.
//   GTEST_INTENTIONAL_CONST_COND_PUSH_ - start code section where MSVC C4127 is
//                                        suppressed (constant conditional).
//   GTEST_INTENTIONAL_CONST_COND_POP_  - finish code section where MSVC C4127
//                                        is suppressed.
//   GTEST_INTERNAL_HAS_STRING_VIEW - for enabling Matcher<std::string_view> or
//                                    Matcher<absl::string_view>
//                                    specializations.
//
// Synchronization:
//   GetThreadCount() - synchronization primitives.
//
// Regular expressions:
//   RE             - a simple regular expression class using the POSIX
//                    Extended Regular Expression syntax on UNIX-like platforms
//                    GOOGLETEST_CM0008 DO NOT DELETE
//                    or a reduced regular exception syntax on other
//                    platforms, including Windows.
// Logging:
//   GTEST_LOG_()   - logs messages at the specified severity level.
//   LogToStderr()  - directs all log messages to stderr.
//   FlushInfoLog() - flushes informational log messages.
//
// Stdout and stderr capturing:
//   CaptureStdout()     - starts capturing stdout.
//   GetCapturedStdout() - stops capturing stdout and returns the captured
//                         string.
//   CaptureStderr()     - starts capturing stderr.
//   GetCapturedStderr() - stops capturing stderr and returns the captured
//                         string.
//
// Integer types:
//   TypeWithSize   - maps an integer to a int type.
//   TimeInMillis   - integers of known sizes.
//   BiggestInt     - the biggest signed integer type.
//
// Command-line utilities:
//   GTEST_DECLARE_*()  - declares a flag.
//   GTEST_DEFINE_*()   - defines a flag.
//   GetInjectableArgvs() - returns the command line as a vector of strings.
//
// Environment variable utilities:
//   GetEnv()             - gets the value of an environment variable.
//   BoolFromGTestEnv()   - parses a bool environment variable.
//   Int32FromGTestEnv()  - parses an int32_t environment variable.
//   StringFromGTestEnv() - parses a string environment variable.
//
// Deprecation warnings:
//   GTEST_INTERNAL_DEPRECATED(message) - attribute marking a function as
//                                        deprecated; calling a marked function
//                                        should generate a compiler warning

#include <ctype.h>   // for isspace, etc
#include <stddef.h>  // for ptrdiff_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cerrno>
#include <cstdint>
#include <limits>
#include <type_traits>

#ifndef _WIN32_WCE
# include <sys/types.h>
# include <sys/stat.h>
#endif  // !_WIN32_WCE

#if defined __APPLE__
# include <AvailabilityMacros.h>
# include <TargetConditionals.h>
#endif

#include <iostream>  // NOLINT
#include <memory>
#include <string>  // NOLINT
#include <tuple>
#include <vector>  // NOLINT

#include "gtest/internal/custom/gtest-port.h"
#include "gtest/internal/gtest-port-arch.h"

#if !defined(GTEST_DEV_EMAIL_)
# define GTEST_DEV_EMAIL_ "googletestframework@@googlegroups.com"
# define GTEST_FLAG_PREFIX_ "gtest_"
# define GTEST_FLAG_PREFIX_DASH_ "gtest-"
# define GTEST_FLAG_PREFIX_UPPER_ "GTEST_"
# define GTEST_NAME_ "Google Test"
# define GTEST_PROJECT_URL_ "https://github.com/google/googletest/"
#endif  // !defined(GTEST_DEV_EMAIL_)

#if !defined(GTEST_INIT_GOOGLE_TEST_NAME_)
# define GTEST_INIT_GOOGLE_TEST_NAME_ "testing::InitGoogleTest"
#endif  // !defined(GTEST_INIT_GOOGLE_TEST_NAME_)

// Determines the version of gcc that is used to compile this.
#ifdef __GNUC__
// 40302 means version 4.3.2.
# define GTEST_GCC_VER_ \
    (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)
#endif  // __GNUC__

// Macros for disabling Microsoft Visual C++ warnings.
//
//   GTEST_DISABLE_MSC_WARNINGS_PUSH_(4800 4385)
//   /* code that triggers warnings C4800 and C4385 */
//   GTEST_DISABLE_MSC_WARNINGS_POP_()
#if defined(_MSC_VER)
# define GTEST_DISABLE_MSC_WARNINGS_PUSH_(warnings) \
    __pragma(warning(push))                        \
    __pragma(warning(disable: warnings))
# define GTEST_DISABLE_MSC_WARNINGS_POP_()          \
    __pragma(warning(pop))
#else
// Not all compilers are MSVC
# define GTEST_DISABLE_MSC_WARNINGS_PUSH_(warnings)
# define GTEST_DISABLE_MSC_WARNINGS_POP_()
#endif

// Clang on Windows does not understand MSVC's pragma warning.
// We need clang-specific way to disable function deprecation warning.
#ifdef __clang__
# define GTEST_DISABLE_MSC_DEPRECATED_PUSH_()                         \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-implementations\"")
#define GTEST_DISABLE_MSC_DEPRECATED_POP_() \
    _Pragma("clang diagnostic pop")
#else
# define GTEST_DISABLE_MSC_DEPRECATED_PUSH_() \
    GTEST_DISABLE_MSC_WARNINGS_PUSH_(4996)
# define GTEST_DISABLE_MSC_DEPRECATED_POP_() \
    GTEST_DISABLE_MSC_WARNINGS_POP_()
#endif

// Brings in definitions for functions used in the testing::internal::posix
// namespace (read, write, close, chdir, isatty, stat). We do not currently
// use them on Windows Mobile.
#if GTEST_OS_WINDOWS
# if !GTEST_OS_WINDOWS_MOBILE
#  include <direct.h>
#  include <io.h>
# endif
#else
// This assumes that non-Windows OSes provide unistd.h. For OSes where this
// is not the case, we need to include headers that provide the functions
// mentioned above.
# include <unistd.h>
# include <strings.h>
#endif  // GTEST_OS_WINDOWS

#if GTEST_OS_LINUX_ANDROID
// Used to define __ANDROID_API__ matching the target NDK API level.
#  include <android/api-level.h>  // NOLINT
#endif

// Defines this to true if and only if Google Test can use POSIX regular
// expressions.
#ifndef GTEST_HAS_POSIX_RE
# if GTEST_OS_LINUX_ANDROID
// On Android, <regex.h> is only available starting with Gingerbread.
#  define GTEST_HAS_POSIX_RE (__ANDROID_API__ >= 9)
# else
#  define GTEST_HAS_POSIX_RE (!GTEST_OS_WINDOWS)
# endif
#endif

#if GTEST_USES_PCRE
// The appropriate headers have already been included.

#elif GTEST_HAS_POSIX_RE

// On some platforms, <regex.h> needs someone to define size_t, and
// won't compile otherwise.  We can #include it here as we already
// included <stdlib.h>, which is guaranteed to define size_t through
// <stddef.h>.
# include <regex.h>  // NOLINT

# define GTEST_USES_POSIX_RE 1

#elif GTEST_OS_WINDOWS

// <regex.h> is not available on Windows.  Use our own simple regex
// implementation instead.
# define GTEST_USES_SIMPLE_RE 1

#else

// <regex.h> may not be available on this platform.  Use our own
// simple regex implementation instead.
# define GTEST_USES_SIMPLE_RE 1

#endif  // GTEST_USES_PCRE

#ifndef GTEST_HAS_EXCEPTIONS
// The user didn't tell us whether exceptions are enabled, so we need
// to figure it out.
# if defined(_MSC_VER) && defined(_CPPUNWIND)
// MSVC defines _CPPUNWIND to 1 if and only if exceptions are enabled.
#  define GTEST_HAS_EXCEPTIONS 1
# elif defined(__BORLANDC__)
// C++Builder's implementation of the STL uses the _HAS_EXCEPTIONS
// macro to enable exceptions, so we'll do the same.
// Assumes that exceptions are enabled by default.
#  ifndef _HAS_EXCEPTIONS
#   define _HAS_EXCEPTIONS 1
#  endif  // _HAS_EXCEPTIONS
#  define GTEST_HAS_EXCEPTIONS _HAS_EXCEPTIONS
# elif defined(__clang__)
// clang defines __EXCEPTIONS if and only if exceptions are enabled before clang
// 220714, but if and only if cleanups are enabled after that. In Obj-C++ files,
// there can be cleanups for ObjC exceptions which also need cleanups, even if
// C++ exceptions are disabled. clang has __has_feature(cxx_exceptions) which
// checks for C++ exceptions starting at clang r206352, but which checked for
// cleanups prior to that. To reliably check for C++ exception availability with
// clang, check for
// __EXCEPTIONS && __has_feature(cxx_exceptions).
#  define GTEST_HAS_EXCEPTIONS (__EXCEPTIONS && __has_feature(cxx_exceptions))
# elif defined(__GNUC__) && __EXCEPTIONS
// gcc defines __EXCEPTIONS to 1 if and only if exceptions are enabled.
#  define GTEST_HAS_EXCEPTIONS 1
# elif defined(__SUNPRO_CC)
// Sun Pro CC supports exceptions.  However, there is no compile-time way of
// detecting whether they are enabled or not.  Therefore, we assume that
// they are enabled unless the user tells us otherwise.
#  define GTEST_HAS_EXCEPTIONS 1
# elif defined(__IBMCPP__) && __EXCEPTIONS
// xlC defines __EXCEPTIONS to 1 if and only if exceptions are enabled.
#  define GTEST_HAS_EXCEPTIONS 1
# elif defined(__HP_aCC)
// Exception handling is in effect by default in HP aCC compiler. It has to
// be turned of by +noeh compiler option if desired.
#  define GTEST_HAS_EXCEPTIONS 1
# else
// For other compilers, we assume exceptions are disabled to be
// conservative.
#  define GTEST_HAS_EXCEPTIONS 0
# endif  // defined(_MSC_VER) || defined(__BORLANDC__)
#endif  // GTEST_HAS_EXCEPTIONS

#ifndef GTEST_HAS_STD_WSTRING
// The user didn't tell us whether ::std::wstring is available, so we need
// to figure it out.
// Cygwin 1.7 and below doesn't support ::std::wstring.
// Solaris' libc++ doesn't support it either.  Android has
// no support for it at least as recent as Froyo (2.2).
#define GTEST_HAS_STD_WSTRING                                         \
  (!(GTEST_OS_LINUX_ANDROID || GTEST_OS_CYGWIN || GTEST_OS_SOLARIS || \
     GTEST_OS_HAIKU || GTEST_OS_ESP32 || GTEST_OS_ESP8266))

#endif  // GTEST_HAS_STD_WSTRING

// Determines whether RTTI is available.
#ifndef GTEST_HAS_RTTI
// The user didn't tell us whether RTTI is enabled, so we need to
// figure it out.

# ifdef _MSC_VER

#ifdef _CPPRTTI  // MSVC defines this macro if and only if RTTI is enabled.
#   define GTEST_HAS_RTTI 1
#  else
#   define GTEST_HAS_RTTI 0
#  endif

// Starting with version 4.3.2, gcc defines __GXX_RTTI if and only if RTTI is
// enabled.
# elif defined(__GNUC__)

#  ifdef __GXX_RTTI
// When building against STLport with the Android NDK and with
// -frtti -fno-exceptions, the build fails at link time with undefined
// references to __cxa_bad_typeid. Note sure if STL or toolchain bug,
// so disable RTTI when detected.
#   if GTEST_OS_LINUX_ANDROID && defined(_STLPORT_MAJOR) && \
       !defined(__EXCEPTIONS)
#    define GTEST_HAS_RTTI 0
#   else
#    define GTEST_HAS_RTTI 1
#   endif  // GTEST_OS_LINUX_ANDROID && __STLPORT_MAJOR && !__EXCEPTIONS
#  else
#   define GTEST_HAS_RTTI 0
#  endif  // __GXX_RTTI

// Clang defines __GXX_RTTI starting with version 3.0, but its manual recommends
// using has_feature instead. has_feature(cxx_rtti) is supported since 2.7, the
// first version with C++ support.
# elif defined(__clang__)

#  define GTEST_HAS_RTTI __has_feature(cxx_rtti)

// Starting with version 9.0 IBM Visual Age defines __RTTI_ALL__ to 1 if
// both the typeid and dynamic_cast features are present.
# elif defined(__IBMCPP__) && (__IBMCPP__ >= 900)

#  ifdef __RTTI_ALL__
#   define GTEST_HAS_RTTI 1
#  else
#   define GTEST_HAS_RTTI 0
#  endif

# else

// For all other compilers, we assume RTTI is enabled.
#  define GTEST_HAS_RTTI 1

# endif  // _MSC_VER

#endif  // GTEST_HAS_RTTI

// It's this header's responsibility to #include <typeinfo> when RTTI
// is enabled.
#if GTEST_HAS_RTTI
# include <typeinfo>
#endif

// Determines whether clone(2) is supported.
// Usually it will only be available on Linux, excluding
// Linux on the Itanium architecture.
// Also see http://linux.die.net/man/2/clone.
#ifndef GTEST_HAS_CLONE
// The user didn't tell us, so we need to figure it out.

# if GTEST_OS_LINUX && !defined(__ia64__)
#  if GTEST_OS_LINUX_ANDROID
// On Android, clone() became available at different API levels for each 32-bit
// architecture.
#    if defined(__LP64__) || \
        (defined(__arm__) && __ANDROID_API__ >= 9) || \
        (defined(__mips__) && __ANDROID_API__ >= 12) || \
        (defined(__i386__) && __ANDROID_API__ >= 17)
#     define GTEST_HAS_CLONE 1
#    else
#     define GTEST_HAS_CLONE 0
#    endif
#  else
#   define GTEST_HAS_CLONE 1
#  endif
# else
#  define GTEST_HAS_CLONE 0
# endif  // GTEST_OS_LINUX && !defined(__ia64__)

#endif  // GTEST_HAS_CLONE

// Determines whether to support stream redirection. This is used to test
// output correctness and to implement death tests.
#ifndef GTEST_HAS_STREAM_REDIRECTION
// By default, we assume that stream redirection is supported on all
// platforms except known mobile ones.
#if GTEST_OS_WINDOWS_MOBILE || GTEST_OS_WINDOWS_PHONE || \
    GTEST_OS_WINDOWS_RT || GTEST_OS_ESP8266
#  define GTEST_HAS_STREAM_REDIRECTION 0
# else
#  define GTEST_HAS_STREAM_REDIRECTION 1
# endif  // !GTEST_OS_WINDOWS_MOBILE
#endif  // GTEST_HAS_STREAM_REDIRECTION

// Determines whether to support death tests.
// pops up a dialog window that cannot be suppressed programmatically.
#if (GTEST_OS_LINUX || GTEST_OS_CYGWIN || GTEST_OS_SOLARIS ||             \
     (GTEST_OS_MAC && !GTEST_OS_IOS) ||                                   \
     (GTEST_OS_WINDOWS_DESKTOP && _MSC_VER) || GTEST_OS_WINDOWS_MINGW ||  \
     GTEST_OS_AIX || GTEST_OS_HPUX || GTEST_OS_OPENBSD || GTEST_OS_QNX || \
     GTEST_OS_FREEBSD || GTEST_OS_NETBSD || GTEST_OS_FUCHSIA ||           \
     GTEST_OS_DRAGONFLY || GTEST_OS_GNU_KFREEBSD || GTEST_OS_HAIKU)
# define GTEST_HAS_DEATH_TEST 1
#endif

// Determines whether to support type-driven tests.

// Typed tests need <typeinfo> and variadic macros, which GCC, VC++ 8.0,
// Sun Pro CC, IBM Visual Age, and HP aCC support.
#if defined(__GNUC__) || defined(_MSC_VER) || defined(__SUNPRO_CC) || \
    defined(__IBMCPP__) || defined(__HP_aCC)
# define GTEST_HAS_TYPED_TEST 1
# define GTEST_HAS_TYPED_TEST_P 1
#endif

// Determines whether the system compiler uses UTF-16 for encoding wide strings.
#define GTEST_WIDE_STRING_USES_UTF16_ \
  (GTEST_OS_WINDOWS || GTEST_OS_CYGWIN || GTEST_OS_AIX || GTEST_OS_OS2)

// Determines whether test results can be streamed to a socket.
#if GTEST_OS_LINUX || GTEST_OS_GNU_KFREEBSD || GTEST_OS_DRAGONFLY || \
    GTEST_OS_FREEBSD || GTEST_OS_NETBSD || GTEST_OS_OPENBSD
# define GTEST_CAN_STREAM_RESULTS_ 1
#endif

// Defines some utility macros.

// The GNU compiler emits a warning if nested "if" statements are followed by
// an "else" statement and braces are not used to explicitly disambiguate the
// "else" binding.  This leads to problems with code like:
//
//   if (gate)
//     ASSERT_*(condition) << "Some message";
//
// The "switch (0) case 0:" idiom is used to suppress this.
#ifdef __INTEL_COMPILER
# define GTEST_AMBIGUOUS_ELSE_BLOCKER_
#else
# define GTEST_AMBIGUOUS_ELSE_BLOCKER_ switch (0) case 0: default:  // NOLINT
#endif

// Use this annotation at the end of a struct/class definition to
// prevent the compiler from optimizing away instances that are never
// used.  This is useful when all interesting logic happens inside the
// c'tor and / or d'tor.  Example:
//
//   struct Foo {
//     Foo() { ... }
//   } GTEST_ATTRIBUTE_UNUSED_;
//
// Also use it after a variable or parameter declaration to tell the
// compiler the variable/parameter does not have to be used.
#if defined(__GNUC__) && !defined(COMPILER_ICC)
# define GTEST_ATTRIBUTE_UNUSED_ __attribute__ ((unused))
#elif defined(__clang__)
# if __has_attribute(unused)
#  define GTEST_ATTRIBUTE_UNUSED_ __attribute__ ((unused))
# endif
#endif
#ifndef GTEST_ATTRIBUTE_UNUSED_
# define GTEST_ATTRIBUTE_UNUSED_
#endif

// Use this annotation before a function that takes a printf format string.
#if (defined(__GNUC__) || defined(__clang__)) && !defined(COMPILER_ICC)
# if defined(__MINGW_PRINTF_FORMAT)
// MinGW has two different printf implementations. Ensure the format macro
// matches the selected implementation. See
// https://sourceforge.net/p/mingw-w64/wiki2/gnu%20printf/.
#  define GTEST_ATTRIBUTE_PRINTF_(string_index, first_to_check) \
       __attribute__((__format__(__MINGW_PRINTF_FORMAT, string_index, \
                                 first_to_check)))
# else
#  define GTEST_ATTRIBUTE_PRINTF_(string_index, first_to_check) \
       __attribute__((__format__(__printf__, string_index, first_to_check)))
# endif
#else
# define GTEST_ATTRIBUTE_PRINTF_(string_index, first_to_check)
#endif


// A macro to disallow copy operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_ASSIGN_(type) \
  type& operator=(type const &) = delete

// A macro to disallow copy constructor and operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_COPY_AND_ASSIGN_(type) \
  type(type const &) = delete; \
  GTEST_DISALLOW_ASSIGN_(type)

// A macro to disallow move operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_MOVE_ASSIGN_(type) \
  type& operator=(type &&) noexcept = delete

// A macro to disallow move constructor and operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_MOVE_AND_ASSIGN_(type) \
  type(type &&) noexcept = delete; \
  GTEST_DISALLOW_MOVE_ASSIGN_(type)

// Tell the compiler to warn about unused return values for functions declared
// with this macro.  The macro should be used on function declarations
// following the argument list:
//
//   Sprocket* AllocateSprocket() GTEST_MUST_USE_RESULT_;
#if defined(__GNUC__) && !defined(COMPILER_ICC)
# define GTEST_MUST_USE_RESULT_ __attribute__ ((warn_unused_result))
#else
# define GTEST_MUST_USE_RESULT_
#endif  // __GNUC__ && !COMPILER_ICC

// MS C++ compiler emits warning when a conditional expression is compile time
// constant. In some contexts this warning is false positive and needs to be
// suppressed. Use the following two macros in such cases:
//
// GTEST_INTENTIONAL_CONST_COND_PUSH_()
// while (true) {
// GTEST_INTENTIONAL_CONST_COND_POP_()
// }
# define GTEST_INTENTIONAL_CONST_COND_PUSH_() \
    GTEST_DISABLE_MSC_WARNINGS_PUSH_(4127)
# define GTEST_INTENTIONAL_CONST_COND_POP_() \
    GTEST_DISABLE_MSC_WARNINGS_POP_()

// Determine whether the compiler supports Microsoft's Structured Exception
// Handling.  This is supported by several Windows compilers but generally
// does not exist on any other system.
#ifndef GTEST_HAS_SEH
// The user didn't tell us, so we need to figure it out.

# if defined(_MSC_VER) || defined(__BORLANDC__)
// These two compilers are known to support SEH.
#  define GTEST_HAS_SEH 1
# else
// Assume no SEH.
#  define GTEST_HAS_SEH 0
# endif

#endif  // GTEST_HAS_SEH

// GTEST_API_ qualifies all symbols that must be exported. The definitions below
// are guarded by #ifndef to give embedders a chance to define GTEST_API_ in
// gtest/internal/custom/gtest-port.h
#ifndef GTEST_API_

#ifdef _MSC_VER
# if GTEST_LINKED_AS_SHARED_LIBRARY
#  define GTEST_API_ __declspec(dllimport)
# elif GTEST_CREATE_SHARED_LIBRARY
#  define GTEST_API_ __declspec(dllexport)
# endif
#elif __GNUC__ >= 4 || defined(__clang__)
# define GTEST_API_ __attribute__((visibility ("default")))
#endif  // _MSC_VER

#endif  // GTEST_API_

#ifndef GTEST_API_
# define GTEST_API_
#endif  // GTEST_API_

#ifndef GTEST_DEFAULT_DEATH_TEST_STYLE
# define GTEST_DEFAULT_DEATH_TEST_STYLE  "fast"
#endif  // GTEST_DEFAULT_DEATH_TEST_STYLE

#ifdef __GNUC__
// Ask the compiler to never inline a given function.
# define GTEST_NO_INLINE_ __attribute__((noinline))
#else
# define GTEST_NO_INLINE_
#endif

// _LIBCPP_VERSION is defined by the libc++ library from the LLVM project.
#if !defined(GTEST_HAS_CXXABI_H_)
# if defined(__GLIBCXX__) || (defined(_LIBCPP_VERSION) && !defined(_MSC_VER))
#  define GTEST_HAS_CXXABI_H_ 1
# else
#  define GTEST_HAS_CXXABI_H_ 0
# endif
#endif

// A function level attribute to disable checking for use of uninitialized
// memory when built with MemorySanitizer.
#if defined(__clang__)
# if __has_feature(memory_sanitizer)
#  define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_ \
       __attribute__((no_sanitize_memory))
# else
#  define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_
# endif  // __has_feature(memory_sanitizer)
#else
# define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_
#endif  // __clang__

// A function level attribute to disable AddressSanitizer instrumentation.
#if defined(__clang__)
# if __has_feature(address_sanitizer)
#  define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_ \
       __attribute__((no_sanitize_address))
# else
#  define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_
# endif  // __has_feature(address_sanitizer)
#else
# define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_
#endif  // __clang__

// A function level attribute to disable HWAddressSanitizer instrumentation.
#if defined(__clang__)
# if __has_feature(hwaddress_sanitizer)
#  define GTEST_ATTRIBUTE_NO_SANITIZE_HWADDRESS_ \
       __attribute__((no_sanitize("hwaddress")))
# else
#  define GTEST_ATTRIBUTE_NO_SANITIZE_HWADDRESS_
# endif  // __has_feature(hwaddress_sanitizer)
#else
# define GTEST_ATTRIBUTE_NO_SANITIZE_HWADDRESS_
#endif  // __clang__

// A function level attribute to disable ThreadSanitizer instrumentation.
#if defined(__clang__)
# if __has_feature(thread_sanitizer)
#  define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_ \
       __attribute__((no_sanitize_thread))
# else
#  define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_
# endif  // __has_feature(thread_sanitizer)
#else
# define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_
#endif  // __clang__

namespace testing {

class Message;

// Legacy imports for backwards compatibility.
// New code should use std:: names directly.
using std::get;
using std::make_tuple;
using std::tuple;
using std::tuple_element;
using std::tuple_size;

namespace internal {

// A secret type that Google Test users don't know about.  It has no
// definition on purpose.  Therefore it's impossible to create a
// Secret object, which is what we want.
class Secret;

// The GTEST_COMPILE_ASSERT_ is a legacy macro used to verify that a compile
// time expression is true (in new code, use static_assert instead). For
// example, you could use it to verify the size of a static array:
//
//   GTEST_COMPILE_ASSERT_(GTEST_ARRAY_SIZE_(names) == NUM_NAMES,
//                         names_incorrect_size);
//
// The second argument to the macro must be a valid C++ identifier. If the
// expression is false, compiler will issue an error containing this identifier.
#define GTEST_COMPILE_ASSERT_(expr, msg) static_assert(expr, #msg)

// A helper for suppressing warnings on constant condition.  It just
// returns 'condition'.
GTEST_API_ bool IsTrue(bool condition);

// Defines RE.

#if GTEST_USES_PCRE
// if used, PCRE is injected by custom/gtest-port.h
#elif GTEST_USES_POSIX_RE || GTEST_USES_SIMPLE_RE

// A simple C++ wrapper for <regex.h>.  It uses the POSIX Extended
// Regular Expression syntax.
class GTEST_API_ RE {
 public:
  // A copy constructor is required by the Standard to initialize object
  // references from r-values.
  RE(const RE& other) { Init(other.pattern()); }

  // Constructs an RE from a string.
  RE(const ::std::string& regex) { Init(regex.c_str()); }  // NOLINT

  RE(const char* regex) { Init(regex); }  // NOLINT
  ~RE();

  // Returns the string representation of the regex.
  const char* pattern() const { return pattern_; }

  // FullMatch(str, re) returns true if and only if regular expression re
  // matches the entire str.
  // PartialMatch(str, re) returns true if and only if regular expression re
  // matches a substring of str (including str itself).
  static bool FullMatch(const ::std::string& str, const RE& re) {
    return FullMatch(str.c_str(), re);
  }
  static bool PartialMatch(const ::std::string& str, const RE& re) {
    return PartialMatch(str.c_str(), re);
  }

  static bool FullMatch(const char* str, const RE& re);
  static bool PartialMatch(const char* str, const RE& re);

 private:
  void Init(const char* regex);
  const char* pattern_;
  bool is_valid_;

# if GTEST_USES_POSIX_RE

  regex_t full_regex_;     // For FullMatch().
  regex_t partial_regex_;  // For PartialMatch().

# else  // GTEST_USES_SIMPLE_RE

  const char* full_pattern_;  // For FullMatch();

# endif

  GTEST_DISALLOW_ASSIGN_(RE);
};

#endif  // GTEST_USES_PCRE

// Formats a source file path and a line number as they would appear
// in an error message from the compiler used to compile this code.
GTEST_API_ ::std::string FormatFileLocation(const char* file, int line);

// Formats a file location for compiler-independent XML output.
// Although this function is not platform dependent, we put it next to
// FormatFileLocation in order to contrast the two functions.
GTEST_API_ ::std::string FormatCompilerIndependentFileLocation(const char* file,
                                                               int line);

// Defines logging utilities:
//   GTEST_LOG_(severity) - logs messages at the specified severity level. The
//                          message itself is streamed into the macro.
//   LogToStderr()  - directs all log messages to stderr.
//   FlushInfoLog() - flushes informational log messages.

enum GTestLogSeverity {
  GTEST_INFO,
  GTEST_WARNING,
  GTEST_ERROR,
  GTEST_FATAL
};

// Formats log entry severity, provides a stream object for streaming the
// log message, and terminates the message with a newline when going out of
// scope.
class GTEST_API_ GTestLog {
 public:
  GTestLog(GTestLogSeverity severity, const char* file, int line);

  // Flushes the buffers and, if severity is GTEST_FATAL, aborts the program.
  ~GTestLog();

  ::std::ostream& GetStream() { return ::std::cerr; }

 private:
  const GTestLogSeverity severity_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(GTestLog);
};

#if !defined(GTEST_LOG_)

# define GTEST_LOG_(severity) \
    ::testing::internal::GTestLog(::testing::internal::GTEST_##severity, \
                                  __FILE__, __LINE__).GetStream()

inline void LogToStderr() {}
inline void FlushInfoLog() { fflush(nullptr); }

#endif  // !defined(GTEST_LOG_)

#if !defined(GTEST_CHECK_)
// INTERNAL IMPLEMENTATION - DO NOT USE.
//
// GTEST_CHECK_ is an all-mode assert. It aborts the program if the condition
// is not satisfied.
//  Synopsys:
//    GTEST_CHECK_(boolean_condition);
//     or
//    GTEST_CHECK_(boolean_condition) << "Additional message";
//
//    This checks the condition and if the condition is not satisfied
//    it prints message about the condition violation, including the
//    condition itself, plus additional message streamed into it, if any,
//    and then it aborts the program. It aborts the program irrespective of
//    whether it is built in the debug mode or not.
# define GTEST_CHECK_(condition) \
    GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
    if (::testing::internal::IsTrue(condition)) \
      ; \
    else \
      GTEST_LOG_(FATAL) << "Condition " #condition " failed. "
#endif  // !defined(GTEST_CHECK_)

// An all-mode assert to verify that the given POSIX-style function
// call returns 0 (indicating success).  Known limitation: this
// doesn't expand to a balanced 'if' statement, so enclose the macro
// in {} if you need to use it as the only statement in an 'if'
// branch.
#define GTEST_CHECK_POSIX_SUCCESS_(posix_call) \
  if (const int gtest_error = (posix_call)) \
    GTEST_LOG_(FATAL) << #posix_call << "failed with error " \
                      << gtest_error

// Transforms "T" into "const T&" according to standard reference collapsing
// rules (this is only needed as a backport for C++98 compilers that do not
// support reference collapsing). Specifically, it transforms:
//
//   char         ==> const char&
//   const char   ==> const char&
//   char&        ==> char&
//   const char&  ==> const char&
//
// Note that the non-const reference will not have "const" added. This is
// standard, and necessary so that "T" can always bind to "const T&".
template <typename T>
struct ConstRef { typedef const T& type; };
template <typename T>
struct ConstRef<T&> { typedef T& type; };

// The argument T must depend on some template parameters.
#define GTEST_REFERENCE_TO_CONST_(T) \
  typename ::testing::internal::ConstRef<T>::type

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Use ImplicitCast_ as a safe version of static_cast for upcasting in
// the type hierarchy (e.g. casting a Foo* to a SuperclassOfFoo* or a
// const Foo*).  When you use ImplicitCast_, the compiler checks that
// the cast is safe.  Such explicit ImplicitCast_s are necessary in
// surprisingly many situations where C++ demands an exact type match
// instead of an argument type convertable to a target type.
//
// The syntax for using ImplicitCast_ is the same as for static_cast:
//
//   ImplicitCast_<ToType>(expr)
//
// ImplicitCast_ would have been part of the C++ standard library,
// but the proposal was submitted too late.  It will probably make
// its way into the language in the future.
//
// This relatively ugly name is intentional. It prevents clashes with
// similar functions users may have (e.g., implicit_cast). The internal
// namespace alone is not enough because the function can be found by ADL.
template<typename To>
inline To ImplicitCast_(To x) { return x; }

// When you upcast (that is, cast a pointer from type Foo to type
// SuperclassOfFoo), it's fine to use ImplicitCast_<>, since upcasts
// always succeed.  When you downcast (that is, cast a pointer from
// type Foo to type SubclassOfFoo), static_cast<> isn't safe, because
// how do you know the pointer is really of type SubclassOfFoo?  It
// could be a bare Foo, or of type DifferentSubclassOfFoo.  Thus,
// when you downcast, you should use this macro.  In debug mode, we
// use dynamic_cast<> to double-check the downcast is legal (we die
// if it's not).  In normal mode, we do the efficient static_cast<>
// instead.  Thus, it's important to test in debug mode to make sure
// the cast is legal!
//    This is the only place in the code we should use dynamic_cast<>.
// In particular, you SHOULDN'T be using dynamic_cast<> in order to
// do RTTI (eg code like this:
//    if (dynamic_cast<Subclass1>(foo)) HandleASubclass1Object(foo);
//    if (dynamic_cast<Subclass2>(foo)) HandleASubclass2Object(foo);
// You should design the code some other way not to need this.
//
// This relatively ugly name is intentional. It prevents clashes with
// similar functions users may have (e.g., down_cast). The internal
// namespace alone is not enough because the function can be found by ADL.
template<typename To, typename From>  // use like this: DownCast_<T*>(foo);
inline To DownCast_(From* f) {  // so we only accept pointers
  // Ensures that To is a sub-type of From *.  This test is here only
  // for compile-time type checking, and has no overhead in an
  // optimized build at run-time, as it will be optimized away
  // completely.
  GTEST_INTENTIONAL_CONST_COND_PUSH_()
  if (false) {
  GTEST_INTENTIONAL_CONST_COND_POP_()
  const To to = nullptr;
  ::testing::internal::ImplicitCast_<From*>(to);
  }

#if GTEST_HAS_RTTI
  // RTTI: debug mode only!
  GTEST_CHECK_(f == nullptr || dynamic_cast<To>(f) != nullptr);
#endif
  return static_cast<To>(f);
}

// Downcasts the pointer of type Base to Derived.
// Derived must be a subclass of Base. The parameter MUST
// point to a class of type Derived, not any subclass of it.
// When RTTI is available, the function performs a runtime
// check to enforce this.
template <class Derived, class Base>
Derived* CheckedDowncastToActualType(Base* base) {
#if GTEST_HAS_RTTI
  GTEST_CHECK_(typeid(*base) == typeid(Derived));
#endif

#if GTEST_HAS_DOWNCAST_
  return ::down_cast<Derived*>(base);
#elif GTEST_HAS_RTTI
  return dynamic_cast<Derived*>(base);  // NOLINT
#else
  return static_cast<Derived*>(base);  // Poor man's downcast.
#endif
}

#if GTEST_HAS_STREAM_REDIRECTION

// Defines the stderr capturer:
//   CaptureStdout     - starts capturing stdout.
//   GetCapturedStdout - stops capturing stdout and returns the captured string.
//   CaptureStderr     - starts capturing stderr.
//   GetCapturedStderr - stops capturing stderr and returns the captured string.
//
GTEST_API_ void CaptureStdout();
GTEST_API_ std::string GetCapturedStdout();
GTEST_API_ void CaptureStderr();
GTEST_API_ std::string GetCapturedStderr();

#endif  // GTEST_HAS_STREAM_REDIRECTION
// Returns the size (in bytes) of a file.
GTEST_API_ size_t GetFileSize(FILE* file);

// Reads the entire content of a file as a string.
GTEST_API_ std::string ReadEntireFile(FILE* file);

// All command line arguments.
GTEST_API_ std::vector<std::string> GetArgvs();

#if GTEST_HAS_DEATH_TEST

std::vector<std::string> GetInjectableArgvs();
// Deprecated: pass the args vector by value instead.
void SetInjectableArgvs(const std::vector<std::string>* new_argvs);
void SetInjectableArgvs(const std::vector<std::string>& new_argvs);
void ClearInjectableArgvs();

#endif  // GTEST_HAS_DEATH_TEST

// Sleeps for (roughly) n milliseconds.  This function is only for testing
// Google Test's own constructs.  Don't use it in user tests, either
// directly or indirectly.
GTEST_API_ void SleepMilliseconds(int n);

// Returns the number of threads running in the process, or 0 to indicate that
// we cannot detect it.
GTEST_API_ size_t GetThreadCount();

#if GTEST_OS_WINDOWS
# define GTEST_PATH_SEP_ "\\"
# define GTEST_HAS_ALT_PATH_SEP_ 1
#else
# define GTEST_PATH_SEP_ "/"
# define GTEST_HAS_ALT_PATH_SEP_ 0
#endif  // GTEST_OS_WINDOWS

// Utilities for char.

// isspace(int ch) and friends accept an unsigned char or EOF.  char
// may be signed, depending on the compiler (or compiler flags).
// Therefore we need to cast a char to unsigned char before calling
// isspace(), etc.

inline bool IsAlpha(char ch) {
  return isalpha(static_cast<unsigned char>(ch)) != 0;
}
inline bool IsAlNum(char ch) {
  return isalnum(static_cast<unsigned char>(ch)) != 0;
}
inline bool IsDigit(char ch) {
  return isdigit(static_cast<unsigned char>(ch)) != 0;
}
inline bool IsLower(char ch) {
  return islower(static_cast<unsigned char>(ch)) != 0;
}
inline bool IsSpace(char ch) {
  return isspace(static_cast<unsigned char>(ch)) != 0;
}
inline bool IsUpper(char ch) {
  return isupper(static_cast<unsigned char>(ch)) != 0;
}
inline bool IsXDigit(char ch) {
  return isxdigit(static_cast<unsigned char>(ch)) != 0;
}
inline bool IsXDigit(wchar_t ch) {
  const unsigned char low_byte = static_cast<unsigned char>(ch);
  return ch == low_byte && isxdigit(low_byte) != 0;
}

inline char ToLower(char ch) {
  return static_cast<char>(tolower(static_cast<unsigned char>(ch)));
}
inline char ToUpper(char ch) {
  return static_cast<char>(toupper(static_cast<unsigned char>(ch)));
}

inline std::string StripTrailingSpaces(std::string str) {
  std::string::iterator it = str.end();
  while (it != str.begin() && IsSpace(*--it))
    it = str.erase(it);
  return str;
}

// The testing::internal::posix namespace holds wrappers for common
// POSIX functions.  These wrappers hide the differences between
// Windows/MSVC and POSIX systems.  Since some compilers define these
// standard functions as macros, the wrapper cannot have the same name
// as the wrapped function.

namespace posix {

// Functions with a different name on Windows.

#if GTEST_OS_WINDOWS

typedef struct _stat StatStruct;

# ifdef __BORLANDC__
inline int DoIsATTY(int fd) { return isatty(fd); }
inline int StrCaseCmp(const char* s1, const char* s2) {
  return stricmp(s1, s2);
}
inline char* StrDup(const char* src) { return strdup(src); }
# else  // !__BORLANDC__
#  if GTEST_OS_WINDOWS_MOBILE
inline int DoIsATTY(int /* fd */) { return 0; }
#  else
inline int DoIsATTY(int fd) { return _isatty(fd); }
#  endif  // GTEST_OS_WINDOWS_MOBILE
inline int StrCaseCmp(const char* s1, const char* s2) {
  return _stricmp(s1, s2);
}
inline char* StrDup(const char* src) { return _strdup(src); }
# endif  // __BORLANDC__

# if GTEST_OS_WINDOWS_MOBILE
inline int FileNo(FILE* file) { return reinterpret_cast<int>(_fileno(file)); }
// Stat(), RmDir(), and IsDir() are not needed on Windows CE at this
// time and thus not defined there.
# else
inline int FileNo(FILE* file) { return _fileno(file); }
inline int Stat(const char* path, StatStruct* buf) { return _stat(path, buf); }
inline int RmDir(const char* dir) { return _rmdir(dir); }
inline bool IsDir(const StatStruct& st) {
  return (_S_IFDIR & st.st_mode) != 0;
}
# endif  // GTEST_OS_WINDOWS_MOBILE

#elif GTEST_OS_ESP8266
typedef struct stat StatStruct;

inline int FileNo(FILE* file) { return fileno(file); }
inline int DoIsATTY(int fd) { return isatty(fd); }
inline int Stat(const char* path, StatStruct* buf) {
  // stat function not implemented on ESP8266
  return 0;
}
inline int StrCaseCmp(const char* s1, const char* s2) {
  return strcasecmp(s1, s2);
}
inline char* StrDup(const char* src) { return strdup(src); }
inline int RmDir(const char* dir) { return rmdir(dir); }
inline bool IsDir(const StatStruct& st) { return S_ISDIR(st.st_mode); }

#else

typedef struct stat StatStruct;

inline int FileNo(FILE* file) { return fileno(file); }
inline int DoIsATTY(int fd) { return isatty(fd); }
inline int Stat(const char* path, StatStruct* buf) { return stat(path, buf); }
inline int StrCaseCmp(const char* s1, const char* s2) {
  return strcasecmp(s1, s2);
}
inline char* StrDup(const char* src) { return strdup(src); }
inline int RmDir(const char* dir) { return rmdir(dir); }
inline bool IsDir(const StatStruct& st) { return S_ISDIR(st.st_mode); }

#endif  // GTEST_OS_WINDOWS

inline int IsATTY(int fd) {
  // DoIsATTY might change errno (for example ENOTTY in case you redirect stdout
  // to a file on Linux), which is unexpected, so save the previous value, and
  // restore it after the call.
  int savedErrno = errno;
  int isAttyValue = DoIsATTY(fd);
  errno = savedErrno;

  return isAttyValue;
}

// Functions deprecated by MSVC 8.0.

GTEST_DISABLE_MSC_DEPRECATED_PUSH_()

// ChDir(), FReopen(), FDOpen(), Read(), Write(), Close(), and
// StrError() aren't needed on Windows CE at this time and thus not
// defined there.

#if !GTEST_OS_WINDOWS_MOBILE && !GTEST_OS_WINDOWS_PHONE && !GTEST_OS_WINDOWS_RT
inline int ChDir(const char* dir) { return chdir(dir); }
#endif
inline FILE* FOpen(const char* path, const char* mode) {
  return fopen(path, mode);
}
#if !GTEST_OS_WINDOWS_MOBILE
inline FILE *FReopen(const char* path, const char* mode, FILE* stream) {
  return freopen(path, mode, stream);
}
inline FILE* FDOpen(int fd, const char* mode) { return fdopen(fd, mode); }
#endif
inline int FClose(FILE* fp) { return fclose(fp); }
#if !GTEST_OS_WINDOWS_MOBILE
inline int Read(int fd, void* buf, unsigned int count) {
  return static_cast<int>(read(fd, buf, count));
}
inline int Write(int fd, const void* buf, unsigned int count) {
  return static_cast<int>(write(fd, buf, count));
}
inline int Close(int fd) { return close(fd); }
inline const char* StrError(int errnum) { return strerror(errnum); }
#endif
inline const char* GetEnv(const char* name) {
#if GTEST_OS_WINDOWS_MOBILE || GTEST_OS_WINDOWS_PHONE || \
    GTEST_OS_WINDOWS_RT || GTEST_OS_ESP8266
  // We are on an embedded platform, which has no environment variables.
  static_cast<void>(name);  // To prevent 'unused argument' warning.
  return nullptr;
#elif defined(__BORLANDC__) || defined(__SunOS_5_8) || defined(__SunOS_5_9)
  // Environment variables which we programmatically clear will be set to the
  // empty string rather than unset (NULL).  Handle that case.
  const char* const env = getenv(name);
  return (env != nullptr && env[0] != '\0') ? env : nullptr;
#else
  return getenv(name);
#endif
}

GTEST_DISABLE_MSC_DEPRECATED_POP_()

#if GTEST_OS_WINDOWS_MOBILE
// Windows CE has no C library. The abort() function is used in
// several places in Google Test. This implementation provides a reasonable
// imitation of standard behaviour.
[[noreturn]] void Abort();
#else
[[noreturn]] inline void Abort() { abort(); }
#endif  // GTEST_OS_WINDOWS_MOBILE

}  // namespace posix

// MSVC "deprecates" snprintf and issues warnings wherever it is used.  In
// order to avoid these warnings, we need to use _snprintf or _snprintf_s on
// MSVC-based platforms.  We map the GTEST_SNPRINTF_ macro to the appropriate
// function in order to achieve that.  We use macro definition here because
// snprintf is a variadic function.
#if _MSC_VER && !GTEST_OS_WINDOWS_MOBILE
// MSVC 2005 and above support variadic macros.
# define GTEST_SNPRINTF_(buffer, size, format, ...) \
     _snprintf_s(buffer, size, size, format, __VA_ARGS__)
#elif defined(_MSC_VER)
// Windows CE does not define _snprintf_s
# define GTEST_SNPRINTF_ _snprintf
#else
# define GTEST_SNPRINTF_ snprintf
#endif

// The biggest signed integer type the compiler supports.
//
// long long is guaranteed to be at least 64-bits in C++11.
using BiggestInt = long long;  // NOLINT

// The maximum number a BiggestInt can represent.
constexpr BiggestInt kMaxBiggestInt = (std::numeric_limits<BiggestInt>::max)();

// This template class serves as a compile-time function from size to
// type.  It maps a size in bytes to a primitive type with that
// size. e.g.
//
//   TypeWithSize<4>::UInt
//
// is typedef-ed to be unsigned int (unsigned integer made up of 4
// bytes).
//
// Such functionality should belong to STL, but I cannot find it
// there.
//
// Google Test uses this class in the implementation of floating-point
// comparison.
//
// For now it only handles UInt (unsigned int) as that's all Google Test
// needs.  Other types can be easily added in the future if need
// arises.
template <size_t size>
class TypeWithSize {
 public:
  // This prevents the user from using TypeWithSize<N> with incorrect
  // values of N.
  using UInt = void;
};

// The specialization for size 4.
template <>
class TypeWithSize<4> {
 public:
  using Int = std::int32_t;
  using UInt = std::uint32_t;
};

// The specialization for size 8.
template <>
class TypeWithSize<8> {
 public:
  using Int = std::int64_t;
  using UInt = std::uint64_t;
};

// Integer types of known sizes.
using TimeInMillis = int64_t;  // Represents time in milliseconds.

// Utilities for command line flags and environment variables.

// Macro for referencing flags.
#if !defined(GTEST_FLAG)
# define GTEST_FLAG(name) FLAGS_gtest_##name
#endif  // !defined(GTEST_FLAG)

#if !defined(GTEST_USE_OWN_FLAGFILE_FLAG_)
# define GTEST_USE_OWN_FLAGFILE_FLAG_ 1
#endif  // !defined(GTEST_USE_OWN_FLAGFILE_FLAG_)

#if !defined(GTEST_DECLARE_bool_)
# define GTEST_FLAG_SAVER_ ::testing::internal::GTestFlagSaver

// Macros for declaring flags.
# define GTEST_DECLARE_bool_(name) GTEST_API_ extern bool GTEST_FLAG(name)
# define GTEST_DECLARE_int32_(name) \
    GTEST_API_ extern std::int32_t GTEST_FLAG(name)
# define GTEST_DECLARE_string_(name) \
    GTEST_API_ extern ::std::string GTEST_FLAG(name)

// Macros for defining flags.
# define GTEST_DEFINE_bool_(name, default_val, doc) \
    GTEST_API_ bool GTEST_FLAG(name) = (default_val)
# define GTEST_DEFINE_int32_(name, default_val, doc) \
    GTEST_API_ std::int32_t GTEST_FLAG(name) = (default_val)
# define GTEST_DEFINE_string_(name, default_val, doc) \
    GTEST_API_ ::std::string GTEST_FLAG(name) = (default_val)

#endif  // !defined(GTEST_DECLARE_bool_)

// Thread annotations
#if !defined(GTEST_EXCLUSIVE_LOCK_REQUIRED_)
# define GTEST_EXCLUSIVE_LOCK_REQUIRED_(locks)
# define GTEST_LOCK_EXCLUDED_(locks)
#endif  // !defined(GTEST_EXCLUSIVE_LOCK_REQUIRED_)

// Parses 'str' for a 32-bit signed integer.  If successful, writes the result
// to *value and returns true; otherwise leaves *value unchanged and returns
// false.
bool ParseInt32(const Message& src_text, const char* str, int32_t* value);

// Parses a bool/int32_t/string from the environment variable
// corresponding to the given Google Test flag.
bool BoolFromGTestEnv(const char* flag, bool default_val);
GTEST_API_ int32_t Int32FromGTestEnv(const char* flag, int32_t default_val);
std::string OutputFlagAlsoCheckEnvVar();
const char* StringFromGTestEnv(const char* flag, const char* default_val);

}  // namespace internal
}  // namespace testing

#if !defined(GTEST_INTERNAL_DEPRECATED)

// Internal Macro to mark an API deprecated, for googletest usage only
// Usage: class GTEST_INTERNAL_DEPRECATED(message) MyClass or
// GTEST_INTERNAL_DEPRECATED(message) <return_type> myFunction(); Every usage of
// a deprecated entity will trigger a warning when compiled with
// `-Wdeprecated-declarations` option (clang, gcc, any __GNUC__ compiler).
// For msvc /W3 option will need to be used
// Note that for 'other' compilers this macro evaluates to nothing to prevent
// compilations errors.
#if defined(_MSC_VER)
#define GTEST_INTERNAL_DEPRECATED(message) __declspec(deprecated(message))
#elif defined(__GNUC__)
#define GTEST_INTERNAL_DEPRECATED(message) __attribute__((deprecated(message)))
#else
#define GTEST_INTERNAL_DEPRECATED(message)
#endif

#endif  // !defined(GTEST_INTERNAL_DEPRECATED)

#if GTEST_HAS_ABSL
// Always use absl::string_view for Matcher<> specializations if googletest
// is built with absl support.
# define GTEST_INTERNAL_HAS_STRING_VIEW 1
#include "absl/strings/string_view.h"
namespace testing {
namespace internal {
using StringView = ::absl::string_view;
}  // namespace internal
}  // namespace testing
#else
# ifdef __has_include
#   if __has_include(<string_view>) && __cplusplus >= 201703L
// Otherwise for C++17 and higher use std::string_view for Matcher<>
// specializations.
#   define GTEST_INTERNAL_HAS_STRING_VIEW 1
#include <string_view>
namespace testing {
namespace internal {
using StringView = ::std::string_view;
}  // namespace internal
}  // namespace testing
// The case where absl is configured NOT to alias std::string_view is not
// supported.
#  endif  // __has_include(<string_view>) && __cplusplus >= 201703L
# endif  // __has_include
#endif  // GTEST_HAS_ABSL

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_
