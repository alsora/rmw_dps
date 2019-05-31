
#ifndef RMW_DPS_CPP__CONTEXT_IMPLEMENTATION_HPP_
#define RMW_DPS_CPP__CONTEXT_IMPLEMENTATION_HPP_

#include <map>
#include <memory>
#include <set>
#include <string>

#include "rmw/rmw.h"

#include "rmw_dps_cpp/Listener.hpp"
#include "rmw_dps_cpp/CborStream.hpp"

#include <iostream>



typedef struct rmw_context_impl_t
{

    typedef std::shared_ptr<rmw_dps_cpp::cbor::RxStream> IPCMessageT;


    rmw_context_impl_t(){}


    void add_subscription(rmw_subscription_t* sub);

    void remove_subscription(rmw_subscription_t* sub);

    void push_to_queues(std::string topic_name, IPCMessageT ros_message);

    std::map<std::string, std::set<rmw_subscription_t*>> topics_subscriptions_map;


}rmw_context_impl_t;

#endif //RMW_DPS_CPP__CONTEXT_IMPLEMENTATION_HPP_
