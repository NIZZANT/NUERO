// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#ifndef INCLUDE_ABSTRACT_PORT_H_
#define INCLUDE_ABSTRACT_PORT_H_

#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "shm.h"
#include "utils.h"

namespace message_infrastructure {

class AbstractPort {
 public:
  virtual int Start() = 0;
  virtual int Join() = 0;

  std::string name_;
  pybind11::dtype dtype_;
  ssize_t *shape_ = NULL;
  size_t size_;
};

class AbstractSendPort : public AbstractPort {
 public:
  virtual int Send() = 0;
};

class AbstractRecvPort : public AbstractPort {
 public:
  virtual int Recv() = 0;
};

using PortPtr = AbstractPort *;
using SendPortPtr = AbstractSendPort *;
using RecvPortPtr = AbstractRecvPort *;

} // namespace message_infrastructure

#endif