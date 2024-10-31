
/*
 * This file was automatically generated by sdbus-c++-xml2cpp; DO NOT EDIT!
 */

#ifndef __sdbuscpp__permissions_server_glue_h__adaptor__H__
#define __sdbuscpp__permissions_server_glue_h__adaptor__H__

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace com
{
    namespace system
    {

        class permissions_adaptor
        {
        public:
            static constexpr const char *INTERFACE_NAME = "com.system.permissions";

        protected:
            permissions_adaptor(sdbus::IObject &object)
                : m_object(object)
            {
            }

            permissions_adaptor(const permissions_adaptor &) = delete;
            permissions_adaptor &operator=(const permissions_adaptor &) = delete;
            permissions_adaptor(permissions_adaptor &&) = delete;
            permissions_adaptor &operator=(permissions_adaptor &&) = delete;

            ~permissions_adaptor() = default;

            void registerAdaptor()
            {
                m_object.addVTable(sdbus::registerMethod("RequestPermission").withInputParamNames("permissionEnumCode").implementedAs([this](const int32_t &permissionEnumCode)
                                                                                                                                      { return this->RequestPermission(permissionEnumCode); }),
                                   sdbus::registerMethod("CheckApplicationHasPermission").withInputParamNames("applicationExecPath", "permissionEnumCode").withOutputParamNames("status").implementedAs([this](const std::string &applicationExecPath, const int32_t &permissionEnumCode)
                                                                                                                                                                                                        { return this->CheckApplicationHasPermission(applicationExecPath, permissionEnumCode); }))
                    .forInterface(INTERFACE_NAME);
            }

        private:
            virtual void RequestPermission(const int32_t &permissionEnumCode) = 0;
            virtual bool CheckApplicationHasPermission(const std::string &applicationExecPath, const int32_t &permissionEnumCode) = 0;

        private:
            sdbus::IObject &m_object;
        };

    }
} // namespaces

#endif