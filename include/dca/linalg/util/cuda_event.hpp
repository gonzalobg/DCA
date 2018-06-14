// Copyright (C) 2018 ETH Zurich
// Copyright (C) 2018 UT-Battelle, LLC
// All rights reserved.
//
// See LICENSE for terms of usage.
// See CITATION.md for citation guidelines, if DCA++ is used for scientific publications.
//
// Author: Giovanni Balduzzi (gbalduzz@itp.phys.ethz.ch)
//
// RAII wrapper for cuda events.

#ifndef DCA_LINALG_UTIL_CUDA_EVENT_HPP
#define DCA_LINALG_UTIL_CUDA_EVENT_HPP
#ifdef DCA_HAVE_CUDA

#include <cuda.h>

namespace dca {
namespace linalg {
namespace util {
// dca::linalg::util::

class CudaEvent {
public:
  CudaEvent() {
    cudaEventCreate(&event_);
  }

  ~CudaEvent() {
    cudaEventDestroy(event_);
  }

  inline operator cudaEvent_t() {
    return event_;
  }

  void record(cudaStream_t stream) {
    cudaEventRecord(event_, stream);
  }

  void block() {
    cudaEventSynchronize(event_);
  }

  void block(cudaStream_t stream) {
    cudaStreamWaitEvent(stream, event_, 0);
  }

  operator bool() {
    return cudaEventQuery(event_);
  }

private:
  cudaEvent_t event_ = nullptr;
};

// Returns the elapsed time in seconds between two recorded events. Blocks host.
float elapsedTime(cudaEvent_t stop, cudaEvent_t start) {
  cudaEventSynchronize(stop);
  float msec(0);
  cudaEventElapsedTime(&msec, start, stop);
  return 1e-3 * msec;
}

}  // util
}  // linalg
}  // dca

#endif  // DCA_HAVE_CUDA
#endif  // DCA_LINALG_UTIL_CUDA_EVENT_HPP
