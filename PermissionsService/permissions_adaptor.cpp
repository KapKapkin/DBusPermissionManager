#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <filesystem>
#include <format>

#include "permissions_adaptor.h"
#include "permissions_server_glue.h"
#include "common.h"
#include "db.h"

std::string get_exe_for_pid(pid_t pid)
{
    std::string path = std::format("/proc/{}/exe", pid);
    return std::filesystem::canonical(path).string();
}

PermissionsAdaptor::PermissionsAdaptor(sdbus::IConnection &connection, sdbus::ObjectPath path) : AdaptorInterfaces(connection, std::move(path))
{
    registerAdaptor();
}

PermissionsAdaptor::~PermissionsAdaptor()
{
    unregisterAdaptor();
}

void PermissionsAdaptor::RequestPermission(const int32_t &permissionEnumCode)
{
    auto obj = getObject().getCurrentlyProcessedMessage();
    std::string path_to_exe = [&]()
    {
        try
        {
            return get_exe_for_pid(obj.getCredsPid());
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            throw sdbus::Error(sdbus::Error::Name("com.system.permissions.FileError"), "can't find sender path or something else went wrong.");
        }
    }();
    db::Database::Instance().setPermission(path_to_exe, permissionEnumCode);
}
bool PermissionsAdaptor::CheckApplicationHasPermission(const std::string &applicationExecPath, const int32_t &permissionEnumCode)
{
    std::string path_canonical = [&]()
    {
        try
        {
            return std::filesystem::canonical(applicationExecPath).string();
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            throw sdbus::Error(sdbus::Error::Name("com.system.permissions.FileError"), "can't find file with given path or something else went wrong.");
        }
    }();

    return db::Database::Instance().hasPermission(path_canonical, permissionEnumCode);
}
