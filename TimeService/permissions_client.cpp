#include "permissions_client.h"

PermissionsProxy::PermissionsProxy(sdbus::IConnection &connection, sdbus::ServiceName destination, sdbus::ObjectPath path)
    : ProxyInterfaces(connection, std::move(destination), std::move(path))
{
    registerProxy();
}

PermissionsProxy::~PermissionsProxy()
{
    unregisterProxy();
}