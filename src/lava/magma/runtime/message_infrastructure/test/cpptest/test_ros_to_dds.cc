// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#include <message_infrastructure/csrc/channel/dds/fast_dds.h>
#include <message_infrastructure/csrc/core/channel_factory.h>
#include <message_infrastructure/csrc/channel/dds/dds_channel.h>

using namespace message_infrastructure;

#define LOOP_NUM 100

int main() {
	auto dds_channel = GetChannelFactory()
    .GetDDSChannel("rt/dds_topic", DDSUDPv4, FASTDDSBackend, 10);
    // .GetDDSChannel("rt/dds_topic", DDSSHM, FASTDDSBackend, 10);
	auto dds_recv = dds_channel->GetRecvPort();
	int loop = LOOP_NUM;

	dds_recv->Start();
	while (loop--) {
		MetaDataPtr res = dds_recv->Recv();
		printf("DDS recv : %d\n", *reinterpret_cast<int64_t*>(res->mdata));
	}
	dds_recv->Join();
	return 0;
}