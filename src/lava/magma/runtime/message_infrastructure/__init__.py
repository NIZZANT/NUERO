# Copyright (C) 2022 Intel Corporation
# SPDX-License-Identifier: BSD-3-Clause
# See: https://spdx.org/licenses/

from ctypes import CDLL, RTLD_GLOBAL
import os


def load_library():
    lib_name = 'libmessage_infrastructure.so'
    here = os.path.abspath(__file__)
    lib_path = os.path.join(os.path.dirname(here), lib_name)
    if (os.path.exists(lib_path)):
        CDLL(lib_path, mode=RTLD_GLOBAL)
    else:
        print("Warn: No library file")
    extra_lib_folder = os.path.join(os.path.dirname(here), "install", "lib")
    if (os.path.exists(extra_lib_folder)):
        extra_libs = os.listdir(extra_lib_folder)
        for lib in extra_libs:
            if '.so' in lib and ('idl' not in lib):
                lib_file = os.path.join(extra_lib_folder, lib)
                CDLL(lib_file, mode=RTLD_GLOBAL)
    else:
        print("No lib include")


load_library()


from lava.magma.runtime.message_infrastructure. \
    MessageInfrastructurePywrapper import (  # noqa
        CppMultiProcessing,
        ProcessType,
        Actor,
        ActorStatus,
        ActorCmd,
        RecvPort,
        AbstractTransferPort,
        support_grpc_channel,
        support_fastdds_channel,
        support_cyclonedds_channel)

from lava.magma.runtime.message_infrastructure.MessageInfrastructurePywrapper \
    import ChannelType as ChannelBackend  # noqa: E402

from .ports import (  # noqa: E402
    SendPort,
    Channel,
    getTempSendPort,
    getTempRecvPort)

ChannelQueueSize = 1
SyncChannelBytes = 128
SupportGRPCChannel = support_grpc_channel()
SupportFastDDSChannel = support_fastdds_channel()
SupportCycloneDDSChannel = support_cyclonedds_channel()

if SupportGRPCChannel:
    from .ports import GetRPCChannel
if SupportFastDDSChannel or SupportCycloneDDSChannel:
    from .ports import GetDDSChannel
    from lava.magma.runtime.message_infrastructure. \
        MessageInfrastructurePywrapper import (
            DDSTransportType,
            DDSBackendType)