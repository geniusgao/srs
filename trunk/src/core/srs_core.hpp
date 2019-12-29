/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2019 Winlin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SRS_CORE_HPP
#define SRS_CORE_HPP

// The version config.
#define VERSION_MAJOR       3
#define VERSION_MINOR       0
#define VERSION_REVISION    89

// The macros generated by configure script.
#include <srs_auto_headers.hpp>

// To convert macro values to string.
// @see https://gcc.gnu.org/onlinedocs/cpp/Stringification.html#Stringification
#define SRS_INTERNAL_STR(v) #v
#define SRS_XSTR(v) SRS_INTERNAL_STR(v)

// The project informations, may sent to client in HTTP header or RTMP metadata.
#define RTMP_SIG_SRS_KEY "SRS"
#define RTMP_SIG_SRS_CODE "OuXuli"
#define RTMP_SIG_SRS_URL "https://github.com/ossrs/srs"
#define RTMP_SIG_SRS_LICENSE "The MIT License (MIT)"
#define RTMP_SIG_SRS_VERSION SRS_XSTR(VERSION_MAJOR) "." SRS_XSTR(VERSION_MINOR) "." SRS_XSTR(VERSION_REVISION)
#define RTMP_SIG_SRS_SERVER RTMP_SIG_SRS_KEY "/" RTMP_SIG_SRS_VERSION "(" RTMP_SIG_SRS_CODE ")"

// The current stable release.
#define VERSION_STABLE 2
#define VERSION_STABLE_BRANCH SRS_XSTR(VERSION_STABLE)".0release"

// For 32bit os, 2G big file limit for unistd io,
// ie. read/write/lseek to use 64bits size for huge file.
#ifndef _FILE_OFFSET_BITS
    #define _FILE_OFFSET_BITS 64
#endif

// For int64_t print using PRId64 format.
#ifndef __STDC_FORMAT_MACROS
    #define __STDC_FORMAT_MACROS
#endif

// For srs-librtmp, @see https://github.com/ossrs/srs/issues/213
#ifndef _WIN32
#include <inttypes.h>
#endif

#include <assert.h>
#define srs_assert(expression) assert(expression)

#include <stddef.h>
#include <sys/types.h>

// The time unit for timeout, interval or duration.
#include <srs_core_time.hpp>

// Some important performance options.
#include <srs_core_performance.hpp>

// To free the p and set to NULL.
// @remark The p must be a pointer T*.
#define srs_freep(p) \
    if (p) { \
        delete p; \
        p = NULL; \
    } \
    (void)0
// Please use the freepa(T[]) to free an array, otherwise the behavior is undefined.
#define srs_freepa(pa) \
    if (pa) { \
        delete[] pa; \
        pa = NULL; \
    } \
    (void)0

// For librtmp, it is pure c++ and supports all OS.
#ifndef SRS_EXPORT_LIBRTMP
    // Checking for st(state-threads), only support the following cpus: i386/amd64/x86_64/arm
    // @reamrk To patch ST for arm, read https://github.com/ossrs/state-threads/issues/1
    #if !defined(__amd64__) && !defined(__x86_64__) && !defined(__i386__) && !defined(__arm__) && !defined(__aarch64__)
        #error "only support i386/amd64/x86_64/arm cpu"
    #endif
#endif

// Error predefined for all modules.
class SrsCplxError;
typedef SrsCplxError* srs_error_t;

#endif
