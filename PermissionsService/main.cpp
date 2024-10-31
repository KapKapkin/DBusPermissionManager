#include <sdbus-c++/sdbus-c++.h>

#include "db.h"
#include "permissions_adaptor.h"

int main() {
  db::Database::Instance().initDB();
  auto connection = sdbus::createSessionBusConnection();
  sdbus::ServiceName permissionsServiceName("com.system.permissions");
  sdbus::ObjectPath objectPath{"/com/system/permissions"};

  connection->requestName(permissionsServiceName);

  PermissionsAdaptor adapter(*connection, objectPath);

  connection->enterEventLoop();

  return 0;
}
