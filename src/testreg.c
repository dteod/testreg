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

#include "testreg.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static testreg_node* g_tests_list = NULL;

TESTREG_LINK void
testreg_register_function(testreg_test test, const char* id, int n_labels, ...)
{
    const char** labels;
    if(n_labels) {
        labels = malloc(n_labels * sizeof(const char*));
        if(!labels) {
            fprintf(stderr, "failed to allocate memory to store test labels");
            exit(EXIT_FAILURE);
        }
        va_list vl;
        va_start(vl, n_labels);
        for(int i = 0; i != n_labels; ++i) {
            labels[i] = va_arg(vl, const char*);
        }
        va_end(vl);
    }

    testreg_node **pnode = &g_tests_list, *tmp;
    while(*pnode) {
        pnode = &((*pnode)->next);
    }
    *pnode = tmp = malloc(sizeof(testreg_node));
    tmp->id      = id;
    tmp->test    = test;
    tmp->labels  = labels;
    tmp->result  = TESTREG_RESULT_NOT_RUN;
    tmp->next    = NULL;
}

TESTREG_LINK testreg_node*
testreg_get_test_register()
{
    return g_tests_list;
}