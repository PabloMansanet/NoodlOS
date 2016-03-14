set (TEST_EXECUTABLE RunSchedulerTests)

# Add a line to this variable whenever you add a test
set(TESTS
   tests.Scheduler)

# Add a line to this variable whenever you add a mock
set(MOCK_LIBRARIES)

# Add a line to this variable if the tests in this folder 
# start depending on a new system library
set(PROJECT_DEPENDENCIES)

# include directories for the unit under test
include_directories(./)

###################
## BUILD PROCESS ##
###################

get_filename_component(RELATIVE_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

PREPEND(QUALIFIED_MOCK_LIBRARIES ${RELATIVE_TEST_DIR}. ${MOCK_LIBRARIES})

list(APPEND GLOBAL_TESTS ${TEST_EXECUTABLE})
set(GLOBAL_TESTS ${GLOBAL_TESTS} PARENT_SCOPE)


# Local mocks
set(MOCK_LIBRARIES_DIR Mocks)

foreach(MOCK_LIBRARY ${MOCK_LIBRARIES})
   add_library(${RELATIVE_TEST_DIR}.${MOCK_LIBRARY} 
               ${MOCK_LIBRARIES_DIR}/mock.${MOCK_LIBRARY}.c)
endforeach(MOCK_LIBRARY)

foreach(TEST ${TESTS})
   add_library(${TEST} ${TEST}.c)
endforeach(TEST)

add_executable(${TEST_EXECUTABLE} ${TEST_EXECUTABLE}.c)
target_link_libraries(${TEST_EXECUTABLE}
                      ${TESTS}
                      stdlib_metal_hooks
                      metal_test 
                      ${PROJECT_DEPENDENCIES}
                      ${QUALIFIED_MOCK_LIBRARIES}
                      ${PROJECT_DEPENDENCIES}
                      ${QUALIFIED_MOCK_LIBRARIES})
