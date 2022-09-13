// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#ifndef SHMEM_CHANNEL_H_
#define SHMEM_CHANNEL_H_

// #include <pybind11/pybind11.h>
// #include <pybind11/numpy.h>
#include <semaphore.h>

#include <memory>
#include <string>

#include "abstract_channel.h"
#include "shm.h"
#include "shmem_port.h"
#include "utils.h"
#include "port_proxy.h"

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
  SharedMemoryPtr shm_ = NULL;
  ShmemSendPortPtr send_port_ = NULL;
  ShmemRecvPortPtr recv_port_ = NULL;
};

std::shared_ptr<ShmemChannel> GetShmemChannel(const size_t &size,
                              const size_t &nbytes,
                              const std::string &name);

}  // namespace message_infrastructure

#endif  // SHMEM_CHANNEL_H_
