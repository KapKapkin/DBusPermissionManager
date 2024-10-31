#include <filesystem>
#include <memory>
#include <ctime>

#include "time_server_glue.h"
#include "time_adaptor.h"
#include "permissions_client.h"

std::string get_exe_for_pid(pid_t pid)
{
    std::string path = std::format("/proc/{}/exe", pid);
    return std::filesystem::canonical(path).string();
}

TimeAdaptor::TimeAdaptor(sdbus::IConnection &connection, sdbus::ObjectPath path, sdbus::ServiceName permissions_service_name, sdbus::ObjectPath permissions_path) : AdaptorInterfaces(connection, std::move(path)), permissions_service_name(permissions_service_name), permissions_path(permissions_path), m_connection(connection)
{
    registerAdaptor();
}

TimeAdaptor::~TimeAdaptor()
{
    unregisterAdaptor();
}

uint64_t TimeAdaptor::GetSystemTime()
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
            throw sdbus::Error(sdbus::Error::Name("com.system.time.FileError"), "can't find sender path or something else went wrong.");
        }
    }();

    if (CheckPermission(path_to_exe))
    {
        std::time_t timestump = std::time(nullptr);
        return timestump;
    }
    else
    {
        throw sdbus::Error(sdbus::Error::Name("com.system.time.UnauthorizedAccess"), "Sender file has no SystemTime permission.");
    }
}

bool TimeAdaptor::CheckPermission(std::string &path)
{
    PermissionsProxy permissions = [&]()
    {
        try
        {
            return PermissionsProxy(m_connection, permissions_service_name, permissions_path);
        }
        catch (...)
        {
            throw sdbus::Error(sdbus::Error::Name("com.system.time.ServiceError"), "com.system.permissions sevice is not active.");
        }
    }();

    return permissions.CheckApplicationHasPermission(path, permissionCodeEnum::SystemTime);
}
