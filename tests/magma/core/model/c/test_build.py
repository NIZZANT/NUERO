# Copyright (C) 2021 Intel Corporation
# SPDX-License-Identifier: BSD-3-Clause
# See: https://spdx.org/licenses/
import unittest

from lava.magma.core.model.c.model import CProcessModelMeta

import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))


class MockServicePort:
    phase: int = 0

    def probe(self) -> int:
        return 1

    def recv(self) -> int:
        self.phase += 1
        return self.phase


class MockDataPort:
    sent: int = 0
    recd: int = 0

    def peek(self):
        return 1

    def probe(self):
        return 1

    def recv(self):
        self.recd += 1
        return np.ones(1)

    def send(self, data):
        self.sent += 1
        pass


class Test_Build(unittest.TestCase):
    """
    def test_boring(self):
        class PM(AbstractCProcessModel):
            source_files = ["test_boring.c"]

        pm = PM()
        pm.run()
    """

    def test_runstate(self):
        class PM(metaclass=CProcessModelMeta):
            service_to_process_cmd: MockServicePort = MockServicePort()
            source_files = ["test_runstate.c"]

        pm = PM()
        pm.run()
        self.assertEqual(pm.service_to_process_cmd.phase, 10)


if __name__ == "__main__":
    unittest.main()
