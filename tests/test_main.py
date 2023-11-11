import json
from pathlib import Path

import pytest

from ph4gas.sensirion import (
    GasIndexAlgorithm,
    NoxGasIndexAlgorithm,
    VocGasIndexAlgorithm,
)

test_data = [
    ("data-01.json", "data-01.json"),
    ("data-02.json", "data-02.json"),
]


@pytest.mark.parametrize("data_file, test_case_name", test_data, ids=[name for _, name in test_data])
def test_function(data_file, test_case_name):
    data_file_path = Path(__file__).parent / "data" / data_file
    with open(data_file_path, "r") as fh:
        data = json.load(fh)

    nox_est = NoxGasIndexAlgorithm(1.0)
    voc_est = VocGasIndexAlgorithm(1.0)

    # initial blackout
    for i in range(int(GasIndexAlgorithm.INITIAL_BLACKOUT) + 1):
        nox_est.process(1000 + i)
        voc_est.process(1000 + i)

    # measurements
    print("\n")
    for i in range(len(data)):
        cdata = data[i]
        voc_gi = voc_est.process(cdata[1])
        assert voc_gi == cdata[3]

        nox_gi = nox_est.process(cdata[2])
        assert nox_gi == cdata[4]

        # Original test code:
        # voc_gi = voc_est.process(GasIndexAlgorithm.VOC_SRAW_MINIMUM + (i - 2) * 25)
        # nox_gi = nox_est.process(GasIndexAlgorithm.NOX_SRAW_MINIMUM + (i - 2) * 25)
        # print(i, voc_gi, nox_gi)
