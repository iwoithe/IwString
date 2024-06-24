add_executable(generaltest generaltest.cpp)
target_link_libraries(generaltest iwstring)
target_include_directories(generaltest PRIVATE src/${PROJECT_SOURCE_DIR})
