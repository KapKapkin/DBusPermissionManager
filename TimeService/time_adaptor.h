#ifndef TIME_ADAPTOR_H
#define TIME_ADAPTOR_H

#include <sdbus-c++/sdbus-c++.h>

#include "time_server_glue.h"
#include "permissions_client.h"
#include "common.h"
#include "memory"

class TimeAdaptor final : public sdbus::AdaptorInterfaces<com::system::time_adaptor>
{
public:
    TimeAdaptor(sdbus::IConnection &connection, sdbus::ObjectPath path, sdbus::ServiceName, sdbus::ObjectPath);
    ~TimeAdaptor();

    uint64_t GetSystemTime();

private:
    bool CheckPermission(std::string &path);

    sdbus::IConnection &m_connection;
    sdbus::ServiceName permissions_service_name;
    sdbus::ObjectPath permissions_path;
};

#endif