// Copyright (C) 2009-2016 ETH Zurich
// Copyright (C) 2007?-2016 Center for Nanophase Materials Sciences, ORNL
// All rights reserved.
//
// See LICENSE.txt for terms of usage.
// See CITATION.txt for citation guidelines if you use this code for scientific publications.
//
// Author: Peter Staar (taa@zurich.ibm.com)
//
// This file implements the atomic convolution for NFFT.

#ifndef DCA_MATH_NFFT_NFFT_ATOMIC_CONVOLUTION_HPP
#define DCA_MATH_NFFT_NFFT_ATOMIC_CONVOLUTION_HPP

namespace dca {
namespace math {
namespace nfft {
// dca::math::nfft::

template <int max_count, int count>
struct nfft_atomic_convolution {
  template <typename scalar_type>
  inline static void execute_linear(scalar_type* f, scalar_type* M, scalar_type* y) {
    f[count] += (M[0 + 2 * count] * y[0] + M[1 + 2 * count] * y[1]);

    nfft_atomic_convolution<max_count, count + 1>::execute_linear(f, M, y);
  }

  template <typename scalar_type>
  inline static void execute_cubic(scalar_type* f, scalar_type* M, scalar_type* y) {
    f[count] += (M[0 + 4 * count] * y[0] + M[1 + 4 * count] * y[1] + M[2 + 4 * count] * y[2] +
                 M[3 + 4 * count] * y[3]);

    nfft_atomic_convolution<max_count, count + 1>::execute_cubic(f, M, y);
  }

  template <typename scalar_type>
  inline static void execute_M_y_2(scalar_type* f, scalar_type* M, int LDA, scalar_type* y) {
    execute_Mt_y_1(f, M + 0 * LDA, y + 0);
    execute_Mt_y_1(f, M + 1 * LDA, y + 1);
  }

  template <typename scalar_type>
  inline static void execute_M_y_4(scalar_type* f, scalar_type* M, int LDA, scalar_type* y) {
    execute_Mt_y_1(f, M + 0 * LDA, y + 0);
    execute_Mt_y_1(f, M + 1 * LDA, y + 1);
    execute_Mt_y_1(f, M + 0 * LDA, y + 2);
    execute_Mt_y_1(f, M + 1 * LDA, y + 3);
  }

  template <typename scalar_type>
  inline static void execute_Mt_y_1(scalar_type* f, scalar_type* M, scalar_type* y) {
    f[count] += M[count] * y[0];

    nfft_atomic_convolution<max_count, count + 1>::execute_Mt_y_1(f, M, y);
  }

  template <typename scalar_type>
  inline static void execute_Mt_y_2(scalar_type* f, scalar_type* M, scalar_type* y) {
    f[count] += (M[0 + 2 * count] * y[0] + M[1 + 2 * count] * y[1]);

    nfft_atomic_convolution<max_count, count + 1>::execute_Mt_y_2(f, M, y);
  }

  template <typename scalar_type>
  inline static void execute_Mt_y_4(scalar_type* f, scalar_type* M, scalar_type* y) {
    f[count] += (M[0 + 4 * count] * y[0] + M[1 + 4 * count] * y[1] + M[2 + 4 * count] * y[2] +
                 M[3 + 4 * count] * y[3]);

    nfft_atomic_convolution<max_count, count + 1>::execute_Mt_y_4(f, M, y);
  }
};

template <int max_count>
struct nfft_atomic_convolution<max_count, max_count> {
  template <typename scalar_type>
  inline static void execute_linear(scalar_type* /*f*/, scalar_type* /*y*/, scalar_type* /*M*/) {}

  template <typename scalar_type>
  inline static void execute_cubic(scalar_type* /*f*/, scalar_type* /*y*/, scalar_type* /*M*/) {}

  template <typename scalar_type>
  inline static void execute_Mt_y_2(scalar_type* /*f*/, scalar_type* /*M*/, scalar_type* /*y*/) {}

  template <typename scalar_type>
  inline static void execute_Mt_y_4(scalar_type* /*f*/, scalar_type* /*M*/, scalar_type* /*y*/) {}
};

}  // nfft
}  // math
}  // dca

#endif  // DCA_MATH_NFFT_NFFT_ATOMIC_CONVOLUTION_HPP