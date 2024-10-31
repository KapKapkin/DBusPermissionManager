#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <filesystem>
#include <format>

#include "permissions_adaptor.h"
#include "permissions-server-glue.h"
#include "common.h"
#include "db.h"

std::string get_exe_for_pid(pid_t pid)
{
    std::string path = std::format("/proc/{}/exe", pid);
    return std::filesystem::canonical(path).string();
}

PermissionsAdapter::PermissionsAdapter(sdbus::IConnection &connection, sdbus::ObjectPath path) : AdaptorInterfaces(connection, std::move(path))
{
    registerAdaptor();
}

PermissionsAdapter::~PermissionsAdapter()
{
    unregisterAdaptor();
}

void PermissionsAdapter::RequestPermission(const int32_t &permissionEnumCode)
{
    auto obj = getObject().getCurrentlyProcessedMessage();
    std::string path_to_exe = get_exe_for_pid(obj.getCredsPid());
    db::Database::Instance().setPermission(path_to_exe, permissionEnumCode);
}
bool PermissionsAdapter::CheckApplicationHasPermission(const std::string &applicationExecPath, const int32_t &permissionEnumCode)
{
    std::string path_canonical = std::filesystem::weakly_canonical(applicationExecPath).string();
    return db::Database::Instance().hasPermission(path_canonical, permissionEnumCode);
}
