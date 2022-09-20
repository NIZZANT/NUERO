// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: BSD-3-Clause
// See: https://spdx.org/licenses/

#include <memory>

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "abstract_actor.h"
#include "channel_proxy.h"
#include "multiprocessing.h"
#include "port_proxy.h"
#include "utils.h"
#include "selector.h"

namespace message_infrastructure {

namespace py = pybind11;

PYBIND11_MODULE(MessageInfrastructurePywrapper, m) {
  py::class_<MultiProcessing> (m, "CppMultiProcessing")
    .def(py::init<>())
    .def("build_actor", &MultiProcessing::BuildActor)
    .def("check_actor", &MultiProcessing::CheckActor)
    .def("get_actors", &MultiProcessing::GetActors)
    .def("stop", &MultiProcessing::Stop);
  py::enum_<ProcessType> (m, "ProcessType")
    .value("ErrorProcess", ErrorProcess)
    .value("ChildProcess", ChildProcess)
    .value("ParentProcess", ParentProcess);
  py::class_<PosixActor> (m, "Actor")
    .def("wait", &PosixActor::Wait)
    .def("get_status", &PosixActor::GetStatus)
    .def("get_cmd", &PosixActor::GetCmd)
    .def("pause", [](PosixActor &actor){
        actor.Control(ActorCmd::CmdPause);
      })
    .def("start", [](PosixActor &actor){
        actor.Control(ActorCmd::CmdRun);
      })
    .def("stop", [](PosixActor &actor){
        actor.Control(ActorCmd::CmdStop);
      })
    .def("error", [](PosixActor &actor){
        actor.SetStatus(ActorStatus::StatusError);
      });
  py::enum_<ChannelType> (m, "ChannelType")
    .value("SHMEMCHANNEL", SHMEMCHANNEL)
    .value("RPCCHANNEL", RPCCHANNEL)
    .value("DDSCHANNEL", DDSCHANNEL);
  py::class_<PortProxy, std::shared_ptr<PortProxy>> (m, "AbstractTransferPort");
  py::class_<ChannelProxy, std::shared_ptr<ChannelProxy>> (m, "Channel")
    .def(py::init<ChannelType, size_t, size_t, std::string>())
    .def("get_send_port", &ChannelProxy::GetSendPort, py::return_value_policy::reference)
    .def("get_recv_port", &ChannelProxy::GetRecvPort, py::return_value_policy::reference);
  py::class_<SendPortProxy, PortProxy, std::shared_ptr<SendPortProxy>> (m, "SendPort")
    .def(py::init<>())
    .def("get_channel_type", &SendPortProxy::GetChannelType)
    .def("start", &SendPortProxy::Start)
    .def("probe", &SendPortProxy::Probe)
    .def("send", &SendPortProxy::Send)
    .def("join", &SendPortProxy::Join)
    .def("name", &SendPortProxy::Name)
    .def("size", &SendPortProxy::Size);
  py::class_<RecvPortProxy, PortProxy, std::shared_ptr<RecvPortProxy>> (m, "RecvPort")
    .def(py::init<>())
    .def("get_channel_type", &RecvPortProxy::GetChannelType)
    .def("start", &RecvPortProxy::Start)
    .def("probe", &RecvPortProxy::Probe)
    .def("recv", &RecvPortProxy::Recv)
    .def("peek", &RecvPortProxy::Peek)
    .def("join", &RecvPortProxy::Join)
    .def_property_readonly("name", &RecvPortProxy::Name)
    .def("size", &RecvPortProxy::Size);
}

}  // namespace message_infrastructure
