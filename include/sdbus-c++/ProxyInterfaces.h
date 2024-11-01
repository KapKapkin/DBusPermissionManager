/**
 * (C) 2016 - 2021 KISTLER INSTRUMENTE AG, Winterthur, Switzerland
 * (C) 2016 - 2024 Stanislav Angelovic <stanislav.angelovic@protonmail.com>
 *
 * @file ProxyInterfaces.h
 *
 * Created on: Apr 8, 2019
 * Project: sdbus-c++
 * Description: High-level D-Bus IPC C++ library based on sd-bus
 *
 * This file is part of sdbus-c++.
 *
 * sdbus-c++ is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * sdbus-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with sdbus-c++. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SDBUS_CXX_PROXYINTERFACES_H_
#define SDBUS_CXX_PROXYINTERFACES_H_

#include <sdbus-c++/IProxy.h>
#include <cassert>
#include <string>
#include <memory>

// Forward declarations
namespace sdbus {
    class IConnection;
}

namespace sdbus {

    /********************************************//**
     * @class ProxyObjectHolder
     *
     * ProxyObjectHolder is a helper that simply owns and provides
     * access to a proxy object to other classes in the inheritance
     * hierarchy of a native-like proxy object based on generated
     * interface classes.
     *
     ***********************************************/
    class ProxyObjectHolder
    {
    protected:
        ProxyObjectHolder(std::unique_ptr<IProxy>&& proxy)
            : proxy_(std::move(proxy))
        {
            assert(proxy_ != nullptr);
        }

        const IProxy& getProxy() const
        {
            assert(proxy_ != nullptr);
            return *proxy_;
        }

        IProxy& getProxy()
        {
            assert(proxy_ != nullptr);
            return *proxy_;
        }

    private:
        std::unique_ptr<IProxy> proxy_;
    };

    /********************************************//**
     * @class ProxyInterfaces
     *
     * ProxyInterfaces is a helper template class that joins all interface classes of a remote
     * D-Bus object generated by sdbus-c++-xml2cpp to be used on the client (the proxy) side,
     * including some auxiliary classes. ProxyInterfaces is the class that native-like proxy
     * implementation classes written by users should inherit from and implement all pure virtual
     * methods. So the _Interfaces template parameter is a list of sdbus-c++-xml2cpp-generated
     * proxy-side interface classes representing interfaces of the corresponding remote D-Bus object.
     *
     * In the final adaptor class inherited from ProxyInterfaces, one needs to make sure:
     *   1. to call `registerProxy();` in the class constructor, and, conversely,
     *   2. to call `unregisterProxy();` in the class destructor,
     * so that the signals are subscribed to and unsubscribed from at a proper time.
     *
     ***********************************************/
    template <typename... _Interfaces>
    class ProxyInterfaces
        : protected ProxyObjectHolder
        , public _Interfaces...
    {
    public:
        /*!
         * @brief Creates native-like proxy object instance
         *
         * @param[in] destination Bus name that provides a D-Bus object
         * @param[in] objectPath Path of the D-Bus object
         *
         * This constructor overload creates a proxy that manages its own D-Bus connection(s).
         * For more information on its behavior, consult @ref createProxy(std::string,std::string)
         */
        ProxyInterfaces(ServiceName destination, ObjectPath objectPath)
            : ProxyObjectHolder(createProxy(std::move(destination), std::move(objectPath)))
            , _Interfaces(getProxy())...
        {
        }

        /*!
         * @brief Creates native-like proxy object instance
         *
         * @param[in] destination Bus name that provides a D-Bus object
         * @param[in] objectPath Path of the D-Bus object
         *
         * This constructor overload creates a proxy that manages its own D-Bus connection(s).
         * For more information on its behavior, consult @ref createProxy(std::string,std::string,sdbus::dont_run_event_loop_thread_t)
         */
        ProxyInterfaces(ServiceName destination, ObjectPath objectPath, dont_run_event_loop_thread_t)
            : ProxyObjectHolder(createProxy(std::move(destination), std::move(objectPath), dont_run_event_loop_thread))
            , _Interfaces(getProxy())...
        {
        }

        /*!
         * @brief Creates native-like proxy object instance
         *
         * @param[in] connection D-Bus connection to be used by the proxy object
         * @param[in] destination Bus name that provides a D-Bus object
         * @param[in] objectPath Path of the D-Bus object
         *
         * The proxy created this way just references a D-Bus connection owned and managed by the user.
         * For more information on its behavior, consult @ref createProxy(IConnection&,std::string,std::string)
         */
        ProxyInterfaces(IConnection& connection, ServiceName destination, ObjectPath objectPath)
            : ProxyObjectHolder(createProxy(connection, std::move(destination), std::move(objectPath)))
            , _Interfaces(getProxy())...
        {
        }

        /*!
         * @brief Creates native-like proxy object instance
         *
         * @param[in] connection D-Bus connection to be used by the proxy object
         * @param[in] destination Bus name that provides a D-Bus object
         * @param[in] objectPath Path of the D-Bus object
         *
         * The proxy created this way becomes an owner of the connection.
         * For more information on its behavior, consult @ref createProxy(std::unique_ptr<sdbus::IConnection>&&,std::string,std::string)
         */
        ProxyInterfaces(std::unique_ptr<sdbus::IConnection>&& connection, ServiceName destination, ObjectPath objectPath)
            : ProxyObjectHolder(createProxy(std::move(connection), std::move(destination), std::move(objectPath)))
            , _Interfaces(getProxy())...
        {
        }

        /*!
         * @brief Creates native-like proxy object instance
         *
         * @param[in] connection D-Bus connection to be used by the proxy object
         * @param[in] destination Bus name that provides a D-Bus object
         * @param[in] objectPath Path of the D-Bus object
         *
         * The proxy created this way becomes an owner of the connection.
         * For more information on its behavior, consult @ref createProxy(std::unique_ptr<sdbus::IConnection>&&,std::string,std::string,sdbus::dont_run_event_loop_thread_t)
         */
        ProxyInterfaces(std::unique_ptr<sdbus::IConnection>&& connection, ServiceName destination, ObjectPath objectPath, dont_run_event_loop_thread_t)
                : ProxyObjectHolder(createProxy(std::move(connection), std::move(destination), std::move(objectPath), dont_run_event_loop_thread))
                , _Interfaces(getProxy())...
        {
        }

        /*!
         * @brief Registers handlers for D-Bus signals of the remote object
         *
         * This function must be called in the constructor of the final proxy class that implements ProxyInterfaces.
         *
         * See also @ref IProxy::registerSignalHandler()
         */
        void registerProxy()
        {
            (_Interfaces::registerProxy(), ...);
        }

        /*!
         * @brief Unregisters the proxy so it no more receives signals and async call replies
         *
         * This function must be called in the destructor of the final proxy class that implements ProxyInterfaces.
         *
         * See underlying @ref IProxy::unregister()
         */
        void unregisterProxy()
        {
            getProxy().unregister();
        }

        /*!
         * @brief Returns reference to the underlying IProxy instance
         */
        using ProxyObjectHolder::getProxy;

    protected:
        using base_type = ProxyInterfaces;

        ProxyInterfaces(const ProxyInterfaces&) = delete;
        ProxyInterfaces& operator=(const ProxyInterfaces&) = delete;
        ProxyInterfaces(ProxyInterfaces&&) = delete;
        ProxyInterfaces& operator=(ProxyInterfaces&&) = delete;
        ~ProxyInterfaces() = default;
    };

}

#endif /* SDBUS_CXX_INTERFACES_H_ */
