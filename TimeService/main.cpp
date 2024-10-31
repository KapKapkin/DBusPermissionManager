#include "permissions_client.h"
#include "time_adaptor.h"

int main() {
  auto connection = sdbus::createSessionBusConnection();
  sdbus::ServiceName timeServiceName("com.system.time");
  sdbus::ObjectPath timeObjectPath{"/com/system/time"};

  sdbus::ServiceName permissionsServiceName("com.system.permissions");
  sdbus::ObjectPath permissionsObjectPath{"/com/system/permissions"};

  connection->requestName(timeServiceName);

  TimeAdaptor adapter(*connection, timeObjectPath, permissionsServiceName,
                      permissionsObjectPath);

  connection->enterEventLoop();
}