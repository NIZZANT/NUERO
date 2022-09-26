# Copyright (C) 2022 Intel Corporation
# SPDX-License-Identifier: BSD-3-Clause
# See: https://spdx.org/licenses/
import typing as ty

from lava.magma.core.process.ports.ports import InPort
from lava.magma.core.process.process import AbstractProcess, LogConfig
from lava.magma.core.process.variable import Var


class Receiver(AbstractProcess):
    """Process saving input messages as a payload variable.

    Parameters
    ----------
    shape: Shape of the population of process units.
    name: Name of the Process. Default is 'Process_ID', where ID is an
    integer value that is determined automatically.
    log_config: Configuration options for logging.
    """

    def __init__(self, *,
                 shape: ty.Tuple[int, ...] = (1,),
                 name: ty.Optional[str] = None,
                 log_config: ty.Optional[LogConfig] = None) -> None:
        super().__init__(shape=shape, name=name, log_config=log_config)
        self.a_in = InPort(shape=shape)
        self.payload = Var(shape=shape, init=0)
