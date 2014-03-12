project(elelo)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src/ SRC_LIST)

include_directories(lib/)

find_package(Boost COMPONENTS system filesystem random thread REQUIRED)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRC_LIST})
ADD_EXECUTABLE(${PROJECT_NAME}-bin main.cpp ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-bin ${Boost_LIBRARIES})
