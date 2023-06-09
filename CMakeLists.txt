cmake_minimum_required(VERSION 2.8.12)

project(hydrazine CXX)

find_package(Boost COMPONENTS thread REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB SRCS "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} Boost::thread OpenGL::GL)

include(CTest)

file(GLOB TESTS "test/*.cpp")
foreach(TEST ${TESTS})
	get_filename_component(TEST_WE ${TEST} NAME_WE)
	set(TEST_NAME ${PROJECT_NAME}_${TEST_WE})
	add_executable(${TEST_NAME} ${TEST})
	target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
	set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 11)
	target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
	add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}> -v)
endforeach()

