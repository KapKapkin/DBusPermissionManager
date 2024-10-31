#include "time_client.h"

TimeProxy::TimeProxy(sdbus::IConnection &connection, sdbus::ServiceName destination, sdbus::ObjectPath path)
    : ProxyInterfaces(connection, std::move(destination), std::move(path))
{
    registerProxy();
}

TimeProxy::~TimeProxy()
{
    unregisterProxy();
}