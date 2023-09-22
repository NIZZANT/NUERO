# Copyright (C) 2023 Intel Corporation
# SPDX-License-Identifier: BSD-3-Clause
# See: https://spdx.org/licenses/

# Creates a pkgutil-style namespace package that extends the namespace over
# multiple directory structures.
__path__ = __import__('pkgutil').extend_path(__path__, __name__)

######
# IMPORTS

# Import the most common classes and functions to the top level to enable
# >>> import lava
# as the only required import for the most common Lava programs.

# MOST COMMON PROCESSES
from lava.proc.conv.process import Conv
from lava.proc.dense.process import Dense, DelayDense, LearningDense
from lava.proc.io.dataloader import SpikeDataloader, StateDataloader
from lava.proc.io.source import RingBuffer as SourceRingBuffer
from lava.proc.io.sink import RingBuffer as SinkRingBuffer
from lava.proc.io.encoder import DeltaEncoder
from lava.proc.io.injector import Injector
from lava.proc.io.extractor import Extractor
from lava.proc.io.reset import Reset
from lava.proc.learning_rules.r_stdp_learning_rule import RewardModulatedSTDP
from lava.proc.learning_rules.stdp_learning_rule import STDPLoihi
from lava.proc.lif.process import LIF, LearningLIF, LIFRefractory
from lava.proc.monitor.process import Monitor
from lava.proc.receiver.process import Receiver
from lava.proc.rf.process import RF
from lava.proc.rf_iz.process import RF_IZ
from lava.proc.sdn.process import Sigma, Delta, SigmaDelta, ActivationMode
from lava.proc.sparse.process import Sparse, LearningSparse, DelaySparse

# RUN CONFIGURATIONS & CONDITIONS
from lava.magma.core.run_configs import Loihi2SimCfg, Loihi2HwCfg
from lava.magma.core.run_conditions import RunContinuous, RunSteps

# MAGMA
from lava.magma.core.process.process import LogConfig

# UTILS
from lava.utils import loihi
from lava.utils import plots
from lava.utils.serialization import save, load

__all__ = ['Conv', 'Dense', 'DelayDense', 'LearningDense', 'SpikeDataloader',
           'StateDataloader', 'SourceRingBuffer', 'SinkRingBuffer',
           'DeltaEncoder', 'Injector', 'Extractor', 'Reset',
           'RewardModulatedSTDP', 'STDPLoihi', 'LIF', 'LearningLIF',
           'LIFRefractory', 'Monitor', 'Receiver', 'RF', 'RF_IZ',
           'Sigma', 'Delta', 'SigmaDelta', 'ActivationMode', 'Sparse',
           'LearningSparse', 'DelaySparse', 'Loihi2HwCfg', 'Loihi2SimCfg',
           'RunContinuous', 'RunSteps', 'LogConfig', 'loihi', 'plots',
           'save', 'load']
