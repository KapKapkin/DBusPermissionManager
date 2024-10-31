#include <chrono>
#include <ctime>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

#include "common.h"
#include "permissions_client.h"
#include "time_client.h"

void print_time(uint64_t i_time) {
  auto current_time = static_cast<time_t>(i_time);
  std::cout << std::ctime(&current_time) << std::endl;
}

int main() {
  auto connection = sdbus::createSessionBusConnection();
  sdbus::ServiceName timeServiceName("com.system.time");
  sdbus::ObjectPath timeObjectPath{"/com/system/time"};

  sdbus::ServiceName permissionsServiceName("com.system.permissions");
  sdbus::ObjectPath permissionsObjectPath{"/com/system/permissions"};

  TimeProxy time_proxy(*connection, timeServiceName, timeObjectPath);
  PermissionsProxy permissions_proxy(*connection, permissionsServiceName,
                                     permissionsObjectPath);
  try {
    print_time(time_proxy.GetSystemTime());
  } catch (const sdbus::Error &e) {
    if (e.getName() ==
        sdbus::Error::Name("com.system.time.UnauthorizedAccess")) {
      permissions_proxy.RequestPermission(permissionCodeEnum::SystemTime);
      print_time(time_proxy.GetSystemTime());
    } else {
      throw;
    }
  }
}