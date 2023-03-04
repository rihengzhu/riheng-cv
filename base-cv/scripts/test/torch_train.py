import argparse
import copy
import os
import  time
import sys
sys.path.append('../../')
import mmcv
import torch

from mmcv import Config, DictAction
from mmcv.runner import get_dist_info, init_dist

from mmdet import __version__
from mmdet.apis import set_random_seed
from mmdet.datasets import build_dataset
from mmdet.models import build_detector
from mmdet.utils import collect_env, get_root_logger

from train_cv.model import *