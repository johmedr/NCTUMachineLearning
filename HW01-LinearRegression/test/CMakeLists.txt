cmake_minimum_required (VERSION 2.8.11)
project (NEOS)

unset(EXECUTABLE_OUTPUT_PATH)

file(GLOB_RECURSE test_files ${CMAKE_CURRENT_LIST_DIR}/**/*.cc)
set(TEST_FILES_NAMES)
foreach(test_file ${test_files})
	get_filename_component(test_file_name ${test_file} NAME_WE)
	add_executable(_${test_file_name} ${test_file})
	add_test(NAME ${test_file_name} COMMAND _${test_file_name})
	list(APPEND TEST_FILES_NAMES _${test_file_name})
endforeach() 


macro(ADDEXTEST FILE)
	get_filename_component(test_file_name ${FILE} NAME_WE)
	add_executable(_${test_file_name} ${FILE})
	add_test(${test_file_name} _${test_file_name})
	list(APPEND TEST_FILES_NAMES _${test_file_name})
endmacro() 

ADDEXTEST(${CMAKE_CURRENT_LIST_DIR}/TestStaticMatrix.cc)
ADDEXTEST(${CMAKE_CURRENT_LIST_DIR}/TestStaticMatrixOperators.cc)
ADDEXTEST(${CMAKE_CURRENT_LIST_DIR}/TestStaticLinAlgCommon.cc)
ADDEXTEST(${CMAKE_CURRENT_LIST_DIR}/TestDynamicMatrix.cc)
ADDEXTEST(${CMAKE_CURRENT_LIST_DIR}/TestDynamicMatrixOperators.cc)
ADDEXTEST(${CMAKE_CURRENT_LIST_DIR}/TestLinearRegression.cc)


add_custom_target(all_tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS ${TEST_FILES_NAMES})
