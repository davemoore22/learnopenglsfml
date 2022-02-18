cmake_minimum_required(VERSION 3.1.6)
set(CMAKE_CXX_STANDARD 20)
project(learnopenglsfml VERSION 0.1.0)

find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/graphics.cpp)
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${PROJECT_NAME} PRIVATE /usr/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio sfml-graphics sfml-network sfml-system)
target_link_libraries(${PROJECT_NAME} PRIVATE GL)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/dat/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)