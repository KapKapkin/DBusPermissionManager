cmake_minimum_required (VERSION 3.8)

project("DBusPermissionManager")

set(SOURCE_DIR "./src")

add_executable(DBusPermissionManager "${SOURCE_DIR}/main.cpp")

target_link_libraries(DBusPermissionManager PRIVATE "/home/oleg0/projects/DBusPermissionManager/lib/libsdbus-c++.so")

target_include_directories(DBusPermissionManager PUBLIC "./include")