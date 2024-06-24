add_executable(testiwstring
    testiwstring.cpp
    testhandler.cpp
)
target_link_libraries(testiwstring iwstring)
target_include_directories(testiwstring PRIVATE src/${PROJECT_SOURCE_DIR})
