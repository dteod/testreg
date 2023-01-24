/*
    testreg - A small unit testing library for C with automatic test registration
    Copyright (C) 2023  Domenico Teodonio

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef TESTREG_COMPILER_H_INCLUDED
#define TESTREG_COMPILER_H_INCLUDED

#if TESTREG_STATIC
#  define TESTREG_LINK
#else
#  if defined(_MSC_VER)
#    if defined(TESTREG_INTERNAL)
#      define TESTREG_LINK declspec(dllexport)
#    else
#      define TESTREG_LINK declspec(dllimport)
#    endif
#  else
#    define TESTREG_LINK
#  endif
#endif

#define TESTREG_API extern TESTREG_LINK

#if defined(__GNUC__) || defined(__clang__)  // GCC
#  define TESTREG_CTOR(FUNCNAME) __attribute__((constructor))
#elif defined(_MSC_VER)  // Microsoft Visual C++
#  define TESTREG_CTOR(FUNCNAME) _Pragma("init_seg(lib)")
#elif defined(__BORLANDC__)  // Borland C++ Builder
#  define TESTREG_CTOR(FUNCNAME) _Pragma("startup")
#elif defined(__INTEL_COMPILER)  // Intel C++
#  define TESTREG_CTOR(FUNCNAME) _Pragma("intel_constructor")
#elif defined(__xlC__)  // IBM XL C/C++
#  define TESTREG_CTOR(FUNCNAME) _Pragma("prolog")
#elif defined(__SUNPRO_C)  // Sun Studio
#  define TESTREG_CTOR(FUNCNAME) _Pragma("init")
#elif defined(__WATCOMC__)  // Open Watcom
#  define TESTREG_CTOR(FUNCNAME) _Pragma("library")
#elif defined(__DMC__)  // Digital Mars
#  define TESTREG_CTOR(FUNCNAME) _Pragma(lib, #FUNCNAME)
#endif

#endif