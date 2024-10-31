

project(DBusTimeRequester CXX)
set(CMAKE_CXX_STANDARD 20)


find_package(sdbus-c++ REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(DBusTimeRequester  "main.cpp" "time_client.cpp" "permissions_client.cpp")
target_link_libraries(DBusTimeRequester PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(DBusTimeRequester PRIVATE SQLiteCpp sqlite3 pthread dl)


target_compile_options(DBusTimeRequester PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)