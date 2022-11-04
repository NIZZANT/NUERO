// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#ifndef CORE_UTILS_H_
#define CORE_UTILS_H_

#include <memory>
#include <chrono>  // NOLINT
#include <thread>  // NOLINT

#define MAX_ARRAY_DIMS (5)
#define SLEEP_US (1)

namespace message_infrastructure {

enum ProcessType {
  ErrorProcess = 0,
  ParentProcess = 1,
  ChildProcess = 2
};

enum ChannelType {
  SHMEMCHANNEL = 0,
  RPCCHANNEL = 1,
  DDSCHANNEL = 2,
  SOCKETCHANNEL = 3
};

enum DDSTransportType {
  DDSSHM = 0,
  DDSTCPv4 = 1,
  DDSTCPv6 = 2,
  DDSUDPv4 = 3,
  DDSUDPv6 = 4
};

enum DDSBackendType {
  FASTDDSBackend = 0,
  CycloneDDSBackend = 1
};

enum DDSInitErrorType {
  DDSParticipantError = 1,
  DDSPublisherError = 2,
  DDSSubscriberError = 3,
  DDSTopicError = 4,
  DDSDataWriterError = 5,
  DDSDataReaderError = 6,
  DDSTypeParserError = 7
};

struct MetaData {
  int64_t nd;
  int64_t type;
  int64_t elsize;
  int64_t total_size;
  int64_t dims[MAX_ARRAY_DIMS] = {0};
  int64_t strides[MAX_ARRAY_DIMS] = {0};
  void* mdata;
};

using MetaDataPtr = std::shared_ptr<MetaData>;

namespace helper {

static void Sleep() {
  std::this_thread::sleep_for(std::chrono::nanoseconds(1));
}
}
}  // namespace message_infrastructure

#endif  // CORE_UTILS_H_
