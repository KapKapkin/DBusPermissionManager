#ifndef PERMISSIONS_CLIENT_H
#define PERMISSIONS_CLIENT_H

#include <sdbus-c++/sdbus-c++.h>

#include "permissions_client_glue.h"

class PermissionsProxy final
    : public sdbus::ProxyInterfaces<com::system::permissions_proxy> {
public:
  PermissionsProxy(sdbus::IConnection &connection,
                   sdbus::ServiceName destination, sdbus::ObjectPath path);

  ~PermissionsProxy();
};

#endif