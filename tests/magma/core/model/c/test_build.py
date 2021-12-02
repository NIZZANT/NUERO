# Copyright (C) 2021 Intel Corporation
# SPDX-License-Identifier: BSD-3-Clause
# See: https://spdx.org/licenses/
import unittest

from lava.magma.core.model.c.model import AbstractCProcessModel
from lava.proc.dense.models import PyDenseModel

import os
import numpy as np


class MockServicePort:
    phase: int = 10

    def probe(self) -> int:
        return 1

    def recv(self) -> int:
        self.phase = (self.phase - 1) % 10
        return self.phase


class MockDataPort:
    sent: int = 0
    recd: int = 0

    def peek(self):
        print("peek")
        return 1

    def probe(self):
        print("probe")
        return 1

    def recv(self):
        print("recv")
        self.recd += 1
        return np.ones(1, dtype=np.int64)

    def send(self, data):
        print("send")
        self.sent += 1
        pass

    def flush(self):
        print("flush")
        pass


class Test_Build(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        os.chdir(os.path.dirname(os.path.abspath(__file__)))
        return super().setUpClass()

    def test_run(self):
        class PM(AbstractCProcessModel):
            service_to_process_cmd: MockServicePort = MockServicePort()
            source_files = ["test_run.c"]

        pm = PM()
        pm.run()
        self.assertEqual(pm.service_to_process_cmd.phase, 0)

    def test_io(self):
        class PM(AbstractCProcessModel):
            service_to_process_cmd: MockServicePort = MockServicePort()
            in_port = MockDataPort()
            out_port = MockDataPort()
            source_files = ["test_io.c"]

        pm = PM()
        pm.run()
        self.assertEqual(pm.in_port.recd, 1)
        self.assertEqual(pm.out_port.sent, 1)

    def test_loihi(self):
        """
        compile a loihi protocol CProcessModel
        expect it to fail because of the mock service port
        """

        class PM(AbstractCProcessModel, PyDenseModel):
            service_to_process_cmd: MockServicePort = MockServicePort()
            source_files = ["test_loihi.c"]

        pm = PM()
        self.assertRaises(ValueError, pm.run)


if __name__ == "__main__":
    unittest.main()
