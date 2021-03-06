# Copyright 2019 Michael Rodriguez
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

set(SRCS bus.c cpu.c disasm.c gpu.c ps.c)

set(HDRS include/bus.h
         include/cpu.h
         include/cpu_defs.h
         include/disasm.h
         include/gpu.h
         include/ps.h)

add_library(ps STATIC ${SRCS} ${HDRS})

set_target_properties(ps PROPERTIES
                      C_STANDARD 17
                      C_STANDARD_REQUIRED YES
                      C_EXTENSIONS ON)

target_include_directories(ps PRIVATE include)

target_compile_options(ps PRIVATE
                       $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>,$<C_COMPILER_ID:GNU>>:
                       -Wall -Wextra -Wno-gnu-case-range -Wno-old-style-cast>)