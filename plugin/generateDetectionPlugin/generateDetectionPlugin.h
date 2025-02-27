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

#ifndef TRT_GENERATE_DETECTION_PLUGIN_H
#define TRT_GENERATE_DETECTION_PLUGIN_H
#include <cuda_runtime_api.h>
#include <memory>
#include <string.h>
#include <string>
#include <vector>

#include "NvInfer.h"
#include "NvInferPlugin.h"
#include "common/kernels/maskRCNNKernels.h"
#include "multilevelProposeROI/tlt_mrcnn_config.h"

namespace nvinfer1
{
namespace plugin
{

class GenerateDetection : public IPluginV2Ext
{
public:
    GenerateDetection(
        int num_classes, int keep_topk, float score_threshold, float iou_threshold, nvinfer1::Dims const& image_size);

    GenerateDetection(void const* data, size_t length);

    ~GenerateDetection() noexcept override = default;

    int getNbOutputs() const noexcept override;

    Dims getOutputDimensions(int index, Dims const* inputs, int nbInputDims) noexcept override;

    int initialize() noexcept override;

    void terminate() noexcept override;

    void destroy() noexcept override;

    size_t getWorkspaceSize(int maxBatchSize) const noexcept override;

    int32_t enqueue(int32_t batch_size, void const* const* inputs, void* const* outputs, void* workspace,
        cudaStream_t stream) noexcept override;

    size_t getSerializationSize() const noexcept override;

    void serialize(void* buffer) const noexcept override;

    bool supportsFormat(DataType type, PluginFormat format) const noexcept override;

    char const* getPluginType() const noexcept override;

    char const* getPluginVersion() const noexcept override;

    IPluginV2Ext* clone() const noexcept override;

    void setPluginNamespace(char const* libNamespace) noexcept override;

    char const* getPluginNamespace() const noexcept override;

    DataType getOutputDataType(int index, nvinfer1::DataType const* inputTypes, int nbInputs) const noexcept override;

    bool isOutputBroadcastAcrossBatch(
        int outputIndex, bool const* inputIsBroadcasted, int nbInputs) const noexcept override;

    bool canBroadcastInputAcrossBatch(int inputIndex) const noexcept override;

    void attachToContext(
        cudnnContext* cudnnContext, cublasContext* cublasContext, IGpuAllocator* gpuAllocator) noexcept override;

    void configurePlugin(Dims const* inputDims, int nbInputs, Dims const* outputDims, int nbOutputs,
        DataType const* inputTypes, DataType const* outputTypes, bool const* inputIsBroadcast,
        bool const* outputIsBroadcast, PluginFormat floatFormat, int maxBatchSize) noexcept override;

    void detachFromContext() noexcept override;

private:
    void deserialize(int8_t const* data, size_t length);
    void check_valid_inputs(nvinfer1::Dims const* inputs, int nbInputDims) noexcept;

    int32_t mBackgroundLabel{};
    int32_t mNbClasses{};
    int32_t mKeepTopK{};
    float mScoreThreshold{};
    float mIOUThreshold{};

    int32_t mMaxBatchSize{};
    int32_t mAnchorsCnt{};
    std::shared_ptr<CudaBind<int32_t>> mValidCnt; // valid cnt = number of input rois for every image.
    nvinfer1::DataType mType{};
    RefineNMSParameters mParam{};
    std::shared_ptr<CudaBind<float>> mRegWeightDevice;

    nvinfer1::Dims mImageSize{};

    std::string mNameSpace;
};

class GenerateDetectionPluginCreator : public nvinfer1::pluginInternal::BaseCreator
{
public:
    GenerateDetectionPluginCreator() noexcept;

    ~GenerateDetectionPluginCreator() noexcept override{};

    char const* getPluginName() const noexcept override;

    char const* getPluginVersion() const noexcept override;

    PluginFieldCollection const* getFieldNames() noexcept override;

    IPluginV2Ext* createPlugin(char const* name, PluginFieldCollection const* fc) noexcept override;

    IPluginV2Ext* deserializePlugin(char const* name, void const* data, size_t length) noexcept override;

private:
    static PluginFieldCollection mFC;
    int32_t mNbClasses{};
    int32_t mKeepTopK{};
    float mScoreThreshold{};
    float mIOUThreshold{};
    static std::vector<PluginField> mPluginAttributes;
};
} // namespace plugin
} // namespace nvinfer1
#endif // TRT_GENERATE_DETECTION_PLUGIN_H
