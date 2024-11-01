
set(CMAKE_CXX_STANDARD 20)

get_filename_component(LIB_DIR "../libs" ABSOLUTE)

add_executable(DBusTimeService  "main.cpp" "time_adaptor.cpp" "permissions_client.cpp")

target_link_libraries(DBusTimeService PRIVATE sdbus-c++ SQLiteCpp sqlite3 pthread dl)


target_compile_options(DBusTimeService PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)