/*
 * SPDX-FileCopyrightText: Copyright (c) 1993-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MASKRCNN_CONFIG_HEADER
#define MASKRCNN_CONFIG_HEADER
#include "NvInfer.h"
#include <string>
#include <utility>
#include <vector>

namespace TLTMaskRCNNConfig
{
static const nvinfer1::Dims3 IMAGE_SHAPE{3, 832, 1344};

// Pooled ROIs
static int const POOL_SIZE = 7;
static int const MASK_POOL_SIZE = 14;

// Threshold to determine the mask area out of final convolution output
static float const MASK_THRESHOLD = 0.5;

// Bounding box refinement standard deviation for RPN and final detections.
static float const DETECTION_REG_WEIGHTS[] = {10, 10, 5, 5};

// Max number of final detections
static int const DETECTION_MAX_INSTANCES = 100;

// Minimum probability value to accept a detected instance
// ROIs below this threshold are skipped
static float const DETECTION_MIN_CONFIDENCE = 0;

// Non-maximum suppression threshold for detection
static float const DETECTION_NMS_THRESHOLD = 0.5;

// Size of the fully-connected layers in the classification graph
static int const FPN_CLASSIF_FC_LAYERS_SIZE = 1024;

// Size of the top-down layers used to build the feature pyramid
static int const TOP_DOWN_PYRAMID_SIZE = 256;

// Number of classification classes (including background)
static int const NUM_CLASSES = 1 + 90;

// Min and max level of fpn feature pyramids:
// p2, p3, p4, p5, p6.
static int const MIN_LEVEL = 2;
static int const MAX_LEVEL = 6;

// Length of minimum square anchor side in pixels
static float const RPN_ANCHOR_SCALE = 8;

// Ratios of anchors at each cell (width,height)
static const std::vector<std::pair<float, float>> ANCHOR_RATIOS
    = {std::make_pair(1.0F, 1.0F), std::make_pair(1.4F, 0.7F), std::make_pair(0.7F, 1.4F)};

// Anchor stride
// If 1 then anchors are created for each cell in the backbone feature map.
// If 2, then anchors are created for every other cell, and so on.
static int const RPN_ANCHOR_STRIDE = 1;

//  TRT fails if this number larger than kMAX_TOPK_K defined in engine/checkMacros.h
static int const MAX_PRE_NMS_RESULTS = 1000; // 3840;

// Non-max suppression threshold to filter RPN proposals.
// You can increase this during training to generate more propsals.
static float const RPN_NMS_THRESHOLD = 0.7F;

// ROIs kept after non-maximum suppression (training and inference)
static int const POST_NMS_ROIS_INFERENCE = 1000;

// COCO Class names
static const std::vector<std::string> CLASS_NAMES = {
    "BG",
    "person",
    "bicycle",
    "car",
    "motorcycle",
    "airplane",
    "bus",
    "train",
    "truck",
    "boat",
    "traffic light",
    "fire hydrant",
    "stop sign",
    "parking meter",
    "bench",
    "bird",
    "cat",
    "dog",
    "horse",
    "sheep",
    "cow",
    "elephant",
    "bear",
    "zebra",
    "giraffe",
    "backpack",
    "umbrella",
    "handbag",
    "tie",
    "suitcase",
    "frisbee",
    "skis",
    "snowboard",
    "sports ball",
    "kite",
    "baseball bat",
    "baseball glove",
    "skateboard",
    "surfboard",
    "tennis racket",
    "bottle",
    "wine glass",
    "cup",
    "fork",
    "knife",
    "spoon",
    "bowl",
    "banana",
    "apple",
    "sandwich",
    "orange",
    "broccoli",
    "carrot",
    "hot dog",
    "pizza",
    "donut",
    "cake",
    "chair",
    "couch",
    "potted plant",
    "bed",
    "dining table",
    "toilet",
    "tv",
    "laptop",
    "mouse",
    "remote",
    "keyboard",
    "cell phone",
    "microwave",
    "oven",
    "toaster",
    "sink",
    "refrigerator",
    "book",
    "clock",
    "vase",
    "scissors",
    "teddy bear",
    "hair drier",
    "toothbrush",
};

static const std::string MODEL_NAME = "mrcnn_nchw.uff";
static const std::string MODEL_INPUT = "Input";
static const nvinfer1::Dims3 MODEL_INPUT_SHAPE = IMAGE_SHAPE;
static const std::vector<std::string> MODEL_OUTPUTS = {"generate_detections", "mask_head/mask_fcn_logits/BiasAdd"};
static const nvinfer1::Dims2 MODEL_DETECTION_SHAPE{DETECTION_MAX_INSTANCES, 6};
static const nvinfer1::Dims4 MODEL_MASK_SHAPE{DETECTION_MAX_INSTANCES, NUM_CLASSES, 28, 28};
} // namespace TLTMaskRCNNConfig
#endif
