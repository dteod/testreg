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

#include <stdbool.h>

#define TESTREG_RUNNER
#include <testreg.h>

TEST_CASE()
{
    printf("ciao da %s\n", __func__);
    ASSERT(true);
}

TEST_CASE()
{
    printf("ciao da %s\n", __func__);
    ASSERT(false);
}

TEST_CASE()
{
    printf("ciao da %s\n", __func__);
    CHECK(false);
}