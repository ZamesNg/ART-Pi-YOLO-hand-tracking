/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Sep 29 15:46:19 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"



#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 2
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "ff2d8adfb0082a2a73fe7dc702c23b4f"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.2.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Sep 29 15:46:19 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_8_bias_array;   /* Array #0 */
AI_STATIC ai_array conv2d_8_weights_array;   /* Array #1 */
AI_STATIC ai_array conv2d_7_bias_array;   /* Array #2 */
AI_STATIC ai_array conv2d_7_weights_array;   /* Array #3 */
AI_STATIC ai_array conv2d_6_bias_array;   /* Array #4 */
AI_STATIC ai_array conv2d_6_weights_array;   /* Array #5 */
AI_STATIC ai_array depthwise_conv2d_2_bias_array;   /* Array #6 */
AI_STATIC ai_array depthwise_conv2d_2_weights_array;   /* Array #7 */
AI_STATIC ai_array conv2d_5_bias_array;   /* Array #8 */
AI_STATIC ai_array conv2d_5_weights_array;   /* Array #9 */
AI_STATIC ai_array conv2d_4_bias_array;   /* Array #10 */
AI_STATIC ai_array conv2d_4_weights_array;   /* Array #11 */
AI_STATIC ai_array depthwise_conv2d_1_bias_array;   /* Array #12 */
AI_STATIC ai_array depthwise_conv2d_1_weights_array;   /* Array #13 */
AI_STATIC ai_array conv2d_3_bias_array;   /* Array #14 */
AI_STATIC ai_array conv2d_3_weights_array;   /* Array #15 */
AI_STATIC ai_array conv2d_2_bias_array;   /* Array #16 */
AI_STATIC ai_array conv2d_2_weights_array;   /* Array #17 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #18 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #19 */
AI_STATIC ai_array depthwise_conv2d_bias_array;   /* Array #20 */
AI_STATIC ai_array depthwise_conv2d_weights_array;   /* Array #21 */
AI_STATIC ai_array conv2d_bias_array;   /* Array #22 */
AI_STATIC ai_array conv2d_weights_array;   /* Array #23 */
AI_STATIC ai_array image_input_output_array;   /* Array #24 */
AI_STATIC ai_array conv2d_output_array;   /* Array #25 */
AI_STATIC ai_array depthwise_conv2d_output_array;   /* Array #26 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #27 */
AI_STATIC ai_array conv2d_2_output_array;   /* Array #28 */
AI_STATIC ai_array conv2d_3_output_array;   /* Array #29 */
AI_STATIC ai_array depthwise_conv2d_1_output_array;   /* Array #30 */
AI_STATIC ai_array conv2d_4_output_array;   /* Array #31 */
AI_STATIC ai_array conv2d_5_output_array;   /* Array #32 */
AI_STATIC ai_array depthwise_conv2d_2_output_array;   /* Array #33 */
AI_STATIC ai_array conv2d_6_output_array;   /* Array #34 */
AI_STATIC ai_array conv2d_7_output_array;   /* Array #35 */
AI_STATIC ai_array conv2d_8_output_array;   /* Array #36 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_8_bias;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_8_weights;   /* Tensor #1 */
AI_STATIC ai_tensor conv2d_7_bias;   /* Tensor #2 */
AI_STATIC ai_tensor conv2d_7_weights;   /* Tensor #3 */
AI_STATIC ai_tensor conv2d_6_bias;   /* Tensor #4 */
AI_STATIC ai_tensor conv2d_6_weights;   /* Tensor #5 */
AI_STATIC ai_tensor depthwise_conv2d_2_bias;   /* Tensor #6 */
AI_STATIC ai_tensor depthwise_conv2d_2_weights;   /* Tensor #7 */
AI_STATIC ai_tensor conv2d_5_bias;   /* Tensor #8 */
AI_STATIC ai_tensor conv2d_5_weights;   /* Tensor #9 */
AI_STATIC ai_tensor conv2d_4_bias;   /* Tensor #10 */
AI_STATIC ai_tensor conv2d_4_weights;   /* Tensor #11 */
AI_STATIC ai_tensor depthwise_conv2d_1_bias;   /* Tensor #12 */
AI_STATIC ai_tensor depthwise_conv2d_1_weights;   /* Tensor #13 */
AI_STATIC ai_tensor conv2d_3_bias;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_3_weights;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_2_bias;   /* Tensor #16 */
AI_STATIC ai_tensor conv2d_2_weights;   /* Tensor #17 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #18 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #19 */
AI_STATIC ai_tensor depthwise_conv2d_bias;   /* Tensor #20 */
AI_STATIC ai_tensor depthwise_conv2d_weights;   /* Tensor #21 */
AI_STATIC ai_tensor conv2d_bias;   /* Tensor #22 */
AI_STATIC ai_tensor conv2d_weights;   /* Tensor #23 */
AI_STATIC ai_tensor image_input_output;   /* Tensor #24 */
AI_STATIC ai_tensor conv2d_output;   /* Tensor #25 */
AI_STATIC ai_tensor depthwise_conv2d_output;   /* Tensor #26 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #27 */
AI_STATIC ai_tensor conv2d_2_output;   /* Tensor #28 */
AI_STATIC ai_tensor conv2d_3_output;   /* Tensor #29 */
AI_STATIC ai_tensor depthwise_conv2d_1_output;   /* Tensor #30 */
AI_STATIC ai_tensor conv2d_4_output;   /* Tensor #31 */
AI_STATIC ai_tensor conv2d_5_output;   /* Tensor #32 */
AI_STATIC ai_tensor depthwise_conv2d_2_output;   /* Tensor #33 */
AI_STATIC ai_tensor conv2d_6_output;   /* Tensor #34 */
AI_STATIC ai_tensor conv2d_7_output;   /* Tensor #35 */
AI_STATIC ai_tensor conv2d_8_output;   /* Tensor #36 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain depthwise_conv2d_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain conv2d_2_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain conv2d_3_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain depthwise_conv2d_1_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain conv2d_4_chain;   /* Chain #6 */
AI_STATIC_CONST ai_tensor_chain conv2d_5_chain;   /* Chain #7 */
AI_STATIC_CONST ai_tensor_chain depthwise_conv2d_2_chain;   /* Chain #8 */
AI_STATIC_CONST ai_tensor_chain conv2d_6_chain;   /* Chain #9 */
AI_STATIC_CONST ai_tensor_chain conv2d_7_chain;   /* Chain #10 */
AI_STATIC_CONST ai_tensor_chain conv2d_8_chain;   /* Chain #11 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d conv2d_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d depthwise_conv2d_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d conv2d_1_layer; /* Layer #2 */
AI_STATIC ai_layer_conv2d conv2d_2_layer; /* Layer #3 */
AI_STATIC ai_layer_conv2d conv2d_3_layer; /* Layer #4 */
AI_STATIC ai_layer_conv2d depthwise_conv2d_1_layer; /* Layer #5 */
AI_STATIC ai_layer_conv2d conv2d_4_layer; /* Layer #6 */
AI_STATIC ai_layer_conv2d conv2d_5_layer; /* Layer #7 */
AI_STATIC ai_layer_conv2d depthwise_conv2d_2_layer; /* Layer #8 */
AI_STATIC ai_layer_conv2d conv2d_6_layer; /* Layer #9 */
AI_STATIC ai_layer_conv2d conv2d_7_layer; /* Layer #10 */
AI_STATIC ai_layer_conv2d conv2d_8_layer; /* Layer #11 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_8_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 30, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_8_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3840, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3072, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 24, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1536, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1024, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 768, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 48, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 432, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 48, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 384, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 72, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 72, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  image_input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 25600, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 19200, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4800, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1600, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_5_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  depthwise_conv2d_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1600, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 600, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_8_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 750, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_8_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 30, 1, 1), AI_STRIDE_INIT(4, 4, 4, 120, 120),
  1, &conv2d_8_bias_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_8_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 30), AI_STRIDE_INIT(4, 4, 512, 512, 512),
  1, &conv2d_8_weights_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &conv2d_7_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 24, 1, 1, 128), AI_STRIDE_INIT(4, 4, 96, 96, 96),
  1, &conv2d_7_weights_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 1, 1), AI_STRIDE_INIT(4, 4, 4, 96, 96),
  1, &conv2d_6_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 24), AI_STRIDE_INIT(4, 4, 256, 256, 256),
  1, &conv2d_6_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_2_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &depthwise_conv2d_2_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_2_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &depthwise_conv2d_2_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_5_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 16, 1, 1, 64), AI_STRIDE_INIT(4, 4, 64, 64, 64),
  1, &conv2d_5_weights_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_4_bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 48, 1, 1, 16), AI_STRIDE_INIT(4, 4, 192, 192, 192),
  1, &conv2d_4_weights_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 48, 1, 1), AI_STRIDE_INIT(4, 4, 4, 192, 192),
  1, &depthwise_conv2d_1_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 48), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &depthwise_conv2d_1_weights_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 48, 1, 1), AI_STRIDE_INIT(4, 4, 4, 192, 192),
  1, &conv2d_3_bias_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 48), AI_STRIDE_INIT(4, 4, 32, 32, 32),
  1, &conv2d_3_weights_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_2_bias_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 4, 3, 3, 8), AI_STRIDE_INIT(4, 4, 16, 48, 144),
  1, &conv2d_2_weights_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 8, 1, 1, 4), AI_STRIDE_INIT(4, 4, 32, 32, 32),
  1, &conv2d_1_weights_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &depthwise_conv2d_bias_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 8), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &depthwise_conv2d_weights_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &conv2d_bias_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 8), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &conv2d_weights_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  image_input_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 160, 160), AI_STRIDE_INIT(4, 4, 4, 4, 640),
  1, &image_input_output_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 80, 80), AI_STRIDE_INIT(4, 4, 4, 32, 2560),
  1, &conv2d_output_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 40, 40), AI_STRIDE_INIT(4, 4, 4, 32, 1280),
  1, &depthwise_conv2d_output_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 40, 40), AI_STRIDE_INIT(4, 4, 4, 16, 640),
  1, &conv2d_1_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 20, 20), AI_STRIDE_INIT(4, 4, 4, 32, 640),
  1, &conv2d_2_output_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 48, 20, 20), AI_STRIDE_INIT(4, 4, 4, 192, 3840),
  1, &conv2d_3_output_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 48, 10, 10), AI_STRIDE_INIT(4, 4, 4, 192, 1920),
  1, &depthwise_conv2d_1_output_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 10, 10), AI_STRIDE_INIT(4, 4, 4, 64, 640),
  1, &conv2d_4_output_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_5_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &conv2d_5_output_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  depthwise_conv2d_2_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 5), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &depthwise_conv2d_2_output_array, NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 24, 5, 5), AI_STRIDE_INIT(4, 4, 4, 96, 480),
  1, &conv2d_6_output_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 5, 5), AI_STRIDE_INIT(4, 4, 4, 512, 2560),
  1, &conv2d_7_output_array, NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_8_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 30, 5, 5), AI_STRIDE_INIT(4, 4, 4, 120, 600),
  1, &conv2d_8_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &image_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_weights, &conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_layer, 2,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &depthwise_conv2d_layer, AI_STATIC,
  .tensors = &conv2d_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  depthwise_conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &depthwise_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &depthwise_conv2d_weights, &depthwise_conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  depthwise_conv2d_layer, 6,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_1_layer, AI_STATIC,
  .tensors = &depthwise_conv2d_chain, 
  .groups = 8, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &depthwise_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 9,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_2_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_2_weights, &conv2d_2_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_layer, 12,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_3_layer, AI_STATIC,
  .tensors = &conv2d_2_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 15,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &depthwise_conv2d_1_layer, AI_STATIC,
  .tensors = &conv2d_3_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  depthwise_conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &depthwise_conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &depthwise_conv2d_1_weights, &depthwise_conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  depthwise_conv2d_1_layer, 19,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_4_layer, AI_STATIC,
  .tensors = &depthwise_conv2d_1_chain, 
  .groups = 48, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &depthwise_conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_4_weights, &conv2d_4_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_4_layer, 22,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_5_layer, AI_STATIC,
  .tensors = &conv2d_4_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_5_weights, &conv2d_5_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_5_layer, 25,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &depthwise_conv2d_2_layer, AI_STATIC,
  .tensors = &conv2d_5_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  depthwise_conv2d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &depthwise_conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &depthwise_conv2d_2_weights, &depthwise_conv2d_2_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  depthwise_conv2d_2_layer, 29,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_6_layer, AI_STATIC,
  .tensors = &depthwise_conv2d_2_chain, 
  .groups = 64, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &depthwise_conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_6_weights, &conv2d_6_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_6_layer, 32,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_7_layer, AI_STATIC,
  .tensors = &conv2d_6_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_7_weights, &conv2d_7_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_7_layer, 34,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_8_layer, AI_STATIC,
  .tensors = &conv2d_7_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_8_weights, &conv2d_8_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_8_layer, 36,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_8_layer, AI_STATIC,
  .tensors = &conv2d_8_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 50184, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 206112, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &image_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &conv2d_8_output),
  &conv2d_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, AI_NETWORK_ACTIVATIONS_ALIGNMENT));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    image_input_output_array.data = AI_PTR(NULL);
    image_input_output_array.data_start = AI_PTR(NULL);
    conv2d_output_array.data = AI_PTR(activations + 1312);
    conv2d_output_array.data_start = AI_PTR(activations + 1312);
    depthwise_conv2d_output_array.data = AI_PTR(activations + 0);
    depthwise_conv2d_output_array.data_start = AI_PTR(activations + 0);
    conv2d_1_output_array.data = AI_PTR(activations + 51200);
    conv2d_1_output_array.data_start = AI_PTR(activations + 51200);
    conv2d_2_output_array.data = AI_PTR(activations + 0);
    conv2d_2_output_array.data_start = AI_PTR(activations + 0);
    conv2d_3_output_array.data = AI_PTR(activations + 12800);
    conv2d_3_output_array.data_start = AI_PTR(activations + 12800);
    depthwise_conv2d_1_output_array.data = AI_PTR(activations + 89600);
    depthwise_conv2d_1_output_array.data_start = AI_PTR(activations + 89600);
    conv2d_4_output_array.data = AI_PTR(activations + 0);
    conv2d_4_output_array.data_start = AI_PTR(activations + 0);
    conv2d_5_output_array.data = AI_PTR(activations + 6400);
    conv2d_5_output_array.data_start = AI_PTR(activations + 6400);
    depthwise_conv2d_2_output_array.data = AI_PTR(activations + 0);
    depthwise_conv2d_2_output_array.data_start = AI_PTR(activations + 0);
    conv2d_6_output_array.data = AI_PTR(activations + 6400);
    conv2d_6_output_array.data_start = AI_PTR(activations + 6400);
    conv2d_7_output_array.data = AI_PTR(activations + 8800);
    conv2d_7_output_array.data_start = AI_PTR(activations + 8800);
    conv2d_8_output_array.data = AI_PTR(NULL);
    conv2d_8_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    conv2d_8_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_8_bias_array.data = AI_PTR(weights + 50064);
    conv2d_8_bias_array.data_start = AI_PTR(weights + 50064);
    conv2d_8_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_8_weights_array.data = AI_PTR(weights + 34704);
    conv2d_8_weights_array.data_start = AI_PTR(weights + 34704);
    conv2d_7_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_7_bias_array.data = AI_PTR(weights + 34192);
    conv2d_7_bias_array.data_start = AI_PTR(weights + 34192);
    conv2d_7_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_7_weights_array.data = AI_PTR(weights + 21904);
    conv2d_7_weights_array.data_start = AI_PTR(weights + 21904);
    conv2d_6_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_6_bias_array.data = AI_PTR(weights + 21808);
    conv2d_6_bias_array.data_start = AI_PTR(weights + 21808);
    conv2d_6_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_6_weights_array.data = AI_PTR(weights + 15664);
    conv2d_6_weights_array.data_start = AI_PTR(weights + 15664);
    depthwise_conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    depthwise_conv2d_2_bias_array.data = AI_PTR(weights + 15408);
    depthwise_conv2d_2_bias_array.data_start = AI_PTR(weights + 15408);
    depthwise_conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    depthwise_conv2d_2_weights_array.data = AI_PTR(weights + 13104);
    depthwise_conv2d_2_weights_array.data_start = AI_PTR(weights + 13104);
    conv2d_5_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_bias_array.data = AI_PTR(weights + 12848);
    conv2d_5_bias_array.data_start = AI_PTR(weights + 12848);
    conv2d_5_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_5_weights_array.data = AI_PTR(weights + 8752);
    conv2d_5_weights_array.data_start = AI_PTR(weights + 8752);
    conv2d_4_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_bias_array.data = AI_PTR(weights + 8688);
    conv2d_4_bias_array.data_start = AI_PTR(weights + 8688);
    conv2d_4_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_weights_array.data = AI_PTR(weights + 5616);
    conv2d_4_weights_array.data_start = AI_PTR(weights + 5616);
    depthwise_conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    depthwise_conv2d_1_bias_array.data = AI_PTR(weights + 5424);
    depthwise_conv2d_1_bias_array.data_start = AI_PTR(weights + 5424);
    depthwise_conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    depthwise_conv2d_1_weights_array.data = AI_PTR(weights + 3696);
    depthwise_conv2d_1_weights_array.data_start = AI_PTR(weights + 3696);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(weights + 3504);
    conv2d_3_bias_array.data_start = AI_PTR(weights + 3504);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(weights + 1968);
    conv2d_3_weights_array.data_start = AI_PTR(weights + 1968);
    conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_bias_array.data = AI_PTR(weights + 1936);
    conv2d_2_bias_array.data_start = AI_PTR(weights + 1936);
    conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_weights_array.data = AI_PTR(weights + 784);
    conv2d_2_weights_array.data_start = AI_PTR(weights + 784);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 768);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 768);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 640);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 640);
    depthwise_conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    depthwise_conv2d_bias_array.data = AI_PTR(weights + 608);
    depthwise_conv2d_bias_array.data_start = AI_PTR(weights + 608);
    depthwise_conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    depthwise_conv2d_weights_array.data = AI_PTR(weights + 320);
    depthwise_conv2d_weights_array.data_start = AI_PTR(weights + 320);
    conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_bias_array.data = AI_PTR(weights + 288);
    conv2d_bias_array.data_start = AI_PTR(weights + 288);
    conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_weights_array.data = AI_PTR(weights + 0);
    conv2d_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1443650,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}




#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

