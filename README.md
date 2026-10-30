# QNX-Oriented CAN Bus Intrusion Detection System

**Status:** Offline ML model and portable C classifier available; live CAN
acquisition, QNX integration, and real-time performance validation are
future integration tasks.

A prototype automotive CAN-bus intrusion-detection project that classifies
CAN frames as **Normal (0)** or **Attack (1)** using a Decision Tree model.
The intended target is a Raspberry Pi 4 platform running QNX, with an
MCP2515 CAN controller interface. This repository currently contains the
generated C classifier and offline evaluation artifacts.

## Current results

| Item | Reported result |
|---|---:|
| Parsed CAN frames | 7,504,631 |
| Samples used for ML | 100,000 |
| Normal / attack samples | 85,617 / 14,383 |
| Decision Tree accuracy | 99.69% |
| Decision Tree ROC-AUC | 0.9952 |
| Decision Tree depth / leaves | 8 / 20 |
| KNN accuracy (comparison) | 99.67% |

These are offline dataset evaluation results, not measurements from a
running QNX target. The repository does **not** currently demonstrate a
guaranteed detection deadline or a sub-2 ms worst-case execution time.

## Architecture goal

```text
CAN network / attack traffic
          |
      MCP2515
          | SPI
    Raspberry Pi 4
     (QNX target)
          |
   Feature extraction
          |
   Decision Tree in C
          |
   Normal / Attack result
          |
   Alerting and event logging
```

The architecture above is the planned integration. Hardware acquisition,
the QNX driver/interface, alert GPIO/LCD/buzzer code, and end-to-end
latency measurement are not included as completed functionality here.

## Repository structure

```text
can-bus-ids-github/
├── src/
│   └── dt_classifier.c
├── tests/
│   └── test_classifier.c
├── docs/
│   └── feature_names.txt
├── results/
│   ├── model_results.txt
│   ├── confusion_matrices.png
│   └── feature_importance.png
├── models/
│   └── README.md
├── Makefile
├── .gitignore
└── README.md
```

## Classifier interface

`src/dt_classifier.c` defines:

```c
typedef struct {
    uint32_t can_id;
    uint8_t  dlc;
    uint8_t  data[8];
    float    inter_arrival;
} CANFrame;

int classify_can_frame(const CANFrame *frame);
```

Return values:

- `0` — Normal
- `1` — Attack

The classifier is ordinary C and does not itself call QNX APIs. It can be
compiled and unit-tested on a desktop before being integrated into a QNX
application.

**Important:** `inter_arrival` must be supplied in exactly the same unit
and scale used when training the Python model. The feature extraction
pipeline must also preserve the training-time interpretation and ordering
of CAN ID, DLC, payload bytes, and inter-arrival time. Confirm this before
relying on live classifications.

## Build and run the smoke tests

Requirements: GCC or another C11-compatible compiler, and `make`.

```bash
make test
```

To remove generated test binaries:

```bash
make clean
```

These are interface/branch smoke tests. They do not replace validation
against a labelled test dataset or live CAN traffic.

## Evaluation artifacts

- `results/confusion_matrices.png` — Decision Tree and KNN confusion
  matrices from the offline evaluation.
- `results/feature_importance.png` — Decision Tree feature-importance plot.
- `results/model_results.txt` — reported dataset and model metrics.
- `docs/feature_names.txt` — feature list used in the model workflow.

## Dataset and reproducibility

The project notes identify the DoS and Fuzzy CAN intrusion datasets from
the Car-Hacking dataset collection. The raw CSV datasets are not included.
Obtain them from the original provider and follow its terms of use before
redistributing data.

For a fully reproducible ML pipeline, add the training script, exact
dataset source/version, preprocessing steps, train/test split strategy,
random seed, dependency versions, and the command used to export the C
classifier. Do not claim reproducibility from the exported C file alone.

## Limitations and next engineering steps

1. Validate the C classifier against the same held-out samples used for
   Python evaluation; compare predictions sample-by-sample.
2. Verify CAN ID parsing (hexadecimal to integer), DLC handling, payload
   padding, timestamp units, and inter-arrival calculation.
3. Integrate a real MCP2515 receive path and test with normal and attack
   traffic on an isolated bench CAN network.
4. Port the application to the actual QNX BSP and verify supported SPI,
   GPIO, scheduling, and timing APIs for that BSP.
5. Measure classifier execution time and end-to-end detection latency on
   the target. Report observed average, percentile, and worst-case values
   under stated test conditions; do not call them guaranteed bounds
   without a proper real-time analysis.
6. Evaluate per-class precision, recall, F1-score, false-positive rate,
   false-negative rate, and performance on traffic not used during
   training.

## Safety note

This is an academic/research prototype. It is not a production automotive
safety or security control and must not be connected to or used to control
a road vehicle.
