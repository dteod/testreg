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

#ifndef TESTREG_MACROS_H_INCLUDED
#define TESTREG_MACROS_H_INCLUDED

#define TESTREG_NEW_FUNCTION()           TESTREG_CREATE_NEW_FUNCTION(__COUNTER__)
#define TESTREG_CREATE_NEW_FUNCTION(CNT) TESTREG_EXPAND_NEW_FUNCTION(CNT)
#define TESTREG_EXPAND_NEW_FUNCTION(CNT) TEST_NUMBER_##CNT

#define TESTREG_INTERNAL_TEST_CASE(TEST_NAME, ...) TESTREG_INTERNAL_REGISTER_TEST(TEST_NAME, __VA_ARGS__)
#define TESTREG_INTERNAL_REGISTER_TEST(TEST_NAME, ...)                                                                           \
  static void                         TEST_NAME(testreg_result*);                                                                \
  static TESTREG_CTOR(TEST_NAME) void register_##TEST_NAME()                                                                     \
  {                                                                                                                              \
    testreg_register_function(                                                                                                   \
        TEST_NAME, #TEST_NAME, (sizeof((const char*[]){__VA_ARGS__}) / sizeof(const char*)), "" __VA_ARGS__                      \
    );                                                                                                                           \
  }                                                                                                                              \
  static void TEST_NAME(testreg_result* testreg_result_variable)

#define TEST_CASE(...) TESTREG_INTERNAL_TEST_CASE(TESTREG_NEW_FUNCTION(), __VA_ARGS__)

#define TESTREG_CHECK(expr, TEST_NAME)                                                                                           \
  do {                                                                                                                           \
    const char* expr_string_literal = #expr;                                                                                     \
    if(!!(expr)) {                                                                                                               \
      *testreg_result_variable = TESTREG_RESULT_SKIPPED;                                                                         \
      return;                                                                                                                    \
    }                                                                                                                            \
  } while(0)

#define TESTREG_ASSERT(expr, TEST_NAME)                                                                                          \
  do {                                                                                                                           \
    const char* expr_string_literal = #expr;                                                                                     \
    if(!!(expr)) {                                                                                                               \
      *testreg_result_variable = TESTREG_RESULT_FAILURE;                                                                         \
      return;                                                                                                                    \
    }                                                                                                                            \
  } while(0)

#define ASSERT(expr) TESTREG_ASSERT(expr, __FUNC__)

#define CHECK(expr) TESTREG_CHECK(expr, __FUNC__)

#endif