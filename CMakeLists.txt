cmake_minimum_required (VERSION 3.8)

project("DBusPermissionManager")

set(SOURCE_DIR "./src")

add_subdirectory("./thirdparty/SQLiteCpp")
add_subdirectory("./thirdparty/sdbus-cpp")


add_executable(DBusPermissionManager "${SOURCE_DIR}/main.cpp" "${SOURCE_DIR}/db.cpp" "${SOURCE_DIR}/db.h")

target_link_libraries(DBusPermissionManager PRIVATE sdbus-c++ SQLiteCpp sqlite3 pthread dl)
