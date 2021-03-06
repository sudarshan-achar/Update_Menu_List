
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__proxy_d_h__PROXY_MARSHAL_H
#define __dbusxx__proxy_d_h__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>
#include <cassert>

namespace com {
namespace example {

class UpdateList_proxy: public ::DBus::InterfaceProxy
{
public:

    UpdateList_proxy()
    : ::DBus::InterfaceProxy("com.example.UpdateList")
    {
    }

    virtual ~UpdateList_proxy(){}

public:

    /* properties exported by this interface */
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */
    int32_t AddClient(const ::DBus::Struct< std::string, int32_t >& info)
    {
    	//std::cout<<"UpdateList_proxy:: int32_t AddClient\n"<<info._1<<"  "<<info._2<<"\n";
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << info;
        call.member("AddClient");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    int32_t RemoveClient(const std::string& name, const int32_t& passcode)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << name;
        wi << passcode;
        call.member("RemoveClient");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    int32_t UpdateMenuList(const int32_t& password, const ::DBus::Struct< int32_t, int32_t, std::string, std::string >& elements)
    {
        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        wi << password;
        wi << elements;
        call.member("UpdateMenuList");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    int32_t GetClientListSize()
    {
        ::DBus::CallMessage call;
        call.member("GetClientListSize");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    int32_t GetMenuListSize()
    {
        ::DBus::CallMessage call;
        call.member("GetMenuListSize");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        int32_t argout;
        ri >> argout;
        return argout;
    }

    ::DBus::Struct< std::string, int32_t > GetClientInfo()
    {
        ::DBus::CallMessage call;
        call.member("GetClientInfo");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        ::DBus::Struct< std::string, int32_t > argout;
        ri >> argout;
        return argout;
    }

    ::DBus::Struct< int32_t, int32_t, std::string, std::string > GetMenuInfo()
    {
        ::DBus::CallMessage call;
        call.member("GetMenuInfo");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        ::DBus::Struct< int32_t, int32_t, std::string, std::string > argout;
        ri >> argout;
        return argout;
    }


public:

    /* signal handlers for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
};

} } 
#endif //__dbusxx__proxy_d_h__PROXY_MARSHAL_H
