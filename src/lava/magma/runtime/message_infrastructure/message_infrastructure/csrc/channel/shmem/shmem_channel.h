// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#ifndef CHANNEL_SHMEM_SHMEM_CHANNEL_H_
#define CHANNEL_SHMEM_SHMEM_CHANNEL_H_

#include <message_infrastructure/csrc/core/abstract_channel.h>
#include <message_infrastructure/csrc/core/abstract_port.h>
#include <message_infrastructure/csrc/channel/shmem/shm.h>
#include <message_infrastructure/csrc/channel/shmem/shmem_port.h>

#include <memory>
#include <string>

namespace message_infrastructure {

class ShmemChannel : public AbstractChannel {
 public:
  ShmemChannel() {}
  ShmemChannel(const std::string &src_name,
               const std::string &dst_name,
               const size_t &size,
               const size_t &nbytes);
  AbstractSendPortPtr GetSendPort();
  AbstractRecvPortPtr GetRecvPort();
 private:
  SharedMemoryPtr shm_ = nullptr;
  ShmemSendPortPtr send_port_ = nullptr;
  AbstractRecvPortPtr recv_port_ = nullptr;
};

std::shared_ptr<ShmemChannel> GetShmemChannel(const size_t &size,
                              const size_t &nbytes,
                              const std::string &src_name,
                              const std::string &dst_name);

}  // namespace message_infrastructure

#endif  // CHANNEL_SHMEM_SHMEM_CHANNEL_H_
