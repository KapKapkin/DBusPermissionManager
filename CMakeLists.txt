cmake_minimum_required (VERSION 3.8)
project(DBusPermissionManager CXX)


add_subdirectory("./thirdparty/sdbus-cpp")
add_subdirectory("./thirdparty/SQLiteCpp")

add_subdirectory("./PermissionsService")
add_subdirectory("./TimeService")
add_subdirectory("./TimeRequester")
