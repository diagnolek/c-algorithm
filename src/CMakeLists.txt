add_executable(dfs dfs.cpp)
add_executable(bfs bfs.cpp)
add_executable(kruskala kruskala.cpp)
add_executable(prima prima.cpp)
add_executable(dijkstry dijkstry.cpp)
add_executable(b-forda b-forda.cpp)
add_executable(cycle cycle.cpp)

target_link_libraries(dfs algorithm)
target_link_libraries(bfs algorithm)
target_link_libraries(kruskala algorithm)
target_link_libraries(prima algorithm)
target_link_libraries(dijkstry algorithm)
target_link_libraries(b-forda algorithm)
target_link_libraries(cycle algorithm)