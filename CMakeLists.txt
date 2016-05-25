cmake_minimum_required(VERSION 3.2)
project(42sh C)


if (BUILD_TYPE MATCHES DEBUG)
    set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic -g")
else()
    set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic")
endif (BUILD_TYPE MATCHES DEBUG)

set(MAIN_SOURCES src/main.c)
set(EXEC_DIR src/exec)
set(PARSER_DIR src/parser)
set(LEXER_DIR src/lexer)
set(UTILS_DIR src/utils)

aux_source_directory(${EXEC_DIR} EXEC_SRC)
aux_source_directory(${PARSER_DIR} PARSER_SRC)
aux_source_directory(${LEXER_DIR} LEXER_SRC)
aux_source_directory(${UTILS_DIR} UTILS_SRC)

include_directories(src/includes)

add_executable(42sh
        ${MAIN_SOURCES}
        ${EXEC_SRC}
        ${PARSER_SRC}
        ${LEXER_SRC}
        ${UTILS_SRC}
        )

add_library(my42sh SHARED
        ${MAIN_SOURCES}
        ${EXEC_SRC}
        ${PARSER_SRC}
        ${LEXER_SRC}
        ${UTILS_SRC}
)

add_custom_target(check
        COMMAND python3 ../tests/test.py
        )

add_custom_target(doc
        COMMAND cd ../doc && mkdir -p doxygen && doxygen Doxyfile
        )


