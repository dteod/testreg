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

#ifndef TESTREG_LOADER_H_INCLUDED
#define TESTREG_LOADER_H_INCLUDED

typedef enum {
    TESTREG_RESULT_NOT_RUN,
    TESTREG_RESULT_SUCCESS,
    TESTREG_RESULT_FAILURE,
    TESTREG_RESULT_SKIPPED,
} testreg_result;

typedef void (*testreg_test)(testreg_result*);

typedef struct testreg_node {
    const char*          id;
    testreg_test         test;
    const char**         labels;
    testreg_result       result;
    struct testreg_node* next;
} testreg_node;

TESTREG_API void testreg_register_function(testreg_test test, const char* name, int n_labels, ...);

TESTREG_API testreg_node* testreg_get_test_register();

#endif