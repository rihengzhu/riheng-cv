# TDA Quantization Tool
This is an [TI official code of quantization](https://github.com/TexasInstruments/edgeai-torchvision).

## 量化设置
* __需要进行量化的节点__：relu, relu6, hardtanh, Add，Concat，Mul，MaxPool2d，AvgPool2d(说白了就是需要计算量化Scale发生变化的节点)
* __不进行量化的节点__：Dropout2d 
  

##QAT流程
1. 根据上面的链接，安装XNN(老版xnn直接在主分支里面，新版在edgeai-torchvision/torchvision/edgeailite里面)无论edgeai如何变化，XNN基本不会发生变化，只需要将其剥离出来即可。
2. 搭建自己的模型，加载模型权重
3. 模型利用QAT API封装（xnn.quantize.QuantTrainModule）
4. 模型QAT训练
5. 模型利用QAT API封装(xnn.quantize.QuantTestModule)，模型导出
6. 模拟器导出时设置`quantizationStype=3`，`calibrationOption=64`

##QAT参数

1. 111
   
##QAT模型训练流程
```[python]
```

##注意事项
* 相同的模块不要复用
* 尽量使用torch.nn所支持的节点，而不是torch.nn.functional的
* 对于加，减，乘，除以及concat，要使用`xnn.layers`内节点代替正常的操作(还是上面的话，<font color="#dd0000">只要涉及两个输入端都需要计算系数，都需要量化)</font><br />
* 不建议同时使用constrain bias和per_channel_q
* per_channel_q(per channel quantization)会使weight scale飞快增加，导致bias饱和如果constrain_bias设置为True。过多的bias饱和会使得精度下降。如果要同时使用建议将constrain_bias设置为CONSTRAIN_BIAS_TYPE_REDUCE_WEIGHT_SCALE
  
##个人碎碎念
这里单独提一嘴，由于TI的DL加速属于专用的加速硬件，相对于普通的cpu来说，__depthwise__ 所带来的收益远小于非专用加速硬件，而且TI的量化相对其他硬件厂商做的非常差，所以尽量不要讲channel完全开放，尤其是对那些输出值相对重要的任务。