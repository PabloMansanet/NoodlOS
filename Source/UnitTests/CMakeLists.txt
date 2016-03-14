# Add a new line here whenever you include a new test subdirectory
# (And write a CMakeLists.txt on it)
set(TEST_SUBDIRECTORIES 
    SchedulerTests)

# Add a new line here whenever there is a new cfile
# that must be compiled for the tests
set(PROJECT_CFILES)

###################
## BUILD PROCESS ##
###################
cmake_minimum_required(VERSION 2.8)
project(NoodlOS_UnitTests)

if(CMAKE_COMPILER_IS_GNUCC)
   set(CMAKE_C_FLAGS "-g -Wall -Werror  -std=c11")
endif(CMAKE_COMPILER_IS_GNUCC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SOURCE_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)

set(METALTEST_DIR ${PROJECT_SOURCE_DIR}/../../Tools/metal_test)

include_directories(${METALTEST_DIR}/include)
include_directories(${SOURCE_ROOT_DIR}/
                    ./)

# Builds binaries from the metal_test framework
add_library(stdlib_metal_hooks ${METALTEST_DIR}/source/stdlib_metal_hooks.c)
add_library(metal_test ${METALTEST_DIR}/source/metal_test.c)

foreach(CFILE ${PROJECT_CFILES})
   add_library(${CFILE} ${PROJECT_DIR}/${CFILE}.c)
endforeach(CFILE)

foreach(TEST_SUBDIRECTORY ${TEST_SUBDIRECTORIES})
   add_subdirectory(${TEST_SUBDIRECTORY})
endforeach(TEST_SUBDIRECTORY)

# Retrieves all test commands from subdirectories and ties them to 
# the global test target
enable_testing()
foreach(TEST ${GLOBAL_TESTS})
   add_test(run_${TEST} ${EXECUTABLE_OUTPUT_PATH}/${TEST})
   set_tests_properties(run_${TEST} PROPERTIES FAIL_REGULAR_EXPRESSION "failed")
endforeach(TEST)
