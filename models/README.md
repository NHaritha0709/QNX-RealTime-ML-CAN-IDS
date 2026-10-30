# Model artifacts

The selected deployment artifact is `../src/dt_classifier.c`, a C
implementation generated from the trained Decision Tree.

Python pickle files (`.pkl`) are intentionally not included in this
repository: they are not required by the C classifier at runtime, and
loading pickle files from untrusted sources can execute code. If you later
add a reproducible Python training pipeline, document the exact Python and
scikit-learn versions and provide a trusted model-generation workflow.
