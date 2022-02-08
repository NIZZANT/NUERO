# Copyright (C) 2021 Intel Corporation
# SPDX-License-Identifier: BSD-3-Clause
# See: https://spdx.org/licenses/

from abc import ABC, abstractmethod

import typing as ty

from lava.magma.compiler.channels.interfaces import AbstractCspPort
from lava.magma.core.model.model import AbstractProcessModel


class AbstractProcessBuilder(ABC):
    """An AbstractProcessBuilder is the base type for process builders.

    Process builders instantiate and initialize a ProcessModel.
    """
    def __init__(
            self,
            proc_model: ty.Type[AbstractProcessModel],
            model_id: int):
        self._proc_model = proc_model
        self._model_id = model_id

    @abstractmethod
    def set_csp_ports(self, csp_ports: ty.List[AbstractCspPort]):
        pass

    @property
    @abstractmethod
    def proc_model(self) -> "AbstractProcessModel":
        pass


class AbstractRuntimeServiceBuilder(ABC):
    """An AbstractRuntimeServiceBuilder is the base type for
    RuntimeService builders.

    RuntimeService builders instantiate and initialize a RuntimeService.
    """
    def __init__(self, rs_class, sync_protocol):
        self.rs_class = rs_class
        self.sync_protocol = sync_protocol

    @property
    @abstractmethod
    def runtime_service_id(self):
        pass

    def build(self):
        raise NotImplementedError(
            "build function for RuntimeServiceBuilder is not implemented"
        )


class AbstractChannelBuilder(ABC):
    """An AbstractChannelBuilder is the base type for
    channel builders which build communication channels
    between services and processes"""

    pass
