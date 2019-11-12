cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
project (CPLCompiler)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})

set (CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

include_directories(src)

file(GLOB SOURCES
    "src/*.h"
    "src/*.cpp"
)

FLEX_TARGET(lexer src/scanner.l "${OUTPUT_DIRECTORY}/scanner.lex.cc")

BISON_TARGET(parser src/parser.yy "${OUTPUT_DIRECTORY}/parser.tab.cc")

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_executable(cpl_parser
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
    ${SOURCES})
target_link_libraries(cpl_parser ${FLEX_LIBRARIES})