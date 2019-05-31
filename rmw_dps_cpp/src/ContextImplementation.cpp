
#include "rmw_dps_cpp/ContextImplementation.hpp"

#include "rmw_dps_cpp/custom_publisher_info.hpp"
#include "rmw_dps_cpp/custom_subscriber_info.hpp"

void rmw_context_impl_t::add_subscription(rmw_subscription_t* sub)
{
    std::string topic = sub->topic_name;
    topics_subscriptions_map[topic].insert(sub);
}

void rmw_context_impl_t::remove_subscription(rmw_subscription_t* sub)
{

    std::cout<<"Removing subscription"<<std::endl;
    /*
    if (sub == nullptr){
        std::cout<<"sub is nullptr"<<std::endl;
    }
    else{
        if (sub->topic_name == nullptr){
            std::cout<<"sub->topic_name is nullptr"<<std::endl;
        }
    }
    std::string topic = sub->topic_name;
    std::cout<<"Size before: "<< topics_subscriptions_map[topic].size()<<std::endl;
    topics_subscriptions_map[topic].erase(sub);
    std::cout<<"Size after: "<< topics_subscriptions_map[topic].size()<<std::endl;
    */
}


void rmw_context_impl_t::push_to_queues(std::string topic_name, IPCMessageT ros_message)
{
    for(auto sub : topics_subscriptions_map[topic_name]) {
        auto info = static_cast<CustomSubscriberInfo *>(sub->data);
        auto queue = info->queue_;
        auto listener = info->listener_;
        Listener::onIPCPublication(listener, queue, ros_message);
    }

}