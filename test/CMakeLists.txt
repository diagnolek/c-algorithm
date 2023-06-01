add_executable(unit_tests
        unit_tests.cpp
        dfs_test.cpp
        bfs_test.cpp
        )

target_link_libraries(unit_tests algorithm)

add_test(NAME DfsAlgorithm COMMAND unit_tests dfs)
add_test(NAME BfsAlgorithm COMMAND unit_tests bfs)