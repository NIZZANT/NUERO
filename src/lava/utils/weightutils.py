# Copyright (C) 2022 Intel Corporation
# SPDX-License-Identifier: BSD-3-Clause
# See: https://spdx.org/licenses/

import numpy as np
import typing as ty
from enum import Enum, unique


@unique
class SignMode(Enum):
    """Enumeration of sign mode of weights.
    """
    NULL = 0
    MIXED = 1
    EXCITATORY = 2
    INHIBITORY = 3


def optimize_weight_bits(weight: np.ndarray,
                         loihi2: bool = False) -> ty.Tuple[np.ndarray,
                                                           int,
                                                           int,
                                                           SignMode]:
    """Optimizes the weight matrix to best fit in Loihi's synapse.

    Parameters
    ----------
    weight : np.ndarray
        Standard 8 bit signed weight matrix.
    loihi2 : bool, optional
        Flag to optimize for Lohi 2. By default False.

    Returns
    -------
    np.ndarray
        optimized weight matrix
    int
        weight bits
    int
        weight_exponent
    SignMode
        synapse sign mode
    """
    weight = truncate_weights(weight, sign_mode=1, num_weight_bits=8)

    max_weight = np.max(weight)
    min_weight = np.min(weight)

    if max_weight < 0:
        sign_mode = SignMode.INHIBITORY
        is_signed = 0
    elif min_weight >= 0:
        sign_mode = SignMode.EXCITATORY
        is_signed = 0
    else:
        sign_mode = SignMode.MIXED
        is_signed = 1

    scale = 0

    if sign_mode == SignMode.MIXED:
        pos_scale = 127 / max_weight
        neg_scale = -128 / min_weight
        scale = np.min([pos_scale, neg_scale])
    elif sign_mode == SignMode.INHIBITORY:
        scale = -256 / min_weight
    elif sign_mode == SignMode.EXCITATORY:
        scale = 255 / max_weight

    scale_bits = int(np.floor(np.log2(scale)) + is_signed)

    precision_found = False
    n = 8
    while (precision_found is False) and (n > 0):
        roundingError = np.sum(
            np.abs(weight / (2**n) - np.round(weight / (2**n)))
        )
        if roundingError == 0:
            precision_found = True
        else:
            n -= 1

    n -= is_signed

    num_weight_bits = 8 - scale_bits - n
    weight_exponent = -scale_bits

    weight = np.left_shift(weight.astype(np.int32), int(scale_bits))

    if loihi2:
        weight = weight // (1 << (8 - num_weight_bits))
        if sign_mode == SignMode.MIXED:
            weight = weight // 2

    return (
        weight.astype(int),
        int(num_weight_bits),
        int(weight_exponent),
        sign_mode
    )


def truncate_weights(weights: np.ndarray,
                     sign_mode: int,
                     num_weight_bits: int) -> np.ndarray:
    """
    Truncate the given weight matrix based on the specified SignMode and
    number of bits.

    Parameters
    ----------
    weights : numpy.ndarray
        Weight matrix that is to be truncated.
    sign_mode : int
        Integer representing the sign mode. See SignMode class for the
        correct values.
    num_weight_bits : int
        Number of bits to use for the weight matrix.

    Returns
    -------
    numpy.ndarray
        Truncated weight matrix.

    """
    wgt_vals = np.copy(weights).astype(np.int32)

    # Saturate the weights according to the sign_mode:
    # 0 : null
    # 1 : mixed
    # 2 : excitatory
    # 3 : inhibitory
    mixed_flag = np.equal(sign_mode, 1).astype(np.int32)
    excitatory_flag = np.equal(sign_mode, 2).astype(np.int32)
    inhibitory_flag = np.equal(sign_mode, 3).astype(np.int32)

    min_wgt = -2 ** 8 * (mixed_flag + inhibitory_flag)
    max_wgt = (2 ** 8 - 1) * (mixed_flag + excitatory_flag)

    saturated_wgts = np.clip(wgt_vals, min_wgt, max_wgt)

    # Truncate least significant bits given sign_mode and num_wgt_bits.
    num_truncate_bits = 8 - num_weight_bits + mixed_flag

    truncated_wgts = np.left_shift(
        np.right_shift(saturated_wgts, num_truncate_bits),
        num_truncate_bits).astype(np.int32)

    return np.copy(truncated_wgts)
