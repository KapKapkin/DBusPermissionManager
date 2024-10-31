#ifndef PERMISSIONS_ADAPTOR_H
#define PERMISSIONS_ADAPTOR_H

#include <sdbus-c++/sdbus-c++.h>

#include "common.h"
#include "permissions_server_glue.h"

class PermissionsAdaptor final
    : public sdbus::AdaptorInterfaces<com::system::permissions_adaptor> {
public:
  PermissionsAdaptor(sdbus::IConnection &connection, sdbus::ObjectPath path);

  ~PermissionsAdaptor();

  void RequestPermission(const int32_t &permissionEnumCode) override;
  bool
  CheckApplicationHasPermission(const std::string &applicationExecPath,
                                const int32_t &permissionEnumCode) override;
};

#endif