cmake_minimum_required (VERSION 3.8)

project(DBusPermissionManager CXX)
set(CMAKE_CXX_STANDARD 20)

set(BUILD_TESTS ON)

find_package(sdbus-c++ REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(DBusPermissionManager  "main.cpp" "db.cpp" "permissions_adaptor.cpp")
target_link_libraries(DBusPermissionManager PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(DBusPermissionManager PRIVATE SQLiteCpp sqlite3 pthread dl)




