aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test_moveable ${SRC})