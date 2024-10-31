#ifndef TIME_CLIENT_H
#define TIME_CLIENT_H

#include <sdbus-c++/sdbus-c++.h>

#include "time_client_glue.h"

class TimeProxy final : public sdbus::ProxyInterfaces<com::system::time_proxy> {
public:
  TimeProxy(sdbus::IConnection &connection, sdbus::ServiceName destination,
            sdbus::ObjectPath path);

  ~TimeProxy();
};

#endif