此项目向Cambricon mlu-ops 仓库中集成进erfc算子，为一个算子开发项目

目前算子的性能: 支持float、half两种数据类型的任意范围的输入数据，当数据量小于10^6级时性能达到了基于Nvidia V100的 pytorch.erfc() 的 1/3