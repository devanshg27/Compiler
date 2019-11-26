cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
project (CPLCompiler)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})

set (CMAKE_CXX_STANDARD 17)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-pedantic")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(LLVM REQUIRED)

include_directories(src)
include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )

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

llvm_map_components_to_libnames(REQ_LLVM_LIBRARIES native)

target_link_libraries(cpl_parser ${FLEX_LIBRARIES} ${REQ_LLVM_LIBRARIES})