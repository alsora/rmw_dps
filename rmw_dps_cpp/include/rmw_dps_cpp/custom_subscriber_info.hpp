// Copyright 2018 Intel Corporation All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RMW_DPS_CPP__CUSTOM_SUBSCRIBER_INFO_HPP_
#define RMW_DPS_CPP__CUSTOM_SUBSCRIBER_INFO_HPP_

#include <dps/dps.h>

#include "rmw_dps_cpp/Listener.hpp"
#include "rmw_dps_cpp/CborStream.hpp"
#include "rmw_dps_cpp/ContextImplementation.hpp"

#include "rmw_dps_cpp/concurrent_queue.h"
#include "rmw_dps_cpp/cpqueue.h"

#include <memory>

#include <iostream>

class Listener;

typedef struct CustomSubscriberInfo
{

  typedef std::shared_ptr<rmw_dps_cpp::cbor::RxStream> IPCMessageT;


  CustomSubscriberInfo()
  {
    //queue_ = std::make_shared<moodycamel::ConcurrentQueue<IPCMessageT>>();
    queue_ = std::make_shared<ConsumerProducerQueue<IPCMessageT>>(100);
  }


  DPS_Subscription * subscription_;
  Listener * listener_;
  void * type_support_;
  const char * typesupport_identifier_;
  //std::shared_ptr<moodycamel::ConcurrentQueue<IPCMessageT>> queue_;
  std::shared_ptr<ConsumerProducerQueue<IPCMessageT>> queue_;

  bool hasData()
  {
    //return (queue_->size_approx() > 0 || listener_->hasData());
    return (!queue_->isEmpty() || listener_->hasData());
  }


} CustomSubscriberInfo;

#endif  // RMW_DPS_CPP__CUSTOM_SUBSCRIBER_INFO_HPP_
