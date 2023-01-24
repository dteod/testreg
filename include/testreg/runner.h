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

#ifndef TESTREG_RUNNER_H_INCLUDED
#define TESTREG_RUNNER_H_INCLUDED

#ifdef TESTREG_RUNNER
#  include <stdio.h>
#  include <stdlib.h>

int
main()
{
    testreg_node* node    = testreg_get_test_register();
    int           success = 0, failure = 0, skipped = 0, total = 0;
    FILE*         old_stdout = stdout;
    FILE*         old_stderr = stderr;
#  ifdef _WIN32
    stdout = fopen("nul", "w");
    stderr = fopen("nul", "w");
#  elif __unix__
    stdout = fopen("/dev/null", "w");
    stderr = fopen("/dev/null", "w");
#  endif
    while(node) {
        node->result = TESTREG_RESULT_SUCCESS;
        node->test(&node->result);
        switch(node->result) {
        case TESTREG_RESULT_SUCCESS: success++; break;
        case TESTREG_RESULT_FAILURE: failure++; break;
        case TESTREG_RESULT_SKIPPED: skipped++; break;
        case TESTREG_RESULT_NOT_RUN: break;
        }
        total++;
        node = node->next;
    }
    fclose(stdout);
    fclose(stderr);
    stdout = old_stdout;
    stderr = old_stderr;
    if(total == 0) {
        printf("No tests were found.\n");
    }
    else {
        printf(" Test report\n");
        printf("------------------\n");
        if(success) {
            printf("%8s: %d/%d\n", "success", success, total);
        }
        if(failure) {
            printf("%8s: %d/%d\n", "failure", failure, total);
        }
        if(skipped) {
            printf("%8s: %d/%d\n", "skipped", skipped, total);
        }
    }
    return total ? failure ? EXIT_FAILURE : EXIT_SUCCESS : EXIT_SUCCESS;
}
#endif

#endif