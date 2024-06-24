add_executable(generalexample generalexample.cpp)
target_link_libraries(generalexample iwstring)
target_include_directories(generalexample PRIVATE src/${PROJECT_SOURCE_DIR})
