// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#include <memory>
#include <string>
#include <vector>

#include "channel_proxy.h"
#include "abstract_channel.h"
#include "utils.h"
#include "channel_factory.h"
#include "port_proxy.h"

namespace message_infrastructure {

ChannelProxy::ChannelProxy(const ChannelType &channel_type,
                           const size_t &size,
                           const size_t &nbytes,
                           const std::string &name) {
  ChannelFactory &channel_factory = GetChannelFactory();
  channel_ = channel_factory.GetChannel(channel_type,
                                        size,
                                        nbytes,
                                        name);
  send_port_ = std::make_shared<SendPortProxy>(channel_type,
                  channel_->GetSendPort());
  recv_port_ = std::make_shared<RecvPortProxy>(channel_type,
                  channel_->GetRecvPort());
}
SendPortProxyPtr ChannelProxy::GetSendPort() {
    return send_port_;
}
RecvPortProxyPtr ChannelProxy::GetRecvPort() {
    return recv_port_;
}

}  // namespace message_infrastructure
