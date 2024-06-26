/*************************************************************************
 * Copyright (C) [2022] by Cambricon, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *************************************************************************/
#include "erfc.h"

#include "core/context.h"
#include "core/gen_case.h"
#include "core/logging.h"
#include "core/runtime/device.h"
#include "core/tensor.h"
#include "core/type.h"
#include "kernels/unary_op/unary_op_host.h"


// 1. 为 k_dim赋值，就是创建一个网格   2. 为 k_type 赋值
static void policyFunc(const mluOpHandle_t &handle,
                       const mluOpTensorDescriptor_t &desc, cnrtDim3_t *k_dim,
                       cnrtFunctionType_t *k_type) {
  size_t dim = mluOpGetTensorElementNum(desc);
  // Union1 policyFunc
  *k_type = CNRT_FUNC_TYPE_UNION1;
  k_dim->x = handle->core_num_per_cluster;
  k_dim->y = mluop::runtime::getClusterLimitCapability(handle);
  k_dim->z = 1;
  // if a case is smaller than 2048 , it just need one cluster can work best.
  size_t small_case_thread = 2048;
  if (dim <= small_case_thread) k_dim->y = 1;

}

// printf("result: %f\n",((float*)y)[0]);

mluOpStatus_t MLUOP_WIN_API mluOpErfc(mluOpHandle_t handle,
                                     const mluOpTensorDescriptor_t x_desc,
                                     const void *x,
                                     const mluOpTensorDescriptor_t y_desc,
                                     void *y) {
  mluOpDataType_t support_type[2] = {MLUOP_DTYPE_HALF, MLUOP_DTYPE_FLOAT};

  /**
  bool zero_element = false;
  mluOpStatus_t param_check =
      unaryOpParamCheck("[mluOpErfc]", handle, x_desc, x, y_desc, y,
                        support_type, 2, zero_element);
  if (zero_element == true) {
    return MLUOP_STATUS_SUCCESS;
  }
  if (param_check != MLUOP_STATUS_SUCCESS) {
    return param_check;
  }
  **/
  if (MLUOP_GEN_CASE_ON_NEW) {
    GEN_CASE_START("erfc");
    GEN_CASE_HANDLE(handle);
    GEN_CASE_DATA(true, "x", x, x_desc, 10, 0);
    GEN_CASE_DATA(false, "y", y, y_desc, 0, 0);
    GEN_CASE_TEST_PARAM_NEW(true, true, false, 0.003, 0.003, 0);    // 最后三个参数分别是 diff1 diff2 diff3 
  }

  // Choose the best task dimension.
  cnrtDim3_t k_dim;
  cnrtFunctionType_t k_type;
  // policyFunc(handle, x_desc, &k_dim, &k_type);
  unaryOpPolicyFunc(handle,x_desc,&k_dim,&k_type);
  
  const int element_num = mluOpGetTensorElementNum(x_desc);

  printf("dim.x:%d \n",k_dim.x);
  printf("dim.y:%d \n",k_dim.y);
  printf("dim.z:%d \n",k_dim.z);


  int len_kdimX = 4;
  k_dim.x = len_kdimX;
  if(element_num <= len_kdimX * WORKLOAD) k_dim.y = 2;
  else {
    int validNum = element_num % WORKLOAD == 0 ? element_num / WORKLOAD : element_num / WORKLOAD + 1;
    validNum = validNum % len_kdimX == 0 ? validNum / len_kdimX : validNum / len_kdimX + 1;
    k_dim.y = validNum;
  }
  k_dim.z = 1;
   

  VLOG(5) << "kernel Kernel3StagePipelineErfc.";
  CHECK_RETURN("[mluOpErfc] ",
               Kernel3StagePipelineErfc(k_dim, k_type, handle->queue,
                                       x_desc->dtype, x, y, element_num));
  // for(int i = 0; i < element_num; i++) printf("result: %f\n",(float*)x[i]);


  GEN_CASE_END();
  return MLUOP_STATUS_SUCCESS;
}





