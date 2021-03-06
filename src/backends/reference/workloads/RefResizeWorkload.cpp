﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "RefResizeWorkload.hpp"

#include "RefWorkloadUtils.hpp"
#include "Resize.hpp"
#include "BaseIterator.hpp"
#include "Profiling.hpp"

#include "BaseIterator.hpp"
#include "Decoders.hpp"
#include "Encoders.hpp"

namespace armnn
{

void RefResizeWorkload::Execute() const
{
    ARMNN_SCOPED_PROFILING_EVENT(Compute::CpuRef, "RefResizeWorkload_Execute");

    const TensorInfo& inputInfo = GetTensorInfo(m_Data.m_Inputs[0]);
    const TensorInfo& outputInfo = GetTensorInfo(m_Data.m_Outputs[0]);

    std::unique_ptr<Decoder<float>> decoderPtr = MakeDecoder<float>(inputInfo, m_Data.m_Inputs[0]->Map());
    Decoder<float> &decoder = *decoderPtr;
    std::unique_ptr<Encoder<float>> encoderPtr = MakeEncoder<float>(outputInfo, m_Data.m_Outputs[0]->Map());
    Encoder<float> &encoder = *encoderPtr;

    Resize(decoder,
           inputInfo,
           encoder,
           outputInfo,
           m_Data.m_Parameters.m_DataLayout,
           m_Data.m_Parameters.m_Method,
           m_Data.m_Parameters.m_BilinearAlignCorners);
}

} //namespace armnn
