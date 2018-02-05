
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser pc-from-file.yy ${PROJECT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(scanner pc-from-file.l ${PROJECT_BINARY_DIR}/scanner.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE_FILES)

add_executable(ic ${SOURCE_FILES} ${FLEX_scanner_OUTPUTS} ${BISON_parser_OUTPUTS})
target_include_directories(ic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
