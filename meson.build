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

project('testreg', 'c', version: '0.1.0', description: 'A small unit testing library for C with automatic test registration')

lib_static = library('testreg-static', 'src/testreg.c',
    include_directories: 'include',
    install: true)

lib_shared = library('testreg', 'src/testreg.c',
    include_directories: 'include',
    version: '0.1.0',
    install: true)

executable('testreg_runner', 'test/runner.c',
    link_with: lib_static,
    install: false)

