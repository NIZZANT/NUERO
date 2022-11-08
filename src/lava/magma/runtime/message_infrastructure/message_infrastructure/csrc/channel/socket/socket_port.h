// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#ifndef CHANNEL_SOCKET_SOCKET_PORT_H_
#define CHANNEL_SOCKET_SOCKET_PORT_H_

#include <message_infrastructure/csrc/channel/socket/socket.h>
#include <message_infrastructure/csrc/core/utils.h>
#include <message_infrastructure/csrc/core/abstract_port.h>

#include <string>
#include <vector>
#include <memory>

namespace message_infrastructure {

class SocketSendPort final : public AbstractSendPort {
 public:
  SocketSendPort(const std::string &name,
                 const SocketPair &socket,
                 const size_t &nbytes) :
                 name_(name), nbytes_(nbytes), socket_(socket) {}
  void Start();
  void Send(MetaDataPtr metadata);
  void Join();
  bool Probe();

 private:
  std::string name_;
  size_t nbytes_;
  SocketPair socket_;
};

using SocketSendPortPtr = std::shared_ptr<SocketSendPort>;

class SocketRecvPort final : public AbstractRecvPort {
 public:
  SocketRecvPort(const std::string &name,
                 const SocketPair &socket,
                 const size_t &nbytes) :
                 name_(name), nbytes_(nbytes), socket_(socket) {}
  void Start();
  bool Probe();
  MetaDataPtr Recv();
  void Join();
  MetaDataPtr Peek();

 private:
  std::string name_;
  size_t nbytes_;
  SocketPair socket_;
};

using SocketRecvPortPtr = std::shared_ptr<SocketRecvPort>;

}  // namespace message_infrastructure

#endif  // CHANNEL_SOCKET_SOCKET_PORT_H_