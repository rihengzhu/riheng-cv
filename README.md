#Deeo Learning Trainging Tools



##Introduction
This is a personal project mainly  for object detection.





## Prerequisites

In this section we demonstrate how to prepare an environment with PyTorch.

This project is tested on Linux and macOS. It's test on  Python 3.7+, CUDA 11.1+ and PyTorch 1.7+.





**Step 0.** Create a conda environment and activate it.

```shell
    conda create --name py39 python=3.9 -y
    conda activate py39
```
**Step 1.** Install PyTorch following [official instructions](https://pytorch.org/get-started/locally/), e.g.

For GPU version:
```python
    conda install pytorch torchvision -c pytorch
```
For CPU version:
```python
    conda install pytorch torchvision cpuonly -c pytorch
```
**Step 2.** Install preprocess or ti QAT, if you need yuv format for training and using tda plateform.

```shell
    cd ti_qat
    pip install .
    cd ../preprocess
    pip install .
```
**Step 3.** Install mmcv
For Mac Arm, till now there is no 

```shell
    git clone https://github.com/open-mmlab/mmcv.git
    cd mmcv
    pip install -r requires/optional.txt
    MMCV_WITH_OPS=1 pip install -e .

```
After install, you need verify
```shell
    python .dev_scripts.check_installation.py
```
For Linux, you can build from source(the command is same with mac plateform) or direct install compiled version, you can find appropriate version in [this link](https://mmcv.readthedocs.io/en/latest/get_started/installation.html).
```shell
    pip install mmcv-full==version -f https://download.openmmlab.com/mmcv/dist/cuda_version/torch_versino/index.html
```