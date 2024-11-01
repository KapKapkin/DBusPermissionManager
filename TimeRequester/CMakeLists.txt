
set(CMAKE_CXX_STANDARD 20)


add_executable(DBusTimeRequester  "main.cpp" "time_client.cpp" "permissions_client.cpp")

target_link_libraries(DBusTimeRequester PRIVATE sdbus-c++ SQLiteCpp sqlite3 pthread dl)

target_compile_options(DBusTimeRequester PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)