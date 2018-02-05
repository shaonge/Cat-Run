cmake_minimum_required(VERSION 2.8)

project(ProgrammableCalculator CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

#BISON_TARGET(parser pc-command-line.yy ${PROJECT_BINARY_DIR}/parser.tab.cc)
#FLEX_TARGET(scanner pc-command-line.l ${PROJECT_BINARY_DIR}/scanner.yy.cc)
BISON_TARGET(parser pc-from-file.yy ${PROJECT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(scanner pc-from-file.l ${PROJECT_BINARY_DIR}/scanner.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

add_executable(bc ${SOURCE_FILES} ${FLEX_scanner_OUTPUTS} ${BISON_parser_OUTPUTS})
target_include_directories(bc PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
