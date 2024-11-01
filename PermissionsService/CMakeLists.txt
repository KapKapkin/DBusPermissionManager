
set(CMAKE_CXX_STANDARD 20)

get_filename_component(LIB_DIR "../libs" ABSOLUTE)

add_executable(DBusPermissionService   "main.cpp" "db.cpp" "permissions_adaptor.cpp")

target_include_directories(DBusPermissionService PUBLIC ../include)
target_link_directories(DBusPermissionService PUBLIC LIB_DIR)
target_link_libraries(DBusPermissionService "${LIB_DIR}/libsdbus-c++.so" SQLiteCpp sqlite3 pthread dl)

target_compile_options(DBusPermissionService PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
