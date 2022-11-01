// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#include <message_infrastructure/csrc/channel_proxy.h>
#include <message_infrastructure/csrc/core/channel_factory.h>
#include <memory>

namespace message_infrastructure {

ChannelProxy::ChannelProxy(const ChannelType &channel_type,
                           const size_t &size,
                           const size_t &nbytes,
                           const std::string &src_name,
                           const std::string &dst_name) {
  ChannelFactory &channel_factory = GetChannelFactory();
  channel_ = channel_factory.GetChannel(channel_type,
                                        size,
                                        nbytes,
                                        src_name,
                                        dst_name);
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

#if defined(GRPC_CHANNEL)
GetRPCChannelProxy::GetRPCChannelProxy(const std::string &url,
                                       const int &port,
                                       const std::string &src_name,
                                       const std::string &dst_name,
                                       const size_t &size) {
  ChannelFactory &channel_factory = GetChannelFactory();
  channel_ = channel_factory.GetRPCChannel(url, port, src_name, dst_name, size);
  send_port_ = std::make_shared<SendPortProxy>(channel_type,
                                               channel_->GetSendPort());
  recv_port_ = std::make_shared<RecvPortProxy>(channel_type,
                                               channel_->GetRecvPort());
}
GetRPCChannelProxy::GetRPCChannelProxy(const std::string &src_name,
                                       const std::string &dst_name,
                                       const size_t &size) {
  ChannelFactory &channel_factory = GetChannelFactory();
  channel_ = channel_factory.GetDefRPCChannel(src_name, dst_name, size);
  send_port_ = std::make_shared<SendPortProxy>(channel_type,
                                               channel_->GetSendPort());
  recv_port_ = std::make_shared<RecvPortProxy>(channel_type,
                                               channel_->GetRecvPort());
}
SendPortProxyPtr GetRPCChannelProxy::GetSendPort() {
    return send_port_;
}
RecvPortProxyPtr GetRPCChannelProxy::GetRecvPort() {
    return recv_port_;
}
#endif
}  // namespace message_infrastructure
