  本项目向Cambricon mlu-ops 仓库中集成erfc算子，erfc文件夹下的内容为erfc算子的全部开发代码
  由于受中科寒武纪有限公司的保密协议所限，其它项目依赖文件、算子开发环境依赖、算子性能测试等文件均无法上传，本仓库的的全部内容仅仅为erfc算子开发代码。目前算子的性能: 支持float、half、int16/32 long long等数据类型的任意范围（0-10^8数量级）的输入数据，目前Cambricon erfc算子的推理性能达到了基于Nvidia V100的 pytorch.erfc() 的 1/3 ,功能性已验证通过
