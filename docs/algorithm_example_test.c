/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "sensirion_gas_index_algorithm.h"
#include <stdio.h>  // printf

int main(void) {
    uint16_t sraw_voc = 0;
    uint16_t sraw_nox = 0;
    int32_t voc_index_value = 0;
    int32_t nox_index_value = 0;

    // initialize gas index parameters
    GasIndexAlgorithmParams voc_params;
    GasIndexAlgorithm_init(&voc_params, GasIndexAlgorithm_ALGORITHM_TYPE_VOC);
    GasIndexAlgorithmParams nox_params;
    GasIndexAlgorithm_init(&nox_params, GasIndexAlgorithm_ALGORITHM_TYPE_NOX);

    // Initial blackout
    for (int i = 0; i <= (int)GasIndexAlgorithm_INITIAL_BLACKOUT; i += 1) {
        GasIndexAlgorithm_process(&voc_params, 1000 + i, &voc_index_value);
        GasIndexAlgorithm_process(&nox_params, 1000 + i, &nox_index_value);
    }

    printf("\n");
    for (int i = 0; i < 500; i += 1) {
        sraw_voc = GasIndexAlgorithm_VOC_SRAW_MINIMUM + (i - 2) * 25;
        sraw_nox = GasIndexAlgorithm_NOX_SRAW_MINIMUM + (i - 2) * 25;

        GasIndexAlgorithm_process(&voc_params, sraw_voc, &voc_index_value);
        GasIndexAlgorithm_process(&nox_params, sraw_nox, &nox_index_value);
        printf("[%i, %i, %i, %i, %i], \n", i, sraw_voc, sraw_nox, voc_index_value, nox_index_value);
    }
    printf("\n");

    return 0;
}
