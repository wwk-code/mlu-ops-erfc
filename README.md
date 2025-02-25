  本项目的内容为向 寒武纪软件体系栈中的Cambricon mlu-ops仓库中集成erfc算子，erfc文件夹下的内容为erfc算子的全部开发代码，由此也可轻松开发出erf算子。
  
  由于受中科寒武纪有限责任公司的保密协议所限，其它项目依赖环境文件、算子开发环境依赖文件、算子性能测试等文件均无法上传，本仓库的的全部内容仅仅为erfc算子功能性开发代码。目前算子的性能: 支持half、float、int16/32、long long等数据类型的任意范围、大数据量（0-10^15数量级）的输入数据，目前功能性已验证通过; Cambricon erfc算子的推理性能达到了基于Nvidia V100的 pytorch.erfc() 的3/4以上 ,具体性能对比记录可查看 erfc_performance_test.md文件

  


  
