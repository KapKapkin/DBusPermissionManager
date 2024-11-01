
set(CMAKE_CXX_STANDARD 20)



get_filename_component(LIB_DIR "../libs" ABSOLUTE)
add_executable(DBusTimeRequester  "main.cpp" "time_client.cpp" "permissions_client.cpp")

target_include_directories(DBusTimeRequester PUBLIC ../include)
target_link_directories(DBusTimeRequester PUBLIC LIB_DIR)
target_link_libraries(DBusTimeRequester "${LIB_DIR}/libsdbus-c++.so" SQLiteCpp sqlite3 pthread dl)

target_compile_options(DBusTimeRequester PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)