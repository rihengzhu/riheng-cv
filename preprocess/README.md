# Preprocess

This is a data


## Python 接口使用
111


## 接口参数说明

BGR转其他颜色时，BGR是HWC的存储顺序
I444是YUV444的plane的存储顺序，I444是CHW的存储顺序，YUV444是HWC的存储顺序，转换方式是
```[python]
import numpy as np
I444 = np.transpose(YUV444,(2,0,1))
YUV444
```