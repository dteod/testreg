# testreg - A small unit testing library for C with automatic test registration
# Copyright (C) 2023  Domenico Teodonio

# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
# USA

cmake_minimum_required(VERSION 3.23)

project(testreg VERSION 0.1.0 DESCRIPTION "A small unit testing library for C with automatic test registration" LANGUAGES C)

get_property(TARGET_SUPPORTS_SHARED_LIBS GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)

function(add_testreg_library LIB_TYPE)
    string(TOLOWER ${LIB_TYPE} LIB_NAME_SUFFIX)
    add_library(testreg_${LIB_NAME_SUFFIX} ${LIB_TYPE})
    add_library(testreg::${LIB_NAME_SUFFIX} ALIAS testreg_${LIB_NAME_SUFFIX})
    target_sources(testreg_${LIB_NAME_SUFFIX}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/testreg.c
        PUBLIC FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/
            FILES 
                ${CMAKE_CURRENT_SOURCE_DIR}/include/testreg.h
                ${CMAKE_CURRENT_SOURCE_DIR}/include/testreg/compiler.h
                ${CMAKE_CURRENT_SOURCE_DIR}/include/testreg/register.h
                ${CMAKE_CURRENT_SOURCE_DIR}/include/testreg/macros.h
                ${CMAKE_CURRENT_SOURCE_DIR}/include/testreg/runner.h
    )
    target_include_directories(testreg_${LIB_NAME_SUFFIX} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
    if(WIN32 AND LIB_TYPE STREQUAL "STATIC")
        set_target_properties(testreg_${LIB_NAME_SUFFIX} PROPERTIES OUTPUT_NAME "testreg-static")
        target_compile_definitions(testreg_${LIB_NAME_SUFFIX} PUBLIC -DTESTREG_STATIC=1)
    elseif(UNIX OR LIB_TYPE STREQUAL "SHARED")
        set_target_properties(testreg_${LIB_NAME_SUFFIX} PROPERTIES OUTPUT_NAME "testreg")
        target_compile_definitions(testreg_${LIB_NAME_SUFFIX} PUBLIC -DTESTREG_STATIC=0)
    endif()
    target_compile_definitions(testreg_${LIB_NAME_SUFFIX} PRIVATE -DTESTREG_INTERNAL=1)
endfunction()

add_testreg_library(STATIC)

if(TARGET_SUPPORTS_SHARED_LIBS)
    add_testreg_library(SHARED)
endif()

add_executable(testreg_runner EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/test/runner.c)
target_link_libraries(testreg_runner PUBLIC testreg_static)