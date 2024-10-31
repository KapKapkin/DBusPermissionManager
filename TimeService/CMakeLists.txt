

project(DBusTimeService CXX)
set(CMAKE_CXX_STANDARD 20)


find_package(sdbus-c++ REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(DBusTimeService  "main.cpp" "time_adaptor.cpp" "permissions_client.cpp")
target_link_libraries(DBusTimeService PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(DBusTimeService PRIVATE SQLiteCpp sqlite3 pthread dl)


