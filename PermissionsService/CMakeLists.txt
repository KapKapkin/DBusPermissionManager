
project(DBusPermissionService CXX)
set(CMAKE_CXX_STANDARD 20)

set(BUILD_TESTS ON)

find_package(sdbus-c++ REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(DBusPermissionService  "main.cpp" "db.cpp" "permissions_adaptor.cpp")
target_link_libraries(DBusPermissionService PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(DBusPermissionService PRIVATE SQLiteCpp sqlite3 pthread dl)


target_compile_options(DBusPermissionService PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)


