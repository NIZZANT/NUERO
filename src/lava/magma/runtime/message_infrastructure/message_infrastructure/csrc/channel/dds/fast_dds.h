// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#ifndef CHANNEL_DDS_FAST_DDS_H_
#define CHANNEL_DDS_FAST_DDS_H_

#include <message_infrastructure/csrc/channel/dds/dds.h>
#include <message_infrastructure/csrc/channel/dds/protos/fast_dds/metadataPubSubTypes.h>
#include <message_infrastructure/csrc/channel/dds/protos/fast_dds/metadata.h>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/Topic.hpp>

#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

#include <message_infrastructure/csrc/core/utils.h>

namespace message_infrastructure {

class FastDDSPubLisener final : public
                                eprosima::fastdds::dds::DataWriterListener {
 public:
  FastDDSPubLisener() : matched_(0), first_connected_(false) {}
  ~FastDDSPubLisener() override {}
  void on_publication_matched(
    eprosima::fastdds::dds::DataWriter* writer,
    const eprosima::fastdds::dds::PublicationMatchedStatus& info
  ) override;

  int matched_;
  bool first_connected_;
  eprosima::fastdds::dds::TypeSupport type_;
};

using FastDDSPubLisenerPtr = std::shared_ptr<FastDDSPubLisener>;

class FastDDSPublisher final : public DDSPublisher {
 public:
  FastDDSPublisher(const size_t &max_samples,
                   const size_t &nbytes,
                   const std::string &topic_name) :
                   type_(new DDSMetaDataPubSubType()),
                   max_samples_(max_samples),
                   nbytes_(nbytes),
                   topic_name_(topic_name)
                    {};
  ~FastDDSPublisher();
  int Init();
  bool Publish(MetaDataPtr metadata);
 private:
  void InitParticipant(); // Add type for shm, tcp or others
  void InitDataWriter();
  
  FastDDSPubLisenerPtr listener_ = nullptr;
  std::shared_ptr<DDSMetaData> dds_metadata_;
  eprosima::fastdds::dds::DomainParticipant* participant_ = nullptr;
  eprosima::fastdds::dds::Publisher* publisher_ = nullptr;
  eprosima::fastdds::dds::Topic* topic_ = nullptr;
  eprosima::fastdds::dds::DataWriter* writer_ = nullptr;
  eprosima::fastdds::dds::TypeSupport type_;
  bool stop_;
  int max_samples_;
  size_t nbytes_;
  std::string topic_name_;
};

class FastDDSSubscriber final : public DDSSubscriber {
 public:
  FastDDSSubscriber(const size_t &max_samples,
                   const size_t &nbytes,
                   const std::string &topic_name) :
                   type_(new DDSMetaDataPubSubType()),
                   max_samples_(max_samples),
                   nbytes_(nbytes),
                   topic_name_(topic_name)
                    {};
  ~FastDDSSubscriber();
  int Init();
  void Run();
  MetaDataPtr Read();
 private:
  void InitParticipant();
  void InitDataReader();
  std::shared_ptr<DDSMetaData> dds_metadata_;
  eprosima::fastdds::dds::DomainParticipant* participant_ = nullptr;
  eprosima::fastdds::dds::Subscriber* subscriber_ = nullptr;
  eprosima::fastdds::dds::Topic* topic_ = nullptr;
  eprosima::fastdds::dds::DataReader* reader_ = nullptr;
  eprosima::fastdds::dds::TypeSupport type_;
  int max_samples_;
  size_t nbytes_;
  std::string topic_name_;
};

}  // namespace message_infrastructure

#endif