# Preprocess

Preprocess 是一个简单的图像格式转换工具，它支持很多的图像类型转换


## Python 接口使用
* 安装：cd到preprocess这一级，执行 __pip install.__，将preprocess安装到当前所在的python环境（测试环境为mac ventura，由于无法使用混合编译，暂时默认c++）


## 接口参数说明
* BGR转其他颜色时，BGR是HWC的存储顺序
* 444是YUV444的plane的存储顺序，I444是CHW的存储顺序，YUV444是HWC的存储顺序，转换方式是
```[python]
import numpy as np
I444 = np.transpose(YUV444,(2,0,1))
YUV444 = np.transpose(I444,(1,2,0))
```
* sample code
```[python]
import numpy as np
import preprocess
width = 640
height = 480
nv12_file = '***.NV12'
nv12_data = np.fromfile(nv12_file,np.uint8)
I444_nv12 = np.ndarray((3,height,width),dtype=np.uint8)
I444_nv12 = preprocess.NV122I444(nv12_data,I444_nv12,width,height)
```
* 支持转换列表