#include <sdbus-c++/sdbus-c++.h>

#include "permissions_adaptor.h"
#include "db.h"

int main(int argc, char *argv[])
{
    db::Database::Instance().initDB();
    auto connection = sdbus::createSessionBusConnection();
    sdbus::ServiceName permissionsServiceName("com.system.permissions");

    connection->requestName(permissionsServiceName);

    sdbus::ObjectPath objectPath{"/com/system/permissions"};
    PermissionsAdapter adapter(*connection, objectPath);

    connection->enterEventLoop();

    return 0;
}
