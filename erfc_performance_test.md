一、Pytorch.erfc性能测试:
float类型数据:
[10240] torch.Size([10240])
[pytorch-digamma-py] time: 0.013816595077514648 ms
[102400] torch.Size([102400])
[pytorch-digamma-py] time: 0.01920771598815918 ms
[1024000] torch.Size([1024000])
[pytorch-digamma-py] time: 0.021748065948486328 ms
[10240] torch.Size([10240])
[pytorch-digamma-py] time: 0.012364625930786133 ms
half
[10240] torch.Size([10240])
[pytorch-digamma-py] time: 0.013695955276489258 ms
[102400] torch.Size([102400])
[pytorch-digamma-py] time: 0.017413854598999023 ms
[1024000] torch.Size([1024000])
[pytorch-digamma-py] time: 0.020115137100219727 ms
[10240] torch.Size([10240])
[pytorch-digamma-py] time: 0.012649774551391602 ms


二、Cambricon.erfc性能测试:
float类型数据:
[10240] cambricon.erfc.Size([10240])
[cambricon-erfc-wdhs] time: 0.035 ms
[102400] cambricon.erfc.Size([102400])
[cambricon-erfc-wdhs] time: 0.027 ms
[1024000] cambricon.erfc.Size([1024000])
[cambricon-erfc-wdhs] time: 0.052 ms

half类型数据
[10240] cambricon.erfc.Size([10240])
[cambricon-erfc-wdhs] time: 0.039 ms
[102400] cambricon.erfc.Size([102400])
[cambricon-erfc-wdhs] time: 0.042 ms
[1024000] cambricon.erfc.Size([1024000])
[cambricon-erfc-wdhs] time: 0.027 ms
[10240] cambricon.erfc.Size([10240])
[cambricon-erfc-wdhs] time: 0.013 ms


