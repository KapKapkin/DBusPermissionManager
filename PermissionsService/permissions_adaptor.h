#ifndef PERMISSIONS_ADAPTER_H
#define PERMISSIONS_ADAPTER_H

#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <filesystem>
#include <format>

#include "permissions-server-glue.h"
#include "common.h"

class PermissionsAdapter final : public sdbus::AdaptorInterfaces<com::system::permissions_adaptor>
{
public:
    PermissionsAdapter(sdbus::IConnection &connection, sdbus::ObjectPath path);

    ~PermissionsAdapter();

    void RequestPermission(const int32_t &permissionEnumCode) override;
    bool CheckApplicationHasPermission(const std::string &applicationExecPath, const int32_t &permissionEnumCode) override;
};

#endif